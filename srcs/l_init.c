/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:04:41 by ajones            #+#    #+#             */
/*   Updated: 2022/12/03 21:22:47 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_room(t_room *room)
{
	room->name = NULL;
	room->edge = NULL;
	room->start = 0;
	room->end = 0;
	room->index = -1;
	room->bfs_previous = -1;
}

void	init_data(t_data *data)
{
	data->nb_ants = 0;
	data->nb_rooms = 0;
	data->rooms_malloced = 0;
	data->q_mode = OFF;
	data->p_mode = OFF;
	data->sink_index = -1;
	data->src_index = -1;
	data->vertex = OFF;
	data->line = NULL;
	data->source = NULL;
}

void	init_verify(t_verify *verify)
{
	verify->index = 0;
	verify->valid_map = 0;
	verify->ants = 0;
	verify->nb_of_starts = 0;
	verify->nb_of_ends = 0;
	verify->start = 0;
	verify->end = 0;
	verify->all_rooms_read = NOT_READ;
}

void	init_vert(t_vert *room)
{
	room->coord_y = -1;
	room->coord_x = -1;
	room->name = NULL;
	room->edge = NULL;
	room->start = OFF;
	room->end = OFF;
	room->next = NULL;
	room->index = -1;
}

void	init_ant(t_ant *ant)
{
	ant->ant_num = 0;
	ant->finished = NO;
	ant->launched = NO;
	ant->head = NULL;
	ant->next = NULL;
}
