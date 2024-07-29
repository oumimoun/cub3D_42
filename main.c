#include "cub3d.h"


int	main(int ac, char **av)
{
	t_data *data;
	t_map *map_info;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	map_info = malloc(sizeof(t_map));
	if (!map_info)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	data->map_info = map_info;
	if (ac != 2)
		return (ft_putstr_fd("Eroor\nWrong number of arguments\n", 2), ERROR);
	if (ft_parsing(av[1], data) == ERROR)
		return (ERROR);
	////////////////////////////////////////////
	if (ft_init_vars(data) == ERROR)
		return ERROR;

	return (SUCCESS);
}
