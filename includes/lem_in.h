/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/12/15 15:23:47 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL		"ERROR! File input\n"
# define ANT_ERROR		"ERROR! Not a valid number of ants\n"
# define TOO_MANY_ANTS	"ERROR! Too many ants, limit is 30 000\n"
# define MAP_ERROR		"ERROR! Not a valid map\n"
# define DATA_FAIL		"ERROR! Memory allocation of t_data failed!\n"
# define VERIFY_FAIL	"ERROR! Memory allocation of t_verify failed!\n"
# define VERT_FAIL		"ERROR! Memory allocation of t_vert failed\n"
# define T_ROOM_FAIL	"ERROR! Memory allocation of t_room failed\n"
# define QUEUE_FAIL		"ERROR! Memory allocation of data->queue failed\n"
# define OPT_FAIL		"ERROR! Memory allocation of t_opt failed\n"
# define PATH_FAIL		"ERROR! Memory allocation of t_path failed\n"
# define NO_PATHS		"ERROR! No paths found\n"
# define ANTS_FAIL		"ERROR! Memory allocation of t_ants failed\n"
# define ROOM_FAIL		"ERROR! Invalid room\n"
# define SPACES			"ERROR! Invalid room, too many spaces\n"
# define NO_ROOMS		"ERROR! No rooms\n"
# define COORD_FAIL		"ERROR! Invalid coordinates\n"
# define LINK_FAIL		"ERROR! Invalid link\n"
# define INVALID_COM	"ERROR! Invalid start or end\n"
# define DUPLICATE		"ERROR! Duplicate room name or coordinates\n"

# define OFF			0
# define ON				1
# define COMMENT		1
# define START_END		2
# define ERROR			0
# define SUCCESS		1
# define YES			1
# define NO				0
# define REACHED		-1
# define END			-2
# define ANT_LIMIT		30000

# include "../libft/libft.h"
# include <stdio.h>			//REMEMBER TO DELETE THIS AND stdint.h FROM PRINTF!!

typedef struct s_ant
{
	int				ant_num;
	int				launched;
	int				finished;
	struct s_ant	*next;
	struct s_path	*head;
}				t_ant;

typedef struct s_edge
{
	int				room;
	int8_t			on_off;
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
}					t_verify;

typedef struct s_vert
{
	char			*name;
	int				coord_y;
	int				coord_x;
	int				index;
	int8_t			start;
	int8_t			end;
	struct s_vert	*next;
	struct s_edge	*edge;
}					t_vert;

typedef struct s_room
{
	char			*name;
	int				index;
	int8_t			start;
	int8_t			end;
	int8_t			hop_off_switch;
	int8_t			bfs_folo;
	int				to_folo;
	int				bfs_previous;
	struct s_edge	*edge;
}					t_room;

typedef struct s_path
{
	struct s_path	*previous;
	int				index;
	int				edges;
	struct s_path	*next;
}					t_path;

typedef struct s_opt
{
	struct s_path	*path;
	int				p_len;
	int				used;
	int				limit;
	int				ants;
	struct s_opt	*previous;
	struct s_opt	*next;
}					t_opt;

typedef struct s_data
{
	int				turns;
	int				ants_in_sink;
	int				ant_num;
	int				nb_ants;
	int				nb_rooms;
	int				nb_paths;
	int				q_mode;
	int				p_mode;
	int				t_mode;
	int				sink_index;
	int				src_index;
	int				rooms_malloced;
	int				*queue;
	char			*line;
	int8_t			vertex;
	t_vert			*source;
	t_room			**room;
	t_ant			*queen;
}					t_data;

/*
	Functions that parse input
*/

void	read_input(t_data *data);
void	get_ant_info(char *line, t_data *data, t_verify *verify);
void	read_room_and_link_info(char *line, t_verify *verify, t_data *data);
void	comment_found(char *line, t_verify *verify, t_data *data);
void	get_link_info(char *line, t_verify *verify, t_data *data);
int		comment_start_end(char *line);
int		check_line_is_digits(char *line);
t_vert	*get_vert_info(char *line, t_verify *verif, t_data *data, t_vert *room);
t_room	**make_room_array(t_data *data);
t_room	*make_index_room(t_vert *head, t_room *new_room, int index);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);
void	init_vert(t_vert *room);
void	init_room(t_room *room);
void	init_ant(t_ant *ant);

/*
	Error management
*/

void	error_exit(char *error_str);
void	error_exit1(char *error_str, t_data *data);
void	error_exit2(char *error_str, t_data *data, t_verify *verify);

/*
	Freeing functions
*/

void	free_data(t_data *data);
void	free_all(t_data *data, int condition);
void	free_edge(t_edge *head);
void	free_room_arr(t_data *data);
void	free_vert(t_data *data);

void	free_option(t_opt *option);
void	free_path(t_path *path);
void	free_ants(t_data *data);

/*
	Solving functions
*/

t_opt	*solver(t_data *data);
t_opt	*find_all_disjoint_paths(t_data *data, t_room **room);
t_opt	*make_t_opt(t_data *data, t_path *cur_path);

t_path	*bfs(t_data *data, t_room **room);
void	set_queue(t_room **room, int *queue, int index);

void	follow_backwards(t_room **room, int *queue, int index);
void	add_to_queue(t_room **room, t_edge *temp, int *queue, int index);
int		search_int_in_int_array(int index, int *queue);
int		search_int_from_path(t_room **room, int index, int x, int *queue);
void	clean_bfs(t_data *data, t_room **room);
void	init_queue(t_data *data);

t_opt	*vertex_disjoint(t_data *data, t_room **room, t_opt *option);
void	make_residual_path(t_opt *option, t_room **room, int vertex);

void	find_edge_to_delete(t_room **room, t_path *path);
void	set_vertex_queue(t_room **room, int *queue, int index);

/*
	Functions that calculate data
*/

int		calculate_min_for_path(t_opt *option);
int		calculate_paths_used(t_data *data, t_opt *option);
int		calculate_paths(t_opt *option);
void	calculate_ants_in_paths(t_data *data, t_opt *option);

/*
	Functions that locate data
*/

t_vert	*find_room_index(t_vert *head, int target);
t_vert	*find_room_name(t_vert *head, char *target);
t_path	*get_path_head(t_path *path);
t_opt	*get_opt_head(t_opt *option);
t_opt	*get_opt_tail(t_opt *option);

void	print_output(t_data *data, t_opt *option);
void	make_ant_army(t_data *data, t_opt *option);
void	print_paths(t_data *data, t_opt *option);
void	print_flag_modes(t_data *data, t_opt *option);

#endif
