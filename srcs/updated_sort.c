/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 01:39:01 by ttran             #+#    #+#             */
/*   Updated: 2018/02/26 01:39:13 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Heuristic is equal to pos + number of iterations. Lower is better!
*/
/*
void    up_movement(t_control *a, t_control *b)
{
    t_stack *ptr;

    ptr = a->top;
    if (ptr != NULL)
        h->heuristic = ptr->pos;
    while (ptr != NULL)
    {
        h->heuristictmp = ptr->pos + h->counter;
        if (h->heuristic > h->heuristictmp)
        {
            h->heuristic = h->heuristictmp;
            h->path = h->counter;
        }
        ptr = ptr->down;
        h->counter++;
    }
}

void	set_h(t_h **h)
{
	*h = malloc(sizeof(t_h));
	(*h)->heuristic = 0;
    (*h)->heuristictmp = 0;
    (*h)->counter = 0;
    (*h)->path;
}

void    reset_h(t_h *h)
{
    h->heuristic = 0;
    h->heuristictmp = 0;
    h->counter = 0;
    h->path;
}
*/
/*
** Hm. You can stop it at any number you like, so you can see how it fares up to a certain
** point. Ie. stop while num > 2, num > 25, num > 50, so you can see how good it is
** at certain points. Get a simple working version then add heuristics and 
** double movements after.
*/
/*
void    updated_sort(t_control *a, t_control *b, int num)
{
    t_h *h;

    set_h(&h);
    set_pos(a, num);
    while (a->top != NULL)
    {
        up_movement(a, b);
        up_setup(a, b);
        up_placement(a, b);
        up_cleanup(a, b);
        reset_h(h);
    }
    fuck_it_all(a, b);
    check_stack(a);
}*/