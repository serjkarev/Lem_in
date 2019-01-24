/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:41:42 by skarev            #+#    #+#             */
/*   Updated: 2019/01/23 17:41:42 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_flags(t_lem *lem)
{
	if (lem->flags->color_on == 1)
		write(1, "\x1b[36m", 5);
	write(1, "c - color on ", 13);
	if (lem->flags->color_on == 1)
		write(1, "🥑", 4);
	write(1, "\nh - hide map ", 14);
	if (lem->flags->hide_map == 1)
		write(1, "🥑", 4);
	write(1, "\na - approve flags ", 19);
	if (lem->flags->approve_flags == 1)
		write(1, "🥑", 4);
	write(1, "\ni - number of lines ", 21);
	if (lem->flags->iterations == 1)
		write(1, "🥑", 4);
	write(1, "\ns - show ways ", 15);
	if (lem->flags->iterations == 1)
		write(1, "🥑", 4);
	write(1, "\n", 1);
}

void	print_iter(t_lem *lem, int count)
{
	if (lem->flags->color_on == 1)
	{
		write(1, "\x1b[31m", 5);
		write(1, "Here is the number of lines received: ", 38);
		write(1, "\x1b[32m", 5);
		ft_putnbr(count);
		write(1, "\n\033[0m", 6);
	}
	else
	{
		write(1, "Here is the number of lines received: ", 38);
		ft_putnbr(count);
		write(1, "\n", 1);
	}
}

void	print_pack(t_lem *lem)
{
	t_p		*tmp;
	t_w		*tmp2;

	tmp = lem->packs;
	while (tmp)
	{
		tmp2 = tmp->ways;
		while (tmp2)
		{
			if (lem->flags->color_on)
				write(1, "\x1b[33m", 5);
			print_way(tmp2->path);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	write(1, "\n", 1);
}

static void	print_v3(char *rname, t_a *curr, t_q *path)
{
	t_q		*tmp;
	int		i;

	write(1, "\x1b[33mL\033[0m\x1b[31m", 16);
	ft_putnbr(curr->num);
	write(1, "\x1b[33m-\033[0m", 11);
	if (path)
	{
		i = 0;
		tmp = path;
		while (i < curr->pos)
		{
			i++;
			tmp = tmp->next;
		}
		write(1, "\x1b[32m", 5);
		ft_putstr(tmp->room->name);	
	}
	else
	{
		write(1, "\x1b[32m", 5);
		ft_putstr(rname);
	}
}

void	print_v2(char *rname, t_a *curr, t_q *path, t_lem *lem)
{
	t_q		*tmp;
	int		i;
	
	if (lem->flags && lem->flags->color_on)
		print_v3(rname, curr, path);
	else
	{
		write(1, "L", 1);
		ft_putnbr(curr->num);
		write(1, "-", 1);
		if (path)
		{
			i = 0;
			tmp = path;
			while (i < curr->pos)
			{
				i++;
				tmp = tmp->next;
			}
			ft_putstr(tmp->room->name);	
		}
		else
			ft_putstr(rname);
	}
}
