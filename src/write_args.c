/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:53 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/01 11:30:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	case_multi_col(t_selecter *selecter)
{
	t_arg	*current;
	int		current_col;
	int		current_row;
	int		i;

	i = 0;
	current_col = 0;
	current_row = 0;
	current = selecter->first_arg;
	while (!i || current != selecter->first_arg)
	{
		tputs(tgoto((const char*)selecter->cmds.mv_curs,\
					current_col * (selecter->max_len + 3),\
					current_row), 1, &outc);
		write_arg(selecter, current);
		current_row++;
		if (current_row == selecter->termsize.ws_row - 1)
		{
			current_col++;
			current_row = 0;
		}
		current = current->next;
		i++;
	}
	selecter->freeze = 0;
}

void	case_single_col(t_selecter *selecter)
{
	t_arg	*current;
	int		current_row;
	int		i;

	i = 0;
	current_row = 0;
	current = selecter->first_arg;
	while (!i || current != selecter->first_arg)
	{
		tputs(tgoto((const char*)selecter->cmds.mv_curs, 0, current_row),\
				1, &outc);
		write_arg(selecter, current);
		current_row++;
		current = current->next;
		i++;
	}
	selecter->freeze = 0;
}

void	del_lines(t_selecter *selecter)
{
	int		i;

	i = -1;
	while (++i < selecter->termsize.ws_row)
		tputs(tgetstr("dl", NULL), 1, &outc);
}

void	write_args(t_selecter *selecter)
{
	int		wds_per_line;
	int		nb_lines;

	del_lines(selecter);
	wds_per_line = selecter->termsize.ws_col / (selecter->max_len + 3);
	nb_lines = wds_per_line ? selecter->nb_args / wds_per_line : 0;
	if (wds_per_line && selecter->nb_args % wds_per_line != 0)
		nb_lines++;
	if (selecter->termsize.ws_col < selecter->max_len + 3)
	{
		write(0, "Please enlarge the term window size\n", 36);
		selecter->freeze = 1;
	}
	else if (selecter->termsize.ws_row >= selecter->nb_args + 1)
		case_single_col(selecter);
	else if (nb_lines <= selecter->termsize.ws_row - 1)
		case_multi_col(selecter);
	else
	{
		write(0, "Please enlarge the term window size\n", 36);
		selecter->freeze = 1;
	}
}

void	write_final_args(t_selecter *selecter)
{
	t_arg	*current;
	int		i;

	i = 0;
	if (selecter->first_arg->selected)
	{
		i++;
		write(1, selecter->first_arg->str, selecter->first_arg->len);
	}
	current = selecter->first_arg->next;
	while (current != selecter->first_arg)
	{
		if (current->selected)
		{
			if (i)
				write(1, " ", 1);
			i++;
			write(1, current->str, current->len);
		}
		current = current->next;
	}
	if (i)
		write(1, "\n", 1);
}
