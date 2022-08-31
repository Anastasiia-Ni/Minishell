# Minishell

## About project:
Minishell is a command interpreter based on bash.
It implements basic functionalities of a shell like environment variable, builtins, pipes, redirections...

The program is written in C.

#### Allowed functions: 
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs.

#### Builtins implemented:
- `echo`	echo the string to standart output. -n flag: do not output the trailing newline
- `cd`	change the shell working directory
- `pwd`	print name of current directory
- `export`	set export attribute for shell variables
- `unset`	unset values of shell variables
- `env`	print the environment
- `exit`	cause the shell to exit with the exit status specified

## Index:
- [includes](https://github.com/Anastasiia-Ni/Minishell/tree/master/includes): contains header
- [libft](https://github.com/Anastasiia-Ni/Minishell/tree/master/libft): contains the source code of my libft library, which is used in the program
- [source](https://github.com/Anastasiia-Ni/Minishell/tree/master/sources): contains the source code of the program

## Installation:
```
$ git clone git@github.com:Anastasiia-Ni/Minishell.git
$ cd Minishell
$ make
```
## Usage:
`$ ./minishell` 
