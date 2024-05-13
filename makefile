# Diretórios importantes.
SRC_DIR := src/
INCLUDE_DIR := include/
BUILD_DIR := build/

CXXFLAGS := -pedantic-errors -Wall -I$(SRC_DIR) -I$(INCLUDE_DIR) -I/usr/include/opencv4/
LDLIBS := -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui

# Lista de arquivos .cpp
CPP_FILES := $(shell find $(SRC_DIR) -name "*.cpp")

# Lista de arquivos .o
OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp, $(BUILD_DIR)%.o, $(CPP_FILES))

# Lista de headers sem implementação.
HEADERSONLY := $(filter-out $(patsubst $(SRC_DIR)%.cpp, $(SRC_DIR)%.hpp, $(CPP_FILES)), $(shell find $(SRC_DIR) -name "*.hpp"))

ALL: $(BUILD_DIR) main

# Target para gerar executável para debugging.
debug: CXXFLAGS += -g
debug: clean ALL

# Target para ligação.
main: $(BUILD_DIR)main.o $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $@ $(LDLIBS)

# Targets para compilação.
$(BUILD_DIR)main.o: $(SRC_DIR)main.cpp $(HEADERSONLY)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.hpp $(HEADERSONLY)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target para criar o diretório build.
$(BUILD_DIR):
ifeq ($(wildcard $(BUILD_DIR)),)
    $(shell mkdir $(BUILD_DIR))
    $(shell find $(SRC_DIR) -type d -exec mkdir -p "$(BUILD_DIR){}" \;)
    $(shell mv $(BUILD_DIR)$(SRC_DIR)* $(BUILD_DIR) 2>/dev/null ; true) # "2>/dev/null" faz um possível erro do mv ser ignorado
    $(shell rm -r $(BUILD_DIR)$(SRC_DIR))
endif

# Target para apagar objetos e executável.
clean:
	rm -rf $(BUILD_DIR) *.o main
	clear