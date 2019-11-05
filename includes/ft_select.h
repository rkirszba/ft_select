/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:22:26 by rkirszba          #+#    #+#             */
/*   Updated: 2019/06/26 21:11:15 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termcap.h>
# include <stdlib.h>
# include <curses.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft.h"

typedef struct		s_arg
{
	char			*str;
	int				selected;
	int				len;
	int				type;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_cmds
{
	char	*clear;
	char	*underline;
	char	*reverse;
	char	*mv_curs;
	char	*hide_curs;
	char	*rst_curs;
	char	*reset;
	char	*bold;
	char	*color;
	char	*bg_color;
}					t_cmds;

typedef struct		s_selecter
{
	struct termios	term_conf;
	struct termios	term_conf_backup;
	char			buff[6];
	t_arg			*first_arg;
	t_arg			*current_arg;
	int				nb_args;
	struct winsize	termsize;
	int				max_len;
	t_cmds			cmds;
	int				freeze;
}					t_selecter;

typedef struct		s_cmd_fun
{
	int		(*check)(char*);
	int		(*manager)(t_selecter*);
}					t_cmd_fun;

extern int			g_sig;
extern t_selecter	*g_selecter;

/*
** initializing functions
*/

t_selecter			*init_selecter(int nb_args);
void				init_cmd_tab(t_cmd_fun *cmd_tab);

/*
** set term mode
*/

int					set_term_mode(t_selecter *selecter, int i);

/*
** analyze char
*/

int					is_right_arrow(char *buff);
int					is_left_arrow(char *buff);
int					is_space(char *buff);
int					is_return(char *buff);
int					is_escape(char *buff);
int					is_delete(char *buff);
int					is_backspace(char *buff);

/*
** command functions
*/

int					manage_right_arrow(t_selecter *selecter);
int					manage_left_arrow(t_selecter *selecter);
int					manage_space(t_selecter *selecter);
int					manage_return(t_selecter *selecter);
int					manage_escape(t_selecter *selecter);
int					manage_delete(t_selecter *selecter);
int					manage_backspace(t_selecter *selecter);

/*
** write argument
*/

int					outc(int c);
void				del_lines(t_selecter *selecter);
void				write_arg(t_selecter *selecter, t_arg *arg);
void				case_single_col(t_selecter *selecter);
void				case_multi_col(t_selecter *selecter);
void				write_args(t_selecter *selecter);
void				write_final_args(t_selecter *selecter);

/*
** arguments functions
*/

t_arg				*create_argument(char *str);
void				append_argument(t_selecter *selecter, t_arg *arg);
void				give_max_len(t_selecter *selecter);

/*
** signals manager
*/

void				signals_manager(void);
void				handle_winch_sig(int signum);
void				handle_term_sig(int signum);
void				handle_afterstop_sig(int signum);
void				handle_stop_sig(int signum);

/*
** free functions
*/

void				free_manager(t_selecter *selecter);
void				free_arg(t_arg **arg);

/*
** errors
*/

int					print_usage(void);
int					print_sys_error(void);
int					print_cmd_error(void);
int					print_noenv_error(void);
int					print_noaccess_error(void);
int					print_notdefined_error(void);
int					print_noattr_error(void);

#endif
