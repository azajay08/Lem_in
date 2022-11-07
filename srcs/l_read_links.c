/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:06:41 by ajones            #+#    #+#             */
/*   Updated: 2022/11/07 13:12:55 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	assign_link(char *link_to, t_room *room)
{
	if (room->edges)
		room->edges = ft_strjoin(room->edges, '-');
	room->edges = ft_strjoin(room->edges, link_to);
	return (1);
}

int	verify_and_assign_names(char *line, t_room *start)
{
	char	**temp;
	t_room	*room;
	int		counter;
	int		counter2;

	counter = 0;
	counter2 = 0;
	room = start;
	temp = ft_strsplit(line, '-');
	if (!temp)
		return (0);
	while (room->next != NULL)
	{
		if (ft_strequ(temp[0], room->name))
			counter += assign_link(temp[1], room);
		if (ft_strequ(temp[1], room->name))
			counter2 += assign_link(temp[0], room);
		room = room->next;
	}
	ft_2d_free(temp);
	if (counter != 1 || counter2 != 1)
		return (0);
	return (1);
}
/*
	Here we have a few verifications.
	First we check if there is precisely one dash('-').
	Then we check that both of the room names in the link are found
	exactly in the same format. Both must be found.
*/

int	save_link_info(char *line, t_room *start, t_verify *verify)
{
	if (ft_strchr(line, '-') != ft_strrchr(line, '-'))
	{
		ft_strdel(&line);
		return (0);
	}
	if (!verify_and_assign_names(line, start))
		return (0);

	// NEED a check to see even if that room exists
		
	// Do we need to do something else?
	// It feels like there should be more verifications here...
	// If not we can go straight to verify_and_assign.
	
	// YEAH, this can be like a half way point for what needs to be freed
	// so run the checks here to return 0 or 1, and free accordingly. 
	// can run the line checks here before splitting in the next function
}

void	get_link_info(char *line, t_verify *verify, t_data *data)
{
	int		ret;
	t_room	*start;

	start = data->source;
	if (!save_link_info(line, start, verify))
		error_exit3(LINK_FAIL, verify, data, start);
	ft_strdel(&line);
	while (get_next_line(0, &line) == 1)
	{
		start = data->source;
		if (line[0] == '#')
			comment_found(line, verify);
		else if (ft_strchr(line, ' '))
			error_exit("Room in wrong place", data, verify);
		else if (!save_link_info(line, start, verify))
			error_exit3(LINK_FAIL, verify, data, start);
			// error_data("bad link", data, verify);
		ft_strdel(&line);
	}
}

/*
	Just basic verifying checks in this function.
*/
