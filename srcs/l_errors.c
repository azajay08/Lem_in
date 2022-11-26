/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2022/11/26 18:08:08 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *error_str)
{
	ft_putstr(error_str);
	exit(1);
}

void	error_exit1(char *error_str, t_data *data)
{
	free_data(data);
	ft_putstr(error_str);
	exit(1);
}

void	error_exit2(char *error_str, t_data *data, t_verify *verify)
{
	// str will contain the error message ?
	// free all that needs freeing or maybe not on an exit ?
	free_verify(verify);
	free_data(data);

	ft_putstr(error_str);

	exit(1);
}

void	error_exit3(char *str, t_verify *verify, t_data *data, t_vert *room)
{
	free_verify(verify);
	//free(room);
	free_data(data);
	free_room(room);
	ft_putstr(str);

	exit(1);
}

void	error_exit4(char *str, t_data *data, t_verify *verify, char *line)
{
	free_verify(verify);
	//free(room);
	free_data(data);
	ft_strdel(&line);
	// free_room(room);
	ft_putstr(str);

	exit(1);
}
