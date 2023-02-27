/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_add_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:29:04 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/17 11:29:04 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_env_add_var(t_parser_var *v, char *var)
{
	char	*var_n;
	size_t	len_var;

	var_n = NULL;
	len_var = ft_strlen(var);
	var_n = ft_calloc((len_var + 1), SZ_CHAR);
	ft_memcpy((void *)var_n, (void *)var, len_var);
	ft_lstadd_back(&(v->env_lst), ft_lstnew((void *)var_n));
	ft_ms_env_upd(v);
}
