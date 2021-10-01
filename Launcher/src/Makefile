-include dependencies.txt

TARGET = ShipDuelLauncher
CC = g++
DEBUG = -g
OPT = -O0
WARN = -Wall 
PTHREAD = -pthread
CCFLAGS = $(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe -std=c++0x
GTKLIB = `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`
LD = g++
LDFLAGS = $(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS = main.o
SOURCES = main.cpp
 
all: $(OBJS)
	$(LD) -rdynamic -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: main.cpp
	$(CC) -c $(CCFLAGS) main.cpp $(GTKLIB) -o main.o
    
clean:
	rm -f *.o $(TARGET)

depend:
	$(CC) -M $(SOURCES)