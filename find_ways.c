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

void	jopa(t_lem *lem)
{
	t_q		*queue = NULL;
	t_room	*current;

	current = find_room_by_type(lem, 1);
	queue = q_push_back(queue, current);
	while (queue)
	{
		current = queue->room;
		queue = q_pop(queue);
		// if (current->type == 3)
			//добавить путь в список путей
		
	}
}

t_q		*q_push_back(t_q *queue, t_room *room)
{
	t_q		*current;

	if(!queue)
	{
		queue = (t_q*)ft_memalloc(sizeof(t_q));
		queue->room = room;
		queue->next = NULL;
	}
	else
	{
		current = queue;
		while(current->next)
			current = current->next;
		current->next = (t_q*)ft_memalloc(sizeof(t_q));
		current->next->room = room;
		current->next->next = NULL;
	}
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