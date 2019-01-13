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
	// noi(ants, lem->ants, 1);
	// distribution_ants_on_way(ants, ways, lem);
	// run_vasya_run(ants, ways->num_of_path);
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
	t_w		*tmp1 = NULL;
	t_w		*tmp2 = NULL;
	int		n1;
	int		n2;

	n1 = 0;
	n2 = 0;
	tmp1 = lem->packs->ways;
	n1 = number_of_iterations(tmp1, lem->ants, ants);
	if (lem->packs->next)
	{
		write(1, "tyt\n", 4);
		tmp2 = lem->packs->next->ways;
		n2 = number_of_iterations(tmp2, lem->ants, ants);
		return (n1 <= n2 ? tmp1 : tmp2);
	}
	return (tmp1);
}

int		number_of_iterations(t_w *ways, int ants, t_a *a)
{
	t_w		*mw;
	t_w		*cw;
	t_a		*tmp_a;
	int		j;

	mw = ways;
	cw = ways;
	tmp_a = a;
	j = ants;
	while (ants != 0)
	{
		if (!cw)
			cw = mw;
		if (ABS(ants - (mw->len - 1)) >= (cw->len - 1) - (mw->len - 1))
		{
			tmp_a->path = cw->path;
			tmp_a = tmp_a->next;
			ants--;
		}
		cw = cw->next;
	}
	return (noi(a, j, ways->num_of_path));
}

int		noi(t_a *a, int ants, int n)
{
	int		i;
	int		j;
	t_a		*head;

	i = 1;
	head = a;
	while (ants)
	{
		j = n * i;
		while (j > 0 && ants)
		{
//			if (empty(head, a->path->room, n - 1))
//			{
				print_run(a->num, a->path->room->name);
				a->path->room = a->path->next->room;
//			}
			if (a->path->room->type == 3)
			    ants--; //and delete ant from list
            a = a->next;
			j--;
		}
        a = head;
		write(1, "\n", 1);
		i++;
	}
	return (i);
}

int		empty(t_a *head, t_room *room, int j)
{
	t_a		*tmp;

	tmp = head->next;
	while (tmp && j)
	{
		if (ft_strequ(tmp->path->room->name, room->name))
			return (0);
		tmp = tmp->next;
		j--;
	}
	return (1);
}

// void	run_vasya_run(t_a *ants, int num_of_path)
// {
// 	int		i;
// 	t_a		*head;

// 	head = ants;
// 	while (ants->path)
// 	{
// 		i = num_of_path;
// 		while (i > 0 && ants)
// 		{
// 			// printf("L%d-", ants->num);
// 			// printf("%s ", ants->path->room->name);
// 			print_run(ants->num, ants->path->room->name);
// 			i--;
// 			ants->path = ants->path->next;
// 			ants = ants->next;
// 		}
// 		write(1, "\n", 1);
//         num_of_path += num_of_path;
//         while (!head->path && head->next)
//             head = head->next;
// 		ants = head;
// 	}
// }

void	print_run(int num, char *str)
{
	write(1, "L", 1);
	ft_putnbr(num);
	write(1, "-", 1);
	ft_putstr(str);
	write(1, " ", 1);
}
