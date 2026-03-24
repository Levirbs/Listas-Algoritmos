#include <iostream>
#include <algorithm>

using namespace std;

class Node {
    public:
        int size; 
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr), size(1), height(0) {}
};

class AVL {
    private:
        Node* root;

        Node* inserthelp(Node* rt, int k) {
            if (rt == nullptr) return new Node(k);
            
            if (rt->key > k) {
                rt->left = inserthelp(rt->left, k);
            } else {
                rt->right = inserthelp(rt->right, k);
            }
            
            rt->height = 1 + max(h(rt->left), h(rt->right));
            rt->size = 1 + size(rt->left) + size(rt->right);

            int balance = getBalance(rt);
            if (balance < -1 && k >= rt->right->key) return leftRotate(rt);
            if (balance > 1 && k < rt->left->key) return rightRotate(rt);
            if (balance > 1 && k >= rt->left->key) {
                rt->left = leftRotate(rt->left);
                return rightRotate(rt);
            }
            if (balance < -1 && k <= rt->right->key) {
                rt->right = rightRotate(rt->right);
                return leftRotate(rt);
            }
            return rt;

        }

        int h(Node* rt) {
            if (rt == nullptr) return -1;
            return rt->height;
        }

        int getBalance(Node* rt) {
            if (rt == nullptr) return 0;
            return h(rt->left) - h(rt->right);
        }

        Node* rightRotate(Node* rt) {
            Node* l = rt->left;
            Node* lr = l->right;
            l->right = rt;
            rt->left = lr;
            rt->height = max(h(rt->left), h(rt->right)) +1;
            l ->height = max(h(l ->left ), h(l->right )) + 1;

            rt->size = 1 + size(rt->left) + size(rt->right); 
            l->size = 1 + size(l->left) + size(l->right);
            return l;
        }

        Node* leftRotate(Node* rt) {
            Node* r = rt->right;
            Node* rl = r->left;
            r->left = rt;
            rt->right = rl;
            rt->height = max(h(rt->left), h(rt->right)) +1;
            r ->height = max(h(r ->left ), h(r->right )) + 1;

            rt->size = 1 + size(rt->left) + size(rt->right);
            r->size = 1 + size(r->left) + size(r->right);

            return r;
        }

        int size(Node* rt) {
            if (rt == nullptr) return 0;
            return rt->size;
        }

    public:
        AVL() : root(nullptr) {}

        void insert( int k) {
            root = inserthelp(root, k);
        }

        int findIndex(int k) {
            Node* current = root;
            int index = 0;

            while (current != nullptr) {
                if (k < current->key) {
                    current = current->left;

                } else if (k > current->key) {
                    index += size(current->left) + 1;
                    current = current->right;
                    
                } else {
                    index += size(current->left) + 1;
                    return index;
                }
            }

            return -1;
        }

};

int main() {
    int n;
    cin >> n;
    
    AVL avl;

    for (int i = 0; i < n; i++) {
        int type, x;
        cin >> type >> x;

        if (type == 1) {
            avl.insert(x);

        } else {
            int index = avl.findIndex(x);

            if (index != -1) {
                cout << index << endl;

            } else {
                cout << "Data tidak ada" << endl;
            }
        }
    }
}
