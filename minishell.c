/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:59:05 by abellakr          #+#    #+#             */
/*   Updated: 2022/06/27 19:04:27 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//--------------------------------------------------------- main
int	main(int ac, char **av, char **env)
{
	char	*buffer;
	t_shell	shell;

	if (!env || !env[0])
		return (write(2, "empty env\n", 10), 1);
	ac = 0;
	av = NULL;
	shell.env = get_env(env);
	while (1)
	{
		buffer = readline ("\nminishell$ ");
		add_history(buffer);
		if (ft_strcmp(buffer, "exit") == 0)
			exit(0);
		shell.data = analyse_buffer(buffer);
		// check exit status in syntax error messages
		if(shell.data == NULL)
		{
			free(shell.env->value);
			shell.env->value = ft_strdup("-1");
		}
		expander(&shell);
		//----------------------------- print data
		// printf("\n........................................................list of data\n");
		// while(shell.data)
		// {
		// 	printf("[%s]\t%d\n", shell.data->str, shell.data->token);
		// 	shell.data = shell.data->next;
		// }
		// printf("\n........................................................table of cmds\n");
		// while(shell.cmd)
		// {
		// 	int i = 0;
		// 	while(shell.cmd->cmd_flags[i])
		// 	{
		// 		printf("(%s)\t", shell.cmd->cmd_flags[i]);
		// 		i++;	
		// 	}
		// 	printf("\n");
		// 	shell.cmd = shell.cmd->next;
			
		// }
		//----------------------------------------- print data 
		free_data(&(shell.data));
		free_data3(&(shell.cmd));
	}
	free_data2(&(shell.env));
	return (0);
}