#include <iostream>
#include <vector>
#include <stack>

// TODO breadth first vs depth first
// TODO in order, pre order, post order

template<typename T>
class BinaryTree
{
public:
    enum Order {
        PreOrder,
        InOrder,
        PostOrder
    };
    BinaryTree() {}

    void insert(T element) {
        std::cout << "insert " << element << std::endl;
        int index = searchIndex(element);
        std::cout << "Index " << index << std::endl;
        if (index >= m_elements.size())
            m_elements.resize(index + 1, INT_MIN);
        m_elements[index] = element;
    }

    void breadthFirst(std::function<void(T)> callback) {
        for (int i = 0; i != m_elements.size(); ++i) {
            callback(m_elements[i]);
        }
    }

    void depthFirstRec(Order order, std::function<void(T)> callback) {
        depthFirstRecPriv(order, callback, 0);
    }

    void depthFirstIt(Order order, std::function<void(T)> callback) {
        if (order == PreOrder) {
            std::stack<T> stack;
            stack.push(0);
            while (!stack.empty()) {
                int index = stack.top();
                stack.pop();
                callback(m_elements[index]);
                if (index * 2 + 2 < m_elements.size())
                    stack.push(index * 2 + 2);
                if (index * 2 + 1 < m_elements.size())
                    stack.push(index * 2 + 1);
            }
        } else if (order == InOrder) {
            std::vector<bool> visited(m_elements.size(), false);
            std::stack<T> stack;
            stack.push(0);

            while (!stack.empty()) {
                int index = stack.top();
                stack.pop();
                if (visited[index]) {
                    callback(m_elements[index]);
                } else {
                    visited[index] = true;
                    if (index * 2 + 2 < m_elements.size())
                        stack.push(index * 2 + 2);
                    stack.push(index);
                    if (index * 2 + 1 < m_elements.size())
                        stack.push(index * 2 + 1);
                }
            }
        } else {
            std::vector<bool> visited(m_elements.size(), false);
            std::stack<T> stack;
            stack.push(0);

            while (!stack.empty()) {
                int index = stack.top();
                stack.pop();
                if (visited[index]) {
                    callback(m_elements[index]);
                } else {
                    visited[index] = true;
                    stack.push(index);
                    if (index * 2 + 2 < m_elements.size())
                        stack.push(index * 2 + 2);
                    if (index * 2 + 1 < m_elements.size())
                        stack.push(index * 2 + 1);
                }
            }
        }
    }

    std::vector<T> elements() const { return m_elements; }

private:
    void depthFirstRecPriv(Order order, std::function<void(T)> callback, int index) {
        if (index >= m_elements.size())
            return;
        switch(order) {
            case PreOrder:
                callback(m_elements[index]);
                depthFirstRecPriv(order, callback, index * 2 + 1);
                depthFirstRecPriv(order, callback, index * 2 + 2);
                break;
            case InOrder:
                depthFirstRecPriv(order, callback, index * 2 + 1);
                callback(m_elements[index]);
                depthFirstRecPriv(order, callback, index * 2 + 2);
                break;
            case PostOrder:
                depthFirstRecPriv(order, callback, index * 2 + 1);
                depthFirstRecPriv(order, callback, index * 2 + 2);
                callback(m_elements[index]);
                break;
        }
    }
    int searchIndex(T element) {
        int index = 0;
        while (m_elements.size() > index) {
            if (INT_MIN == m_elements[index])
                return index;
            else if (element <= m_elements[index])
                index = index * 2 + 1;
            else
                index = index * 2 + 2;
        }
        return index;
    }
    std::vector<T> m_elements;
};

int main(int argc, char ** argv)
{
    BinaryTree<int> tree;
    tree.insert(4);
    tree.insert(9);
    tree.insert(2);
    tree.insert(1);
    std::vector<int> els = tree.elements();
    std::cout << els.size() << std::endl;
    for (int i = 0; i != els.size(); ++i) {
        std::cout << els[i] << std::endl;
    }

    std::cout << "Preorder" << std::endl;
    tree.depthFirstRec(BinaryTree<int>::PreOrder, [](int value) {
        std::cout << value << std::endl;
    });
    std::cout << "it" << std::endl;
    tree.depthFirstIt(BinaryTree<int>::PreOrder, [](int value) {
        std::cout << value << std::endl;
    });
    std::cout << "InOrder" << std::endl;
    tree.depthFirstRec(BinaryTree<int>::InOrder, [](int value) {
        std::cout << value << std::endl;
    });
    std::cout << "it" << std::endl;
    tree.depthFirstIt(BinaryTree<int>::InOrder, [](int value) {
        std::cout << value << std::endl;
    });
    std::cout << "PostOrder" << std::endl;
    tree.depthFirstRec(BinaryTree<int>::PostOrder, [](int value) {
        std::cout << value << std::endl;
    });
    std::cout << "it" << std::endl;
    tree.depthFirstIt(BinaryTree<int>::PostOrder, [](int value) {
        std::cout << value << std::endl;
    });
    return 0;
}
