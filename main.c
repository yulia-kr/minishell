/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:53:37 by cudoh             #+#    #+#             */
/*   Updated: 2022/09/27 17:53:37 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_parser_var	v_p;

	ft_parser_init_var(&v_p, envp);
	signal(SIGINT, ft_ms_handle_sig);
	while (MS_TRUE)
	{
		if (ft_ms_prompt_usr(&v_p, argc, argv) < 0)
			continue ;
		if (v_p.str_len > 0)
		{
			if (ft_ms_parse_usr_cmd(&v_p) < 0)
				continue ;
			if (ft_ms_sys_call_parent(&v_p) != 1)
				continue ;
			//ft_ms_run_cmd(v_p.cmd_tree, &v_p);			//
			ft_ms_sys_call_child(&v_p);
		}
		v_p.flag_handler = 0;
		ft_ms_free_rsc(&v_p, FREE_ON_CMD_EXEC);
	}
	return (0);
}
