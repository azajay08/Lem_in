/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:15:15 by ajones            #+#    #+#             */
/*   Updated: 2022/11/01 15:51:58 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
	Could maybe add this to libft with a better name, checks whole line
	is only numbers
*/

int	comment_start_end(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start"))
			return (START);
		if (ft_strequ(line, "##end"))
			return (END);
		return (COMMENT);
	}
	return (0);
}

int	check_if_line_is_digits(char *line)
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
			error_exit(MAP_ERROR, data, verify);
		com_ret = comment_start_end(line);
		if (!com_ret)
		{
			if (!check_if_line_is_digits(line))
				error_exit(ANT_ERROR, data, verify);
			verify->ants = ft_atoi(line);
			if (verify->ants == 0)
				error_exit(ANT_ERROR, data, verify);
		}
		else if (com_ret == START || com_ret == END)
			error_exit(MAP_ERROR, data, verify);
		ft_strdel(&line); //still not sure whether to use this
	}
	data->nb_ants = verify->ants;
}








// {
// 	if (ft_isdigit(line[0]))
// 	{
// 		data->nb_ants = ft_atoi(line);
// 		if (data->nb_ants < 1)
// 			error_exit(ANT_ERROR, data);
// 		ft_strdel(&line);
// 	}
// 	else
// 	{
// 		ft_strdel(&line);
// 		error_exit(ANT_ERROR, data);
// 		return (0);
// 	}
// 	return (1);
// }