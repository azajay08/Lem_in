/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_room_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:14:04 by ajones            #+#    #+#             */
/*   Updated: 2022/11/18 20:30:17 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*make_index_room(t_vert *head, t_room *new_room, int index)
{
	t_vert	*old_room;
	
	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		return (NULL);
	init_room(new_room);
	old_room = head;
	old_room = find_room_index(old_room, index);
	new_room->index = index;
	new_room->name = ft_strdup(old_room->name);
	new_room->start = old_room->start;
	new_room->end = old_room->end;
	new_room->edge = old_room->edge;
	return (new_room);
}

t_room	**make_room_array(t_data *data)
{
	t_vert *head;
	t_room	**room;
	int		i;
	
	head = data->source;
	i = 0;
	room = (t_room **)malloc(sizeof(*room) * (data->nb_rooms));
	while (i < data->nb_rooms)
	{
		room[i] = make_index_room(head, *room, i);
		i++;
	}
	return (room);
}
