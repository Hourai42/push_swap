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
** Not top is one away from the top.
** Hm. Use is very important in stack implementation.
** Ie. whether you need a "top" or a "bottom" ptr, or even neither.
*/

typedef struct s_stack
{
    struct s_stack *top;
    struct s_stack *not_top;
    struct s_stack *uppity;
    struct s_stack *down;
    int nbr;
}               t_stack;

/*
** A regular stack for holding instructions.
*/

typedef struct s_rstack
{
    struct s_rstack *uppity;
    struct s_rstack *bottom;
    int instruction;
}               t_rstack;

/*
** Functions for checker
*/

int main(int argc, char **argv);

#endif
