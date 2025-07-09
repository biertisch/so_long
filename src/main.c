/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:02:15 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/05 15:02:15 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
		error_exit(&data, "Usage: ./so_long <map>\n");
	parse_map(&data, argv[1]);
	validate_map(&data);
	init_display_data(&data);
	render_map(&data);
	mlx_hook(data.win, 2, 1L << 0, key_handler, &data);
	mlx_hook(data.win, 17, 0, close_game, &data);
	mlx_hook(data.win, 22, 1L << 17, resize_handler, &data);
	mlx_loop(data.mlx);
}
