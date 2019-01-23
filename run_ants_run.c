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

void	r_a_r(t_lem *lem)
{
	t_w		*curr;
	int		sn;

	sn = lem->ants;
	while (lem->ants)
	{
		curr = lem->packs->ways;
		while (curr)
		{
			if (norm(lem, curr))
			{
				add_ant(curr, sn - lem->ants + 1);
				lem->ants--;
			}
			else
				break ;
			curr = curr->next;
		}
	}
	run(lem);
}

int		norm(t_lem *lem, t_w *ways)
{
	t_w		*curr;
	int		sum;

	sum = 0;
	curr = lem->packs->ways;
	if (lem->ants <= ways->len - lem->ways->len)
		return (0);
	while (curr != ways)
	{
		sum += ways->len - curr->len;
		curr = curr->next;
	}
	return (lem->ants > sum);
}

void	add_ant(t_w *ways, int ant_num)
{
	t_a		*new;
	t_a		*curr;

	new = (t_a*)ft_memalloc(sizeof(t_a));
	new->pos = 0;
	new->num = ant_num;
	new->next = NULL;
	if (!ways->ants)
		ways->ants = new;
	else
	{
		curr = ways->ants;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	run(t_lem *lem)
{
	t_w		*curr;
	// int	count = 0;
	while (lem->packs->ways->ants)
	{
		curr = lem->packs->ways;
		while (curr)
		{
			print(curr);
			if(!curr->next)
			// {
				// count++;
				write(1, "\n", 1);
			// }
			else
				write(1, " ", 1);
			curr = curr->next;
		}
	}
	// printf("%d\n", count);
}

void	print(t_w *ways)
{
	t_a		*curr;

	curr = ways->ants;
	while (curr)
	{
		if (curr->pos == 0)
		{
			write(1, "L", 1);
			ft_putnbr(curr->num);
			write(1, "-", 1);
			ft_putstr(ways->path->room->name);
			curr->pos++;
			break ;
		}
		write(1, "L", 1);
		ft_putnbr(curr->num);
		write(1, "-", 1);
		t_q		*tmp = ways->path;
		int		i = 0;
		while (i < curr->pos)
		{
			i++;
			tmp = tmp->next;
		}
		ft_putstr(tmp->room->name);
		if (curr->next)
			write(1, " ", 1);
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