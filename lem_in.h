/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:42:04 by skarev            #+#    #+#             */
/*   Updated: 2018/11/01 14:42:04 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/libft.h"
# include <stdio.h>

# define ER01 "🖕\x1B[31m ERROR: start/end room before ants \033[0m🖕\n"
# define ER02 "🖕\x1B[31m ERROR: NO ANTS \033[0m🖕\n"
# define ER03 "🖕\x1B[31m ERROR: ANTS CAN'T BE NEGATIVE \033[0m🖕\n"
# define ER04 "🖕\x1B[31m ERROR: TRASH BEFORE ANTS \033[0m🖕\n"
# define ER05 "🖕\x1B[31m ERROR: BAD ROOM \033[0m🖕\n"
# define ER06 "🖕\x1B[31m ERROR: Invalid room coordinates \033[0m🖕\n"
# define ER07 "🖕\x1B[31m ERROR: 'start' must be one \033[0m🖕\n"
# define ER08 "🖕\x1B[31m ERROR: 'end' must be one \033[0m🖕\n"
# define ER09 "🖕\x1B[31m ERROR: invalid links \033[0m🖕\n"
# define ER10 "🖕\x1B[31m ERROR: link to a non-existent room \033[0m🖕\n"

typedef struct		s_nghbr
{
	struct	s_room	*neighbor;
	struct	s_nghbr	*next;
}					t_nghbr;

typedef struct		s_room
{
	char			*name;
	int				visited;
	int				x;
	int				y;
	int				type;
	struct	s_room	*next;
	struct	s_nghbr	*nghbrs;
}					t_room;

typedef struct		s_lem
{
	int				ants;
	t_nghbr			*queue;
	t_room			*rooms;
}					t_lem;

void	init_lem(t_lem *lem);
void	ft_error(char *str, char **arr, char *error);
int		ft_isdigit_str(char *str);
int		space_detect(char *str);
void	free_arr(char **arr);
void	parse_ants(t_lem *lem);
char	*parse_rooms(t_lem *lem);
void	parse_room(char *str, t_lem *lem, int type);
void	create_room(char **arr, t_lem *lem, int type);
void	parse_links(t_lem *lem, char *str);
void	find_neighbor(t_lem *lem, char **arr, int n1, int n2);
t_room	*get_room_by_name(t_lem *lem, char *name);
void	create_nghbrs(t_room *room, t_room *n);

//########################################################

void				bfs(t_lem *lem);
t_room				*find_start_room(t_lem *lem);
void				add_to_queue(t_lem *lem, t_room *room);
int					is_empty(t_nghbr *queue);
t_room				*dell_from_queue(t_nghbr *q);


#endif
