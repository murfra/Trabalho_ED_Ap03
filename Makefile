# Variáveis
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

# Verificando o sistema operacional
ifeq ($(OS),Windows_NT) TARGET = sparse_matrix.exe
else TARGET = sparse_matrix
endif

# Regra principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

# Regra para compilar os arquivos .cpp em .o
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar um arquivo específico
compile: build/%.o

# Regra para compilar o relatório
relatorio: relatorio/relatorio.tex
	cd relatorio && pdflatex relatorio.tex

# Limpar arquivos gerados pelo LaTeX
clean:
	rm -f relatorio/*.aux relatorio/*.log relatorio/*.pdf

.PHONY: all clean relatorio compile
