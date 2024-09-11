/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hraad <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:23:44 by hraad             #+#    #+#             */
/*   Updated: 2024/09/12 00:39:07 by hraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*read_to_buffer(int fd, char *remaining_text, char *buffer);
static	char	*extract_line(char *buffered_text);
static	char	*find_char(char *str, int ch);

char	*get_next_line(int fd)
{
	static char	*remaining_text;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer || read(fd, 0, 0) < 0)
	{
		free(remaining_text);
		free(buffer);
		remaining_text = NULL;
		return (NULL);
	}
	line = read_to_buffer(fd, remaining_text, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	remaining_text = extract_line(line);
	return (line);
}

static	char	*extract_line(char *buffered_text)
{
	char	*remaining_text;
	int		i;
	int		j;

	i = 0;
	while (buffered_text[i] && buffered_text[i] != '\n')
		i++;
	if (!buffered_text[i] || !buffered_text[i + 1])
		return (NULL);
	j = ft_strlen(buffered_text) - i;
	remaining_text = ft_substr(buffered_text, i + 1, j);
	if (!*remaining_text)
	{
		free(remaining_text);
		remaining_text = NULL;
	}
	buffered_text[i + 1] = 0;
	return (remaining_text);
}

static	char	*read_to_buffer(int fd, char *remaining_text, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remaining_text);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		if (!remaining_text)
			remaining_text = ft_strdup("");
		temp = remaining_text;
		remaining_text = ft_strjoin(temp, buffer);
		free(temp);
		if (find_char(buffer, '\n'))
			break ;
	}
	return (remaining_text);
}

static	char	*find_char(char *str, int ch)
{
	int		i;
	char	target;

	target = (char)ch;
	i = 0;
	while (str[i])
	{
		if (str[i] == target)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
