/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:16:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/25 15:47:22 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_duplicated_vars(char *var, char *line)
{
    char *first_pos;
    char *next_pos;
    size_t var_len = strlen(var);

    first_pos = ft_strnstr(line, var, strlen(line));
    if (first_pos)
    {
        next_pos = ft_strnstr(first_pos + var_len, var, strlen(line) - (first_pos + var_len - line));
        if (next_pos)
        {
            return ERROR;
        }
    }
    return SUCCESS;
}

int ft_missing_vars(char *var, char *line)
{
    if (ft_strnstr(line, var, strlen(line)) == NULL)
    {
        printf("Missing variable: %s\n", var);
        return ERROR;
    }
    return SUCCESS;
}

int ft_double_check_vars(t_data *data)
{
    char *line;

    line = data->map_info->single_line_vars;
    if (ft_duplicated_vars("EA", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("NO", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("WE", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("SO", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("F", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("C", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("EA", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("NO", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("WE", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("SO", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("F", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("C", line) == ERROR)
        return ERROR;
    return SUCCESS;
}
