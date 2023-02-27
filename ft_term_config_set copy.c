/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_config_set.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:59:12 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 10:43:08 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_term_config_set(t_term_var *p_term_var, int option)
{
	if (option == TERM_CONFIG_DEFAULT)
		tcsetattr(p_term_var->fd_tty, TCSANOW, p_term_var->config_default);
	else
		tcsetattr(p_term_var->fd_tty, TCSANOW, p_term_var->config_custom);
}
