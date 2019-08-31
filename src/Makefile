CC=gcc
C_FLAGS=-g

EXE=ugameboy
SRC=utils.c cpu.c mem.c
HEADERS=${SRC:.c=.h}
OBJ=${SRC:.c=.o}

${EXE}=${EXE:=.c} ${EXE:=.h}

../bin/ugameboy: ${OBJ} ${EXE:=.c} ${EXE:=.h}
	${CC} ${C_FLAGS} ${OBJ} ${EXE:=.c} -o ${EXE}
	mv ${EXE} ../bin

utils.o: utils.c utils.h
	${CC} ${C_FLAGS} utils.c -c

cpu.o: cpu.c cpu.h
	${CC} ${C_FLAGS} cpu.c -c

mem.o: mem.c mem.h
	${CC} ${C_FLAGS} mem.c -c

clean: ${EXE} ${OBJ}
	rm ${EXE} ${OBJ}

