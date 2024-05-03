#include "Reader.hpp"

static std::vector<String> tokenize(const String &s);
static MalType *read_form(Reader &reader);
static MalType *read_list(Reader &reader);
static MalType *read_atom(Reader &reader);

static bool contains(const String &s, char c);
static bool is_space(char c);
static bool is_digit(char c);

MalType *read_str(const String &s)
{
	std::vector<String> tokens = tokenize(s);
	for (auto e : tokens)
		std::cout << e << std::endl;
	Reader reader(tokens);
	return (read_form(reader));
}

static bool contains(const String &s, char c)
{
	return s.find(c) != String::npos;
}

static bool is_space(char c)
{
	return contains("\t\n\f\r, ", c);
}

static bool is_digit(char c)
{
	return contains("0123456789", c);
}

static bool is_symbol(char c)
{
	return contains("[]{}()'`~^@", c);
}

static bool is_non_special(char c)
{
	return !is_space(c) && !is_symbol(c) && !contains("\"", c);
}

static std::vector<String> tokenize(const String &s)
{
	std::vector<String> tokens;
	std::size_t i = 0;
	while (i < s.length()) {
		if (is_space(s[i])) {
			i++;
			continue;
		}
		// Comments are ignored, might change later
		if (s[i] == ';') {
			while (s[i] != '\n')
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
			i++;
			while (s.at(i) != '"') {
				if (s[i] == '\\') {
					i++;
					continue;
				}
				tok += s[i];
				i++;
			}
		} else {
			while (i < s.length() && is_non_special(s.at(i))) {
				tok += s[i];
				i++;
			}
			i--;
		}
		tokens.push_back(tok);
		i++;
	}
	return tokens;
}

static MalType *read_form(Reader &reader)
{
	if (reader.peek()[0] == '(')
		return read_list(reader);
	return read_atom(reader);
}

static MalType *read_list(Reader &reader)
{
	auto list = new MalList{};
	reader.next();
	while (reader.peek()[0] != ')') {
		list->add(read_form(reader));
	}
	reader.next();
	return list;
}

static MalType *read_atom(Reader &reader)
{
	const String tok = reader.peek();
	reader.next();
	if (is_digit(tok[0]))
		return new MalNumber(std::atoi(tok.c_str()));
	else
		return new MalSymbol(tok);
}
