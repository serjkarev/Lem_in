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
	while (get_next_line(0, &str))
	{
		if (!ft_isdigit_str(str))
		{
			lem->ants = ft_atoi(str);
			if (lem->ants <= 0)
				lem->ants == 0 ? ft_error(str, NULL, ER02) : ft_error(str, NULL, ER03);
			free(str);
			break;
		}
		else if (str[0] == '#' && str[1] != '#')
			continue ;
		else if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
			ft_error(str, NULL, ER01);
		else if (lem->ants == 0 && str)
			ft_error(str, NULL, ER04);
	}
}

char	*parse_rooms(t_lem *lem)
{
	char	*str;
	int		type;
	int		det[2];

	det[0] = 0;
	det[1] = 0;
    type = 0;
	while (get_next_line(0, &str))
	{
		if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		{
			(ft_strequ(str, "##start") == 1) ? (type = 1) : (type = 3);
			(ft_strequ(str, "##start") == 1) ? (det[0] += 1) : (det[1] += 1);
			if (det[0] > 1 || det[1] > 1)
				det[0] > 1 ? ft_error(str, NULL, ER07) : ft_error(str, NULL, ER08);
			continue ;
		}
		else if (str[0] == '#' && str[1] != '#')
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
	create_room(arr, lem, type);
	free_arr(arr);
}

void	parse_links(t_lem *lem, char *str)
{
	char	**arr;

	if (str)
	{	
		arr = ft_strsplit(str, '-');
		if (arr[2] != NULL || !arr[0] || !arr[1])
			ft_error(NULL, arr, ER09);
		find_neighbor(lem, arr, 0, 1);
		find_neighbor(lem, arr, 1, 0);
		free_arr(arr);
		free(str);
	}
	while (get_next_line(0, &str))
	{
		arr = ft_strsplit(str, '-');
		if (arr[2] != NULL || !arr[0] || !arr[1])
			ft_error(NULL, arr, ER09);
		find_neighbor(lem, arr, 0, 1);
		find_neighbor(lem, arr, 1, 0);
		free_arr(arr);
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
	create_nghbrs(room, n);
}