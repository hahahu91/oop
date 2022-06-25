#pragma once
#include <set>

enum class Operator
{
	Plus,
	Minus,
	Multiplication,
	Division,
	None
};
//не нужно статик Ћучше объ€вить inline const 
static const std::map<std::string, Operator> OPERATORS{
	{ "+", Operator::Plus },
	{ "-", Operator::Minus },
	{ "*", Operator::Multiplication },
	{ "/", Operator::Division }
};

struct FunctionData
{
	std::string firstOperand;
	std::string secondOperand;
	bool isCorrectVal = false;
	double value = std::numeric_limits<double>::quiet_NaN();
	Operator operatorType = Operator::None; // = operator None
};

class Calculate
{
public:
	bool Var(const std::string& var);
	//сделать отдьленьный метод double
	bool Let(const std::string& var, double val);
	bool Let(const std::string& var, const std::string& otherVar);
	bool Fn(const std::string& var, const std::string& otherVar);
	bool Fn(const std::string& var, const std::string& lOperand, Operator operatorType, const std::string& rOperand);
	double GetValue(const std::string& var);

	//
	void EnumerateVars(std::function<void(const std::string& varName, double value)> f) const;
	void EnumerateFunctions(std::function<void(const std::string& functionName, double value)> f);



private:
	//void CalculateFnValue(const std::string& functionName);
	void CalculateValueFn(const std::string& var);

	bool IsCorrectName(const std::string& var) const;
	// rename DoesVarExists, VarExistss
	bool VarExists(const std::string &var) const;
	bool FnExists(const std::string &var) const;

private :

	std::map<std::string, double> m_vars;
	std::map<std::string, FunctionData> m_fns;
	std::map<std::string, std::vector<std::string>> m_usedFns;
	std::map<std::string, std::set<std::string>> m_usedVars;
};
