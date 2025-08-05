CXX = g++
CXXFLAGS = -I./SDL3/include -I./SDL3_image/include -I./include -I./Characters  
LDFLAGS = -L./SDL3/lib -lSDL3 -L./SDL3_image/lib -lSDL3_image #-L./SDL3_ttf/lib -lSDL3_ttf
SRC = src/main.cpp src/Core/Engine.cpp src/Graphics/TextureManager.cpp Characters/Warrior.cpp src/Graphics/Animation.cpp src/Inputs/Input.cpp src/Timer/Timer.cpp src/Map/MapParser.cpp src/Map/TileLayer.cpp
OUT = build/engine.exe

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)
