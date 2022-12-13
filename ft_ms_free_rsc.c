/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_free_rsc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:37:03 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 09:49:06 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_on_cmd_exec(t_parser_var *v)
{
	ft_ms_free_lst(&(v->exec_dyn_lst));
	free(v->usr_cmd_inp);
	free(v->prog_path);
	ft_free_parser_tree(v->cmd_tree);
	v->usr_cmd_inp = NULL;
	v->prog_path = NULL;
}

static void	ft_free_on_exit(t_parser_var *v)
{
	ft_term_config_set(&(v->v_term), TERM_CONFIG_DEFAULT);
	close((v->v_term).fd_tty);
	free((v->v_term).config_custom);
	free((v->v_term).config_default);
	ft_free_on_cmd_exec(v);
	ft_ms_free_lst(&(v->env_lst));
	ft_ms_free_ptr_to_arrs(&(v->env));
	ft_ms_free_ptr_to_arrs(&(v->env_path));
	ft_ms_free_ptr_to_arrs(&(v->dup_argv));
	rl_clear_history();
	close(2);
	close(1);
	close(0);
}

void	ft_ms_free_rsc(t_parser_var *v, t_option_free option)
{
	if (option == FREE_ON_CMD_EXEC)
		ft_free_on_cmd_exec(v);
	else if (option == FREE_ON_EXIT)
		ft_free_on_exit(v);
	else if (option == FREE_ON_SIGNAL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		ft_free_on_exit(v);
	}
}
