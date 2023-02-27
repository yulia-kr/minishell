/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_lst_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:47:04 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/27 15:47:04 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_env_lst_init(char **envp, t_list **lst)
{
	int		idx;
	char	*var_str;

	idx = 0;
	if (envp == NULL)
		return ;
	while (envp[idx] != NULL)
	{
		var_str = ft_strdup(envp[idx]);
		ft_lstadd_back(lst, ft_lstnew((void *)var_str));
		idx++;
	}
}
