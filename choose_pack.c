/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_pack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:24:03 by skarev            #+#    #+#             */
/*   Updated: 2019/01/23 20:24:04 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	no_print(t_w *ways)
{
	t_a		*curr;

	curr = ways->ants;
	while (curr)
	{
		if (curr->pos == 0)
		{
			curr->pos++;
			break ;
		}
		curr->pos++;
		curr = curr->next;
	}
	if (ways->ants && ways->ants->pos == ways->len)
	{
		curr = ways->ants;
		ways->ants = ways->ants->next;
		free(curr);
	}
}

static int	run_iter(t_p *pack)
{
	t_w		*curr;
	int		count;

	count = 0;
	while (pack->ways->ants)
	{
		curr = pack->ways;
		while (curr)
		{
			no_print(curr);
			if (!curr->next)
				count++;
			curr = curr->next;
		}
	}
	return (count);
}

static int	norm_v2(t_lem *lem, t_w *ways, t_p *pack)
{
	t_w		*curr;
	int		sum;

	sum = 0;
	curr = pack->ways;
	if (lem->ants <= ways->len - pack->ways->len)
		return (0);
	while (curr != ways)
	{
		sum += ways->len - curr->len;
		curr = curr->next;
	}
	return (lem->ants > sum);
}

static int	choose(t_lem *lem, t_p *pack)
{
	t_w		*curr;
	int		sn;
	int		ants;

	sn = lem->ants;
	ants = lem->ants;
	while (ants)
	{
		curr = pack->ways;
		while (curr && ants > 0)
		{
			if (norm_v2(lem, curr, pack))
			{
				add_ant(curr, sn - ants + 1);
				ants--;
			}
			else
				break ;
			curr = curr->next;
		}
	}
	return (run_iter(pack));
}

void		choose_pack(t_lem *lem)
{
	int		one;
	int		two;
	t_p		*tmp;

	one = choose(lem, lem->packs);
	two = choose(lem, lem->packs->next);
	if (one >= two)
	{
		tmp = lem->packs;
		lem->packs = lem->packs->next;
		free(tmp->ways);
		free(tmp);
	}
}
