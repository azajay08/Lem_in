/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:00:15 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/11 04:59:08 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	*init_queue(t_data *data)
{
	int	*queue;
	int	i;

	queue = (int *)malloc(sizeof(int) * (data->nb_rooms));
	if (!queue)
		return (NULL); //need to check how to exit from here, need to free?
	i = 0;
	while (i < data->nb_rooms)
	{
		queue[i] = -1;
		i++;
	}
	queue[0] = data->src_index;
	return (queue);
}

void	clean_bfs(t_data *data, t_room **room, int *queue)
{
	int		i;

	i = 0;
	while (i < data->nb_rooms)
	{
		room[i]->bfs_previous = -1;
		room[i]->hop_off_switch = OFF;
		i++;
	}
	free (queue);
}

int	search_int_in_int_array(int index, int *queue) // better name?
{
	int	i;

	i = 0;
	while (queue[i] != -1)
	{
		if (index == queue[i] || index == -1)
			return (1);
		i++;
	}
	return (0);
}

void	follow_backwards(t_room **room, int *queue, int index)
{
	int	i;

	i = 0;
	while (queue[i] != -1)
	{
		if (search_int_in_int_array(room[index]->bfs_previous, queue))
			return ;
		i++;
	}
	queue[i] = room[index]->bfs_previous;
	room[queue[i]]->bfs_previous = index;
	room[queue[i]]->hop_off_switch = ON;
}

void	add_to_queue(t_room **room, t_edge *temp, int *queue, int index)
{
	int		i;

	i = 0;
	queue[i] = temp->room;
	room[temp->room]->bfs_previous = index;
}
