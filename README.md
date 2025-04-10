#	Minishell 🐚 - 42 School Lisbon

### Table of Contents
* [Introduction](#introduction-)
* [How to Install](#how-to-install-️)
* [How to Use?](#how-to-use-)
* [Project Objectives](#project-objectives-)
* [Shell Features](#shell-features-)
* [Conclusion](#conclusion-)


## Introduction 📖

Minishell is a 42 School project that challenges students to recreate a simplified UNIX shell in C. This shell mimics the behavior of Bash by interpreting and executing commands entered by the user in a terminal environment.

The primary goal is to build a robust shell capable of parsing user input, managing environment variables, executing built-in and external commands, and handling input/output redirection, pipes, and signal management — all while respecting UNIX conventions and behavior.

## How to Install 🛠️


**Steps**

To compile and run Minishell, follow these steps:

Dependencies:
Ensure you have the following installed on your system:

readline
gcc / clang
make

Installing Readline (if needed):
```
sudo apt-get update
sudo apt-get install libreadline-dev
```
Building the Project:
```
make
```

## How to Use? 👨‍💻:

After building the project, launch the shell using:
```
./minishell
```
Also if you want to make tests using valgrind, you could just run:
```
make v
```
From here, you can run commands just as you would in a regular shell.
Examples:
```
minishell$ echo Hello World
minishell$ ls -la | grep .c > output.txt
minishell$ export NAME=42
minishell$ echo $NAME
minishell$ cat << EOF
```

##	Project Objectives 🎯

The Minishell project develops a deep understanding of:
	•	Process creation using fork(), execve(), and wait().
	•	Signal handling (e.g., SIGINT, SIGQUIT).
	•	Environment variable management and expansion.
	•	Input/output redirection (>, >>, <, <<).
	•	Command parsing and tokenization with support for quotes and escapes.
	•	Handling pipes between multiple commands (|).
	•	Implementing built-in commands without calling external programs.

##	Shell Features

Key features implemented in Minishell:
•	Prompt: A dynamic shell prompt that waits for user input.
•	Built-in Commands:
	•	echo
	•	cd
	•	pwd
	•	export
	•	unset
	•	env
	•	exit
•	Pipes (|): Chain multiple commands through standard output/input.
•	Redirections:
	•	>: Redirect output
	•	>>: Append output
	•	<: Read from a file
	•	<<: Here-document support
•	Environment Variable Expansion:
	•	echo $HOME prints the value of $HOME.
•	Quotes Handling:
	•	Supports single ' and double " quotes.
•	Signal Handling:
	•	Custom handlers for Ctrl+C, Ctrl+\, etc., mimicking Bash behavior.
•	WildCards (*): A expansion complementing the matches file's names.

## Conclusion ✅

Minishell is a group project developed by me and [@JorgeMarquez05](https://github.com/JorgeMarquez05). Beyond diving into the inner workings of a UNIX shell—covering everything from parsing to execution, and from redirection to signal handling—it was also a collaborative effort where we had to divide tasks, complement each other’s code, and work closely together.

This project deepened my understanding of process control, memory management, and terminal behavior in C. It’s a strong foundation for any developer looking to better understand how shells like Bash or Zsh function internally.

Feel free to test it out, explore the code, or contribute improvements!
