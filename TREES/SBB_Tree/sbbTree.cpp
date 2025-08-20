#include <iostream>
using namespace std;

// Generic element
const char VERTICAL = 'v';
const char HORIZONTAL = 'h';

template<typename T>
struct SBB_TBinaryNode {
    int key;
    T data;
    SBB_TBinaryNode<T> *left;
    char L;
    SBB_TBinaryNode<T> *right;
    char R;
};

// Points to the root of the Generic SBB Tree
template <typename T>
struct SBB_TBinaryTree {
    SBB_TBinaryNode<T> *root;
};

// Boot Generic Tree
template <typename T>
void SBB_boot(SBB_TBinaryTree<T> &tree) {
    tree.root = NULL;
};

// SBB_inserts a new node in the Generic SBB Tree
template<typename T>
int SBB_insert (SBB_TBinaryNode<T> *&node, int key, T data) {
    if (node == NULL) {
        node = new SBB_TBinaryNode<T>;
        node->key = key;
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return 1;
    }
    else {
        if (key > node->key) {
            int n = SBB_insert(node->right, key, data);
            if (n == 1) {
                node->R = HORIZONTAL;
                n++;
            } else {
                if (n == 2 && node->R == HORIZONTAL) {
                    n = 1;
                    if(node->left->R == HORIZONTAL)
                        RL(node);
                    else
                        RR(node);
                } else
                  n = 0;
            }
        } else if (key < node->key) {
            int n = SBB_insert(node->left, key, data);
            if(n == 1) {
                node->L = HORIZONTAL;
                n++;
            } else {
                if (n == 2 && node->L == HORIZONTAL) {
                    n = 1;
                    if (node->left->L == HORIZONTAL)
                       LL(node);
                    else
                       LR(node);
                       balanceLeft(node->key);
                } else
                    n = 0;
            }
        }
    }
    return 0;
}

// Balance case: Left-Left
template <typename T>
void LL(SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->left;
    ap->left = ap1->right;
    ap1->right = ap;
    ap1->L = VERTICAL;
    ap->L = VERTICAL;
    ap = ap1;
}

// Balance case: Right-Right
template <typename T>
void RR(SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->right;
    ap->right = ap1->left;
    ap1->left = ap;
    ap1->R = VERTICAL;
    ap->R = VERTICAL;
    ap = ap1;
}

// Balance case: Left-Right
template <typename T>
void LR (SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->left;
    SBB_TBinaryNode<T> *ap2 = ap1->right;
    ap1->R = VERTICAL;
    ap->L = VERTICAL;
    ap1->right = ap2->left;
    ap2->left = ap1;
    ap->left = ap2->right;
    ap2->right = ap;
    ap = ap2;
}

// Balance case: Right-Left
template <typename T>
void RL (SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->right;
    SBB_TBinaryNode<T> *ap2 = ap1->left;
    ap1->L = VERTICAL;
    ap->R = VERTICAL;
    ap1->left = ap2->right;
    ap2->right = ap1;
    ap->right = ap2->left;
    ap2->left = ap;
    ap = ap2;
}

int main() {
    bool menu = true;
    int resp;
    int conteudo;
    int codigo_chave;
    SBB_TBinaryTree<int> tree;

    SBB_boot(tree);

    while(menu){
    system("CLS");
    printTree(tree.root);
    showTree(tree.root, 3);

    cout << "\n" << endl;
    cout << "=========SBB==========" << endl;
    cout << "=== 1 -  SBB_insert    ===" << endl;
    cout << "=== 2 -  Remove    ===" << endl;
    cout << "=== 3 -  Search    ===" << endl;
    cout << "=== 4 -            ===" << endl;
    cout << "=== 5 -            ===" << endl;
    cout << "=== 6 -            ===" << endl;
    cout << "=== 7 -  RESET     ===" << endl;
    cout << "=== 8 -  Quit      ===" << endl;
    cout << "=========MENU=========" << endl;
    cout << "==KING OF THE JUNGLE==" << endl;

    cin >> resp;
    switch (resp) {
        case 1:
            cout << "digite uma chave" << endl;
            cin >> codigo_chave;
            cout << "digite um valor para o conteudo" << endl;
            cin >> conteudo;
            SBB_insert(tree.root, codigo_chave, conteudo);
            break;
        case 2:
            cout << "digite uma chave para remocao" << endl;
            cin >> codigo_chave;
            searchRemove(tree.root, codigo_chave);
            break;
        case 3:
            cout << "digite uma chave para bUScar" << endl;
            cin >> codigo_chave;
            cout << "Valor do Conteudo: " << searchData(tree.root, codigo_chave) << endl;
            system("PAUSE");
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            SBB_boot(tree);
            break;
        case 8:
            return 0;
            break;
        default:
            cout << "RESPOSTA INVALIDA" << endl;
            system("pause");  /*CodeBlocks*/

            break;
        }
    }
   return 0;
}