/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:44:28 by skarev            #+#    #+#             */
/*   Updated: 2018/12/07 18:44:28 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_ways(t_lem *lem)
{
	t_w		*queue = NULL;
	t_q		*path = NULL;
	t_room	*room = NULL;
	t_q		*newpath = NULL;
	t_nghbr	*tmp = NULL;
	int flag;

	room = find_room_by_type(lem, 1);
	path = push_back(path, room);
	queue = push(queue, path);
    while (queue)
	{
		flag = 0;
		path = queue->path;
		room = path->tail->room;
		if (room->type == 3)
            add_path_to_ways(lem, path);
		else
			flag = 1;
		tmp = room->nghbrs;
		while (tmp && room->type != 3)
		{
			if (is_not_visited(tmp->neighbor, path))
			{
				newpath = copy_path(path);
				newpath = push_back(newpath, tmp->neighbor);
				queue = push(queue, newpath);
			}
			tmp = tmp->next;
		}
		free_path(queue, flag);
		queue = pop(queue);
	}
}

t_q		*copy_path(t_q *path)
{
	t_q		*newpath = NULL;

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

t_q		*push_back(t_q *path, t_room *room)
{
	if (!path)
	{
		path = (t_q*)malloc(sizeof(t_q));
		path->room = room;
		path->tail = path;
		path->next = NULL;
	}
	else
	{
		path->tail->next = (t_q*)malloc(sizeof(t_q));
		path->tail = path->tail->next;
		path->tail->room = room;
		path->tail->next = NULL;
	}
	return (path);
}

t_w		*push(t_w *queue, t_q *path)
{
	if (!queue)
	{
		queue = (t_w*)malloc(sizeof(t_w));
		queue->path = path;
		queue->tail = queue;
		queue->next = NULL;
	}
	else
	{
		queue->tail->next = (t_w*)malloc(sizeof(t_w));
		queue->tail = queue->tail->next;
		queue->tail->path = path;
		queue->tail->next = NULL;
	}
	return (queue);
}

t_w		*pop(t_w *queue)
{
	t_w		*head;

	if (queue)
	{
		head = queue;
		queue = queue->next;
		if (queue)
		    queue->tail = head->tail;
		free(head);
	}
	return (queue);
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

void	add_path_to_ways(t_lem *lem, t_q *path)
{
	if (!lem->ways)
	{
		lem->ways = (t_w*)malloc(sizeof(t_w));
		lem->ways->path = path;
		lem->ways->tail = lem->ways;
		lem->ways->next = NULL;
	}
	else
	{
		lem->ways->tail->next = (t_w*)malloc(sizeof(t_w));
		lem->ways->tail = lem->ways->tail->next;
		lem->ways->tail->path = path;
		lem->ways->tail->next = NULL;
	}
}

void	print_way(t_q* path)
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
