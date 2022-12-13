/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_handle_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:19:15 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/12 22:47:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function checks if the "$?" is present with a given cmd.
 *          If present, it is replaced with the status of the last executed
 * 			program.
 * 
 * @param argv_s 
 * @param v_p 
 */
void	ft_ms_handle_status(char **argn, char **p, int *f, t_parser_var *v_p)
{
	char	*txt_s;
	char	*txt_e;
	char	*d;

	d = *p;
	txt_s = ft_itoa(v_p->status);
	txt_e = txt_s + ft_strlen(txt_s);
	ft_ms_append_str_to_str(argn, &txt_s, &txt_e);
	ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)txt_s));
	if (*(d + 1 + 1) == 34)
	{
		*f = 0;
		*p = d + 2;
	}
	else
	{
		*p = d + 1;
	}
	v_p->str_s = *p + 1;
	v_p->tk_s = *p + 1;
}
