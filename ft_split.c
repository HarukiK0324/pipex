// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_split.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/09 16:46:39 by hkasamat          #+#    #+#             */
// /*   Updated: 2025/02/25 23:40:56 by haruki           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// int ft_strlen(char *str)
// {
// 	int len;

// 	len = 0;
// 	if(str == NULL)
// 		return 0;
// 	while(str[len] != '\0')
// 		len++;
// 	return len;
// }

// static unsigned int	count_words(const char *s, char c)
// {
// 	unsigned int	count;
// 	unsigned int	in_word;

// 	count = 0;
// 	in_word = 0;
// 	while (*s != '\0')
// 	{
// 		if (*s == c)
// 			in_word = 0;
// 		else if (!in_word)
// 		{
// 			in_word = 1;
// 			count++;
// 		}
// 		s++;
// 	}
// 	return (count);
// }

// static char	*substring(char const *s, unsigned int index, char c)
// {
// 	unsigned int	len;
// 	unsigned int	i;
// 	char			*str;

// 	len = 0;
// 	i = 0;
// 	while (s[index + len] != '\0' && s[index + len] != c)
// 		len++;
// 	str = malloc(len + 1);
// 	if (str == (void *)0)
// 		return ((void *)0);
// 	while (i < len)
// 	{
// 		str[i] = s[index + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// static void	free_all(char **arr, unsigned int i)
// {
// 	unsigned int	index;

// 	index = 0;
// 	while (index < i)
// 	{
// 		free(arr[index]);
// 		index++;
// 	}
// 	free(arr);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char			**arr;
// 	unsigned int	i;
// 	unsigned int	index;

// 	i = 0;
// 	index = 0;
// 	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (arr == (void *)0)
// 		return ((void *)0);
// 	while (i < count_words(s, c))
// 	{
// 		while (s[index] == c)
// 			index++;
// 		arr[i] = substring(s, index, c);
// 		if (arr[i] == (void *)0)
// 		{
// 			free_all(arr, i);
// 			return ((void *)0);
// 		}
// 		index += ft_strlen(arr[i]);
// 		i++;
// 	}
// 	arr[i] = (void *)0;
// 	return (arr);
// }
