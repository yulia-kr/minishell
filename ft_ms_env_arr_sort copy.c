/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sort_ptr_ptr_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:21:21 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/26 17:21:21 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ms_env_arr_sort(t_parser_var *v)
{
	char	*tmp;
	int		x;
	int		y;
	int		size_arr;

	tmp = NULL;
	x = 0;
	size_arr = ft_lstsize(v->env_lst);
	while (x < (size_arr - 1))
	{
		y = x + 1;
		while (y < (size_arr))
		{
			if (ft_ms_strcmp(((v->env)[x]), ((v->env)[y])) > 0)
			{
				tmp = (v->env)[x];
				(v->env)[x] = (v->env)[y];
				(v->env)[y] = tmp;
			}
			y++;
		}
		x++;
	}
	return (0);
}
