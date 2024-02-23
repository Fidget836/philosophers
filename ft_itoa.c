/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:10:33 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/17 07:38:41 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_len(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			i;
	long int	nb;

	nb = (long int)n;
	i = ft_len(n);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb < 0)
		nb = -nb;
	i--;
	while (nb)
	{
		result[i--] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		result[i] = '-';
	result[ft_len(n)] = 0;
	return (result);
}
