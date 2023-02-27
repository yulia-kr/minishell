/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:48:27 by cudoh             #+#    #+#             */
/*   Updated: 2022/08/22 20:45:04 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
// Includes for test purpose
//# include <sys/types.h>
//# include <sys/stat.h>
//# include <fcntl.h>
//# include <stdio.h>

// Allow "compiler cc/gcc/clang -D" to override definition
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// FUNCTION DECLARATIONS
char	*get_next_line(int fd);
// UTILS FUNCTION  DECLARATIONS
void	*ft_realloc(void *src, size_t offset_size);

#endif
