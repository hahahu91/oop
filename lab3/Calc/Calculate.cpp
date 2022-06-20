#include "pch.h"
#include "Calculate.h"
#include <iomanip>
#include <cmath>
#include <limits>


bool IsCharCorrect(char ch)
{
	return std::isalnum(ch) || ch == '_';
}

bool Calculate::IsCorrectName(const std::string& var) const
{
	if (var.empty() || isdigit(*var.begin()) || !std::all_of(var.begin(), var.end(), IsCharCorrect))
		return false;
	return true;
}

bool Calculate::Var(const std::string& var)
{
	if (!isVarExist(var) && !isFnExist(var) && IsCorrectName(var))
	{
		m_vars.insert({ var, std::numeric_limits<double>::quiet_NaN() });
		return true;
	}

	return false;
}

bool Calculate::Let(const std::string& var, double val)
{
	if (isFnExist(var))
	{
		return false;
	}
		
	m_vars[var] = val;
	return true;
}

bool Calculate::Let(const std::string& lhs, const std::string& rhs)
{
	if (isFnExist(lhs) || rhs.empty())
	{
		return false;
	}
	if (!isVarExist(lhs))
		if (!Var(lhs))
			return false;

	if (isVarExist(rhs) || isFnExist(rhs))
	{
		m_vars[lhs] = GetValue(rhs);
		return true;
	}	

	return false;
}

bool Calculate::isVarExist(const std::string &var) const
{
	return m_vars.find(var) != m_vars.end();
}

bool Calculate::isFnExist(const std::string &var) const
{
	return m_fns.find(var) != m_fns.end();
}

bool Calculate::Fn(const std::string& var, const std::string& initVar)
{
	if (isFnExist(var) || isVarExist(var))
		return false;

	if (isVarExist(initVar) || isFnExist(initVar))
	{
		FunctionData functionInfo;
		functionInfo.firstOperand = initVar;
		m_fns.insert(std::make_pair(var, functionInfo));
		return true;
	}

	return false;
}

bool Calculate::Fn(const std::string& var, const std::string& lOperand, Operator operatorType, const std::string& rOperand)
{
	if (isFnExist(var))
		return false;

	if ((isVarExist(lOperand) || isFnExist(lOperand)) && (isVarExist(rOperand) || isFnExist(rOperand)))
	{
		FunctionData functionInfo;
		functionInfo.firstOperand = lOperand;
		functionInfo.secondOperand = rOperand;
		functionInfo.operatorType = operatorType;

		m_fns.insert(std::make_pair(var, functionInfo));


		return true;
	}

	return false;
}

double Calculate::GetValue(const std::string& var) const
{
	if (isVarExist(var))
	{
		return m_vars.at(var);
	}
	else if (isFnExist(var))
	{
		return CalculateValueFn(var);
	}
	return std::numeric_limits<double>::quiet_NaN();
}

double Calculate::CalculateValueFn(const std::string& var) const
{
	std::string firstVar = m_fns.at(var).firstOperand;
	double first = std::numeric_limits<double>::quiet_NaN();

	if (isFnExist(firstVar))
	{
		first = CalculateValueFn(firstVar);
	}
	else if (isVarExist(firstVar))
	{
		first = m_vars.at(firstVar);
	}

	double second = std::numeric_limits<double>::quiet_NaN();

	std::string secondVar = m_fns.at(var).secondOperand;
	if (isFnExist(secondVar))
	{
		second = CalculateValueFn(secondVar);
	}
	else if (isVarExist(secondVar))
	{
		second = m_vars.at(secondVar);
	}
	
	switch (m_fns.at(var).operatorType)
	{
		case Operator::None:
			return first;
		case Operator::Plus:
			return first + second;
		case Operator::Minus:
			return first - second;
		case Operator::Multiplication:
			return first * second;
		case Operator::Division:
			return first / second;
		default:
			return std::numeric_limits<double>::quiet_NaN();
	}	
}

void Calculate::EnumerateVars(std::function <void(const std::string& varName, double value)> f) const
{
	for (auto& [name, value] : m_vars)
	{	
		f(name, value);
	}
	return;
}

void Calculate::EnumerateFunctions(std::function<void(const std::string& functionName, double value)> f) const
{
	for (auto& [name, _] : m_fns)
	{
		f(name, GetValue(name));
	}
	return;
}
