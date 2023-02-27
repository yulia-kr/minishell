/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_debug_print_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:35:28 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:27:23 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_debug_print_cmd(char *usr_cmd)
{
	char	*s;

	if (usr_cmd == NULL || usr_cmd == 0)
		return ;
	s = usr_cmd;
	ft_printf("\n");
	while (*s != '\0')
	{
		ft_printf("%p -> %c\n", s, *s);
		s++;
	}
}
