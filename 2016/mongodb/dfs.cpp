#include <stack> 
struct BTNode
{

    BTNode(int d)
    {
        data = d;
    }

    int data;
    BTNode* right;
    BTNode* left;
}; 

    void DFS(BTNode* root)
    {
        BTNode* tmp = root;
        std::stack<BTNode*> stck;
        stck.push(tmp);

        while(stck.empty() == false)
        {
            while (tmp->left != 0)
            {
                tmp = tmp->left;
                stck.push(tmp);
            }
            while(stck.empty() == false)
            {
                tmp = stck.top();
                stck.pop();
                std::cout << tmp->data;
                if(tmp->right != 0)
                {
                    tmp = tmp->right;
                    stck.push(tmp);
                    break;
                }
            }
        }

 void CreateTreeExample(BTNode* root)
    {
        BTNode* b1= new BTNode(1);
        BTNode* b2= new BTNode(2);
        BTNode* b3= new BTNode(3);
        BTNode* b4= new BTNode(4);
        BTNode* b5= new BTNode(5);
        BTNode* b6= new BTNode(6);
        BTNode* b7= new BTNode(7);
        BTNode* b8= new BTNode(8);
        BTNode* b9= new BTNode(9);

        b2->left = b1;
        b2->right = b4;
        b6->left = b2;
        b4->left = b3;
        b4->right = b5;
        b7->left = b6;
        b7->right = b8;
        b8->right = b9;
        root = b7;
    } 

