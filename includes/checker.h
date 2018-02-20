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
** Fuck it, you need to revamp and reorganize ALL of push swap. You're a mess rn.
** Keep the ptr to stack on top, another ptr to bottom held, and a down instruction.
** You'll need an up instruction for purely the top and bottom swap, I guess? 
** Let's go through this step by step.
** You're overthinking this. Just have a stack with a ptr to the very top and a ptr to 
** bottom inside of the stack. Then a way down. This will only have 1 difficult edgecase,
** and that's the last-to-bottom case. Just have control w/ a pointer to that, sheesh. 
*/

/*
** Not top is one away from the top.
** Hm. Use is very important in stack implementation.
** Ie. whether you need a "top" or a "bottom" ptr, or even neither.
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
    struct s_stack *almostbot;
    struct s_stack *bottom;
}               t_control;

/*
** A queue for holding the instructions. Revamp it all you fuck.
*/

typedef struct s_queue
{
    struct s_queue *
    struct s_queue *
    int instruction;
}               t_queue;

/*
** Functions for checker
*/

int main(int argc, char **argv);
void    op_sa(t_control *a_con);
void    op_ss(t_control *a_con, t_control *b_con);
void    op_pb(t_control *a_con, t_control *b_con);

#endif
