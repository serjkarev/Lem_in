/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:03:18 by skarev            #+#    #+#             */
/*   Updated: 2018/12/29 16:03:18 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	run_ants_run(t_lem *lem)
{
	t_a		*ants;
	t_w		*ways;

	ants = create_ants(lem);
	ways = choose_pack(lem, ants);

}

t_a		*create_ants(t_lem *lem)
{
	t_a     *ants = NULL;
	t_a     *current;
	int     i;

	i = 1;
	while (i <= lem->ants)
	{
		if (!ants)
		{
			ants = (t_a*)ft_memalloc(sizeof(t_a));
			ants->num = i++;
			ants->next = NULL;
		}
		else
		{
			current = ants;
			while (current->next)
				current = current->next;
			current->next = (t_a*)ft_memalloc(sizeof(t_a));
			current->next->num = i++;
			current->next->next = NULL;
		}
	}
	return (ants);
}

t_w		*choose_pack(t_lem *lem, t_a *ants)
{
	t_w		*tmp = NULL;
	if (lem->ants <= lem->packs->ways->flow)
		tmp = lem->packs->ways;
	else
	{
		if (lem->packs->next)
			tmp = lem->packs->next->ways;
		else
			tmp = lem->packs->ways;
	}
	return (tmp);
}

void	distribution_ants_on_way(t_a *ants, t_w *ways)
{

}