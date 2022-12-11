/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env_upd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:01:36 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:35:08 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function is used to update the environment variable after
 * 			any change in the environment linked list.
 * 			It obsolete env array and env path array are deleted and recreated
 * 			based on the updated env linked list.
 * 
 * @param v_p 
 */
void	ft_ms_env_upd(t_parser_var *v_p)
{
	ft_ms_free_ptr_to_arrs(&(v_p->env));
	ft_ms_free_ptr_to_arrs(&(v_p->env_path));
	ft_ms_env_lst_to_arr_ptr(&(v_p->env_lst), &(v_p->env));
	ft_ms_env_get_path_dirs(v_p, &(v_p->env_path));
}
