#include "main.h"

/**
 * exitt - fun that exit from the shell
 * @argv: dounble pointer to the argurments
 * @head: pointer to struct of list_t
 */
void exitt(char **argv, __attribute__((unused))list_t **head)
{
	/* if exit with no arguments */
	if (argv[1] == NULL)
		exit(EXIT_SUCCESS);
	/* exit with argument */
	exit(atoi(argv[1]));
}

/**
 * _setenv - fun that add environ variable
 * from the environment list
 * @argv: dounble pointer to the argurments
 * @head: pointer to struct of list_t
 */
void _setenv(char **argv, __attribute__((unused))list_t **head)
{
	int error;
	/* add the value and the key and overwite */
	/* if it aready exist*/
	error = setenv(argv[1], argv[2], 1);
	/* if fails */
	if (error == -1)
		dprintf(STDERR_FILENO, "cannot setenv\n");
}

/**
 * _unsetenv - fun that delete environ variable
 * from the environment list
 * @argv: dounble pointer to the argurments
 * @head: pointer to struct of list_t
 */
void _unsetenv(char **argv, __attribute__((unused))list_t **head)
{
	int error;
	/* delete environ */
	error = unsetenv(argv[1]);
	if (error == -1)
		dprintf(STDERR_FILENO, "cannot setenv\n");
}

/**
 * change_cd - fun that chanage the directory
 * @argv: dounble pointer to the argurments
 * @head: pointer to struct of list_t
*/
void change_cd(char **argv, __attribute__((unused))list_t **head)
{
	char *buffer = NULL;
	size_t len = 0;
	struct  stat bufferr;
	/* add oldpwd varibale to know the old pwd */
	if (getenv("OLDPWD") == NULL)
		setenv("OLDPWD", getcwd(buffer, len), 1);

	if (argv[1] == NULL)
	{   /* go to root if the no arguments*/
		chdir("/root");
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", "/root", 1);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		/* go to the old pwd if if agurment is - */
		chdir(getenv("OLDPWD"));/* go to old dir */
		/* set oldpwd varible to pwd before change */
		setenv("OLDPWD", getenv("PWD"), 1);
		/* set pwd to the new dir*/
		setenv("PWD", getcwd(buffer, len), 1);
	}
	else
	{
		/* check if there dir is right */
		stat(argv[1], &bufferr);
		if (S_ISDIR(bufferr.st_mode))
		{
			/* chage the dir */
			chdir(argv[1]);
			/* set oldpwd varible to pwd before change */
			setenv("OLDPWD", getenv("PWD"), 1);
			/* set pwd to the new dir*/
			setenv("PWD", argv[1], 1);
		}
		/* else *//* we call error fun here */
	}

	free(buffer);
}
/**
 * alias - fun that addes alias to the alias list
 * @argv: dounble pointer to the argurments
 * @head: pointer to struct of list_t
 */
void alias(char **argv, list_t **head)
{
	char **strings = NULL;
	int i, j, index;
	list_t *temp;

	if (argv[1] == NULL)
		print_list(*head);

	for (i = 1; argv[i] != NULL; i++)
	{
		index = key_check(*head, argv[i]);
		/* check there is equal sign or no */
		if (strchr(argv[i], '='))
		{
			strings = split_str(argv[i], "=");
			add_list(head, strings[0], strings[1]);
		}
		else if (index != -1)
		{/* get the right index for the given key  */
			temp = *head;
			for (j = 0; j < index; j++)
				temp = temp->next;
			dprintf(STDOUT_FILENO, "%s=%s \n", temp->key, temp->value);
		}
		else
			perror(argv[i]);
	}
}
