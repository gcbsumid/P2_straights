CXX = clang++  
CXXFLAGS = -g -Wall
OBJECTS = straights.o Card.o Command.o Gameplay.o Player.o ComputerPlayer.o HumanPlayer.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights
GAMEPLAY_FOLDER = gameplay
OBJECT_FOLDER = objects

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

straights.o: ${GAMEPLAY_FOLDER}/straights.cpp
Card.o: ${GAMEPLAY_FOLDER}/Card.h ${GAMEPLAY_FOLDER}/Card.cpp 
Command.o: ${GAMEPLAY_FOLDER}/Command.h ${GAMEPLAY_FOLDER}/Command.cpp
Gameplay.o: ${GAMEPLAY_FOLDER}/Gameplay.h ${GAMEPLAY_FOLDER}/Gameplay.cpp
Player.o: ${GAMEPLAY_FOLDER}/Player.h ${GAMEPLAY_FOLDER}/Player.cpp
ComputerPlayer.o: ${GAMEPLAY_FOLDER}/ComputerPlayer.h ${GAMEPLAY_FOLDER}/ComputerPlayer.cpp
HumanPlayer.o: ${GAMEPLAY_FOLDER}/HumanPlayer.h ${GAMEPLAY_FOLDER}/HumanPlayer.cpp

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
