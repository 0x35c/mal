#include "utils.hpp"

bool contains(const String &s, char c)
{
	return s.find(c) != String::npos;
}

bool is_space(char c)
{
	return contains("\t\n\f\r, ", c);
}

bool is_digit(char c)
{
	return contains("0123456789", c);
}

bool is_symbol(char c)
{
	return contains("[]{}()'`~^@", c);
}

bool is_non_special(char c)
{
	return !is_space(c) && !is_symbol(c) && !contains("\"", c);
}
