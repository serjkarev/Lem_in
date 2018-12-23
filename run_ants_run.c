/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:34:56 by skarev            #+#    #+#             */
/*   Updated: 2018/12/23 13:34:57 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	packs_of_path(t_w *ways)
{
	
}

void	run_ants_run(t_lem *lem)
{
	lem->ways = cut_the_way(lem->ways);
	while (lem->ways)
	{
		printf("%d\n", lem->ways->len);
		print_way(lem->ways->path);
		lem->ways = lem->ways->next;
	}
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