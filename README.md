### 🖥️ Minishell  
📝 **Presentation**  

Minishell is a project aimed at recreating a **basic command-line interpreter**, inspired by **Bash**.  
This project explores **process management, inter-process communication, and file & descriptor manipulation in C**.  

The objective is to implement a **shell** capable of executing Unix commands while handling advanced features such as **pipes, redirections, and signals**.  

🛠️ **Features**  

✅ **Mandatory Features:**  
- Display a prompt (`minishell$`) waiting for user input.  
- Command history management using `readline()`.  
- Execute commands via `execve()`.  
- Handle both **relative and absolute paths** (`PATH`).  
- **File redirections:**  
  - `<` : Input redirection.  
  - `>` : Output redirection.  
  - `<<` : **Heredoc** with a delimiter.  
  - `>>` : Append mode output redirection.  
- **Pipe management (`|`)** to chain multiple commands.  
- **Environment variable management (`$VAR`).**  
- Expand **`$?`** to retrieve the exit code of the last command.  
- **Signal handling** (`ctrl-C`, `ctrl-D`, `ctrl-\`):  
  - `ctrl-C` displays a new prompt.  
  - `ctrl-D` closes the shell.  
  - `ctrl-\` does nothing.  
- Implementation of the following **built-in commands:**  
  - `echo` (with `-n` option).  
  - `cd` (with absolute or relative path).  
  - `pwd` (prints the current directory).  
  - `export` (add/modify environment variables).  
  - `unset` (remove environment variables).  
  - `env` (display environment variables).  
  - `exit` (exit the shell with a status code).  

🎯 **Bonus Features (if implemented):**  
- Logical operators (`&&`, `||`) with **priority management (`()`)**.  
- **Wildcard (`*`) support** to list matching files in the current directory.  

📌 **Technologies Used**  

- **C** (Norminette-compliant)  
- **Process management** (`fork()`, `execve()`, `wait()`, `signal()`)  
- **File redirections** (`dup2()`)  
- **Pipes** (`pipe()`)  
- **Environment variable manipulation** (`getenv()`, `setenv()`)  
- **User input handling** (`readline()`)  
