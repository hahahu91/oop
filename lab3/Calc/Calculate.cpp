#include "pch.h"
#include "Calculate.h"
#include <iomanip>
#include <cmath>
#include <limits>


bool IsCharCorrect(char ch)
{
	return std::isalnum(ch) || ch == '_';
}

void UnionSets(std::set<std::string>& lhs, const std::set<std::string>& rhs)
{
	for (const auto& value : rhs)
	{
		lhs.insert(value);
	}
}

bool Calculate::IsCorrectName(const std::string& var) const
{
	if (var.empty() || isdigit(*var.begin()) || !std::all_of(var.begin(), var.end(), IsCharCorrect))
		return false;
	return true;
}

bool Calculate::Var(const std::string& var)
{
	if (!VarExists(var) && !FnExists(var) && IsCorrectName(var))
	{
		m_vars.insert({ var, std::numeric_limits<double>::quiet_NaN() });
		return true;
	}

	return false;
}

bool Calculate::Let(const std::string& var, double val)
{
	if (FnExists(var) || !IsCorrectName(var))
	{
		return false;
	}
		
	m_vars[var] = val;
	for (const auto& functionName : m_usedFns[var])
	{
		auto& fn = m_fns.at(functionName);
		fn.isCorrectVal = false;
	}
	
	return true;
}

bool Calculate::Let(const std::string& lhs, const std::string& rhs)
{
	if (FnExists(lhs) || rhs.empty())
	{
		return false;
	}
	if (!VarExists(lhs))
		if (!Var(lhs))
			return false;

	if (VarExists(rhs) || FnExists(rhs))
	{
		m_vars[lhs] = GetValue(rhs);

		for (const auto& functionName : m_usedFns[lhs])
		{
			auto& fn = m_fns.at(functionName);
			fn.isCorrectVal = false;
			//std::cout << "false " << functionName << std::endl;

		}

		return true;
	}	

	return false;
}

bool Calculate::VarExists(const std::string &var) const
{
	return m_vars.find(var) != m_vars.end();
}

bool Calculate::FnExists(const std::string &var) const
{
	return m_fns.find(var) != m_fns.end();
}

bool Calculate::Fn(const std::string& var, const std::string& initVar)
{
	if (FnExists(var) || VarExists(var) || !IsCorrectName(var))
		return false;
	if (!VarExists(initVar) && !FnExists(initVar))
		return false;

	FunctionData functionInfo;
	functionInfo.firstOperand = initVar;
	m_fns.insert(std::make_pair(var, functionInfo));

	if (VarExists(initVar))
	{
		m_usedVars[var].insert(initVar);
	}
	else
	{
		m_usedVars[var] = m_usedVars[initVar];
	}

	for (const auto& element : m_usedVars[var])
	{
		m_usedFns[element].push_back(var);
	}

	return true;

}

bool Calculate::Fn(const std::string& var, const std::string& lOperand, Operator operatorType, const std::string& rOperand)
{
	if (FnExists(var))
		return false;

	if ((VarExists(lOperand) || FnExists(lOperand)) && (VarExists(rOperand) || FnExists(rOperand)))
	{
		FunctionData functionInfo;
		functionInfo.firstOperand = lOperand;
		functionInfo.secondOperand = rOperand;
		functionInfo.operatorType = operatorType;

		m_fns.insert(std::make_pair(var, functionInfo));

		if (VarExists(lOperand))
		{
			m_usedVars[var].insert(lOperand);
		}
		else
		{
			UnionSets(m_usedVars[var], m_usedVars[lOperand]);
		}

		if (VarExists(rOperand))
		{
			m_usedVars[var].insert(rOperand);
		}
		else
		{
			UnionSets(m_usedVars[var], m_usedVars[rOperand]);
		}

		for (const auto& element : m_usedVars[var])
		{
			m_usedFns[element].push_back(var);
		}

		return true;
	}

	return false;
}

double Calculate::GetValue(const std::string& var)
{
	if (VarExists(var))
	{
		return m_vars.at(var);
	}
	else if (FnExists(var))
	{
		return CalculateValueFn(var);
	}
	return std::numeric_limits<double>::quiet_NaN();
}

double Calculate::CalculateValueFn(const std::string& var)
{
	auto & fn= m_fns.at(var);
	
	if (fn.isCorrectVal)
		return fn.value;

	double first = std::numeric_limits<double>::quiet_NaN();
	if (FnExists(fn.firstOperand))
	{
		first = CalculateValueFn(fn.firstOperand);
	}
	else if (VarExists(fn.firstOperand))
	{
		first = m_vars.at(fn.firstOperand);
	}

	double second = std::numeric_limits<double>::quiet_NaN();
	if (FnExists(fn.secondOperand))
	{
		second = CalculateValueFn(fn.secondOperand);
	}
	else if (VarExists(fn.secondOperand))
	{
		second = m_vars.at(fn.secondOperand);
	}

	double result = 0;
	switch (fn.operatorType)
	{
	case Operator::None:
		result = first;
		break;
	case Operator::Plus:
		result = first + second;
		break;
	case Operator::Minus:
		result = first - second;
		break;
	case Operator::Multiplication:
		result = first * second;
		break;
	case Operator::Division:
		result = first / second;
		break;
	default:
		result = std::numeric_limits<double>::quiet_NaN();
	}
	fn.value = result;
	fn.isCorrectVal = true;
	return result;
}

void Calculate::EnumerateVars(std::function <void(const std::string& varName, double value)> f) const
{
	for (auto& [name, value] : m_vars)
	{	
		f(name, value);
	}
	return;
}

void Calculate::EnumerateFunctions(std::function<void(const std::string& functionName, double value)> f) 
{
	for (auto& [name, _] : m_fns)
	{
		f(name, GetValue(name));
	}
	return;
}
