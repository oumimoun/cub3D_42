/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:56:26 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/29 12:05:12 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

void my_mlx_pixel_put(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
    {
        mlx_put_pixel(img, x, y, color);
    }
}


void ft_2d_map(t_data *data)
{
    int x, y;
    int i = 0, j;
    uint32_t color = BLACK;
    char **map = data->map_info->map;

    while (i < data->map_info->map_height)
    {
        j = 0;
        while (j < data->map_info->map_width)
        {
            if (map[i][j] == '1')
                color = 0x0000FFFF;
            else if (map[i][j] == '0')
                color = 0xFFFFFFFF;
            else
                color = 0x000000FF;
            
            for (y = i * TILE_SIZE; y < (i + 1) * TILE_SIZE; y++)
            {
                for (x = j * TILE_SIZE; x < (j + 1) * TILE_SIZE; x++)
                {
                    my_mlx_pixel_put(data->image, x, y, color);
                }
            }
            j++;
        }
        i++;
    }
}

void fill_screen_black(t_data *data)
{
    uint32_t x, y;

    for (y = 0; y < data->image->height; y++)
    {
        for (x = 0; x < data->image->width; x++)
        {
            mlx_put_pixel(data->image, x, y, 0x000000FF);
        }
    }
}

int ft_init_vars(t_data *data)
{

    if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false)))
        return (ft_putstr_fd("Eroor\nmlx_init\n", 2), ERROR);

    data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (!data->image)
        return ERROR;

    if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        return (ft_putstr_fd("Eroor\nmlx_image_to_window\n", 2), ERROR);
    }

    // mlx_put_pixel(data->image, 0, 0, 0xFF0000FF);
    fill_screen_black(data);
    ft_2d_map(data);
    // mlx_loop_hook(data->mlx, ft_hook, data->mlx);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return SUCCESS;
}
