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
	// char	*str;

	t_lem	*lem;

	lem = (t_lem*)ft_memalloc(sizeof(t_lem));
	init_lem(lem);
	parse_ants(lem);
	// str = parse_rooms(lem, str);

	// valid_links(lem);
	// bfs(lem);
	// system("leaks -q lem-in");
	// printf("ants = %d\n", lem->ants);
	return (0);
}
