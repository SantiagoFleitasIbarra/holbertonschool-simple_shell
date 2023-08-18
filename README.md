# Simple Shell
![Holberton logo](https://techcrunch.com/wp-content/uploads/2015/11/holberton-logo-horizontal.jpg)
## Content
* [Overview](#Overview)
* [Builtins](#Builtins)
* [Example](#Example)
* [List of functions and system calls](#List-of-functions-and-system-calls)
* [Authors](#Authors)
## Overview
A Unix shell is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems. The shell is both an interactive command language and a scripting language, and is used by the operating system to control the execution of the system using shell scripts.

## Builtins
| Command | Description |
| ------- | ----------- |
| `cd` | Change the current working directory |
| `env` | Print the environment |
| `exit` | Exit the shell |
| `help` | Print a help messages for built-ins |

## Example
### Clone repo using HTTPS
```
$ git clone https://github.com/SantiagoFleitasIbarra/holbertonschool-simple_shell.git
```

### Compilation
You can compile the files using this command to check that there are no errors:
```
$ gcc -Wall -pedantic -Werror Wextra *.c -o hsh
```

### Usage
Enter the interactive mode after compilation:
```bash
$ ./hsh
 #cisfun$ /bin/ls
 README.md exec.c shell.h shell.c prompt.c
 #cisfun$
 #cisfun$ exit
$
```
---

### Usage
Enter the non-interactive mode after compilation:
```bash
$ echo "/bin/ls" | ./hsh
README.md exec.c shell.h shell.c prompt.c
$
```
---

## List of functions and system calls

* all functions from string.h
* access (man 2 access)
* chdir (man 2 chdir)
* close (man 2 close)
* closedir (man 3 closedir)
* execve (man 2 execve)
* exit (man 3 exit)
* _exit (man 2 _exit)
* fflush (man 3 fflush)
* fork (man 2 fork)
* free (man 3 free)
* getcwd (man 3 getcwd)
* getline (man 3 getline)
* getpid (man 2 getpid)
* isatty (man 3 isatty)
* kill (man 2 kill)
* malloc (man 3 malloc)
* open (man 2 open)
* opendir (man 3 opendir)
* perror (man 3 perror)
* printf (man 3 printf)
* fprintf (man 3 fprintf)
* vfprintf (man 3 vfprintf)
* sprintf (man 3 sprintf)
* putchar (man 3 putchar)
* read (man 2 read)
* readdir (man 3 readdir)
* signal (man 2 signal)
* stat (__xstat) (man 2 stat)
* lstat (__lxstat) (man 2 lstat)
* fstat (__fxstat) (man 2 fstat)
* strtok (man 3 strtok)
* wait (man 2 wait)
* waitpid (man 2 waitpid)
* wait3 (man 2 wait3)
* wait4 (man 2 wait4)
* write (man 2 write)


## Authors
* Santiago Fleitas
* Agustina Araujo
