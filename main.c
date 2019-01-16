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
	// system("leaks -q lem-in");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	t_w		*buf;
	buf = lem->ways;
	while (buf)
	{
		print_way(buf->path);
		buf = buf->next;
	}
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	t_p		*tmp;
	t_w		*tmp2;
	tmp = lem->packs;
	while (tmp)
	{
		tmp2 = tmp->ways;
		printf("##########################\n");
		printf("flow = %d\n", tmp2->flow);
		while (tmp2)
		{
			printf("len = %d | ", tmp2->len);
			print_way(tmp2->path);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	printf("##########################\n");
	run_ants_run(lem);
	// system("leaks -q lem-in");
	return (0);
}
