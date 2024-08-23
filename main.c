#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_map (t_data *data)
{
	int i;
	int j;
	int x; // 
	int y; // 

	i = 0;
	x = 0;
	y = 0;
	while (i < data->map->map_height) // 
	{
		j = 0;
		y = 0;
		while (j < data->map->map_width) // 
		{
			if (data->map->map_tiles[i][j])
				draw_rect(data->img, y, x, (int)data->map->map_tiles[i][j] - 48);
			else 
				draw_rect(data->img,y, x, 0);
			j++;
			y += SIZE;
		}
		i++;
		x += SIZE;
	}
}

void f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data *data;
	t_map *map;

	if (ac != 2)
		return (ft_putstr_fd("Eroor\nWrong number of arguments\n", 2), ERROR);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	data->addr = NULL;
	data->map = ft_calloc_ac(&data->addr,1 , sizeof(t_map));
	if (!data->map)
		return (free(data), ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	if (ft_parsing(av[1], data) == ERROR)
		return (free(data), ft_addrclear(&data->addr, free), ERROR);
	data->player.x = data->map->player_x * SIZE + SIZE / 2;
	data->player.y = data->map->player_y * SIZE + SIZE / 2;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	if (data->map->player_direction == 'N')
		data->player.rotation_angle = 3 * M_PI / 2;
	else if (data->map->player_direction == 'S')
		data->player.rotation_angle = M_PI / 2;
	else if (data->map->player_direction == 'E')
		data->player.rotation_angle = 0;
	else if (data->map->player_direction == 'W')
		data->player.rotation_angle = M_PI;

	data->rays.ray_angle = 0;
	data->rays.x_horiz_intersection = 0;
	data->rays.y_horiz_intersection = 0;
	data->rays.x_vertic_intersection = 0;
	data->rays.y_vertic_intersection = 0;
	
	data->rays.distance = 0;
	data->rays.is_horizontal = 0;
	data->rays.is_vertical = 0;
	data->rays.column_id = 0;
	data->rays.wall_hit_x = 0;
	data->rays.wall_hit_y = 0;
	data->rays.is_facing_down = 0;
	data->rays.is_facing_up = 0;
	data->rays.is_facing_right = 0;
	data->rays.is_facing_left = 0;
	data->rays.x_step = 0;
	data->rays.y_step = 0;
	


	
	// TODO protect MLX utils if each one fails
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data->mlx)
		exit(ERROR);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		exit(ERROR);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	draw_map(data);
	draw_player(data);
	mlx_loop_hook(data->mlx, &key_event_handler, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_addrclear(&data->addr, free);
	free(data);
	// atexit(f);
	return (EXIT_SUCCESS);
}
