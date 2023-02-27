/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:39:37 by cudoh             #+#    #+#             */
/*   Updated: 2022/05/09 18:54:13 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ft_get_split_nbr(char const *s, char c)
{
	size_t	idx;
	size_t	cnt;
	int		flag_c;
	int		flag_nc;

	idx = 0;
	flag_c = 0;
	flag_nc = 0;
	cnt = 0;
	while (*(s + idx) != '\0')
	{
		if (*(s + idx) != c && flag_nc == 0)
		{
			flag_nc = 1;
			flag_c = 0;
			cnt++;
		}
		else if (*(s + idx) == c && flag_c == 0)
		{
			flag_nc = 0;
			flag_c = 1;
		}
		idx++;
	}
	return (cnt);
}

static void	ft_bufncpy(char const *s, char **buf, size_t buf_idx, size_t cnt)
{
	size_t	x;
	char	*split_txt;

	x = 0;
	split_txt = (char *)malloc(cnt + 1);
	if (split_txt != 0)
	{
		split_txt[cnt] = '\0';
		while (x < cnt)
		{
			split_txt[x] = *((s - cnt) + x);
			x++;
		}
	}
	buf[buf_idx] = split_txt;
}

static void	ft_ops_nc(int *flag, size_t *cnt)
{
	*flag = 1;
	*cnt = 0;
}

static void	ft_make_split(char const *s, char c, char	**buf)
{
	size_t	cnt;
	size_t	y;
	int		flag;

	cnt = 0;
	y = 0;
	flag = 0;
	while (*(s) != '\0')
	{
		if ((*(s) != c) && flag == 0)
		{
			ft_ops_nc(&flag, &cnt);
		}
		else if ((*(s) == c) && flag == 1)
		{
			flag = 0;
			ft_bufncpy(s, buf, y, cnt);
			y += 1;
		}
		if (flag)
			cnt++;
		s++;
	}
	if (*(s - 1) != c)
		ft_bufncpy(s, buf, y, cnt);
}

char	**ft_split(char const *s, char c)
{
	size_t	splt_nbr;
	char	**splt_buf;

	if (s != 0)
	{
		splt_buf = 0;
		splt_nbr = ft_get_split_nbr(s, c);
		if (splt_nbr != 0)
		{
			splt_buf = (char **)malloc(sizeof(char *) * (splt_nbr + 1));
			if (splt_buf != 0)
			{
				*(splt_buf + splt_nbr) = 0;
				ft_make_split(s, c, splt_buf);
			}
		}
		else
		{
			splt_buf = (char **)malloc(sizeof(char *) * (1));
			if (splt_buf != 0)
				*(splt_buf) = 0;
		}
		return (splt_buf);
	}
	return (0);
}
