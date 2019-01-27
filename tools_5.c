/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 19:37:53 by skarev            #+#    #+#             */
/*   Updated: 2019/01/27 19:37:53 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


t_q		*copy_path(t_q *path)
{
	t_q		*newpath;

	newpath = NULL;
	while (path)
	{
		newpath = push_back(newpath, path->room);
		path = path->next;
	}
	return (newpath);
}

void	free_path(t_w *queue, int flag)
{
	t_q	*buf;

	if (flag)
	{
		while (queue->path)
		{
			buf = queue->path;
			buf = buf->next;
			free(queue->path);
			queue->path = buf;
		}
	}
}

int		is_not_visited(t_room *n, t_q *path)
{
	while (path)
	{
		if (path->room == n)
			return (0);
		path = path->next;
	}
	return (1);
}

void	print_way(t_q *path)
{
	while (path)
	{
		if (path->next)
			printf("%s -> ", path->room->name);
		else
			printf("%s", path->room->name);
		path = path->next;
	}
	printf("\n");
}
