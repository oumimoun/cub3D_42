/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:45 by olamrabt          #+#    #+#             */
/*   Updated: 2024/08/18 15:24:24 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	if (!str)
		return 0;
	if (!*str)
		return (0);
	return (1 + ft_strlen(str + 1));
}
