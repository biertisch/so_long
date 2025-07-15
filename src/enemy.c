/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:45:28 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/12 22:45:28 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	can_move(t_data *data, int new_row, int new_col)
{
	if (new_row > 0 && new_row < data->map_height
		&& new_col > 0 && new_col < data->map_width
		&& data->map[new_row][new_col] != '1')
		return (1);
	return (0);
}

static int	move_horizontally(t_data *data, t_ent_anim *enemy)
{
	int	offset;
	int	new_col;

	if (enemy->current_dir == 2)
		offset = -1;
	else
		offset = 1;
	new_col = enemy->col + offset;
	if (!can_move(data, enemy->row, new_col))
	{
		offset *= -1;
		new_col = enemy->col + offset;
	}
	enemy->col = new_col;
	if (offset == -1)
		return (2);
	else
		return (3);
}

static int	move_vertically(t_data *data, t_ent_anim *enemy)
{
	int	offset;
	int	new_row;

	if (enemy->current_dir == 0)
		offset = -1;
	else
		offset = 1;
	new_row = enemy->row + offset;
	if (!can_move(data, new_row, enemy->col))
	{
		offset *= -1;
		new_row = enemy->row + offset;
	}
	enemy->row = new_row;
	if (offset == -1)
		return (0);
	else
		return (1);
}

int	move_enemy(t_data *data, t_ent_anim *enemy)
{
	int	new_dir;

	if (enemy->current_dir > 1)
	{
		if (can_move(data, enemy->row, enemy->col - 1)
			|| can_move(data, enemy->row, enemy->col + 1))
			new_dir = move_horizontally(data, enemy);
		else
			new_dir = move_vertically(data, enemy);
	}
	else
	{
		if (can_move(data, enemy->row - 1, enemy->col)
			|| can_move(data, enemy->row + 1, enemy->col))
			new_dir = move_vertically(data, enemy);
		else
			new_dir = move_horizontally(data, enemy);
	}
	return (new_dir);
}
