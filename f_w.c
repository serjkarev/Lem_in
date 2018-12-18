/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:04:21 by skarev            #+#    #+#             */
/*   Updated: 2018/12/03 16:04:21 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_ways(t_lem *lem)
{
	int		en;
	int		sn;
	t_w     *w;
	 t_nghbr	*n;
	t_room	*room;

	sn = count_neighbors(find_room_by_type(lem, 1));
	en = count_neighbors(find_room_by_type(lem, 3));
	(sn <= en) ? sn : (sn = en);
	room = find_room_by_type(lem, 3);
	w = lem->ways;
	while (sn > 0)
	{
		n = room->nghbrs;
		while (n->neighbor->visited == 1)
		{
			add_to_ways(n->neighbor, w);
			n = n->neighbor->nghbrs;
		}
		sn--;
		w = w->next;
	}
}

void	add_to_ways(t_room *room, t_w *w)
{
	t_room	*current;
	
	if (!w)
	{
		w = (t_w*)ft_memalloc(sizeof(t_w));
		w->room = room;
		w->room->visited = 0;
		w->next = NULL;
		w->room->next = NULL;
	}
	else
	{
		current = w->room;
		while (current->next)
			current = current->next;
		current->next = (t_room*)ft_memalloc(sizeof(t_room));
		current->next = room;
		current->next->visited = 0;
		current->next->next = NULL;
	}
	
}

int		count_neighbors(t_room *room)
{
	int		ret;
	t_nghbr	*r;

	ret = 0;
	r = room->nghbrs;
	while (r)
	{
		r = r->next;
		ret++;
	}
	return (ret);
}
