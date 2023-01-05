/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:15:15 by ajones            #+#    #+#             */
/*   Updated: 2023/01/05 20:36:14 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	comment_start_end(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			return (START_END);
		return (COMMENT);
	}
	return (0);
}

int	check_line_is_digits(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_ant_info(char *line, t_data *data, t_verify *verify)
{
	int	com_ret;

	com_ret = 0;
	while (!verify->ants)
	{
		if (get_next_line(0, &line) != 1)
			error_exit2(MAP_ERROR, data, verify);
		if (data->q_mode == OFF)
			line_join(data, line);
		com_ret = comment_start_end(line);
		if (!com_ret)
		{
			if (!check_line_is_digits(line))
				error_exit2(ANT_ERROR, data, verify);
			verify->ants = ft_atoi(line);
			if (verify->ants <= 0)
				error_exit2(ANT_ERROR, data, verify);
		}
		else if (com_ret == START_END)
			error_exit2(MAP_ERROR, data, verify);
		ft_strdel(&line);
	}
	data->nb_ants = verify->ants;
}
