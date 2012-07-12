include Makefile.inc
include gameplay/Makefile.objs

OBJ = straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC}: ${OBJ}
	cd gameplay; make; cd ..
	${CXX} ${CXXFLAGS} ${OBJ} ${OBJECTS} -o ${EXEC}


clean :
	rm -rf ${DEPENDS} ${OBJ} ${OBJECTS} ${EXEC}
	rm -rf gameplay/*.o

    

-include ${DEPENDS}	# reads the .d files and reruns dependencies
