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

# define TILE_SIZE		64
# define DIRECTIONS		4
# define WALL_FRAMES	22
# define PLAYER_FRAMES	9
# define ENEMY_FRAMES	6
# define CHAR_FRAMES	11
# define MAGIC_COLOR	0xFF00FF
# define KEY_ESC		65307
# define KEY_Q			113
# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_UP			65362
# define KEY_DOWN		65364
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

typedef enum e_dir
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
}	t_dir;

typedef enum e_game_outcome
{
	RUNNING,
	VICTORY,
	DEFEAT
}	t_game_outcome;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}			t_map;

typedef struct s_win
{
	char	*ptr;
	int		width;
	int		height;
}			t_win;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_image;

typedef struct s_env_anim
{
	t_image	*frames;
	int		frame_count;
	int		current_frame;
	int		frame_tick;
	int		tick_rate;
}			t_env_anim;

typedef struct s_ent
{
	t_image	**frames;
	t_image	**collect_layer;
	t_image	**exit_layer;
	int		row;
	int		col;
	int		frame_count;
	int		current_frame;
	int		current_dir;
	int		frame_tick;
	int		tick_rate;
}			t_ent;

typedef struct s_data
{
	t_map		map;
	void		*mlx;
	t_win		win;
	int			collectibles;
	int			collected;
	int			unlock_exit;
	int			moves;
	int			enemy_count;
	int			game_over;
	int			end_tick;
	t_image		background;
	t_image		move_counter;
	t_image		collect_counter;
	t_image		closed_exit_msg;
	t_image		victory_msg;
	t_image		defeat_msg;
	t_image		*chars;
	t_env_anim	wall;
	t_image		exit;
	t_image		floor;
	t_image		collect;
	t_ent		player;
	t_ent		*enemy;
}				t_data;

//draw.c
void	draw_with_transparency(t_image *dest, t_image *src);

//end.c
void	handle_game_end(t_data *data);
void	error_exit(t_data *data, char *error_msg);
int		close_game(void *param);

//enemy.c
int		move_enemy(t_data *data, t_ent *enemy);

//flood_fill.c
void	flood_fill(t_data *data, char **map, int row, int col);
char	**duplicate_map(char **map, int rows);

//free.c
void	free_data(t_data *data);
void	free_arr(char **arr);

//game_loop.c
int		game_loop(t_data *data);

//init_ent.c
void	init_ent(t_data *data);

//init_env.c
void	init_env(t_data *data);

//init_ui.c
void	init_ui(t_data *data);

//map_data.c
void	init_map_data(t_data *data);

//mlx_data.c
void	init_mlx_data(t_data *data);
void	load_image(t_data *data, t_image *dest, t_image *layer, char *filename);

//parser.c
void	parse_map(t_data *data, char *file);

//player.c
int		key_handler(int keycode, void *param);
void	update_ent_frame(t_ent *ent, int new_dir);

//render.c
void	render_map(t_data *data, char **map);
int		render_counter(t_data *data, int n, int x);

//validate.c
void	validate_map(t_data *data);

#endif