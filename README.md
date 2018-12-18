# simple-shell
Basic shell that will process up to 64 arguments

# Running simple-shell
After compiling simple-shell, one can simply call the executible. This program's main takes no arguments.
```
./simple-shell
```

# Interface
Running the program, will present the user with a prompt
```
input> 
```
Here, the user can enter a command for the shell to execute. If the shell recieves more than 64 arguments it will print the following to stderr: 
```
Warning: More than 64 arguments passed, ignoring arguments from <65th argument> onwards...
```
If the command given was not recognized it will then print:
```
Error: The command <command> could not be found.
```
Otherwise the command will be run. Any side effects of that command can then be expected to occur. Then the user will be presented with another prompt. The program will loop continuously, providing prompts znd executing commands, until the user decides to abort the process.
