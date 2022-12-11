/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_dup_ptr_to_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:39:27 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/02 19:39:27 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/libft.h"

size_t	ft_cnt_ptrs_n_ptr(char **ptr_arr)
{
	size_t	cnt;

	cnt = 0;
	if (ptr_arr == NULL)
		return (cnt);
	while (ptr_arr[cnt] != NULL)
		cnt++;
	return (cnt);
}

int	ft_ms_dup_ptr_to_arr(char **ptr_arr, char ***dup_ptr_arr)
{
	char	**dup;
	size_t	cnt_arr;
	size_t	idx;

	idx = 0;
	if (ptr_arr == NULL)
		return (-1);
	cnt_arr = ft_cnt_ptrs_n_ptr(ptr_arr);
	dup = (char **)ft_calloc((cnt_arr + 1), sizeof(char *));
	while (ptr_arr[idx] != NULL)
	{
		dup[idx] = ft_strdup(ptr_arr[idx]);
		idx++;
	}
	*dup_ptr_arr = dup;
	return (0);
}
