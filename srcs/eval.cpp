#include "MalEnv.hpp"
#include <iostream>

static MalType *eval_ast(MalType *ast, MalEnv &env);

MalType *EVAL(MalType *ast, MalEnv &env)
{
	if (ast->type == MalType::LIST) {
		MalList *list = static_cast<MalList *>(ast);
		if (list->list[0]->type == MalType::SYMBOL) {
			MalSymbol *symbol =
			    static_cast<MalSymbol *>(list->list[0]);
			if (symbol->str(true) == "def!") {
				auto first = list->list[1];
				if (first->type == MalType::LIST)
					first = eval_ast(first, env);
				const auto second = EVAL(list->list[2], env);
				return eval_ast(
				    env.set(first->str(true), second), env);
			} else if (symbol->str(true) == "let*") {
				// TODO
			}
		}
		MalList *new_list =
		    dynamic_cast<MalList *>(eval_ast(list, env));
		if (new_list->list[0]->type == MalType::FUNC) {
			MalFunc *func =
			    static_cast<MalFunc *>(new_list->list[0]);
			if (func)
				return func->apply(new_list->list[1],
				                   new_list->list[2]);
		}
	}
	return (eval_ast(ast, env));
}

static MalType *eval_ast(MalType *ast, MalEnv &env)
{
	switch (ast->type) {
	case MalType::SYMBOL:
		return env.get(static_cast<MalSymbol *>(ast)->str(true));
	case MalType::LIST: {
		MalList *list = static_cast<MalList *>(ast);
		auto copy = new MalList();
		for (std::size_t i = 0; i < list->list.size(); ++i)
			copy->add(EVAL(list->list[i], env));
		return copy;
	}
	default:
		return ast;
	}
}
