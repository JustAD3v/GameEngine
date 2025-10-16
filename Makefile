CC = g++
AR = ar rcs

CFLAGS = -I./SDL3/include -I./SDL3_image/include -I./include -I./Characters
LDFLAGS = -L./SDL3/lib -lSDL3 -L./SDL3_image/lib -lSDL3_image

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard Characters/*.cpp)
OBJ = $(patsubst %.cpp, build/obj/%.o, $(SRC))

OUT_DIR = build
OBJ_DIR = $(OUT_DIR)/obj
OUT_LIB = $(OUT_DIR)/libEngine.a

# Commandes Windows
MKDIR = if not exist "$(subst /,\\,$(1))" mkdir "$(subst /,\\,$(1))"
RMDIR = if exist "$(subst /,\\,$(1))" rmdir /s /q "$(subst /,\\,$(1))"

# Règle principale
all: $(OUT_LIB)

$(OUT_LIB): $(OBJ)
	@echo Creating static library...
	@$(call MKDIR,$(OUT_DIR))
	$(AR) $(OUT_LIB) $(OBJ)
	@echo Library generated : $(OUT_LIB)

# Compilation des objets
$(OBJ_DIR)/%.o: %.cpp
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	@$(call RMDIR,$(OUT_DIR))
	@echo Cleaning done

.PHONY: all clean
