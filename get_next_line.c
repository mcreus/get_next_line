/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:25:43 by mcreus            #+#    #+#             */
/*   Updated: 2023/03/06 13:45:57 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save)
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = 0;
	free(save);
	return (str);
}

char	*ft_read(int fd, char *save)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read (fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = 0;
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_line(save);
	save = ft_save(save);
	return (line);
}
