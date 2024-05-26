/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:40:09 by zderfouf          #+#    #+#             */
/*   Updated: 2024/01/17 15:29:21 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*preserve(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	new_str = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!new_str)
		return (free(str), str = NULL, NULL);
	i++;
	j = 0;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (free(str), str = NULL, new_str);
}

char	*new_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	return (line[i] = '\0', line);
}

char	*read_line(int fd, char *str)
{
	char	*tempo;
	int		n_byte;

	n_byte = 1;
	tempo = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!tempo)
		return (free(str), str = NULL, NULL);
	while (!ft_strchr(str, '\n') && n_byte != 0)
	{
		n_byte = read(fd, tempo, BUFFER_SIZE);
		if (n_byte == -1)
			return (free(str), free(tempo), NULL);
		tempo[n_byte] = '\0';
		str = ft_strjoin(str, tempo);
		if (!str)
			break ;
	}
	return (free (tempo), str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!str[fd])
		str[fd] = ft_strdup("");
	if (!str[fd])
		return (NULL);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = new_line(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = preserve(str[fd]);
	return (line);
}
