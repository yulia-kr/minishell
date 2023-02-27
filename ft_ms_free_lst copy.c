/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_free_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:14:42 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/12 13:14:42 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lst_del_node(void *adr)
{
	if (adr != NULL || adr != 0)
	{
		if (*((t_cmd *)adr) == EXEC)
		{
			free((t_cmd_exec *)adr);
		}
		else if (*((t_cmd *)adr) == REDIR)
		{
			free((t_cmd_redir *)adr);
		}
		else if (*((t_cmd *)adr) == PIPE)
		{
			free((t_cmd_pipe *)adr);
		}
		else
			free(adr);
		adr = NULL;
	}
}

/**
 * @brief   This function releases the memory allocated for the env_list and
 *          its ptr arrays.
 * todo     Parent process: This function is required at all exit.
 * todo     Child process: This function is required at exit before execve call
 * 
 * @param env_lst 
 * @param v_p 
 */
void	ft_ms_free_lst(t_list **env_lst)
{
	if (*env_lst == NULL)
		return ;
	ft_lstclear(env_lst, ft_lst_del_node);
}
