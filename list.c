#include "main.h"

/**
 * key_check -fun that check if the alias aread exist
 * @head: pointer to the head of the list
 * @key: pointer to string of the key
 * Return: the index of the key, -1 otherwise
 */
int key_check(list_t *head, char *key)
{
	int i = 0;
	list_t *temp = head;

	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
			return (i);

		temp = temp->next;
		i++;
	}

	return (-1);
}

/**
*print_list - fun that print elements of a linked list
*@head: pointer to the head of linked list
*/
void print_list(list_t *head)
{
	const list_t *temp = head;
	/* walk trough the list and print it */
	while (temp != NULL)
	{
		dprintf(STDOUT_FILENO, "%s=%s \n", temp->key, temp->value);
		temp = temp->next;
	}
}

/**
*add_list - fun that add node to the end of the list
*@head: pointer to the head of the list
*@key: the key we want add to list
*@value: value we want to add to the list
*/
void add_list(list_t **head, char *key, char *value)
{
	list_t *newNode, *temp;
	int i = 0, j;

	/* create new node of size list_t */
	newNode = malloc(sizeof(list_t));
	if (newNode == NULL)
		return;
	/* cheak if the key is exist */
	i = key_check(*head, key);
	if (i == -1)/* when new node */
	{
		/* fill node with elements */
		newNode->key = strdup(key);
		newNode->value = strdup(value);
		newNode->next = NULL;

		temp = *head;
		if (*head == NULL)/* if the list is empty */
			*head = newNode;
		else
		{
			/* wake though the list to get the end */
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = newNode;
		}
	}
	else
	{ /* if key aready exist */
		temp = *head;
		for (j = 0; j < i; j++)
			temp = temp->next;
		temp->value = strdup(value);
	}
}

/**
 * check_list - fun that get the value of a given key from the alias list
 * @pathname: double pointer of a str
 * @head: pointer to the head of the list
 * @argv: array of strings
 * Return: array of strings
 */
char **check_list(char **pathname, list_t *head, char **argv)
{
	list_t *temp = head;

	while (temp != NULL)
	{
		if (strcmp(temp->key, *pathname) == 0)
		{
			/* let the pathname equal new value*/
			*pathname = strdup(temp->value);
			/* clear it from qoutes */
			check_qoute_2(*pathname);
			/* splite it into arguments */
			argv = split_str(*pathname, " ");
			return (argv);
		}
		temp = temp->next;
	}
	return (argv);
}

/**
*free_list - fun that free linked list
*@head: pointer to the head of the linked list
*/
void free_list(list_t *head)
{
	list_t *node;

	while (head != NULL)
	{
		/* make the node points to what the head points to */
		node = head;
		/* make the header looks to the next node */
		head = head->next;
		/* free the prevoiuse node */
		free(node->key);
		free(node->value);
		free(node);
	}
}
