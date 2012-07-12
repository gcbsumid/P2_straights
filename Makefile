include Makefile.inc
include gameplay/Makefile.objs
include gui/Makefile.objs

OBJ = straights.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights
LDFLAGS = `pkg-config gtkmm-2.4 --libs`

#${EXEC}: ${OBJ}
#	cd gameplay; make; cd ..; cd gui; make; cd ..;
#	${CXX} ${CXXFLAGS} ${OBJ} ${OBJECTS} -o ${EXEC}
#  ${OBJECTSGAME} ${OBJECTS}
${EXEC}: ${OBJ}
	cd gameplay; make; cd ..; cd gui; make; cd ..;	
	${CXX} ${CXXFLAGS} ${OBJ} ${OBJECTS} ${LDFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJ} ${OBJECTS} ${EXEC}
	rm -rf gameplay/*.o
	rm -rf gameplay/*.d
	rm -rf gui/*.o 
	rm -rf gui/*.d
	rm -rf *.o
	rm -rf *.d

    

-include ${DEPENDS}	# reads the .d files and reruns dependencies
