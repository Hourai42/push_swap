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

	if ((*a)->top == NULL)
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
		if (ft_strlen(split_nbrs[n]) > 11 ||
		(nbr = pushswap_atoi(split_nbrs[n])) > 2147483647 ||
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

void	check_s(char c, int *in)
{
	if (c == 'a')
		*in = SA;
	else if (c == 'b')
		*in = SB;
	else if (c == 's')
		*in = SS;
}

void	check_p(char c, int *in)
{
	if (c == 'a')
		*in = PA;
	else if (c == 'b')
		*in = PB;
}

void	check_r(char c, int *in)
{
	if (c == 'a')
		*in = RA;
	else if (c == 'b')
		*in = RB;
	else if (c == 'r')
		*in = RR;
}

void	check_rr(char c, int *in)
{
	if (c == 'a')
		*in = RRA;
	else if (c == 'b')
		*in = RRB;
	else if (c == 'r')
		*in = RRR;
}

int	check_instruction(char *buffer, char *extra)
{
	int in;

	in = 11;
	if (buffer[2] == '\n')
	{
		if (buffer[0] == 's')
			check_s(buffer[1], &in);
		else if (buffer[0] == 'p')
			check_p(buffer[1], &in);
		else if (buffer[0] == 'r')
			check_r(buffer[1], &in);
	}
	else if (extra[0] == '\n')
	{
		if (buffer[0] == 'r' && buffer[1] == 'r')
			check_rr(buffer[2], &in);
	}
	return (in);
}

void	add_instruction(t_rstack *instruct, int instruction)
{
	
}

/*
** I don't need to utilize a double pointer here since
** I can just use "top" to continue adding nodes.
*/

int	read_instructions(t_rstack *instruct)
{
	char buffer[3];
	char extra[1];
	int instruct_nbr;

	while (42)
	{
		ft_bzero(buffer, 3);
		extra[0] = 0;
		read(1, buffer, 3);
		if (buffer[0] == '\n')
			break;
		if (buffer[2] != '\n')
			read(1, extra, 1);
		if ((instruct_nbr = check_instruction(buffer, extra)) == 11)
			return (1);
		add_instruction(instruct, instruct_nbr);
	}
	return (0);
}

/*
** Here, I only send "instruct" because I'm building from the bottom up
** and I wish to keep my final pointer at the bottom once I'm done.
*/

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

/*
** Notice how I send the address of a, since I'm building the stack from
** the top down and I wish to have a pointer to the bottom once I'm done.
*/

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
