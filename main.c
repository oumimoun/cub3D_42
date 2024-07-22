#include "cub3d.h"



int	main(int ac, char **av)
{
	mlx_t*    mlx;
	mlx_image_t *image;
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
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (ft_putstr_fd("Eroor\nmlx_init\n", 2), ERROR);
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		return (ft_putstr_fd("Eroor\nmlx_new_image\n", 2), ERROR);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return (ft_putstr_fd("Eroor\nmlx_image_to_window\n", 2), ERROR);
	}

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (SUCCESS);
}
