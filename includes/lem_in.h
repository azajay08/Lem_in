/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 14:30:13 by ajones           ###   ########.fr       */
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

void	get_ant_info(char *line, t_data *data);
void	get_map_info(char *line, t_data *data);

/*
	Initialize structs
*/

void	init_data(t_data *data);

/*
	Error management
*/

void	error_exit(char *str, t_data *data);

#endif