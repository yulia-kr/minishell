/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_init_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 07:14:26 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/17 18:01:38 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser_init_var(t_parser_var *v_p, char **envp)
{
	ft_memset((void *)v_p, 0, sizeof(t_parser_var));
	v_p->str_s = NULL;
	v_p->str_e = NULL;
	v_p->usr_cmd_inp = NULL;
	v_p->f_read = O_RDONLY | S_IRUSR;
	v_p->f_awrite = O_WRONLY | O_CREAT | O_APPEND;
	v_p->f_owrite = O_WRONLY | O_TRUNC | O_CREAT;
	v_p->prog_path = NULL;
	v_p->flag_debug = 0;
	v_p->pid = PPID;
	ft_ms_env_lst_init(envp, &(v_p->env_lst));
	ft_ms_env_lst_to_arr_ptr(&(v_p->env_lst), &(v_p->env));
	ft_ms_env_get_path_dirs(v_p, &(v_p->env_path));
	ft_term_config_init(v_p);
	v_p->dup_argv = NULL;
}
