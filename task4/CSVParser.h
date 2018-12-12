#pragma once
#include <vector>
#include <tuple>

const char DEFAULT_LINE_DEL = '\n';
const char DEAFULT_COLOUMN_DEL = ',';
const char DEFAULT_ESCAPED = '\\';

template <typename... Args>

class CSVParser
{
public:
	CSVParser(std::istream& stream, size_t skipLines) : stream(stream);
	~CSVParser();
	template <typename T>;
	friend class inputIterator
	{
	public:

		inputIterator(const inputIterator& iter) : parser(iter.parser);
		inputIterator& operator=(const inputIterator& iter);
		
		bool operator==(inputIterator const&) const;
		bool operator!=(inputIterator const&) const;

		const T& operator*();
		const T& operator->(); //?

		inputIterator& operator++();

	private:

		size_t index = 0;
		CSVParser<Args...>* parser;
		friend CSVParser<Args...>;
	};  

private:
	std::vector<std::tuple<Args...>> storedLines;
	std::istream& stream;
	char lineDel = DEFAULT_LINE_DEL;
	char coloumnDel = DEAFULT_COLOUMN_DEL;
	char escaped = DEFAULT_ESCAPED;
};

