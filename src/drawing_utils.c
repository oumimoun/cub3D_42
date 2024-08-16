#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);
}
void draw_rect(mlx_image_t *img, int x, int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x;
    tmp_y = y;

    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x <= x + SIZE)
    {
        tmp_y = y;
        while (tmp_y <= y + SIZE)
        {
            if (color == 1 && (tmp_y % SIZE) && (tmp_x % SIZE))
                protected_ppx(img, tmp_x, tmp_y, get_rgba(255, 255, 255, 255));
            else
                protected_ppx(img, tmp_x, tmp_y, get_rgba(0, 0, 0, 255));
            tmp_y++;
        }
        tmp_x++;
    }
}



void draw_circle(mlx_image_t *img, int x_center, int y_center)
{
    int x, y;
    int radius = SIZE / 10;
    int radius_squared = radius * radius;

    x = x_center - radius;
    // Iterate over the square bounding box of the circle
    while (x <= x_center + radius)
    {
        y = y_center - radius;
        while (y <= y_center + radius)
        {
            // Check if the point is inside the circle
            int dx = x - x_center;
            int dy = y - y_center;
            if (dx * dx + dy * dy <= radius_squared)
            {
                // Check if the point is within the image boundaries
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                {
                    protected_ppx(img, x, y, get_rgba(255, 0, 0, 255));
                    
                }
            }
            y++;
        }
        x++;
    }
}

double draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    int i;
    i = 0;
    while (!is_wall(data, x2, y2))
    {
        protected_ppx(data->img, x1, y1, get_rgba(255, 0, 0, 255));
        i++;
        if (x1 == x2 && y1 == y2)
            return get_distance(data, x1, y1);
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
    return get_distance(data, x1, y1);
}

double normalize_angle(double angle)
{
    double normalized = fmod(angle, 2 * M_PI);
    if (normalized < 0)
        normalized += 2 * M_PI;
    return normalized;
}


