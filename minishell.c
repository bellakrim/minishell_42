/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:59:05 by abellakr          #+#    #+#             */
/*   Updated: 2022/06/19 15:22:49 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if(shell.data == NULL)
		{
			free(shell.env->value);
			shell.env->value = ft_strdup("-1");
		}
		
		// expander(&shell.data, shell.env);
		while(shell.data)
		{
			printf("\n-------------------------- : node\n");
			printf("%s\n%d", shell.data->str, shell.data->token);
			shell.data = shell.data->next;
		}
		free_data(&(shell.data));
	}
	free_data2(&(shell.env));
	return (0);
}
