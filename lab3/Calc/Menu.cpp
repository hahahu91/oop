#include "pch.h"
#include "Menu.h"
#include <iostream>    
#include <iomanip> 

Menu::Menu(Calculate& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", bind(&Menu::Var, this, std::placeholders::_1) },
		  { "let", bind(&Menu::Let, this, std::placeholders::_1) },
		  { "fn", bind(&Menu::Fn, this, std::placeholders::_1) },
		  { "print", bind(&Menu::Print, this, std::placeholders::_1) },
		  { "printvars", bind(&Menu::PrintVars, this, std::placeholders::_1) },
		  { "printfns", bind(&Menu::PrintFns, this, std::placeholders::_1) } })
{
}

bool Menu::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool Menu::Var(std::istream& args)
{
	std::string var;
	args >> var;
	if (m_calc.Var(var))
	{
		return true;
	}
	m_output << "Invalid name of varible!" << std::endl;
	return false;
}

bool Menu::ParseStrToValue(const std::string& expression, std::string& firstValue, std::string& secondValue)
{
	auto parsePosition = expression.find("=");

	if (parsePosition == std::string::npos)
	{
		return false;
	}
	firstValue = expression.substr(0, parsePosition);
	secondValue = expression.substr(parsePosition + 1, expression.size());
	return true;
}


bool Menu::ParseStrWithOperation(const std::string& expression, std::string& firstValue, Operator& operand, std::string& secondValue)
{
	auto operandPos = std::string::npos;

	for (auto& elem : OPERATORS)
	{
		operandPos = expression.find(elem.first);
		if (operandPos != std::string::npos)
		{
			operand = elem.second;
			break;
		}
	}

	if (operandPos != std::string::npos)
	{
		firstValue = expression.substr(0, operandPos);
		secondValue = expression.substr(operandPos + 1, expression.size());
		return true;
	}

	return false;
}

bool Menu::Let(std::istream& args)
{
	std::string str, value1, value2;
	args >> str;
	if (ParseStrToValue(str, value1, value2))
	{
		if (isdigit(*value2.begin()))
			if (m_calc.Let(value1, std::stod(value2)))
				return true;

		if (m_calc.Let(value1, value2))
		{
			return true;
		}
	}

	m_output << "Invalid expression!" << std::endl;
	return false;
}

bool Menu::Fn(std::istream& args)
{
	std::string expression;
	args >> expression;
	std::string firstValue, secondValue, thirdValue, fourthValue;
	Operator expressionOperator;

	if ((!ParseStrToValue(expression, firstValue, secondValue) || !m_calc.Fn(firstValue, secondValue)) 
		&& (!ParseStrWithOperation(secondValue, thirdValue, expressionOperator, fourthValue) || !m_calc.Fn(firstValue, thirdValue, expressionOperator, fourthValue)))
	{
		m_output << "Invalid expression!" << std::endl;
		return false;
	}
	return true;
}


bool Menu::Print(std::istream& args)
{
	std::string var;
	args >> var;

	double value = m_calc.GetValue(var);

		m_output << std::fixed << std::setprecision(2) << value << std::endl;
		return true;
}

bool Menu::PrintVars([[maybe_unused]]std::istream& args)
{
	m_calc.EnumerateVars([&](const std::string &first, double value) {
		m_output << first << ":" << std::setprecision(2) << std::fixed << value << std::endl; 
	});

	return true;
}

bool Menu::PrintFns([[maybe_unused]]std::istream& args)
{
	m_calc.EnumerateFunctions([&](const std::string& first, double value) {
		m_output << first << ":" << std::setprecision(2) << std::fixed << value << std::endl;
	});
	return true;
}