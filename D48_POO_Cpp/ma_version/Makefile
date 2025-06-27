# Cibles fictives (qui ne servent pas à générer directement un fichier)
.PHONY: all clean

# Dossiers
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Compilateur et flags
CXX := $(shell which g++) -std=c++17 -I$(INC_DIR) -Wall -Wextra

# Fichiers source (tous les .cpp dans src)
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")

# Pattern des fichiers binaires à générer
# @see https://www.gnu.org/software/make/manual/html_node/Text-Functions.html#index-patsubst-1
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Point d'entrée principal
MAIN := $(BUILD_DIR)/app

# Règles
all: $(MAIN)

# Pour que le main se génère, il faut que tous les autres binaires de tous les fichiers .cpp soient créés
$(MAIN): $(OBJS)
	@$(CXX) $^ -o $@

# Compilation des .cpp > .o
# 
# Variables magiques :
#     - $@ : le nom de la cible (le fichier bin)
#     - $^ : la liste de toutes les dépendances (les fichiers sources)
#     - $< : la première dépendance
#
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
