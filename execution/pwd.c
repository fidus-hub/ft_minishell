/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:44 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 00:49:45 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	pwd(t_cmds *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	__get_var(SETEXIT, 0);
}
