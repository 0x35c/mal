#include "../includes/readline.hpp"
#include <iostream>

const String &READ(const String &input);
const String &EVAL(const String &ast);
const String &PRINT(const String &ast);
const String &rep(const String &ast);

const String &READ(const String &input)
{
	return (input);
}

const String &EVAL(const String &ast)
{
	return (ast);
}

const String &PRINT(const String &ast)
{
	return (ast);
}

const String &rep(const String &ast)
{
	return READ(EVAL(PRINT(ast)));
}

int main_loop(void)
{
	String input;
	String user = std::getenv("USER");
	String prompt = user + "> ";
	while (Readline(prompt, input)) {
		std::cout << rep(input) << std::endl;
	}
	return (0);
}
