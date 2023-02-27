/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_append_str_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:56:50 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 17:56:50 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/libft.h"

int	ft_ms_append_str_to_str(char **str, char **txt_s, char **txt_e)
{
	size_t	len_str;
	char	*txt;
	char	*str_tmp;

	len_str = *txt_e - *txt_s;
	txt = ft_calloc((len_str + 1), sizeof(char));
	ft_memcpy(txt, *txt_s, len_str);
	if (*str == NULL)
	{
		*str = txt;
	}
	else
	{
		str_tmp = *str;
		*str = ft_strjoin(str_tmp, txt);
		free(str_tmp);
		free(txt);
	}
	return (0);
}
