/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:58:53 by ttran             #+#    #+#             */
/*   Updated: 2018/02/17 18:58:54 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*
** In future projects where speed is important, only include personal libraries
** where you need them instead of inside the header file.
*/

# include <libft.h>
# include "ft_printf.h"

typedef struct s_stack
{
    struct s_stack *down;
    int nbr;
    int pos;
}               t_stack;

typedef struct s_control
{
    struct s_stack *top;
    struct s_stack *bottom;
}               t_control;

/*
** Functions for push_swap
*/

int main(int argc, char **argv);
void	init_control(t_control **control);
int	parse_nbrs(char *nbrs, t_control *a);
intmax_t		pushswap_atoi(char *str);
void	slidebot_stack(t_control *a, int num);
int	check_dup(t_control *a);
int		check_sorted(t_control *a, t_control *b);
void	check_stack(t_control *a);
void    op_sa(t_control *con);
void    op_tsa(t_control *con);
void    op_ss(t_control *a_con, t_control *b_con);
void    op_pa(t_control *a_con, t_control *b_con);
void    op_ra(t_control *con);
void    op_rr(t_control *a_con, t_control *b_con);
void    op_rra(t_control *con);
void    op_rrr(t_control *a_con, t_control *b_con);


void    large_sort(t_control *a, t_control *b, int num);

void	small_sort(t_control *a, t_control *b, int num);
int	num_of_nbrs(t_control *a);
void	fuck_it_all(t_control *a, t_control *b);

#endif
