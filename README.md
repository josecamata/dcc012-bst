# BST: Binary Search Tree

Uma árvore de busca binária é uma estrutura de dados em árvore onde cada nó possui no máximo dois filhos: um nó à esquerda e um nó à direita. Além disso, cada nó da árvore armazena uma chave (valor) que é maior que todas as chaves armazenadas em seu subárvore esquerdo e menor que todas as chaves armazenadas em seu subárvore direito.

A árvore de busca binária é frequentemente usada para implementar estruturas de dados que requerem busca, inserção e exclusão eficientes em tempo médio, como mapas e conjuntos. A complexidade de tempo dessas operações é proporcional à altura da árvore, que é o número de nós percorridos da raiz até o nó desejado. Em uma árvore de busca binária balanceada, a altura é proporcional ao logaritmo do número de nós na árvore, o que garante um bom desempenho em média.

## Implementação

Um nó em uma árvore de busca binária normalmente armazena duas informações: 
  - uma chave (valor)
  - ponteiros para seus filhos esquerdo e direito.
  - ponteiro para nó pai

Aqui está um exemplo de como um nó poderia ser representado em uma árvore de busca binária usando uma linguagem de programação como o C++:

```C++
Class BSTNode {
    public:
        BSTNode(int key);
    private: 
        int key;               // valor armazenado no nó
        BSTNode* left;         // ponteiro para o filho esquerdo
        BSTNode* right;        // ponteiro para o filho direito
        BSTNode* parent;       // ponteiro para o nó pai
};
```

A estrutura de uma árvore binária deve armazena um ponteiro para a raiz da árvore e implementar os métodos para inserção, busca e remoção de nós da árvore.

Aqui está um exemplo de implementação básica de uma árvore binária em C++:
```C++
Class BST{
    public:
        BST();
        BSPNode* insert(int key);
        BSPNode* search(int key);
        void     remove(int key);
        ~BSP();
    private: 
        BSTNode* root;         // ponteiro para o a raiz da arvore
};
```

## Código 

Neste repositório é apresentado uma implementação de uma classe template de arvore binária de pesquisa baseado no livro: **Algoritmo: Teoria e Prática** de *Thomas H. Cormen et al.*

A estrutura do repositório é a seguinte:
```
dcc012-bst
    ├── include
    │    └── bst.h
    ├── main.cpp
    └── CMakeLists.txt 
```      
 - No arquivo [bst.h](include/bst.h) está o codigo fonte do tipo abstrado de dados (TAD) árvore binárias com as implementação das principais operações.
 - O arquivo [main.cpp](main.cpp) ilustra um exemplo básico da utilização da TAD BST.

## Exercício:
1. Leia o capitulo 12.1 do livro  **Algoritmo: Teoria e Prática** de *Thomas H. Cormen et al.* . O livro esta disponivel na biblioteca virtual do siga.
2. Veja como os pseudocódigos do livro foram implementados.
3. Modifique a main.cpp com novos exemplos e testes.
