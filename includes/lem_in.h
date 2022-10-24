/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/10/24 14:49:03 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL	"File input error\n"  // These are examples
# define ANT_ERROR	"Not a valid number of ants\n"
# define MAP_ERROR	"Not a valid map\n"
# define DATA_FAIL "ERROR, malloc of data failed!\n"
# define VERIFY_FAIL "ERROR, malloc of verify failed!\n"

# define NOT_READ	0

# include "../libft/libft.h"

typedef struct s_data
{
	int			nb_ants;
	int			nb_rooms;
}				t_data;

typedef struct s_verify
{
	int			nb_of_starts;
	int			nb_of_ends;
}				t_verify;

/*
	Functions that parse input
*/

int		get_ant_info(char *line, t_data *data);
int		get_room_info(char *line, t_data *data);
int		get_link_info(char *line, t_data *data);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);

/*
	Error management
*/

void	error_exit(char *error_str, t_data *data);
void	error_handling(char *error_str);

#endif