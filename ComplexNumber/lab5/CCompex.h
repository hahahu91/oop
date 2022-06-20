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

	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(CComplex const& complex2);
	CComplex& operator-=(CComplex const& complex2);
	CComplex& operator*=(CComplex const& complex2);
	CComplex& operator/=(CComplex const& complex2);

private:
	double real;
	double image;
};

CComplex const operator+(CComplex const& complex1, CComplex const& complex2);
CComplex const operator-(CComplex const& complex1, CComplex const& complex2);
CComplex const operator*(CComplex const& complex1, CComplex const& complex2);
CComplex const operator/(CComplex const& complex1, CComplex const& complex2);

bool operator==(CComplex const& complex1, CComplex const& complex2);
bool operator!=(CComplex const& complex1, CComplex const& complex2);

std::ostream& operator<<(std::ostream& stream, CComplex const &complex);
std::istream& operator>>(std::istream& stream, CComplex& complexNumber);