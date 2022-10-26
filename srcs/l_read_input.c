/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 01:15:02 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_ant_info(char *line, t_verify *verify)
{
	if (ft_isdigit(line[0])) // more accurate check needed incase of minus
	{
		data->nb_ants = ft_atoi(line);
		if (data->nb_ants < 1)
			error_exit(ANT_ERROR, data);
		ft_strdel(&line);
	}
	else
	{
		ft_strdel(&line);
		error_exit(ANT_ERROR, data);
		return (0);
	}
	return (1);
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
