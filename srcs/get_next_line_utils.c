/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:46:56 by mgwyness          #+#    #+#             */
/*   Updated: 2022/01/16 20:16:20 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_str_len(char *reserved)
{
	int	len;

	len = 0;
	while (reserved[len] != '\n' && reserved[len] != '\0')
		len++;
	if (reserved[len] == '\n')
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	int		len_d;

	i = 0;
	len_d = ft_strlen(dst);
	while (i < n && src[i] != '\0')
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2, int count)
{
	char	*arr;
	int		len_s1;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (len_s1 + count) + 1);
	if (arr == 0)
		return (0);
	arr[0] = 0;
	ft_strncat(arr, s1, -1);
	ft_strncat(arr, s2, count);
	free(s1);
	return (arr);
}
