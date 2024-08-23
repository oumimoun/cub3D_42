#include "../cub3d.h"

double get_distance(t_data *data, double x, double y)
{
    double delta_x;
    double delta_y;

    delta_x = x - data->player.x;
    delta_y = y - data->player.y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

int is_wall(t_data *data, int x, int y)
{
    int map_x;
    int map_y;

    map_x = floor(x / (data->map->tile_size));
    map_y = floor(y / (data->map->tile_size));

    if (map_x < 0 || map_x >= data->map->map_width || map_y < 0 || map_y >= data->map->map_height)
        return 1;
    if (data->map->map_tiles[map_y][map_x])
    {
        if (data->map->map_tiles[map_y][map_x] == '1')
            return 1;
    }

    return 0;
}

void clear_screen(mlx_image_t *img, int color)
{
    int x, y;
    for (y = 0; y < HEIGHT; ++y)
    {
        for (x = 0; x < WIDTH; ++x)
            protected_ppx(img, x, y, color);
    }
}

void render_wall(t_data *data, int distance, int x)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    double scale;

    scale = 2;
    // if (!distance)
    //     distance = 1;
    if (!distance)
        return;
    wall_height = ((int)(HEIGHT / distance) * scale);
    wall_top = (HEIGHT - wall_height) / 2;
    wall_bottom = (HEIGHT + wall_height) / 2;

    // printf("wall_top : %d\n", wall_top);
    while (wall_top < wall_bottom)
    {
        wall_top++;
        protected_ppx(data->img, x, wall_top, get_rgba(255, 200, 0, 255));
    }
}
int is_up(double angle)
{
    return (angle > M_PI);
}

int is_right(double angle)
{
    return (angle >= (3 * M_PI / 2) || angle <= M_PI / 2);
}

double get_alpha(double ray_angle)
{
    if (is_right(ray_angle) && is_up(ray_angle))
        return (2 * M_PI) - ray_angle;
    if (!is_right(ray_angle) && is_up(ray_angle))
        return ray_angle - M_PI;
    if (is_right(ray_angle) && !is_up(ray_angle))
        return ray_angle;
    if (!is_right(ray_angle) && !is_up(ray_angle))
        return M_PI - ray_angle;
    return 0;
}

t_dda get_hor_inters(t_data *data, double angle)
{
    t_dda step;

    step.start.y = floor(data->player.y / SIZE) * SIZE;
    if (!is_up(angle))
        step.start.y += SIZE;
    step.d_x = 0;
    if (tan(get_alpha(angle)) > 1e-6)
        step.d_x = fabs(step.start.y - data->player.y) / tan(get_alpha(angle));
    if (!is_right(angle))
        step.d_x *= -1;
    step.start.x = data->player.x + step.d_x;

    step.end.y = step.start.y - SIZE;
    if (!is_up(angle))
        step.end.y += 2 * SIZE;
    step.d_x = 0;
    if (tan(get_alpha(angle)) > 1e-6)
        step.d_x = SIZE / tan(get_alpha(angle));
    if (!is_right(angle))
        step.d_x *= -1;
    step.end.x = step.start.x + step.d_x;

    if (step.end.x < 0)
        step.end.x = 0;

    step.d_y = step.end.y - step.start.y;
    step.distance = sqrt(pow(step.end.x - step.start.x, 2) + pow(step.end.y - step.start.y, 2));
    return step;
}

t_dda get_vert_inters(t_data *data, double angle)
{
    t_dda step;

    step.start.x = (floor(data->player.x / SIZE) * SIZE) + SIZE; //
    if (!is_right(angle))
        step.start.x -= SIZE;
    step.start.y = data->player.y + (step.start.x - data->player.x) * tan(angle);

    step.d_x = SIZE;
    if (!is_right(angle))
        step.d_x *= -1;
    step.d_y = step.d_x * tan(angle);
    step.end.x = step.start.x + step.d_x;
    step.end.y = step.start.y + step.d_y;

    if (step.end.x < 0)
        step.end.x = 0;
    if (step.end.y < 0)
        step.end.y = 0;
    step.distance = sqrt(pow(step.end.x - step.start.x, 2) + pow(step.end.y - step.start.y, 2));

    return step;
}

// double ft_dda(t_data *data, int column_id)
// {
//     // first horizontal intersection
//     if (data->rays.is_facing_up)
//         data->rays.y_horiz_intersection = floor(data->player.y / SIZE) * SIZE;
//     else if (data->rays.is_facing_down)
//         data->rays.y_horiz_intersection = floor(data->player.y / SIZE) * SIZE + SIZE;
//     data->rays.x_horiz_intersection = data->player.x + fabs(data->rays.y_horiz_intersection - data->player.y) / tan(data->rays.ray_angle);

//     // horizontal step
//     data->rays.y_step = SIZE;
//     if (data->rays.is_facing_up)
//         data->rays.y_step *= -1;
//     data->rays.x_step = data->rays.y_step / tan(data->rays.ray_angle);
//     if (data->rays.is_facing_left && data->rays.x_step > 0)
//         data->rays.x_step *= -1;
//     if (data->rays.is_facing_right && data->rays.x_step < 0)
//         data->rays.x_step *= -1;

//     double  next_hor_x = data->rays.x_horiz_intersection;
//     double  next_hor_y = data->rays.y_horiz_intersection;

//     if (data->rays.is_facing_up)
//         next_hor_y--;

//     while (next_hor_x >= 0 && next_hor_x < WIDTH && next_hor_y >= 0 && next_hor_y < HEIGHT)
//     {
//         if (is_wall(data, next_hor_x, next_hor_y))
//         {
//             data->rays.found_horz_hit = 1;
//             data->rays.wall_hit_x = next_hor_x;
//             data->rays.wall_hit_y = next_hor_y;
//             line(data->img, data->player.x, data->player.y, next_hor_x, next_hor_y, get_rgba(255, 50, 0, 255));
//             // protected_ppx(data->img, next_hor_x, next_hor_y, get_rgba(255, 50, 0, 255));
//             break;
//         }
//         next_hor_x += data->rays.x_step;
//         next_hor_y += data->rays.y_step;
//     }

//     // first vertical intersection

//     if (data->rays.is_facing_right)
//         data->rays.x_vertic_intersection = floor(data->player.x / SIZE) * SIZE + SIZE;
//     else if (data->rays.is_facing_left)
//         data->rays.x_vertic_intersection = floor(data->player.x / SIZE) * SIZE;

//     data->rays.y_vertic_intersection = data->player.y + fabs(data->rays.x_vertic_intersection - data->player.x) * tan(data->rays.ray_angle);

//     // vertical step

//     data->rays.x_step = SIZE;
//     if (data->rays.is_facing_left)
//         data->rays.x_step *= -1;
//     data->rays.y_step = data->rays.x_step * tan(data->rays.ray_angle);

//     if (data->rays.is_facing_up && data->rays.y_step > 0)
//         data->rays.y_step *= -1;
//     if (data->rays.is_facing_down && data->rays.y_step < 0)
//         data->rays.y_step *= -1;

//     double  next_vert_x = data->rays.x_vertic_intersection;
//     double  next_vert_y = data->rays.y_vertic_intersection;

//     if (data->rays.is_facing_left)
//         next_vert_x--;

//     while (next_vert_x >= 0 && next_vert_x < WIDTH && next_vert_y >= 0 && next_vert_y < HEIGHT)
//     {
//         if (is_wall(data, next_vert_x, next_vert_y))
//         {
//             data->rays.found_vert_hit = 1;
//             data->rays.wall_hit_x = next_vert_x;
//             data->rays.wall_hit_y = next_vert_y;
//             line(data->img, data->player.x, data->player.y, next_vert_x, next_vert_y, get_rgba(255, 50, 0, 255));
//             // protected_ppx(data->img, next_vert_x, next_vert_y, get_rgba(255, 50, 0, 255));
//             break;
//         }
//         next_vert_x += data->rays.x_step;
//         next_vert_y += data->rays.y_step;
//     }

// }

double ft_dda(t_data *data, int column_id)
{
    // Horizontal intersection calculation
    if (data->rays.is_facing_up)
        data->rays.y_horiz_intersection = floor(data->player.y / SIZE) * SIZE - 1;
    else
        data->rays.y_horiz_intersection = floor(data->player.y / SIZE) * SIZE + SIZE;

    data->rays.x_horiz_intersection = data->player.x +
        (data->rays.y_horiz_intersection - data->player.y) / tan(data->rays.ray_angle);

    // Horizontal step calculation
    data->rays.y_step = (data->rays.is_facing_up) ? -SIZE : SIZE;
    data->rays.x_step = SIZE / tan(data->rays.ray_angle);

    if ((data->rays.is_facing_left && data->rays.x_step > 0) || 
        (data->rays.is_facing_right && data->rays.x_step < 0))
        data->rays.x_step = -data->rays.x_step;

    double next_hor_x = data->rays.x_horiz_intersection;
    double next_hor_y = data->rays.y_horiz_intersection;

    // Horizontal DDA loop
    while (next_hor_x >= 0 && next_hor_x < WIDTH && next_hor_y >= 0 && next_hor_y < HEIGHT)
    {
        if (is_wall(data, next_hor_x, next_hor_y))
        {
            data->rays.found_horz_hit = 1;
            data->rays.wall_hit_x = next_hor_x;
            data->rays.wall_hit_y = next_hor_y;
            line(data->img, data->player.x, data->player.y, next_hor_x, next_hor_y, get_rgba(255, 50, 0, 255));
            break;
        }
        next_hor_x += data->rays.x_step;
        next_hor_y += data->rays.y_step;
    }

    // Vertical intersection calculation
    if (data->rays.is_facing_right)
        data->rays.x_vertic_intersection = floor(data->player.x / SIZE) * SIZE + SIZE;
    else
        data->rays.x_vertic_intersection = floor(data->player.x / SIZE) * SIZE - 1;

    data->rays.y_vertic_intersection = data->player.y +
        (data->rays.x_vertic_intersection - data->player.x) * tan(data->rays.ray_angle);

    // Vertical step calculation
    data->rays.x_step = (data->rays.is_facing_left) ? -SIZE : SIZE;
    data->rays.y_step = data->rays.x_step * tan(data->rays.ray_angle);

    if ((data->rays.is_facing_up && data->rays.y_step > 0) ||
        (data->rays.is_facing_down && data->rays.y_step < 0))
        data->rays.y_step = -data->rays.y_step;

    double next_vert_x = data->rays.x_vertic_intersection;
    double next_vert_y = data->rays.y_vertic_intersection;

    // Vertical DDA loop
    while (next_vert_x >= 0 && next_vert_x < WIDTH && next_vert_y >= 0 && next_vert_y < HEIGHT)
    {
        if (is_wall(data, next_vert_x, next_vert_y))
        {
            data->rays.found_vert_hit = 1;
            data->rays.wall_hit_x = next_vert_x;
            data->rays.wall_hit_y = next_vert_y;
            line(data->img, data->player.x, data->player.y, next_vert_x, next_vert_y, get_rgba(255, 50, 0, 255));
            break;
        }
        next_vert_x += data->rays.x_step;
        next_vert_y += data->rays.y_step;
    }

    // Calculate the distance to the closest intersection (either horizontal or vertical)
    double horz_dist = (data->rays.found_horz_hit) ?
        sqrt(pow(next_hor_x - data->player.x, 2) + pow(next_hor_y - data->player.y, 2)) : INFINITY;
    double vert_dist = (data->rays.found_vert_hit) ?
        sqrt(pow(next_vert_x - data->player.x, 2) + pow(next_vert_y - data->player.y, 2)) : INFINITY;

    return fmin(horz_dist, vert_dist);
}


// Bresenham's Line Drawing Algorithm
void line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        protected_ppx(img, x1, y1, color); // Set the pixel at the current position

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_rays(t_data *data)
{
    double angle_i = FOV_ANGL / WIDTH;
    double initial_ray_angle = normalize_angle(data->player.rotation_angle - (FOV_ANGL / 2));

    int column_id = 0;
    while (column_id < WIDTH)
    {
        data->rays.ray_angle = normalize_angle(initial_ray_angle + column_id * angle_i);
        data->rays.is_facing_down = data->rays.ray_angle > 0 && data->rays.ray_angle < M_PI;
        data->rays.is_facing_up = !data->rays.is_facing_down;
        data->rays.is_facing_right = data->rays.ray_angle < (M_PI / 2) || data->rays.ray_angle > (3 * M_PI / 2);
        data->rays.is_facing_left = !data->rays.is_facing_right;

        data->rays.found_horz_hit = 0;
        data->rays.found_vert_hit = 0;

        ft_dda(data, column_id);

        // Move on to the next ray
        column_id++;
    }
}
