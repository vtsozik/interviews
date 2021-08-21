/*
 * Imagine a linked list with not just a next node, but a down node as well.
 * We want to write a function that would "Flatten" that linked list by taking all
 * the downward segments and merging them up between their parent and their parent's next.
 * Input:
 *
 * [1] -> [2] -> [3] -> [8] -> [11]
 *             |      |
 *             |     [9] -> [10]
 *             |
 *            [4] -> [5] -> [6] 
 *                           |
 *                          [7]
 *                          
 * Output:
 *
 * [1] -> [2] -> [3] -> [4] -> [5] -> [6] -> [7] -> [8] -> [9] -> [10]
 *
 */

#include <iostream>
#include <string>
#include <list>
#include <cstring>

using namespace std;
struct Node
{
  Node* next;
  Node* down;
  int value;
};

Node* flatten_recursively(Node* head)
{
    Node* p = head;
    while (p != NULL)
    {
        if (p->down != NULL)
	{
            Node* n = p->next;
	    p->next = flatten_recursively(p->down);
	    p->down = NULL;
	    while (p->next != NULL)
	    {
                p = p->next;
	    }
	    p->next = n;
	} 
	p = p->next;
    }
    return head;
}

Node* flatten(Node* head)
{
    Node *p = head;
    list<Node*> tl;
    while(p != NULL) {
        if (p->down != NULL)
        {
            tl.push_front(p->next);
            p->next = p->down;
            p->down = NULL;
        }
        while(p->next == NULL && !tl.empty())
        {
            p->next = tl.front();
            tl.pop_front();
        }
        p = p->next;
    }
    return head;
}

int main(int argc, char* argv[])
{
  int a[11] = {1,2,3,4,5,6,7,8,9,10,11};
  Node* nodes[11];

  for(int i=0; i<sizeof(a)/sizeof(int); i++)
    {
      Node * node = (Node*)malloc(sizeof(Node));
      memset(node, 0, sizeof(Node)); //clear all bytes;
      nodes[i] = node; //store it
      node->value = a[i];
    }

  //construct an 2d linked list

  /* level 1 */
  nodes[0]->next = nodes[1];
  nodes[1]->next = nodes[2];
  nodes[2]->down = nodes[3];
  nodes[2]->next = nodes[7];
  nodes[7]->down = nodes[8];
  nodes[7]->next = nodes[9];

  /* level 2 */
  nodes[3]->next = nodes[4];
  nodes[4]->next = nodes[5];
  
  /* level 3 */
  nodes[5]->down = nodes[6];
  nodes[9]->next = nodes[10];
  

  Node * head = nodes[0];
   /* print all nodes BEFORE */
  printf("Before: ");
  while(head != NULL)
    {
      printf("%d ", head->value);
      head = head->next;
    }
  printf("\n");
  
  head = nodes[0];
#ifdef FLATTEN_RECURSIVELY
  cout << "Flattening recursively." << endl;
  flatten_recursively(head);
#else
  cout << "Flattening in loop." << endl;
  flatten(head);
#endif

  /* print all nodes AFTER*/
  printf("After: ");
  while(head != NULL)
    {
      printf("%d ", head->value);
      head = head->next;
    }
  printf("\n");
  
}

/* this should print
Before: 1 2 3 8 10 
After: 1 2 3 4 5 6 7 8 9 10 
*/
