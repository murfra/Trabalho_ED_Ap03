# Variáveis
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

# Verificando o sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    MKDIR = if not exist build mkdir build
    TARGET = sparse_matrix.exe
else
    RM = rm -f
    MKDIR = mkdir -p build
    TARGET = sparse_matrix
endif

# Regra principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

# Regra para compilar os arquivos .cpp em .o
build/%.o: src/%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o relatório
relatorio: relatorio/relatorio.tex
	cd relatorio && pdflatex relatorio.tex

# Limpar arquivos gerados pelo LaTeX e compilação
clean:
	$(RM) build\*.o $(TARGET) relatorio\*.aux relatorio\*.log relatorio\*.pdf

.PHONY: all clean relatorio
