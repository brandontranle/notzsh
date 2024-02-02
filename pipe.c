#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int argsTotal = argc - 1;

	if (argsTotal == 0)
	{
		fprintf(stderr, "notzsh: Invalid Arguments\n");
		exit(errno);
	}

	int pipe_ends[(argsTotal - 1) * 2];

	if (pipe(pipe_ends) == -1)
	{
		fprintf(stderr, "notzsh: Pipe failed\n");
		exit(errno);
	}

	for (int arg_val = 0; arg_val < argsTotal - 1; arg_val++)
	{
		pipe(pipe_ends + (arg_val * 2));
	}

	pid_t processes[argsTotal + 1];

	for (int curr = 1; curr <= argsTotal; curr++)
	{
		int write_to = (curr * 2) - 1;
		int read_from = (curr > 1) ? (curr - 1) * 2 - 2 : 0;

		pid_t pid = fork();
		processes[curr] = pid;

		if (pid == 0)
		{
			if (curr == argsTotal)
			{
				dup2(pipe_ends[read_from], STDIN_FILENO);
			}
			else if (curr == 1)
			{
				dup2(pipe_ends[write_to], STDOUT_FILENO);
			}
			else
			{
				dup2(pipe_ends[read_from], STDIN_FILENO);
				dup2(pipe_ends[write_to], STDOUT_FILENO);
			}

			for (int i = 0; i < (argsTotal - 1) * 2; i++)
			{
				close(pipe_ends[i]);
			}

			execlp(argv[curr], argv[curr], NULL);

			if (errno)
			{
				fprintf(stderr, "notzsh: command not found: %s\n", argv[curr]);
				exit(errno);
			}
		}
		else if (pid > 0)
		{
			if (curr == argsTotal && argsTotal > 1)
			{
				close(pipe_ends[read_from]);
				int status = 0;
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					// fprintf(stderr, "%s: Exit status: %d\n", argv[0], WEXITSTATUS(status));
					exit(WEXITSTATUS(status));
				}
			}

			if (argsTotal == 1)
			{
				int status = 0;
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					// fprintf(stderr, "%s: Exit status: %d\n", argv[0], WEXITSTATUS(status));
					exit(WEXITSTATUS(status));
				}
				break;
			}

			if (curr == 1)
			{
				close(pipe_ends[write_to]);
			}
			else
			{
				close(pipe_ends[read_from]);
				close(pipe_ends[write_to]);
			}
		}
	}

	for (int i = 1; i <= argsTotal; i++)
	{
		int status = 0;
		waitpid(processes[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			// fprintf(stderr, "%s: Exit status: %d\n", argv[0], WEXITSTATUS(status));
			exit(WEXITSTATUS(status));
		}
	}

	return 0;
}
