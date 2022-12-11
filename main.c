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
	int				pid_child;

	ft_parser_init_var(&v_p, envp);
	signal(SIGINT, ft_ms_handle_sig);
	if (argc == 1 && argv){}
	while (1)
	{
		v_p.usr_cmd_inp = readline(PROMPT);
		if (v_p.usr_cmd_inp == NULL)
		{
			ft_ms_free_rsc(&v_p, FREE_ON_SIGNAL);
			exit(0);
		}
		v_p.str_len = ft_strlen(v_p.usr_cmd_inp);
		if (ft_ms_chk_quote(&(v_p.usr_cmd_inp)) < 0)
			continue ;
		ft_parser_get_max_args(&v_p);
		if (v_p.str_len > 0)
		{
			add_history(v_p.usr_cmd_inp);
			v_p.cmd_tree = ft_parser_parse(v_p.usr_cmd_inp, &v_p);
			if (*(v_p.cmd_tree) == P_ERROR)
			{
				free(v_p.cmd_tree);
				v_p.cmd_tree = NULL;
				ft_ms_free_rsc(&v_p, FREE_ON_CMD_EXEC);
				continue ;
			}
			if (ft_ms_sys_export(v_p.cmd_tree, &v_p) != 1)
				continue ;
			if (ft_ms_sys_unset(v_p.cmd_tree, &v_p) != 1)
				continue ;
			if (ft_ms_sys_chdir(v_p.cmd_tree, &v_p) != 1)
				continue ;
			if (ft_ms_sys_exit(v_p.cmd_tree, &v_p) != 1)
				continue ;
			ft_term_config_set(&(v_p.v_term), TERM_CONFIG_DEFAULT);
			pid_child = fork();
			if (pid_child == 0)
			{
				v_p.pid = 0;
				ft_ms_run_cmd(v_p.cmd_tree, &v_p);
			}
			wait(&(v_p.status));
			v_p.status_code = WIFEXITED(v_p.status);
			if (v_p.status_code == 1)
				v_p.status = WEXITSTATUS(v_p.status);
			ft_term_config_set(&(v_p.v_term), TERM_CONFIG_CUSTOM);
		}
        v_p.flag_handler = 0;
		ft_ms_free_rsc(&v_p, FREE_ON_CMD_EXEC);
	}
	return (0);
}
