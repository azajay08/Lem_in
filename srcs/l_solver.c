/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/08 20:44:11 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	solver(t_data *data)
{
	// Use bfs and maybe other algorithms to get the best route
	// print here or in the main?
	// If in the main, we need to either return the string from here,
	// or save it in data.
}

/*	Hasbulla once said... Coca cola
	Ive just cleaned some stuff, the error exit functions are numbered 
	according to how many structs are being freed. im still unsure about 
	the t_room being freed? does that come unpacked with with data ?
*/