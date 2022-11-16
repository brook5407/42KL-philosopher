NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
#CFLAGS += -g -fsanitize=thread

RM = rm -rf

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

HEADER = $(wildcard $(INC_DIR)/*.h)

SRCS = $(wildcard $(SRC_DIR)/*.c)

vpath %.c $(SRC_DIR)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

#===============================================================================#
#										COLOUR									#
#===============================================================================#

FONT_BOLD	= \e[1m
NO_COLOUR	= \e[0m

FONT_BLUE	= $(NO_COLOUR)\e[38;2;89;147;249m
FONT_YELLOW = $(NO_COLOUR)$(FONT_BOLD)\e[38;2;255;221;98m
FONT_PURPLE = $(NO_COLOUR)\e[38;2;189;147;249m

LF	=\e[1k\r$(NO_COLOUR)

all : $(NAME)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@printf "$(LF)$(FONT_BLUE)Creating $(FONT_YELLOW)$@$(FONT_BLUE)from $(FONT_YELLOW)$<"

$(NAME) : $(LIBFT_FILE) $(HEADER) $(OBJS)
	@printf "$(LF)$(FONT_BLUE)Successfully Created 📦 $(FONT_YELLOW)$@'s Object files\n"
	@printf "$(LF)$(FONT_BLUE)Creating $(FONT_YELLOW)📚 $@\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) -o $@
	@printf "$(FONT_BLUE)Successfully Created $(FONT_YELLOW)🎓 $@ \n$(NO_COLOUR)"
	@printf "$(FONT_BLUE)#====================================================START===================================================================\n"
	@printf "$(FONT_PURPLE)❗Run-$(FONT_YELLOW)./$(NAME) [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n$(NO_COLOUR)"
	@printf "$(FONT_PURPLE)❗Or -$(FONT_YELLOW)./$(NAME) [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n$(NO_COLOUR)"
	@printf "$(FONT_BLUE)#=============================================================================================================================\n$(NO_COLOUR)"

clean :
	@$(RM) $(OBJ_DIR)
	@printf "$(LF)$(FONT_BLUE)Cleaning $(FONT_YELLOW)🧹 $(NAME)'s Object files....\n"

fclean : clean
	@$(RM) $(NAME)
	@printf "$(LF)$(FONT_BLUE)Cleaning $(FONT_YELLOW)🗑 $(NAME)\n"

re : fclean all

.PHONY: all clean fclean re bonus