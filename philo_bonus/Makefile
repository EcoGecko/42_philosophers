#NAME
NAME	= philo_bonus

#COMPILATION
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -rf

VFLAGS	= --leak-check=full --show-leak-kinds=all --track-origins=yes

ifdef DEBUG
	CFLAGS += -g3
endif

ifdef SAN
	CFLAGS += -fsanitize=thread
endif

#COLORS
RESET	= \033[0m
CURSIVE	= \033[3m
BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
MAGENTA	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m

#DIRS
SRCDIR	= src
OBJDIR	= obj
INCDIR	= include

#FILES

SRCF	=

SRCS	= $(addprefix ${SRCDIR}/, $(addsuffix .c, ${SRCF}))
OBJS	= $(addprefix ${OBJDIR}/, $(addsuffix .o, ${SRCF}))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} main.c -I ${INCDIR} ${OBJS} -o ${NAME}
	printf "$(GREEN)$@ compiled\n$(RESET)"

${OBJDIR}/%.o: ${SRCDIR}/%.c | ${OBJDIR}
	${CC} ${FLAGS} -I ${INCDIR} -c $< -o $@
	printf "$(GREEN)Compiled $<\n$(RESET)"


${OBJDIR}:
	mkdir -p $@

clean:
	${RM} ${OBJDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

debug:
	${CC} -g3 main.c ${SRCS} -I${INCS} -o ${NAME}

mem: re
	valgrind ${VFLAGS} ./${NAME}

norm:
	@printf "$(CURSIVE)$(YELLOW)"
	@norminette | grep -v OK!
	@printf "$(RESET)"

.PHONY: all clean fclean re debug mem

${S}.SILENT:
