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
	// t_w		*w;
	// t_nghbr	*n;
	t_room	*room;

	sn = count_neighbors(find_room_by_type(lem, 1));
	en = count_neighbors(find_room_by_type(lem, 3));
	(sn <= en) ? sn : (sn = en);
	room = find_room_by_type(lem, 3);
	while (sn > 0)
	{
		get_way(lem, room);
		while (room->nghbrs ||room->nghbrs->neighbor->visited == 0)
			room->nghbrs = room->nghbrs->next;
		lem->ways = lem->ways->next;
		sn--;
	}
}

void	get_way(t_lem *lem, t_room *room)
{
	while (room->type != 1)
	{
		if (room->nghbrs->neighbor->visited == 1)
			add_to_ways(lem, room->nghbrs->neighbor);
		room = room->nghbrs->neighbor;
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

void	add_to_ways(t_lem *lem, t_room *room)
{
	t_room	*current;
	
	if (!lem->ways)
	{
		lem->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->ways->room = room;
		lem->ways->room->visited = 0;
		lem->ways->next = NULL;
		lem->ways->room->next = NULL;
	}
	else
	{
		current = lem->ways->room;
		while (current->next)
			current = current->next;
		current->next = (t_room*)ft_memalloc(sizeof(t_room));
		current->next = room;
		current->next->visited = 0;
		current->next->next = NULL;
	}
	
}