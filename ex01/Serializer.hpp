#ifndef EX01_SERIALIZER_HPP
#define EX01_SERIALIZER_HPP

#include <stdint.h>

#include "Data.hpp"

class Serializer {
public:
	static uintptr_t serialize(Data* ptr);
	static Data*	 deserialize(uintptr_t raw);

private:
	Serializer(void);
	Serializer(Serializer const& other);
	~Serializer(void);

	Serializer& operator=(Serializer const& other);
};
#endif
