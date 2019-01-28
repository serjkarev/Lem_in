/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:30:49 by skarev            #+#    #+#             */
/*   Updated: 2018/11/02 14:30:49 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error(char *str, char **arr, char *error)
{
	ft_putstr_fd(error, 2);
	if (str)
		free(str);
	else if (arr)
		free_arr(arr);
	exit(1);
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

int		ft_isdigit_str(char *str)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
	{
		i++;
		d++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			d++;
		i++;
	}
	return (i - d);
}

int		space_detect(char *str)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (str[i])
		if (str[i++] == ' ')
			space++;
	return (space);
}

void	create_room(char **arr, t_lem *lem, int type)
{
	if (!lem->rooms)
	{
		lem->rooms = (t_room*)ft_memalloc(sizeof(t_room));
		lem->rooms->name = ft_strdup(arr[0]);
		lem->rooms->type = type;
		lem->rooms->visited = 0;
		create_room_v2(arr, lem->rooms);
		lem->rooms->tail = lem->rooms;
		lem->rooms->tail->next = NULL;
	}
	else
	{
		lem->rooms->tail->next = (t_room*)ft_memalloc(sizeof(t_room));
		lem->rooms->tail = lem->rooms->tail->next;
		lem->rooms->tail->name = ft_strdup(arr[0]);
		lem->rooms->tail->type = type;
		lem->rooms->tail->visited = 0;
		create_room_v2(arr, lem->rooms->tail);
		lem->rooms->tail->next = NULL;
	}
}
