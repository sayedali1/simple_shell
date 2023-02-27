#include "main.h"
/**
 * check_qoute_2 - fun that check the qoute for a string
 * @argv: pointer to a string
 * Return:pointer of the changed string
 */
char *check_qoute_2(char *argv)
{
	if (argv[0] == '\'')/* if single qoute */
		argv = strdup(strtok(argv, "'"));
	else if (argv[0] == '\"')/* if double qoute */
		argv = strdup(strtok(argv, "\""));

	return (argv);
}

/**
 * check_qoute - fun that check the qoute for a strings
 * @argv: pointer to a array of strings
 */
void check_qoute(char **argv)
{
	int i;

	for (i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\'')/* if single qoute */
			argv[i] = strdup(strtok(argv[i], "'"));
		else if (argv[i][0] == '\"')/* if double qoute */
			argv[i] = strdup(strtok(argv[i], "\""));
	}
}
