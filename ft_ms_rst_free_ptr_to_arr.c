/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_rst_free_ptr_to_arr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:42:15 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/08 19:42:15 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_rst_free_ptr_to_arr(char ***arr)
{
	int		idx;
	char	**ptr_arr;

	idx = 0;
	ptr_arr = *arr;
	if (ptr_arr == NULL)
		return ;
	while (ptr_arr[idx] != NULL)
	{
		ptr_arr[idx] = NULL;
		idx++;
	}
	free(ptr_arr);
	ptr_arr = NULL;
}