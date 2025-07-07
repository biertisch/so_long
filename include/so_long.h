/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:02:09 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/05 15:02:09 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include <fcntl.h>

typedef struct	s_found
{
	int	exit;
	int	collectibles;
}	t_found;

typedef struct	s_point
{
	int	row;
	int	column;
}	t_point;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	t_point	win_size;
	char	**map;
	t_point	map_size;
	int		tile_size;
	t_point	player_pos;
	int		collectibles;
	t_found	found;
	int		move;
	void	*img_floor;
	void	*img_wall;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;
}			t_data;


void	error_exit(t_data *data, char *error_msg);
void	parse_map(t_data *data, char *file);
void	validate_map(t_data *data);
int		is_reachable(t_data *data);
void	init_map_data(t_data *data);
void	free_arr(char **arr);

#endif