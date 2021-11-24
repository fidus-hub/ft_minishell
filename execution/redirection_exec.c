/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:48 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:14:49 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	printfile_error(char *str, char *s, int i)
{
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, s, ft_strlen(s));
}

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
		if (*out == -1)
		{
			printfile_error(file_h->filename, ": is a directory\n", 0);
			__get_var(SETEXIT, -1);
		}
	}
	if (file_h->filename && (file_h->type == 3 || file_h->type == 4))
	{
		if (*in != STDIN_FILENO)
			close(*in);
		*in = open(file_h->filename, O_RDONLY, 0644);
		if (*in == -1)
		{
			printfile_error(file_h->filename, ":No such file or directory\n", 0);
			__get_var(SETEXIT, -1);
		}
	}
}

void	redirection(t_cmds *cmd_h, t_exec *exec)
{
	t_file	*nfile;
	int		in;
	int		out;

	nfile = cmd_h->file_h;
	in = 0;
	out = 1;
	while (nfile != NULL && __get_var(GETEXIT, 2) != -1)
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
