#include "../test.hpp"

#include "Serializer.hpp"

static bool test(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {test};
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
TEST_START(test)
	TEST_LOGIC_START
		double const	d_v = 42.42e+42;
		float const		f_v = 21.21e+21;
		int const		i_v = 42;
		char const		c_v = '*';

		Data		d = {d_v, f_v, i_v, c_v};
		uintptr_t	raw = Serializer::serialize(&d);
		Data*		dptr = Serializer::deserialize(raw);

		TEST_ASSERT(dptr == &d)
		TEST_ASSERT(dptr->d == d_v)
		TEST_ASSERT(dptr->f == f_v)
		TEST_ASSERT(dptr->i == i_v)
		TEST_ASSERT(dptr->c == c_v)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on
