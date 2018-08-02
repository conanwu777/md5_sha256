/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 22:35:20 by cwu               #+#    #+#             */
/*   Updated: 2018/05/12 22:35:23 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_table	g_colors[] =
{	{"{BLINK}", "\e[5m"},
	{"{LR}", "\e[38;2;225;100;125m"},
	{"{LY}", "\e[38;2;255;220;65m"},
	{"{LG}", "\e[38;2;185;225;70m"},
	{"{LB}", "\e[38;2;80;220;200m"},
	{"{LP}", "\e[38;2;160;160;255m"},
	{"{W}", "\e[1;38;5;255;255;255m"},
	{"{R}", "\e[1;38;2;225;20;20m"},
	{"{O}", "\e[1;38;2;255;120;10m"},
	{"{Y}", "\e[1;38;2;255;200;0m"},
	{"{G}", "\e[1;38;2;80;200;60m"},
	{"{B}", "\e[1;38;2;50;150;250m"},
	{"{P}", "\e[1;38;2;150;75;255m"},
	{"{BR}", "\e[1;48;2;150;0;0m"},
	{"{BY}", "\e[1;48;2;255;155;0m"},
	{"{BG}", "\e[1;48;2;0;100;25m"},
	{"{BB}", "\e[1;48;2;0;65;140m"},
	{"{BP}", "\e[1;48;2;60;0;125m"},
	{"{E}", "\e[0m"},
	{0, 0}
};

char	*setcolor(const char *restrict fmt)
{
	int		i;
	int		j;
	int		r;
	char	*t;

	r = 0;
	i = 0;
	t = (char*)fmt;
	while (g_colors[i].key)
	{
		if (ft_strstr(fmt, g_colors[i].key))
		{
			t = ft_strstr(fmt, g_colors[i].key);
			write(1, g_colors[i].value, ft_strlen(g_colors[i].value));
			r = 1;
			j = 0;
			while (*t == (g_colors[i].key)[j])
			{
				t++;
				j++;
			}
		}
		i++;
	}
	return (t);
}

void	setbackground(int r, int g, int b)
{
	char *str;

	str = ft_strnew(20);
	str = ft_strcpy(str, "\e[48;2;");
	*(str + 8) = '0' + r * 25 / 100;
	*(str + 9) = '0' + r * 25 % 100 / 10;
	*(str + 10) = '0' + r * 25 % 10;
	*(str + 11) = ';';
	*(str + 12) = '0' + g * 25 / 100;
	*(str + 13) = '0' + g * 25 % 100 / 10;
	*(str + 14) = '0' + g * 25 % 10;
	*(str + 15) = ';';
	*(str + 16) = '0' + b * 25 / 100;
	*(str + 17) = '0' + b * 25 % 100 / 10;
	*(str + 18) = '0' + b * 25 % 10;
	*(str + 19) = 'm';
	write(1, str, 20);
	ft_strdel(&str);
}

void	settext(int r, int g, int b)
{
	char *str;

	str = ft_strnew(20);
	str = ft_strcpy(str, "\e[1;38;2;");
	*(str + 10) = '0' + r / 100;
	*(str + 11) = '0' + r % 100 / 10;
	*(str + 12) = '0' + r % 10;
	*(str + 13) = ';';
	*(str + 14) = '0' + g / 100;
	*(str + 15) = '0' + g % 100 / 10;
	*(str + 16) = '0' + g % 10;
	*(str + 17) = ';';
	*(str + 18) = '0' + b / 100;
	*(str + 19) = '0' + b % 100 / 10;
	*(str + 20) = '0' + b % 10;
	*(str + 21) = 'm';
	write(1, str, 22);
	ft_strdel(&str);
}
