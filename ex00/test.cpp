#include "../test.hpp"

#include <iostream>

#include "ScalarConverter.hpp"

static std::string& expectation(char const* c, char const* i, char const* f, char const* d);

static char const* const impossible = "impossible";
static char const* const nondisplayable = "Non displayable";
/*
static char const* const nan = "-nan";
static char const* const nanf = "-nanf";
static char const* const inf = "-inf";
static char const* const inff = "-inff";
*/

static bool char_displayables(void);
static bool int_normal(void);
static bool int_overflow(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {char_displayables, int_normal, int_overflow};
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

TEST_START(int_overflow)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("-2147483649") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("2147483648") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
		TEST_ASSERT(ScalarConverter::convert("214748364700040060406") == ERR_OVERFLOW)
		expected += expectation(impossible, impossible, impossible, impossible);
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(int_normal)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert("-2147483648") == NO_ERROR)
		expected += expectation(impossible, "-2147483648", "-2147483648.000000f", "-2147483648.000000");
		TEST_ASSERT(ScalarConverter::convert("-128") == NO_ERROR)
		expected += expectation(nondisplayable, "-128", "-128.000000f", "-128.000000");
		TEST_ASSERT(ScalarConverter::convert("31") == NO_ERROR)
		expected += expectation(nondisplayable, "31", "31.000000f", "31.000000");
		TEST_ASSERT(ScalarConverter::convert("127") == NO_ERROR)
		expected += expectation(nondisplayable, "127", "127.000000f", "127.000000");
		TEST_ASSERT(ScalarConverter::convert("2147483647") == NO_ERROR)
		expected += expectation(impossible, "2147483647", "2147483648.000000f", "2147483647.000000");
		TEST_ASSERT(ScalarConverter::convert("-129") == NO_ERROR)
		expected += expectation(impossible, "-129", "-129.000000f", "-129.000000");
		TEST_ASSERT(ScalarConverter::convert("128") == NO_ERROR)
		expected += expectation(impossible, "128", "128.000000f", "128.000000");
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(char_displayables)
	TEST_LOGIC_START
		TEST_ASSERT(ScalarConverter::convert(" ") == NO_ERROR)
		expected += expectation("' '", "32", "32.000000f", "32.000000");
		TEST_ASSERT(ScalarConverter::convert("~") == NO_ERROR)
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
