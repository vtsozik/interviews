#include <stack>
#include <iostream>
using namespace std;

class MyQueue {
  
    public:
        stack<int> stack_newest_on_top, stack_oldest_on_top;   
        void push(int x) {
            stack_newest_on_top.push(x);
        }

        void pop() {
            front();
            stack_oldest_on_top.pop();
        }

        int front() {
            if (stack_oldest_on_top.empty())
            {
                while (!stack_newest_on_top.empty())
                {
                    stack_oldest_on_top.push(stack_newest_on_top.top());
                    stack_newest_on_top.pop();
                }
            }
            return stack_oldest_on_top.top();
        }
};

int main()
{
    MyQueue q;
    for (size_t i(1); i <= 10; ++i)
    {
         q.push(i);
    }
    cout << "Result:";
    for (size_t i(1); i <= 10; ++i)
    {
       cout << ' ' << q.front(); 
       q.pop();
    }
    cout << endl;
    return 0;
}
