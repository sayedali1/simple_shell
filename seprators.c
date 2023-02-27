#include "main.h"

/**
 * check_seprator - fun that check is the there is is one of the oprators
 * @line: pointer to string we want to check
 * @head: pointer to list of alias
 * @head_asign: pointe to list of varible replacement
 * Return: one if success, -1 otherwise
 */
int check_seprator(char *line, list_t *head, list_t *head_asign)
{
	int j, i;
	oprator op[] = {{';', semcolen}, {'&', anding}, {'|', oring}, {'\0', NULL}};

	/* walk through the oprators */
	for (j = 0; op[j].ch != '\0'; j++)
	{
		/* walk through the line */
		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == op[j].ch)
			{
				op[j].fun(line, head, head_asign);
				return (1);
			}
		}
	}
	return (-1);
}

/**
 * semcolen - fun that do the same as ; oprator do in sh shell
 * @line: pointer to string of the line
 * @head: pointer to the head of list of alias
 * @head_asign: pointe to list of varible replacement
 */
void semcolen(char *line, list_t *head, list_t *head_asign)
{
	char **strings = NULL, **argv = NULL;
	int i;

	/* splite the line with ; int strings */
	strings = split_str(line, ";");
	/* walk through each string */
	for (i = 0; strings[i] != NULL; i++)
	{
		/*  splite each string into arguments */
		argv = split_str_2(strings[i]);
		check_qoute(argv);/* check of there is qoute  */
		execute(argv, &head, &head_asign); /* excute each string */
	}
	free(argv), free(strings);
}

/**
 * anding - fun that do the same as && oprator do in sh shell
 * @line: pointer to string of the line
 * @head: pointer to the head of list of alias
 * @head_asign: pointe to list of varible replacement
 */
void anding(char *line, list_t *head, list_t *head_asign)
{
	char **strings = NULL, **argv = NULL;
	int i, exec = 0;

	/* splite the line into strings with && */
	strings = split_str(line, "&&");
	/* walk trough each string */
	for (i = 0; strings[i] != NULL; i++)
	{
		/* if the previous execute was correct */
		if (exec == 0)
		{
			argv = split_str_2(strings[i]);
			check_qoute(argv);/* check of there is qoute  */
			exec = execute(argv, &head, &head_asign);
		}
	}
	free(argv), free(strings);
}

/**
 * oring - fun that do the same as || oprator do in sh shell
 * @line: pointer to string of the line
 * @head: pointer to the head of list of alias
 * @head_asign: pointe to list of varible replacement
 */
void oring(char *line, list_t *head, list_t *head_asign)
{
	char **strings = NULL, **argv = NULL;
	int i, exec = 1;

	/* splite the line into strings with && */
	strings = split_str(line, "||");
	/* walk trough each string */
	for (i = 0; strings[i] != NULL; i++)
	{
		/* if the previous execute was wrong */
		if (exec != 0)
		{
			argv = split_str_2(strings[i]);
			check_qoute(argv);/* check of there is qoute  */
			exec = execute(argv, &head, &head_asign);
		}
	}
	free(argv), free(strings);
}
