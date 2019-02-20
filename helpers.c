/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:46:14 by skarev            #+#    #+#             */
/*   Updated: 2019/01/27 16:46:14 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_room(char *str, t_lem *lem, int type)
{
	int		space;
	char	**arr;

	lem->rn += 1;
	space = space_detect(str);
	arr = ft_strsplit(str, ' ');
	if (arr[3] != NULL || space != 2 || !arr[0] || !arr[1] || !arr[2] ||\
						ft_strchr(arr[0], '-') != NULL || arr[0][0] == 'L')
		ft_error(str, arr, ER05);
	if (get_room_by_name(lem, arr[0]))
		ft_error(str, arr, ER15);
	create_room(arr, lem, type);
	free_arr(arr);
	free(str);
}

void	parce_rooms_v2(int *det0, int *det1, char *str, int *type)
{
	(ft_strequ(str, "##start") == 1) ? (*type = 1) : \
													(*type = 3);
	(ft_strequ(str, "##start") == 1) ? (*det0 += 1) : (*det1 += 1);
	if (*det0 > 1 || *det1 > 1)
		*det0 > 1 ? ft_error(str, NULL, ER07) : ft_error(str, NULL, ER08);
	free(str);
}

void	parce_links_v2(char *str, t_lem *lem)
{
	char	**arr;

	arr = ft_strsplit(str, '-');
	if (arr[2] != NULL || !arr[0] || !arr[1] || check_link(str) > 1)
		ft_error(NULL, arr, ER09);
	find_neighbor(lem, arr, 0, 1);
	find_neighbor(lem, arr, 1, 0);
	free_arr(arr);
}

void	create_room_v2(char **arr, t_room *rooms)
{
	if (!ft_isdigit_str(arr[1]) && !ft_isdigit_str(arr[2]))
	{
		rooms->x = ft_atoi(arr[1]);
		rooms->y = ft_atoi(arr[2]);
	}
	else
		ft_error(NULL, arr, ER06);
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
