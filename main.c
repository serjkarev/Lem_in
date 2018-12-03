/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:42:36 by skarev            #+#    #+#             */
/*   Updated: 2018/11/01 14:42:36 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	char	*str;
	t_lem	*lem;

	str = NULL;
	lem = (t_lem*)ft_memalloc(sizeof(t_lem));
	init_lem(lem);
	parse_ants(lem);
	str = parse_rooms(lem);
	parse_links(lem, str);
	bfs(lem);
	// system("leaks -q lem-in");
	printf("ants = %d\n", lem->ants);
	return (0);
}

// void	bfs(t_lem *lem)
// {
// 	t_room	*start;
// 	t_room	*current;
// 	t_room	*tmp;
	
// 	start = find_start_room(lem);
// 	start->visited = 1;
// 	add_to_queue(lem, start);
// 	while (!is_empty(lem->queue))
// 	{
// 		current = dell_from_queue(lem->queue);
// 		tmp = current;
// 		while (tmp)
// 		{
// 			if (tmp->visited == 0)
// 			{
// 				tmp->visited = 1;
// 				add_to_queue(lem, tmp);
// 			}
// 			tmp = tmp->nghbrs->neighbor;
// 		}
// 	}
// }

// void	add_to_queue(t_lem *lem, t_room *room)
// {
// 	t_nghbr	*temp;

// 	if (!lem->queue)
// 	{
// 		lem->queue = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
// 		lem->queue->neighbor = room;
// 		// room->visited = 1;
// 		lem->queue->next = NULL;
// 		lem->queue->prev = NULL;
// 	}
// 	else
// 	{
// 		while (lem->queue)
// 		{
// 			temp = lem->queue;
// 			lem->queue = lem->queue->next;
// 		}
// 		lem->queue = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
// 		lem->queue->neighbor = room;
// 		lem->queue->next = NULL;
// 		lem->queue->prev = temp;
// 		temp->next = lem->queue;
// 	}
// }

// t_room	*dell_from_queue(t_nghbr *q)
// {
// 	t_room	*tmp;

// 	if (!q)
// 		return (NULL);
// 	tmp = q->neighbor;
// 	q = q->next;
// 	return (tmp);
// }