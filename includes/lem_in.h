/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 18:56:09 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL "File input error\n"  // These are examples
# define ANT_ERROR "Not a valid number of ants\n"

# include "../libft/libft.h"

typedef struct s_data
{
	int			nb_ants;
	int			nb_rooms;
}				t_data;


/*
	Functions that parse input
*/

int		get_ant_info(char *line, t_data *data);
int		get_map_info(char *line, t_data *data);

/*
	Initialize structs
*/

void	init_data(t_data *data);

/*
	Error management
*/

void	error_exit(char *str, t_data *data);

#endif