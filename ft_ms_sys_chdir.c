/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_sys_chdir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:15:14 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 14:28:16 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_n_rep_var(char **var_id, char *var, t_parser_var *v_p)
{
	t_list	*head;

	head = v_p->env_lst;
	while (head != NULL)
	{
		if (ft_strnstr((char *)(head->content), *var_id, ft_strlen(*var_id)))
		{
			free(head->content);
			head->content = (void *)var;
			ft_ms_env_upd(v_p);
			return (0);
		}
		head = head->next;
	}
	return (-1);
}

static int	ft_env_upd_var(char *var_id, char *var_value, t_parser_var *v_p)
{
	char	*env_var;
	char	*env_var_id;

	env_var_id = ft_strjoin(var_id, "=");
	env_var = ft_strjoin(env_var_id, var_value);
	ft_find_n_rep_var(&env_var_id, env_var, v_p);
	free(env_var_id);
	ft_ms_env_upd(v_p);
	return (0);
}

static void	ft_upd_pwd_on_env(t_parser_var *v_p, char **var_value, \
								char **pwd_cur, char **pwd_old)
{
	*pwd_cur = getcwd(NULL, MAX_PATH);
	ft_env_upd_var("PWD", *pwd_cur, v_p);
	free(*pwd_cur);
	if (ft_ms_env_get_var(v_p, "OLDPWD", var_value) < 0)
	{
		ft_lstadd_back(&(v_p->env_lst), \
				ft_lstnew((void *)ft_strjoin("OLDPWD=", *pwd_old)));
		ft_ms_env_upd(v_p);
	}
	else
	{
		ft_env_upd_var("OLDPWD", *pwd_old, v_p);
	}
	free(*var_value);
	free(*pwd_old);
}

/**
 * @brief   This function executes the chdir within the parent process
 *          (1.) - fetch the string value of the HOME var in the environment
 * 
 * @param argv 
 * @param v_p 
 * @return int 
 */
static int	ft_chdir_on_parent(char **argv, t_parser_var *v_p)
{
	char	*s;
	char	*pwd_cur;
	char	*pwd_old;
	char	*var_value;

	pwd_cur = NULL;
	var_value = NULL;
	ft_ms_env_get_var(v_p, "PWD", &pwd_old);
	if (argv[1] == NULL || argv[1] == 0)
		s = getenv("HOME");
	else
		s = argv[1];
	if (chdir(s) < 0)
	{
		ft_printf("%s: %s\n", "cd", strerror(errno));
		v_p->status = 1;
		ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
		return (-1);
	}
	ft_upd_pwd_on_env(v_p, &var_value, &pwd_cur, &pwd_old);
	ft_ms_free_rsc(v_p, FREE_ON_CMD_EXEC);
	v_p->status = STATUS_OK;
	return (0);
}

/**
 * @brief   This function changes the directory to that given by the user.
 *          The function handles whitespaces that may exist within the cmd. 
 * 
 * @param cmd_str 
 * @return int 
 */
int	ft_ms_sys_chdir(t_cmd *cmd, t_parser_var *v_p)
{
	t_cmd_exec	*cmd_exec;

	if (*(cmd) != EXEC)
		return (1);
	cmd_exec = (t_cmd_exec *)(cmd);
	if ((cmd_exec->argv_s)[0] == 0)
		return (-1);
	if (v_p->flag_handler == 0)
	{
		ft_ms_handle_quotes_n_dollar(cmd_exec->argv_s, v_p);
		v_p->flag_handler = 1;
	}
	if (ft_ms_strcmp((cmd_exec->argv_s)[0], "cd") != 0)
		return (1);
	v_p->flag_handler = 0;
	if (v_p->pid == 0)
	{
		ft_ms_free_rsc(v_p, FREE_ON_EXIT);
		exit(0);
	}
	if (ft_chdir_on_parent(cmd_exec->argv_s, v_p) < 0)
		return (-1);
	return (0);
}
