/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:04:41 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 15:32:53 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// file for all the initializing

// void	init_data(t_data *data)
// {
// 	data->nb_ants = 0;
// 	data->nb_rooms = 0;
// 	data->valid_map = 0;
// }

void	init_verify(t_verify *verify)
{
	verify->valid_map = 0;
	verify->ants = 0;
	verify->start = 0;
	verify->end = 0;
}
