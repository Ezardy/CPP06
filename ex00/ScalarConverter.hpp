#ifndef EX00_SCALARCONVERTER_HPP
#define EX00_SCALARCONVERTER_HPP

#include "Error.hpp"

class ScalarConverter {
public:
	static Error convert(char const* str);

private:
	ScalarConverter(void);
};
#endif
