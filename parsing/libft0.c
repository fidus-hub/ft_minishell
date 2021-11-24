/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:02:56 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:02:57 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	unsigned char		*ss1;
	unsigned char		*ss2;

	i = 0;
	ss2 = (unsigned char *)s2;
	ss1 = (unsigned char *)s1;
	while (ss1[i] == ss2[i] && s1[i] && s2[i])
		i++;
	return (ss1[i] - ss2[i]);
}

char	*ft_strdup(const char *s)
{
	size_t	k;
	char	*new;
	size_t	i;

	i = 0;
	k = 0;
	while (s && s[k] != '\0')
		k++;
	new = (char *)malloc((k + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			i;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && ss1[i] == ss2[i])
		i++;
	return (ss1[i] - ss2[i]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	char				*res;
	const char			*acpy;

	i = 0;
	res = dest;
	acpy = src;
	if (res == NULL && acpy == NULL)
		return (0);
	if (ft_memcmp(res, acpy, n) != 0)
	{
		while (i < n)
		{
			res[i] = acpy[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	char		*ssrc;

	dst = (char *)dest;
	ssrc = (char *)src;
	if (dest == NULL && src == NULL)
		return (0);
	if (ssrc > dst)
		ft_memcpy(dst, ssrc, n);
	else
	{
		dst = (char *)dest + (n - 1);
		ssrc = (char *)src + (n - 1);
		while (n > 0)
		{
			*(dst--) = *(ssrc--);
			n--;
		}
	}
	return (dest);
}
