CC = g++
CFLAGS = -I./SDL3/include \
		 -I./SDL3_image/include \
		 -I./include \
		 -I./Characters

LDFLAGS = -L./SDL3/lib -lSDL3 \
		  -L./SDL3_image/lib -lSDL3_image \
		  #-L./SDL3_ttf/lib -lSDL3_ttf

#==============New test
# SRC = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard Characters/*.cpp)
# OBJ = $(patsubst %.cpp, build/objfiles/%.o, $(SRC))

# OUT = build/engine.exe

# #Main rule
# all: $(OUT)

# #Linking
# $(OUT) : $(OBJ)
# 	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

# #Compilation of objetc files
# build/objfiles/%.o: %.cpp
# #make does not create dir automatically so create it if not exist (-p)
# 	mkdir $(dir $@) 
# 	$(CC) $(CFLAGS) -c $< -o $@

# #clean
# clean:
# 	rm -r build\objfiles

# run: $(OUT)
# 	./$(OUT)
#=========================


#backup

OUT = build/engine.exe
SRC = src/main.cpp src/Core/Engine.cpp src/Graphics/TextureManager.cpp Characters/Warrior.cpp src/Graphics/Animation.cpp src/Inputs/Input.cpp src/Timer/Timer.cpp src/Map/MapParser.cpp src/Map/TileLayer.cpp src/Camera/Camera.cpp
all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)