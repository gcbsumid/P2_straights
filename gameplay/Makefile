include ../Makefile.inc
include Makefile.objs

OBJLIB = GamePlay.a
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

all : ${OBJECTSGAME}
	${CXX} -c ${CXXFLAGS} ${OBJECTSGAME}
	cp *.o ..


clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
