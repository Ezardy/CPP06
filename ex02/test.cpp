#include "../test.hpp"

#include <cmath>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void) throw(std::bad_alloc);
void  identify(Base* p) throw();
void  identify(Base& p) throw();

static bool pointer(void);
static bool reference(void);
static bool generate_test(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {pointer, reference, generate_test};
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
TEST_START(generate_test)
	TEST_LOGIC_START
		int const	test_count = 100;
		float const	tolerance = 5.0f;

		int	a_count = 0;
		int	b_count = 0;
		int	c_count = 0;
		int	other_count = 0;

		for (int i = 0; i < test_count; i += 1) {
			Base*	b = generate();

			identify(b);
			if (CURRENT_STDOUT == "A\n")
				a_count += 1;
			else if (CURRENT_STDOUT == "B\n")
				b_count += 1;
			else if (CURRENT_STDOUT == "C\n")
				c_count += 1;
			else
				other_count += 1;
			delete b;
			CLEAN_STDOUT
		}

		TEST_ASSERT(other_count == 0)
		TEST_ASSERT(std::abs((float)a_count / test_count * 100 - 30) <= tolerance)
		TEST_ASSERT(std::abs((float)b_count / test_count * 100 - 30) <= tolerance)
		TEST_ASSERT(std::abs((float)c_count / test_count * 100 - 30) <= tolerance)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(reference)
	TEST_LOGIC_START
		Base	bs;
		A		a;
		B		b;
		C		c;

		Base&	bsr = bs;
		Base&	ar = a;
		Base&	br = b;
		Base&	cr = c;

		identify(bsr);
		TEST_STDOUT("other\n")
		identify(ar);
		TEST_STDOUT("A\n")
		identify(br);
		TEST_STDOUT("B\n")
		identify(cr);
		TEST_STDOUT("C\n")
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(pointer)
	TEST_LOGIC_START
		Base	bs;
		A		a;
		B		b;
		C		c;

		Base*	bsp = &bs;
		Base*	ap = &a;
		Base*	bp = &b;
		Base*	cp = &c;

		identify(bsp);
		TEST_STDOUT("other\n")
		identify(ap);
		TEST_STDOUT("A\n")
		identify(bp);
		TEST_STDOUT("B\n")
		identify(cp);
		TEST_STDOUT("C\n")
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on
