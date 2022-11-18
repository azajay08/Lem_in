/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/11/17 23:08:12 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL		"ERROR! File input error\n"
# define ANT_ERROR		"ERROR! Not a valid number of ants\n"
# define MAP_ERROR		"ERROR! Not a valid map\n"
# define DATA_FAIL		"ERROR! Memory allocation of t_data failed!\n"
# define VERIFY_FAIL	"ERROR! Memory allocation of t_verify failed!\n"
# define VERTEX_FAIL	"ERROR! Memory allocation of t_vertex failed\n"
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

typedef struct s_edge
{
	int				room;
	struct s_edge	*next;
	struct s_edge	*head;
}					t_edge;

typedef struct s_verify
{
	int				valid_map;
	int				ants;
	int				nb_of_starts;
	int				nb_of_ends;
	int				index;
	int8_t			start;
	int8_t			end;
	int8_t			all_rooms_read;
}					t_verify;

typedef struct s_vertex
{
	char			*name;
	int				coord_y;
	int				coord_x;
	int				index;
	int8_t			start;
	int8_t			end;
	struct s_vertex	*next;
	struct s_edge	*edge;
}					t_vertex;

typedef struct s_room
{
	char			*name;
	int				index;
	int8_t			start;
	int8_t			end;
	int				bfs_previous;
	struct s_edge	*edge;
}					t_room;

typedef struct s_path
{
	struct s_path	*previous;
	char			*name;
	int				index;
	int				edges;
	struct s_path	*next;
}					t_path;

typedef struct s_option
{
	struct s_path	*path;
	int				turns;
	int				edges;
	struct s_option	*previous;
	struct s_option	*next;
}					t_option;

typedef struct s_data
{
	int				nb_ants;
	int				nb_rooms;
	t_vertex		*source;
	t_room			**room;
}					t_data;

/*
	Functions that parse input
*/

void	read_input(t_data *data);
void	get_ant_info(char *line, t_data *data, t_verify *verify);
void	read_room_and_link_info(char *line, t_verify *verify, t_data *data);
t_vertex	*get_vertex_info(char *line, t_verify *verify, t_data *data, t_vertex *room);
void	get_link_info(char *line, t_verify *verify, t_data *data);
int		comment_start_end(char *line);
int		check_if_line_is_digits(char *line);
void	comment_found(char *line, t_verify *verify);
t_room	**make_room_array(t_data *data);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);
void	init_vertex(t_vertex *room);
void	init_room(t_room *room);

/*
	Error management
*/

void	error_exit(char *error_str);
void	error_exit1(char *error_str, t_data *data);
void	error_exit2(char *error_str, t_data *data, t_verify *verify);
void	error_exit3(char *str, t_verify *verify, t_data *data, t_vertex *room);

/*
	Freeing functions
*/

void	free_verify(t_verify *verify);
void	free_data(t_data *data);
void	free_room(t_vertex *room);

/*
	Solving functions
*/

void	solver(t_data *data);

/*
	Fucntions that locate data
*/

t_vertex	*find_room_index(t_vertex *head, int target);
t_vertex	*find_room_name(t_vertex *head, char *target);

#endif