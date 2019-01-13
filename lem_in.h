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
# define ER13 "🖕\x1B[31m ERROR: not enough information to build a graph \033[0m🖕\n"
# define ER14 "🖕\x1B[31m ERROR: no way available \033[0m🖕\n"
# define ER15 "🖕\x1B[31m ERROR: duplicate room names \033[0m🖕\n"
# define ER16 "🖕\x1B[31m ERROR: !!! TRASH !!! \033[0m🖕\n"

# define ABS(n) (n >= 0 ? n : (n * -1))

typedef struct		s_a
{
	int			num;
	struct	s_q	*path;
	struct	s_a	*next;
}					t_a;

typedef struct		s_p
{
	struct	s_w	*ways;
	struct	s_p	*next;
}					t_p;

typedef struct		s_s
{
	char		*str;
	struct	s_s	*next;
}					t_s;

typedef struct		s_w
{
	int			len;
	int			block;
	int			flow;
	int			num_of_path;
	struct	s_q	*path;
	struct	s_w	*next;
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
	int				x;
	int				y;
	int				type;
	struct	s_room	*next;
	struct	s_nghbr	*nghbrs;
}					t_room;

typedef struct		s_lem
{
	int				ants;
	t_s				*print;
	t_p				*packs;
	t_w				*ways;
	t_q				*queue;
	t_room			*rooms;
}					t_lem;

// t_q		*freeList(t_q *path);

void	print_map(t_lem *lem);
int		lgnl(int fd, char **line);  // delete me
void	add_to_print(t_lem *lem, char *str);
void	ft_error(char *str, char **arr, char *error);
int		ft_isdigit_str(char *str);
int		space_detect(char *str);
void	free_arr(char **arr);
void	parse_ants(t_lem *lem);
char	*parse_rooms(t_lem *lem);
void	parse_room(char *str, t_lem *lem, int type);
void	create_room(char **arr, t_lem *lem, int type);
void	piece_of_valid(t_lem *lem, char *str);
void	parse_links(t_lem *lem, char *str);
int		check_link(char *str);
void	find_neighbor(t_lem *lem, char **arr, int n1, int n2);
t_room	*get_room_by_name(t_lem *lem, char *name);
int		check_nghbrs(t_nghbr *ns, char *name);
void	create_nghbrs(t_room *room, t_room *n);

t_room	*find_room_by_type(t_lem *lem, int type);
void	find_ways(t_lem *lem);
t_q		*push_back(t_q *path, t_room *room);
t_w		*push(t_w *queue, t_q *newpath);
t_w		*pop(t_w *queue);
t_room	*get_last_elem(t_q *path);
int		is_not_visited(t_room *n, t_q *path);
void	print_way(t_q* path);
t_q		*copy_path(t_q *path);
t_q		*freeList(t_q *path);
t_room	*copy_room(t_room *room);
void	add_path_to_ways(t_lem *lem, t_q *path);
t_w		*cut_the_way(t_w *ways);
int		way_len(t_q *path);

void	packs_of_path(t_lem *lem);
int		compare_ways(t_w *way1, t_w *way2);
int		not_in_pack(t_w *ways, t_q *path);
int		have_same_room(t_q *path1, t_q *path2);
void	add_to_pack(t_p *pack, t_q *path, int len);
t_p		*add_new_pack(t_lem *lem, t_q *path, int len);

void	run_ants_run(t_lem *lem);
t_a		*create_ants(t_lem *lem);
t_w		*choose_pack(t_lem *lem, t_a *ants);
int		number_of_iterations(t_w *ways, int ants, t_a *a);
int		noi(t_a *a, int ants, int n);
int		empty(t_a *head, t_room *room, int j);
void	distribution_ants_on_way(t_a *ants, t_w *ways, t_lem *lem);
void	run_vasya_run(t_a *ants, int num_of_path);
void	print_run(int num, char *str);

#endif


// t_w		*choose_pack(t_lem *lem, t_a *ants)
// {
// 	t_w		*tmp = NULL;
// 	if (lem->ants <= lem->packs->ways->flow)
// 		tmp = lem->packs->ways;
// 	else
// 	{
// 		if (lem->packs->next)
// 			tmp = lem->packs->next->ways;
// 		else
// 			tmp = lem->packs->ways;
// 	}
// 	return (tmp);
// }

// void	distribution_ants_on_way(t_a *ants, t_w *ways, t_lem *lem)
// {
// 	int		max_ant;
// 	t_w		*tmp;	
// 	t_w		*head;

// 	head = ways;
// 	max_ant = lem->ants;
// 	tmp = ways;
// 	while (max_ant != 0)
// 	{
// 		printf("L%d |", ants->num);
// 		print_way(tmp->path);
// 		ants->path = tmp->path;
// 		ants = ants->next;
// 		if (tmp->next)
// 			tmp = tmp->next;
// 		else
// 			tmp = head;
// 		max_ant--;
// 		// printf("\n");
// 	}
// }

// void	run_vasya_run(t_a *ants, int num_of_path)
// {
// 	int		i;
// 	t_a		*head;

// 	head = ants;
// 	while (ants->path)
// 	{
// 		i = num_of_path;
// 		while (i > 0 && ants)
// 		{
// 			// printf("L%d-", ants->num);
// 			// printf("%s ", ants->path->room->name);
// 			print_run(ants->num, ants->path->room->name);
// 			i--;
// 			ants->path = ants->path->next;
// 			ants = ants->next;
// 		}
// 		write(1, "\n", 1);
//         num_of_path += num_of_path;
//         while (!head->path && head->next)
//             head = head->next;
// 		ants = head;
// 	}
// }