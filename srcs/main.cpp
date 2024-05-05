#include "MalEnv.hpp"
#include "Reader.hpp"
#include "printer.hpp"
#include "readline.hpp"

static MalType *READ(const String &s)
{
	return read_str(s);
}

MalType *EVAL(MalType *ast, MalEnv env)
{
	MalList *list = dynamic_cast<MalList *>(ast);
	if (!list)
		return eval_ast(ast, env);
	if (list->empty())
		return ast;
	MalList *new_list = dynamic_cast<MalList *>(eval_ast(ast, env));
	if (!new_list)
		return NULL;
	MalFunc *func = dynamic_cast<MalFunc *>(new_list->list[0]);
	if (func)
		return func->apply(new_list->list[1], new_list->list[2]);
	return NULL;
}

static const String PRINT(MalType *ast)
{
	return pr_str(ast, true);
}

static void rep(const String &s)
{
	MalEnv env;
	const auto e = EVAL(READ(s), env);
	if (e)
		std::cout << PRINT(e) << std::endl;
	else
		std::cerr << "error during execution" << std::endl;
	delete e;
}

int main(void)
{
	String s;
	while (Readline(String{std::getenv("USER")} + "> ", s))
		rep(s);
	return 0;
}
