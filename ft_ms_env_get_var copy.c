/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_get_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:05:27 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/12 19:05:27 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_null_value(char **split_res, char **var_value)
{
	size_t	len_value_str;

	if (split_res[1] == NULL)
	{
		*var_value = (char *)ft_calloc(1 + NULL_BYTE, SZ_CHAR);
		**var_value = '\0';
	}
	else
	{
		len_value_str = ft_strlen(split_res[1]);
		*var_value = (char *)ft_calloc(len_value_str + NULL_BYTE, SZ_CHAR);
		ft_memcpy(*var_value, split_res[1], len_value_str);
	}
}

/**
 * @brief 	This function fetches the environment variable value
 * 			based on the given key.
 * 			It is a replacement for the sys call getenv().
 * 			For each item in the env array the following are performed.
 * 			-> search for the key within the string.
 * 			-> check that the next char after the key string is '='
 * 			-> If found, split the string by '=' and return the second
 * 				item in the split result string array.
 *			-> create a new char array to copy the split result into.
 *			-> copy the value into the newly created char array.
 * 			-> free the split result string array.
 * 
 * @param v_p 
 * @param var_key 
 * @param var_value 
 * @return int 
 */
int	ft_ms_env_get_var(t_parser_var *v_p, char *var_key, char **var_value)
{
	int		idx;
	size_t	len_str;
	char	**split_str;
	char	**env;

	idx = 0;
	env = v_p->env;
	if (v_p->env == NULL || var_key == NULL)
		return (-1);
	while ((v_p->env)[idx] != NULL)
	{
		len_str = ft_strlen(var_key);
		if (ft_strncmp(env[idx], var_key, len_str) == 0 && \
						(env[idx][len_str] == '='))
		{
			split_str = ft_split(env[idx], '=');
			ft_handle_null_value(split_str, var_value);
			ft_ms_free_ptr_to_arrs(&split_str);
			return (0);
		}
		idx++;
	}
	return (-1);
}
