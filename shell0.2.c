#include "main.h"

/**
 * _error - fun that print error messesge
 * @shell: pointer to shell name
 * @arg: pointer to command name
 * @numOforders: orders numbers
 */
void _error(char *shell, char *arg, int numOforders)
{
	dprintf(STDOUT_FILENO, "%s: %d: ", shell, numOforders);
	perror(arg);
}

/**
 * print_prompt - fun that print prompt
 * @ac: num of arguments
 */
void print_prompt(int ac)
{
	if (isatty(STDIN_FILENO) && ac != 2)/* if we in interactive mode */
		write(1, promt, 2); /* print the prompt */
}


/**
 * file_script - fun that handle file script
 * @av: array of strings of the arguments
 * @head: pointer to the list of alias
 * @head_asign: pointer to the list of replacement var
 */
void file_script(char **av, list_t *head, list_t *head_asign)
{
	size_t len = 1024;
	FILE *fd;
	char **arg = NULL;
	char *line = NULL;
	int numOforders = 0;

	fd = fopen(av[1], "r");
	if (fd == NULL)
		_error(av[0], av[1], numOforders);
	else
	{
		line = malloc(sizeof(char) * len);
		while (fgets(line, len, fd) != NULL)
		{
			numOforders++;
			arg = execute_line(line, &head, &head_asign);
			if (arg != NULL)
				_error(av[0], arg[0], numOforders);
		}
		fclose(fd);
	}
}

/**
 * main - fun that act like sh shell
 * @ac: num of arguments
 * @av: array of strings of the arguments
 * Return: 0
 */
int main(int ac, __attribute__((unused))char **av)
{
	int n_read, numOforders = 0;
	char *line = NULL;
	char **arg = NULL;
	size_t len = 0;
	list_t *head = NULL, *head_asign = NULL;

	add_list(&head_asign, "?", "0");/* set the defult exit status to 0 */
	if (ac == 2)/* start get the line from the terminal */
	{
		file_script(av, head, head_asign);
	}
	else if (ac == 1)
	{
		print_prompt(ac);/* print the prompt */
		while ((n_read =  getline(&line, &len, stdin)) != -1)
		{
			 /* line =  */check_begin_space(&line);
			if (n_read == 1 || line[0] == '\n')
			{
				write(1, promt, 2);
				continue;
			}
			numOforders++;/* num of written commands */
			arg = execute_line(line, &head, &head_asign);
			if (arg != NULL)
				_error(av[0], arg[0], numOforders);
			print_prompt(ac);/* print the prompt */
		}
	}
	if (n_read == -1 && isatty(STDIN_FILENO) && ac != 2)
		printf("\n");/* if terminate without type anything */
	free(arg);
	free(line);
	free_list(head);
	free_list(head_asign);
	return (0);
}
