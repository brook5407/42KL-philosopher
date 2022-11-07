NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIBFLAGS = -lncurses

RM = rm -rf

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

HEADER	= $(wildcard $(INC_DIR)/*.h)
SRCS	= $(wildcard *.c)

vpath %.c $(SRC_DIR)

OBJS	= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

#===============================================================================#
#										COLOUR									#
#===============================================================================#

CL_BOLD		= \e[1m
CL_DIM		= \e[2m
CL_UDLINE	= \e[4m

NO_COLOUR	= \e[0m

BG_TEXT		= \e[48;2;45;55;72m
BG_BLACK	= \e[48;2;30;31;33m

FG_WHITE 	= $(NO_COLOUR)\e[0;37m
FG_TEXT		= $(NO_COLOUR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOUR)$(CL_BOLD)\e[38;2;255;121;198m

LF	=\e[1k\r$(NO_COLOUR)
CRLF=\n$(LF)

all : $(NAME)

clean :
	@$(RM) $(OBJ_DIR)
	@printf "$(LF)📃 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files....\n"

fclean : clean
	@$(RM) $(NAME)
	@printf "$(LF)📃 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(LIBFT_FILE) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@printf "$(LF)📝 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : $(LIBFT_FILE) $(HEADER) $(OBJS)
	@printf "$(LF)💯 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📙 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(CLIBFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $@
	@printf "$(LF)🎓 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOUR)"