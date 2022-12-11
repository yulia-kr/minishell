/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_lst_to_arr_ptr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:13:30 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/12 15:13:30 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lst_to_arr(t_list *lst, char **env_var)
{
	int	len_str;

	len_str = ft_strlen((char *)(lst->content));
	*env_var = (char *)ft_calloc((len_str + 1), sizeof(char));
	ft_memcpy(*env_var, (char *)(lst->content), len_str);
}

int	ft_ms_env_lst_to_arr_ptr(t_list **env_lst, char ***env_arr)
{
	t_list	*lst_head;
	char	**env_var_ptr;
	char	*env_var;
	int		var_cnt;

	if (*env_lst == NULL)
		return (-1);
	lst_head = *env_lst;
	var_cnt = ft_lstsize(lst_head);
	env_var_ptr = (char **)ft_calloc((var_cnt + 1), sizeof(char *));
	env_var_ptr[var_cnt] = NULL;
	var_cnt = 0;
	while (lst_head != NULL)
	{
		ft_lst_to_arr(lst_head, &env_var);
		env_var_ptr[var_cnt] = env_var;
		lst_head = lst_head->next;
		var_cnt++;
	}
	*env_arr = env_var_ptr;
	return (0);
}
