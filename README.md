Certainly! Below is the regenerated `README.md` content for easy copy-pasting into your repository. Just copy the text below and paste it into your `README.md` file.

---

```markdown
# Pipex

## Table of Contents
1. [Introduction](#introduction)
2. [What is Pipex?](#what-is-pipex)
3. [Features](#features)
4. [How It Works](#how-it-works)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Example](#example)
8. [Testing](#testing)
9. [Contributing](#contributing)
10. [License](#license)

---

## Introduction
`Pipex` is a 42 school project that simulates the behavior of Unix pipes (`|`) in a shell. It allows you to connect multiple commands together, passing the output of one command as the input to the next, similar to how pipes work in a Unix shell.

This project is written in C and demonstrates the use of system calls like `fork`, `pipe`, `dup2`, `execve`, and `waitpid` to create a custom pipe mechanism.

---

## What is Pipex?
`Pipex` is a program that takes an input file, a series of commands, and an output file. It executes the commands in sequence, passing the output of one command as the input to the next, and finally writes the result to the output file.

For example:
```bash
./pipex infile "cmd1" "cmd2" outfile
```
This is equivalent to the shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

---

## Features
- Supports multiple commands (bonus).
- Handles input and output redirection.
- Simulates Unix pipe behavior.
- Supports here_doc (bonus).
- Error handling for invalid commands, files, or system calls.
- Memory leak-free and compliant with 42's strict coding standards.

---

## How It Works
1. **Input Redirection:**
   - The program reads from the input file (`infile`) or standard input (if using `here_doc`).

2. **Command Execution:**
   - Each command is executed in a child process.
   - The output of one command is passed to the next command using a pipe.

3. **Output Redirection:**
   - The final output is written to the output file (`outfile`).

4. **Error Handling:**
   - The program handles errors such as invalid commands, missing files, or system call failures.

---

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/pipex.git
   ```
2. Navigate to the project directory:
   ```bash
   cd pipex
   ```
3. Compile the program:
   ```bash
   make
   ```
   This will generate an executable named `pipex`.

---

## Usage
### Basic Usage
```bash
./pipex infile "cmd1" "cmd2" outfile
```
- `infile`: The input file.
- `cmd1`, `cmd2`: Commands to execute.
- `outfile`: The output file.

### Here_doc (Bonus)
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
- `LIMITER`: The delimiter to stop reading input.
- `cmd1`, `cmd2`: Commands to execute.
- `outfile`: The output file.

---

## Example
### Basic Example
```bash
./pipex infile "ls -l" "wc -l" outfile
```
This is equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

### Here_doc Example
```bash
./pipex here_doc END "grep hello" "wc -l" outfile
```
This will:
1. Read input from the terminal until the delimiter `END` is entered.
2. Pass the input to `grep hello`.
3. Count the number of lines containing "hello" using `wc -l`.
4. Write the result to `outfile`.

---

## Testing
You can test the program using various commands and input/output files. Here are some examples:

1. **Basic Test:**
   ```bash
   ./pipex infile "cat" "wc -l" outfile
   ```

2. **Here_doc Test:**
   ```bash
   ./pipex here_doc EOF "grep pipex" "wc -l" outfile
   ```

3. **Error Handling Test:**
   - Test with invalid commands:
     ```bash
     ./pipex infile "invalid_cmd" "wc -l" outfile
     ```
   - Test with missing input file:
     ```bash
     ./pipex missing_file "cat" "wc -l" outfile
     ```

---

## Contributing
Contributions are welcome! If you find any issues or have suggestions for improvement, feel free to open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature
   ```
5. Open a pull request.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Enjoy using `pipex`! If you have any questions, feel free to reach out.
```

---

