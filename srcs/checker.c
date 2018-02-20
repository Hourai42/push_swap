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

void	init_queue(t_queue **instruct)
{
	(*instruct) = malloc(sizeof(t_queue));
	(*instruct)->back = NULL;
	(*instruct)->first = NULL;
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

void	add_instruction(t_queue **instruct, int instruction)
{
	t_queue *new;

	if ((*instruct)->first == NULL)
	{
		(*instruct)->first = *instruct;
		(*instruct)->back = NULL;
		(*instruct)->instruction = instruction;
	}
	else
	{
		new = malloc(sizeof(t_queue));
		new->back = NULL;
		new->instruction = instruction;
		new->first = (*instruct)->first;
		(*instruct)->back = new;
		*instruct = new;
	}
}

int	read_instructions(t_queue *instruct)
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
	write(1, "\n", 1);
}

/*
** A stack B that can never be truly empty, eh? 
** Setting number to empty and b->top to NULL will be the condition.
*/

void	run_instructions(t_queue *instruct, t_control *a, t_control *b)
{
	check_stack(a);
	check_stack(b);
	while (instruct != NULL && instruct->first != NULL)
	{
		instruct->instruction == SA ? op_sa(a) : 0;
		instruct->instruction == SB ? op_sa(b) : 0;
		instruct->instruction == SS ? op_ss(a, b) : 0;
		instruct->instruction == PA ? op_pa(a, b) : 0;
		instruct->instruction == PB ? op_pa(b, a) : 0;
		instruct->instruction == RA ? op_ra(a) : 0;
		instruct->instruction == RB ? op_ra(b) : 0;
		instruct->instruction == RR ? op_rr(a, b) : 0;
		instruct->instruction == RRA ? op_rra(a) : 0;
		instruct->instruction == RRB ? op_rra(b) : 0;
		instruct->instruction == RRR ? op_rrr(a, b) : 0;
		instruct = instruct->back;
	}
	check_stack(a);
	check_stack(b);
}

/*
** Here, I only send "instruct" because I'm building from the bottom up
** and I wish to keep my final pointer at the bottom once I'm done.
** Nvm, I can just "store" the bottom and push my way up.
*/

int	check_a(t_control *a, t_control *b)
{
	t_queue *instruct;

	init_queue(&instruct);
	if (read_instructions(instruct) == 1)
	{
		//free instruct all the way thru
		return (0);
	}
	run_instructions(instruct, a, b);
	if (check_sorted(a, b) == 1)
		ft_printf("%s%s", GREEN, "OK\n");
	else
		ft_printf("%s%s", PURPLE, "KO\n");
	//free instruct
	return (1);
}

void	init_control(t_control **control)
{
	(*control) = malloc(sizeof(t_control));
	(*control)->top = NULL;
	(*control)->bottom = NULL;
}

/*
** Notice how I send the address of a, since I'm building the stack from
** the top down and I wish to have a pointer to the bottom once I'm done.
*/

int main(int argc, char **argv)
{
	t_control *a;
	t_control *b;

	init_control(&a);
	init_control(&b);
	if (argc == 2)
	{
		if (parse_nbrs(argv[1], a) == 0 || check_a(a, b) == 0)			
		{
			ft_putstr(RED);
			write(2, "Error\n", 6);
		}
	}
	//Free A and B, from bottom all the way to top
	return (0);
}
