/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:40:55 by rkaga             #+#    #+#             */
/*   Updated: 2025/02/21 17:08:16 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

unsigned int	count_words(const char *s, char c);
char			*substring(char const *s, unsigned int index, char c);
char			**ft_split(char const *s, char c);
int				ft_strlen(char *s);
char			*ft_join(char *s1, char *s2);
void				exec_cmd(char *path, char **args);
void			free_all(char **arr, unsigned int i);
int				exec(char *cmd);
char *ft_join_with_space(char *s1, char *s2);

#endif
