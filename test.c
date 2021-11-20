#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// typedef	struct	s_file
// {
// 	char	*filename;
// 	int		type;
// 	struct	t_file	*next; 
// }t_file;

// typedef struct s_cmds
// {
// 	// redirections;
// 	char	**args;
// 	int		d_q;
// 	int		s_q;
// 	char	*cmd;
// 	struct	t_file	*file;
// 	struct	s_cmds	*next;
// 	struct	s_cmds	*prec;
// }t_cmds;

// typedef struct s_headers
// {
// 	// struct s_env	*env_h;
// 	// struct s_env	*env_f;
// 	struct s_cmds	*cmd_h;
// 	struct s_cmds	*cmd_f;
// }t_headers;

// char	*ft_strdup(char *str)
// {
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	res = malloc(sizeof(char) * i + 1);
// 	i = 0;
// 	while (str[i])
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// static	int	ft_mots(char const *s, char c)
// {
// 	int			i;
// 	int			k;
// 	int			p;
//     int         d_q;
//     int         s_q;

//     d_q = 0;
//     s_q = 0;
// 	i = 0;
// 	k = 0;
// 	p = 1;
// 	if (*s)
// 	{
// 		while (s[i])
// 		{
// 			if (s[i] == '"')
// 			{
// 				i++;
// 				while (s[i] && s[i] != '"')
// 					i++;
// 			}
// 			if (s[i] == c)
// 				p = 1;
// 			else if (p == 1 && !d_q)
// 			{
// 				p = 0;
// 				k++;
// 			}
// 			i++;
// 		}
// 	}
//     return (k);
// }

// static void	*ft_freee(char **p)
// {
// 	int	i;

// 	i = 0;
// 	while (p[i])
// 	{
// 		free(p[i]);
// 		i++;
// 	}
// 	free(p);
// 	return (0);
// }

// static int	ft_alpha(char const *s, char c, int i)
// {
// 	int	r;

// 	r = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		if (s[i] == '"')
// 		{
// 			i++;
// 			while (s[i] != '"')
// 			{
// 				r++;
// 				i++;
// 			}
// 			i++;
// 		}
// 		else
// 		{
// 			r++;
// 			i++;
// 		}
// 	}
// 	return (r);
// }

//fork
// static char	**ft_remp(char **p, char const *s, char c, int mots)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	j = 0;
// 	while (s[i] && mots > j)
// 	{
// 		k = 0;
// 		while (s[i] == c)
// 			s++;
// 		p[j] = malloc(sizeof(char) * ft_alpha(s, c, i) + 1);
// 		if (!p[j])
// 			return (ft_freee(p));
// 		while (s[i] && s[i] != c)
//         {
//             if (s[i] == '"')
//             {
//                 i++;
//                 while (s[i] != '"')
//                 {
// 		        	p[j][k] = s[i];
// 					k++;
// 					i++;
//                 }
//                 i++;
//             }
// 			else
// 				p[j][k++] = s[i++];
//         }
// 		p[j][k] = '\0';
// 		j++;
// 	}
// 	p[j] = 0;
// 	return (p);
// }

// void	ft_addbotcmd(t_headers *head, char *val)
// {
// 	t_cmds	*stack;
// 	t_cmds	*to_add;

// 	to_add = malloc(sizeof(t_cmds));
// 	if (!to_add)
// 		exit(0);
// 	if (head->cmd_h == NULL)
// 	{
// 		to_add->cmd = ft_strdup(val);
// 		// to_add->val = ft_strdup(val);
// 		to_add->next = NULL;
// 		to_add->prec = NULL;
// 		head->cmd_f = to_add;
// 		head->cmd_h = to_add;
// 	}
// 	else
// 	{
// 		stack = head->cmd_f;
// 		// to_add->var = ft_strdup(var);
// 		to_add->cmd = ft_strdup(val);
// 		to_add->prec = stack;
// 		to_add->next = NULL;
// 		stack->next = to_add;
// 		head->cmd_f = to_add;
// 	}
// }

// char	**ft_flex(char const *s, char c)
// {
// 	char	**p;
// 	int		mots;

// 	if (s == NULL)
// 		return (0);
// 	mots = ft_mots(s, c);
// 	p = malloc(sizeof(char *) * (mots + 1));
// 	if (!p)
// 		return (0);
// 	return (ft_remp(p, s, c, mots));
// }

// int	main(int ac, char **av)
// {
//     (void)ac;
// 	t_headers *head;
// 	t_cmds		*test;
//     // char    **test;
//     int     i = 0;

// 	head->cmd_h = NULL;
// 	ft_addbotcmd(head, "\" test| \" | ls");
// 	ft_addbotcmd(head, "\" test| \"");
// 	// test->cmd = "\" test| \" | ls";
// 	test = head->cmd_h;
// 	while (test)
// 	{
// 		test->args = ft_flex(test->cmd, ' ');
// 		test = test->next;
// 	}
// 	test = head->cmd_h;
// 	while (test)
// 	{
// 		int i = 0;
// 		while (test->args[i])
//     	{
//        		printf("%s\n", test->args[i]);
//         	i++;
//     	}
// 		printf("---------------\n");
// 		test = test->next;
// 	}
//     // while (test[i])
//     // {
//     //     printf("%s\n", test[i]);
//     //     i++;
//     // }
//     ft_freee(test->args);
//     // var = "test | \"test|ls\"";
// 	// var = getenv("SHELL");
// 	// printf("la valeur de PATH est %s\n", var);
//     // printf("%d\n%s\n",ft_mots(var, '|'), var);
//     // printf("%d\n%s\n",ft_mots(var, '|'), var);
//     // printf("%d\n%s\n",ft_alpha(var, '|', 0), var);

    
// }


// int	ft_memcmp(const void *s1, const void *s2, size_t n)
// {
// 	unsigned char	*ss1;
// 	unsigned char	*ss2;
// 	size_t			i;

// 	ss1 = (unsigned char *)s1;
// 	ss2 = (unsigned char *)s2;
// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (i < n - 1 && ss1[i] == ss2[i])
// 		i++;
// 	return (ss1[i] - ss2[i]);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t				i;
// 	char				*res;
// 	const char			*acpy;

// 	i = 0;
// 	res = dest;
// 	acpy = src;
// 	if (res == NULL && acpy == NULL)
// 		return (0);
// 	if (ft_memcmp(res, acpy, n) != 0)
// 	{
// 		while (i < n)
// 		{
// 			res[i] = acpy[i];
// 			i++;
// 		}
// 	}
// 	return (dest);
// }

// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	char		*dst;
// 	char		*ssrc;

// 	dst = (char *)dest;
// 	ssrc = (char *)src;
// 	if (dest == NULL && src == NULL)
// 		return (0);
// 	if (ssrc > dst)
// 		ft_memcpy(dst, ssrc, n);
// 	else
// 	{
// 		dst = (char *)dest + (n - 1);
// 		ssrc = (char *)src + (n - 1);
// 		while (n > 0)
// 		{
// 			*(dst--) = *(ssrc--);
// 			n--;
// 		}
// 	}
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	unsigned int		ss1;
// 	unsigned int		ss2;
// 	char				*new;

// 	ss1 = 0;
// 	ss2 = 0;
// 	if (s1 == NULL || s2 == NULL)
// 		return (0);
// 	while (s1[ss1] != '$')
// 		ss1++;
// 	while (s2[ss2] != '\0')
// 		ss2++;
// 	if (!(new = (char *)malloc((ss1 + ss2 + 1) * sizeof(char))))
// 		return (0);
// 	ft_memmove(new, s1, ss1);
// 	ft_memmove(new + ss1, s2, ss2);
// 	new[ss1 + ss2] = '\0';
// 	return (new);
// }

// char	*ft_strstr(char *src, char *tofind)
// {
// 	char	*deb;
// 	char	*fin;


// 	// printf("%s/n", src);
// 	if (*tofind == '\0')
// 		return (char*)src;
// 	while (*src != '\0')
// 	{
// 		deb = src;
// 		fin = tofind;
// 		while (*src && *fin && *src == *fin)
// 		{
// 			src++;
// 			fin++;
// 		}
// 		if (*fin == '\0')
// 			return ((char *)src);
// 		src = deb + 1;
// 	}
// 	return (0);
// }

// char	*ft_strdup(const char *s)
// {
// 	size_t	k;
// 	char	*new;
// 	size_t	i;

// 	i = 0;
// 	k = 0;
// 	while (s && s[k] != '\0')
// 		k++;
//     new = (char *)malloc((k + 1) * sizeof(char));
// 	if (!new)
// 		return (0);
// 	while (s[i] != '\0')
// 	{
// 		new[i] = s[i];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// char	*ft_strdup(char *str)
// {
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	res = malloc(sizeof(char) * i + 1);
// 	i = 0;
// 	while (str[i])
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// int main()
// {
// 	char *s;
// 	char *str = "hello $world $pwd";
// 	char *ll = "$world";
// 	// str = ft_strjoin(str, ll);
// 	// int k = 0;
// 	// while (str[k]!='$')
// 	// 	k++;
// 	// s = to_find(str, k);
// 	//ft_strdup(NULL);
// 	ft_strdup(NULL);
// 	// free(str);
// 	// system("leaks a.out");
// }


// typedef struct s_stack
// {
// 	char				*name;
// 	int					age;
// 	struct s_stack	*next;
// 	// struct s_stack	*preced;
// }t_stack;

// typedef struct s_list
// {
// 	struct s_stack	*header;
// 	// struct s_stack	*footer;
// }t_list;

// void	ft_depiler(t_list *head)
// {
// 	t_stack	*to_delete;
// 	t_stack	*a;

// 	if (head != NULL && head->header != NULL)
// 	{
// 		to_delete = head->header;
// 		if (!to_delete->next)
// 		{
// 			free(to_delete);
// 			head->header = NULL;
// 			// head->footer = NULL;
// 			to_delete = NULL;
// 		}
// 		else
// 		{
// 			a = to_delete->next;
// 			head->header = a;
// 			// a->preced = NULL;
// 			free(to_delete);
// 			to_delete = NULL;
// 		}
// 	}
// }

// void	ft_remplir(t_list *head, char *name, int age)
// {
// 	t_stack	*a;
// 	t_stack	*to_add;

// 	to_add = malloc(sizeof(t_stack));
// 	// if (!to_add)
// 	// 	ft_exit();
// 	if (head->header == NULL)
// 	{
// 		to_add->age = age;
// 		to_add->name = strdup(name);
// 		to_add->next = NULL;
// 		// to_add->preced = NULL;
// 		// head->footer = to_add;
// 		head->header = to_add;
// 	}
// 	else
// 	{
// 		a = head->header;
// 		to_add->age = age;
// 		to_add->name = strdup(name);
// 		to_add->next = a;
// 		// to_add->preced = NULL;
// 		// a->preced = to_add;
// 		head->header = to_add;
// 	}
// }

// int main()
// {
// 	t_stack *o;
// 	t_list	*head;
// 	head = malloc(sizeof(t_list));

// 	head->header = NULL;
// 	ft_remplir(head, "fahd", 20);
// 	ft_remplir(head, "yassine", 21);
// 	ft_remplir(head, "karim", 35);
// 	o = head->header;
// 	while (o)
// 	{
// 		printf("name:%s age:%d\n",o->name, o->age);
// 		o = o->next;
// 	}
	
// 	// o->age=2; 
// }