/*
 * You are given a binary tree. Each node contains extra pointer to
 * right sibling on the same level (m_next). Initially m_next = NULL.
 * Create an algorithm that traverse this tree and links up right
 * siblings. Also write a test case code to demonstrate the verify
 * your solution.
 */

#include <iostream>
#include <list>
using namespace std;

struct Node
{
 Node() : m_left(NULL), m_right(NULL), m_next(NULL), m_val(0) {}
 Node *m_left;
 Node *m_right;
 Node *m_next;
 int m_val;
};

void verifySiblings(Node* n)
{
    if (n)
    {
        cout << "Level: " << n->m_val << " has ";
	int cnt(1);
	for (Node* p = n->m_next; p; p = p->m_next)
	{
           ++cnt;
	}
	cout << cnt << ((cnt != 1) ? " nodes." : " node.") << endl;
        verifySiblings(n->m_left);
    }
}

void linkrightsiblings(Node* root)
{
    list<Node*> l(1, root);
    while (!l.empty())
    {
        size_t s(l.size());
	for (size_t i(0); i < s; ++i)
	{
            Node *n = l.front();
	    l.pop_front(); 
	    if (!n)
	    {
                continue;
	    }
	    if (i + 1 < s)
	    {
                n->m_next = l.front();
	    }
	    l.push_back(n->m_left);
	    l.push_back(n->m_right);
	}
    }
}

void deleteTree(Node* n)
{
    if (n)
    {
        deleteTree(n->m_left);
        deleteTree(n->m_right);
	delete n;
    }
}

Node* makeBinaryTree(int level, int depth)
{
    Node* n(NULL);
    if (level <= depth)
    {
        n = new Node();
        n->m_val = level++;
        n->m_left = makeBinaryTree(level, depth);
        n->m_right = makeBinaryTree(level, depth);
    }
    return n;
}
int main()
{
    Node* root(makeBinaryTree(0, 4));
    linkrightsiblings(root);
    verifySiblings(root);
    deleteTree(root);
    return 0;
}
