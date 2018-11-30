/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:18:33 by skarev            #+#    #+#             */
/*   Updated: 2018/11/15 15:18:33 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*get_room_by_name(t_lem *lem, char *name)
{
	t_room	*tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
		
	}
	return (NULL);
}

void	create_nghbrs(t_room *room, t_room *n)
{
	t_nghbr	*current;

	if (!room->nghbrs)
	{
		room->nghbrs = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		room->nghbrs->neighbor = n;
		room->nghbrs->next = NULL;
	}
	else
	{
	    current = room->nghbrs;
		while (current->next)
			current = current->next;
		current->next = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		current->next->neighbor = n;
		current->next->next = NULL;
	}
}