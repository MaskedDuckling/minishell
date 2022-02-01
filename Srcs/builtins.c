/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:50:11 by maskedduck        #+#    #+#             */
/*   Updated: 2022/02/01 20:01:47 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	printf("%s\n", buffer);
	return (1);
}

int main()
{
	ft_pwd();
}