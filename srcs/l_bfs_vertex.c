#include "../includes/lem_in.h"

int	search_int_from_path(t_room **room, int index, int x, int *queue)
{
	int	prev;
	int	i;

	prev = room[x]->bfs_previous;
	while (prev != -1 && room[prev]->start == OFF)
	{
		if (room[prev]->bfs_previous == index)
			return (0);
		prev = room[prev]->bfs_previous;
	}
	i = 0;
	while (queue[i] != END)
	{
		if (queue[i] == -1)
			break ;
		i++;
	}
	return (i);
}

void	follow_backwards(t_room **room, int *queue, int index)
{
	int	i;

	i = 0;
	while (queue[i] != -1)
	{
		i++;
	}
	queue[i] = room[index]->to_folo;
	room[queue[i]]->bfs_previous = index;
	room[queue[i]]->hop_off_switch = ON;
}

void	set_vert_queue(t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge;
	while (edge)
	{
		if (edge && (room[edge->room]->bfs_previous != -1 || edge->on_off == OFF
				|| room[edge->room]->bfs_previous == index)
			&& room[edge->room]->bfs_folo == OFF)
			edge = edge->next;
		if (!edge)
			break ;
		in_list = OFF;
		i = search_int_from_path(room, edge->room, index, queue);
		if (!i)
			in_list = ON;
		if (in_list == OFF && ((room[edge->room]->bfs_previous == -1
					&& edge->on_off == ON) || (room[edge->room]->bfs_folo == ON
					&& room[index]->start == OFF && edge->on_off == ON
					&& room[index]->bfs_previous != edge->room)))
			add_to_queue(room, edge, &queue[i], index);
		edge = edge->next;
	}
}

void	set_vertex_queue(t_room **room, int *queue, int index)
{
	if (room[index]->bfs_previous != -1 && room[index]->hop_off_switch == OFF
		&& room[index]->bfs_folo == ON && room[index]->start == OFF
		&& room[index]->end == OFF)
		follow_backwards(room, queue, index);
	else
		set_vert_queue(room, queue, index);
}
