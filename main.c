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
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
		return (ft_putstr_fd("Eroor\nmlx_init\n", 2), ERROR);

	mlx_texture_t* texture = mlx_load_png("./textures/color_bg.png");
  	if (!texture)
        return ERROR;

	data->image = mlx_texture_to_image(data->mlx, texture);
  	if (!data->image)
        return ERROR;

	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return (ft_putstr_fd("Eroor\nmlx_image_to_window\n", 2), ERROR);
	}
	mlx_put_pixel(data->image, 0, 0, 0xFF0000FF);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->image);
  	mlx_delete_texture(texture);
	mlx_terminate(data->mlx);
	return (SUCCESS);
}
