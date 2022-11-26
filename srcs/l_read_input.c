/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/11/26 18:09:52 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	verify_all(t_verify *verify, t_data *data)
{
	if (verify->nb_of_starts != 1 || verify->nb_of_ends != 1)
		error_exit2(INVALID_COM, data, verify);
	if (verify->start == ON || verify->end == ON)
		error_exit2(INVALID_COM, data, verify);
}

void	comment_found(char *line, t_verify *verify, t_data *data)
{
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
		error_exit4(INVALID_COM, data, verify, line);
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
			error_exit3(GNL_FAIL, verify, data, room);
		if (data->q_mode == OFF)
			data->line = ft_strjoin_line(data->line, line);
		if (line[0] == '#')
			comment_found(line, verify, data);
		else if (line[0] == 'L')
			error_exit2(ROOM_FAIL, data, verify);
		else if (!ft_strchr(line, ' '))
			break ;
		else if (verify->all_rooms_read == NOT_READ)
			room = get_vert_info(line, verify, data, room);
		ft_strdel(&line);
	}
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
	read_room_and_link_info(line, verify, data);
	verify_all(verify, data);
	data->room = make_room_array(data);
	free(verify);
}
