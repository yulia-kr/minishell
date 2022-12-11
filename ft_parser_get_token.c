/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_get_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 08:15:10 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 10:32:38 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	This function adjust the scan pointer if the redirection char
 * 			occurs once or twice (<, <<, >, >>)
 * 
 * @param s 
 * @param rc 
 */
static void	ft_on_redir(char **s, int *rc)
{
	(*s)++;
	if (**s == '>' && *((*s) - 1) == '>')
	{
		*rc = '+';
		(*s)++;
	}
	else if (**s == '<' && *((*s) - 1) == '<')
	{
		*rc = '-';
		(*s)++;
	}
}

/**
 * @brief   This function handles the quotes (' (39) and " (34) )
 * 
 * @param s 
 * @param str_e 
 */
static void	ft_on_quotes(char **s, char *str_e)
{
	char	quote;
	int		flag;

	quote = **s;
	flag = 0;
	while (*s < str_e)
	{
		if (flag == 1 && **s == quote)
			flag ^= 1;
		else if (flag == 0 && (**s == 39 || **s == 34))
		{
			quote = **s;
			flag ^= 1;
		}
		if (flag == 0 && ft_strchr(P_WHITESPACE, **s))
			break ;
		(*s)++;
	}
}

/**
 * @brief 	This function checks that the found token matches its corresponding
 * 			return character and advance the scan ptr to next whitespace
 * 			character which is marked as the end of the token.
 * 			The return characters are updated accordingly.
 *
 * @param s
 * @param str_e
 * @param rc
 */
static void	ft_match_char(char **s, char *str_e, int *rc)
{
	if (**s == 0)
		return ;
	else if (**s == '|')
		(*s)++;
	else if (**s == '<' || **s == '>')
		ft_on_redir(s, rc);
	else
	{
		*rc = 'a';
		while (*s < str_e && !ft_strchr(P_WHITESPACE, **s) && \
				!ft_strchr(P_SYMBOLS, **s))
		{
			if (**s == 39 || **s == 34)
				ft_on_quotes(s, str_e);
			else
			(*s)++;
		}
	}
}

/**
 * @brief 	This function scans a string and tokenize it. Each scan returns
 * 			a token. A token is considered to be a character or sequence of
 * 			chars bounded by whitespace char (" <a> " or " <hello> ").
 * 			It could also be a symbol character ("| < > ' &")
 * 			(1) Advance the scan ptr through the string until a non whitespace
 * 				is found. (start of a token is found).
 * 			(2) Update the token starting address pointer (tk_s) with scan ptr
 * 				address.
 * 			(3) Update the return variable with the value at the scan ptr addr.
 * 			(4) Check the char value and ensure the return variable has its
 * 				right matching and correspond return value.
 * 			(5) Update the token end pointer variable (end of token - next 
 * 				whitespace after token).
 * 			(6) Scan for the next token start by skipping whitespace characters
 * 				if they exist.
 * 			(7) Update the String start pointer if a new token start is found.
 * 
 * @param p_s  -> pointer to the starting position (char) of the scan (string)
 * @param p_e  -> pointer to the end of the string ('\0') being scanned
 * @param tk_s -> pointer to the starting position of found token
 * @param tk_e -> pointer to the end position of the found token (the next
 * 					whitespace after the found token)
 * @return int
 */
int	ft_parser_get_token(char **str_s, char *str_e, char **tk_s, char **tk_e)
{
	int		rc;
	char	*s;

	s = *str_s;
	while (s < str_e && ft_strchr(P_WHITESPACE, *s))
		s++;
	if (tk_s != NULL)
		*tk_s = s;
	rc = *s;
	ft_match_char(&s, str_e, &rc);
	if (tk_e != NULL)
		*tk_e = s;
	while (s < str_e && ft_strchr(P_WHITESPACE, *s))
		s++;
	*str_s = s;
	return (rc);
}
