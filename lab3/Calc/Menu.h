#pragma once
#include "Calculate.h"
#include <boost/noncopyable.hpp>

class Menu : boost::noncopyable
{
public:
	Menu(Calculate& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool Var(std::istream& args);
	bool Let(std::istream& args);
	bool Fn(std::istream& args);

	bool Print(std::istream& args);
	bool PrintVars(std::istream& args);
	bool PrintFns(std::istream& args);
	bool ParseStrToValue(const std::string& str, std::string& firstValue, std::string& secondValue);
	bool ParseStrWithOperation(const std::string& expression, std::string& firstValue, Operator& operand, std::string& secondValue);


private:
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	Calculate& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
