
#include "../includes/lem_in.h"

void	make_residual_path(t_option *option, t_room **room)
{
	while (option)
	{
		while (option->path->next)
		{
			while (room[option->path->index]->edge)
			{
				if (room[option->path->index]->edge->room == option->path->next->index)
					room[option->path->index]->edge->room = -1;
				room[option->path->index]->edge = room[option->path->index]->edge->next;
			}
			option->path = option->path->next;
		}
		option = option->next;
	}
}

t_option	*vertex_disjoint(t_data *data, t_room **room, t_option *option)
{
	t_option	*new_option;

	make_residual_path(option, room);

	// saving the bfs_previouses might help in here
	// But would have to save ONLY the used ones.

	// Do we use bfs here or make another similiar algo..?

	new_option = find_all_disjoin_paths(data, room);
	return (new_option);
}
