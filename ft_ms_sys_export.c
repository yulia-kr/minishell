/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:52:53 by cudoh             #+#    #+#             */
/*   Updated: 2022/11/13 11:52:53 by cudoh            ###   ########.fr       */
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
static int	ft_is_var_valid__chk_char(char **var, t_parser_var *v_p)
{
	char	*s;

	s = *var;
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
	*var = s;
	return (0);
}

/**
 * @brief 	This function checks that variable passed by user is valid.
 * 				(1) Check that the pointer to the var is valid (not NULL)
 * 					and check that user did not provide option to cmd
 * 				(2) Validate the characters within the variable id (greeting=).
 * 				(3) If no error from (2), then check that the format is ok
 * 				(4) Update the var_id address ptr.
 * 					create a new dynamic str for this and add it to dynamic
 * 					link list for deallocation after cmd execution is complete
 * 
 * @param var_id 
 * @param var 
 * @param v_p 
 * @return int 
 */
static int	ft_is_var_valid(char **var_id, char *var, t_parser_var *v_p)
{
	char	*s;

	s = var;
	if (var == NULL || var == 0 || *var == '-' || *var == '\0')
	{
		ft_printf("Usage : No option required but argument is required\n");
		v_p->status = STATUS_ERROR_OPTION;
		ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
		return (-1);
	}
	if (ft_is_var_valid__chk_char(&s, v_p) < 0)
		return (-1);
	if (*s == '\0' || s == var)
	{
		ft_printf("Error! : Invalid variable format\n");
		v_p->status = STATUS_ERROR_OPTION;
		ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
		return (-1);
	}
	*var_id = (char *)ft_calloc(((s - var + 1) + NULL_BYTE), SZ_CHAR);
	ft_memcpy(*var_id, var, (s - var + 1));
	ft_lstadd_back(&(v_p->exec_dyn_lst), ft_lstnew((void *)(*var_id)));
	return (0);
}

/**
 * @brief 	The export command should be modified only within the main (parent)
 * 			process. Hence, this function only prints the shell env if 
 * 			executed within a child process.
 * 			(1) : Replaces the cmd "export" with "env" in arg array.
 * 			(1a) -> create a buffer to store the str "env";
 * 			(1b) -> copy the string "env" into the created buffer
 * 			(2) : Add the newly created buffer to garbage linked list
 * 				(exec_dyn_lst) for deallocation after cmd execution.
 * 			(3) : Terminate the cmd argv array with a null just after
 * 				or next to the cmd "env" string in the array.
 * 			(4) : Execute the sys call function ft_ms_sys_env.
 * 			(5) : Free all resources used for during execution process.
 * 
 * 
 * @param argv_s 
 * @param v_p 
 */
static void	ft_export_on_child(t_cmd_exec *cmd_exec, t_parser_var *v_p)
{
	char	**argv_s;

	argv_s = cmd_exec->argv_s;
	argv_s[0] = (char *)ft_calloc(ft_strlen("env") + 1, SZ_CHAR);
	ft_memcpy((void *)((argv_s)[0]), (void *)("env"), ft_strlen("env"));
	ft_lstadd_back(&(v_p->exec_dyn_lst), \
			ft_lstnew((void *)(&((argv_s)[0]))));
	(argv_s)[1] = NULL;
	ft_ms_sys_env((t_cmd *)cmd_exec, v_p);
	ft_ms_free_rsc(v_p, FREE_ON_EXIT);
	exit(0);
}

static int	ft_export_on_parent(char **var_id, char *var, t_parser_var *v_p)
{
	char	*var_n;

	if (ft_is_var_valid(var_id, var, v_p) < 0)
		return (-1);
	if (ft_ms_var_id_n_env_var(var_id, var, v_p) == 0)
		return (0);
	var_n = ft_calloc((ft_strlen(var) + 1), SZ_CHAR);
	ft_memcpy((void *)var_n, (void *)var, ft_strlen(var));
	ft_lstadd_back(&(v_p->env_lst), ft_lstnew((void *)var_n));
	ft_ms_env_upd(v_p);
	v_p->status = STATUS_OK;
	ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
	return (0);
}

/**
 * @brief 	The export sys call adds new or replace existing var in the shell
 * 			environment array. This operation should be done only in the main
 * 			(parent) process. If called within a child process, then it should
 * 			only print the contents of the environment array.
 * 			(1) - Check that the cmd type is of EXEC. if true, typecast ptr.
 * 			(2) - Handle the status character within cmd argv ($?).
 * 			(3) - Handle quote and dollar sign within cmd argv.
 * 			(4) - Store env value in variable (var) from cmd argv buffer.
 * 			(5) - Confirm that the first item in cmd argv equals "export".
 * 			(6) - Check the process level (parent or child).
 * 			(6a) -> if child, call ft_export_on_child.
 * 			(6b) -> if parent, call ft_export_on_parent.
 * 
 * @param v_p 
 * @return int 
 */
int	ft_ms_sys_export(t_cmd *cmd, t_parser_var *v_p)
{
	char		*var;
	char		*var_id;
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if ((cmd_exec->argv_s)[0] == 0)
		return (-1);
	var = (cmd_exec->argv_s)[1];
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "export") != 0)
		return (1);
	v_p->flag_handler = 0;
	if (v_p->pid == 0)
		ft_export_on_child(cmd_exec, v_p);
	if (ft_export_on_parent(&var_id, var, v_p) < 0)
		return (-1);
	return (0);
}
