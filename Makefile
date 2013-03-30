
SRC_FILES=$(wildcard *.cpp)
OBJ_FILES=$(patsubst %.cpp,%.o, ${SRC_FILES}) 
HEADER_FILES=$(wildcard *.hpp)
LIBS=-lcurl -ljsoncpp -lpng -lfreetype -lboost_program_options

wanikaniwallpaper: ${OBJ_FILES}
	g++  ${OBJ_FILES} ${LIBS} -o wanikaniwallpaper

%.o: %.cpp ${HEADER_FILES}
	g++ -I/usr/include/freetype2 -o $@ $< -c
