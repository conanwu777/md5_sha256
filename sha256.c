/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 18:38:20 by cwu               #+#    #+#             */
/*   Updated: 2018/07/19 18:38:21 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

unsigned int g_h0;
unsigned int g_h1;
unsigned int g_h2;
unsigned int g_h3;
unsigned int g_h4;
unsigned int g_h5;
unsigned int g_h6;
unsigned int g_h7;

unsigned int g_w[64];

unsigned int g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void			do_step_s(int i, t_v *vp)
{
	unsigned int s0;
	unsigned int s1;
	unsigned int ch;
	unsigned int temp1;
	unsigned int maj;

	s1 = rotate(vp->e, 6) ^ rotate(vp->e, 11) ^ rotate(vp->e, 25);
	ch = (vp->e & vp->f) ^ ((~vp->e) & vp->g);
	temp1 = vp->h + s1 + ch + g_k[i] + g_w[i];
	s0 = rotate(vp->a, 2) ^ rotate(vp->a, 13) ^ rotate(vp->a, 22);
	maj = (vp->a & vp->b) ^ (vp->a & vp->c) ^ (vp->b & vp->c);
	vp->h = vp->g;
	vp->g = vp->f;
	vp->f = vp->e;
	vp->e = vp->d + temp1;
	vp->d = vp->c;
	vp->c = vp->b;
	vp->b = vp->a;
	vp->a = temp1 + s0 + maj;
}

void			perp_stage(int count)
{
	unsigned int	s0;
	unsigned int	s1;
	int				i;

	i = -1;
	while (++i < 16)
	{
		g_w[i] = (g_new[count * 64 + i * 4] << 24)
		+ (g_new[count * 64 + i * 4 + 1] << 16)
		+ (g_new[count * 64 + i * 4 + 2] << 8)
		+ (g_new[count * 64 + i * 4 + 3]);
	}
	i = 15;
	while (++i < 64)
	{
		s0 = rotate(g_w[i - 15], 7) ^ rotate(g_w[i - 15], 18)
		^ (g_w[i - 15] >> 3);
		s1 = rotate(g_w[i - 2], 17) ^ rotate(g_w[i - 2], 19)
		^ (g_w[i - 2] >> 10);
		g_w[i] = g_w[i - 16] + s0 + g_w[i - 7] + s1;
	}
}

void			do_stage_s(int count, t_v *vp)
{
	int	i;

	perp_stage(count);
	vp->a = g_h0;
	vp->b = g_h1;
	vp->c = g_h2;
	vp->d = g_h3;
	vp->e = g_h4;
	vp->f = g_h5;
	vp->g = g_h6;
	vp->h = g_h7;
	i = -1;
	while (++i < 64)
		do_step_s(i, vp);
	g_h0 += vp->a;
	g_h1 += vp->b;
	g_h2 += vp->c;
	g_h3 += vp->d;
	g_h4 += vp->e;
	g_h5 += vp->f;
	g_h6 += vp->g;
	g_h7 += vp->h;
}

void			init_variables(void)
{
	g_h0 = 0x6a09e667;
	g_h1 = 0xbb67ae85;
	g_h2 = 0x3c6ef372;
	g_h3 = 0xa54ff53a;
	g_h4 = 0x510e527f;
	g_h5 = 0x9b05688c;
	g_h6 = 0x1f83d9ab;
	g_h7 = 0x5be0cd19;
}

int				sha256_hash(char *str, char c)
{
	t_v				v;
	unsigned int	count;
	int				i;

	init_variables();
	set_up(str, 's');
	i = -1;
	while (++i < 8)
		g_new[64 * g_cks - i - 1] = ((char*)(&g_len))[i];
	count = -1;
	while (++count < g_cks)
		do_stage_s(count, &v);
	if (c == 'p')
		return (ft_printf("{W}%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
			g_h0, g_h1, g_h2, g_h3, g_h4, g_h5, g_h6, g_h7));
	else if (c == 's')
		return (ft_printf("{B}%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
			g_h0, g_h1, g_h2, g_h3, g_h4, g_h5, g_h6, g_h7));
	else
		return (ft_printf("{Y}%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
			g_h0, g_h1, g_h2, g_h3, g_h4, g_h5, g_h6, g_h7));
}
