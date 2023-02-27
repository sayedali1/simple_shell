#include "main.h"

/**
 * get_dollar_list - fun that variables replacement arguments
 * @head: pointer to the head of the list
 * @pathname: double pointer to the str
 * Return: pointer to string of the replacemet
 */
char *get_dollar_list(list_t *head, char **pathname)
{
	list_t *temp = head;
	char *cp = *pathname;
	pid_t pid;
	/* delete the $ of the given argv */
	cp = strndup(&cp[1], (strlen(*pathname) - 1));
	/* if it an env */
	if (getenv(cp))
	{
		*pathname = strdup(getenv(cp));
		return (*pathname);
	}
	else if (strcmp(cp, "$") == 0)
	{
		pid = getpid();
		sprintf(*pathname, "%d", pid);
		return (*pathname);
	}
	/* if it in the dollar list */
	while (temp != NULL)
	{
		if (strcmp(temp->key, cp) == 0)
		{
			/* let the pathname equal new value*/
			*pathname = strdup(temp->value);
			/* clear it from qoutes */
			check_qoute(pathname);
			free(cp);
			return (*pathname);
		}
		temp = temp->next;
	}
	free(cp);
	return (*pathname);
}
/**
 * check_dollar - fun that check for $ char in a string
 * @argv: array of strings of the arguments
 * @head: pointer to the head of the list
 * Return: array of strings of the changed arguments
 */
char **check_dollar(char **argv, list_t *head)
{
	int i;
	/* check if there is dollar sign */
	for (i = 0; argv[i] != NULL; i++)
	{
		if  (strchr(argv[i], '$'))
			argv[i] = get_dollar_list(head, &argv[i]);
	}
	return (argv);
}
