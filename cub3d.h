#ifndef CUB3D_H
#define CUB3D_H


# define ERROR 1
# define SUCCESS 0
# define TILE_SIZE 32
# define PI 3.14159265
# define FOV 60
#include "./MLX42/include/MLX42/MLX42.h"
#include "./Libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>


#define WIDTH 1088
#define HEIGHT 704
#define SIZE 64
#define BPP sizeof(int32_t)

#define BLACK  0x000000
#define WHITE  0xFFFFFF
#define RED    0xFF0000
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00



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
    char    player_direction;
    char *single_line_map;
    char *single_line_vars;

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

typedef struct s_data
{
    struct s_map *map_info;
    // struct s_addr *addr;
    struct player *player;
    char        *mlx_addr;
    int bpp;
    int line_length;
    int endian;
    mlx_t   *mlx;
    mlx_image_t *image;
	int		bits_per_pixel;
	
    void *window;
}   t_data;



int ft_parsing(char *map_path, t_data *data);
int	ft_strcmp(const char *s1, const char *s2);
int ft_parsing_map(char *map_path, t_data *data);
int ft_save_vars(char *map_path, t_data *data);
int ft_valide_wall_direction(char *line);
int ft_check_vars(t_data *data);
int ft_save_player_pos(t_data *data);
char *ft_bring_map(int fd);

int ft_has_tabs(t_data *data);
int ft_split_map(t_data *data);

int ft_check_players(t_data *data);
int ft_fill_map_dimension(t_data *data);


int ft_valide_map(t_data *data);

int ft_double_check_vars(t_data *data);
int ft_init_vars(t_data *data);
int ft_fill_map_with_sp(t_data *data);










#endif
