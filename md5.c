/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:12:24 by cwu               #+#    #+#             */
/*   Updated: 2018/07/19 14:12:25 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

unsigned int g_a;
unsigned int g_b;
unsigned int g_c;
unsigned int g_d;

unsigned int g_k[64];
t_bt g_m[16][4];

unsigned int g_coe[64] = {7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

void	do_step(int i, t_v *vp)
{
	if (0 <= i && i < 16)
	{
		vp->f = (vp->b & vp->c) | ((~vp->b) & vp->d);
		vp->g = i;
	}
	else if (16 <= i && i < 32)
	{
		vp->f = (vp->d & vp->b) | ((~vp->d) & vp->c);
		vp->g = (5 * i + 1) & 15;
	}
	else if (32 <= i && i < 48)
	{
		vp->f = vp->b ^ vp->c ^ vp->d;
		vp->g = (3 * i + 5) & 15;
	}
	else
	{
		vp->f = vp->c ^ (vp->b | (~vp->d));
		vp->g = 7 * i & 15;
	}
	vp->f += vp->a + g_k[i] + *((unsigned int*)(g_m[vp->g]));
	vp->a = vp->d;
	vp->d = vp->c;
	vp->c = vp->b;
	vp->b += (vp->f << g_coe[i]) | (vp->f >> (32 - g_coe[i]));
}

void	do_stage(int count, t_v *vp)
{
	int i;
	int j;

	vp->a = g_a;
	vp->b = g_b;
	vp->c = g_c;
	vp->d = g_d;
	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 4)
			g_m[i][j] = g_new[count * 64 + i * 4 + j];
	}
	i = -1;
	while (++i < 64)
		do_step(i, vp);
	g_a += vp->a;
	g_b += vp->b;
	g_c += vp->c;
	g_d += vp->d;
}

void	set_up(char *str, char c)
{
	int		i;
	t_bt	bt;

	g_len = ft_strlen(str) << 3;
	g_cks = (ft_strlen(str) + 8) / 64 + 1;
	g_new = (t_bt*)malloc(64 * g_cks);
	i = -1;
	while (++i < (int)(64 * g_cks))
		g_new[i] = 0;
	i = -1;
	while (str[++i])
		g_new[i] = str[i];
	bt = 1 << 7;
	g_new[ft_strlen(str)] = bt;
	i = -1;
	while (++i < 8)
		if (c == 's')
			g_new[64 * g_cks - i - 1] = ((char*)(&g_len))[i];
		else
			g_new[64 * g_cks - 8 + i] = ((char*)(&g_len))[i];
}

int		md5_hash(char *str, char c)
{
	t_v				v;
	unsigned int	count;
	int				i;

	g_a = 0x67452301;
	g_b = 0xefcdab89;
	g_c = 0x98badcfe;
	g_d = 0x10325476;
	i = -1;
	while (++i < 64)
		g_k[i] = floor(pow(2, 32) * fabs(sin(i + 1)));
	set_up(str, 'm');
	count = -1;
	while (++count < g_cks)
		do_stage(count, &v);
	reverse_bits(&g_a);
	reverse_bits(&g_b);
	reverse_bits(&g_c);
	reverse_bits(&g_d);
	if (c == 'p')
		return (ft_printf("{W}%.8x%.8x%.8x%.8x", g_a, g_b, g_c, g_d));
	else if (c == 's')
		return (ft_printf("{B}%.8x%.8x%.8x%.8x", g_a, g_b, g_c, g_d));
	else
		return (ft_printf("{Y}%.8x%.8x%.8x%.8x", g_a, g_b, g_c, g_d));
}
