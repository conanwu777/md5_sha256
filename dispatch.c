/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:12:03 by cwu               #+#    #+#             */
/*   Updated: 2018/07/19 14:12:08 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

bool g_p;
bool g_q;
bool g_r;
bool g_s;
t_command	g_cmd;

int				dispatch_2(char *str, char *file)
{
	if (g_r)
	{
		g_cmd.f(str, 'f');
		ft_printf("{Y} %s\n", file);
	}
	else if (g_s)
	{
		ft_printf("{B}%s (\"%s\") = ", g_cmd.upper, str);
		g_cmd.f(str, 's');
		ft_printf("\n");
	}
	else
	{
		ft_printf("{Y}%s (%s) = ", g_cmd.upper, file);
		g_cmd.f(str, 'f');
		ft_printf("\n");
	}
	return (0);
}

int				dispatch(char *str, char *file)
{
	if (g_p)
	{
		ft_printf("{W}%s", str);
		g_cmd.f(str, 'p');
		ft_printf("\n");
		g_p = 0;
	}
	else if (g_q || (!g_s && !file && !g_p))
	{
		g_cmd.f(str, 'p');
		ft_printf("\n");
	}
	else if (g_r && g_s)
	{
		g_cmd.f(str, 's');
		ft_printf("{B} \"%s\"\n", str);
	}
	else
		dispatch_2(str, file);
	return (0);
}

unsigned int	rotate(unsigned int nbr, int n)
{
	int				i;
	unsigned int	bit;

	i = 0;
	while (i < n)
	{
		bit = (nbr & 1) << 31;
		nbr = nbr >> 1;
		nbr += bit;
		i++;
	}
	return (nbr);
}

void			reverse_bits(unsigned int *c)
{
	unsigned int t;

	t = 0;
	t += *c & 0xff;
	t = t << 8;
	t += (*c >> 8) & 0xff;
	t = t << 8;
	t += (*c >> 16) & 0xff;
	t = t << 8;
	t += (*c >> 24) & 0xff;
	*c = t;
}
