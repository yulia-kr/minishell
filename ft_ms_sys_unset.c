/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:53:20 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/26 20:53:20 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function performs the following operation.
 * 			(1) Check that the var character starts with [a-zA-Z0-9].
 * 			(2) Search for the '=' character with the variable string
 * 				while ensuring that each char in the sting is [a-zA-Z0-9]
 * 				during the string transversing.
 * 			(3) Once the '=' character is found, its address is assigned to
 * 				the pointer address argument passed in (**var). The '='
 * 				addr would be used to compute the str_len of the variable id.
 * 				For example: WEEKDAY=MONDAY
 * 
 * @param var 
 * @param v_p 
 * @return int 
 */
static int	ft_is_var_valid__chk_char(char *var, t_parser_var *v_p)
{
	char	*s;

	s = var;
	if ((!ft_strchr(ASCII_ALPHA_S, *s) && !ft_strchr(ASCII_ALPHA_B, *s)) || \
		*s == '\0')
	{
		v_p->status = STATUS_ERROR_INVALID_ID;
		ft_printf("Error! Invalid env identifier\n");
		return (-1);
	}
	s++;
	while (*s != '\0' && !ft_strchr("=", *s))
	{
		if (!(*s >= 'A' && *s <= 'Z') && !(*s >= 'a' && *s <= 'z') && \
			!(*s >= '0' && *s <= '9'))
		{
			v_p->status = STATUS_ERROR_INVALID_ID;
			ft_printf("Error! Invalid env identifier\n");
			return (-1);
		}
		s++;
	}
	return (0);
}

/**
 * @brief   This functions checks if the variable id (name) already exist
 * 			 within the env linked list.
 *          If the var id is found within the list then the link is rebuilt by
 * 			connecting its previous node to its next node and deallocating the
 * 			node.
 * 			The environment array is rebuilt after the update within the linked
 * 			list and returns 0 on success.
 *          else -1 is returned.
 * 
 * @param var       This contains both the var id and var value. eg. WEEDAY=SUNDAY
 * @param v_p 
 * @return int 
 */
static int	ft_is_var_id_n_env_var(char *var, t_parser_var *v_p)
{
	t_list	*head;
	t_list	*prev;
	char	*var_id;

	head = v_p->env_lst;
	var_id = NULL;
	var_id = ft_strjoin(var, "=");
	while (head != NULL)
	{
		if (ft_strnstr((char *)(head->content), var_id, ft_strlen(var_id)))
		{
			prev->next = head->next;
			free(head->content);
			free(head);
			ft_ms_env_upd(v_p);
			v_p->status = STATUS_OK;
			ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
			free(var_id);
			return (0);
		}
		prev = head;
		head = head->next;
	}
	free(var_id);
	return (-1);
}

static int	ft_unset_on_parent(char *var, t_parser_var *v_p)
{
	if (var == NULL)
		return (-1);
	if (*var == '-')
	{
		ft_printf("Usage : No option required but argument is required\n");
		v_p->status = STATUS_ERROR_OPTION;
		ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
		return (-1);
	}
	if (ft_is_var_valid__chk_char(var, v_p) < 0)
		return (-1);
	if (ft_is_var_id_n_env_var(var, v_p) == 0)
		return (0);
	v_p->status = STATUS_OK;
	ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
	return (0);
}

/**
 * @brief 	The unset command should be effective only within the main (parent)
 * 			process. Hence, this function does nothing when executed within a 
 * 			child process.
 * 			(1) : Free all resources due to process duplication from parent
 * 			(2) : Exit the child process with success status.
 * 
 * @param v_p 
 */
static void	ft_unset_on_child(t_parser_var *v_p)
{
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	exit(0);
}

int	ft_ms_sys_unset(t_cmd *cmd, t_parser_var *v)
{
	char		*var;
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if ((cmd_exec->argv_s)[0] == 0)
		return (-1);
	if (v->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v);
		v->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "unset") != 0)
		return (1);
	v->flag_handler = 0;
	if ((cmd_exec->argv_s)[1] == NULL)
	{
		if (v->pid == 0)
			ft_unset_on_child(v);
		v->status = STATUS_OK;
		ft_ms_free_rsc(v, FREE_ON_CMD_EXEC);
	}
	var = (cmd_exec->argv_s)[1];
	if (v->pid == 0)
		ft_unset_on_child(v);
	if (ft_unset_on_parent(var, v) < 0)
		return (-1);
	return (0);
}
