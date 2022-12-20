/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:54:05 by cudoh             #+#    #+#             */
/*   Updated: 2022/09/27 17:54:05 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>
# include <ncurses.h>
# include "libft/libft.h"
# include "parser.h"
# define PROMPT ("minishell$> ")
# define TERM_CONFIG_DEFAULT (0)
# define TERM_CONFIG_CUSTOM (1)
# define STATUS_ERROR_OPTION (2)
# define STATUS_ERROR_SYNTAX (2)
# define STATUS_ERROR_CMD (127)
# define STATUS_OK (0)
# define STATUS_ERROR_INVALID_ID (1)
# define PPID (1000)
# define SZ_CHAR (1)
# define MS_TRUE (1)
# define NULL_BYTE (1)
# define ASCII_ALPHA_S ("abcdefghijklmnopqrstuvwxyz")
# define ASCII_ALPHA_B ("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
# define ASCII_DIGITS ("0123456789")
# define MAX_PATH (4096)

void	ft_ms_env_lst_init(char **envp, t_list **lst);
int		ft_ms_env_get_path_dirs(t_parser_var *v_p, char ***env_path_dirs);
int		ft_ms_env_lst_to_arr_ptr(t_list **env_lst, char ***env_arr);
int		ft_ms_env_get_var(t_parser_var *v_p, char *var_key, char **var_value);
void	ft_ms_env_upd(t_parser_var *v_p);
void	ft_ms_env_add_var(t_parser_var *v, char *var);
int		ft_exec_cmd(void);
int		ft_ms_run_cmd(t_cmd *cmd, t_parser_var *v_p);	
void	ft_ms_cmd_exec(t_cmd *cmd, t_parser_var *v_p);	
void	ft_ms_cmd_list(t_cmd *cmd, t_parser_var *v_p);	
void	ft_ms_cmd_pipe(t_cmd *cmd, t_parser_var *v_p);
void	ft_ms_cmd_redir(t_cmd *cmd, t_parser_var *v_p);
void	ft_ms_find_prog(char **env_path_dirs, char **prog, t_parser_var *v_p);
int		ft_ms_sys_open_fd(void);
int		ft_ms_sys_chdir(t_cmd *cmd, t_parser_var *v_p);
int		ft_ms_sys_exit(t_cmd *cmd, t_parser_var *v_p);
int		ft_ms_sys_env(t_cmd *cmd, t_parser_var *v_p);
int		ft_ms_sys_export(t_cmd *cmd, t_parser_var *v_p);
int		ft_ms_sys_pwd(t_cmd *cmd, t_parser_var *v);
int		ft_ms_sys_unset(t_cmd *cmd, t_parser_var *v);
int		ft_ms_sys_echo(t_cmd *cmd, t_parser_var *v);
void	ft_ms_handle_status(char **argn, char **p, t_parser_var *v_p);
void	ft_ms_handle_env_var(char **argn, char **p, t_parser_var *v_p);
void	ft_ms_handle_sig(int sig_val);
void	ft_ms_handle_quotes_n_dollar(char **argv_s, t_parser_var *v_p);
int		ft_ms_chk_quote(char **usr_inp);
void	ft_term_config_init(t_parser_var *v_p);
void	ft_term_config_set(t_term_var *p_term_var, int option);
void	ft_ms_free_ptr_to_arrs(char ***arr);
void	ft_ms_rst_free_ptr_to_arr(char ***arr);
void	ft_ms_free_lst(t_list **env_lst);
void	ft_ms_free_rsc(t_parser_var *v, t_option_free option);
void	ft_ms_debug_print_cmd(char *usr_cmd);
int		ft_ms_dup_ptr_to_arr(char **ptr_arr, char ***dup_ptr_arr);
int		ft_ms_strcmp(char *s1, char *s2);
int		ft_ms_var_id_n_env_var(char **var_id, char *var, t_parser_var *v_p);
int		ft_ms_sys_call_parent(t_parser_var *v_p);
void	ft_ms_sys_call_child(t_parser_var *v_p);
int		ft_ms_prompt_usr(t_parser_var *v_p, int argc, char **argv);
int		ft_ms_parse_usr_cmd(t_parser_var *v_p);
int		ft_ms_append_str_to_str(char **str, char **txt_s, char **txt_e);
#endif
