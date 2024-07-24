/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:25:51 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/24 18:08:42 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_fill_map_dimension(t_data *data)
{
    int i = 0;
    int max_width = 0;
    char **map;

    if (!data)
        return ERROR;
    map = data->map_info->map;
    while (map[i])
    {
        int line_length = ft_strlen(map[i]);
        if (line_length > max_width)
            max_width = line_length;
        i++;
    }
    if (i == 0)
        return ERROR;
    data->map_info->map_width = max_width;
    printf("map_width:-->%d\n", data->map_info->map_width);
    data->map_info->map_height = i;
    printf("map_height:-->%d\n", data->map_info->map_height);
    return SUCCESS;
}

int ft_only_ones(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '1')
            return ERROR;
        i++;
    }
    return SUCCESS;
}

int ft_start_with_one(t_data *data)
{
    char **map;
    map = data->map_info->map;
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] != '1')
            return ERROR;
        i++;
    }
    return SUCCESS;
}

int ft_valide_map(t_data *data)
{
    char **temp;
    temp = data->map_info->map;
    int i;
    int j;

    i = 0;

    printf("-%s-\n", temp[0]);
    printf("-%s-\n", temp[data->map_info->map_height - 1]);
    if (ft_only_ones(temp[0]) == ERROR)
        return ERROR;
    if (ft_only_ones(temp[data->map_info->map_height - 1]) == ERROR)
        return ERROR;

    if (ft_start_with_one(data) == ERROR)
        return ERROR;


    while (temp[i])
    {
        j = 0;
        while (temp[i][j])
        {
            if (temp[i][j] == '0')
            {
                if (temp[i][j + 1] == ' ' || temp[i][j + 1] == '\0')
                {
                    
                }
                
            }
            
        }
        i++;
    }
    return SUCCESS;
}