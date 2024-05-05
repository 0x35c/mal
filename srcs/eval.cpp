#include "MalEnv.hpp"
#include <iostream>

MalType *eval_ast(MalType *ast, MalEnv env)
{
	MalSymbol *symbol = dynamic_cast<MalSymbol *>(ast);
	if (symbol)
		return env.find(symbol->str(true));
	MalList *list = dynamic_cast<MalList *>(ast);
	if (!list)
		return ast;
	/* for (auto e : list->list) { */
	/* 	std::cout << e->str(true) << std::endl; */
	/* 	e = EVAL(e, env); */
	/* 	std::cout << e->str(true) << std::endl; */
	/* } */
	for (std::size_t i = 0; i < list->list.size(); ++i)
		list->list[i] = EVAL(list->list[i], env);
	return list;
}
