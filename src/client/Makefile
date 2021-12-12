program	= pid_game
objects	= main.o keybindings.o

LDFLAGS	= `pkg-config --cflags --libs sdl2`

all: ${program}
${program}: ${objects}
	${CXX} -o $@ ${objects} ${LDFLAGS}


main.o: main.cpp
keybindings.o: keybindings.cpp keybindings.hpp

.SUFFIXES: .cpp .o
.cpp.o:
	${CXX} -c $< ${CXXFLAGS}

.PHONY: clean
clean:
	rm -f ${program} ${objects}
