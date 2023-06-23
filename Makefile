# ---------------------------------------------------------------------------- #
#	Define the compiler and flags											   #
# ---------------------------------------------------------------------------- #

CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror -O2
CPPFLAGS			= -I includes -I $(LIBFT_DIR)/includes -I $(MLX_DIR)
LDFLAGS				= -L $(LIBFT_DIR) -L .
LDLIBS				:= -l ft -l mlx

# ---------------------------------------------------------------------------- #
#	Define the libraries													   #
# ---------------------------------------------------------------------------- #

LIBFT_DIR			:= libft
MLX_DIR				:= mlx

# ---------------------------------------------------------------------------- #
#	Define the directories													   #
# ---------------------------------------------------------------------------- #

SRC_DIR				:= sources

MAIN_DIR			:= main
PARSER_DIR			:= parser
RENDER_DIR			:= render
EVENT_DIR			:= event
VECTOR_DIR			:= vector
GENERIC_LST_DIR		:= generic_lst

BUILD_DIR			:= build
OBJ_DIR				:= obj

# ---------------------------------------------------------------------------- #
#	Define the source files													   #
# ---------------------------------------------------------------------------- #

SRCS				:= $(addprefix $(SRC_DIR)/$(MAIN_DIR)/, main.c utils.c ft_atof.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(PARSER_DIR)/, parser.c parser_lst.c parser_utils.c parser_validation.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(RENDER_DIR)/, render.c ray.c phong_lighting.c \
						texture.c texture_uv.c texture_tbn.c \
						hit.c hit_sphere.c hit_plane.c hit_cylinder.c hit_cone.c hit_utils.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(EVENT_DIR)/, key_hook.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(VECTOR_DIR)/, vector.c vector_operation.c vector_product.c vector_utils.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(GENERIC_LST_DIR)/, generic_lst.c)

define SRCS_GOAL
	$(if $(filter bonus, $(MAKECMDGOALS)), $(SRCS_BONUS), $(SRCS))
endef

OBJS				:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/$(OBJ_DIR)/%.o, $(SRCS_GOAL))

# ---------------------------------------------------------------------------- #
#	Define the variables for progress bar									   #
# ---------------------------------------------------------------------------- #

TOTAL_FILES			:= $(shell echo $(SRCS_GOAL) | wc -w)
COMPILED_FILES		:= 0
STEP				:= 100

# ---------------------------------------------------------------------------- #
#	Define the target														   #
# ---------------------------------------------------------------------------- #

LIBFT				:= $(LIBFT_DIR)/libft.a
MLX					:= libmlx.dylib
NAME				:= miniRT

# ---------------------------------------------------------------------------- #
#	Define the rules														   #
# ---------------------------------------------------------------------------- #

all:
		@$(MAKE) $(NAME)

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR) bonus

$(MLX):
		@$(MAKE) -C $(MLX_DIR)
		@cp $(MLX_DIR)/$(MLX) $(MLX)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		@$(CC) $(CFLAGS) $(LDLIBS) $(LDFLAGS) $(OBJS) -o $@
		@printf "\n$(MAGENTA)[$(NAME)] Linking Success\n$(DEF_COLOR)"

$(BUILD_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | dir_guard
		@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
		@$(eval COMPILED_FILES = $(shell expr $(COMPILED_FILES) + 1))
		@$(eval PROGRESS = $(shell expr $(COMPILED_FILES) "*" $(STEP) / $(TOTAL_FILES)))
		@printf "$(SAVECUR) $(DELINE) $(YELLOW)[$(NAME)] [%02d/%02d] ( %3d %%) Compiling $<\r$(DEF_COLOR) $(RESTCUR)" $(COMPILED_FILES) $(TOTAL_FILES) $(PROGRESS)

clean:
		@$(MAKE) -C $(LIBFT_DIR) clean
		@$(MAKE) -C $(MLX_DIR) clean
		@$(RM) -r $(BUILD_DIR)
		@printf "$(BLUE)[$(NAME)] obj. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

fclean:
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@$(MAKE) -C $(MLX_DIR) clean
		@$(RM) -r $(BUILD_DIR) $(NAME) $(MLX)
		@printf "$(BLUE)[$(NAME)] obj. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"
		@printf "$(CYAN)[$(NAME)] exec. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

re:
		@$(MAKE) fclean
		@$(MAKE) all
		@printf "$(GREEN)[$(NAME)] Cleaned and rebuilt everything!\n$(DEF_COLOR)"

dir_guard:
		@mkdir -p $(addprefix $(BUILD_DIR)/$(OBJ_DIR)/, $(MAIN_DIR) $(PARSER_DIR) $(RENDER_DIR) \
			$(EVENT_DIR) $(VECTOR_DIR) $(GENERIC_LST_DIR))

norm:
		@$(MAKE) -C $(LIBFT_DIR) norm
		@(norminette | grep Error) || (printf "$(GREEN)[$(NAME)] Norminette Success\n$(DEF_COLOR)")

.PHONY: all clean fclean re dir_guard norm

# ---------------------------------------------------------------------------- #
#	Define the colors														   #
# ---------------------------------------------------------------------------- #

DELINE = \033[K
CURSUP = \033[A
SAVECUR = \033[s
RESTCUR = \033[u

DEF_COLOR	= \033[1;39m
GRAY		= \033[1;90m
RED			= \033[1;91m
GREEN		= \033[1;92m
YELLOW		= \033[1;93m
BLUE		= \033[1;94m
MAGENTA		= \033[1;95m
CYAN		= \033[1;96m
WHITE		= \033[1;97m
