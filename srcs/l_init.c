/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:04:41 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 15:32:53 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// file for all the initializing

void	init_data(t_data *data)
{
	data->nb_ants = 0;
	data->nb_rooms = 0;
	data->source = NULL;
	data->sink = NULL;
}

void	init_verify(t_verify *verify)
{
	verify->valid_map = 0;
	verify->ants = 0;
	verify->nb_of_starts = 0;
	verify->nb_of_ends = 0;
	verify->start = 0;
	verify->end = 0;
	verify->all_rooms_read = NOT_READ;
}

void	init_room(t_room *room)
{
	room->name = NULL;
	room->edges = NULL;
	room->start = OFF;
	room->end = OFF;
	room->next = NULL;
}
