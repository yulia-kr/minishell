/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_open_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:29:27 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 10:22:53 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function ensures that only three file descriptors are open.
 *          This include the fd (stdin, stdout, stderr)
 *      
 * 
 */
int	ft_ms_sys_open_fd(void)
{
	int	fd;

	while (1)
	{
		fd = open("console", O_RDWR | O_CREAT, S_IRWXU);
		if (fd < 0)
		{
			perror("Error! \nopen");
			return (-1);
		}
		else if (fd > 3)
		{
			close(fd);
			break ;
		}
	}
	return (0);
}
