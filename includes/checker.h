/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 20:02:51 by ttran             #+#    #+#             */
/*   Updated: 2018/02/17 20:02:52 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

/*
** In future projects where speed is important, only include personal libraries
** where you need them instead of inside the header file.
*/

# include <libft.h>
# include "ft_printf.h"

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

/*
** Well, that was absolutely painful. I hoped you learned your lesson.
** Implementations are done in a certain way for a reason.
*/

typedef struct s_stack
{
    struct s_stack *down;
    int nbr;
}               t_stack;

/*
** First from top, second from top, last from top. 
*/

typedef struct s_control
{
    struct s_stack *top;
    struct s_stack *bottom;
}               t_control;

/*
** A queue for holding the instructions. Revamp it all you fuck.
*/

typedef struct s_queue
{
    struct s_queue *back;
    struct s_queue *first;
    int instruction;
}               t_queue;

/*
** Functions for checker
*/

int main(int argc, char **argv);
void    op_sa(t_control *con);
void    op_ss(t_control *a_con, t_control *b_con);
void    op_pa(t_control *a_con, t_control *b_con);
void    op_ra(t_control *con);
void    op_rr(t_control *a_con, t_control *b_con);
void    op_rra(t_control *con);
void    op_rrr(t_control *a_con, t_control *b_con);

#endif
