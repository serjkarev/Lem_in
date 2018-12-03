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
	// t_w		*ways;
	// t_nghbr	*n;
	t_room	*room;

	sn = count_neighbors(find_room_by_type(lem, 1));
	en = count_neighbors(find_room_by_type(lem, 3));
	(sn <= en) ? sn : (sn = en);
	room = find_room_by_type(lem, 3);
	while (sn > 0)
	{
		if (room->nghbrs->neighbor->visited == 1)
			add_to_ways(lem, room->nghbrs->neighbor);
		room->nghbrs->neighbor = room->nghbrs->next->neighbor;
		sn--;
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
	t_w	*current;
	
	if (!lem->ways)
	{
		lem->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->ways->room = room;
		lem->ways->next = NULL;
	}
	else
	{
		current = lem->ways;
		while (current->next)
			current = current->next;
		current->next = (t_w*)ft_memalloc(sizeof(t_w));
		current->next->room = room;
		current->next->next = NULL;
	}
	
}