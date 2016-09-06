
SRC_FILES=$(wildcard *.cpp)
OBJ_FILES=$(patsubst %.cpp,%.o, ${SRC_FILES}) 
HEADER_FILES=$(wildcard *.hpp)

LIBPNGFLAGS := $(shell pkg-config --cflags --libs libpng)
LIBCURLFLAGS := $(shell pkg-config --cflags --libs libcurl)
JSONCPPFLAGS := $(shell pkg-config --cflags --libs jsoncpp)
FREETYPEFLAGS := $(shell pkg-config --cflags --libs freetype2)

CFLAGS := $(LIBPNGFLAGS) $(LIBCURLFLAGS) $(JSONCPPFLAGS) $(FREETYPEFLAGS) -lboost_program_options

wanikaniwallpaper: ${OBJ_FILES}
	g++ $(CFLAGS) ${OBJ_FILES} -o wanikaniwallpaper

%.o: %.cpp ${HEADER_FILES}
	g++ $(CFLAGS) -I/usr/include/freetype2 -o $@ $< -c
