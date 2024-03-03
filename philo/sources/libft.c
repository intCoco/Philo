/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:02:27 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/03 07:48:49 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_calloc(size_t c, size_t l)
{
	char	*s;
	size_t	i;

	s = (void *)malloc(l * c);
	if (!s)
		return (NULL);
	if (l > SIZE_MAX / c)
		return (NULL);
	i = -1;
	while (++i < c * l)
		*(unsigned char *)(s + i) = 0;
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t	i;

	i = 0;
	if (l <= 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
		&& ((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] && i < l - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_bzero(void *s, size_t len)
{
	char	*s2;
	size_t	i;

	s2 = s;
	i = -1;
	while (++i < len)
		s2[i] = '\0';
}

int	ft_ph_atoi(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str[0] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + ((char *)str)[i] - '0';
		i++;
	}
	if (str[i])
		return (INV_CH);
	if (str[0] == '-')
		return (NEG_NB);
	return (ret);
}
