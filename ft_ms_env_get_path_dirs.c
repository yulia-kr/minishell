/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_get_path_dirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:26:57 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:31:27 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   This function path variable value from env and splits the path
 *          value in to string array.
 * 
 * @param env_path_dirs 
 * @return int 
 */
int	ft_ms_env_get_path_dirs(t_parser_var *v_p, char ***env_path_dirs)
{
	char	*env_path;
	int		idx;

	idx = 0;
	env_path = NULL;
	if (ft_ms_env_get_var(v_p, "PATH", &env_path) < 0)
		return (-1);
	*env_path_dirs = ft_split(env_path, ':');
	free(env_path);
	if (v_p->flag_debug)
	{
		while ((*env_path_dirs)[idx] != 0)
		{
			ft_printf("\n%s", (*env_path_dirs)[idx]);
			idx++;
		}
	}
	return (0);
}
