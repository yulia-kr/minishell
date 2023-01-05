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

/**
 * @brief 	This function performs the following operation.
 * 			(1) Check that the var character starts with [a-zA-Z0-9].
 * 			(2) Search for the '=' character with the variable string
 * 				while ensuring that each char in the sting is [a-zA-Z0-9]
 * 				during the string transversing.
 * 			(3) Once the '=' character is found, its address is assigned to
 * 				the pointer address argument passed in (**var). The '='
 * 				addr would be used to compute the str_len of the variable id.
 * 				For example: WEEKDAY=MONDAY
 * 
 * @param var 
 * @param v_p 
 * @return int 
 */
static int	ft_env_var__chk_char(char **d, int len_var_id)
{
	char	*s;
	int		idx;

	idx = 1;
	s = (*d) + idx;
	if ((!ft_strchr(ASCII_ALPHA_S, *s) && !ft_strchr(ASCII_ALPHA_B, *s)) || \
		*s == '\0')
	{
		return (-1);
	}
	s++;
	idx++;
	while (idx <= len_var_id && *s != '\0')
	{
		if (!(*s >= 'A' && *s <= 'Z') && !(*s >= 'a' && *s <= 'z') && \
			!(*s >= '0' && *s <= '9'))
		{
			return (-1);
		}
		s++;
		idx++;
	}
	return (0);
}

static void	ft_set_ptrs(char **p, int len_var_id, t_parser_var *v_p)
{
	free(v_p->tk_s);
	v_p->tk_s = NULL;
	if ((*(*p + len_var_id + 1) == 34) && (v_p->flag_quote == 1))
	{
		v_p->flag_quote = 0;
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
		v_p->str_s = *p + 1;
		status = 0;
	}
	else if (*(*p + len_var_id) == '$' || \
		ft_env_var__chk_char(p, len_var_id) < 0)
	{
		*p = *p + len_var_id - 1;
		v_p->str_s = *p + 1;
		v_p->tk_s = *p + 1;
		status = 0;
	}
	return (status);
}

static void	ft_on_no_env_var(char **d, int len_v, char **argn, t_parser_var *v)
{
	char	*ch_s;
	char	*ch_e;

	ch_s = NULL;
	ch_e = NULL;
	if ((v->rc) == 0)
	{
		ch_s = ft_strjoin("\0", "\0");
		ch_e = ch_s + ft_strlen(ch_s);
		ft_ms_append_str_to_str(argn, &ch_s, &ch_e);
		ft_lstadd_back(&(v->exec_dyn_lst), ft_lstnew((void *)ch_s));
		v->tk_s = *d + len_v;
	}
	if ((*d + len_v) == v->str_e)
		v->str_s = v->str_e;
}

void	ft_ms_handle_env_var(char **argn, char **p, t_parser_var *v_p)
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
			ft_set_ptrs(p, len_var_id, v_p);
			v_p->rc = 1;
			break ;
		}
		if (ft_on_quote_or_dollar(p, len_var_id, v_p) == 0)
			break ;
		free(var_id);
		var_id = NULL;
		len_var_id++;
	}
	free(var_id);
	ft_on_no_env_var(&d, len_var_id, argn, v_p);
}
