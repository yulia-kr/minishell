/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_export_on_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 20:26:26 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/26 20:26:26 by cudoh            ###   ########.fr       */
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
static int	ft_is_var_valid__chk_char(char **var, t_parser_var *v_p)
{
	char	*s;

	s = *var;
	if ((!ft_strchr(ASCII_ALPHA_S, *s) && !ft_strchr(ASCII_ALPHA_B, *s)) || \
		*s == '\0')
	{
		v_p->status = STATUS_ERROR_INVALID_ID;
		ft_printf("Error! Invalid env identifier\n");
		return (-1);
	}
	s++;
	while (*s != '\0' && !ft_strchr("=", *s))
	{
		if (!(*s >= 'A' && *s <= 'Z') && !(*s >= 'a' && *s <= 'z') && \
			!(*s >= '0' && *s <= '9'))
		{
			v_p->status = STATUS_ERROR_INVALID_ID;
			ft_printf("Error! Invalid env identifier\n");
			return (-1);
		}
		s++;
	}
	*var = s;
	return (0);
}

/**
 * @brief 	This function checks that variable passed by user is valid.
 * 				(1) Check that the pointer to the var is valid (not NULL)
 * 					and check that user did not provide option to cmd
 * 				(2) Validate the characters within the variable id (greeting=).
 * 				(3) If no error from (2), then check that the format is ok
 * 				(4) Update the var_id address ptr.
 * 					create a new dynamic str for this and add it to dynamic
 * 					link list for deallocation after cmd execution is complete
 * 
 * @param var_id 
 * @param var 
 * @param v_p 
 * @return int 
 */
static int	ft_is_var_valid(char **var_id, char *var, t_parser_var *v_p)
{
	char	*s;

	s = var;
	if (*var == '-')
	{
		ft_printf("Usage : No option required\n");
		v_p->status = STATUS_ERROR_OPTION;
		return (-1);
	}
	if (ft_is_var_valid__chk_char(&s, v_p) < 0)
		return (-1);
	if (s == var)
	{
		ft_printf("Error! : Invalid variable format\n");
		v_p->status = STATUS_ERROR_OPTION;
		return (-1);
	}
	*var_id = (char *)ft_calloc(((s - var + 1) + NULL_BYTE), SZ_CHAR);
	ft_memcpy(*var_id, var, (s - var + 1));
	ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)(*var_id)));
	return (0);
}

static int	ft_chk_arg(t_cmd_exec *cmd_exec, t_parser_var *v_p, \
						int (*f)(t_parser_var *))
{
	if (cmd_exec->argv_s[1] == NULL || (cmd_exec->argv_s[1][0] == '\0'))
	{
		f(v_p);
		return (0);
	}
	return (-1);
}

int	ft_ms_export_on_parent(t_cmd_exec *cmd_exec, t_parser_var *v_p, \
						int (*f)(t_parser_var *))
{
	char	*var;
	char	*var_id;
	int		idx;

	idx = 1;
	if (ft_chk_arg(cmd_exec, v_p, f) == 0)
		return (0);
	while (MS_TRUE)
	{
		if (cmd_exec->argv_s[idx] == NULL)
			break ;
		var = (cmd_exec->argv_s)[idx];
		if ((ft_is_var_valid(&var_id, var, v_p) < 0) || \
			(ft_ms_var_id_n_env_var(&var_id, var, v_p) == 0))
		{
			idx++;
			continue ;
		}
		ft_ms_env_add_var(v_p, var);
		v_p->status = STATUS_OK;
		idx++;
	}
	ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
	return (0);
}
