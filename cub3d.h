#ifndef CUB3D_H
#define CUB3D_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include "MLX42/include/MLX42/MLX42.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>

#define WIDTH 1088
#define HEIGHT 704

#define ERROR 1
#define SUCCESS 0

#define SIZE 32
#define FOV_ANGL (60 * M_PI / 180)
#define MOVE_SPEED 2.0
#define ROT_SPEED (2 * M_PI / 180)

typedef struct s_map
{
	double player_x;
    double player_y;
    int tile_size;
	int map_width;
	int map_height;
	char **map_tiles;
	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	char *f_color;
	char *c_color;
	char player_direction;
	char *single_line_map;
	char *single_line_vars;

} t_map;

typedef struct s_player
{
	double x;  // player x position in pixels
	double y;  // player y position in pixels
	double turn_direction; // -1 if left, 1 if right
	double walk_direction; // -1 if back, 1 if front
	double rotation_angle; // player rotation angle in radians
} t_player;

typedef struct s_point
{
	double x;
	double y;
} t_point;

typedef struct dda_step
{
	double d_x;
	double d_y;
	t_point start;
	t_point end;
	int distance;
} t_dda;


typedef struct s_ray
{
	int 			column_id;
	double			ray_angle;
	double			x_horiz_intersection;
	double			y_horiz_intersection;

	double			x_vertic_intersection;
	double			y_vertic_intersection;
	
	double			distance;
	int				is_horizontal;
	int				is_vertical;
	int 			is_facing_down;
	int 			is_facing_up;
	int 			is_facing_right;
	int 			is_facing_left;
	int 			wall_hit_x;
	int 			wall_hit_y;

	double			x_step;
	double			y_step;

	int 			found_horz_hit;
	int 			found_vert_hit;


}					t_ray;

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t	*mlx;
	t_addr *addr;
	t_player player;
	t_map *map;
	t_ray rays;
}	t_data;

int		add_addr(t_addr **list, t_addr *new);
void	*ft_calloc_ac(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
void	ft_addrclear(t_addr **lst, void (*del)(void *));


void key_event_handler(void *arg);
int get_rgba(int r, int g, int b, int a);
void protected_ppx(mlx_image_t *img, int x, int y, int color);
void clear_screen(mlx_image_t *img, int color);
// void parse_map(t_data *data, char *filename);
void draw_rect(mlx_image_t *img, int x , int y, int color);
void draw_player(t_data *data);
void draw_circle(mlx_image_t *img, int x0, int y0);
void draw_map (t_data *data);
double draw_line(t_data *data, int x1, int y1, int x2, int y2);
double normalize_angle(double angle);
// dda
int is_wall(t_data *data, int x, int y);
double get_distance(t_data *data, double x, double y);
void draw_rays(t_data *data); // change name later

void line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);


//=======================================================================
//                             parsing                                 //
//=======================================================================


char *get_next_line(int fd, t_data *data);
int ft_parsing(char *map_path, t_data *data);
// int ft_strcmp(const char *s1, const char *s2);
int ft_parsing_map(char *map_path, t_data *data);
int ft_save_vars(char *map_path, t_data *data);
int ft_valide_wall_direction(char *line);
int ft_check_vars(t_data *data);
int ft_save_player_pos(t_data *data);
char *ft_bring_map(int fd, t_data *data);
char	**ft_split(char const *s, char c, t_data *data);
int ft_has_tabs(t_data *data);
int ft_split_map(t_data *data);

char	*gc_substr(char *s, unsigned int start, size_t len, t_addr **addr);
char	*gc_strdup(const char *s, t_addr **addr);
char	*gc_strjoin(char *s1, char *s2, t_addr **addr);
int ft_check_players(t_data *data);
int ft_fill_map_dimension(t_data *data);

int ft_valide_map(t_data *data);

int ft_double_check_vars(t_data *data);
int ft_fill_map_with_sp(t_data *data);

#endif