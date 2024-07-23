/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:15:51 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/22 22:17:45 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

int		flag(char *str);
char	*get_next_line(int fd);
char	*ft_read_buffer(int fd, char *buff, char *line);
char	*ft_new_line(char *temp);
char	*ft_the_next_line(char *buff);

#endif