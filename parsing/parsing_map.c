/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:49:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/23 08:58:15 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_valid_char(char c)
{
    if (c == '\n')
        return 1;
    if (c == ' ')
        return 1;
    if (c == '0')
        return 1;
    if (c == '1')
        return 1;
    if (c == 'N')
        return 1;
    if (c == 'S')
        return 1;
    if (c == 'E')
        return 1;
    if (c == 'W')
        return 1;
    return 0;
}

int ft_check_random_chars(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (!ft_valid_char(line[i]))
            return (ERROR);
        i++;
    }
    return SUCCESS;
}

int ft_parsing_map(char *map_path, t_data *data)
{
    int fd;
    char *line;

    (void)data;
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return ERROR;
    line = get_next_line(fd);
    printf("[%d] line: |%s|\n", fd, line);
    while (line)
    {
        int  i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if ((line[i] == '0' || line[i] == '1'))
            break;
        line = get_next_line(fd);
    }
    while (line)
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        // printf("line: |%s|\n", line);
        // printf("index: |%d|\n", i);
        // printf("char: |%c|\n", line[i]);
        if (line[i] == '\n')
            return ERROR;
        if (ft_check_random_chars(&line[i]) == ERROR)
            return ERROR;
        line = get_next_line(fd);
    }
    close(fd);
    return SUCCESS;
}
