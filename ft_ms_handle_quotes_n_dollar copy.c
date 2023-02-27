/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_handle_quotes_n_dollar.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:33:08 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/18 11:51:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_quote(char **argv, char **s, char **q, \
							t_parser_var *v_p)
{
	if (v_p->flag_quote == 1 && (*(*s)) == **q)
	{
		v_p->flag_quote = 0;
		v_p->str_s = (*(s)) + 1;
		ft_ms_append_str_to_str(argv, &(v_p->tk_s), s);
	}
	else if (v_p->flag_quote == 0 && (**s == 39 || **s == 34))
	{
		**q = **s;
		v_p->flag_quote = 1;
		if (*s > v_p->str_s)
			ft_ms_append_str_to_str(argv, &(v_p->str_s), s);
		v_p->tk_s = (*(s)) + 1;
	}
}

static void	ft_preserve_argv(char **argv, char **s, char **q, \
										t_parser_var *v_p)
{
	if ((v_p->flag_quote == 0) && (*s > v_p->str_s))
	{
		ft_ms_append_str_to_str(argv, &(v_p->str_s), s);
		v_p->str_s = *s;
	}
	else if (v_p->flag_quote == 1 && **q == 34 && *s > (v_p->tk_s))
	{
		ft_ms_append_str_to_str(argv, &(v_p->tk_s), s);
		v_p->tk_s = *s;
	}
}

static void	ft_handle_dollar_n_dquote(char **argv, char **s, \
										t_parser_var *v_p)
{
	char	*tmp_str;

	tmp_str = NULL;
	v_p->rc = 0;
	if (*(*s + 1) == '?')
		ft_ms_handle_status(argv, s, v_p);
	else if (*(*s + 1) == '$')
	{
		tmp_str = *argv;
		if (tmp_str == 0 || tmp_str == NULL)
			*argv = ft_strjoin("", "$$");
		else
			*argv = ft_strjoin(tmp_str, "$$");
		free(tmp_str);
		tmp_str = NULL;
		v_p->tk_s = (*s) + 2;
		v_p->str_s = (*s) + 2;
		*s = *s + 1;
	}
	else
		ft_ms_handle_env_var(argv, s, v_p);
}

/**
 * @brief 		This function checks to see if the quote with the usr command
 * 				is even numbered ("->34, '->39).
 * 				The quote char is updated as the string chars are examined
 * 				while transversing the string.
 *
 * @param usr_inp
 * @param flag
 * @param quote
 */
static void	ft_handle_dollar_n_quote(char **argv, char *q, t_parser_var *v_p)
{
	char	*s;
	char	*argv_n;

	s = *argv;
	v_p->str_s = *argv;
	v_p->str_e = s + ft_strlen(s);
	argv_n = NULL;
	while (s < v_p->str_e)
	{
		ft_handle_quote(&argv_n, &s, &q, v_p);
		if (*s == '$')
		{
			ft_preserve_argv(&argv_n, &s, &q, v_p);
			if ((v_p->flag_quote == 0) || (v_p->flag_quote == 1 && *q == 34))
				ft_handle_dollar_n_dquote(&argv_n, &s, v_p);
		}
		s++;
	}
	if (*(v_p->str_s) != '\0')
		ft_ms_append_str_to_str(&argv_n, &(v_p->str_s), &(v_p->str_e));
	if (argv_n != NULL)
	{
		*argv = argv_n;
		ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)argv_n));
	}
}

void	ft_ms_handle_quotes_n_dollar(char **argv_s, t_parser_var *v_p)
{
	int		idx;
	char	quote;

	idx = 0;
	v_p->flag_quote = 0;
	quote = 0;
	while (argv_s[idx] != 0 && (ft_strlen(argv_s[idx]) > 0))
	{
		ft_handle_dollar_n_quote(&argv_s[idx], &quote, v_p);
		idx++;
	}
}
