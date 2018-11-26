/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:30:49 by skarev            #+#    #+#             */
/*   Updated: 2018/11/02 14:30:49 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error(char *str, char *error)
{
	ft_putstr_fd(error, 2);
	free(str);
	exit(1);
}

int		ft_isdigit_str(char *str)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
	{
		i++;
		d++;
	}
	while(str[i])
	{
		if (ft_isdigit(str[i]))
			d++;
		i++;
	}
	return (i - d);
}
