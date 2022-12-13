/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_handle_env_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:38:38 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 19:38:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_ptrs(char **p, int len_var_id, int *f, t_parser_var *v_p)
{
	free(v_p->tk_s);
	if (*(*p + len_var_id + 1) == 34)
	{
		*f = 0;
		*p = *p + len_var_id + 1;
	}
	else
	{
		*p = *p + len_var_id;
	}
	v_p->str_s = *p + 1;
	v_p->tk_s = *p + 1;
}

static int	ft_on_quote_or_dollar(char **p, int len_var_id, t_parser_var *v_p)
{
	int	status;

	status = 1;
	if (*(*p + len_var_id) == 34)
	{
		*p = *p + len_var_id - 1;
		status = 0;
	}
	else if (*(*p + len_var_id) == '$')
	{
		*p = *p + len_var_id - 1;
		v_p->str_s = *p + 1;
		v_p->tk_s = *p + 1;
		status = 0;
	}
	return (status);
}

static void	ft_on_no_env_var(char **p, int len_v, char **argn, t_parser_var *v)
{
	if (*(*p + len_v) == '\0')
	{
		ft_ms_append_str_to_str(argn, &(v->tk_s), &(v->str_e));
		v->str_s = v->str_e;
	}
}

void	ft_ms_handle_env_var(char **argn, char **p, int *f, t_parser_var *v_p)
{
	char	*var_id;
	int		len_var_id;
	char	*d;

	d = *p;
	len_var_id = 1;
	while ((d + len_var_id) < v_p->str_e)
	{
		var_id = ft_substr((d + 1), 0, len_var_id);
		if (ft_ms_env_get_var(v_p, var_id, &(v_p->tk_s)) == 0)
		{
			v_p->tk_e = v_p->tk_s + ft_strlen(v_p->tk_s);
			ft_ms_append_str_to_str(argn, &(v_p->tk_s), &(v_p->tk_e));
			ft_set_ptrs(p, len_var_id, f, v_p);
			break ;
		}
		if (ft_on_quote_or_dollar(p, len_var_id, v_p) == 0)
			break ;
		free(var_id);
		len_var_id++;
	}
	free(var_id);
	ft_on_no_env_var(p, len_var_id, argn, v_p);
}
