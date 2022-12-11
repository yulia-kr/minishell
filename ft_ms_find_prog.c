/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_find_prog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:00:25 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 09:37:26 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	Opens a folder (directory : dir_p) and update the dir_stream
 * 			 pointer.
 * 			return  0: on success.
 * 			return -1: on error.
 * 
 * @param dir_p 
 * @param dir_s 
 * @return int 
 */
static int	ft_dir_open(char *dir_p, DIR **dir_s)
{
	*dir_s = opendir(dir_p);
	if (*dir_s == NULL)
		return (-1);
	return (0);
}

/**
 * @brief	The function is used to read the contents of a directory.
 * 			For each execution, the struct (*dir_e) is filled with
 * 			the item in the directory
 * 
 * @param dir_s 
 * @param dir_e 
 * @return int 
 */
static int	ft_dir_read(DIR **dir_s, struct dirent **dir_e)
{
	*dir_e = readdir(*dir_s);
	if (*dir_e == NULL)
	{
		closedir(*dir_s);
		return (-1);
	}
	return (0);
}

/**
 * @brief 	This function checks if a dir entry string matches the 
 * 			prog name string.
 * 
 */
static int	ft_srch_prog_n_entry(char *path_dir, DIR *dir_s, \
									char *dir_e_name, char **prog)
{
	char	*path_prog;
	int		len_prog_str;
	int		len_dir_e_name;

	path_prog = NULL;
	len_prog_str = ft_strlen(*prog);
	len_dir_e_name = ft_strlen(dir_e_name);
	if ((len_dir_e_name == len_prog_str) && \
		ft_strncmp(*prog, dir_e_name, len_prog_str) == 0)
	{
		path_prog = ft_strjoin(path_dir, "/");
		*prog = ft_strjoin(path_prog, *prog);
		free(path_prog);
		closedir(dir_s);
		return (0);
	}
	return (-1);
}

/**
 * @brief 	This function search for the a prog_name within each directory
 * 			listed with the environment PATH variable.
 * 			If found, the program addr (**prog) is updated with its full
 * 			directory path (dir_path/prog_name)
 * 
 * @param env_path_dirs 
 * @param prog 
 * @param v_p 
 */
void	ft_ms_find_prog(char **env_path_dirs, char **prog, t_parser_var *v_p)
{
	int				idx;
	DIR				*dir_stream;
	struct dirent	*dir_entry_s;

	idx = 0;
	if ((prog[0][0] == '.') || (prog[0][0] == '/'))
		return ;
	while (env_path_dirs[idx] != NULL)
	{
		if (ft_dir_open(env_path_dirs[idx], &dir_stream) == 0)
		{
			while (ft_dir_read(&dir_stream, &dir_entry_s) == 0)
			{
				if (ft_srch_prog_n_entry(env_path_dirs[idx], dir_stream, \
								dir_entry_s->d_name, &prog[0]) == 0)
				{
					v_p->prog_path = prog[0];
					return ;
				}
			}
		}
		idx++;
	}
}
