/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:12:01 by cudoh             #+#    #+#             */
/*   Updated: 2022/12/06 17:17:28 by ykruhlyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_cmd(void)
{
    int pid;
    int rc;
    char    *args[] = {
        "ls",
        ".",
        NULL
    };
    char    *env[] = {
        "TEST=test_code",
        NULL
    };
    rc = 0;
    pid = fork();
    if (pid == 0)
    {
        execve("ls", args, env); 
        perror("execve");
    }
    wait(&rc);
    return (rc);
}
