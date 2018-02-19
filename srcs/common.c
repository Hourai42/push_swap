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

void    op_sa(t_control *a_con)
{
    int tmp;

    if (a_con->top != NULL && a_con->not_top != NULL)
    {
        tmp = a_con->top->nbr;
        a_con->top->nbr = a_con->not_top->nbr;
        a_con->not_top->nbr = tmp; 
    }
}

void    op_ss(t_control *a_con, t_control *b_con)
{
    op_sa(a_con);
    op_sa(b_con);
}

/*
** Couldn't A/B get mixed up like this?
** Eeeh..... shit. Who cares? They're all arbitrary sections 
** of memory somewhere in the PC anyway.
*/

void    op_pb(t_control *a_con, t_control *b_con)
{
    if (a_con->top != NULL)
    {
        if (b_con->top == NULL && b_con->bottom != NULL)
        {
            b_con->top = b_con->bottom;
            b_con->bottom->nbr = a_con->top->nbr;
            free(a_con->top);
            a_con->top = a_con->not_top;
            if (a_con->not_top != NULL)
            {
                a_con->top->uppity = NULL;
                a_con->not_top = a_con->not_top->down;
            }
            if (a_con->top == NULL)
                a_con->bottom = NULL;
        }
        else
        {
            b_con->top = a_con->top;
            b_con->top->uppity = NULL;
            b_con->top->down = b_con->not_top;
            a_con->top = a_con->not_top;
            if (a_con->not_top != NULL)
            {
                a_con->not_top = a_con->not_top->down;
                a_con->top->uppity = NULL;
            }
            if (a_con->top == NULL)
                a_con->bottom = NULL;
            
        }
    }
}