/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:08:17 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/08 12:21:15 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	ft_lstfree(t_list *list);
void	ft_lstclean(t_list **list);
void	ft_get_line(t_list *list, char **line);
void	ft_create_line(t_list *list, char **line);
void	read_and_stash(int fd, t_list **list, int *bytes_read);
void	ft_lstadd_back(t_list **list, char *buffer, int bytes_read);

// Utils
size_t	ft_strlen(const char *s);
int		ft_lstchr(t_list *stash, char c);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content, size_t size);

#endif