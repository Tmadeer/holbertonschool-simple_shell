# Simple Shell

A simple UNIX command line interpreter written in C, built as part of
the Holberton School curriculum.

## Table of Contents

- [Description](#description)
- [Compilation](#compilation)
- [Usage](#usage)
- [Builtin Commands](#builtin-commands)
- [Files and Functions](#files-and-functions)
- [Limitations](#limitations)
- [Authors](#authors)

## Description

`hsh` reads commands from standard input (interactively or from a
pipe/file), locates the matching executable via `PATH`, and runs it
in a child process — similarly to `sh`.

## Compilation

```
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh
```

## Usage

```
$ ./hsh
$ /bin/ls
hsh main.c main.h
$ env
HOME=/home/user
PATH=/usr/bin:/bin
$ exit
```

Non-interactive:

```
$ echo "/bin/ls" | ./hsh
hsh main.c main.h
```

## Builtin Commands

| Command | Description |
|---|---|
| `exit` | Exits the shell. No arguments are handled. |
| `env` | Prints the current environment, one variable per line. |

## Files and Functions

### `main.h`
Header file: macros, includes, and function prototypes shared across
the project.

### `main.c`
| Function | What it does |
|---|---|
| `main` | Runs the shell's main loop: prints the prompt, reads a line, tokenizes it, checks for builtins, resolves and executes the command, and tracks the exit status. |

### `path.c`
| Function | What it does |
|---|---|
| `get_path` | Returns the value of the `PATH` environment variable. |
| `find_path` | Searches each directory in `PATH` for an executable matching the given command name. |
| `resolve_command` | Decides how to resolve a command: uses it directly if it contains `/`, otherwise searches `PATH` via `find_path`. |

### `builtin.c`
| Function | What it does |
|---|---|
| `print_env` | Prints every environment variable, one per line. |
| `handle_builtin` | Checks if the typed command is a builtin (`exit` or `env`) and runs it. |

### `helpers.c`
| Function | What it does |
|---|---|
| `tokenize_line` | Splits a line of input into an array of arguments, separated by whitespace. |
| `execute_command` | Forks a child process and runs the resolved command with `execve`, then waits for it and returns its exit status. |

## Limitations

- No pipes (`|`), redirection (`>`, `<`), or command chaining (`;`, `&&`, `||`).
- No quoting/escaping support in the input line.
- `exit` does not accept a numeric status argument.
- No comments (`#`) or variable substitution (e.g. `$HOME`).

## Authors

- Tumadhir Hani Fattah <hanitmader@gmail.com>
- Abdulrahman Saleh Alduqail <d.7.o.m.e.989@gmail.com>
