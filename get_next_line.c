/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:43:40 by aaghbal           #+#    #+#             */
/*   Updated: 2022/11/11 16:35:27 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0')
		p[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}

char	*ft_join(char *reserve, char *buf)
{
	char	*temp;

	temp = ft_strjoin(reserve, buf);
	free(reserve);
	return (temp);
}

char	*ft_readfile(int fd, char *reserve)
{
	char	*buffer;
	int		br;

	if (!reserve)
		reserve = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	br = 1;
	while (br > 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[br] = '\0';
		reserve = ft_join(reserve, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	line = NULL;
	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, line, 0) == -1)
		return (NULL);
	reserve = ft_readfile(fd, reserve);
	if (!reserve)
		return (NULL);
	line = ft_line(reserve);
	reserve = ft_next(reserve);
	return (line);
}
