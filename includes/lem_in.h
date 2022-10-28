/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 23:03:09 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL	"File input error\n"  // These are examples
# define ANT_ERROR	"Not a valid number of ants\n"
# define MAP_ERROR	"Not a valid map\n"
# define DATA_FAIL "ERROR, malloc of data failed!\n"
# define VERIFY_FAIL "ERROR, malloc of verify failed!\n"

# define COMMENT	1
# define START		2
# define END		3
# define NOT_READ	0

# include "../libft/libft.h"

typedef struct s_data
{
	int			nb_ants;
	int			nb_rooms;
}				t_data;

typedef struct s_verify
{
	int			valid_map;
	int			ants;
	int			nb_of_starts;
	int			nb_of_ends;
	int8_t		start;
	int8_t		end;
	int8_t		all_rooms_read;
}				t_verify;

typedef struct s_room
{
	char			*name;
	char			*edges;
	int8_t			start;
	int8_t			end;
	struct s_room	*next;
}					t_room;

/*
	Functions that parse input
*/

int		read_input(t_verify *verify);
void	get_ant_info(char *line, t_verify *verify);
int		get_room_info(char *line, t_verify *verify);
int		get_link_info(char *line, t_verify *verify);
int		comment_start_end(char *line, t_verify *verify);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);

/*
	Error management
*/

void	error_exit(char *error_str, t_verify *verify);
void	error_handling(char *error_str);

/*
	Freeing functions
*/

void	free_verify(t_verify *verify);

#endif