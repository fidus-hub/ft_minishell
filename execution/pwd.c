/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:26:50 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/13 22:26:54 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "execution.h"

void	pwd(t_cmds *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	__get_var(SETEXIT,0);
}
