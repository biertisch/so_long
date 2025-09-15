/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:31:54 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/15 22:31:50 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	display_collected(t_data *data)
{
	int	x;

	mlx_put_image_to_window(data->mlx, data->win.ptr, data->collect_counter.img,
		150, 0);
	x = 182;
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->background.img,
		x, 0);
	x = render_counter(data, data->collected, x);
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->chars[10].img,
		x, 0);
	x += 16;
	x = render_counter(data, data->collectibles, x);
}

static void	display_moves(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->move_counter.img,
		10, 0);
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->background.img,
		82, 0);
	render_counter(data, data->moves, 82);
}

static void	animate_enemy(t_data *data)
{
	int		new_dir;
	int		i;
	long	now;

	i = 0;
	while (i < data->enemy_count)
	{
		now = get_time_ms();
		if (now - data->enemy[i].last_move >= data->enemy[i].move_interval_ms)
		{
			new_dir = move_enemy(data, &data->enemy[i]);
			update_ent_frame(&data->enemy[i], new_dir);
			data->enemy[i].last_move = now;
		}
		if (data->enemy[i].row == data->player.row
			&& data->enemy[i].col == data->player.col && !data->game_over)
		{
			data->game_over = DEFEAT;
			ft_printf("Total moves: %d\n", data->moves);
			ft_printf("You lost the game. So long!\n");
		}
		i++;
	}
}

static void	animate_object(t_env_anim *obj)
{
	long	now;

	now = get_time_ms();
	if (now - obj->last_move >= obj->move_interval_ms)
	{
		obj->current_frame = (obj->current_frame + 1) % obj->frame_count;
		obj->last_move = now;
	}
}

int	game_loop(t_data *data)
{
	if (data->game_over)
	{
		handle_game_end(data);
		return (0);
	}
	animate_object(&data->wall);
	animate_enemy(data);
	render_map(data, data->map.map);
	display_moves(data);
	display_collected(data);
	return (0);
}
