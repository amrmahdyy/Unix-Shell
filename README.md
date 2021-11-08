
1. **The internal shell command "exit" which terminates the shell**
   - Concepts: shell commands, exiting the shell.
   - System calls: `exit()`
2. **A command with no arguments**
   - Example: ls …etc
   - Details: The shell must block until the command completes and, if the return code is abnormal, print out a message to that effect.
   - Concepts: Forking a child process, waiting for it to complete and synchronous execution.
   - System calls: `fork()`, `execvp()`, `exit()`, `wait()`
3. **A command with arguments**
   - Example: ls –l, cp source destination, rm filename.
   - Details: Argument 0 is the name of the command.
   - Concepts: Command-line parameters
4. **A command, with or without arguments, executed in the background using &.**

   - Example: firefox &
   - Details: In this case, The shell must execute the command and return immediately, not blocking until the command finishes.
   - Concepts: Background execution, signals, signal handlers, processes and asynchronous execution.

   Notice how Firefox, Calculator and Gedit are child processes to the SimpleShell process

   ### To process the user command, do the following:

   1.  command shell should take the user command and its parameter(s), i.e., “ls” and “–l” in this example, and convert them into C strings. (Recall that a C string terminates with a null string, i.e., \0.)
   2. The command shell should create a child process via `fork()`.
   3. The child process passes the C strings—the command and parameter(s)—to `execvp()`.
   4. The parent process, i.e., the command shell, should wait, via `wait()`, for the child process to finish.
   5. The command shell gets the next command and repeats the above steps. The command shell terminates itself when the user types exit.

   In case a user wants to execute the command in background (i.e. as a background process), he/she writes & at the end of the command. For example, a user command can be:

   ```bash
   Shell > firefox &
   ```
