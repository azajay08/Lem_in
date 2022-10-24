/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:04:41 by ajones            #+#    #+#             */
/*   Updated: 2022/10/24 14:10:57 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// file for all the initializing

void	init_data(t_data *data)
{
	data->nb_ants = 0;
	data->nb_rooms = 0;
}

void	init_verify(t_verify *verify)
{
	verify->nb_of_starts = 0;
	verify->nb_of_ends = 0;
}
