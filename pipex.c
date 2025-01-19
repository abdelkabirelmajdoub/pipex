#include "pipex.h"

void exe(const char *cmd, int in, int out)
{
    if (dup2(in, STDIN_FILENO) == -1)
    {
        perror("dup2 in");
        exit(EXIT_FAILURE);
    }
    if (dup2(out, STDOUT_FILENO) == -1)
    {
        perror("dup2 out");
        exit(EXIT_FAILURE);
    }
    char *shell = "/bin/zsh";
    char *args[] = {shell, "-c", (char *)cmd, NULL};
    if (execve(shell, args, NULL) == -1)
    {
        perror("execution error");
        exit(EXIT_FAILURE);
    }
}

void	cmd1(int pipefd[2], int infile, pid_t pid1, char **av)
{
	if (pid1 == 0)
    {

        close(pipefd[0]);
        if (dup2(infile, STDIN_FILENO) == -1)
        {
            perror("dup2 infile");
            exit(EXIT_FAILURE);
        }
        close(infile); 
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 pipe write end");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]); 
        exe(av[2], STDIN_FILENO, STDOUT_FILENO);
    }
    else if (pid1 < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
}

void	cmd2(int pipefd[2], int outfile, pid_t pid2, char **av)
{
	 if (pid2 == 0)
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 pipe read end");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]); 
        if (dup2(outfile, STDOUT_FILENO) == -1)
        {
            perror("dup2 outfile");
            exit(EXIT_FAILURE);
        }
        close(outfile); 
        exe(av[3], STDIN_FILENO, STDOUT_FILENO);
    }
    else if (pid2 < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
}
void closefile(int pipefd[2], int infile, int outfile, pid_t pid1, pid_t pid2)
{
	close(pipefd[0]); 
    close(pipefd[1]);
    close(infile);
    close(outfile);

    waitpid(pid1, NULL, 0); 
    waitpid(pid2, NULL, 0);
}
int main(int ac, char **av)
{
    int		pipefd[2];
    int		infile;
    int		outfile;
	pid_t	pid1;
	pid_t	pid2;

    if (ac != 5)
    {
		write(STDERR_FILENO, "Error: Bad arguments\nUsage: ./pipex infile cmd1 cmd2 outfile\n",61);
        exit(EXIT_FAILURE);
    }
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipe(pipefd) == -1)
    {
        perror("pipe error");
        return (EXIT_FAILURE);
    }
    if (infile == -1)
    {
        perror("Error opening input file");
        return (EXIT_FAILURE);
    }
    if (outfile == -1)
    {
        perror("Error opening output file");
        close(infile);
        return (EXIT_FAILURE);
    }
    pid1 = fork();
	cmd1(pipefd, infile, pid1, av);
    pid2 = fork();
	cmd2(pipefd, outfile, pid2, av);
	closefile(pipefd, infile, outfile, pid1, pid2);
    return EXIT_SUCCESS;
}
