/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_free_ptr_to_arrs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:50:12 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/12 13:50:12 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_free_ptr_to_arrs(char ***arr)
{
	int		idx;
	char	**ptr_arr;

	idx = 0;
	ptr_arr = *arr;
	if (ptr_arr == NULL)
		return ;
	while (ptr_arr[idx] != NULL)
	{
		free(ptr_arr[idx]);
		ptr_arr[idx] = NULL;
		idx++;
	}
	free(ptr_arr);
	ptr_arr = NULL;
}
