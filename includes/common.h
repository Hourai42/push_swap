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

/*
** Ah, the only thing that matters is the "controlling" stack. 
** Use is vital. 
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
** A controller main stack
** Check if a stack is empty by "a_con->top" since the top constantly updates.
*/

typedef struct s_control
{
    struct s_stack *top;
    struct s_stack *not_top;
    struct s_stack *bottom;
}               t_control;

/*
** Functions for common
** A lot of these are the same, except they affect different stacks.
** Remember that it's all relative and based on links.. and ptrs.
*/

void    op_sa(t_control *a_con);
void    op_ss(t_control *a_con, t_control *b_con);
void    op_pa(t_control *a_con, t_control *b_con);
void    op_ra(t_control *a_con);
void    op_rr(t_control *a_con, t_control *b_con);
void    op_rra(t_control *a_con);
void    op_rrr(t_control *a_con, t_control *b_con);

#endif
