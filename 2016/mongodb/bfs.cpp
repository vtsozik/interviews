void BreadthFirstTravseral(struct node* root)
{
    queue<node*> q;

    if (!root) {
        return;
    }
    for (q.push(root); !q.empty(); q.pop()) {
        const node * const temp_node = q.front();
        cout<<temp_node->data << " ";

        if (temp_node->left) {
            q.push(temp_node->left);
        }
        if (temp_node->right) {
            q.push(temp_node->right);
        }
    }
}
