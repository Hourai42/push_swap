/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:28:45 by ttran             #+#    #+#             */
/*   Updated: 2018/02/17 22:28:47 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

/*
** In future projects where speed is important, only include personal libraries
** where you need them instead of inside the header file.
*/

# include <libft.h>
# include "ft_printf.h"

typedef struct s_stack
{
    struct s_stack *top;
    struct s_stack *not_top;
    struct s_stack *uppity;
    int nbr;
}               t_stack;

/*
** Functions for common
*/

void    op_sa(t_stack *a, t_stack *b);
void    op_sb(t_stack *a, t_stack *b);
void    op_ss(t_stack *a, t_stack *b);
void    op_pa(t_stack *a, t_stack *b);
void    op_pb(t_stack *a, t_stack *b);
void    op_ra(t_stack *a, t_stack *b);
void    op_rb(t_stack *a, t_stack *b);
void    op_rr(t_stack *a, t_stack *b);
void    op_rra(t_stack *a, t_stack *b);
void    op_rrb(t_stack *a, t_stack *b);
void    op_rrr(t_stack *a, t_stack *b);

#endif
