/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:24:55 by skarev            #+#    #+#             */
/*   Updated: 2019/01/27 17:24:55 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_w		*cut_the_way(t_w *ways)
{
	t_w		*head;
	t_q		*tmp;

	head = ways;
	while (ways)
	{
		if (ways->path)
		{
			tmp = ways->path;
			ways->path = ways->path->next;
			free(tmp);
			ways->len = way_len(ways->path);
		}
		ways->block = 0;
		ways->flow = 0;
		ways = ways->next;
	}
	return (head);
}

int		way_len(t_q *path)
{
	int		len;
	t_q		*tmp;

	len = 0;
	tmp = path;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

int		not_in_pack(t_w *ways, t_q *path)
{
	while (ways)
	{
		if (have_same_room(ways->path, path))
			return (0);
		ways = ways->next;
	}
	return (1);
}

void	init_new_pack(t_w *ways, int len)
{
	ways->flow = len;
	ways->len = len;
	ways->num_of_path = 1;
}
