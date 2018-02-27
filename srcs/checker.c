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

/*
** Change it to read 1 byte at a time.
*/

int	read_instructions(t_queue *instruct)
{
	char buffer[3];
	char extra[1];
	int instruct_nbr;

	while (42)
	{
		ft_bzero(buffer, 3);
		extra[0] = 0;
		read(STDIN_FILENO, &buffer[0], 1);
		if (buffer[0] == '\n' || buffer[0] == 0)
			break;
		read(STDIN_FILENO, &buffer[1], 1);
		if (buffer[1] == '\n' || buffer[1] == 0)
			return (1);
		read(STDIN_FILENO, &buffer[2], 1);
		if (buffer[2] != '\n' && buffer[2] != 0)
			read(STDIN_FILENO, extra, 1);
		if ((instruct_nbr = check_instruction(buffer, extra)) == 11)
			return (1);
		add_instruction(&instruct, instruct_nbr);
	}
	return (0);
}

/*
** A stack B that can never be truly empty, eh? 
** Setting number to empty and b->top to NULL will be the condition.
*/

void	run_instructions(t_queue *instruct, t_control *a, t_control *b)
{
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
