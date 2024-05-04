#include "Environment.hpp"
#include "Reader.hpp"
#include "printer.hpp"
#include "readline.hpp"

static MalType *READ(const String &s)
{
	return read_str(s);
}

static MalType *EVAL(MalType *ast, MalEnv env)
{
	MalList *list = dynamic_cast<MalList *>(ast);
	if (!list)
		return eval_ast(ast, env);
	if (list->empty())
		return ast;
	MalList *new_list = dynamic_cast<MalList *>(eval_ast(ast, env));
	return ast;
}

static const String PRINT(MalType *ast)
{
	return pr_str(ast, true);
}

static void rep(const String &s)
{
	MalEnv env;
	const auto e = EVAL(READ(s), env);
	std::cout << PRINT(e) << std::endl;
	delete e;
}

int main(void)
{
	String s;
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s);
	return 0;
}
