/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumutlu <mumutlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:57:58 by mumutlu           #+#    #+#             */
/*   Updated: 2023/11/03 17:27:25 by mumutlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_new_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc((total_len * sizeof(char)) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = ((unsigned char *)s1)[i];
		i++;
	}
	result[i++] = '/';
	j = 0;
	while (s2[j] != '\0')
		result[i++] = ((unsigned char *)s2)[j++];
	result[i] = '\0';
	return (result);
}

char	**ft_path_search(char **env)
{
	char	**result;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			temp = ft_strdup(env[i]);
			if (!temp)
				return (NULL);
		}
		i++;
	}
	if (temp)
	{
		result = ft_split(&temp[5], ':');
		if (!result)
			return (NULL);
		free(temp);
		return (result);
	}
	return (NULL);
}

char	*path_finder(char **path, char *str)
{
	char	*new_path;
	int		i;

	i = 0;
	while (path[i])
	{
		new_path = ft_new_strjoin(path[i], str);
		if (access(new_path, F_OK) == 0)
			return (new_path);
		free(new_path);
		i++;
	}
	return (NULL);
}

char	*deneme(char *line, char *env[])
{
	char	**path;
	char	*command_path;
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (*line == '/' || *line == '.')
	{
		if (access(line, F_OK))
			return (perror("PATH not found\n"), NULL);
		execve(cmd[0], cmd, env);
	}
	path = ft_path_search(env);
	if (path == NULL)
		return (perror("PATH not found\n"), NULL);
	command_path = path_finder(path, cmd[0]);
	if (command_path == NULL)
	{
		free_tab(path);
		free(command_path);
		return (NULL);
	}
	else
		execve(command_path, cmd, env);
	return (NULL);
}

char	*get_line()
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("Minishell>");
	if (line)
		add_history(line);
	return (line);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	(void)argv;
	while (argc)
	{
		line = readline("minishell@42Kocaeli % ");
		//ft_readline(line);
		deneme(line, env);
	}
}


// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// /usr/local/bin
// /usr/bin
// /bin
// /usr/sbin
// /sbin
// /usr/local/munki