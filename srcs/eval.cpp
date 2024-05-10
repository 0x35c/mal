#include "Env.hpp"
#include <iostream>

static MalType *eval_ast(MalType *ast, Env &env);
static MalType *_def(MalList *list, Env &env);
static MalType *_let(MalList *list, Env &env);
static MalType *_do(MalList *list, Env &env);
static MalType *_if(MalList *list, Env &env);
static MalType *_fn(MalList *list, Env &env);

static MalType *_def(MalList *list, Env &env)
{
	if (list->list[1]->type != MalType::SYMBOL)
		throw std::invalid_argument(
		    "can't def! without a symbol as first argument");
	const auto first = static_cast<MalSymbol *>(list->list[1].get());
	const auto second = EVAL(list->list[2].get(), env);
	env.set(first->value, second);
	return eval_ast(second, env);
}

static MalType *_let(MalList *list, Env &env)
{
	if (list->list[1]->type != MalType::LIST)
		throw std::invalid_argument(
		    "can't let* without a list as first argument");
	// NOTE might need to put actual vectors
	Env new_env = Env(&env, StringVec{}, NULL);
	const auto args = static_cast<MalList *>(list->list[1].get());
	const auto size = args->list.size();
	for (std::size_t i = 0; i < size - (size % 2); i += 2) {
		const auto key = static_cast<MalSymbol *>(args->list[i].get());
		new_env.set(key->value, EVAL(args->list[i + 1].get(), new_env));
	}
	return EVAL(list->list[2].get(), new_env);
}

static MalType *_do(MalList *list, Env &env)
{
	auto ret = std::unique_ptr<MalType>();
	for (auto &e : list->list) {
		ret = std::unique_ptr<MalType>(eval_ast(e.get(), env));
	}
	return ret.get()->dup();
}

static MalType *_if(MalList *list, Env &env)
{
	if (list->list.size() < 3 || list->list.size() > 4)
		throw std::invalid_argument(
		    "can't if on args nb different than 3 or 4");
	const auto el =
	    std::unique_ptr<MalType>(EVAL(list->list[1].get(), env));
	const auto _true = [](MalType *_el) {
		return (_el->type != MalType::NIL &&
		        _el->type != MalType::FALSE);
	};
	if (_true(el.get()))
		return EVAL(list->list[2].get(), env);
	else if (list->list.size() == 4)
		return EVAL(list->list[3].get(), env);
	return new MalNil;
}

static MalType *_fn(MalList *list, Env &env)
{
	// TODO
	(void)list;
	(void)env;
	return NULL;
}

MalType *EVAL(MalType *ast, Env &env)
{
	if (ast->type == MalType::LIST) {
		auto list = static_cast<MalList *>(ast);
		if (list->empty())
			return new MalNil;
		if (list->list[0]->type == MalType::SYMBOL) {
			MalSymbol *symbol =
			    static_cast<MalSymbol *>(list->list[0].get());
			if (symbol->value == "def!")
				return _def(list, env);
			if (symbol->value == "let*")
				return _let(list, env);
			if (symbol->value == "do")
				return _do(list, env);
			if (symbol->value == "if")
				return _if(list, env);
			if (symbol->value == "fn*")
				return _fn(list, env);
		}
		auto copy = std::unique_ptr<MalList>(
		    static_cast<MalList *>(eval_ast(list, env)));
		if (copy->list[0]->type == MalType::FUNC) {
			return static_cast<MalFunc *>(copy->list[0].get())
			    ->apply(copy.get());
		} else {
			throw std::invalid_argument(
			    "not a function as first element");
		}
	}
	return (eval_ast(ast, env));
}

static MalType *eval_ast(MalType *ast, Env &env)
{
	switch (ast->type) {
	case MalType::SYMBOL: {
		auto symbol = static_cast<MalSymbol *>(ast)->value;
		return env.get(symbol)->dup();
	}
	case MalType::LIST: {
		MalList *list = static_cast<MalList *>(ast);
		auto copy = new MalList{};
		for (auto &e : list->list)
			copy->add(EVAL(e.get(), env));
		return copy;
	}
	default:
		return ast->dup();
	}
}
