/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 16:05:24 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*put_start_or_end_in_order(t_room *new_room, t_room *start, t_verify *verify)
{
	t_room	*temp;

	temp = start;
	if (verify->start == ON)
	{
		new_room->next = start;
		start = new_room;
		verify->start = OFF;
	}
	else if (verify->end == ON)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_room;
		verify->end = OFF;
	}
	return (start);
}

t_room	*make_room(char *line, t_verify *verify)
{
	t_room	*new_room;
	char	*temp;

	temp = ft_strsplit(line, ' ');
	if (!check_if_line_is_digits(temp[1]) || !check_if_line_is_digits(temp[2])
		|| temp[3])
		error_handling("Inavlid coordinates");
	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		error_handling(MALLOC_ERROR);
	new_room->name = ft_strdup(temp[0]);
	//new_room->coord_x = ft_atoi(temp[1]);
	//new_room->coord_y = ft_atoi(temp[2]);
	new_room->start = OFF;
	new_room->end = OFF;
	if (verify->start == ON)
		new_room->start = ON;
	else if (verify->end == ON)
		new_room->end = ON;
	return (new_room);
}

int	get_room_info(char *line, t_verify *verify)
{
	t_room	*new_room;
	t_room	*start;

	if (!ft_strchr(line, ' '))
	{
		verify->all_rooms_read = HAS_BEEN_READ;
		return (get_link_info);
	}
	else
	{
		new_room = make_room(line, verify);
		if (verify->start == ON || verify->end == ON)
		{
			start = put_start_or_end_in_order(new_room, rooms, verify);
		}
		else
			rooms->next = new_room;
	}
}