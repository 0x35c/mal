#include "types.hpp"
#include <stdexcept>

static bool contains(const String &s, char c);
static bool is_space(char c);
static bool is_symbol(char c);
static bool is_non_special(char c);

static bool contains(const String &s, char c)
{
	return s.find(c) != String::npos;
}

static bool is_space(char c)
{
	return contains("\t\n\f\r, ", c);
}

static bool is_symbol(char c)
{
	return contains("[]{}()'`~^@", c);
}

static bool is_non_special(char c)
{
	return !is_space(c) && !is_symbol(c) && !contains("\"", c);
}

// I really don't like this function, might change it later
std::vector<String> tokenize(const String &s)
{
	std::vector<String> tokens;
	std::size_t i = 0;
	while (i < s.length()) {
		if (is_space(s[i])) {
			i++;
			continue;
		}
		// We don't need comments ig??
		if (s[i] == ';') {
			while (s.at(i) != '\n')
				i++;
			continue;
		}

		String tok;

		if (s[i] == '~' && s.at(i + 1) == '@') {
			tok = "~@";
			i++;
		} else if (is_symbol(s[i])) {
			tok += s[i];
		} else if (s[i] == '"') {
			tok += s[i++];
			while (i < s.length() && s[i] != '"') {
				if (s[i] == '\\') {
					i++;
					tok += s.at(i++);
					continue;
				}
				tok += s[i];
				i++;
			}
			if (i == s.length() && s[i - 1] != '"')
				throw std::invalid_argument(
				    "Missing \" operand");
			tok += s[i];
		} else {
			while (i < s.length() && is_non_special(s[i]))
				tok += s[i++];
			i--;
		}
		tokens.push_back(tok);
		i++;
	}
	return tokens;
}
