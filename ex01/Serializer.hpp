#ifndef EX01_SERIALIZER_HPP
#define EX01_SERIALIZER_HPP

#include <stdint.h>

#include "Data.hpp"

class Serializer {
public:
	static uintptr_t serialize(Data* ptr) throw();
	static Data*	 deserialize(uintptr_t raw) throw();

private:
	Serializer(void) throw();
	Serializer(Serializer const& other) throw();
	~Serializer(void) throw();

	Serializer& operator=(Serializer const& other) throw();
};
#endif
