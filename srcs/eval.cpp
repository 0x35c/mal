#include "MalEnv.hpp"
#include <iostream>

static MalType *eval_ast(MalType *ast, MalEnv env);

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

static MalType *eval_ast(MalType *ast, MalEnv env)
{
	switch (ast->type) {
	case MalType::SYMBOL:
		return env.get(dynamic_cast<MalSymbol *>(ast)->str(true));
	case MalType::LIST: {
		MalList *list = dynamic_cast<MalList *>(ast);
		for (std::size_t i = 0; i < list->list.size(); ++i)
			list->list[i] = EVAL(list->list[i], env);
		return list;
	}
	default:
		return ast;
	}
}
