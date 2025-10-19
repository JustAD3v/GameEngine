CC = g++
CFLAGS = -I../include -I../SDL3/include -I../SDL3_image/include -I./include
LDFLAGS = -L../build -lEngine -L../SDL3/lib -lSDL3 -L../SDL3_image/lib -lSDL3_image

OUT = build/game.exe
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst %.cpp, build/obj/%.o, $(SRC))

all: $(OUT)

$(OUT): $(OBJ) ../build/libEngine.a build
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

build/obj/%.o: %.cpp ../include/IGame.h ../include/Engine.h build/obj
	$(CC) $(CFLAGS) -c $< -o $@

build/obj:
	mkdir build/obj

build:
	mkdir build
	
run: all
	$(OUT)

clean:
	if exist build rmdir /S /Q build

.PHONY: all run clean
