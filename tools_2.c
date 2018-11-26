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
		tmp = tmp->prev;
		
	}
	return (NULL);
}

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_nghbr	*create_nghbrs(char **arr, t_room *room, t_room *n)
{
	t_nghbr	*nghbrs;
	t_nghbr	*temp;

	if (!arr)
		return (NULL);
	if (!room->nghbrs)
	{
		if (!(nghbrs = (t_nghbr*)ft_memalloc(sizeof(t_nghbr))))
			return (NULL);
		nghbrs->neighbor = n;
		nghbrs->next = NULL;
		nghbrs->prev = NULL;
	}
	else
	{
	    nghbrs = room->nghbrs;
		while (nghbrs)
		{
			temp = nghbrs;
			nghbrs = nghbrs->next;
		}
		if (!(nghbrs = (t_nghbr*)ft_memalloc(sizeof(t_nghbr))))
			return (NULL);
		nghbrs->neighbor = n;
		nghbrs->next = NULL;
		nghbrs->prev = temp;
		temp->next = nghbrs;
	}
	return (nghbrs);
}