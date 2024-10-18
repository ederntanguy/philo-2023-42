NAME		=	philo

HEADERS		=	headers/action.h headers/creat_destroy.h headers/eating_part.h headers/including_struc.h headers/other_action.h headers/philo.h headers/utils.h

LIB		=	ft_atoi.c ft_putstr_fd.c ft_strdup.c ft_strlen.c ft_strcmp.c

SRCS		=	main.c action.c creat_destroy.c eating_part.c other_action.c utils.c

OBJDIR_SRCS	=	obj
OBJDIR_SRCS2	=	lib/obj

OBJS		=	\
				$(addprefix $(OBJDIR_SRCS)/,$(SRCS:.c=.o)) \
				$(addprefix $(OBJDIR_SRCS2)/,$(LIB:.c=.o))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3
RM			=	rm -f

$(OBJDIR_SRCS)/%.o: %.c | $(OBJDIR_SRCS)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_SRCS2)/%.o: lib/%.c | $(OBJDIR_SRCS2)
				$(CC) $(CFLAGS) -c $< -o $@

all:			${NAME}

$(OBJDIR_SRCS):
				mkdir -p $(OBJDIR_SRCS)

$(OBJDIR_SRCS2):
				mkdir -p $(OBJDIR_SRCS2)

${NAME}:		${OBJS} Makefile ${HEADERS}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
				rm -rf $(OBJDIR_SRCS) $(OBJDIR_SRCS2)

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
