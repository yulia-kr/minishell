/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_handle_quotes_n_dollar.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:33:08 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 13:49:29 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_preserve_arg(char **argv_n, char **txt_s, char *s)
{
	int		len_str;
	char	*txt;
	char 	*tmp_argv_n;

	len_str = s - *txt_s;
	txt = ft_calloc((len_str + 1), SZ_CHAR);
	ft_memcpy(txt, *txt_s, len_str);
	if (*argv_n == NULL)
	{
		*argv_n = txt;
	}
	else
	{
		tmp_argv_n = *argv_n;
		*argv_n = ft_strjoin(tmp_argv_n, txt);
		free(tmp_argv_n);
		free(txt);
	}
	
}

static void ft_append_txt_to_arg(char **str, char **txt_s, char **txt_e)
{
	size_t	len_str;
	char	*txt;
	char	*str_tmp;
	
	len_str = *txt_e - *txt_s;
	txt = ft_calloc((len_str + 1), sizeof(char));
	ft_memcpy(txt, *txt_s, len_str);
	if (*str == NULL)
	{
		*str = txt;
	}
	else
	{
		str_tmp = *str;
		*str = ft_strjoin(str_tmp, txt);
		free(str_tmp);
		free(txt);
	}
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
static void ft_handle_dollar_n_quote(char **argv, int *flag, char *q, \
													t_parser_var *v_p)
{
	char 	*s;
	char	*str_s;
	char 	*str_e;
	char	*txt_s;
	char	*argv_n;
	char	*var_id;
	char	*var_value;
	int		len_var_id;
	
	s = *argv;
	str_s = *argv;
	str_e = s + ft_strlen(s);
	argv_n = NULL;
	var_value = NULL;
	while (s < str_e)
	{
		if (*flag == 1 && *s == *q)
		{
			*flag = 0;
			str_s = s + 1;
			ft_append_txt_to_arg(&argv_n, &txt_s, &s);
			if (v_p->flag_debug)
				ft_printf("quote_state: %d\n", *flag);
		}
		else if (*flag == 0 && (*s == 39 || *s == 34))
		{
			*q = *s;
			*flag = 1;
			if (s > str_s)
				ft_preserve_arg(&argv_n, &str_s, s);
			txt_s = s + 1;
			if (v_p->flag_debug)
				ft_printf("quote_state: %d\n", *flag);
		}
		
		// check and handle the dollar char when quote char = 39
		if (*s == '$') // handle the dollar
		{
			len_var_id = 1;
			// preservation
			if (*flag == 0 && s > str_s)
			{
				ft_preserve_arg(&argv_n, &str_s, s);
				
			}
			else if  (*flag == 1 && *q == 34 && s > txt_s)
			{
				ft_append_txt_to_arg(&argv_n, &txt_s, &s);
			}

			if ((*flag == 0) || (*flag == 1 && *q == 34))
			{
				if (*(s + 1) == '?')
				{
					var_value = ft_itoa(v_p->status);
					ft_preserve_arg(&argv_n, &var_value, (var_value + ft_strlen(var_value)));
					ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)var_value));
					if (*(s + len_var_id + 1) == 34)
					{
						*flag = 0;
						s = s + len_var_id + 1;
					}
					else
					{
						s = s + len_var_id;
					}
					str_s = s + 1;
					txt_s = s + 1;
				}
				else
				{
					var_id = (char *)ft_calloc(len_var_id + 1, SZ_CHAR);
					ft_memcpy(var_id, (s + 1), len_var_id);
					while ((s + len_var_id) < str_e)
					{
						if (ft_ms_env_get_var(v_p, var_id, &var_value) == 0)
						{
							ft_preserve_arg(&argv_n, &var_value, (var_value + ft_strlen(var_value)));
							// free(var_value);
							if (*(s + len_var_id + 1) == 34)
							{
								*flag = 0;
								s = s + len_var_id + 1;
							}
							else
							{
								s = s + len_var_id;
							}
							str_s = s + 1;
							txt_s = s + 1;
							break;
						}
						// ft_printf("count - var_id:\n");
						len_var_id++;
						free(var_id);
						var_id = (char *)ft_calloc(len_var_id + 1, SZ_CHAR);
						ft_memcpy(var_id, (s + 1), len_var_id);
					}
					if (var_value != NULL)
					{
						free(var_value);
					}
					else
					{
						*s = '\0';
						txt_s = s;
						str_s = s;
					}

					/* 	HANDLE DOLLAR WITHIN QUOTES HERE !!!
						----------------------
						+ increment s within the handler until the closing quote
						+ is found.
						+ During s increment find matching var in env list or arr
						+ to replace the dollar preceeding text ($xxx).
						*/

					free(var_id);
				}
			}
		}
		s++;
	}
	// append remaining chars after last closed quote to new argv str new'world'[order]
	if (*str_s != '\0')
		ft_append_txt_to_arg(&argv_n, &str_s, &str_e);
	if (argv_n != NULL)
	{
		*argv = argv_n;
		ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)argv_n));
	}
}

void ft_ms_handle_quotes_n_dollar(char **argv_s, t_parser_var *v_p)
{
    int		idx;
	int		flag;
	char	quote;
	
	idx = 0;
	flag = 0;
	quote = 0;
	while (argv_s[idx] != 0)
	{
		ft_handle_dollar_n_quote(&argv_s[idx], &flag, &quote, v_p);
		idx++;
	}
    
}


