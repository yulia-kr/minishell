/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_call_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:34:11 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 14:34:11 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ms_sys_call_parent(t_parser_var *v_p)
{
	int	status;

	status = 0;
	status = ft_ms_sys_export(v_p->cmd_tree, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_unset(v_p->cmd_tree, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_chdir(v_p->cmd_tree, v_p);
	if (status <= 0)
		return (status);
	status = ft_ms_sys_exit(v_p->cmd_tree, v_p);
	if (status <= 0)
		return (status);
	return (status);
}
