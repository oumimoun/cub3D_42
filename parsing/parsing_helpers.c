/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:22:15 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/02 01:06:11 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*gc_strdup(const char *s, t_addr **addr)
{
	char	*copy;

	if (!s || !s[0])
	{
		copy = (char *)safe_alloc(addr, 1, sizeof(char));
		if (!copy)
			return (NULL);
		copy[0] = '\0';
		return (copy);
	}
	copy = (char *)safe_alloc(addr, (ft_strlen(s) + 1), sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s));
	copy[ft_strlen(s)] = '\0';
	return (copy);
}

char	*gc_substr(char *s, unsigned int start, size_t len, t_addr **addr)
{
	char	*result;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s) || !len)
		return (gc_strdup("", addr));
	if (len + start > (unsigned int)ft_strlen(s))
		len = (unsigned int)ft_strlen(s) - start;
	result = (char *)safe_alloc(addr, (len + 1), sizeof(char));
	if (!result)
		exit(1);
	ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}

char	*gc_strjoin(char *s1, char *s2, t_addr **addr)
{
	char	*arr;
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	dest = s1;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(dest);
	s2_len = ft_strlen(s2);
	arr = (char *)safe_alloc(addr, (s1_len + s2_len + 1), sizeof(char));
	if (!arr)
		return (NULL);
	ft_memmove(arr, dest, s1_len);
	ft_memmove(arr + s1_len, s2, s2_len);
	arr[s1_len + s2_len] = '\0';
	return (arr);
}

static char	*put_str(int n, char *str, int count)
{
	str[count] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		while (--count)
		{
			str[count] = n % 10 + 48;
			n /= 10;
		}
		return (str);
	}
	while (count--)
	{
		str[count] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char	*gc_itoa(int n, t_addr **addr)
{
	size_t	count;
	int		temp;
	char	*str;

	count = 1;
	temp = n;
	while (temp / 10)
	{
		temp /= 10;
		count++;
	}
	if (n < 0)
		count++;
	str = (char *)safe_alloc(addr, sizeof(char), count + 1);
	if (!str)
		return (NULL);
	return (put_str(n, str, count));
}
