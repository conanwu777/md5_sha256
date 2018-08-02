/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:12:42 by cwu               #+#    #+#             */
/*   Updated: 2018/07/19 14:12:44 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static t_command	g_command[] =
{	{"md5", "MD5", &md5_hash, 'd'},
	{"sha256", "SHA256", &sha256_hash, 'd'},
	{0, 0, 0, 0}
};

bool g_p = 0;
bool g_q = 0;
bool g_r = 0;
bool g_s = 0;

t_command	g_cmd;

void	get_command(int ac, char **av)
{
	int i;

	if (ac == 1)
	{
		ft_printf("{O}usage: ft_ssl command [command opts] [command args]\n");
		exit(1);
	}
	i = -1;
	while (g_command[++i].str)
		if (!ft_strcmp(av[1], g_command[i].str))
		{
			g_cmd = g_command[i];
			break ;
		}
	if (!g_command[i].str)
	{
		ft_printf("{R}ft_ssl: Error: '%s' is an invalid command.\n\n", av[1]);
		ft_printf("{Y}\tStandard commands:\n\tMessage Digest commands:");
		i = -1;
		while (g_command[++i].str)
			if (g_command[i].type == 'd')
				ft_printf("{Y} %s", g_command[i].str);
		ft_printf("{Y}\n\tCipher commands:\n\n");
		exit(1);
	}
}

int		get_flags(char **av)
{
	int i;

	i = 2;
	while (av[i] && av[i][0] == '-' && ft_strlen(av[i]) == 2)
	{
		if (av[i][1] == 'p')
			g_p = 1;
		else if (av[i][1] == 'q')
			g_q = 1;
		else if (av[i][1] == 'r')
			g_r = 1;
		else if (av[i][1] == 's')
			g_s = 1;
		else
			break ;
		i++;
	}
	return (i);
}

int		process_files(int i, char **av)
{
	int		fd;
	char	c;
	char	*buf;

	while (av[i])
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			ft_printf("{R}ft_ssl: %s: %s: No such file or directory\n",
				g_cmd.str, av[i]);
		else
		{
			buf = "\0";
			while (read(fd, &c, 1))
				buf = cw_stradd(buf, &c, 1);
			dispatch(buf, av[i]);
		}
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		i;
	char	c;
	char	*buf;

	get_command(ac, av);
	i = get_flags(av);
	if (g_p || !av[i])
	{
		buf = "\0";
		while (read(0, &c, 1))
			buf = cw_stradd(buf, &c, 1);
		dispatch(buf, av[i]);
	}
	if (g_s)
	{
		if (!av[i])
			return (dispatch("", NULL));
		else
			dispatch(av[i], NULL);
		g_s = 0;
		i++;
	}
	return (process_files(i, av));
}
