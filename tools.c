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
	t_room	*current;

	if (!lem->rooms)
	{
		lem->rooms = (t_room*)ft_memalloc(sizeof(t_room));
		lem->rooms->name = ft_strdup(arr[0]);
		lem->rooms->type = type;
		if (!ft_isdigit_str(arr[1]) && !ft_isdigit_str(arr[2]))
		{
			lem->rooms->x = ft_atoi(arr[1]);
			lem->rooms->y = ft_atoi(arr[2]);
		}
		else
			ft_error(NULL, arr, ER06);
		lem->rooms->next = NULL;
	}
	else
	{
		current = lem->rooms;
		while (current->next)
			current = current->next;
		current->next = (t_room*)ft_memalloc(sizeof(t_room));
		current->next->name = ft_strdup(arr[0]);
		current->next->type = type;
		if (!ft_isdigit_str(arr[1]) && !ft_isdigit_str(arr[2]))
		{
			current->next->x = ft_atoi(arr[1]);
			current->next->y = ft_atoi(arr[2]);
		}
		else
			ft_error(NULL, arr, ER06);
		current->next->next = NULL;
	}
}
