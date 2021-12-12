program	= pid_game
objects	= main.o

LDFLAGS	= `pkg-config --cflags --libs sdl2`

all: ${program}
${program}: ${objects}
	${CXX} -o $@ ${objects} ${LDFLAGS}


main.o: main.cpp

.SUFFIXES: .cpp .o
.cpp.o:
	${CXX} -c $< ${CXXFLAGS}

.PHONY: clean
clean:
	rm -f ${program} ${objects}
