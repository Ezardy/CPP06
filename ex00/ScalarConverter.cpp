#include "ScalarConverter.hpp"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

#include "Expression.hpp"

static void recognize_expression(char const* str, Expression& exp, double& v, Error& err);
static void print_char(Expression type, double v, Error err);
static void print_int(Expression type, double v, Error err);
static void print_float(Expression type, double v, Error err);
static void print_double(Expression type, double v, Error err);
static void char_message(double v);
static void float_message(double v);
static void double_message(double v);
static void impossible_message(void);
static void underflow_message(void);
static bool nonfinite(double d);

ScalarConverter::ScalarConverter(void) {
}

ScalarConverter::ScalarConverter(ScalarConverter const& other) {
	(void)other;
}

ScalarConverter::~ScalarConverter(void) {
}

ScalarConverter& ScalarConverter::operator=(ScalarConverter const& other) {
	(void)other;
	return *this;
}

Error ScalarConverter::convert(char const* str) {
	double	   v;
	Expression exp;
	Error	   err = NO_ERROR;

	recognize_expression(str, exp, v, err);
	print_char(exp, v, err);
	print_int(exp, v, err);
	print_float(exp, v, err);
	print_double(exp, v, err);

	return err;
}

static void recognize_expression(char const* str, Expression& exp, double& v, Error& err) {
	char const* sub;

	if (str == NULL || *str == 0 || std::isspace(*str)
		|| ((sub = strcasestr(str, "nan"))
			&& (!std::strstr(sub, "nan") || (sub[3] && (sub[3] != 'f' || sub[4]))))
		|| ((sub = strcasestr(str, "inf"))
			&& (!std::strstr(sub, "inf") || (sub[3] && (sub[3] != 'f' || sub[4]))))
		|| (!std::strpbrk(str, "'n.eE") && std::strpbrk(str, "fF"))) {
		exp = EXPR_TYPE_NONE;
		err = INVALID_EXPRESSION;
	} else {
		char* end;

		if (std::strlen(str) == 3 && *str == '\'' && str[2] == '\'') {
			exp = CHAR;
			v = str[1];
		} else {
			errno = 0;
			long l = std::strtol(str, &end, 10);
			if (*end == 0 || ((*end == 'u' || *end == 'U') && end[1] == 0)) {
				exp = INT;
				if (errno == ERANGE || l < std::numeric_limits<int>::min()
					|| l > std::numeric_limits<int>::max())
					err = ERR_OVERFLOW;
				v = l;
			} else {
				errno = 0;
				float f = std::strtof(str, &end);
				v = f;
				if ((*end == 'f' || *end == 'F') && end[1] == 0) {
					exp = FLOAT;
					if (errno == ERANGE) {
						if ((f > 0.0f && f == HUGE_VALF) || (f < 0.0f && f == -HUGE_VALF))
							err = ERR_OVERFLOW;
						else
							err = ERR_UNDERFLOW;
					}
				} else {
					errno = 0;
					v = std::strtod(str, &end);
					if (*end == 0) {
						exp = DOUBLE;
						if (errno == ERANGE) {
							if ((v > 0.0 && v == HUGE_VAL) || (v < 0.0 && v == -HUGE_VAL))
								err = ERR_OVERFLOW;
							else
								err = ERR_UNDERFLOW;
						}
					} else {
						exp = EXPR_TYPE_NONE;
						err = INVALID_EXPRESSION;
					}
				}
			}
		}
	}
}

static void print_char(Expression type, double v, Error err) {
	std::cout << "char: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
			case INT:
				char_message(v);
				break;
			case FLOAT:
			case DOUBLE:
				if (nonfinite(v))
					impossible_message();
				else
					char_message(v);
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void print_int(Expression type, double v, Error err) {
	std::cout << "int: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
			case INT:
				std::cout << static_cast<int>(v);
				break;
			case FLOAT:
			case DOUBLE:
				if (nonfinite(v) || v < std::numeric_limits<int>::min()
					|| v > std::numeric_limits<int>::max())
					impossible_message();
				else
					std::cout << static_cast<int>(v);
				break;
			default:
				impossible_message();
				break;
		}
	}
	std::cout << '\n';
}

static void print_float(Expression type, double v, Error err) {
	std::cout << "float: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
			case INT:
			case DOUBLE:
				float_message(v);
				break;
			case FLOAT:
				float_message(v);
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

static void print_double(Expression type, double v, Error err) {
	std::cout << "double: ";
	if (err == ERR_OVERFLOW)
		impossible_message();
	else {
		switch (type) {
			case CHAR:
			case INT:
			case FLOAT:
				double_message(v);
				break;
			case DOUBLE:
				double_message(v);
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

static void char_message(double v) {
	if (std::numeric_limits<char>::min() > v || std::numeric_limits<char>::max() < v)
		impossible_message();
	else if (std::isprint(v))
		std::cout << '\'' << static_cast<char>(v) << '\'';
	else
		std::cout << "Non displayable";
}

static void float_message(double v) {
	if (!nonfinite(v)
		&& (v < -std::numeric_limits<float>::max() || v > std::numeric_limits<float>::max()))
		impossible_message();
	else
		std::cout << std::fixed << static_cast<float>(v) << 'f';
}

static void double_message(double v) {
	std::cout << std::fixed << v;
}

static void underflow_message(void) {
	std::cout << " (underflow)";
}

static bool nonfinite(double d) {
	return d == std::numeric_limits<double>::infinity()
		   || d == -std::numeric_limits<double>::infinity() || d != d;
}
