#NAME
NAME	= philo

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

SRCF	= validate libft

SRCS	= $(addprefix ${SRCDIR}/, $(addsuffix .c, ${SRCF}))
OBJS	= $(addprefix ${OBJDIR}/, $(addsuffix .o, ${SRCF}))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} main.c -I ${INCDIR} ${OBJS} -o ${NAME}
	printf "$(GREEN)$@ compiled\n$(RESET)"

${OBJDIR}/%.o: ${SRCDIR}/%.c | ${OBJDIR}
	${CC} ${CFLAGS} -I ${INCDIR} -c $< -o $@
	printf "$(GREEN)Compiled $<\n$(RESET)"

${OBJDIR}:
	mkdir -p $@

clean:
	${RM} ${OBJDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

debug:
	${CC} -g3 main.c ${SRCS} -I${INCDIR} -o ${NAME}

mem:
	DEBUG=1 make re
	valgrind ${VFLAGS} ./${NAME} 5 400 200 200

hel:
	DEBUG=1 make re
	valgrind --tool=helgrind ./${NAME} 2 800 200 200 1

run: re
	./${NAME} 5 410 200 200

norm:
	@printf "$(CURSIVE)$(YELLOW)"
	@norminette | grep -v OK!
	@printf "$(RESET)"

.PHONY: all clean fclean re debug mem

${S}.SILENT:
