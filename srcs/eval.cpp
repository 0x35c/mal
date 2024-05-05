#include "MalEnv.hpp"
#include <iostream>

MalType *eval_ast(MalType *ast, MalEnv env)
{
	MalSymbol *symbol = dynamic_cast<MalSymbol *>(ast);
	if (symbol) {
		MalFunc *func =
		    dynamic_cast<MalFunc *>(env.find(symbol->str(true)));
		if (!func)
			throw std::invalid_argument("invalid symbol");
		return func;
	}
	MalList *list = dynamic_cast<MalList *>(ast);
	if (!list)
		return ast;
	for (std::size_t i = 0; i < list->list.size(); ++i)
		list->list[i] = EVAL(list->list[i], env);
	return list;
}
