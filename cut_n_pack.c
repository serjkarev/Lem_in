/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_n_pack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:34:56 by skarev            #+#    #+#             */
/*   Updated: 2018/12/23 13:34:57 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	packs_of_path(t_lem *lem)
{
	int		i;
	t_w		*way1;
	t_w		*way2;
	t_p		*pack;

	i = 0;
	if (!lem->ways)
		return ;
	way1 = lem->ways;
	while (way1)
	{
		way2 = lem->ways;
		if (way1->block == 0 && i <= 2)
			pack = add_new_pack(lem, way1->path, way1->len);
		while (way2)
		{
			if (way1 != way2 && compare_ways(way1, way2) == 0 && \
			way2->block == 0 && not_in_pack(pack->ways, way2->path))
				add_to_pack(pack, way2->path, way2->len, way2);
			way2 = way2->next;
		}
		i++;
		way1->block = 1;
		way1 = way1->next;
	}
}

int		compare_ways(t_w *way1, t_w *way2)
{
	t_q		*head1;
	t_q		*head2;

	head1 = way1->path;
	while (head1)
	{
		head2 = way2->path;
		while (head2)
		{
			if (head1->room->name == head2->room->name)
			{
				if ((head1->room->type == 1 && head2->room->type == 1) ||
					(head1->room->type == 3 && head2->room->type == 3))
					;
				else
					return (1);
			}
			head2 = head2->next;
		}
		head1 = head1->next;
	}
	return (0);
}

int		have_same_room(t_q *path1, t_q *path2)
{
	t_q		*tmp;

	while (path1)
	{
		tmp = path2;
		while (tmp)
		{
			if ((path1->room->name == tmp->room->name) && \
				path1->room->type != 3 && tmp->room->type != 3)
				return (1);
			tmp = tmp->next;
		}
		path1 = path1->next;
	}
	return (0);
}

void	add_to_pack(t_p *pack, t_q *path, int len, t_w *way2)
{
	t_w		*current;

	way2->block = 1;
	if (!pack->ways)
	{
		pack->ways = (t_w*)ft_memalloc(sizeof(t_w));
		pack->ways->path = path;
		pack->ways->next = NULL;
	}
	else
	{
		current = pack->ways;
		while (current->next)
			current = current->next;
		current->next = (t_w*)ft_memalloc(sizeof(t_w));
		current->next->path = path;
		current->next->flow = len;
		current->next->len = len;
		current->next->next = NULL;
	}
	pack->ways->flow += len;
	pack->ways->num_of_path += 1;
}

t_p		*add_new_pack(t_lem *lem, t_q *path, int len)
{
	t_p		*tmp;

	if (!lem->packs)
	{
		lem->packs = (t_p*)ft_memalloc(sizeof(t_p));
		lem->packs->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->packs->ways->path = path;
		init_new_pack(lem->packs->ways, len);
		lem->packs->next = NULL;
		tmp = lem->packs;
		return (tmp);
	}
	else
	{
		tmp = lem->packs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_p*)ft_memalloc(sizeof(t_p));
		tmp->next->ways = (t_w*)ft_memalloc(sizeof(t_w));
		tmp->next->ways->path = path;
		init_new_pack(tmp->next->ways, len);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}
