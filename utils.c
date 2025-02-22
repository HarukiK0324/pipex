/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:51:09 by haruki            #+#    #+#             */
/*   Updated: 2025/02/21 17:34:10 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

char *ft_join(char *s1, char *s2)
{
    char *str;
    int i;

    i = 0;
    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return (NULL);
    while(s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;
    }
    while(*s2 != '\0')
    {
        str[i] = *s2;
        i++;
        s2++;
    }
    str[i] = '\0';
    return (str);
}

unsigned int	count_words(const char *s, char c)
{
	unsigned int	count;
	unsigned int	in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

char	*substring(char const *s, unsigned int index, char c)
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	len = 0;
	i = 0;
	while (s[index + len] != '\0' && s[index + len] != c)
		len++;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[index + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_all(char **arr, unsigned int i)
{
	unsigned int	index;

	index = 0;
	while (index < i)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	index;

	i = 0;
	index = 0;
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (i < count_words(s, c))
	{
		while (s[index] == c)
			index++;
		arr[i] = substring(s, index, c);
		if (arr[i] == NULL)
		{
			free_all(arr, i);
			return (NULL);
		}
		index += ft_strlen(arr[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char *ft_join_with_space(char *s1,char *s2)
{
    char *str;
    int i;

    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
    i = 0;
    if (!str)
        return (NULL);
    while(s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = ' ';
    i++;
    while(*s2 != '\0')
    {
        str[i] = *s2;
        i++;
        s2++;
    }
    str[i] = '\0';
    free(s1);
    return (str);
}
