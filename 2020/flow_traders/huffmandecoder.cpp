/* 
The structure of the node is
*/
#include <string>
#include <iostream>
using namespace std;

typedef struct node {
    int freq;
    char data;
    node* left;
    node* right;
} node;

void decode_huff(node* root, string s) {
   node *p = root;
   for (size_t i(0); i < s.size(); ++i)
   {
       int c(s[i] - 48);
       if (c == 0)
       {
           p = p->left;
       } 
       else if (c == 1)
       {
           p = p->right;
       }
       else
       {
           cerr << "Corrupted Huffman tree, node edge value outside of [0, 1]: " << c << endl;
	   exit(-1);
       }
       if (p->left == NULL && p->right == NULL)
       {
           cout << p->data;
	   p = root;
       }
   } 
   cout << endl;
}

int main()
{
    node n5{1, 'C', NULL, NULL};
    node n4{1, 'B', NULL, NULL};
    node n3{3, 'A', NULL, NULL};
    node n2{3, '\0', &n4, &n5};
    node n1{5, '\0', &n2, &n3};
    decode_huff(&n1, "1001011");
}
