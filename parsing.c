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
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (!ft_isdigit_str(str))
		{
			lem->ants = ft_atoi(str);
			if (lem->ants <= 0)
				lem->ants == 0 ? ft_error(str, NULL, ER02) : ft_error(str, NULL, ER03);
			free(str);
			break ;
		}
		else if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
			ft_error(str, NULL, ER01);
		else if (str[0] == '#')
			continue ;
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

	det[0] = 0;
	det[1] = 0;
	type = 0;
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		{
			(ft_strequ(str, "##start") == 1) ? (type = 1) : (type = 3);
			(ft_strequ(str, "##start") == 1) ? (det[0] += 1) : (det[1] += 1);
			if (det[0] > 1 || det[1] > 1)
				det[0] > 1 ? ft_error(str, NULL, ER07) : ft_error(str, NULL, ER08);
			continue ;
		}
		else if (str[0] == '#')
			continue ;
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

void	parse_room(char *str, t_lem *lem, int type)
{
	int		space;
	char	**arr;

	space = space_detect(str);
	arr = ft_strsplit(str, ' ');
	if (arr[3] != NULL || space != 2 || !arr[0] || !arr[1] || !arr[2] ||\
										ft_strchr(arr[0], '-') != NULL)
		ft_error(str, arr, ER05);
	if (get_room_by_name(lem, arr[0]))
		ft_error(str, arr, ER15);
	create_room(arr, lem, type);
	free_arr(arr);
}

void	parse_links(t_lem *lem, char *str)
{
	char	**arr;

	if (str)
	{
		add_to_print(lem, str);
		arr = ft_strsplit(str, '-');
		if (arr[2] != NULL || !arr[0] || !arr[1] || check_link(str) > 1)
			ft_error(NULL, arr, ER09);
		find_neighbor(lem, arr, 0, 1);
		find_neighbor(lem, arr, 1, 0);
		free_arr(arr);
		free(str);
	}
	while (lgnl(0, &str))
	{
		add_to_print(lem, str);
		if (str[0] != '#')
		{
			arr = ft_strsplit(str, '-');
			if (arr[2] != NULL || !arr[0] || !arr[1] || check_link(str) > 1)
				ft_error(NULL, arr, ER09);
			find_neighbor(lem, arr, 0, 1);
			find_neighbor(lem, arr, 1, 0);
			free_arr(arr);
			free(str);
		}
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
		if (ft_strequ(head->neighbor->name, name))
			return (0);
		head = head->next;
	}
	return (1);
}
