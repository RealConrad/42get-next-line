/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:48:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/05/02 14:12:08 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		i2;

	i = -1;
	i2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[i2])
		str[i++] = s2[i2++];
	str[i] = '\0';
	// printf("STRJOIN(): %s\n", str);
	free(s1);
	return (str);
}

/**
** @brief Searches for the first occurrence of a character in a string
**			and returns a pointer to that character or a null pointer
**			if the character is not found.
** @param s Pointer to the string to be searched
** @param c Character to be located
** @return Returns a pointer to the first occurrence of the character
*/
char	*ft_strchr(const char *s, int c)
{
	char	*ptr_s;

	ptr_s = (char *)s;
	if (!s)
		return (NULL);
	if (*ptr_s == (char)c)
		return (ptr_s);
	while (*ptr_s++)
		if (*ptr_s == (char)c)
			return (ptr_s);
	return (0);
}
