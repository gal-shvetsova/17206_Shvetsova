
#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <exception>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace csv {

	const char DEFAULT_LINE_DELIMITER = '\n';
	const char DEFAULT_COLOUMN_DELIMITER = ',';
	const char DEFAULT_ESCAPING_SYMBOL = '\\';

	class CSVParseException : public std::exception {
	public:
		CSVParseException(const std::string& desc) : desc(desc) {}

		CSVParseException(const std::string& desc, size_t line, size_t pos)
			: desc(desc + " at line " + std::to_string(line) + " position " +
				std::to_string(pos) + ".") {}

		const char* what() const noexcept override { return desc.c_str(); }

	private:
		const std::string desc;
	};

	template <size_t position>
	struct pos_type {
		static const size_t pos = position;
	};

	template <typename... Args>

	class CSVParser {
	public:
		template <typename T>
		class iterator {
		public:
			iterator(const iterator& iter) : parser(iter.parser) {}

			iterator& operator=(const iterator& iter) {
				parser = iter.parser;
				position = iter.position;
				return (*this);
			}

			bool operator==(iterator const& iter) const {
				return parser == iter.parser &&
					(parser == nullptr || position == iter.position);
			}

			bool operator!=(iterator const& iter) const { return !operator==(iter); }

			const T& operator*() const throw(CSVParseException) {
				if (parser == nullptr || !parser->hasLine(position))
					throw CSVParseException("Error reading line");

				return parser->storedLines[position];
			}

			const T& operator->() const throw(CSVParseException) {
				if (parser == nullptr || !parser->hasLine(position))
					throw CSVParseException("Error reading line");

				return parser->storedLines[position];
			}

			iterator& operator++() throw(CSVParseException) {
				if (parser == nullptr || !parser->hasLine(position))
					throw CSVParseException("Error reading more lines.");

				position++;

				if (!parser->hasLine(position))
					parser = nullptr;

				return (*this);
			}

		private:
			size_t position = 0;
			CSVParser<Args...>* parser;

			iterator(CSVParser<Args...>* parser) : parser(parser) {}

			friend CSVParser<Args...>;
		};  // class iterator

		CSVParser(std::istream& stream, size_t skipLines) : stream(stream) {
			for (size_t i = 0; i < skipLines; i++) {
				std::string line;
				if (!std::getline(stream, line))
					throw CSVParseException("Unexpected EOF while skipping first lines.");
			}
		}

		CSVParser() = delete;

		CSVParser& operator=(const CSVParser& parser) {
			storedLines = parser.storedLines;
			stream = parser.stream;
			return (*this);
		}

		iterator<std::tuple<Args...>> begin() {
			return iterator<std::tuple<Args...>>(this);
		}

		iterator<std::tuple<Args...>> end() {
			return iterator<std::tuple<Args...>>(nullptr);
		}

		void setLineDelimiter(const char delim) { lineDelimiter = delim; }

		void setColoumnDelimiter(const char delim) { coloumnDelimiter = delim; }

		void setEscapingSymbol(const char sub) { escapingSymbol = sub; }

	private:
		std::vector<std::tuple<Args...>> storedLines;
		std::istream& stream;

		char lineDelimiter = DEFAULT_LINE_DELIMITER;
		char coloumnDelimiter = DEFAULT_COLOUMN_DELIMITER;
		char escapingSymbol = DEFAULT_ESCAPING_SYMBOL;

		std::string readColoumnWithEscapeing(std::istream& stream, size_t& position) const throw(CSVParseException) {
			std::ostringstream result;
			std::string coloumn;
			bool isMultiColoumn = false;

			while (std::getline(stream, coloumn, coloumnDelimiter)) {
				position += coloumn.size();
				if (coloumn[coloumn.size() - 1] == escapingSymbol) {
					result << coloumn.substr(0, coloumn.size() - 1) << coloumnDelimiter;
					isMultiColoumn = true;
				}
				else {
					result << coloumn;
					isMultiColoumn = false;
					break;
				}
			}

			if (isMultiColoumn && stream.eof())
				throw CSVParseException("Unexpected EOL", storedLines.size() + 1,
					position);

			return result.str();
		}

		template <typename tuple, size_t N>
		auto readColoumn(std::istream& stream, pos_type<N>, size_t& position) const throw(CSVParseException) {
				typename std::tuple_element<std::tuple_size<tuple>::value - N, tuple>::type
					coloumn;
				std::istringstream coloumnStream(
					readColoumnWithEscapeing(stream, position));
				if (coloumnStream >> coloumn)
					return std::tuple_cat(
						std::make_tuple(coloumn),
						readColoumn<tuple, N - 1>(stream, pos_type<N - 1>(), position));
				if (coloumnStream.eof())
					throw CSVParseException("Unexpected EOL", storedLines.size() + 1,
						position);
				throw CSVParseException("Coloumn type error", storedLines.size() + 1,
					position);
		}

		template <typename tuple, size_t N>
		auto readColoumn(std::istream& stream, pos_type<1>, size_t& position) const throw(CSVParseException) {
				typename std::tuple_element<std::tuple_size<tuple>::value - 1, tuple>::type
					coloumn;
				std::istringstream coloumnStream(
					readColoumnWithEscapeing(stream, position));
				if (coloumnStream >> coloumn)
					return std::make_tuple(coloumn);
				if (coloumnStream.eof())
					throw CSVParseException("Unexpected EOL", storedLines.size() + 1, position);
				throw CSVParseException("Coloumn type error", storedLines.size() + 1, position);
		}

		bool readLine() throw(CSVParseException) {
			std::string str;
			if (!std::getline(stream, str, lineDelimiter))
				return false;

			std::istringstream line(str);
			size_t pos = 0;
			storedLines.push_back(readColoumn<std::tuple<Args...>, sizeof...(Args)>(
				line, pos_type<sizeof...(Args)>(), pos));

			if (!line.eof())
				throw CSVParseException("Wrong coloumns number", storedLines.size(), pos);

			return true;
		}

		bool hasLine(size_t pos) throw(CSVParseException) {
			if (pos < storedLines.size())
				return true;

			size_t count = pos - storedLines.size() + 1;
			for (size_t i = 0; i < count; i++)
				if (!readLine())
					return false;

			return true;
		}

		friend class iterator<std::tuple<Args...>()>;
	};

	template <typename Ch, typename Tr, typename tuple, size_t N>
	static void printTuple(std::basic_ostream<Ch, Tr>& os,
		const tuple& value,
		pos_type<N>) {
		os << std::get<std::tuple_size<tuple>::value - N>(value) << " | ";
		printTuple<Ch, Tr, tuple, N - 1>(os, value, pos_type<N - 1>());
	}

	template <typename Ch, typename Tr, typename tuple, size_t N>
	static void printTuple(std::basic_ostream<Ch, Tr>& os,
		const tuple& value,
		pos_type<1>) {
		os << std::get<std::tuple_size<tuple>::value - 1>(value);
	}

}  // namespace csv

template <typename Ch, typename Tr, typename... Types>
std::ostream& operator<<(std::basic_ostream<Ch, Tr>& os,
	const std::tuple<Types...>& value) {
	csv::printTuple<Ch, Tr, std::tuple<Types...>, sizeof...(Types)>(
		os, value, csv::pos_type<sizeof...(Types)>());
	return os;
}

#endif /* CSV_PARSER_H */
