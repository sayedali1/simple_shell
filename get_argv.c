#include "main.h"
/**
 * check_begin_space - fun that delete the spaces from
 * the begining of line
 * @line: pointer to string we want to check
 * Return: pointer to newline
 */
void/* char * */check_begin_space(char **line)
{
	char *newline = NULL;
	unsigned int spaces = 0, i;
	
	newline = malloc(sizeof(char) * strlen(*line));
	strcpy(newline, *line);

	for (i = 0; newline[i] == ' '; i++);
	
	spaces = strlen(newline) - i;
	*line = malloc(sizeof(char) * (spaces + 1));
	 if(*line == NULL)
		return;
	strcpy(*line, &newline[i]);
	
	free(newline);
}
/**
 * split_str - fun that splite string with a given seprator
 * @line: pointer to string we want to splite
 * @seprator: pointer to str of the seprator
 * Return: array of strings
 */
char **split_str(char *line, char *seprator)
{
	char *token = NULL, *cpline = NULL;
	char **strings = NULL;
	int lines = 0, i;
	/* check for spaces in the begining of a line */
	/* line =  */check_begin_space(&line);
	cpline = strdup(line);
	/* calc how many strings to allcate it  */
	token = _strtok(&cpline, seprator);

	while (token != NULL)
	{
		lines++;
		token = _strtok(&cpline, seprator);
	}
	strings = malloc(sizeof(char *) * (lines + 1));
	if (strings == NULL)
		exit(EXIT_FAILURE);
	/* splite the line into strings */
	token = _strtok(&line, seprator);
	i = 0;
	while (token != NULL)
	{	/* allocate memory for each string */
		strings[i] = malloc(sizeof(char) * strlen(token));
		if (strings[i] == NULL)
		{
			for (i = 0; i < lines; i++)
				free(strings[i]);
			free(strings);
			exit(EXIT_FAILURE);
		}
		strings[i] = token;/* make each string points to token */
		token = _strtok(&line, seprator);
		i++;
	}
	strings[i] = NULL;/* make last element equal NULL */
	free(token), free(cpline);
	return (strings);
}

/**
*check_word - fun that get num on words in the str
*@str: pointer to the first element in str
*Return: num of words
*/
int check_word(char *str)
{
	size_t i = 0, word = 0, flag = 0, flag_2 = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		/* check if there is any qoutes */
		if ((str[i] == '\'' || str[i] == '\"') && flag_2 == 0)
			flag_2 = 1;
		else if ((str[i] == '\'' || str[i] == '\"') && flag_2 == 1)
			flag_2 = 0;

		/* check for spaces */
		if ((str[i] != ' ' && str[i] != '\0') && flag == 0)
		{
			word++;
			flag = 1;
		}
		else if ((str[i] == ' ' && flag_2 == 0) || i == strlen(str) - 1)
			flag = 0;
	}
	return (word);
}

/**
*get_len - get the len of each word in the str
*@str: pointer to the first element in str
*@i: pointer to hold the number of the index
*Return: len of the word, 0 otherwise
*/
int get_len(char *str, size_t *i)
{
	int len = 0, flag = 0, flag_2 = 0;

	while (*i <= strlen(str))
	{
		/* check for qoutes */
		if ((str[*i] == '\'' || str[*i] == '\"') && flag_2 == 0)
			flag_2 = 1;
		else if ((str[*i] == '\'' || str[*i] == '\"') && flag_2 == 1)
			flag_2 = 0;

		/* check for spaces */
		if (((str[*i] != ' ' && str[*i] != '\0')) || flag_2 == 1)
		{
			len++;
			flag = 1;
		}
		else if ((str[*i] == ' ' || str[*i] == '\0') && flag == 1)
		{
			if (flag_2 == 0)
				return (len);

			flag = 0;
		}
		*i += 1;
	}
	return (0);
}

/**
 * split_str_2 - fun that spilt string with respect to qoutes
 * @line: pointer to string we want to spilt
 * Return: array of strings
 */
char **split_str_2(char *line)
{
	char **strings = NULL;
	int i, len = 0;
	size_t *p, index;
	int word = 0;

	/* check if there is spaces */
	/* line =  */check_begin_space(&line);
	/* get the num of words in the line */
	word = check_word(line);
	/* create memory size of words */
	strings = malloc(sizeof(char *) * (word + 1));

	index = 0;
	for (i = 0; i < word; i++)
	{
		p = &index;/* hold the index of the line */
		len = get_len(line, p);/* get len of each word */
		/* alocate memory size of len */
		strings[i] = malloc(sizeof(char) * (len + 1));
		if (strings[i] == NULL)
		{
			for (i = 0;  i <= word ; i++)
				free(strings[i]);
			free(strings);
			return (NULL);
		}
		/* duplicate the word from the line */
		strings[i] = strndup(&line[*p - len], len);
	}
	strings[i] = NULL;

	return (strings);
}
