/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:46:50 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/01 11:30:04 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			outc(int c)
{
	write(0, &c, 1);
	return (0);
}

static void	chose_color2(t_selecter *selecter, int arg_type)
{
	if (arg_type == 6 || arg_type == 7)
	{
		tputs(tparm(selecter->cmds.color, COLOR_BLUE), 1, &outc);
		if (arg_type == 6)
			tputs(tparm(selecter->cmds.bg_color, COLOR_CYAN), 1, &outc);
		if (arg_type == 7)
			tputs(tparm(selecter->cmds.bg_color, COLOR_YELLOW), 1, &outc);
	}
	if (arg_type >= 8 && arg_type <= 11)
	{
		tputs(tparm(selecter->cmds.color, COLOR_BLACK), 1, &outc);
		if (arg_type == 8)
			tputs(tparm(selecter->cmds.bg_color, COLOR_RED), 1, &outc);
		if (arg_type == 9)
			tputs(tparm(selecter->cmds.bg_color, COLOR_CYAN), 1, &outc);
		if (arg_type == 10)
			tputs(tparm(selecter->cmds.bg_color, COLOR_GREEN), 1, &outc);
		if (arg_type == 11)
			tputs(tparm(selecter->cmds.bg_color, COLOR_YELLOW), 1, &outc);
	}
}

static void	chose_color(t_selecter *selecter, int arg_type)
{
	if (arg_type == 1)
	{
		tputs(selecter->cmds.bold, 1, &outc);
		tputs(tparm(selecter->cmds.color, COLOR_CYAN), 1, &outc);
	}
	if (arg_type == 2)
		tputs(tparm(selecter->cmds.color, COLOR_MAGENTA), 1, &outc);
	if (arg_type == 3)
		tputs(tparm(selecter->cmds.color, COLOR_GREEN), 1, &outc);
	if (arg_type == 4)
		tputs(tparm(selecter->cmds.color, COLOR_YELLOW), 1, &outc);
	if (arg_type == 5)
		tputs(tparm(selecter->cmds.color, COLOR_RED), 1, &outc);
	chose_color2(selecter, arg_type);
}

void		write_arg(t_selecter *selecter, t_arg *arg)
{
	static char	arrow[3] = {0xe2, 0x9e, 0x9c};

	if (selecter->current_arg == arg)
	{
		tputs(tparm(selecter->cmds.color, COLOR_GREEN), 1, &outc);
		tputs(selecter->cmds.bold, 1, &outc);
		write(0, arrow, 3);
		tputs(selecter->cmds.reset, 1, &outc);
		write(0, " ", 1);
		tputs(selecter->cmds.underline, 1, &outc);
	}
	else
		write(0, "  ", 2);
	if (!arg->selected)
		chose_color(selecter, arg->type);
	if (arg->selected)
		tputs(selecter->cmds.reverse, 1, &outc);
	write(0, arg->str, arg->len);
	tputs(selecter->cmds.reset, 1, &outc);
}
