#include "readline.hpp"

bool Readline(String prompt, String &output)
{
	char *out = readline(prompt.c_str());
	if (out == NULL)
		return (false);
	if (out && *out)
		add_history(out);
	output = out;
	return (true);
}
