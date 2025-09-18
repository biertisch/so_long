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

SRC         =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         =	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -I$(INC_DIR) -I$(LIBFT_DIR)$(INC_DIR) -I$(MLX_DIR)
LFLAGS		=	-L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
RM			=	rm -rf

SENTINEL	=	$(OBJ_DIR).compiled

all: $(NAME)
	@cat banner.txt

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "Linking executable..."
	@$(CC) $(OBJ) $(LFLAGS) -o $@

$(LIBFT): | $(LIBFT_DIR)
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) extra > /dev/null

$(LIBFT_DIR):
	@echo "Cloning libft..."
	@git clone --quiet $(LIBFT_URL) $(LIBFT_DIR)

$(MLX):
	@echo "Building minilibx..."
	@$(MAKE) -C $(MLX_DIR) > /dev/null

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ): $(SENTINEL)

$(SENTINEL):
	@echo "Compiling object files..."
	@touch $@

clean:
	@echo "Removing object files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "Removing executable and libraries..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(LIBFT_DIR)

re: fclean all

play: $(NAME)
	@cat banner.txt
	@./play.sh

test: $(NAME)
	@./maps/invalid/test_parser.sh

.PHONY: all clean fclean re play test