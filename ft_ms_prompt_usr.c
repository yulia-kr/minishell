/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_prompt_usr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:18:30 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 15:18:30 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function handles the CTRL + D signal
 * 
 * @param v_p 
 * @return int 
 */
int	ft_ms_prompt_usr(t_parser_var *v_p, int argc, char **argv)
{
	int	status;

	status = 0;
	if (argc > 1)
	{
		v_p->usr_cmd_inp = argv[1];
		ft_printf("Shell Prompt argv: Disabled\n");
		v_p->usr_cmd_inp = NULL;
		ft_ms_free_rsc(v_p, FREE_ON_EXIT);
		exit(-1);
	}
	else
	{
		v_p->usr_cmd_inp = readline(PROMPT);
	}
	if (v_p->usr_cmd_inp == NULL)
	{
		ft_ms_free_rsc(v_p, FREE_ON_SIGNAL);
		exit(0);
	}
	v_p->str_len = ft_strlen(v_p->usr_cmd_inp);
	status = ft_ms_chk_quote(&(v_p->usr_cmd_inp));
	return (status);
}
