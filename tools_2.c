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

t_room		*find_room_by_type(t_lem *lem, int type)
{
	t_room	*current;

	current = lem->rooms;
	while (current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_to_print(t_lem *lem, char *str)
{
	t_s		*current;

	if (!lem->print)
	{
		lem->print = (t_s*)ft_memalloc(sizeof(t_s));
		lem->print->str = ft_strdup(str);
		lem->print->next = NULL;
	}
	else
	{
		current = lem->print;
		while (current->next)
			current = current->next;
		current->next = (t_s*)ft_memalloc(sizeof(t_s));
		current->next->str = ft_strdup(str);
		current->next->next = NULL;
	}
}

void	print_map(t_lem *lem)
{
	while (lem->print)
	{
		ft_putstr(lem->print->str);
		write(1, "\n", 1);
		free(lem->print->str);
		lem->print = lem->print->next;
	}
	write(1, "\n", 1);
}

int		check_link(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-')
			count += 1;
		i++;
	}
	return (count);
}

void	piece_of_valid(t_lem *lem, char *str)
{
	if (!str)
		ft_error(NULL, NULL, ER13);
	else if (check_link(str) > 1 || check_link(str) == 0)
		ft_error(str, NULL, ER16);
	else if (!find_room_by_type(lem, 1))
		ft_error(str, NULL, ER11);
	else if (!find_room_by_type(lem, 3))
		ft_error(str, NULL, ER12);
}
