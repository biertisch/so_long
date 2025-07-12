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
	animate_object(&data->exit);
	animate_object(&data->wall);
	render_map(data);
	return (0);
}
