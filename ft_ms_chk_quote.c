/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_chk_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:41:23 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 21:34:39 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 		This function checks to see if the quote with the usr command
 * 				is even numbered ('->34, "->39).
 * 				The quote char is updated as the string chars are examined
 * 				while transversing the string.
 * 
 * @param usr_inp 
 * @param flag 
 * @param quote 
 */
static void	ft_is_quote_complete(char *usr_inp, int *flag, char *quote)
{
	char	*s;
	char	*str_e;

	*quote = 0;
	*flag = 0;
	s = usr_inp;
	str_e = usr_inp + ft_strlen(usr_inp);
	while (s < str_e)
	{
		if (*flag == 1 && *s == *quote)
			*flag ^= 1;
		else if (*flag == 0 && (*s == 39 || *s == 34))
		{
			*quote = *s;
			*flag ^= 1;
		}
		s++;
	}
}

/**
 * @brief 			This function manages the user command inputted by
 * 					concatenating new command (*r_inp) to existing command
 * 					(*usr_inp).
 * 					If (*r_inp) equal zero, it mean (ctlr + d) was pressed.
 * 					Then the function should exit with a code (-1)
 * 					If (*r_inp) equal null, it mean (enter ) was pressed without
 * 					any char passed in. Then a newline is appended to existing
 * 					command string.
 * 					If (*r_inp) is greater zero, it mean usr passed in char or
 * 					string. The new string or char is appended to existing 
 * 					command string.
 * 
 * @param usr_inp 
 * @param usr_inp_t 
 * @param r_inp 
 * @return int 
 */
static int	ft_recurs_roll_inp(char **usr_inp, char **usr_inp_t, char **r_inp)
{
	free(*usr_inp);
	*usr_inp = NULL;
	if (*r_inp == 0)
	{
		return (-1);
	}
	else if (ft_strlen(*r_inp) > 0 && *r_inp != NULL)
	{
		*usr_inp = ft_strjoin(*usr_inp_t, *r_inp);
		free(*usr_inp_t);
		free(*r_inp);
		*usr_inp_t = NULL;
		*r_inp = NULL;
		return (1);
	}
	else
	{
		*usr_inp = ft_strjoin(*usr_inp_t, "\n");
		free(*usr_inp_t);
		*usr_inp_t = NULL;
		*usr_inp_t = ft_strdup(*usr_inp);
		return (0);
	}
	return (0);
}

/**
 * @brief 	This function ensures that the user is prompted when
 * 			the quotes within the given command are not even numbered.
 * 			It activates the interactive mode.
 * 			It duplicates the given command and store in a tmp char, then
 * 			prompt the user to provide further string or char with the
 * 			require quote within.
 * 			The new string or char received will be concatenated to the
 * 			duplicated initial string, hence extending the string length
 * 			of the user command.
 * 			It returns the following status.
 * 			 0 - user had pressed only enter button. no char received.
 * 			 1 - user has inputted chars
 * 			-1 - user pressed ctrl + D. interactive mode will exit.
 * 
 * @param usr_inp 
 * @return int 
 */
static int	ft_recurs_cmd_inp(char **usr_inp)
{
	char	*recurs_inp;
	char	*usr_inp_tmp;
	int		status;

	status = 0;
	recurs_inp = NULL;
	usr_inp_tmp = ft_strdup(*usr_inp);
	while (recurs_inp == NULL)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		recurs_inp = readline("> ");
		status = ft_recurs_roll_inp(usr_inp, &usr_inp_tmp, &recurs_inp);
		if (status > 0 || status < 0)
			break ;
	}
	return (status);
}

int	ft_handle_usr_inp_end(char *usr_inp)
{
	size_t	i;

	i = 0;
	if (usr_inp == NULL || *usr_inp == '\0')
		return (0);
	i = ft_strlen(usr_inp) - 1;
	while (i > 0 && ft_strchr(P_WHITESPACE, usr_inp[i]))
		i--;
	if (usr_inp[i] == '|')
		return (-1);
	return (0);
}

/**
 * @brief 	This function ensures that the quote (' and ") depicts the following
 * 			-> quote counts within the given usr command are even numbered.
 * 			-> characters within quotes and not interpreter.
 * 			-> repeatedly prompt the user until the quotes are even numbered.
 * 
 * @param usr_inp 
 */

int	ft_ms_chk_quote(char **usr_inp)
{
	int		flag;
	char	quote;
	int		flag_debug;
	int		status;

	flag = 0;
	flag_debug = 0;
	status = 0;
	ft_is_quote_complete(*usr_inp, &flag, &quote);
	while (flag == 1 || (ft_handle_usr_inp_end(*usr_inp) < 0))
	{
		status = ft_recurs_cmd_inp(usr_inp);
		if (status < 0)
			return (status);
		ft_is_quote_complete(*usr_inp, &flag, &quote);
		if (flag_debug)
		{
			ft_printf("recurse_flag: %d\n", flag);
			ft_printf("|%s|\n", *usr_inp);
		}
	}
	return (status);
}
