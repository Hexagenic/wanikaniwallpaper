
SRC_FILES=$(wildcard *.cpp)
OBJ_FILES=$(patsubst %.cpp,%.o, ${SRC_FILES}) 
HEADER_FILES=$(wildcard *.hpp)
LIBS=-lcurl -ljsoncpp -lpng -lfreetype

wanikaniwallpaper: ${OBJ_FILES}
	g++ -std=c++11 ${OBJ_FILES} ${LIBS} -o wanikaniwallpaper

%.o: %.cpp ${HEADER_FILES}
	g++ -std=c++11 -I/usr/include/freetype2 -o $@ $< -c
