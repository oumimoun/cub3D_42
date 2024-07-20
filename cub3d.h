#ifndef CUB3D_H
#define CUB3D_H

#include "./MLX42/include/MLX42/MLX42.h"
#include "./Libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>


#define WIDTH 500
#define HEIGHT 500
#define SIZE 20

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00



typedef struct s_map
{
    int        map_width;
    int        map_height;
    int        player_x;
    int        player_y;
    char    **map;
    char    *no_texture_path;
    char    *so_texture_path;
    char    *we_texture_path;
    char    *ea_texture_path;
    char    *f_color;
    char    *c_color;
}    t_map;


typedef struct player
{
	int x;
	int y;
	int turn_direction;
	int walk_direction;
	double rotation_angle;
	double move_speed;
	double rot_speed;
} t_player;

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;





#endif