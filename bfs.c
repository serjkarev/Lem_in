/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:11:34 by skarev            #+#    #+#             */
/*   Updated: 2018/11/20 11:11:34 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	bfs(t_lem *lem)
{
	t_room	*start;
	t_room	*current;
	t_room	*tmp;
	
	start = find_start_room(lem);
	start->visited = 1;
	add_to_queue(lem, start);
	while (!is_empty(lem->queue))
	{
		current = dell_from_queue(lem->queue);
		tmp = current;
		while (tmp)
		{
			if (tmp->visited == 0)
			{
				tmp->visited = 1;
				add_to_queue(lem, tmp);
			}
			tmp = tmp->nghbrs->neighbor;
		}
	}
}

t_room	*find_start_room(t_lem *lem)
{
	while (lem->rooms)
	{
		if (lem->rooms->type == 1)
			return (lem->rooms);
		// lem->rooms = lem->rooms->prev;
	}
	return (NULL);
}

void	add_to_queue(t_lem *lem, t_room *room)
{
	t_nghbr	*temp;

	if (!lem->queue)
	{
		lem->queue = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		lem->queue->neighbor = room;
		// room->visited = 1;
		lem->queue->next = NULL;
		lem->queue->prev = NULL;
	}
	else
	{
		while (lem->queue)
		{
			temp = lem->queue;
			lem->queue = lem->queue->next;
		}
		lem->queue = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		lem->queue->neighbor = room;
		lem->queue->next = NULL;
		lem->queue->prev = temp;
		temp->next = lem->queue;
	}
}

int		is_empty(t_nghbr *queue)
{
	if (!queue->neighbor)
		return (1);
	return (0);
}

t_room	*dell_from_queue(t_nghbr *q)
{
	t_room	*tmp;

	if (!q)
		return (NULL);
	tmp = q->neighbor;
	q = q->next;
	return (tmp);
}