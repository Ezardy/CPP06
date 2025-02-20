#include "ScalarConverter.hpp"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

#include "Expression.hpp"
#include "Value.hpp"

static void recognize_expression(char const* str, Expression& exp, Value& v, Error& err);
static void print_char(Expression type, Value v, Error err);
static void print_int(Expression type, Value v, Error err);
static void print_float(Expression type, Value v, Error err);
static void print_double(Expression type, Value v, Error err);
static void char_message(int v);
static void float_message(float v);
static void double_message(double v);
static void impossible_message(void);
static void underflow_message(void);
static bool nonfinitef(float f);
static bool nonfinite(double d);

ScalarConverter::ScalarConverter(void) {
}

Error ScalarConverter::convert(char const* str) {
	Value	   v;
	Expression exp;
	Error	   err = NO_ERROR;

	recognize_expression(str, exp, v, err);
	print_char(exp, v, err);
	print_int(exp, v, err);
	print_float(exp, v, err);
	print_double(exp, v, err);

	return err;
}

static void recognize_expression(char const* str, Expression& exp, Value& v, Error& err) {
	char const* sub;

	if (str == NULL || *str == 0 || (std::isspace(*str) && str[1] != 0)
		|| ((sub = std::strstr(str, "nan")) && sub[3] != 0 && (sub[3] != 'f' || sub[4]))
		|| ((sub = std::strstr(str, "NAN")) && sub[3] != 0 && (sub[3] != 'F' || sub[4]))) {
		exp = EXPR_TYPE_NONE;
	} else {
		char*		 end;
		size_t const len = std::strlen(str);

		if (len == 1 && !std::isdigit(*str)) {
			exp = CHAR;
			v.c = *str;
		} else {
			long l = std::strtol(str, &end, 10);
			if (*end == 0) {
				exp = INT;
				if (errno == ERANGE || l < std::numeric_limits<int>::min()
					|| l > std::numeric_limits<int>::max())
					err = ERR_OVERFLOW;
				v.i = static_cast<int>(l);
			} else {
				v.f = std::strtof(str, &end);
				if ((*end == 'f' || *end == 'F') && end[1] == 0) {
					exp = FLOAT;
					if (errno == ERANGE) {
						if ((v.f > 0.0f && v.f == HUGE_VALF) || (v.f < 0.0f && v.f == -HUGE_VALF))
							err = ERR_OVERFLOW;
						else
							err = ERR_UNDERFLOW;
					}
				} else {
					v.d = std::strtod(str, &end);
					if (*end == 0) {
						exp = DOUBLE;
						if (errno == ERANGE) {
							if ((v.d > 0.0 && v.d == HUGE_VAL) || (v.d < 0.0 && v.d == HUGE_VAL))
								err = ERR_OVERFLOW;
							else
								err = ERR_UNDERFLOW;
						}
					} else
						exp = EXPR_TYPE_NONE;
				}
			}
		}
	}
}

static void print_char(Expression type, Value v, Error err) {
	std::cout << "char: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
				char_message(v.c);
				break;
			case INT:
				char_message(v.i);
				break;
			case FLOAT:
				if (nonfinitef(v.f))
					impossible_message();
				else
					char_message(static_cast<int>(v.f));
				break;
			case DOUBLE:
				if (nonfinite(v.d))
					impossible_message();
				else
					char_message(static_cast<int>(v.d));
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void print_int(Expression type, Value v, Error err) {
	std::cout << "int: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
				std::cout << static_cast<int>(v.c);
				break;
			case INT:
				std::cout << v.i;
				break;
			case FLOAT:
				if (nonfinitef(v.f))
					impossible_message();
				else
					std::cout << static_cast<int>(v.f);
				break;
			case DOUBLE:
				if (nonfinite(v.d))
					impossible_message();
				else
					std::cout << static_cast<int>(v.d);
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void print_float(Expression type, Value v, Error err) {
	std::cout << "float: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
				float_message(v.c);
				break;
			case INT:
				float_message(v.i);
				break;
			case FLOAT:
				float_message(v.f);
				if (err == ERR_UNDERFLOW)
					underflow_message();
				break;
			case DOUBLE:
				float_message(static_cast<float>(v.d));
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void print_double(Expression type, Value v, Error err) {
	std::cout << "double: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
				double_message(v.c);
				break;
			case INT:
				double_message(v.i);
				break;
			case FLOAT:
				double_message(v.f);
				break;
			case DOUBLE:
				double_message(v.d);
				if (err == ERR_UNDERFLOW)
					underflow_message();
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void impossible_message(void) {
	std::cout << "impossible";
}

static void char_message(int v) {
	if (std::numeric_limits<char>::min() > v || std::numeric_limits<char>::max() < v)
		impossible_message();
	else if (std::isprint(v))
		std::cout << '\'' << static_cast<char>(v) << '\'';
	else
		std::cout << "Non displayable";
}

static void float_message(float v) {
	std::cout << std::fixed << v << 'f';
}

static void double_message(double v) {
	std::cout << std::fixed << v;
}

static void underflow_message(void) {
	std::cout << " (underflow)";
}

static bool nonfinitef(float f) {
	return f == std::numeric_limits<float>::infinity()
		   || f == -std::numeric_limits<float>::infinity() || f != f;
}

static bool nonfinite(double d) {
	return d == std::numeric_limits<double>::infinity()
		   || d == -std::numeric_limits<double>::infinity() || d != d;
}
