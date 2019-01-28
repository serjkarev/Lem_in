/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:42:36 by skarev            #+#    #+#             */
/*   Updated: 2018/11/01 14:42:36 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_flags_help(t_f *flags, char *av)
{
	if (!av || !*av)
		return (1);
	while (*av)
	{
		if (*av == 'c')
			flags->color_on = 1;
		else if (*av == 'h')
			flags->hide_map = 1;
		else if (*av == 'a')
			flags->approve_flags = 1;
		else if (*av == 'i')
			flags->iterations = 1;
		else if (*av == 's')
			flags->show_ways = 1;
		else
			return (1);
		av++;
	}
	return (0);
}

static void	get_flags(t_lem *lem, int ac, char **av)
{
	if (ac == 1 || !av)
		return ;
	if (!(lem->flags = (t_f*)ft_memalloc(sizeof(t_f))))
		exit(1);
	while (*av)
	{
		if (ft_strcmp(*av, "-c") == 0)
			lem->flags->color_on = 1;
		else if (ft_strcmp(*av, "-h") == 0)
			lem->flags->hide_map = 1;
		else if (ft_strcmp(*av, "-a") == 0)
			lem->flags->approve_flags = 1;
		else if (ft_strcmp(*av, "-i") == 0)
			lem->flags->iterations = 1;
		else if (ft_strcmp(*av, "-s") == 0)
			lem->flags->show_ways = 1;
		else if (**av == '-')
			if (get_flags_help(lem->flags, (*av + 1)) == 1)
			{
				free(lem->flags);
				ft_putstr(USAGE);
				exit(1);
			}
		av++;
	}
}

int			main(int ac, char **av)
{
	char	*str;
	t_lem	*lem;

	str = NULL;
	lem = (t_lem*)ft_memalloc(sizeof(t_lem));
	get_flags(lem, ac, av);
	parse_ants(lem);
	str = parse_rooms(lem);
	piece_of_valid(lem, str);
	parse_links(lem, str);
	if (lem->rn < 1800 || lem->rn >3000)
		find_ways(lem);
	else
		find_ways_v2(lem);
	if (!lem->ways)
		ft_error(NULL, NULL, ER14);
	lem->ways = cut_the_way(lem->ways);
	packs_of_path(lem);
	if (!lem->flags || lem->flags->hide_map != 1)
		print_map(lem);
	if (lem->flags && lem->flags->show_ways)
		print_pack(lem);
	if (lem->packs->next)
		choose_pack(lem);
	r_a_r(lem);
	if (lem->flags && lem->flags->approve_flags)
		print_flags(lem);
	// system("leaks -q lem-in");
	return (0);
}
