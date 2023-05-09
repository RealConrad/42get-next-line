/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:48:29 by cwenz             #+#    #+#             */
/*   Updated: 2023/05/09 12:26:12 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
--------HOW BONUS WORKS--------
The function can manage separate internal states for each file descriptor, 
enabling you to read from different file descriptors in any order without 
mixing up the data between them
For example, if you have three file descriptors, fd3, fd4, and fd5, you can call get_next_line() in the following order:
	1. get_next_line(fd3) - reads a line from fd3
	2. get_next_line(fd4) - reads a line from fd4
	3. get_next_line(fd5) - reads a line from fd5
	4. get_next_line(fd3) - reads the next line from fd3
	5. get_next_line(fd4) - reads the next line from fd4
	6. get_next_line(fd5) - reads the next line from fd5
	7. etc...

Despite the interleaved calls to read from different file descriptors, it maintains
the reading position for each file descriptor and doesn't lose track of the reading context.
*/


/**
 * @brief Extracts one line at a time from a text file
 *  the file descriptor is pointing to and allocates
 *  dynamically, which must be freed by the caller. Stops reading 
 *  at the first newline character or EOF (End of file).
 * @param fd The file descriptor to read from
 * @return A pointer to the newly allocated null-terminated string 
 *  containing the newline, or NULL if the input fd fails, BUFFER_SIZE 
 *  is less than 1, the EOF has been reached.
*/
char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer[fd] = get_current_line(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = set_current_line(buffer[fd]);
	if (line[0] == '\0' && !ft_strchr(buffer[fd], '\n'))
	{
		free(line);
		buffer[fd] = free_upto(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = free_upto(buffer[fd]);
	return (line);
}

/**
 * @brief Reads from a file descriptor until a newline 
 *  character is found or if end of file has been reached. 
 *  It reads in chunks of BUFFER_SIZE and appends
 *  the content to the input buffer variable.
 * @param buffer The null-terminated input buffer to append content to.
 * @param fd The file descriptor to read from.
 * @return A pointer to the updated input buffer containing the 
 *  newly appended contetn, or NULL if read() fails or 
 *  if the end of file has been reached.
*/
char	*get_current_line(char *buffer, int fd)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while ((!ft_strchr(buffer, '\n') && bytes_read != 0))
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

/**
 * @brief Extracts the current line from a null terminated 
 *  string up to and including the newline character and 
 *  assigns to a variable. 
 *  The strings memory is dynamically allocated,
 *  but must be freed by the caller to avoid memory leaks.
 *  @param str The null terminated string to extract a line from.
 * @return A pointer to the newly created string containing all 
 *  characters up to and including the newline or NULL 
 *  on allocation or if the input string (str) is NULL.
*/
char	*set_current_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
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
	if (line[i])
		line[++i] = '\0';
	return (line);
}

/**
 * @brief Frees memory allocated for a string up to the 
 *  first newline character and returns the remaining 
 *  part of the string. This function takes a null terminated 
 *  string and searches for the first newline character and 
 *  creates a new string with the remaining characters after the newline. 
 *  The original memory is freed. The new string's memory is 
 *  dynamically calculated, but must be freed by the caller after
 *  use to avoid memory leaks.
 * @param str The null-terminated string to check.
 * @return A pointer to the newly allocated string containing everything 
 *  after the first found newline character, or NULL on allocation or 
 *  if no newline is found.
*/
char	*free_upto(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	i++;
	temp = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (!temp)
		return (free(str), NULL);
	while (str[i])
		temp[j++] = str[i++];
	temp[j] = '\0';
	free(str);
	return (temp);
}
