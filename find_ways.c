/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:44:28 by skarev            #+#    #+#             */
/*   Updated: 2018/12/07 18:44:28 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
void	find_ways(t_lem *lem)
{
	t_w		*queue = NULL;
	t_q		*path = NULL;
	t_room	*room = NULL;
	t_q		*newpath = NULL;
	t_nghbr	*tmp;

	room = find_room_by_type(lem, 1);
	path = push_back(path, room);
	queue = push(queue, path);
	write(1, "\nHUI\n", 5);
	while (queue)
	{
		path = queue->path;
		room = get_last_elem(path);
		if (room->type == 3)
			add_path_to_ways(lem, path);
		tmp = room->nghbrs;
		while (tmp)
		{
			if (is_not_visited(tmp->neighbor, path))
			{
				newpath = copy_path(path); // у тебя был поинтер на алоцированые данные
				newpath = push_back(newpath, tmp->neighbor); // и тут
				queue = push(queue, newpath);
			}
			tmp = tmp->next;
		}
		queue = pop(queue);
	}
}

t_q		*push_back(t_q *path, t_room *room)
{
	t_q		*current;

	if (!path)
	{
		path = (t_q*)ft_memalloc(sizeof(t_q));
		path->room = room;
		path->next = NULL;
	}
	else
	{
		current = path;
		while (current->next)
			current = current->next;
		current->next = (t_q*)ft_memalloc(sizeof(t_q));
		current->next->room = room;
		current->next->next = NULL;
	}
	return (path);
}

t_w		*push(t_w *queue, t_q *path)
{
	t_w		*curr;

	if (!queue)
	{
		queue = (t_w*)ft_memalloc(sizeof(t_w));
		queue->path = path;
		queue->next = NULL;
	}
	else
	{
		curr = queue;
		while (curr->next)
			curr = curr->next;
		curr->next = (t_w*)ft_memalloc(sizeof(t_w));
		curr->next->path = path;
		curr->next->next = NULL;
	}
	return (queue);
}

t_w		*pop(t_w *queue)
{
	t_w		*head;

	if (queue)
	{
		head = queue;
		queue = queue->next;
		free(head);
	}
	return (queue);
}

t_room	*get_last_elem(t_q *path)
{
	t_q	*current;

	current = path;
	while (current->next)
		current = current->next;
	return (current->room);
}

int		is_not_visited(t_room *n, t_q *path)
{
	while (path)
	{
		if (ft_strequ(path->room->name, n->name))
			return (0);
		path = path->next;
	}
	return (1);
}

void	add_path_to_ways(t_lem *lem, t_q *path)
{
	t_w		*current;

	if (!lem->ways)
	{
		lem->ways = (t_w*)ft_memalloc(sizeof(t_w));
		lem->ways->path = path;
		lem->ways->next = NULL;
	}
	else
	{
		current = lem->ways;
		while (current->next)
			current = current->next;
		current->next = (t_w*)ft_memalloc(sizeof(t_w));
		current->next->path = path;
		current->next->next = NULL;
	}
}

void	print_way(t_q* path)
{
	while (path)
	{
		if (path->next)
			printf("%s -> ", path->room->name);
		else
			printf("%s", path->room->name);
		path = path->next;
	}
	printf("\n");
}

t_q		*copy_path(t_q *path)
{
	t_q		*newpath = NULL;

	while (path)
	{
		newpath = push_back(newpath, path->room);
		path = path->next;
	}
	return (newpath);
}

t_q		*freeList(t_q *path)
{
	t_q		*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
	return (path);
}
