#include "pch.h"
#include "lab5/CCompex.h"
#include "lab5/MathFunctions.h"

TEST_CASE("standarts complex methods")
{
	CComplex complex(3.45, -2);

	CHECK(complex.Re() == 3.45);
	CHECK(complex.Im() == -2);

	CHECK(IsEqual(complex.GetMagnitude(), 3.9878));
	CHECK(IsEqual(complex.GetArgument(), -0.5254));
}

TEST_CASE("addition of complex numbers by operator +")
{
	CComplex a(3.0, 5);
	CComplex b(23.0, -3);
	CComplex c = a + b;
	CComplex d = b + 4;
	CComplex result(26.0, 2);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 27.0);
	CHECK(d.Im() == -3.0);

	a += b;
	b += 7;
	CHECK(a.Re() == c.Re());
	CHECK(a.Im() == c.Im());
	CHECK(b.Re() == 30.0);
	CHECK(b.Im() == -3);
}
TEST_CASE("sub of complex numbers by operator -")
{
	CComplex a(3.0, 5);
	CComplex b(23.0, -3);
	CComplex c = a - b;
	CComplex d = b - 3;
	CComplex result(-20.0, 8);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 20.0);
	CHECK(d.Im() == -3.0);

	a -= b;
	b -= 3;
	CHECK(a.Re() == result.Re());
	CHECK(a.Im() == result.Im());
	CHECK(b.Re() == 20.0);
	CHECK(b.Im() == -3.0);
}
TEST_CASE("mult of complex numbers by operator *")
{
	CComplex a(3.0, 5);
	CComplex b(2.0, -3);
	CComplex c = a * b;
	CComplex d = b * 3;
	CComplex result(21, 1);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 6.0);
	CHECK(d.Im() == -9.0);

	a *= b;
	b *= 3;

	CHECK(a.Re() == result.Re());
	CHECK(a.Im() == result.Im());
	CHECK(b.Re() == 6.0);
	CHECK(b.Im() == -9.0);
}
TEST_CASE("del of complex numbers by operator /")
{
	CComplex a(8.0, 6);
	CComplex b(4.0, -2);
	CComplex c = a / b;
	CComplex d = a / 2;
	CComplex result(1, 2);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 4.0);
	CHECK(d.Im() == 3.0);
}
TEST_CASE("Unary operators")
{
	CComplex a(8.0, 6);
	CComplex b(4.0, -2);
	CComplex c = -a;
	CComplex d = +b;
	CComplex result(-8, -6);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 4.0);
	CHECK(d.Im() == -2.0);
}

TEST_CASE("Equal operators")
{
	CComplex a(8.0, 6);
	CComplex b(8.0, 6);
	CHECK(a == b);

}