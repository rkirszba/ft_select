/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:46:25 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 21:11:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		g_sig = 0;

void	handle_term_sig(int signum)
{
	(void)signum;
	set_term_mode(g_selecter, 1);
	free_manager(g_selecter);
	exit(1);
}

void	handle_winch_sig(int signum)
{
	(void)signum;
	del_lines(g_selecter);
	ioctl(0, TIOCGWINSZ, &(g_selecter->termsize));
	del_lines(g_selecter);
	if (g_sig != 1)
		write_args(g_selecter);
	g_sig = 0;
	ioctl(0, TIOCSTI, "a");
}

void	handle_afterstop_sig(int signum)
{
	(void)signum;
	signals_manager();
	signal(SIGTSTP, handle_stop_sig);
	g_sig = 0;
	if (set_term_mode(g_selecter, 0))
		g_sig = -1;
	tputs(tgetstr("ti", NULL), 1, &outc);
	tputs(g_selecter->cmds.hide_curs, 1, &outc);
	ioctl(0, TIOCGWINSZ, &(g_selecter->termsize));
	write_args(g_selecter);
	ioctl(0, TIOCSTI, "a");
}

void	handle_stop_sig(int signum)
{
	int i;

	(void)signum;
	i = -1;
	while (++i < 32)
	{
		if (i != SIGCONT)
			signal(i, SIG_DFL);
	}
	if (set_term_mode(g_selecter, 1))
		g_sig = -1;
	tputs(tgetstr("te", NULL), 1, &outc);
	tputs(g_selecter->cmds.rst_curs, 1, &outc);
	g_sig = 1;
	ioctl(0, TIOCSTI, "\x1A");
}

void	signals_manager(void)
{
	int		i;

	i = 0;
	while (++i <= 31)
	{
		if (i <= 15 || (i >= 24 && i <= 27) || i == 30 || i == 31)
			signal(i, handle_term_sig);
	}
	signal(SIGTSTP, handle_stop_sig);
	signal(SIGCONT, handle_afterstop_sig);
	signal(SIGWINCH, handle_winch_sig);
}
