#include <iostream>
#include <string>
#include <queue>
//using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        struct Node
        {
            T value;
            Node *left;
            Node *right;
            explicit Node(T val = 0, Node *l = nullptr, Node *r = nullptr) : value(val), left(l), right(r){};

            friend std::ostream &operator<<(std::ostream &out, const Node &n) { return out; }
        };

        Node *root;

         void copy(Node **newer, Node *other)
        {
            if (other == nullptr)
            {
                return;
            }
            *newer = new Node(other->value);
            copy(&((*newer)->left), other->left);
            copy(&((*newer)->right), other->right);
        }


        void delete_tree(Node** n){
            if(*n == nullptr){
                return;
            }
            delete_tree(&((*n)->left));
            delete_tree(&((*n)->right));
            delete *n;
        }

    public:
        BinaryTree<T>(){
            root=nullptr;
        }
        BinaryTree<T>(BinaryTree<T> &other){
            if (other.root == nullptr)
            {
                root = nullptr;
            }
            else{
                copy(&root, other.root);
            }
        }

        BinaryTree(BinaryTree<T> &&other) noexcept
        {
            this->root = other.root;
            other.root = nullptr;
        }

        BinaryTree &operator=(BinaryTree<T> &&bt) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = bt.root;
            bt.root = nullptr;
            return *this;
        }
        
        BinaryTree<T> &operator=(const BinaryTree<T> &other)
        {
            if (this != &other)
            {
                copy(&root, other.root);
            }
            return *this;
        }

        class pre_iterator
        {
        private:
            Node *current;
            std::queue<Node*> q;
            void preorder(Node *n)
            {
                if (n == nullptr){
                    return;
                }
                this->q.push(n);
                preorder(n->left);
                preorder(n->right);
            }

        public:
            explicit pre_iterator(Node *pTree = nullptr) : current(pTree)
            {
                if (current != nullptr)
                {
                    preorder(current);
                    current=q.front();
                }
            }
            pre_iterator &operator++()
            {
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return *this;
            }

            pre_iterator operator++(int)
            {
                pre_iterator temp = *this;
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return temp;
            }

            bool operator==(const pre_iterator &other) const
            {
                return current==other.current;
            }

            bool operator!=(const pre_iterator &other) const
            {
                return current!=other.current;
            }

            T &operator*() const
            {
                return this->current->value;
            }

            T *operator->() const
            {
                return &(this->current->value);
            }

            Node* get_current(){
                return current;
            }

            friend std::ostream &operator<<(std::ostream &out, const pre_iterator &num)
            {
                return out;
            }
        };
        class in_iterator
        {
        private:
            Node *current;
            std::queue<Node*> q;
            void inorder(Node *n)
            {
                if (n == nullptr){
                    return;
                }
                inorder(n->left);
                this->q.push(n);
                inorder(n->right);
            }

        public:
            explicit in_iterator(Node *pTree = nullptr) : current(pTree)
            {
                if (current != nullptr)
                {
                    inorder(current);
                    current=q.front();
                }
            }
            in_iterator &operator++()
            {
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return *this;
            }
            in_iterator operator++(int)
            {
                in_iterator temp = *this;
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return temp;
            }
            bool operator==(const in_iterator &other) const
            {
                return current==other.current;
            }
            bool operator!=(const in_iterator &other) const
            {
                return current!=other.current;
            }
            T &operator*() const
            {
                return this->current->value;
            }

            T *operator->() const
            {
                return &(this->current->value);
            }
            Node* get_current(){
                return current;
            }
            friend std::ostream &operator<<(std::ostream &out, const in_iterator &num)
            {
                return out;
            }
        };
        class post_iterator
        {
        private:
            Node *current;
            std::queue<Node*> q;
            void postorder(Node *n)
            {
                if (n == nullptr){
                    return;
                }
                postorder(n->left);
                postorder(n->right);
                this->q.push(n);
            }

        public:
            explicit post_iterator(Node *pTree = nullptr) : current(pTree)
            {
                if (current != nullptr)
                {
                    postorder(current);
                    current=q.front();
                }
            }
            post_iterator &operator++()
            {
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return *this;
            }
            post_iterator operator++(int)
            {
                post_iterator temp = *this;
                q.pop();
                if (q.empty())
                {
                    current = nullptr;
                }
                else
                {
                    current=q.front();
                }
                return temp;
            }
            bool operator==(const post_iterator &other) const
            {
                return current==other.current;
            }
            bool operator!=(const post_iterator &other) const
            {
                return current!=other.current;
            }
            T &operator*() const
            {
                return this->current->value;
            }

            T *operator->() const
            {
                return &(this->current->value);
            }

            Node* get_current(){
                return current;
            }

            friend std::ostream &operator<<(std::ostream &out, const post_iterator &num)
            {
                return out;
            }
        };
        BinaryTree<T>::in_iterator begin()
        {
            return begin_inorder();
        }
        BinaryTree<T>::in_iterator end()
        {
            return end_inorder();
        }
        BinaryTree<T>::pre_iterator begin_preorder()
        {
            return pre_iterator(root);
        }
        BinaryTree<T>::pre_iterator end_preorder()
        {
            return pre_iterator();
        }
        BinaryTree<T>::in_iterator begin_inorder()
        {
            return in_iterator(root);
        }
        BinaryTree<T>::in_iterator end_inorder()
        {
            return in_iterator();
        }
        BinaryTree<T>::post_iterator begin_postorder()
        {
            return post_iterator(root);
        }
        BinaryTree<T>::post_iterator end_postorder()
        {
            return post_iterator();
        }

        Node* get_root(){
            return this->root;
        }

        BinaryTree<T> &add_root(T root)
        {
            if (this->root == nullptr){
                this->root=new Node(root);
            }
            else {
                this->root->value=root;
            }
            return *this;
        }

        BinaryTree<T> &add_left(T father, T l)
        {
            if (root == nullptr){
                throw std::invalid_argument("the tree is null");
            }
            in_iterator temp;
            for (temp = this->begin(); temp != this->end(); ++temp)
            {
                if(*temp == father){
                    if(temp.get_current()->left == nullptr){
                        temp.get_current()->left=new Node(l);
                    }
                    else {
                        temp.get_current()->left->value=l;
                    }
                    return *this;
                }
            }
            throw std::invalid_argument("the father isn't there");
        }
        BinaryTree<T> &add_right(T father, T r)
        {
            if (root == nullptr){
                throw std::invalid_argument("the tree is null");
            }
            in_iterator temp;
            for (temp = this->begin(); temp != this->end(); ++temp)
            {
                if(*temp == father){
                    if(temp.get_current()->right == nullptr){
                        temp.get_current()->right=new Node(r);
                    }
                    else {
                        temp.get_current()->right->value=r;
                    }
                    return *this;
                }
            }
            throw std::invalid_argument("the father isn't there");
        }

        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &num)
        {
            return out;
        }
        ~BinaryTree<T>(){
            if(this->root != nullptr){
                return;
            }
            delete_tree(&this->root);
        }
    };
}