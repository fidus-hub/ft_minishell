# include "execution.h"

void	redirection_inside_loop(int *in, int *out, t_file *file_h) 
{
	if (file_h->filename && (file_h->type == 1 || file_h->type == 2))
	{
		if (*out != STDOUT_FILENO)
			close(*out);
		if (file_h->type == 1)
			*out = open(file_h->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file_h->type == 2)
			*out = open(file_h->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (file_h->filename && (file_h->type == 3 || file_h->type == 4))
	{
		if (*in != STDIN_FILENO)
			close(*in);
		*in = open(file_h->filename, O_RDONLY, 0644);
		if (*in == -1)
		{
			printf("bash: %s: No such file or directory\n", file_h->filename);
			__get_var(SETEXIT, 1);
		}
	}
}

void	redirection(t_cmds *cmd_h, t_exec *exec)
{
	t_file *nfile;
	nfile = cmd_h->file_h;
	int in = 0;
	int out = 1;
	while (nfile != NULL)
	{
		redirection_inside_loop(&in, &out, nfile);
		nfile = nfile->next;
	}
	if (in > 2)
	{
		dup2(in, 0);
		close(in);
	}
	if (out > 2)
	{
		dup2(out, 1);
		close(out);
	}
}
