#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr_fd("Eroor\nWrong number of arguments\n", 2), 1);
	ft_pasing(av[1]);
	

	// mlx_image_t	*img;
	// mlx_t*    mlx;
	// t_addr *addr;
	// t_player player;

	// addr = NULL;

	// char **map;

	// map = parse_map(addr, "./maps/example.map");
	// player.x = WIDTH/2;
	// player.y = HEIGHT/2;
	// player.turn_direction = 0;
	// player.walk_direction = 0;
	// player.rotation_angle = M_PI / 2;
	// player.move_speed = 3.0;
	// player.rot_speed = 2 * M_PI / 180;

	// TODO protect MLX utils if each one fails
	// mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// if (!mlx)
	// 	exit(EXIT_FAILURE);
	// img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(mlx, img, 0, 0);
	// draw_map(map, img);
	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// ft_lstclear(&addr, free);
	return (EXIT_SUCCESS);
}
