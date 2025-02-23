#ifndef EX00_SCALARCONVERTER_HPP
#define EX00_SCALARCONVERTER_HPP

#include "Error.hpp"

class ScalarConverter {
public:
	static Error convert(char const* str) throw();

private:
	ScalarConverter(void) throw();
	ScalarConverter(ScalarConverter const& other) throw();
	~ScalarConverter(void) throw();

	ScalarConverter& operator=(ScalarConverter const& other) throw();
};
#endif
