/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:53:56 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/11 17:28:55 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define P_SYMBOLS ("|<>")
# define P_WHITESPACE (" \n\r\t\v")
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
//# include "minishell.h"

typedef struct s_term
{
	struct termios	*config_custom;
	struct termios	*config_default;
	int				fd_tty;
}	t_term_var;

typedef enum e_cmd
{
	P_ERROR = -1,
	EXEC = 1,
	PIPE,
	REDIR,
	LIST
}	t_cmd;

typedef enum e_option_free
{
	FREE_ON_EXIT = 0,
	FREE_ON_SIGNAL,
	FREE_ON_CMD_EXEC,
}	t_option_free;

typedef struct s_cmd_pipe
{
	t_cmd	cmd_type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd_pipe;

typedef struct s_cmd_list
{
	t_cmd	cmd_type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd_list;

typedef struct s_cmd_redir
{
	t_cmd	cmd_type;
	char	*file_s;
	char	*file_e;
	int		file_mode;
	int		file_fd;
	t_cmd	*cmd;
}	t_cmd_redir;

typedef struct s_cmd_exec
{
	t_cmd	cmd_type;
	char	**argv_s;
	char	**argv_e;
}	t_cmd_exec;

typedef struct s_parser_var
{
	t_term_var	v_term;
	int			flag_handler;
	char		**dup_argv;
	char		*str_s;
	char		*str_e;
	char		*usr_cmd_inp;
	t_list		*env_lst;
	t_list		*exec_dyn_lst;
	char		**env;
	char		**env_path;
	char		*prog_path;
	size_t		str_len;
	int			max_args;
	int			rc;
	int			pid;
	int			status;
	int			status_code;
	int			f_read;
	int			f_awrite;
	int			f_owrite;
	int			tok;
	int			flag_debug;
	char		*tk_s;
	char		*tk_e;
	t_cmd		*cmd_tree;
}			t_parser_var;

void	ft_parser_init_var(t_parser_var *v_p, char **envp);
int		ft_parser_get_max_args(t_parser_var *v_p);
t_cmd	*ft_parser_init_cmd_pipe(t_cmd *left, t_cmd *right);
t_cmd	*ft_parser_init_cmd_list(t_cmd *left, t_cmd *right);
t_cmd	*ft_parser_init_cmd_exec(t_parser_var *v_p);
t_cmd	*ft_parser_init_cmd_redir(t_cmd *subcmd, t_parser_var *v, \
									int f_m, int f_fd);
int		ft_parser_peek(char **str_s, char *str_e, char *tk);
int		ft_parser_get_token(char **str_s, char *str_e, \
						char **tk_s, char **tk_e);
t_cmd	*ft_parser_parse(char *s, t_parser_var *v);
t_cmd	*ft_parser_parse_line(char **str_s, char *str_e, t_parser_var *v);
t_cmd	*ft_parser_parse_pipe(char **str_s, char *str_e, t_parser_var *v);
t_cmd	*ft_parser_parse_exec(char **str_s, char *str_e, t_parser_var *v);
t_cmd	*ft_parser_null_term(t_cmd *cmd);
t_cmd	*ft_parser_parse_redir(t_cmd *cmd, char **str_s, char *str_e, \
								t_parser_var *v);
void	ft_free_parser_tree(t_cmd *cmd);
#endif