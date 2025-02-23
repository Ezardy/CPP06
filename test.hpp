#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <sstream>
#include <string>

#define TEST_START(func_name)                           \
	static bool func_name() {                           \
		bool			   success = true;              \
		const std::string  _func_name = #func_name;     \
		std::streambuf*	   old = std::cout.rdbuf();     \
		std::streambuf*	   oldCerr = std::cerr.rdbuf(); \
		std::ostringstream oss;                         \
		std::ostringstream ess;                         \
		std::string		   expected;                    \
		std::string		   cerrExpected;                \
		std::string		   assertion;                   \
		std::cout << "[START " << _func_name << "]\n";  \
		std::cout.rdbuf(oss.rdbuf());                   \
		std::cerr.rdbuf(ess.rdbuf());
#define TEST_LOGIC_START try {
#define TEST_LOGIC_END                                                                         \
	std::cout.rdbuf(old);                                                                      \
	std::cerr.rdbuf(oldCerr);                                                                  \
	if (!(success = success && expected == oss.str() && cerrExpected == ess.str())) {          \
		std::cout << "CATCHED STDOUT:\n" << oss.str() << "CATCHED STDERR:\n" << ess.str();     \
		std::cout << "EXPECTED STDOUT:\n" << expected << "EXPECTED STDERR:\n" << cerrExpected; \
	}                                                                                          \
	}
#define TEST_EMERGENCY_START           \
	catch (const std::exception& e) {  \
		std::cout.rdbuf(old);          \
		std::cerr.rdbuf(oldCerr);      \
		std::cerr << e.what() << '\n'; \
		success = false;
#define TEST_EMERGENCY_END }
#define TEST_END                                        \
	if (!success)                                       \
		std::cout << '(' << _func_name << " failed)\n"; \
	return success;                                     \
	}

#define TEST_STRINGIFY(X) #X
#define TEST_EXPAND_AND_STRINGIFY(X) TEST_STRINGIFY(X)
#define TEST_ASSERT(cond) \
	if (!(cond))          \
		throw std::logic_error(#cond ":" TEST_EXPAND_AND_STRINGIFY(__LINE__));

#define TEST_STDOUT(X)                                                                     \
	if (X == oss.str())                                                                    \
		oss.str("");                                                                       \
	else                                                                                   \
		throw std::logic_error("CATCHED STDOUT:" TEST_EXPAND_AND_STRINGIFY(__LINE__) ":\n" \
							   + oss.str() + "EXPECTED STDOUT:\n" + X);

#define TEST_STDERR(X)                                                                     \
	if (X == ess.str())                                                                    \
		ess.str("");                                                                       \
	else                                                                                   \
		throw std::logic_error("CATCHED STDERR:" TEST_EXPAND_AND_STRINGIFY(__LINE__) ":\n" \
							   + ess.str() + "EXPECTED STDERR:\n" + X);

#define TEST_EXCEPTION(X, E)                                                                 \
	bool caught = false;                                                                     \
	try {                                                                                    \
		X;                                                                                   \
	} catch (const E& e) {                                                                   \
		caught = true;                                                                       \
	} catch (const std::exception& e) {                                                      \
		throw std::bad_exception(                                                            \
			std::string("Wrong exception catched:" TEST_EXPAND_AND_STRINGIFY(__LINE__) ": ") \
			+ e.what());                                                                     \
	}                                                                                        \
	if (!caught)                                                                             \
		throw std::bad_exception("No exception was catched");

#define CURRENT_STDOUT oss.str()

#define CURRENT_STDERR ess.str()

#define CLEAN_STDOUT oss.str("");

#endif
