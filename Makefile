NAME		=	so_long

SRC_FILES	=	draw game_loop end enemy flood_fill free init_ent init_env init_ui\
				main map_data mlx_data parser player render time validate

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	include/
LIBFT_DIR	=	libft/
MLX_DIR		=	mlx/

LIBFT_URL	=	https://github.com/biertisch/libft.git

LIBFT		=	$(LIBFT_DIR)libft.a
MLX			=	$(MLX_DIR)libmlx.a

SRC         =	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ         =	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INC_DIR) -I$(LIBFT_DIR)$(INC_DIR) -I$(MLX_DIR)
LFLAGS		=	-L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
RM			=	rm -rf

all: $(NAME)
	@cat banner.txt

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

$(LIBFT): $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) extra

$(LIBFT_DIR):
	git clone $(LIBFT_URL) $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re