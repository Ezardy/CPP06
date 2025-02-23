#include <cstdlib>
#include <iostream>
#include <new>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void) throw(std::bad_alloc) {
	Base* n = NULL;
	switch (rand() % 3) {
		case 0:
			n = new A();
			break;
		case 1:
			n = new B();
			break;
		case 2:
			n = new C();
			break;
	}
	return n;
}

void identify(Base* p) throw() {
	if (dynamic_cast<A*>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "C\n";
	else
		std::cout << "other\n";
}

void identify(Base& p) throw() {
	try {
		A const& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A\n";
	} catch (std::exception const& h) {
		try {
			B const& b = dynamic_cast<B&>(p);
			(void)b;
			std::cout << "B\n";
		} catch (std::exception const& l) {
			try {
				C const& c = dynamic_cast<C&>(p);
				(void)c;
				std::cout << "C\n";
			} catch (std::exception const& ll) {
				std::cout << "other\n";
			}
		}
	}
}
