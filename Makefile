include Makefile.inc

OBJECTS = straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights


clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
