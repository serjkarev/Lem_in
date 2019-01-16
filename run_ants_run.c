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
	ants = create_ants(lem);
	distribution_ants_on_way(ways, lem->ants, ants);
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
			ants->current_room = NULL;
			ants->next = NULL;
		}
		else
		{
			current = ants;
			while (current->next)
				current = current->next;
			current->next = (t_a*)ft_memalloc(sizeof(t_a));
			current->next->num = i++;
			current->next->current_room = NULL;
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
		ants = create_ants(lem);
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

	mw = ways;
	cw = ways;
	tmp_a = a;
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
	return (noi(a, ways->num_of_path));
}

int		noi(t_a *a, int n)
{
	int		i;
	int		j;
	int     f;
	t_a		*head;

	i = 1;
	head = a;
	while (a)
	{
		j = n * i;
		f = j;
		while (j > 0 && a)
		{
			if (empty(head, a, f))
			{
                if (a->path->room->type == 3)
					ft_list_remove_if(&head, a->num);
				a->current_room = a->path->room;
				a->path = a->path->next;
			}
            a = a->next;
			j--;
		}
        a = head;
		i++;
	}
	return (i);
}

int		empty(t_a *head, t_a *a, int j)
{
	t_a		*tmp;

	tmp = head;
	while (tmp && j)
	{
		if (tmp->current_room && ft_strequ(tmp->current_room->name, a->path->room->name) && tmp->num != a->num \
		&& (a->path->room->type != 3 && tmp->current_room->type != 3))
			return (0);
		tmp = tmp->next;
		j--;
	}
	return (1);
}

void	ft_list_remove_if(t_a **head, int num)
{
	t_a	*tmp;
	t_a	*current;

	while (*head && (*head)->num == num)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	current = *head;
	while (current && current->next)
	{
		if (current->next->num == num)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp);
		}
		current = current->next;
	}
}

void	distribution_ants_on_way(t_w *ways, int ants, t_a *a)
{
	t_w		*mw;
	t_w		*cw;
	t_a		*tmp_a;

	mw = ways;
	cw = ways;
	tmp_a = a;
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
	run_vasya_run(a, ways->num_of_path);
}

void	run_vasya_run(t_a *a, int n)
{
	int		i;
	int		j;
	int     f;
	t_a		*head;

	i = 1;
	head = a;
	while (a)
	{
		j = n * i;
		f = j;
		while (j > 0 && a)
		{
			if (empty(head, a, f))
			{
				print_run(a->num, a->path->room->name);
                if (a->path->room->type == 3)
					ft_list_remove_if(&head, a->num);
				a->current_room = a->path->room;
				a->path = a->path->next;
			}
            a = a->next;
			j--;
		}
        a = head;
		write(1, "\n", 1);
		i++;
	}
	printf("NUMBER_OF_ITEARATION = %d\n", i - 1);
}

void	print_run(int num, char *str)
{
	write(1, "L", 1);
	ft_putnbr(num);
	write(1, "-", 1);
	ft_putstr(str);
	write(1, " ", 1);
}
