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
# define ER11 "🖕\x1B[31m ERROR: START room not found \033[0m🖕\n"
# define ER12 "🖕\x1B[31m ERROR: END room not found \033[0m🖕\n"

typedef struct		s_w
{
	struct	s_room	*room;
	struct	s_w		*next;
}					t_w;

typedef struct		s_q
{
	struct	s_room	*room;
	struct	s_q		*next;
}					t_q;

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
	int				deep;
	struct	s_room	*next;
	struct	s_nghbr	*nghbrs;
}					t_room;

typedef struct		s_lem
{
	int				ants;
	t_w				*ways;
	t_q				*queue;
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
void	bfs(t_lem *lem);
t_room	*find_room_by_type(t_lem *lem, int type);
void	add_to_queue(t_lem *lem, t_room *room, int deep);
void	dell_from_queue(t_lem *lem, t_room *room);
int		is_in_queue(t_q *queue, t_room *room);
void	find_ways(t_lem *lem);
int		count_neighbors(t_room *room);
void	add_to_ways(t_lem *lem, t_room *room);
void	get_way(t_lem *lem, t_room *room);
// t_w		*get_the_way(t_lem *lem);
// void	add_room_in_way(t_w *way, t_room *room);

#endif
