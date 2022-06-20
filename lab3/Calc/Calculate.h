#pragma once

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
	double GetValue(const std::string& var) const;

	//
	void EnumerateVars(std::function<void(const std::string& varName, double value)> f) const;
	void EnumerateFunctions(std::function<void(const std::string& functionName, double value)> f) const;



private:
	double CalculateValueFn(const std::string& var) const;

	bool IsCorrectName(const std::string& var) const;
	// rename DoesVarExist, VarExists
	bool isVarExist(const std::string &var) const;
	bool isFnExist(const std::string &var) const;

private :

	std::map<std::string, double> m_vars;
	std::map<std::string, FunctionData> m_fns;
};
