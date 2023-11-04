/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:42:17 by lquehec           #+#    #+#             */
/*   Updated: 2023/10/16 18:42:17 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstclean(t_list **list)
{
	int		i;
	int		j;
	t_list	*last;
	t_list	*clean;

	clean = (t_list *)malloc(sizeof(t_list));
	if (list == NULL || clean == NULL)
		return ;
	clean->next = NULL;
	last = ft_lstlast(*list);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char) *((ft_strlen(last->content) - i) + 1));
	if (clean->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	ft_lstfree(*list);
	*list = clean;
}

void	ft_get_line(t_list *list, char **line)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	ft_create_line(list, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				(*line)[j++] = list->content[i];
				break ;
			}
			(*line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
}

void	ft_create_line(t_list *list, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*line = (char *)malloc(sizeof(char) * (len + 1));
}

void	read_and_stash(int fd, t_list **list, int *bytes_read)
{
	char	*buffer;

	while (!ft_lstchr(*list, '\n') && *bytes_read != 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		*bytes_read = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*list == NULL && *bytes_read == 0) || *bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[*bytes_read] = '\0';
		ft_lstadd_back(list, buffer, *bytes_read);
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || (int)read(fd, &line, 0) < 0)
		return (NULL);
	bytes_read = 1;
	line = NULL;
	read_and_stash(fd, &list, &bytes_read);
	if (list == NULL)
		return (NULL);
	ft_get_line(list, &line);
	ft_lstclean(&list);
	if (*line == '\0')
	{
		ft_lstfree(list);
		list = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	#include <stdio.h>

// 	int		fd;
// 	char	*line;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd < 0) 
// 		return (1);
// 	line = get_next_line(fd);
// 	printf("Ligne: %s\n", line);
// 	free(line);
// 	return (0);
// }