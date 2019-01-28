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

void	find_ways_v2(t_lem *lem)//еще нужно доработать test1 не совсем коректно находит ебучие пути
{
	t_w		*queue;
	t_q		*path;
	t_room	*room;
	t_q		*newpath;
	t_nghbr	*tmp;

	queue = NULL;
	path = NULL;
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
		queue = pop(queue, lem->flag);
	}
}
