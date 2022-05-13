# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 13:33:10 by rburri            #+#    #+#              #
#    Updated: 2022/05/13 15:36:49 by rburri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_SRC		=	./miniRT_base

DIR_BON		=	./miniRT_bonus

all:		${DIR_SRC} ${DIR_BON}

${DIR_SRC}:
			${MAKE} -C $@
			@cp ./miniRT_base/miniRT .

${DIR_BON}:	
			${MAKE} -C $@
			@cp ./miniRT_bonus/bonus .

bonus:		${DIR_BON}

minirt:		${DIR_SRC}

clean:

fclean:		clean
			${RM} miniRT
			${RM} bonus
			@${MAKE} -C ${DIR_SRC} fclean
			@${MAKE} -C ${DIR_BON} fclean

re:			fclean  all

.PHONY:		all clean fclean ${DIR_SRC} ${DIR_BON} re