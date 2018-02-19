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

void    op_pa(t_control *a_con, t_control *b_con)
{
    
}