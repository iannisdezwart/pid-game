program	= pid_game
objects	= main.o

LDFLAGS	= -lSDL2

all: ${program}
${program}: ${objects}
	${CXX} ${LDFLAGS} -o $@ ${objects}


main.o: main.cpp

.SUFFIXES: .cpp .o
.cxx.o:
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean
clean:
	rm -f ${program} ${objects}
