/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 15:34:55 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	comment_start_end(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strstr(line, "##start")) // might need more accurate libft function
			return (START);
		if (ft_strstr(line, "##end")) // same, so that it is only this
			return (END);
		return (COMMENT);
	}
	return (0);
}

int	get_room_info(char *line, t_data *data)
{

	if (data->start == 1)
	{
		deal_with_start();
		data->start = 0;
	}
	else
		deal_with_rooms(); 
	while (ft_strchr(line) != ft_strrchr(line))//check if there are two spaces
	{
		save_room_info(line, data);	//example
		ft_strdel(&line);
		if (ft_strchr(line, '-')
			get_link_info(line, data);
		data->nb_rooms++;
	}
}

/*
	In the function above the problem is now that we have the data for the
	first link. Could maybe do the same way I did on filler, that it's saved
	in the struct?

	Other option would be to call the get_link_info from this function?
	Or even to do them both in the same function
	(which both make the readability worse)

	!*** The while loop checks if there are two spaces,					   ***!
	!*** which would make it a room. Needs another check for the comments. ***!
	!*** Then the save_room_info would do the comment check too.		   ***!
	!***																   ***!
	!*** It's just an idea how it could be done,						   ***!
	!*** we'll probably find a better way								   ***!
*/

int	get_link_info(char *line, t_data *data)
{
	int		ret;

	ret = 1;
	while (ret == 1)
	{
		save_link_info(line, data);	//example
		ft_strdel(&line);
		ret = get_next_line(0, &line);
	}
	if (ret != 0)
		error_exit(GNL_FAIL, data);
	return (1);
}

int	read_input(t_verify *verify)
{
	char		*line;
	int			ret;

	line = NULL;
	get_ant_info(line, verify);
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
			error_exit(GNL_FAIL, verify);
		else if (line[0] == '#')
			comment_found(line, data);
		else if (rooms)
			get_room_info(line, data);
		else if(links)
			get_link_info(line, data);
		ft_strdel(&line);
	}
	// free_verify(verify);
	if (!verify->valid_map)
		error_exit(MAP_ERROR, verify);
}
