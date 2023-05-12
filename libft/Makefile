# ---------------------------------------------------------------------------- #
#	Define the compiler and flags											   #
# ---------------------------------------------------------------------------- #

CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror
CPPFLAGS			= -I includes
ARFLAGS				:= -rcs
RM					:= rm -f

# ---------------------------------------------------------------------------- #
#	Define the directories													   #
# ---------------------------------------------------------------------------- #

SRC_DIR				:= sources

GNL_DIR				:= gnl
PRINTF_DIR			:= printf

OBJ_DIR				:= obj

# ---------------------------------------------------------------------------- #
#	Define the source files													   #
# ---------------------------------------------------------------------------- #

SRCS				:= $(addprefix $(SRC_DIR)/,\
					ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(GNL_DIR)/, get_next_line.c get_next_line_utils.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(PRINTF_DIR)/, ft_printf.c ft_printf_parser.c ft_printf_printer.c ft_printf_printer_tools.c ft_printf_printer_utils.c ft_printf_sub_printer.c)

OBJS				:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

SRCS_BONUS			:= $(addprefix $(SRC_DIR)/,\
					ft_lstadd_back.c \
					ft_lstadd_front.c \
					ft_lstclear.c \
					ft_lstdelone.c \
					ft_lstiter.c \
					ft_lstlast.c \
					ft_lstmap.c \
					ft_lstnew.c \
					ft_lstsize.c)

OBJS_BONUS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_BONUS))

# ---------------------------------------------------------------------------- #
#	Define the variables for progress bar									   #
# ---------------------------------------------------------------------------- #

ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)
TOTAL_FILES			:= $(shell echo $(SRCS) $(SRCS_BONUS) | wc -w)
else
TOTAL_FILES			:= $(shell echo $(SRCS) | wc -w)
endif
COMPILED_FILES		:= 0
STEP				:= 100

# ---------------------------------------------------------------------------- #
#	Define the target														   #
# ---------------------------------------------------------------------------- #

NAME	= libft.a

# ---------------------------------------------------------------------------- #
#	Define the rules														   #
# ---------------------------------------------------------------------------- #

all:
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJS)
		@$(AR) $(ARFLAGS) $@ $^
		@printf "\n$(MAGENTA)[LIBFT] Archiving Success\n$(DEF_COLOR)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | dir_guard
		@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
		@$(eval COMPILED_FILES = $(shell expr $(COMPILED_FILES) + 1))
		@$(eval PROGRESS = $(shell expr $(COMPILED_FILES) "*" $(STEP) / $(TOTAL_FILES)))
		@printf "$(SAVECUR) $(DELINE) $(YELLOW)[LIBFT] [%02d/%02d] ( %3d %%) Compiling $<\r$(DEF_COLOR) $(RESTCUR)" $(COMPILED_FILES) $(TOTAL_FILES) $(PROGRESS)

bonus : $(OBJS) $(OBJS_BONUS)
		@$(AR) $(ARFLAGS) $(NAME) $^
		@touch bonus
		@printf "\n$(MAGENTA)[LIBFT bonus] Archiving Success\n$(DEF_COLOR)"

clean:
		@$(RM) -r $(OBJ_DIR) bonus
		@printf "$(BLUE)[LIBFT] obj. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

fclean:
		@$(RM) -r $(OBJ_DIR) $(NAME) bonus
		@printf "$(BLUE)[LIBFT] obj. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"
		@printf "$(CYAN)[LIBFT] exec. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

re:
		@$(MAKE) fclean
		@$(MAKE) all
		@printf "$(GREEN)[LIBFT] Cleaned and rebuilt everything!\n$(DEF_COLOR)"

dir_guard:
		@mkdir -p $(addprefix $(OBJ_DIR)/, $(GNL_DIR) $(PRINTF_DIR))

norm:
		@(norminette | grep Error) || (printf "$(GREEN)[LIBFT] Norminette Success\n$(DEF_COLOR)")

.PHONY:		all clean fclean re dir_guard norm

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
