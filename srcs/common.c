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

/*
** A version that swaps the positions as well.
*/

void    op_tsa(t_control *con)
{
	int tmp;

	if (con->top != NULL && con->top->down != NULL)
	{
		tmp = con->top->nbr;
		con->top->nbr = con->top->down->nbr;
		con->top->down->nbr = tmp;
		tmp = con->top->pos;
		con->top->pos = con->top->down->pos;
		con->top->down->pos = tmp;
	}
}

void    op_ss(t_control *a_con, t_control *b_con)
{
	op_sa(a_con);
	op_sa(b_con);
}

void	op_tss(t_control *a_con, t_control *b_con)
{
	op_tsa(a_con);
	op_tsa(b_con);
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

void	init_control(t_control **control)
{
	(*control) = malloc(sizeof(t_control));
	(*control)->top = NULL;
	(*control)->bottom = NULL;
}

int	parse_nbrs(char *nbrs, t_control *a)
{
	char **split_nbrs;
	intmax_t nbr;
	int n;

	n = 0;
	split_nbrs = ft_strsplit(nbrs, ' ');
	while (split_nbrs[n])
	{
		if (ft_strlen(split_nbrs[n]) > 11 ||
		(nbr = pushswap_atoi(split_nbrs[n])) > 2147483647 ||
		nbr < -2147483648)
		{
			//free split_nbrs string with a function
			return (0);
		}
		slidebot_stack(a, (int)nbr);
		if (check_dup(a) == 1)
		{
			//free split_nbrs
			return (0);
		}
		n++;
	}
	//free split_nbrs
	if (n < 1)
		return (0);
	return (1);
}

intmax_t		pushswap_atoi(char *str)
{
	int neg;
	intmax_t nbr;

	neg = 1;
	nbr = 0;
	if (!((*str >= '0' && *str <= '9') || *str == '-'))
		return (4242424242424242);
	if (*str == '-')
	{
		neg *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			nbr = nbr * 10 + (*str - '0');
		else
			return (4242424242424242);
		str++;
	}
	return (nbr * neg);
}

/*
** Slide bottom stack!
*/

void	slidebot_stack(t_control *a, int num)
{
	t_stack *new;

	if (a->top == NULL)
	{
		new = malloc(sizeof(t_stack));
		a->top = new;
		a->bottom = new;
		new->nbr = num;
		new->down = NULL; 
	}
	else
	{
		new = malloc(sizeof(t_stack));
		a->bottom->down = new;
		a->bottom = new;
		new->down = NULL;
		new->nbr = num;
	}
}

/*
** Stops at the last one without checking.
*/

int	check_dup(t_control *a)
{
	int nbr;
	t_stack *ptr;

	if (a->top->down != NULL)
	{
		nbr = a->bottom->nbr;
		ptr = a->top;
		while (ptr->down != NULL)
		{
			if (nbr == ptr->nbr)
				return (1);
			ptr = ptr->down;
		}
	}
	return (0);
}

int		check_sorted(t_control *a, t_control *b)
{
	t_stack *ptr;

	ptr = a->top;
	if (b->bottom != NULL)
		return (0);
	while (ptr->down != NULL)
	{
		if (ptr->nbr > ptr->down->nbr)
			return (0);
		ptr = ptr->down;
	}
	return (1);
}

void	check_stack(t_control *a)
{
	t_stack *ptr;

	ptr = a->top;
	ft_putstr("stack:");
	while (ptr != NULL)
	{
		ft_putnbr(ptr->nbr);
		write(1, " ", 1);
		ptr = ptr->down;
	}
	ptr = a->top;
	write(1, "\n", 1);
	ft_putstr("pos:");
	while (ptr != NULL)
	{
		ft_putnbr(ptr->pos);
		write(1, " ", 1);
		ptr = ptr->down;
	}
	write(1, "\n", 1);
}