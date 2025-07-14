/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:31:54 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/11 12:31:54 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	display_moves(t_data *data)
{
	int	digits[10];
	int	tmp;
	int	len;
	int	x;

	x = 82;
	mlx_put_image_to_window(data->mlx, data->win, data->text_moves.img, 10, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->text_background.img, x, 0);
	tmp = data->moves;
	len = 0;
	if (tmp == 0)
		digits[len++] = 0;
	while (tmp > 0)
	{
		digits[len++] = tmp % 10;
		tmp /= 10;
	}
	while (--len >= 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->chars[digits[len]].img, x, 0);
		x += 16;
	}
}

static void	animate_enemy(t_data *data)
{
	int	new_dir;
	
	data->enemy.frame_tick++;
	if (data->enemy.frame_tick >= data->enemy.tick_rate)
	{
		new_dir = move_enemy(data);
		update_frame(&data->enemy, new_dir);
		data->enemy.frame_tick = 0;
	}
	if (data->enemy.row == data->player.row &&
		data->enemy.col == data->player.col && !data->game_over)
		defeat(data);
}

static void	animate_object(t_env_anim *obj)
{
	obj->frame_tick++;
	if (obj->frame_tick >= obj->tick_rate)
	{
		obj->current_frame = (obj->current_frame + 1) % obj->frame_count;
		obj->frame_tick = 0;
	}
}

int	game_loop(t_data *data)
{
	if (data->game_over)
	{
		close_game((void *)data);
		return (0);
	}
	animate_object(&data->wall);
	animate_enemy(data);
	render_map(data);
	display_moves(data);
	return (0);
}
