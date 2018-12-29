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

int		main(void)
{
	char	*str;
	t_lem	*lem;

	str = NULL;
	lem = (t_lem*)ft_memalloc(sizeof(t_lem));
	parse_ants(lem);
	str = parse_rooms(lem);
	piece_of_valid(lem, str);
	parse_links(lem, str);
	find_ways(lem);
	if (!lem->ways)
		ft_error(NULL, NULL, ER14);
	lem->ways = cut_the_way(lem->ways);
	packs_of_path(lem);
	print_map(lem);
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	while (lem->ways)
	{
		print_way(lem->ways->path);
		lem->ways = lem->ways->next;
	}
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	while (lem->packs)
	{
		printf("##########################\n");
		printf("flow = %d\n", lem->packs->ways->flow);
		while (lem->packs->ways)
		{
			printf("%d\n", lem->packs->ways->len);
			print_way(lem->packs->ways->path);
			lem->packs->ways = lem->packs->ways->next;
		}
		lem->packs = lem->packs->next;
	}
	run_ants_run(lem);
	// system("leaks -q lem-in");
	return (0);
}