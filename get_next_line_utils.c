/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:07:56 by lquehec           #+#    #+#             */
/*   Updated: 2023/11/13 21:29:44 by lquehec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **list, char *buffer, int bytes_read)
{
	int		i;
	t_list	*last;
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->content = malloc(sizeof(*buffer) * (bytes_read + 1));
	if (new->content == NULL)
		return ;
	new->next = NULL;
	i = 0;
	while (buffer[i] && i < bytes_read)
	{
		new->content[i] = buffer[i];
		i++;
	}
	new->content[i] = '\0';
	if (*list == NULL)
		*list = new;
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
	}
}

int	ft_lstchr(t_list *stash, char c)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_lstlast(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstfree(t_list *list)
{
	t_list	*current;
	t_list	*backup;

	current = list;
	while (current)
	{
		free(current->content);
		backup = current->next;
		free(current);
		current = backup;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
