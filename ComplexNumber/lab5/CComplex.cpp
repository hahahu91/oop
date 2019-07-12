#pragma once
#include "pch.h"
#include "CCompex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdexcept>
#include "MathFunctions.h"

using namespace std;

// инициализация комплексного числа значениями действительной и мнимой частей
CComplex::CComplex(double real, double image)
	: real(real)
	, image(image)
{}
// возвращает действительную часть комплексного числа
double CComplex::Re() const
{
	return real;
}
// возвращает мнимую часть комплексного числа
double CComplex::Im() const
{
	return image;
}
// возвращает модуль комплексного числа
double CComplex::GetMagnitude() const
{
	return sqrt(pow(real, 2) + pow(image, 2));
}
// возвращает аргумент комплексного числа
double CComplex::GetArgument() const
{
	if (real == 0 && image == 0)
	{
		throw invalid_argument("Invalide argument, Use: argument from real != 0 or image != 0.\n");
	}
	return atan2(image, real);
}

CComplex const operator+(CComplex const& complex1, CComplex const& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());
}

CComplex const operator-(CComplex const& complex1, CComplex const& complex2)
{
	return CComplex(complex1.Re() - complex2.Re(), complex1.Im() - complex2.Im());
}

CComplex const operator*(CComplex const& complex1, CComplex const& complex2)
{
	double re, im;
	re = complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im();
	im = complex1.Re() * complex2.Im() + complex1.Im() * complex2.Re();

	return CComplex(re, im);
}

CComplex const operator/(CComplex const& complex1, CComplex const& divider)
{
	if ((divider.Re() == 0) && (divider.Im() == 0))
	{
		throw invalid_argument("Error: division by zero!\n");
	}

	double re, im;
	re = (complex1.Re() * divider.Re() + complex1.Im() * divider.Im()) / (pow(divider.Re(), 2) + pow(divider.Im(), 2));
	im = (complex1.Im() * divider.Re() - complex1.Re() * divider.Im()) / (pow(divider.Re(), 2) + pow(divider.Im(), 2));

	return CComplex(re, im);
}

CComplex const CComplex::operator+() const
{
	return *this;
}

CComplex const CComplex::operator-() const
{
	return CComplex(-real, -image);
}

CComplex& CComplex::operator+=(CComplex const& complex2)
{
	real += complex2.real;
	image += complex2.image;

	return *this;
}

CComplex& CComplex::operator-=(CComplex const& complex2)
{
	real -= complex2.real;
	image -= complex2.image;

	return *this;
}

CComplex& CComplex::operator*=(CComplex const& complex2)
{
	*this = *this * complex2;

	return *this;
}

CComplex& CComplex::operator/=(CComplex const& divider)
{
	if ((divider.Re() == 0) && (divider.Im() == 0))
	{
		throw invalid_argument("Error: division by zero!\n");
	}

	*this = *this / divider;

	return *this;
}

bool operator==(CComplex const& complex1, CComplex const& complex2)
{
	return IsEqual(complex1.Re(), complex2.Re()) && IsEqual(complex1.Im(), complex2.Im());
}

bool operator!=(CComplex const& complex1, CComplex const& complex2)
{
	return !(complex1 == complex2);
}

std::ostream& operator<<(std::ostream& stream, CComplex const& complexNumber)
{
	if (complexNumber.Re() != 0 && complexNumber.Im() > 0)
	{
		stream << complexNumber.Re() << '+' << complexNumber.Im() << 'i';
	}
	else if (complexNumber.Re() != 0 && complexNumber.Im() < 0)
	{
		stream << complexNumber.Re() << complexNumber.Im() << 'i';
	}
	else if (complexNumber.Im() == 0)
	{
		stream << complexNumber.Re();
	}
	else if (complexNumber.Re() == 0 && complexNumber.Im() != 0)
	{
		stream << complexNumber.Im() << 'i';
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CComplex &complexNumber)
{
	double re = 0;
	double im = 0;

	if ((stream >> re) && (stream >> im) && (stream.get() == 'i'))
	{
		complexNumber = CComplex(re, im);
	}

	return stream;
}