#include "pch.h"
#include "../Calc/pch.h"
#include "../Calc/Calculate.h"
#include "../Calc/Menu.h"
#include <time.h>

SCENARIO("Calculate")
{
	Calculate calc;
	SECTION("Can add new var")
	{
		CHECK(calc.Var("sqrt"));
		THEN("Var initialized NAN")
		{
			CHECK(std::isnan(calc.GetValue("sqrt")));
		}
		AND_WHEN("try adding a variable that already exist")
		{
			THEN("there will be an error")
			{
				CHECK(!calc.Var("sqrt"));
			}
		}
	}
	SECTION("Can let var")
	{
		SECTION("can let the value new var")
		{
			CHECK(calc.Let("x515", 5.15));
			CHECK(calc.Let("x0", 0));
			CHECK(calc.GetValue("x0") == 0);
			CHECK(calc.GetValue("x515") == 5.15);
		}
		SECTION("can let the value initialized var")
		{
			CHECK(calc.Var("sqrt4"));
			CHECK(std::isnan(calc.GetValue("sqrt4")));
			CHECK(calc.Let("sqrt4", 2));
			CHECK(calc.GetValue("sqrt4") == 2);

			SECTION("can also set a value from another variable")
			{
				CHECK(calc.Let("sqrt", "sqrt4"));
				CHECK(calc.GetValue("sqrt") == 2);
				WHEN("try to install a variable with the name of an existing function.")
				{
					calc.Let("num", 25);
					CHECK(calc.Fn("numFn", "num"));
					CHECK(!calc.Let("numFn", 5));

				}
			}
		}
		
		SECTION("it is impossible to set a value from not initialized variable")
		{
			CHECK(!calc.Let("sqrt", "sqrt5"));
		}
		SECTION("cannot set an empty value of the variable")
		{
			CHECK(!calc.Let("empty", ""));
		}
	}
	SECTION("functions from Var")
	{
		WHEN("can dec new fn from init var")
		{
			calc.Let("num", 25);
			CHECK(calc.Fn("numFn", "num"));
			THEN("this fn has value this var")
			{
				CHECK(calc.GetValue("num") == 25);
				CHECK(calc.GetValue("numFn") == 25);
			}
			AND_THEN("fn returns the value of the variable at the time of calling the function and not at the time of creation")
			{
				calc.Let("num", 45);
				CHECK(calc.GetValue("numFn") == 45);
			}
		}
		WHEN("can dec new fn from not init var")
		{
			THEN("not can dec Fn")
			{
				CHECK(!calc.Fn("FnFromNotInitVar", "notInitVar"));
			}
		}
		WHEN("can dec new fn from var with a value that is Nan")
		{
			calc.Var("newVar");
			THEN("value Fn will is Nan")
			{
				CHECK(calc.Fn("FnNanVar", "newVar"));
				CHECK(std::isnan(calc.GetValue("FnNanVar")));
				calc.Let("newVar", 5.22);
				CHECK(calc.GetValue("FnNanVar") == 5.22);
			}
		}
	}
	SECTION("functions with operation")
	{
		WHEN("can dec new fn")
		{
			calc.Let("x", 3);
			calc.Let("y", 5);

			CHECK(calc.Fn("XPlusY", "x", Operator::Plus, "y"));
			THEN("this fn will meaning of this expression")
			{
				CHECK(calc.GetValue("XPlusY") == 8);
			}

			WHEN("can dec new fn from exist fn with operation")
			{
				CHECK(calc.Fn("xPlusXPlusY", "x", Operator::Plus, "XPlusY"));
				THEN("this fn will meaning of this expression")
				{
					CHECK(calc.GetValue("xPlusXPlusY") == 11);
				}

				CHECK(calc.Fn("XPlusYMinusY", "XPlusY", Operator::Minus, "y"));
				THEN("this fn will meaning of this expression")
				{
					CHECK(calc.GetValue("XPlusYMinusY") == 3);
				}
			}
		}
		WHEN("can dec new fn with indefinite values ")
		{
			calc.Let("x", 3);
			calc.Var("y");
			THEN("this fn will meaning of this expression")
			{
				CHECK(calc.Fn("XPlusY", "x", Operator::Plus, "y"));
				CHECK(std::isnan(calc.GetValue("XPlusY")));
				calc.Let("y", 5);
				CHECK(calc.GetValue("XPlusY") == 8);
				calc.Var("z");
				CHECK(calc.Fn("XPlusYPlusZ", "XPlusY", Operator::Plus, "z"));

				CHECK(std::isnan(calc.GetValue("XPlusYPlusZ")));
			}
		}
	}
}
SCENARIO("Examples")
{
	Calculate calc;
	SECTION("announcement, assignment and withdrawal of variables")
	{
		calc.Var("x");
		THEN("value X has not yet been defined")
		{
			CHECK(std::isnan(calc.GetValue("x")));
		}
		calc.Let("x", 42);
		CHECK(calc.GetValue("x") == 42);
		calc.Let("x", 1.234);
		THEN("The value of the variable can be changed")
		{
			CHECK(calc.GetValue("x") == 1.234);
		}
		WHEN("Automatically declare a variable Y and assign it the current value of X")
		{
			calc.Let("y", "x");
			calc.Let("x", 99);
			THEN("The variable y stores the value of the x. Subsequent manipulations over X do not affect it.")
			{
				CHECK(calc.GetValue("x") == 99);
				CHECK(calc.GetValue("y") == 1.234);
			}
		}
	}

	SECTION("Announcement of fns")
	{
		calc.Var("x");
		calc.Var("y");
		calc.Fn("XPlusY", "x", Operator::Plus, "y");

		THEN("value of fn is not determined, because the values of its arg are not defined")
		{
			CHECK(std::isnan(calc.GetValue("XPlusY")));
		}
		calc.Let("x", 3);
		calc.Let("y", 4);
		THEN("value of the function is determined")
		{
			CHECK(calc.GetValue("XPlusY") == 7);
		}
		calc.Let("x", 10);
		calc.Let("y", 4);
		THEN("value of the fn depends on the val of its arg")
		{
			CHECK(calc.GetValue("XPlusY") == 14);
		}
		calc.Let("z", 3.5);
		calc.Fn("XPlusYDivZ", "XPlusY", Operator::Division, "z");
		THEN("value of the fn can depend on the val of other fn")
		{
			CHECK(calc.GetValue("XPlusY") == 14);
			CHECK(calc.GetValue("XPlusYDivZ") == 4);
		}
	}

	SECTION("About the difference between fn and let")
	{
		calc.Let("v", 42);
		calc.Let("variable", "v");
		calc.Fn("function", "v");
		calc.Let("v", 43);
		CHECK(calc.GetValue("variable") == 42);
		CHECK(calc.GetValue("function") == 43);
	}

	SECTION("Calc of the area of the circle")
	{
		calc.Var("radius");
		calc.Let("pi", 3.14159265);
		CHECK(calc.Fn("radiusSquared", "radius", Operator::Multiplication, "radius"));
		CHECK(calc.Fn("circleArea", "pi", Operator::Multiplication, "radiusSquared"));
		CHECK(calc.Let("radius", 10)); 
		CHECK(calc.GetValue("circleArea") == 314.159265);
		CHECK(calc.Let("circle10Area", "circleArea"));
		CHECK(calc.Let("radius", 20));
		CHECK(calc.Let("circle20Area", "circleArea"));
		CHECK(calc.GetValue("circleArea") == 1256.63706);

		CHECK(calc.GetValue("radiusSquared") == 400);
		CHECK(calc.GetValue("circle10Area") == 314.159265);
		CHECK(calc.GetValue("circle20Area") == 1256.63706);
		CHECK(calc.GetValue("pi") == 3.14159265);
		CHECK(calc.GetValue("radius") == 20);
	}
}

SCENARIO("Menu")
{
	Calculate calc;

	SECTION("announcement, assignment and withdrawal of variables")
	{
		std::stringstream input, output;
		Menu menu(calc, input, output);

		input << "var x" << std::endl;
		CHECK(menu.HandleCommand());
		THEN("value X is nan")
		{
			input << "print x" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "nan\n");
		}
		
		input << "let x=42" << std::endl;
		CHECK(menu.HandleCommand());
		CHECK(calc.GetValue("x") == 42);

		input << "let x=1.234" << std::endl;
		CHECK(menu.HandleCommand());

		THEN("print var averages the value to 2 signs")
		{
			THEN("value X is 1.23")
			{
				input << "print x" << std::endl;
				CHECK(menu.HandleCommand());
				CHECK(output.str() == "1.23\n");
			}
		}

		input << "let y=x" << std::endl;
		CHECK(menu.HandleCommand());
		input << "let x=99" << std::endl;
		CHECK(menu.HandleCommand());

		WHEN("Automatically declare a variable Y and assign it the current value of X")
		{
			THEN("The variable y stores the value of the x. Subsequent manipulations over X do not affect it.")
			{
				input << "printvars" << std::endl;
				CHECK(menu.HandleCommand());
				CHECK(output.str() == "x:99.00\ny:1.23\n");
			}
		}
	}
	SECTION("Announcement of functions")
	{

		std::stringstream input, output;
		Menu menu(calc, input, output);

		input << "var x" << std::endl;
		CHECK(menu.HandleCommand());
		input << "var y" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn XPlusY=x+y" << std::endl;
		CHECK(menu.HandleCommand());
		WHEN("value of the function is not definite, since the value of the arguments of Nan")
		{
			input << "print XPlusY" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "nan\n");
		}
		input << "let x=3" << std::endl;
		CHECK(menu.HandleCommand());
		input << "let y=4" << std::endl;
		CHECK(menu.HandleCommand());
		THEN("value of the function is determined")
		{
			input << "print XPlusY" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "7.00\n");
		}
		input << "let x=10" << std::endl;
		CHECK(menu.HandleCommand());
		THEN("value of the fn depends on the val of its arg")
		{
			input << "print XPlusY" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "14.00\n");
		}
		input << "let z=3.5" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn XPlusYDivZ=XPlusY/z" << std::endl;
		CHECK(menu.HandleCommand());
		
		THEN("value of the fn can depend on the val of other fn")
		{
			input << "printfns" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "XPlusY:14.00\nXPlusYDivZ:4.00\n");
		}
	}

	SECTION("error input data")
	{

		std::stringstream input, output;
		Menu menu(calc, input, output);

		WHEN("try to set new var with an already established name of var or fn")
		{
			calc.Var("x");
			THEN("an error message")
			{
				input << "var x" << std::endl;
				CHECK(!menu.HandleCommand());
				CHECK(output.str() == "Invalid name of varible!\n");
			}
		}
		WHEN("try to let value with not exist var")
		{
			THEN("an error message")
			{
				input << "let x=y" << std::endl;
				CHECK(!menu.HandleCommand());
				CHECK(output.str() == "Invalid expression!\n");
			}
		}
		WHEN("try to set new fn with exist var or fn")
		{
			THEN("an error message")
			{
				calc.Var("y");
				calc.Var("x");
				input << "fn x=y" << std::endl;
				CHECK(!menu.HandleCommand());
				CHECK(output.str() == "Invalid expression!\n");
			}
		}
	}
	SECTION("Fibonacci")
	{
		std::stringstream input, output;
		Menu menu(calc, input, output);
		input << "let v0=0" << std::endl;
		CHECK(menu.HandleCommand());
		CHECK(calc.GetValue("v0") == 0);
		calc.Let("v0", 0);
		calc.Let("v1", 1);
		calc.Fn("fib0", "v0");
		calc.Fn("fib1", "v1");


		input << "fn fib2=fib1+fib0" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn fib3=fib2+fib1" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn fib4=fib3+fib2" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn fib5=fib4+fib3" << std::endl;
		CHECK(menu.HandleCommand());
		input << "fn fib6=fib5+fib4" << std::endl;
		CHECK(menu.HandleCommand());
		THEN("out fib1-fib6")
		{
			input << "printfns" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "fib0:0.00\nfib1:1.00\nfib2:1.00\nfib3:2.00\nfib4:3.00\nfib5:5.00\nfib6:8.00\n");
		}
				
		calc.Let("v0", 5);
		calc.Let("v1", 8);
		THEN("out fib1-fib6")
		{
			input << "printfns" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "fib0:5.00\nfib1:8.00\nfib2:13.00\nfib3:21.00\nfib4:34.00\nfib5:55.00\nfib6:89.00\n");
		}
		WHEN("fib55")
		{
			clock_t start, end;
			std::cout << "----------------\n";
			start = clock();
			
			for (size_t i = 2; i <= 55; i++)
			{
				calc.Fn("fib" + std::to_string(i), "fib" + std::to_string(i - 1), Operator::Plus, "fib" + std::to_string(i - 2));
			}

			input << "print fib55" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "1548008755920.00\n");
			end = clock();

			printf("The above code block was executed in %.4f second(s)\n", ((double)end - start) / ((double)CLOCKS_PER_SEC));
		}
		WHEN("x1000000")
		{
			calc.Let("x",1);
			calc.Fn("x2", "x", Operator::Plus, "x");
			for (size_t i = 3; i <= 1000000; i++)
			{
				calc.Fn("x" + std::to_string(i), "x" + std::to_string(i - 1), Operator::Plus, "x");
				//std::cout << "x" + std::to_string(i) << "x" + std::to_string(i - 1) << " + " << std::to_string(i - 2) << std::endl;
			}
			
			input << "print x1000000" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "1000000.00\n");
			calc.Let("x", 2);
			input << "print x1000000" << std::endl;
			CHECK(menu.HandleCommand());
			CHECK(output.str() == "1000000.00\n2000000.00\n");
		}
	}
}