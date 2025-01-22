#include "pipex_bonus.h"

void exec_cmd(char *cmd, char **env)
{
    char **full_cmd;
    char *path;

    full_cmd = ft_split(cmd, ' ');
    path = get_path(full_cmd[0], env);
    if (execve(path, full_cmd, env) == -1)
    {
        perror("exec error");
        free_paths(full_cmd);
        exit(1);
    }
}

void child_process(char *cmd, char **env, int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO)
    {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    exec_cmd(cmd, env);
}

void pipex(int ac, char **av, char **env)
{
    int pipefd[2];
    int input_fd;
    int i;
    pid_t pid;

    input_fd = open(av[1], O_RDONLY);
    if (input_fd == -1)
    {
        perror("Input file error");
        exit(1);
    }

    for (i = 2; i < ac - 2; i++)
    {
        if (pipe(pipefd) == -1)
        {
            perror("Pipe error");
            exit(1);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("Fork error");
            exit(1);
        }
        if (pid == 0)
        {
            close(pipefd[0]);
            child_process(av[i], env, input_fd, pipefd[1]);
        }
        else
        {
            close(pipefd[1]);
            close(input_fd);
            input_fd = pipefd[0];
        }
    }
	int output_fd = -1;
    if(access(av[1],F_OK) == 0)
    	output_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1)
    {
        perror("Output file error");
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Fork error");
        exit(1);
    }
    if (pid == 0)
    {
        child_process(av[i], env, input_fd, output_fd);
    }
    else
    {
        close(input_fd);
        close(output_fd);
        waitpid(pid, NULL, 0);
    }
}

int main(int ac, char **av, char **env)
{
    if (ac < 5)
    {
        ft_putstr_fd("Bad arguments:\n./pipex infile <cmd1> ... <cmdn> outfile\n", 2);
        exit(1);
    }
    pipex(ac, av, env);
    return 0;
}
