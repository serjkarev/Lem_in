/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:30:02 by skarev            #+#    #+#             */
/*   Updated: 2019/01/28 17:30:02 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		find_ways_v2h(t_room *room, t_q *path, t_q *newpath, t_w *queue)
{
	t_nghbr	*tmp;

	tmp = room->nghbrs;
	while (tmp && room->type != 3)
	{
		if (is_not_visited(tmp->neighbor, path) && tmp->neighbor->visited == 0)
		{
			if (tmp->neighbor->type != 1 && tmp->neighbor->type != 3)
				tmp->neighbor->visited = 1;
			newpath = copy_path(path);
			newpath = push_back(newpath, tmp->neighbor);
			queue = push(queue, newpath);
		}
		tmp = tmp->next;
	}
}

void		find_ways_v2(t_lem *lem)
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
		find_ways_v2h(room, path, newpath, queue);
		queue = pop(queue, lem->flag);
	}
}

void		find_ways_h(t_room *room, t_q *path, t_q *newpath, t_w *queue)
{
	t_nghbr	*tmp;

	tmp = room->nghbrs;
	while (tmp && room->type != 3)
	{
		if (is_not_visited(tmp->neighbor, path) && tmp->neighbor->visited == 0)
		{
			newpath = copy_path(path);
			newpath = push_back(newpath, tmp->neighbor);
			queue = push(queue, newpath);
		}
		tmp = tmp->next;
	}
}
