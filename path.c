#include "main.h"

/**
 * new_path - fun the change the size of the pathname to the new one
 * @pathname: the name of the command
 * @fullpath: the new pathname
 */
void new_path(char **pathname, char *fullpath)
{
	if (fullpath != NULL)
	{
		/* change the allocated memory for the argv[0]  */
		*pathname = realloc(*pathname, (sizeof(char) * strlen(fullpath)));
		if (*pathname == NULL)
			return;
		*pathname = fullpath;/* add the new path to argv[0] */
	}
}

/**
 * get_path - fun that get the full path of a given command
 * @pathname: the command we want to get its path
 * Return: the fullpath, NULL otherwise
 */
char *get_path(char *pathname)
{
	char *path = NULL, *dir = NULL, *cp_path = NULL, *fullpath = NULL;
	struct  stat buffer;

	/* get the path */
	path = getenv("PATH");


	cp_path = strdup(path);/* copy it to can add the /bin */
	dir = strtok(cp_path, ":");/* separate the cp_path */

	if (stat(pathname, &buffer) != 0)
	{
		/* walk through the full path unil we get the right directory */
		while (dir)
		{
			fullpath = malloc((sizeof(char) *
			(strlen(dir) + (strlen(pathname)) + 2)));
			if (fullpath == NULL)
				exit(EXIT_FAILURE);
			/* concat the path with the pathname */
			strcpy(fullpath, dir);
			strcat(fullpath, "/");
			strcat(fullpath, pathname);
			/* check if the full path exist */
			if (stat(fullpath, &buffer) == 0)
			{
				free(cp_path);
				return (fullpath);
			}
			free(fullpath);
			dir = strtok(NULL, ":");
		}
	}
	free(cp_path);
	free(dir);
	return (NULL);
}
