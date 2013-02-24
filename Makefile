
SRC_FILES=$(wildcard *.cpp)
HEADER_FILES=$(wildcard *.hpp)
LIBS=-lSDL -lSDL_ttf -lcurl -ljsoncpp -lpng

wanikaniwallpaper: ${SRC_FILES} ${HEADER_FILES}
	g++ -std=c++11 ${SRC_FILES} ${LIBS} -o wanikaniwallpaper
