/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:48:57 by cudoh             #+#    #+#             */
/*   Updated: 2022/08/22 20:45:48 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_realloc(void *src, size_t offset_size)
{
	void	*new_buf;

	if (src == NULL)
	{
		new_buf = malloc(offset_size + 1);
		if (new_buf == NULL)
			return (0);
		ft_memset(new_buf, 0, offset_size + 1);
		return (new_buf);
	}
	new_buf = malloc(ft_strlen(src) + offset_size + 1);
	if (new_buf == NULL)
		return (0);
	ft_memset(new_buf, 0, ft_strlen(src) + offset_size + 1);
	ft_strlcpy((char *)new_buf, (char *)src, ft_strlen(src) + 1);
	free(src);
	src = NULL;
	return (new_buf);
}
