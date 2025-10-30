CC = g++
CFLAGS = -I../include -I../SDL3/include -I../SDL3_image/include -I./include
LDFLAGS = -L../build -lEngine -L../SDL3/lib -lSDL3 -L../SDL3_image/lib -lSDL3_image
DBGFLAG = -DDEBUG -g

OUT = build/game.exe
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst %.cpp, build/obj/%.o, $(SRC))

all: $(OUT)

$(OUT): $(OBJ) ../build/libEngine.a
	@if not exist build mkdir build
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS) 

build/obj/%.o: %.cpp ../include/IGame.h ../include/Engine.h 
	@if not exist build\obj\src mkdir build\obj\src
	$(CC) $(CFLAGS) $(DBGFLAG) -c $< -o $@ 

run: all
	$(OUT)

clean:
	@if exist "build/obj" rmdir /S /Q "build/obj" && echo Obj folder deleted.
	@if exist "build\game.exe" del /F /Q "build\game.exe" && echo Executable deleted.

.PHONY: all run clean
