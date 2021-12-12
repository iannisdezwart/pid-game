program	= pid_game
objects	= main.o

LDFLAGS	= `pkg-config --cflags --libs sdl2`

all: ${program}
${program}: ${objects}
	${CXX} ${LDFLAGS} -o $@ ${objects}


main.o: main.cpp

.SUFFIXES: .cpp .o
.cpp.o:
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean
clean:
	rm -f ${program} ${objects}
