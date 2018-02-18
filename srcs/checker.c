/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:59:03 by ttran             #+#    #+#             */
/*   Updated: 2018/02/17 18:59:07 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		pushswap_atoi(char *str)
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

void	init_stack(t_stack **a)
{
	*a = malloc(sizeof(t_stack));
	(*a)->top = NULL;
	(*a)->not_top = NULL;
	(*a)->uppity = NULL;
}

int	check_dup(t_stack *a)
{
	int nbr;

	if (a->uppity != NULL)
	{
		nbr = a->nbr;
		a = a->uppity;
		while (a != NULL)
		{
			if (nbr == a->nbr)
				return (1);
			a = a->uppity;
		}
	}
	return (0);
}

/*
** Slide bottom stack!
*/

void	slideb_stack(t_stack **a, int num)
{
	t_stack *new;

	if (*a)->top == NULL
	{
		(*a)->top = *a;
		(*a)->nbr = num;
	}
	else
	{
		new = malloc(sizeof(t_stack));
		if ((*a)->not_top == NULL)
			(*a)->not_top = new;
		new->top = (*a)->top;
		new->not_top = (*a)->not_top;
		new->uppity = *a;
		new->nbr = num;
		*a = new;
	}
}

int	parse_nbrs(char *nbrs, t_stack **a)
{
	char **split_nbrs;
	intmax_t nbr;
	int n;

	n = 0;
	split_nbrs = ft_strsplit(nbrs, ' ');
	while (split_nbrs[n])
	{
		if (ft_strlen(split_nbrs[n]) > 11) ||
		(nbr = pushswap_atoi(split_nbr[n])) > 2147483647 ||
		nbr < -2147483648 || check_dup(*a) == 1) 
		{
			//free split_nbrs string with a function
			return (0);
		}
		slideb_stack(a, (int)nbr);
		n++;
	}
	//free split_nbrs
	return (1);
}

void	init_rstack(t_rstack **instruct)
{
	(*instruct) = malloc(sizeof(t_rstack));
	(*instruct)->top = NULL;
	(*instruct)->uppity = NULL;
}

int	read_instructions(t_rstack *instruct)
{
	char *buffer;

	//Can't use GNL, just read and stop when '\n'.
	// Have a fully null terminated buff size of 5, 
	//b zero it then read until the end. All are size 2 or 3.
	// Return 1 if wrong instruction or dumb format. 
	return (0);
}

int	check_a(t_stack *a, t_stack *b)
{
	t_rstack *instruct;

	init_rstack(&instruct);
	if (read_instructions(instruct) == 1)
	{
		//free instruct all the way thru
		return (0);
	}
	// function to go thru instruct and run them all
	// Then the fun part of making all 11 instructions! 
	// Then another function to see if sorted, for OK or KO.
	//free instruct
	return (1);
}

int main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;

	init_stack(&a);
	init_stack(&b);
	if (argc == 2)
	{
		if (parse_nbrs(argv[1], &a) == 0 || check_a(a, b) == 0)			
		{
			ft_putstr(RED);
			write(2, "Error\n", 6);
		}
	}
	//Free A and B, from bottom all the way to top
	return (0);
}
