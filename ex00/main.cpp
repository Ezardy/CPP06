#include <iostream>

#include "ScalarConverter.hpp"

int main(int argc, char const* const* const argv) {
	Error error;

	if (argc == 2)
		error = ScalarConverter::convert(argv[1]);
	else {
		error = INV_PAR_COUNT;
		std::cout << "Invalid parameter count\n";
	}
	return error;
}
