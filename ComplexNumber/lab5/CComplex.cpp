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
	if (real == 0)
	{
		throw invalid_argument("Invalide argument, Use: argument from real != 0.\n");
	}
	return atan2(image, real);
}

CComplex const CComplex::operator+(CComplex const& complex2) const
{
	return CComplex(real + complex2.real, image + complex2.image);
}

CComplex const CComplex::operator-(CComplex const& complex2) const
{
	return CComplex(real - complex2.real, image - complex2.image);
}

CComplex const CComplex::operator*(CComplex const& complex2) const
{
	double re, im;
	re = real * complex2.real - image * complex2.image;
	im = real * complex2.image + image * complex2.real;

	return CComplex(re, im);
}

CComplex const CComplex::operator/(CComplex const& divider) const
{
	if ((divider.Re() == 0) && (divider.Im() == 0))
	{
		throw invalid_argument("Error: division by zero!\n");
	}

	double re, im;
	re = (real * divider.real + image * divider.image) / (pow(divider.real, 2) + pow(divider.image, 2));
	im = (image * divider.real - real * divider.image) / (pow(divider.real, 2) + pow(divider.image, 2));

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

CComplex CComplex::operator+=(CComplex const& complex2)
{
	real += complex2.real;
	image += complex2.image;

	return *this;
}

CComplex CComplex::operator-=(CComplex const& complex2)
{
	real -= complex2.real;
	image -= complex2.image;

	return *this;
}

CComplex CComplex::operator*=(CComplex const& complex2)
{
	*this = *this * complex2;

	return *this;
}

CComplex CComplex::operator/=(CComplex const& divider)
{
	if ((divider.Re() == 0) && (divider.Im() == 0))
	{
		throw invalid_argument("Error: division by zero!\n");
	}

	*this = *this / divider;

	return *this;
}

bool CComplex::operator==(CComplex const& complex2) const
{
	return IsEqual(real, complex2.real) && IsEqual(image, complex2.image);
}

bool CComplex::operator!=(CComplex const& complex2) const
{
	return !(*this == complex2);
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