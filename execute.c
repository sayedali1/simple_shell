#include "main.h"

/**
 * check_comment - fun that delete any comments if exits
 * @line:double pointer to str
 */
void check_comment(char **line)
{
	char *str = strchr(*line, '#');

	if (str != NULL)
		*line = strndup(*line, strlen(*line) - strlen(str));
}

/**
 * check_command - fun that check if there the is built-in
 * command and execute it
 * @argv: array of arguments
 * @head: pointer to the list of alias
 * Return: 1 if success, 0 otherwise
 */
int check_command(char **argv, list_t **head)
{
	int i;

	command command[] = {{"exit", exitt}, {"setenv", _setenv},
	{"unsetenv", _unsetenv}, {"cd", change_cd}, {"alias", alias}, {NULL, NULL}};

	/* check if the pathname is built in commands */
	for (i = 0; command[i].name != NULL; i++)
	{
		argv[0] = check_qoute_2(argv[0]);/* check for qoute */
		if (strcmp(argv[0], command[i].name) == 0)
		{
			command[i].fun(argv, head);
			return (1);
		}
	}
	return (0);
}

/**
 * check_asign - fun that add the argument to the asign list
 * @argv: array of the strings of the arguments
 * @head: double pointer to the head of the list
 * Return: -1 if there is no sign, 0 otherwise
 */
int check_asign(char **argv, list_t **head)
{
	int i;
	char **strings = NULL;

	for (i = 0; argv[i] != NULL; i++)
	{
		if (strchr(argv[i], '='))
		{
			strings = split_str(argv[i], "=");
			add_list(head, strings[0], strings[1]);
		}
		else
			return (-1);
	}

	return (0);
}

/**
 * execute - fun that execute a given command
 * @argv: array of string of the arguments
 * @head: pointer to the head of alias list
 * @head_asign: pointer to the head of replacement list
 * Return:statues of the executed command
 */
int execute(char **argv, list_t **head, list_t **head_asign)
{
	struct stat buffer;
	int status, asign;
	char str[10];

	/* check built_in commands */
	if (check_command(argv, head))
		return (0);

	/* check if argv is an alias */
	argv = check_list(&argv[0], *head, argv);
	/* check if its asign */
	asign = check_asign(argv, head_asign);
	if ((asign) != -1)
		return (0);
	check_qoute(argv);/* check if there is qoutes */
	/* check if there any $ values */
	argv = check_dollar(argv, *head_asign);
	/* create the new path and chage the pathname to the new path */
	new_path(&argv[0], get_path(argv[0]));
	/* check is the pathname is exist */
	if (stat(argv[0], &buffer) == 0)
	{
		if (fork() == 0)/* when we in the child */
			/* execute new process */
			execve(argv[0], argv, environ);
		else
		{
			wait(&status);
			sprintf(str, "%d", status);
			add_list(head_asign, "?", str);
		}
	}
	return (status);
}

/**
 * execute_line - fun that take a given line execute it
 * @line: line we want to execute
 * @head: pointer to the head of alias list
 * @head_asign: pointer to the head of replacement list
 * Return: pointer to str of the command, NULL otherwise
 */
char **execute_line(char *line, list_t **head, list_t **head_asign)
{
	int separtor = 0, n_read;
	char **argv = NULL;
	int status;

	n_read = strlen(line);
		/* delete the extra element we get from the getline */
	if (line[n_read - 1] == '\n')
		line[n_read - 1] = '\0';
	/* check if there any comments */
	check_comment(&line);
	/* check if there is separtor */
	separtor = check_seprator(line, *head, *head_asign);

	if (separtor == -1)/* if seprator */
	{
		argv = split_str_2(line);/* splite line */
		status = execute(argv, head, head_asign);/* execute the line */
		if (status != 0)
			return (argv);
	}

	return (NULL);
}
