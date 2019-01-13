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

void	packs_of_path(t_lem *lem)
{
	t_w	*way1;
	t_w	*way2;
	t_p	*pack;

	if (lem->ways)
		way1 = lem->ways;
	else
		return ;
	while (way1)
	{
		way2 = lem->ways;
		if (way1->block == 0)
			pack = add_new_pack(lem, way1->path, way1->len);
		while (way2)
		{
			if (way1 != way2 && compare_ways(way1, way2) == 0 && way2->block == 0 && not_in_pack(pack->ways, way2->path))
			{
				way2->block = 1;
				add_to_pack(pack, way2->path, way2->len);
			}
			way2 = way2->next;
		}
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
			if (ft_strequ(head1->room->name, head2->room->name))
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

int		have_same_room(t_q *path1, t_q *path2)
{
	t_q		*tmp;

	while (path1)
	{
		tmp = path2;
		while (tmp)
		{
			if (ft_strequ(path1->room->name, tmp->room->name) && path1->room->type != 3 && tmp->room->type != 3)
				return (1);
			tmp = tmp->next;
		}
		path1 = path1->next;
	}
	return (0);
}

void	add_to_pack(t_p *pack, t_q *path, int len)
{
	t_w		*current;

	if (!pack->ways)
	{
		pack->ways = (t_w*)ft_memalloc(sizeof(t_w));
		pack->ways->path = path;
		pack->ways->flow += len;
		pack->ways->num_of_path += 1;
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
		pack->ways->flow += len;
		pack->ways->num_of_path += 1;
		current->next->len = len;
		current->next->next = NULL;
	}
}

t_p		*add_new_pack(t_lem *lem, t_q *path, int len)
{
	t_p		*tmp;

	if (!lem->packs)
	{
		lem->packs = (t_p*)ft_memalloc(sizeof(t_p));
		lem->packs->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->packs->ways->path = path;
		lem->packs->ways->flow = len;
		lem->packs->ways->len = len;
		lem->packs->ways->num_of_path = 1;
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
		tmp->next->ways->flow = len;
		tmp->next->ways->len = len;
		tmp->next->ways->num_of_path = 1;
		tmp->next->next = NULL;
		return (tmp->next);
	}
}
