# minishell

A small UNIX shell written in C, built as a 42-school `minishell` project. It
reimplements a subset of bash: commands are read line by line with GNU
readline, tokenized by a lexer, organized into a command pipeline AST by a
parser, and executed with proper process handling, pipes, redirections, and
environment variable expansion.

The interactive prompt is a green `DEDSEC ❋` banner followed by the current
directory (driven by the `PWD_HIDE` environment variable). It was developed
and tested on macOS, but the code is portable C with only readline/termcap as
external dependencies.

## Tech stack

- **Language:** C
- **Command-line editing:** GNU readline (`-lreadline`) with termcap
  (`-ltermcap`)
- **Utility library:** custom libft (vendored in `libft/`)
- **Build:** GNU Make

## Prerequisites

- A C compiler (`cc`/gcc/clang) and `make`
- GNU readline development headers (e.g. `libreadline-dev` on Debian/Ubuntu,
  or `brew install readline` on macOS)

> Note: the Makefile hardcodes the macOS Homebrew readline paths
> (`/usr/local/opt/readline`). On other systems, install the readline dev
> package and adjust the `-I`/`-L` flags in the Makefile accordingly.

## Build

```sh
make
```

This compiles `libft` and links the `minishell` binary.

Other targets:

```sh
make clean    # remove object files
make fclean   # clean + remove the minishell binary
make re       # fclean + rebuild from scratch
```

## Usage

```sh
./minishell
```

You get an interactive prompt where you can type commands. The shell supports:

### Builtins

| Command | Description |
| --- | --- |
| `echo` | Print arguments |
| `cd` | Change directory |
| `pwd` | Print the working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print the environment |
| `exit` | Exit the shell with a status code |

### Execution features

- **Pipes** — `cmd1 | cmd2 | cmd3` pipelines (each stage runs in its own
  process, managed via a pid-tracking list)
- **Redirections** — `<`, `>`, `>>`, and here-documents `<<` (implemented
  with pipes, with its own SIGINT handling)
- **Environment variable expansion** — `$VAR` in command lines is replaced
  from the shell's environment (see `srcs/parsing/vars.c` and `lexer.c`)
- **Signal handling** — SIGINT/SIGQUIT are caught and handled (interactive
  prompt, child processes, and here-doc input each have dedicated handlers)

### Test scripts

`scripts/` contains small stdin-driven scripts used for testing redirections
and pipelines:

- `scripts/double.sh` — reads stdin line by line and prints each line twice
- `scripts/uppercase.sh` — reads stdin and converts it to uppercase

For example: `echo hello | ./scripts/uppercase.sh` prints `HELLO`.

## Project layout

```
srcs/
├── parsing/     # lexer, parser, AST construction, variable expansion
├── builtins/    # echo, cd, pwd, export, unset, env, exit
├── execution/   # exec, redirects, pipes (exec_pipe/), pid management
└── utils/       # signals, environment copying, error printing, helpers
```

## License

[MIT](LICENSE)
