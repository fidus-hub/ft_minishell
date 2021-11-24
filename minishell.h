/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:50:44 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 00:50:45 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include  <errno.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ONE 1
# define TWO 2
# define ONEREV 3
# define TWOREV 4

typedef struct s_toke
{
	int	i;
	int	j;
	int	k;
}t_toke;

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*suivant;
	struct s_env	*preced;
}t_env;

typedef struct s_file
{
	char			*filename;
	int				type;
	struct s_file	*next;
	struct s_file	*prec;
}t_file;

typedef struct s_cmds
{
	char			**args;
	char			*path;
	char			*cmd;
	struct s_file	*file_h;
	struct s_file	*file_f;
	struct s_cmds	*next;
	struct s_cmds	*prec;
}t_cmds;

typedef struct s_headers
{
	struct s_env	*env_h;
	struct s_env	*env_f;
	struct s_cmds	*cmd_h;
	struct s_cmds	*cmd_f;
}t_headers;

int		g_pids;

typedef enum e_norm
{
	GETEXIT,
	SETEXIT,
	GETPID,
	SETPID
}t_norm;

int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strdup_free(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strstr(char *src, char *tofind);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin_dollar(char *s1, char *s2, int i);
char	*ft_strjoin_red(char *s1, char *s2, int i);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_free2(char *s1, char *s2);
char	*ft_strjoin_dollarfree(char *s1, char *s2, int i);
void	envi(char **env, t_headers *header);
void	ft_delbottom(t_headers *head);
void	ft_addbottom(t_headers *head, char *var, char *val);
int		check_error(char *line);
int		nb_of_quotes(char *line);
int		check_error_pipes(char *line);
int		check_error_redirections(char *line);
char	**ft_toke(char const *s, char c);
char	**ft_flex(char const *s, char c);
char	**split_pipe(char *line, t_headers *header);
void	*ft_free(char **p);
void	save_cmd(t_headers *header, char **str);
void	ft_addbotfile(t_cmds *head, char *val, int type);
void	ft_delbotfile(t_cmds *head);
int		checkredirection_cmd(t_cmds	*find_redirection);
void	fill_cmd(t_headers *header, char	**str);
void	ft_delbotcmd(t_headers *head);
int		execute(t_headers *header);
void	laysameh(int *r, int *i);
int		__get_var(t_norm op, int value);
#endif