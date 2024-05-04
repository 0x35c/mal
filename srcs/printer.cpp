#include "printer.hpp"

const String pr_str(MalType *e, bool print_readably)
{
	return e->str(print_readably);
}
