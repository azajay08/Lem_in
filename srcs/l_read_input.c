/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/11/28 14:20:19 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	verify_all(t_verify *verify, t_data *data)
{
	if (verify->nb_of_starts != 1 || verify->nb_of_ends != 1)
		error_exit2(INVALID_COM, data, verify);
	if (verify->start == ON || verify->end == ON)
		error_exit2(INVALID_COM, data, verify);
}

void	comment_found(char *line, t_verify *verify, t_data *data)
{
	if (verify->start == ON || verify->end == ON)
	{
		free(verify);
		error_exit1(INVALID_COM, data);
	}
	if (ft_strequ(line, "##start"))
	{
		verify->start = ON;
		verify->nb_of_starts++;
	}
	if (ft_strequ(line, "##end"))
	{
		verify->end = ON;
		verify->nb_of_ends++;
	}
	if (verify->start == ON && verify->end == ON)
		error_exit2(INVALID_COM, data, verify);
}

void	read_room_and_link_info(char *line, t_verify *verify, t_data *data)
{
	t_vert	*room;
	int		ret;

	room = NULL;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret < 1)
			error_exit2(MAP_ERROR, data, verify);
		if (line[0] == '#')
			comment_found(line, verify, data);
		else if (line[0] == 'L')
			error_exit2(ROOM_FAIL, data, verify);
		else if (!ft_strchr(line, ' '))
			break ;
		else
			room = get_vert_info(line, verify, data, room);
		if (data->q_mode == OFF)
			data->line = ft_strjoin_line(data->line, line);
		ft_strdel(&line);
	}
	if (data->nb_rooms == 0)
		error_exit1(NO_ROOMS, data);
	get_link_info(line, verify, data);
}

void	read_input(t_data *data)
{
	t_verify	*verify;
	char		*line;

	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_exit1(VERIFY_FAIL, data);
	init_verify(verify);
	line = NULL;
	get_ant_info(line, data, verify);
	if (data->nb_ants >= ANT_LIMIT)
	{
		free(verify);
		error_exit1(TOO_MANY_ANTS, data);
	}
	read_room_and_link_info(line, verify, data);
	verify_all(verify, data);
	free(verify);
	data->queue = (int *)malloc(sizeof(int) * ((data->nb_rooms * 2) + 1));
	if (!data->queue)
		error_exit1(QUEUE_FAIL, data);
}
