/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/11/15 02:19:21 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL		"ERROR! File input error\n"
# define ANT_ERROR		"ERROR! Not a valid number of ants\n"
# define MAP_ERROR		"ERROR! Not a valid map\n"
# define DATA_FAIL		"ERROR! Memory allocation of t_data failed!\n"
# define VERIFY_FAIL	"ERROR! Memory allocation of t_verify failed!\n"
# define T_ROOM_FAIL	"ERROR! Memory allocation of t_room failed\n"
# define ROOM_FAIL		"ERROR! Invalid room\n"
# define COORD_FAIL		"ERROR! Invalid coordinates\n"
# define LINK_FAIL		"ERROR! Invalid link\n"
# define START_FAIL		"ERROR! No start or too many starts\n"
# define END_FAIL		"ERROR! No end or too many ends\n"
# define NO_COMMAND		"ERROR! No start or end has been specified\n"
# define TOO_MANY		"ERROR! Too many starts or ends have been found\n"

# define OFF			0
# define ON				1
# define COMMENT		1
# define START_END		2
# define NOT_READ		0

# include "../libft/libft.h"

typedef struct s_verify
{
	int			valid_map;
	int			ants;
	int			nb_of_starts;
	int			nb_of_ends;
	int			index;
	int8_t		start;
	int8_t		end;
	int8_t		all_rooms_read;
}				t_verify;

typedef struct s_room
{
	char			*name;
	char			*edges;
	int				coord_y;
	int				coord_x;
	int				index;
	int8_t			start;
	int8_t			end;
	struct s_room	*bfs_previous;
	struct s_room	*next;
}					t_room;

typedef struct s_path
{
	struct s_path	*previous;
	char			*present;
	int				turns;
	struct s_path	*next;
}					t_path;

typedef struct s_option
{
	struct s_path	*start;
	int				turns;
	struct s_option	*previous;
	struct s_option	*next;
}					t_option;

typedef struct s_queue
{
	t_room			*next_room;
	t_room			*cold_rooms;
	char			*room_queue;
}					t_queue;

typedef struct s_data
{
	int			nb_ants;
	int			nb_rooms;
	t_room		*source;
	t_room		*sink;
}				t_data;

/*
	Functions that parse input
*/

void	read_input(t_data *data);
void	get_ant_info(char *line, t_data *data, t_verify *verify);
void	read_room_and_link_info(char *line, t_verify *verify, t_data *data);
t_room	*get_room_info(char *line, t_verify *verify, t_data *data, t_room *room);
void	get_link_info(char *line, t_verify *verify, t_data *data);
int		comment_start_end(char *line);
int		check_if_line_is_digits(char *line);
void	comment_found(char *line, t_verify *verify);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);
void	init_room(t_room *room);

/*
	Error management
*/

void	error_exit(char *error_str);
void	error_exit1(char *error_str, t_data *data);
void	error_exit2(char *error_str, t_data *data, t_verify *verify);
void	error_exit3(char *str, t_verify *verify, t_data *data, t_room *room);

/*
	Freeing functions
*/

void	free_verify(t_verify *verify);
void	free_data(t_data *data);
void	free_room(t_room *room);

/*
	Solving functions
*/

void	solver(t_data *data);

#endif