/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_handle_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:19:15 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:50:34 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function checks if the only word in the user cmd is "$?".
 *          if true, the status of the last foreground executed is printed.
 *          After printing, the child process exit.
 *          If the status is not 0, then the function exits with 1 to retain
 *          the status else, it exit with 0.
 * 
 * @param argv_s 
 * @param v_p 
 */
static void	ft_handle_status_cmd(char **argv_s, t_parser_var *v_p)
{
	if (argv_s[0] != 0 && argv_s[1] == 0)
	{
		if (ft_strncmp(argv_s[0], "$?", 2) == 0)
		{
			ft_printf("%d\n", v_p->status);
			if (v_p->status > 0)
				exit(1);
			else
				exit(0);
		}
	}
}

void	ft_ms_handle_status(char **argv_s, t_parser_var *v_p)
{
	char	*str_status;
	int		idx;
	int		flag_set;

	idx = 0;
	flag_set = 0;
	ft_handle_status_cmd(argv_s, v_p);
	str_status = ft_itoa(v_p->status);
	while (argv_s[idx] != 0)
	{
		if (ft_strncmp(argv_s[idx], "$?", 2) == 0)
		{
			argv_s[idx] = str_status;
			flag_set++;
		}
		idx++;
	}
	if (flag_set == 0)
		free(str_status);
}
