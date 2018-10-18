all:  libjsoncpp.so test mymv
LIB_PATH = ./lib
LOCAL_LIBS = jsoncpp
LIBS = pthread
INCLUDES = ./include/
FLAGS = std=c++11 -g -Wall
OFLAGS = fPIC -shared
JSON_SRCS = ./src/json/*.cpp
SRCS = ./src/common/*.cpp \
	./src/config/*.cpp \
	./src/obj/*.cpp \
	./src/bt/*.cpp \
	./src/bt_node/action/*.cpp \
	./src/bt_node/condition/*.cpp \
	./test.cpp
	
test: $(SRCS)
	g++ $^ -g -o $@ -$(FLAGS) -I$(INCLUDES) -L$(LIB_PATH) -l$(LOCAL_LIBS) -l$(LIBS)
	
#server: server.cpp
#	g++ $^ -g -o $@ -$(FLAGS) -I$(INCLUDES) -L$(LIB_PATH) -l$(LOCAL_LIBS) -l$(LIBS)
	
libjsoncpp.so: $(JSON_SRCS)
	g++ $^ -g -o $@ -$(FLAGS) -$(OFLAGS) -I$(INCLUDES) -l$(LIBS) 
	
.PHONY : clean
clean:
	rm -rf ./bin/* *.o
	rm -rf ./lib/*
	
mymv:
	mv libjsoncpp.so ./lib/
	mv test ./bin/
	#mv server ./bin/