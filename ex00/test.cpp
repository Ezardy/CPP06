#include "../test.hpp"

#include <iostream>

#include "ScalarConverter.hpp"

static std::string& expectation(char const* c, char const* i, char const* f, char const* d);

static char const* const impossible = "impossible";
static char const* const nondisplayable = "Non displayable";
static char const* const nanf = "-nanf";
static char const* const inff = "-inff";
static char const* const nan = "-nan";
static char const* const inf = "-inf";

static bool char_displayables(void);
static bool int_normal(void);
static bool int_overflow(void);
static bool float_normal(void);
static bool float_overflow(void);
static bool float_underflow(void);
static bool double_normal(void);
static bool double_overflow(void);
static bool double_underflow(void);
static bool invalids(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {char_displayables, int_normal,	   int_overflow,  float_normal,
							   float_overflow,	  float_underflow, double_normal, double_overflow,
							   double_underflow,  invalids};
	size_t tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

// clang-format off

TEST_START(invalids)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("''") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'ab'") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("a'") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("\"a\"") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'-4'") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 'a'") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a' 'a'") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a' ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a'f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a'F") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a'u") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("'a'U") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("a") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("au") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("aU") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("af") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("aF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))

		TEST_ASSERT(ScalarConverter::convert("4 4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4 ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("- 4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+ 4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" +4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" -4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" +4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("u4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("U4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("++4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("--4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+-4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-+4") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))

		TEST_ASSERT(ScalarConverter::convert("4f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4F") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+4f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(".f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-.f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0ff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0FF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0fF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0Ff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0f ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0ff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0FF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0fF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0Ff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" -4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0f ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" -4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("--4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-+4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+-4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("++4.0f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(".e-20f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-.e-20f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+.e-20f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("3.4e-f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("3.4e+f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-3.4e-f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-3.4e+f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("e+5f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-e+5f") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("nanff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("nanfF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("nanF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("NANFF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("NANf") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("NANF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("infff") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("infF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("INFF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))

		TEST_ASSERT(ScalarConverter::convert(".") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-.") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("4.0 ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" 4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(" -4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4.0 ") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("--4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-+4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+-4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("++4.0") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert(".e-20") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-.e-20") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("+.e-20") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("3.4e-") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("3.4e+") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-3.4e-") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-3.4e+") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("e+5") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-e+5") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("NAN") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-NAN") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("NAN1") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("1NAN") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("INF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-INF") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("infinity") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("INFINITY") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))

		TEST_ASSERT(ScalarConverter::convert("\"afg\"") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("afg") == INVALID_EXPRESSION)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(double_underflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("2.21e-308") == ERR_UNDERFLOW)
		TEST_STDOUT(expectation(nondisplayable, "0", "0.000000f", "0.000000 (underflow)"))
		TEST_ASSERT(ScalarConverter::convert("-2.21e-308") == ERR_UNDERFLOW)
		TEST_STDOUT(expectation(nondisplayable, "0", "-0.000000f", "-0.000000 (underflow)"))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(double_overflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("1.8e+308") == ERR_OVERFLOW)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-1.8e+308") == ERR_OVERFLOW)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(double_normal)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("97.") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("97.0") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert(".05") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "0", "0.050000f", "0.050000"))
		TEST_ASSERT(ScalarConverter::convert("9.7e1") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7e1") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7E1") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7E1") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))

		TEST_ASSERT(ScalarConverter::convert("+97.95") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.949997f", "97.950000"))
		TEST_ASSERT(ScalarConverter::convert("+97.95") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.949997f", "97.950000"))

		TEST_ASSERT(ScalarConverter::convert("-97.95") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "-97", "-97.949997f", "-97.950000"))
		TEST_ASSERT(ScalarConverter::convert("-97.95") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "-97", "-97.949997f", "-97.950000"))

		TEST_ASSERT(ScalarConverter::convert("350.") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "350", "350.000000f", "350.000000"))
		TEST_ASSERT(ScalarConverter::convert("350.") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "350", "350.000000f", "350.000000"))

		TEST_ASSERT(ScalarConverter::convert("2147483648.") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, "2147483648.000000f", "2147483648.000000"))
		TEST_ASSERT(ScalarConverter::convert("2147483648.") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, "2147483648.000000f", "2147483648.000000"))

		TEST_ASSERT(ScalarConverter::convert("1.1E-38") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "0", "0.000000f", "0.000000"))
		TEST_ASSERT(ScalarConverter::convert("-1.1E-38") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "0", "-0.000000f", "-0.000000"))

		TEST_ASSERT(ScalarConverter::convert("1e56") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, impossible, "100000000000000009190283508143378238084034459715684532224.000000"))
		TEST_ASSERT(ScalarConverter::convert("-1e56") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, impossible, "-100000000000000009190283508143378238084034459715684532224.000000"))

		TEST_ASSERT(ScalarConverter::convert("nan") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf + 1, nan + 1))
		TEST_ASSERT(ScalarConverter::convert("+nan") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf + 1, nan + 1))
		TEST_ASSERT(ScalarConverter::convert("-nan") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf, nan))

		TEST_ASSERT(ScalarConverter::convert("inf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff + 1, inf + 1))
		TEST_ASSERT(ScalarConverter::convert("+inf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff + 1, inf + 1))
		TEST_ASSERT(ScalarConverter::convert("-inf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff, inf))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(float_underflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("1.1E-38f") == ERR_UNDERFLOW)
		TEST_STDOUT(expectation(nondisplayable, "0", "0.000000f (underflow)", "0.000000"))
		TEST_ASSERT(ScalarConverter::convert("-1.1E-38f") == ERR_UNDERFLOW)
		TEST_STDOUT(expectation(nondisplayable, "0", "-0.000000f (underflow)", "-0.000000"))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(float_overflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("4e38f") == ERR_OVERFLOW)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_ASSERT(ScalarConverter::convert("-4e38f") == ERR_OVERFLOW)
		TEST_STDOUT(expectation(impossible, impossible, impossible, impossible))
		TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(float_normal)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("97.f") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("97.0f") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert(".05f") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "0", "0.050000f", "0.050000"))
		TEST_ASSERT(ScalarConverter::convert("9.7e1f") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7e1F") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7E1F") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
		TEST_ASSERT(ScalarConverter::convert("9.7E1f") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.000000f", "97.000000"))
	
		TEST_ASSERT(ScalarConverter::convert("+97.95F") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.949997f", "97.949997"))
		TEST_ASSERT(ScalarConverter::convert("+97.95f") == NO_ERROR)
		TEST_STDOUT(expectation("'a'", "97", "97.949997f", "97.949997"))

		TEST_ASSERT(ScalarConverter::convert("-97.95F") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "-97", "-97.949997f", "-97.949997"))
		TEST_ASSERT(ScalarConverter::convert("-97.95f") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "-97", "-97.949997f", "-97.949997"))

		TEST_ASSERT(ScalarConverter::convert("350.F") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "350", "350.000000f", "350.000000"))
		TEST_ASSERT(ScalarConverter::convert("350.f") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "350", "350.000000f", "350.000000"))

		TEST_ASSERT(ScalarConverter::convert("2147483648.F") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, "2147483648.000000f", "2147483648.000000"))
		TEST_ASSERT(ScalarConverter::convert("2147483648.f") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, "2147483648.000000f", "2147483648.000000"))

		TEST_ASSERT(ScalarConverter::convert("nanf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf + 1, nan + 1))
		TEST_ASSERT(ScalarConverter::convert("+nanf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf + 1, nan + 1))
		TEST_ASSERT(ScalarConverter::convert("-nanf") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, nanf, nan))

		TEST_ASSERT(ScalarConverter::convert("inff") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff + 1, inf + 1))
		TEST_ASSERT(ScalarConverter::convert("+inff") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff + 1, inf + 1))
		TEST_ASSERT(ScalarConverter::convert("-inff") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, impossible, inff, inf))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(int_overflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("-2147483649") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("-2147483649u") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("-2147483649U") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);

		TEST_ASSERT(ScalarConverter::convert("2147483648") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("2147483648u") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("2147483648U") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);

		TEST_ASSERT(ScalarConverter::convert("214748364700040060406") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("214748364700040060406u") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("214748364700040060406U") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(int_normal)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("-2147483648") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "-2147483648", "-2147483648.000000f", "-2147483648.000000"))

		TEST_ASSERT(ScalarConverter::convert("-128") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "-128", "-128.000000f", "-128.000000"))

		TEST_ASSERT(ScalarConverter::convert("31") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "31", "31.000000f", "31.000000"))

		TEST_ASSERT(ScalarConverter::convert("127") == NO_ERROR)
		TEST_STDOUT(expectation(nondisplayable, "127", "127.000000f", "127.000000"))

		TEST_ASSERT(ScalarConverter::convert("2147483647") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "2147483647", "2147483648.000000f", "2147483647.000000"))

		TEST_ASSERT(ScalarConverter::convert("-129") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "-129", "-129.000000f", "-129.000000"))

		TEST_ASSERT(ScalarConverter::convert("128") == NO_ERROR)
		TEST_STDOUT(expectation(impossible, "128", "128.000000f", "128.000000"))
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(char_displayables)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("'4'") == NO_ERROR)
		expected += expectation("'4'", "52", "52.000000f", "52.000000");
		TEST_ASSERT(ScalarConverter::convert("' '") == NO_ERROR)
		expected += expectation("' '", "32", "32.000000f", "32.000000");
		TEST_ASSERT(ScalarConverter::convert("'~'") == NO_ERROR)
		expected += expectation("'~'", "126", "126.000000f", "126.000000");
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

// clang-format on

static std::string& expectation(char const* c, char const* i, char const* f, char const* d) {
	static std::string exp;

	exp.reserve(100);
	exp = "char: ";
	exp += c;
	exp += "\nint: ";
	exp += i;
	exp += "\nfloat: ";
	exp += f;
	exp += "\ndouble: ";
	exp += d;
	exp += '\n';
	return exp;
}
