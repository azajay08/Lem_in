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

int	verify_all(t_verify *verify)
{
	if (!verify->valid_map)
		error_handling();
	if (verify->nb_of_starts != 1 || verify->nb_of_ends != 1)
		error_handling("Too many or not enough Starts or Ends");
	if (verify->start == ON || verify->end == ON)
		error_handling("Start or End not specified");
}

int	comment_start_end(char *line, t_verify *verify)
{
	if (line[0] == '#')
	{
		if (ft_strstr(line, "##start")) // might need more accurate libft function
		{
			verify->start = ON;
			verify->nb_of_starts++;
			return (START);
		}
		if (ft_strstr(line, "##end")) // same, so that it is only this
		{
			verify->end = ON;
			verify->nb_of_ends++;
			return (END);
		}
		return (COMMENT);
	}
	return (0);
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
		if (ret != 1 || ret != 0)
			error_exit(GNL_FAIL, verify);
		else if (line[0] == '#')
			comment_found(line, data);
		else if (line[0] == 'L')
			error_handling("Invalid room name");
		else if (verify->all_rooms_read == NOT_READ)
			get_room_info(line, data);
		else if(links)
			get_link_info(line, data);
		ft_strdel(&line);
	}
	if (!verify_all(verify))
		error_exit(MAP_ERROR, verify);
	// free_verify(verify);
}
