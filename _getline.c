#include "main.h"

/**
 * _getline - fun that read line stream from the standard input
 * @buffer: pointer to pointer to string that we store the line in
 * @size: the size of the buffer
 * Return: num of char have been read, -1 if nothing is read, 1 otherwise
 */
int _getline(char **buffer, size_t size)
{
	int n_read;
	/* allocate memory of size to store*/
	/* what we read from stdin */
	*buffer = malloc(sizeof(char) * size);
	if (*buffer == NULL)
		exit(EXIT_FAILURE);
	/* read from stdin and store it in buffer */
	n_read = read(STDIN_FILENO, *buffer, size);
	/* if we didnt write anything*/
	if (n_read == 0)
		return (-1);
	else
		return (n_read);

	return (1);
}
