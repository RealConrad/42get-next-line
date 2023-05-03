/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:48:29 by cwenz             #+#    #+#             */
/*   Updated: 2023/05/02 19:20:55 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
** @brief Extracts one line at a time from a 
**	text file the file descriptor is pointing to
** @param fd The file descriptor to read from
** @return
*/
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	// buffer = NULL; // THIS THING HERE AHHHHHHHHHHHHHH
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = get_current_line(buffer, fd);
	if (!buffer)
		return (NULL);
	line = set_current_line(buffer);
	buffer = free_upto(buffer); // Free up static char
	return (line);
}

char	*get_current_line(char *buffer, int fd)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while ((!ft_strchr(buffer, '\n') && bytes_read != 0) || (bytes_read == BUFFER_SIZE && buffer[ft_strlen(buffer) - 1] != '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			temp = NULL;
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
	}
	free(temp);
	return (buffer);
}


char	*set_current_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = str[i];
	if (line[i] != '\0')
		line[++i] = '\0';
	return (line);
}
char	*free_upto(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	// Skip over everything until find newline
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	i++;
	// Since we found a newline, assign rest of chars to temp variable
	temp = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (!temp)
		return (free(str), NULL);
	// i++;
	while (str[i])
		temp[j++] = str[i++];
	temp[j] = '\0';
	free(str);
	return (temp); // Return the temp value (everything after newline)
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("\n");
	return (0);
}
