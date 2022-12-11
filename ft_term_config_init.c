/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_config_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:10:03 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/10 13:04:13 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function is deactivate the SIG_QUIT signal for the console
 * 			by modifying the default console (terminal) settings. The default
 * 			settings is preserved for use within child processes as they may  
 * 			require the signal during their execution.
 * 
 * @param p_term_var 
 */
void	ft_term_config_init(t_parser_var *v_p)
{
	char	*dev_tty;

	v_p->v_term.config_custom = ft_calloc(1, sizeof(struct termios));
	v_p->v_term.config_default = ft_calloc(1, sizeof(struct termios));
	dev_tty = ttyname(STDIN_FILENO);
	v_p->v_term.fd_tty = open(dev_tty, O_NONBLOCK);
	if (isatty(v_p->v_term.fd_tty))
	{
		if (v_p->flag_debug)
			ft_printf("Terminal name: %s\n", dev_tty);
		tcgetattr(v_p->v_term.fd_tty, v_p->v_term.config_default);
		ft_memcpy(v_p->v_term.config_custom, v_p->v_term.config_default, \
					sizeof(struct termios));
		v_p->v_term.config_custom->c_lflag &= ~ISIG;
		v_p->v_term.config_custom->c_cc[VQUIT] = 0;
		tcsetattr(v_p->v_term.fd_tty, TCSANOW, v_p->v_term.config_custom);
	}
}
