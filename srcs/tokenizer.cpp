#include "utils.hpp"
#include <stdexcept>

std::vector<String> tokenize(const String &s)
{
	std::vector<String> tokens;

	// We don't need comments lines
	if (s[0] == ';')
		return {};
	std::size_t i = 0;
	while (i < s.length()) {
		if (is_space(s[i])) {
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
				    "missing '\"' operand");
			tokens.push_back(s.substr(start, i - start + 1));
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
