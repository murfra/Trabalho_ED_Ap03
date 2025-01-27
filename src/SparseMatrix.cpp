#include "../include/SparseMatrix.h"

#include <iostream>
#include <stdexcept>

void SparseMatrix::initializeMatrix(int m, int n) {
    // Inicilizando nós sentinela para cada linha m e coluna n
    for(int i = m+n; i >= 1; i--) {
        if (i > n) { // inicilizando as colunas (0, n)
            Node *aux = new Node(0, i-n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else { // inicilizando as linhas (m, 0);
            Node *aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }
}

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n) {
    if (m <= 0 || n <= 0) throw std::out_of_range("Invalid line or column");
    initializeMatrix(m, n);
}

SparseMatrix::SparseMatrix(const SparseMatrix& matrix) {
    if (this != &matrix) {
        clear();
        linhas = matrix.linhas;
        colunas = matrix.colunas;
        initializeMatrix(linhas, colunas);

        Node* aux = matrix.m_head->direito;
        Node* temp = m_head;

        // Inicializa todos os nós colunas sentinelas
        while(aux != matrix.m_head) {
            Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
            auy->direito = m_head->direito;
            m_head->direito = auy;
            aux = aux->direito;
        }
        
        aux = matrix.m_head->abaixo;
        while (aux != matrix.m_head) {
            Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
            auy->abaixo = m_head;
            temp->abaixo = auy;
            temp = temp->abaixo;
            aux = aux->abaixo;
        } 
    }
}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix() {
    clear();
    // m_head = nullptr;
    delete m_head;
}

void SparseMatrix::clear(){
    // Libera os nós em cada coluna
    // Começa de (0, 1) 
    Node* col = m_head->direito;
    while (col != m_head) { // Anda as colunas
        Node* atual = col->abaixo; // Primeiro nó na coluna (1,1)
        while (atual != col) { // Percorre todos os nós na coluna
            Node* temp = atual;
            atual = atual->abaixo;
            delete temp; // Libera o nó atual
        }
        
        Node* temp = col;
        col = col->direito;
        delete temp; // Libera o nó sentinela da coluna
    }

    // Libera os nós sentinelas das linhas
    Node* linha = m_head->abaixo; // Começa na primeira linha (1, 0)
    while (linha != m_head) { // Anda as linhas
        Node* temp = linha;
        linha = linha->abaixo;
        delete temp; // Libera o nó sentinela da linha
    }

    m_head->direito = m_head;
    m_head->abaixo = m_head;
}

void SparseMatrix::insert(int i, int j, double value) {
    // Teste de verificação de limites para as linhas
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }
    else if (value != 0) {
        Node *aux = m_head->direito;

        // move o aux até a coluna j
        while (aux->coluna != j) {
            aux = aux->direito;
        }
        // move o aux até a linha i ou até quse seja igual a 0
        while (aux->abaixo->linha != 0 && aux->abaixo->linha != i) {
            aux = aux->abaixo;
        }

        // verifica se já existe uma célula na posição i, j
        if (aux->abaixo->linha == i) aux->abaixo->valor = value;
        else {
            Node *temp = new Node(i, j, value);
            temp->abaixo = aux->abaixo;
            aux->abaixo = temp;

            aux = m_head->abaixo; // redefine aux para começar da linha 1, coluna 0
            while (aux->linha != i) {
                aux = aux->abaixo; // move o aux até a linha i
            }
            
            // move até o último "direito", até a última coluna, no caso
            while (aux->direito->coluna != 0) aux = aux->direito;

            temp->direito = aux->direito; // faz temp apontar para o começo da linha
            aux->direito = temp; // aponta o direito para o temp
        }
    }
}

double SparseMatrix::get(int i, int j) {
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }

    Node* aux_linha = m_head->abaixo;
    while (aux_linha->linha != m_head->linha && aux_linha->linha < i) aux_linha = aux_linha->abaixo;
    
    if (aux_linha == m_head || aux_linha->linha != i) return 0; 
    
    Node* aux_coluna = aux_linha->direito;
    while (aux_coluna != aux_linha && aux_coluna->coluna < j) aux_coluna = aux_coluna->direito;
    
    if (aux_coluna == aux_linha || aux_coluna->coluna != j) return 0; 
    
    return aux_coluna->valor;
}

void SparseMatrix::print() {
    Node *aux = m_head->abaixo;

    for (int i = 1; i <= linhas; i++) {
        Node *temp = aux->direito; 

        std::cout << "[ ";
        for (int j = 1; j <= colunas; j++) {
            if (temp->coluna == j) std::cout << temp->valor << " ";
            else std::cout << 0 << " ";

            if (j == temp->coluna) temp = temp->direito;
        }
        aux = aux->abaixo;
        std::cout << ']' << std::endl;
    }
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& matrix) {
    if (this != &matrix) {
        clear();
        linhas = matrix.linhas;
        colunas = matrix.colunas;
        initializeMatrix(linhas, colunas);

        Node* aux = matrix.m_head->direito;
        Node* temp = m_head;

        // Inicializa todos os nós colunas sentinelas
        while(aux != matrix.m_head) {
            Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
            auy->direito = m_head->direito;
            m_head->direito = auy;
            aux = aux->direito;
        }
        
        aux = matrix.m_head->abaixo;
        while (aux != matrix.m_head) {
            Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
            auy->abaixo = m_head;
            temp->abaixo = auy;
            temp = temp->abaixo;
            aux = aux->abaixo;
        }
    }
    return *this;
}

int SparseMatrix::getLines() const {
  return linhas;
}

int SparseMatrix::getCols() const {
  return colunas;
}

int SparseMatrix::size() const {
  return linhas*colunas;
}
