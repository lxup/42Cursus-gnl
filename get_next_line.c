/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:07:52 by lquehec           #+#    #+#             */
/*   Updated: 2024/02/12 22:33:39 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(char *s, ssize_t *len)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (*len += i + 1, 1);
	*len += i;
	return (0);
}

void	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		++i;
	}
	if (size)
		dst[i] = 0;
}

int	read_file(int fd, t_string *string)
{
	ssize_t	read_ret;
	ssize_t	ret;
	char	*tmp;

	ret = 0;
	read_ret = BUFFER_SIZE;
	while (!find_nl(string->content + ret, &ret) && read_ret == BUFFER_SIZE)
	{
		if (string->len + BUFFER_SIZE >= string->max_size)
		{
			tmp = malloc(string->max_size * 2);
			if (!tmp)
				return (-1);
			ft_strlcpy_gnl(tmp, string->content, string->len + 1);
			free(string->content);
			string->content = tmp;
			string->max_size *= 2;
		}
		read_ret = read(fd, string->content + string->len, BUFFER_SIZE);
		if (read_ret == -1)
			return (-1);
		string->len += read_ret;
		string->content[string->len] = 0;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	ssize_t		line_len;
	char		*ret;
	t_string	string;
	static char	save[BUFFER_SIZE] = {0};

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	string.max_size = BUFFER_SIZE + 1;
	string.content = malloc(string.max_size);
	if (!string.content)
		return (NULL);
	string.len = 0;
	while (save[string.len])
		string.len++;
	ft_strlcpy_gnl(string.content, save, string.len + 1);
	line_len = read_file(fd, &string);
	if (line_len == -1 || !*string.content)
		return (free(string.content), NULL);
	ret = malloc(line_len + 1);
	if (!ret)
		return (free(string.content), NULL);
	ft_strlcpy_gnl(ret, string.content, line_len + 1);
	ft_strlcpy_gnl(save, string.content + line_len, string.len - line_len + 1);
	return (free(string.content), ret);
}
