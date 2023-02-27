#ifndef main_h
#define main_h



#define promt "$ "

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>

/**
 * struct list -linked list for alias
 * @key: pointer to string of the key
 * @value: pointer to string of the value
 * @next: pointer to struct of list
 */
typedef struct list
{
	char *key;
	char *value;
	struct list *next;
} list_t;

/**
 * struct oprator - sturct for the built-in oprators
 * @ch: char of the oprator
 * @fun: pointer to fun to excute the comands
 */
typedef struct oprator
{
	char ch;
	void (*fun)(char *, list_t *, list_t *);
} oprator;

/**
 * struct command - sturct for the built-in commands
 * @name: string of the comand name
 * @fun: pointer to fun to excute the comands
 */
typedef struct command
{
	char *name;
	void (*fun)(char **, list_t **);
} command;


extern char **environ;/* varible of the environments */

void print_prompt(int ac);
int _getline(char **buffer, size_t size);
void _unsetenv(char **argv, list_t **head);
void _setenv(char **argv, list_t **head);
void exitt(char **argv, list_t **head);
void change_cd(char **argv, list_t **head);
void new_path(char **pathname, char *fullpath);
char *get_path(char *pathname);
int execute(char **argv, list_t **head, list_t **head_asign);
void/* char * */check_begin_space(char **line);
char **split_str(char *line, char *seprator);
char **split_str_2(char *line);
void semcolen(char *line, list_t *head, list_t *head_asign);
void anding(char *line, list_t *head, list_t *head_asign);
void oring(char *line, list_t *head, list_t *head_asign);
int check_seprator(char *line, list_t *head, list_t *head_asign);
void alias(char **argv, list_t **head);
void add_list(list_t **head, char *key, char *value);
void print_list(list_t *head);
int key_check(list_t *head, char *key);
void check_qoute(char **argv);
char **check_list(char **pathname, list_t *head, char **argv);
char *check_qoute_2(char *argv);
int key_check(list_t *head, char *key);
int check_word(char *str);
int get_len(char *str, size_t *i);
char *get_dollar_list(list_t *head, char **pathname);
char **check_dollar(char **argv, list_t *head);
void check_comment(char **line);
char **execute_line(char *line, list_t **head, list_t **head_asign);
char *_strtok(char **str, char *seprator);
void free_list(list_t *head);
void file_script(char **av, list_t *head, list_t *head_asign);

#endif
