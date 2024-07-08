struct Node{
    Node *left, *right;
    Student student ;
    int height;
    Node(){
        left = right = NULL;
        height = 1;
    }
    Node(Student student){
        left = right = NULL;
        this->student.id = student.id;
        this->student.name = student.name;
        this->student.department = student.department;
        this->student.gpa = student.gpa;
        height = 1;
    }
};

class AVL{
    private:
        Node* root;
        int nodeHeight(Node* node){
            int leftH = 0 , rightH = 0;
            if(node){
                if(node->left != NULL){
                    leftH = node->left->height ;
                }
                if(node->right != NULL){
                    rightH = node->right->height ;
                }
            }
            return max(leftH,rightH)+1;
        }
        int balanceFactor(Node* node){
            int leftH = 0 , rightH = 0;
            if(node){
                if(node->left != NULL){
                    leftH = node->left->height ;
                }
                if(node->right != NULL){
                    rightH = node->right->height ;
                }
            }
            return leftH-rightH;
        }
        Node* balanceTree(Node* node){
            node->height = nodeHeight(node);

            if(balanceFactor(node) == 2 && balanceFactor(node->left) == 1){
                return LLRotation(node);
            }
            else if(balanceFactor(node) == -2 && balanceFactor(node->right) == -1){
                return RRRotation(node);
            }
            else if(balanceFactor(node) == 2 && balanceFactor(node->left) == -1){
                return LRRotation(node);
            }
            else if(balanceFactor(node) == -2 && balanceFactor(node->right) == 1){
                return RLRotation(node);
            }
            return node;
        }
        Node* LLRotation(Node* node){
            Node* nodeLeft = node->left;
            Node* nodeLeftRight = nodeLeft->right;
            nodeLeft->right = node;
            node->left = nodeLeftRight;

            node->height = nodeHeight(node);
            nodeLeft->height = nodeHeight(nodeLeft);

            if(root == node){
                root = nodeLeft;
            }
            return nodeLeft;
        }
        Node* RRRotation(Node* node){
            Node* nodeRight = node->right;
            Node* nodeRightLeft = nodeRight->left;
            nodeRight->left = node;
            node->right = nodeRightLeft;

            node->height = nodeHeight(node);
            nodeRight->height = nodeHeight(nodeRight);

            if(root == node){
                root = nodeRight;
            }
            return nodeRight;
        }
        Node* LRRotation(Node* node){
            node->left = RRRotation(node->left);
            return LLRotation(node);
        }
        Node* RLRotation(Node* node){
            node->right = LLRotation(node->right);
            return RRRotation(node);
        }
        Node* insertStudent(Node* node , int key , Student student){
            if(node == NULL){
                Node* newNode = new Node(student);
                return newNode;
            }
            if(key <= node->student.id){
                node->left = insertStudent(node->left,key,student);
            }
            else if(key > node->student.id){
                node->right = insertStudent(node->right,key,student);
            }

            node = balanceTree(node);
            return node;
        }
        Node* minNode(Node* node)
        {
            Node* tempNode = node;
            while (tempNode->left != NULL){
                tempNode = tempNode->left;
            }
            return tempNode;
        }
        Node* removeStudent(Node* node , Student student){
            if(node == NULL){
                return node;
            }
            if(student.id > node->student.id){
                node->right = removeStudent(node->right , student);
            }
            else if(student.id < node->student.id){
                node->left = removeStudent(node->left , student);
            }
            else{
                if(node->left == NULL && node->right == NULL){
                    node = NULL;
                }
                else if(node->left != NULL && node->right == NULL){
                    Node* tempNode = node->left;
                    node->student = tempNode->student;
                    delete tempNode;
                }
                else if(node->left == NULL && node->right != NULL){
                    Node* tempNode = node->right;
                    node->student = tempNode->student;
                    delete tempNode;
                }
                else{ // It has 2 children
                    Node* tempNode = minNode(tempNode->right);
                    node->student = tempNode->student;
                    node->right = removeStudent(node->right,tempNode->student);
                }
            }
            // Now we should rebalance the tree because we deleted a student from it
            if(node == NULL){
                return node;
            }
            node->height = 1 + max(nodeHeight(node->left),nodeHeight(node->right));
            node = balanceTree(node);
            return node;
        }
        void inOrderPrint(Node* rootNode){ // left -> root -> right
            if (rootNode == NULL){
                return;
            }
            inOrderPrint(rootNode->left);
            cout << "ID : " <<rootNode->student.id << endl;
            cout << "Name : " <<rootNode->student.name << endl;
            cout << "GPA : " <<rootNode->student.gpa << endl;
            cout << "Department : " <<rootNode->student.department << endl << endl;
            inOrderPrint(rootNode->right);
        }
    public:
        map<string,int> departmentFrequency;
        AVL(){
            root = NULL;
        }
        Student search(int key){
            Student tempStudent ;
            tempStudent.name = "NULL";
            if (root == NULL){
                cout << "There are no students !" << endl;
                return tempStudent;
            }
            queue<Node*> q;
            q.push(root);

            while(!q.empty()){
                if(q.front()->student.id == key){
                    cout << "Student is found" << endl;
                    cout << "ID : " <<q.front()->student.id << endl;
                    cout << "Name : " <<q.front()->student.name << endl;
                    cout << "GPA : " <<q.front()->student.gpa << endl;
                    cout << "Department : " <<q.front()->student.department << endl << endl;
                    return q.front()->student;
                }
                if(q.front()->left != NULL){
                    q.push(q.front()->left);
                }
                if(q.front()->right != NULL){
                    q.push(q.front()->right);
                }
                q.pop();
            }
            return tempStudent;
        }
        void inOrderPrint(){
            inOrderPrint(root);
        }
        void printDepartments(){
            for(auto it : departmentFrequency){
                cout << it.first << " " << it.second << " Students\n";
            }
            cout << endl;
        }
        void insertStudent(const Student &student){
            root = insertStudent(root,student.id,student);
            departmentFrequency[student.department]++;
        }
        void removeStudent(const Student &student){
            root = removeStudent(root,student);
            departmentFrequency[student.department]--;
        }
        Node* returnRoot(){
            return root;
        }
};