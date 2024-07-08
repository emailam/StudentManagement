#ifndef X_BST_H
#define X_BST_H

using namespace std;
class BST{
private:
    struct Node{
        Student data;
        Node* left;
        Node* right;
    };
    Node *root;
    map<string,int>department;
    void clr(Node *p){
        if(p== nullptr){
            return;
        }
        else{
            clr(p->left);
            clr(p->right);
            delete p;
        }
    }
    Node* findMin(Node *p){
        if(p== nullptr){
            return nullptr;
        }
        else if(p->left== nullptr){
            return p;
        }
        else{
            return findMin(p->left);
        }
    }
    void inorder(Node* rootNode){ // left -> root -> right
            if (rootNode == NULL){
                return;
            }
            inorder(rootNode->left);
            cout << "ID : " <<rootNode->data.id << endl;
            cout << "Name : " <<rootNode->data.name << endl;
            cout << "GPA : " <<rootNode->data.gpa << endl;
            cout << "Department : " <<rootNode->data.department << endl << endl;
            inorder(rootNode->right);
        }
    void dep(map<string,int>x){
        for(auto it : x){
            cout << it.first << " " << it.second << " Students\n";
        }
        cout << endl;
    }
    Node* find(Node *p,int id){
        if(p== nullptr){
            return nullptr;
        }
        else if(id < p->data.id){
            return find(p->left,id);
        }
        else if(id > p->data.id){
            return find(p->right,id);
        }
        else{
            return p;
        }
    }
    Node* insert(Node* p,const int& id,const Student& x){
        if(p==nullptr){
            p=new Node;
            p->data=x;
            p->left=p->right= nullptr;
            department[p->data.department]++;
        }
        else if(id>p->data.id){
            p->right=insert(p->right,id,x);
        }
        else if(id<p->data.id){
            p->left=insert(p->left,id,x);
        }
        return p;
    }
    Node* remove(Node* p,int id){
        Node* tmp;
        if(p== nullptr){
            return nullptr;
        }
        else if(id<p->data.id){
            p->left=remove(p->left,id);
        }
        else if(id>p->data.id){
            p->right=remove(p->right,id);
        }
        else if(p->left!= nullptr&&p->right!=nullptr){
            tmp=findMin(p->right);
            p->data=tmp->data;
            p->right=remove(p->right,tmp->data.id);
        }
        else{
            tmp=p;
            if(p->left== nullptr){
                p=p->right;
            }
            else if(p->right== nullptr){
                p=p->left;
            }
            delete tmp;
        }
        return p;
    }
public:
    BST(){
        root=nullptr;
    }
    ~BST(){
        clr(root);
        department.clear();
    }
    void print(){
        inorder(root);
        cout << "\n";
        dep(department);
    }
    Student search(int id){
        Node* tmp=find(root,id);
        Student tempStudent;
        tempStudent.name = "NULL";
        if(tmp!=nullptr){
            cout<<"ID :"<<tmp->data.id<<endl;
            cout<<"Name :"<<tmp->data.name<<endl;
            cout<<"Department :"<<tmp->data.department<<endl;
            cout<<"GPA :"<<tmp->data.gpa<<endl;
            return tmp->data;
        }
        cout<<"Student Not Found!"<<endl;
        return tempStudent;
    }
    void removeStudent(const Student& x){
        root=remove(root,x.id);
    }
    void insertStudent(const Student& x){
        root=insert(root,x.id,x);
    }
    Node* returnRoot(){
        return root;
    }
};

#endif //X_BST_H