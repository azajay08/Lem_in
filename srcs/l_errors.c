/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2022/11/07 13:01:57 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *error_str, t_data *data, t_verify *verify)
{
	// str will contain the error message ?
	// free all that needs freeing or maybe not on an exit ?

	free(verify);
	free_data(data);

	ft_putstr(error_str);

	exit(1);
}

/*
	error_exit is used in reading functions
	when both data and verify need to be freed.
*/


void	error_exit2(char *error_str, t_data *data)
{
	free_data(data);
	ft_putstr(error_str);
	exit(1);
}

/*
	error_exit2 is used when mallocing verify fails,
	so only data needs to be freed.
*/

void	error_nothing_to_be_freed(char *error_str)
{
	ft_putstr(error_str);
	exit(1);
}

/*
	The name is not final.
*/

void	error_exit3(char *str, t_verify *verify, t_data *data, t_room *room)
{
	free(verify);
	free(room);
	free_data(data);

	ft_putstr(str);

	exit(1);
}