#include "../include/SparseMatrix.h"

#include <iostream>
#include <stdexcept>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n) {
    if (m <= 0 || n <= 0) throw std::out_of_range("Invalid line or column");
    
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

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix() {
    clear();
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
}

void SparseMatrix::insert(int i, int j, double value) {
    // Teste de verificação de limites para as linhas
    // veja que não podem ser negativas
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }
    
    else if (value != 0) {
        Node *aux = m_head->direito;

        while (aux->coluna != j) aux = aux->direito; // move o aux até a coluna j
        while (aux->abaixo->linha != 0 && aux->abaixo->linha != i) aux = aux->abaixo;

        // verifica se já existe uma célula na posição i, j
        if (aux->abaixo->linha == i) aux->abaixo->valor = value;
        else {
            Node *temp = new Node(i, j, value);
            temp->abaixo = aux->abaixo;
            aux->abaixo = temp;

            aux = m_head->abaixo; // redefine aux para começar da linha 1, coluna 0
            while (aux->linha != i) aux = aux->abaixo; // move o aux até a linha i
            
            // move até o último "direito", até a última coluna, no caso
            while (aux->direito->coluna != 0) aux = aux->direito;

            temp->direito = aux->direito; // faz temp apontar para onde aux apontava (o começo da linha)
            aux->direito = temp; // aponta o direito para o temp
            
        }
    }
}

double SparseMatrix::get(int i, int j) {
    
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }

    Node* aux = m_head->abaixo;

    while (aux->linha != m_head->linha && aux->linha < i) aux = aux->abaixo;
    
    if (aux == m_head || aux->linha != i) return 0; 
    
    Node* aux2 = aux->direito;

    while (aux2 != aux && aux2->coluna < j) aux2 = aux2->direito;
    
    if (aux2 == aux || aux2->coluna != j) return 0; 
    
    return aux2->valor;
}

void SparseMatrix::print() {
    Node *aux = m_head->abaixo;

    for (int i = 1; i <= linhas; i++) {
        Node *temp = aux->direito; // pega o valor direito do aux, seria algo como m_head->abaixo->direito

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

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& matriz) {
    this->~SparseMatrix();
    this->m_head = new Node(0, 0);
    linhas = matriz.linhas;
    colunas = matriz.colunas;

    Node* aux = matriz.m_head->direito;
    Node* temp = m_head;

    // Inicializa todos os nós colunas sentinelas
    while(aux != matriz.m_head) {
        Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
        auy->direito = m_head->direito;
        m_head->direito = auy;
        aux = aux->direito;
    }
    
    aux = matriz.m_head->abaixo;
    while (aux != matriz.m_head) {
        Node* auy = new Node(aux->linha, aux->coluna, aux->valor);
        auy->abaixo = m_head;
        temp->abaixo = auy;
        temp = temp->abaixo;
        aux = aux->abaixo;
    }

    Node* atualM = matriz.m_head->abaixo->direito;
    for (int i = 0, j = linhas; i <= colunas && atualM->coluna != 0; i++) {
        if (atualM->valor != 0) {
            insert(atualM->linha, atualM->coluna, atualM->valor);
        }
        atualM = atualM->direito;

        if (i == colunas && j > 0) {
            atualM = atualM->direito;
            atualM = atualM->abaixo->direito;
            i = 0;
            j--;
        }
    }

    return *this;
}

int SparseMatrix::getLines() {
  return linhas;
}

int SparseMatrix::getCols() {
  return colunas;
}

int SparseMatrix::size() {
  return linhas*colunas;
}
