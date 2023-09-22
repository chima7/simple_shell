#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Read/write buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

/* Flags for convert_number() */
#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

/* Use system getline() flag */
#define USE_GETLINE 0
#define USE_STRTOK  0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;

/* Structure for singly linked list of strings */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/* Structure containing information passed to functions */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

/* Function prototypes */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int display_history(info_t *info);
int remove_alias(info_t *info, char *str);
int add_alias(info_t *info, char *str);
int print_alias_str(list_t *node);
int manage_alias(info_t *info);
int _displayEnv(info_t *info);
char *_retrieveEnv(info_t *info, const char *name);
int _initializeEnv(info_t *info);
int _removeEnv(info_t *info);
int _populateEnvList(info_t *info);
void _eprintString(char *str);
int _eputCharacter(char c);
int _putToFD(char c, int fd);
int _putsToFD(char *str, int fd);
int _strtoi(char *s);
void printErrorMessage(info_t *info, char *estr);
int printInteger(int input, int fd);
char *convertToBase(long int num, int base, int flags);
void stripComments(char *buf);
char *_custom_strncpy(char *dest, const char *src, int n);
char *_custom_strncat(char *dest, const char *src, int n);
char *_custom_strchr(const char *s, int c);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int main(int ac, char **av);
int bfree(void **ptr);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *_custom_memset(char *s, char b, unsigned int n);
void custom_free(char **pp);
void *_custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new_str);

