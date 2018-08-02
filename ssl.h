/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:12:55 by cwu               #+#    #+#             */
/*   Updated: 2018/07/19 14:12:57 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <math.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

typedef int				(*t_f)(char *str, char c);

typedef struct			s_command
{
	char				*str;
	char				*upper;
	t_f					f;
	char				type;
}						t_command;

typedef unsigned char	t_bt;

typedef struct			s_v
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
	unsigned int		e;
	unsigned int		f;
	unsigned int		g;
	unsigned int		h;
}						t_v;

unsigned int			g_cks;
unsigned long long		g_len;
unsigned char			*g_new;

int						md5(char *str, char *file);
int						sha256(char *str, char *file);
int						md5_hash(char *str, char c);
int						sha256_hash(char *str, char c);
void					reverse_bits(unsigned int *c);
unsigned int			rotate(unsigned int nbr, int n);
int						dispatch(char *str, char *file);
void					set_up(char *str, char c);
#endif
