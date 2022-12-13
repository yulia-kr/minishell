/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_parse_usr_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:40:21 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 16:40:21 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ms_parse_usr_cmd(t_parser_var *v_p)
{
	ft_parser_get_max_args(v_p);
	add_history(v_p->usr_cmd_inp);
	v_p->cmd_tree = ft_parser_parse(v_p->usr_cmd_inp, v_p);
	if (*(v_p->cmd_tree) == P_ERROR)
	{
		free(v_p->cmd_tree);
		v_p->cmd_tree = NULL;
		ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
		return (-1);
	}
	return (0);
}
