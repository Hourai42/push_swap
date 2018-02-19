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
	(*a)->down = NULL;
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
		new->down = NULL;
		(*a)->down = new;
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
		nbr < -2147483648)
		{
			//free split_nbrs string with a function
			return (0);
		}
		slideb_stack(a, (int)nbr);
		if (check_dup(*a) == 1)
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

void	init_rstack(t_rstack **instruct)
{
	(*instruct) = malloc(sizeof(t_rstack));
	(*instruct)->bottom = NULL;
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

/*
** Well... now you see the folly in having a pointer to "top".
** Top constantly changes, so you'll have to update it all the
** way down. Instead of having "bottom" be the pointer.
*/

void	add_instruction(t_rstack **instruct, int instruction)
{
	t_rstack *new;

	if ((*instruct)->bottom == NULL)
	{
		(*instruct)->bottom = *instruct;
		(*instruct)->instruction = instruction;
	}
	else
	{
		new = malloc(sizeof(t_rstack));
		new->instruction = instruction;
		new->uppity = NULL;
		(*instruct)->uppity = new;
		new->bottom = (*instruct)->bottom;
		*instruct = new;
	}
}

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
		if (buffer[1] == '\n')
			return (1);
		if (buffer[2] != '\n')
			read(1, extra, 1);
		if ((instruct_nbr = check_instruction(buffer, extra)) == 11)
			return (1);
		add_instruction(&instruct, instruct_nbr);
	}
	return (0);
}

void	init_control(t_control **control, t_stack *stack)
{
	(*control) = malloc(sizeof(t_control));
	(*control)->top = stack->top;
	(*control)->not_top = stack->not_top;
	(*control)->bottom = stack;
}

/*
** A stack B that can never be truly empty, eh? 
** Setting number to empty and b->top to NULL will be the condition.
*/

void	run_instructions(t_rstack *instruct, t_stack *a, t_stack *b)
{
	t_control *a_control;
	t_control *b_control;

	init_control(&a_control, a);
	init_control(&b_control, b);
	//Make a function to check stacks
	while (instruct != NULL)
	{
		instruct->instruction == SA ? op_sa(a_control) : 0;
		instruct->instruction == SB ? op_sa(b_control) : 0;
		instruct->instruction == SS ? op_ss(a_control, b_control) : 0;
		instruct->instruction == PA ? op_pb(b_control, a_control) : 0;
		instruct->instruction == PB ? op_pb(a_control, b_control) : 0;
		//instruct->instruction == RA ? op_ra(a_control) : 0;
		//instruct->instruction == RB ? op_ra(b_control) : 0;
		//instruct->instruction == RR ? op_rr(a_control, b_control) : 0;
		//instruct->instruction == RRA ? op_rra(a_control) : 0;
		//instruct->instruction == RRB ? op_rra(b_control) : 0;
		//instruct->instruction == RRR ? op_rrr(a_control, b_control) : 0;
		instruct = instruct->uppity;
	}
	//Make a function to check stacks and see if it's working properly
	//free controls
}

/*
** Here, I only send "instruct" because I'm building from the bottom up
** and I wish to keep my final pointer at the bottom once I'm done.
** Nvm, I can just "store" the bottom and push my way up.
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
	run_instructions(instruct, a, b);
	// Then the fun part of making all 11 instructions! 
	// Then another function to see if sorted, for OK or KO. A sorted and B empty
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
	//Check if it's not == NULL already before freeing, because B can become
	//a part of A. 
	return (0);
}
