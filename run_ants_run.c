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
	distribution_ants_on_way(ants, ways, lem);
	run_vasya_run(ants, ways->num_of_path);
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

void	distribution_ants_on_way(t_a *ants, t_w *ways, t_lem *lem)
{
	int		max_ant;
	t_w		*tmp;	
	t_w		*head;

	head = ways;
	max_ant = lem->ants;
	tmp = ways;
	while (max_ant != 0)
	{
		printf("L%d |", ants->num);
		print_way(tmp->path);
		ants->path = tmp->path;
		ants = ants->next;
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = head;
		max_ant--;
		// printf("\n");
	}
}

void	run_vasya_run(t_a *ants, int num_of_path)
{
	int		i;
	t_a		*head;

	head = ants;
	while (ants->path)
	{
		i = num_of_path;
		while (i > 0 && ants)
		{
			// printf("L%d-", ants->num);
			// printf("%s ", ants->path->room->name);
			print_run(ants->num, ants->path->room->name);
			i--;
			ants->path = ants->path->next;
			ants = ants->next;
		}
		write(1, "\n", 1);
        num_of_path += num_of_path;
        while (!head->path && head->next)
            head = head->next;
		ants = head;
	}
}

void	print_run(int num, char *str)
{
	write(1, "L", 1);
	ft_putnbr(num);
	write(1, "-", 1);
	ft_putstr(str);
	write(1, " ", 1);
}