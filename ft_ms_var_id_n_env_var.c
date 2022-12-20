/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_var_id_n_env_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:10:04 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 13:10:04 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This functions checks if the variable id (name) already exist 
 * 			within the env linked list.
 *          If the var id is found within the list then the value is replaced
 * 			 and return 0 else -1 is returned.
 * 
 * @param var_id    The variable id must end with "=" character. eg. WEEDAY=
 * @param var       This contains both the var id and var value. eg. WKDAY=MON
 * @param v_p 
 * @return int 
 */
int	ft_ms_var_id_n_env_var(char **var_id, char *var, t_parser_var *v_p)
{
	t_list	*head;
	char	*var_n;

	head = v_p->env_lst;
	var_n = NULL;
	while (head != NULL)
	{
		if (ft_strnstr((char *)(head->content), *var_id, ft_strlen(*var_id)))
		{
			free(head->content);
			var_n = ft_calloc((ft_strlen(var) + 1), SZ_CHAR);
			ft_memcpy((void *)var_n, (void *)var, ft_strlen(var));
			head->content = (void *)var_n;
			ft_ms_env_upd(v_p);
			v_p->status = STATUS_OK;
			//ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
			return (0);
		}
		head = head->next;
	}
	return (-1);
}
