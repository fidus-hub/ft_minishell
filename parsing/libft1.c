/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:02 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:03:03 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strstr(char *src, char *tofind)
{
	char	*deb;
	char	*fin;

	if (*tofind == '\0')
		return ((char *)src);
	while (*src != '\0')
	{
		deb = src;
		fin = tofind;
		while (*src && *fin && *src == *fin)
		{
			src++;
			fin++;
		}
		if (*fin == '\0')
			return ((char *)src);
		src = deb + 1;
	}
	return (0);
}

char	*ft_strdup_free(char *s1)
{
	char	*ret;

	ret = ft_strdup(s1);
	free(s1);
	s1 = NULL;
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	str;

	str = (unsigned char)c;
	i = 0;
	while (s[i] != str)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)s + i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
