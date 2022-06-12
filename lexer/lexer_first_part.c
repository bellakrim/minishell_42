/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_first_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:11:13 by abellakr          #+#    #+#             */
/*   Updated: 2022/06/12 15:37:55 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//------------------------- ANALYSE BUFFER
t_data	*analyse_buffer(char *buffer)
{
	t_data	*data;
	char	*str;

	data = NULL;
	str = buffer;
	free(buffer);
	buffer = ft_strtrim(str, " ");
	if (check_syntax_error(buffer) == 1)
	{
		write (2, "syntax error", 12);
		return (NULL);
	}		
	if (data_reconization(buffer, &data) == 1)
	{
		free_data(&data);
		write (2, "syntax error", 12);
		return (NULL);
	}
	free(buffer);
	return (data);
}

// ----------------------------------- save data and token reconization
int	data_reconization(char *buffer, t_data **data)
{
	while (*buffer)
	{
		if (ft_is_operator(*buffer) == 1)
		{
			if (operator_type(&buffer, data) == 1)
				return (1);
		}
		else if (ft_is_operator(*buffer) == 0)
		{
			if (word_token(&buffer, data) == 1)
				return (1);
		}
	}
	return (0);
}

//<----------------------------------------------------------->    word
int	word_token(char **buffer, t_data **data)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = *buffer;
	while (**buffer != '\0')
	{
		i++;
		(*buffer)++;
		if (ft_is_operator(**buffer) == 1)
			break ;
	}
	str1 = ft_substr(str1, 0, i);
	str2 = ft_strtrim(str1, " ");
	ft_lstadd_back_lexer(data, ft_lstnew_lexer(str2, CMD_WORD));
	free(str1);
	free(str2);
	return (0);
}
