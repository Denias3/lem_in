/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:12:31 by emeha             #+#    #+#             */
/*   Updated: 2018/12/17 14:08:37 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static int		ft_searchchar(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

static int		get_collect2_line(char **line, char *buf, t_list **list, int nd)
{
	char	*tmp;
	int		cut;

	if ((nd = ft_searchchar((*list)->content, '\n')) != -1)
	{
		tmp = *line;
		*line = ft_strsub((*list)->content, 0, nd);
		free(tmp);
		tmp = (*list)->content;
		(*list)->content = ft_strjoin((*list)->content, buf);
		free(tmp);
		tmp = (*list)->content;
		if ((cut = ft_searchchar((*list)->content, '\n')) > -1)
			(*list)->content = ft_strsub((*list)->content, cut + 1,
				ft_strlen((*list)->content) - cut - 1);
		free(tmp);
		return (1);
	}
	else
	{
		tmp = (*list)->content;
		(*list)->content = ft_strjoin((*list)->content, buf);
		free(tmp);
	}
	return (0);
}

static int		get_collect_line(int ret, char **line, char *buf, t_list **list)
{
	int		cut;
	char	*tmp;
	int		nd;

	nd = 0;
	buf[ret] = '\0';
	if (get_collect2_line(line, buf, list, nd))
		return (1);
	if (ret == 0)
	{
		tmp = *line;
		*line = ft_strdup((*list)->content);
		free(tmp);
		tmp = (*list)->content;
		if ((cut = ft_searchchar((*list)->content, '\0')) > -1)
			(*list)->content = ft_strsub((*list)->content,\
				cut + 1, ft_strlen((*list)->content) - cut);
		free(tmp);
		return (1);
	}
	return (0);
}

static t_list	*search_fd(t_list **start, int fd)
{
	t_list	*temp;
	t_list	*node;

	if (*start == NULL)
	{
		*start = ft_lstnew("", 1);
		(*start)->content_size = fd;
		return (*start);
	}
	else
	{
		temp = *start;
		while (temp != NULL)
		{
			if ((int)temp->content_size == fd)
				return (temp);
			temp = temp->next;
		}
		node = ft_lstnew("", 1);
		node->content_size = fd;
		ft_lstadd(start, node);
		return (node);
	}
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*start;
	t_list			*list;

	if (fd != -1 && line != NULL)
	{
		*line = ft_strnew(0);
		list = search_fd(&start, fd);
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0\
			|| 0 != ft_strlen(list->content))
		{
			buf[ret] = '\0';
			if (get_collect_line(ret, line, buf, &list))
				return (1);
		}
		free(*line);
		if (ret == -1)
			return (-1);
		return (0);
	}
	return (-1);
}
