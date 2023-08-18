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

## Authors
* Santiago Fleitas
* Agustina Araujo
