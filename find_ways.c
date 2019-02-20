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
	t_w		*queue;
	t_q		*path;
	t_room	*room;
	t_q		*newpath;

	queue = NULL;
	path = NULL;
	newpath = NULL;
	room = find_room_by_type(lem, 1);
	path = push_back(path, room);
	queue = push(queue, path);
	while (queue)
	{
		lem->flag = 0;
		path = queue->path;
		room = path->tail->room;
		if (room->type == 3)
			add_path_to_ways(lem, path);
		else
			lem->flag = 1;
		find_ways_h(room, path, newpath, queue);
		queue = pop(queue, lem->flag);
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

t_w		*pop(t_w *queue, int flag)
{
	t_w		*head;

	free_path(queue, flag);
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
