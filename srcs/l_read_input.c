/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 14:30:22 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	get_ant_info(char *line, t_data *data)
{
	if (ft_isdigit(line[0])) // more accurate check needed incase of minus
	{
		data->nb_ants = ft_atoi(line);
		if (data->nb_ants < 1)
			error_exit(ANT_ERROR, data);
			
	}
	ft_strdel(&line);
}

void	get_map_info(char *line, t_data *data)
{
	
}