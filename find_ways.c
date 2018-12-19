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
	t_q		*queue;
	t_q		*path = NULL;
	t_room	*last;

	queue = (t_q*)ft_memalloc(sizeof(t_q));
	path->room = find_room_by_type(lem, 1);
	queue = q_push_back(queue, path->room);
	while (queue->room)
	{
		path->room = queue->room;
		queue = q_pop(queue);
		last = get_last_elem(path);
		if (last->type == 3)
			add_path_to_ways(lem, path);
		while (last->nghbrs->neighbor)
		{
			if (is_not_visited(last->nghbrs->neighbor, path))
				queue = q_push_back(queue, last->nghbrs->neighbor);
			last->nghbrs->neighbor = last->nghbrs->next->neighbor;
		}
	}
}

int		is_not_visited(t_room *n, t_q *path)
{
	while (path->next)
	{
		if (ft_strequ(path->room->name, n->name))
			return (0);
		path = path->next;
	}
	return (1);
}

void	add_path_to_ways(t_lem *lem, t_q *path)
{
	t_w		*current;

	if (!lem->ways)
	{
		lem->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->ways->path = path;
		lem->ways->next = NULL;
	}
	else
	{
		current = lem->ways;
		while (current->next)
			current = current->next;
		current->next = (t_w*)ft_memalloc(sizeof(t_w));
		current->next->path = path;
		current->next->next = NULL;
	}
}

t_room	*get_last_elem(t_q *path)
{
	t_q	*current;

	current = path;
	while (current->next)
		current->room = current->next->room;
	return (current->room);
}

t_q		*q_push_back(t_q *queue, t_room *room)
{
	t_q		*current;

	current = queue;
	while(current->next)
		current = current->next;
	current->next = (t_q*)ft_memalloc(sizeof(t_q));
	current->next->room = room;
	current->next->next = NULL;
	return (queue);
}

t_q		*q_pop(t_q *queue)
{
	t_q		*head;

	head = queue->next;
	queue = NULL;
	queue = head;
	return(head);
}