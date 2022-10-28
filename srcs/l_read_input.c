/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 23:01:50 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	verify_all(t_verify *verify, t_data *data)
{
	t_room	*temp;

	if (!verify->valid_map)
		error_handling("Wrong input");
	if (verify->nb_of_starts != 1 || verify->nb_of_ends != 1)
		error_handling("Too many Starts or Ends");
	if (verify->start == ON || verify->end == ON)
		error_handling("Start or End not specified");
	temp = data->source;
	while (temp->next != NULL)
	{
		if (!temp->edges)
			error_handling("No links in room <temp->name>");//is it invalid?
		temp = temp->next;
	}
}
/*
	Here we check the validity of the input.
	We need to have one start, one end, and enough data to proceed.
****Not sure yet if all rooms need links!!****
****it might be that we have enough data even if few rooms are without****
****There must be more checks for the validity...?****
*/

void	arrange_sink(t_data *data)
{
	t_room	*temp;

	if (!data->source)
		error_handling("No ##start found");
	temp = data->source;
	while (temp->next != NULL)
		temp = temp->next;
	if (data->sink)
		temp->next = data->sink;
	else
		error_handling("No ##end found");
}
/*
	We want to arrange our list in a way that ##start is the starting point,
	and ##end is the last element in the list.
	That is why we have to move the ##end-element when the list is ready.
*/

int	comment_start_end(char *line, t_verify *verify)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start"))
		{
			verify->start = ON;
			verify->nb_of_starts++;
			return (START);
		}
		if (ft_strequ(line, "##end"))
		{
			verify->end = ON;
			verify->nb_of_ends++;
			return (END);
		}
		return (COMMENT);
	}
	return (0);
}
/*
	Turns on a switch when ##start or ##end is found.
	Also keeps count how many times they occur.
*/

void	read_room_and_link_info(char *line, t_verify *verify, t_data *data)
{
	t_room	*room;

	room = NULL;
	while (get_next_line(0, &line) == 1)
	{
		if (line[0] == '#')
			comment_found(line, verify);
		else if (line[0] == 'L')
			error_handling("Invalid room name");
		else if (!ft_strchr(line, ' '))
			break ;
		else if (verify->all_rooms_read == NOT_READ)
			room = get_room_info(line, verify, data, room);
		ft_strdel(&line);
	}
	arrange_sink(data);
	get_link_info(line, verify, data);
}
/*
	This function reads, checks comments and
	sends the line to the correct function to be dealt with.
	It is mostly used for getting room info.
*/

void	read_input(t_data *data)
{
	t_verify	*verify;
	char		*line;

	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_handling("MALLOC FAILED");
	init_verify(verify);
	line = NULL;
	get_ant_info(line, verify);
	read_room_and_link_info(line, verify, data);
	if (!verify_all(verify, data))
		error_exit(MAP_ERROR, verify);
	free_verify(verify);
}

/*
	read_input -function is actually a separator function.
	From here we call different reading and verifying functions.
*/
