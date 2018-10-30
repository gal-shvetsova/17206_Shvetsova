#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>
#include <string>

using std::string;

class calc_except : public std::exception
{
public:
	virtual const char* what() const noexcept { return NULL; };
};

class empty_stack : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Stack is empty";
	}
};

class empty_args : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Not enough arguments";
	}
};

class negative_number : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Negative argument";
	}
};

class division_by_zero : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Division by zero";
	}
};

class nodefinition : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "No definition for the variable";
	}
};

class no_operation : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Operation is not exist";
	}
};

class invalid_arg : public calc_except
{
public:
	const char* what() const noexcept override
	{
		return "Invalid argument";
	}
};

#endif
#pragma once
