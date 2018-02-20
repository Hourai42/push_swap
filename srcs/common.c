/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 22:18:57 by ttran             #+#    #+#             */
/*   Updated: 2018/02/18 22:18:58 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
** Use before changing. Well, or you could just swap the values inside.
*/

void    op_sa(t_control *con)
{
    int tmp;

    if (con->top != NULL && con->top->down != NULL)
    {
        tmp = con->top->nbr;
        con->top->nbr = con->top->down->nbr;
        con->top->down->nbr = tmp;
    }
}

void    op_ss(t_control *a_con, t_control *b_con)
{
    op_sa(a_con);
    op_sa(b_con);
}

void    op_pa(t_control *a_con, t_control *b_con)
{
    t_stack *ptr;

    if (b_con->bottom != NULL)
    {
        ptr = b_con->top->down;
        b_con->top->down = a_con->top;
        if (a_con->bottom == NULL)
            a_con->bottom = b_con->top;
        a_con->top = b_con->top;
        if (ptr == NULL)
            b_con->bottom = NULL;
        b_con->top = ptr;
    }
}

void    op_ra(t_control *con)
{
    if (con->top != NULL && con->top->down != NULL)
    {
        con->bottom->down = con->top;
        con->bottom = con->top;
        con->top = con->top->down;
        con->bottom->down = NULL;
    }
}

void    op_rr(t_control *a_con, t_control *b_con)
{
    op_ra(a_con);
    op_ra(b_con);
}

void    op_rra(t_control *con)
{
    t_stack *ptr;
    int num;

    if (con->top != NULL && con->top->down != NULL)
    {
        ptr = con->top;
        num = con->bottom->nbr;
        con->bottom->down = con->top;
        con->top = con->bottom;
        while (42)
        {
            if (ptr->down->nbr == num)
                break;
            ptr = ptr->down;
        }
        con->bottom = ptr;
        con->bottom->down = NULL;
    }
}

void    op_rrr(t_control *a_con, t_control *b_con)
{
    op_rra(a_con);
    op_rra(b_con);
}
