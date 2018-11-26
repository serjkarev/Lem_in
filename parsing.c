/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:22:02 by skarev            #+#    #+#             */
/*   Updated: 2018/11/15 15:22:02 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*parse_ants(t_lem *lem)
{
	char	*str;

	while (get_next_line(0, &str))
	{
		if (!ft_isdigit_str(str))
		{
			lem->ants = ft_atoi(str);
			if (lem->ants <= 0)
				lem->ants == 0 ? ft_error(str, ER02) : ft_error(str, ER03);
			free(str);
			break;
		}
		else if (str[0] == '#' && str[1] != '#')
			continue ;
		else if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
			ft_error(str, ER01);
		else if (lem->ants == 0 && str)
			ft_error(str, ER04);
	}
}

char	*parse_rooms(t_lem *lem, char *str)
{
	while (get_next_line(0, &str))
	{
		
	}
}

void	parse_rooms_and_links(t_lem *lem)
{
	char	*str;
	t_room	*room = NULL;

	lem->rooms = room;
	while(get_next_line(0, &str))
    {
		if (ft_strequ(str, "##start"))
		{
			free(str);
			get_next_line(0, &str);
			if (str[0] == '#' && str[1] != '#')
			{
				free(str);
				continue;
			}
			else
			{
				parse_room(str, lem);
				lem->rooms->type = 1;
			}
		}
		else if (ft_strequ(str, "##end"))
		{
			free(str);
			get_next_line(0, &str);
			if (str[0] == '#' && str[1] != '#')
			{
				free(str);
				continue;
			}
			else
			{
				parse_room(str, lem);
				lem->rooms->type = 2;
			}
		}
		else if (str[0] == '#' && str[1] != '#')
			continue ;
		else if (space_detect(str) == 2)
			parse_room(str, lem);
		else
			parse_links(lem, str);
		free(str);
	}
}
