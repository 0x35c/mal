#include "types.hpp"
#include <iostream>
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
			while (i < s.length() && s.at(i) != '\n')
				i++;
			continue;
		}

		if (s[i] == '~' && s.at(i + 1) == '@') {
			tokens.push_back("~@");
			i += 2;
			continue;
		}
		if (is_symbol(s[i])) {
			tokens.push_back(String{s[i++]});
			continue;
		}
		if (s[i] == '"') {
			const auto start = i;
			i++;
			while (i < s.length() && s[i] != '"') {
				if (s[i] == '\\')
					i++;
				i++;
			}
			if (i == s.length() && s[i - 1] != '"')
				throw std::invalid_argument(
				    "Missing \" operand");
			tokens.push_back(s.substr(start, i));
			i++;
			continue;
		}

		String word;
		while (i < s.length() && is_non_special(s[i]))
			word += s[i++];
		tokens.push_back(word);
	}
	return tokens;
}
