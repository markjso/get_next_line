/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:41:39 by jmarks            #+#    #+#             */
/*   Updated: 2022/06/20 12:35:33 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_from_file(int fd, char *buffer, char *rest)
{
	char	*temp;
	int		read_file;

	read_file = 1;
	while (read_file)
	{
		read_file = read(fd, buffer, BUFFER_SIZE);
		{
			if (read_file == -1)
				return (0);
			else if (read_file == 0)
				break ;
		}
		buffer[read_file] = '\0';
		if (!rest)
			rest = ft_strdup("");
		temp = rest;
		rest = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

char	*ft_get_line(char *rest)
{
	int		i;
	char	*temp;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		temp[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
	{
		temp[i] = rest[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_save_remainder(char *rest)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(rest) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (rest[i])
		temp[j++] = rest[i++];
	temp[j] = '\0';
	free (rest);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	rest = ft_read_from_file(fd, buffer, rest);
	free(buffer);
	if (!rest)
		return (NULL);
	line = ft_get_line(rest);
	rest = ft_save_remainder(rest);
	return (line);
}
