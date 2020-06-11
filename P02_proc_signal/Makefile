CC := gcc
CFLAGS = -Wall -Wextra -O2 -g
LDFLAGS := -L. -lsig

LSRC := $(wildcard lib*.c)
LIB := $(LSRC:.c=.so)
SRC := $(filter-out ${LSRC}, $(wildcard *.c))
EXE := $(SRC:.c=.exe)

all: ${LIB} ${EXE}

%.so: %.o
	${CC} ${CFLAGS} -fPIC -shared $^ -o $@

%.exe: %.o
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

#%.o: %.c
#	${CC} ${CFLAGS} -c $^ -o $@

clean:
	${RM} *.so ${EXE} *.o

allclean: clean
	${RM} .dep a.out

.dep: $(wildcard *.c)
	@${CC} ${CFLAGS} -MM $^ > .dep

-include .dep
