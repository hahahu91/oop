#include "pch.h"
#include "lab5/CCompex.h"
#include "lab5/MathFunctions.h"
#include <sstream>

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
	CComplex e(1), f(2), g(3); // какие-то числа
	(e += f) += g;
	CHECK(e.Re() == 6);
	CHECK(f.Re() == 2);
	CHECK(g.Re() == 3);
	// a == 6, а у вас a будет равен 3 (c прибавится к временной копии a, возвращённоё из a += b)
	// b == 2
	// c == 3
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
	CComplex e = 3 * b;
	CComplex result(21, 1);

	CHECK(c.Re() == result.Re());
	CHECK(c.Im() == result.Im());
	CHECK(d.Re() == 6.0);
	CHECK(d.Im() == -9.0);
	CHECK(e.Re() == 6.0);
	CHECK(e.Im() == -9.0);

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
	CComplex c(8);
	CHECK(c == 8);
	CHECK(8 == c);

}

TEST_CASE("operators << & >>")
{
	std::stringstream input;
	std::ostringstream output;

	output << CComplex(-1.24, -2.5) << std::endl;
	output << CComplex(1.24, 2.5) << std::endl;
	output << CComplex(-3, 2.5) << std::endl;
	output << CComplex(3, -2.5) << std::endl;
	output << CComplex(3, 0) << std::endl;
	output << CComplex(0, 6.2) << std::endl;
	output << CComplex(0, 0) << std::endl;

	CHECK(output.str() == "-1.24-2.5i\n"
						  "1.24+2.5i\n"
						  "-3+2.5i\n"
						  "3-2.5i\n"
						  "3\n"
						  "6.2i\n"
						  "0\n");
	input << "-1.24-2.5i\n"
				"1.24+2.5i\n"
				"-3+2.5i\n"
				"3-2.5i\n"
				"3\n"
				"6.2i\n"
				"0\n";
	CComplex c1, c2, c3, c4, c5, c6, c7;
	input >> c1 >> c2 >> c3>> c4 >> c5 >> c6 >> c7;
	CComplex res1(-1.24, -2.5), res2(1.24, 2.5), res3(-3, 2.5);
	CHECK(c2 == res2);
	CHECK(c3 == res3);
}
