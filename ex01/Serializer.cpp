#include "Serializer.hpp"

Serializer::Serializer(void) throw() {
}

Serializer::Serializer(Serializer const& other) throw() {
	(void)other;
}

Serializer::~Serializer(void) throw() {
}

Serializer& Serializer::operator=(Serializer const& other) throw() {
	(void)other;
	return *this;
}

uintptr_t Serializer::serialize(Data* ptr) throw() {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) throw() {
	return reinterpret_cast<Data*>(raw);
}
