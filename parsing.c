/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:22:02 by skarev            #+#    #+#             */
/*   Updated: 2018/11/15 15:22:02 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_ants(t_lem *lem)
{
	char	*str;

	lem->ants = 0;
	lem->rn = 0;
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (!ft_isdigit_str(str))
		{
			lem->ants = ft_atoi(str);
			if (lem->ants <= 0)
				lem->ants == 0 ? ft_error(str, NULL, ER02) : \
												ft_error(str, NULL, ER03);
			free(str);
			break ;
		}
		else if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
			ft_error(str, NULL, ER01);
		else if (str[0] == '#')
			free(str);
		else if (lem->ants == 0 && str)
			ft_error(str, NULL, ER04);
	}
	if (lem->ants == 0)
		ft_error(str, NULL, ER02);
}

char	*parse_rooms(t_lem *lem)
{
	char	*str;
	int		type;
	int		det[2];

	*((unsigned long int *)det) = 0;
	type = 0;
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
			parce_rooms_v2(&det[0], &det[1], str, &type);
		else if (str[0] == '#')
			free(str);
		else if (space_detect(str) == 2)
		{
			parse_room(str, lem, type);
			type = 0;
		}
		else
			return (str);
	}
	return (str);
}

void	parse_links(t_lem *lem, char *str)
{
	if (str)
	{
		parce_links_v2(str, lem);
		free(str);
	}
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (str[0] != '#')
			parce_links_v2(str, lem);
		free(str);
	}
}

void	find_neighbor(t_lem *lem, char **arr, int n1, int n2)
{
	t_room	*room;
	t_room	*n;

	room = get_room_by_name(lem, arr[n1]);
	n = get_room_by_name(lem, arr[n2]);
	if (room == NULL || n == NULL)
		ft_error(NULL, arr, ER10);
	if (check_nghbrs(room->nghbrs, n->name))
		create_nghbrs(room, n);
}

int		check_nghbrs(t_nghbr *ns, char *name)
{
	t_nghbr		*head;

	head = ns;
	while (head)
	{
		if (head->neighbor->name == name)
			return (0);
		head = head->next;
	}
	return (1);
}
