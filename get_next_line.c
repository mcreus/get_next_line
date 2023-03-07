/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:43 by mcreus            #+#    #+#             */
/*   Updated: 2023/03/07 12:07:31 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_function(int fd, char *buffer, char *save)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!save)
			save = ft_strdup("");
		char_temp = save;
		save = ft_strjoin(char_temp, buffer);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (save);
}

static char	*ft_save(char *line)
{
	size_t	count;
	char	*save;

	count = 0;
	while (line[count] != '\n' && line[count])
		count++;
	if (!line[count] || line[1] == '\0')
		return (0);
	save = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (!*save)
	{
		free(save);
		save = NULL;
	}
	line[count + 1] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = ft_function(fd, buffer, save);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	save = ft_save(line);
	return (line);
}
