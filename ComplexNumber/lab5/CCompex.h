#pragma once
class CComplex
{
public:
	// инициализация комплексного числа значениями действительной и мнимой частей
	CComplex(double real = 0, double image = 0);
	// возвращает действительную часть комплексного числа
	double Re() const;
	// возвращает мнимую часть комплексного числа
	double Im() const;
	// возвращает модуль комплексного числа
	double GetMagnitude() const;
	// возвращает аргумент комплексного числа
	double GetArgument() const;
	CComplex const operator+(CComplex const& complex2) const;
	CComplex const operator-(CComplex const& complex2) const;
	CComplex const operator*(CComplex const& complex2) const;
	CComplex const operator/(CComplex const& complex2) const;
	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex operator+=(CComplex const& complex2);
	CComplex operator-=(CComplex const& complex2);
	CComplex operator*=(CComplex const& complex2);
	CComplex operator/=(CComplex const& complex2);
	bool operator==(CComplex const& complex2) const;
	bool operator!=(CComplex const& complex2) const;

private:
	double real;
	double image;
};
