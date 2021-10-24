#include <iostream>

using namespace std;

// CÂY AVL
struct Node{

   int key;
   int bal; // 0: can bang // -1: lech trai // 1:lech phai
   Node *left;
   Node *right;
   Node *parent;
};

struct Tree{
   Node *root;
   int NumberNode;
   int NumeberLeaf;
   int Hight;
};

Node* createNode(int k);
void InitTree(Tree &T);
int Put(Node *&root, Node* x, Node* parent);
int PutNodeTree(Tree &tree, int x);
void Rotate_LL(Node *&T);
void Rotate_LR(Node *&T);
void Rotate_RR(Node *&T);
void Rotate_RL(Node *&T);

Node* createNode(int k){
   Node *n=new Node;
   n->key=k;
   n->bal=0;
   n->left=NULL;
   n->right=NULL;
   n->parent=NULL;
   return n;
}

void InitTree(Tree &T){
   T.root=NULL;
   T.NumberNode=0;
   T.NumeberLeaf=0;
   T.Hight=0;
}

int Put(Node* &root, Node * x, Node* parent)
{
    // return 0 neu khong lm thay doi chieu cao
    // return 1 chieu cao thay doi
    // return -1 khong chen
    int res=0;
	if(root!=NULL)
	{
		if(root->key == x->key) return -1;
		if(root->key>x->key){

                res=Put(root->left, x,root);    //chen vao trai
                if(res<1) return res;  // khong lm thay doi chieu cao

                switch(root->bal){
                    case -1:  
                        if(root->left->bal==-1) {  // LL
                            Rotate_LL(root);
                        }
                        else {
                            if(root->left->bal==1) { // LR
                                Rotate_LR(root);
                            }
                            // return 0;
                        }
                        return 0;
                    case 0:  
                        root->bal=-1; 
                        return 1;
                    case 1:  
                        root->bal=0 ;  
                        return 0;
                }
              }
		else {
                res=Put(root->right, x,root);
                if(res<1) return res;  // khong lm thay doi chieu cao

                switch(root->bal){
                    case -1:  
                        root->bal=0; 
                        return 0;
                    case 0:   
                        root->bal=1;
                        return 1;
                    case 1:   
                    {
                        if(root->right->bal==1) {  // RR
                            Rotate_RR(root);
                        } else {
                            if(root->right->bal==-1) {  // RL
                                Rotate_RL(root);
                            }
                        }
                        return 0;
                    }       
	         }
        }
    }
	//Node *tmp = createNode(x);
	x->parent=parent;
	root=x;
	return 1;
}

int PutNodeTree(Tree &tree, int x){ //insert node into tree
    // Node *p=tree.root;
    Node *X = createNode(x);
    if(Put(tree.root,X,NULL)!=-1){
        if(tree.root==NULL) {
            tree.root=X;
        } 
        tree.NumberNode++;
    }
}

bool search(Node *&root,int x,int &count)
{    
    if(root!=NULL){
        if(root->key==x) {
            count+=1;
            return true;  //Tim dc nut p co khoa x
        }
        if(root->key<x) {
            count+=1;
            return search(root->right,x,count); //Tim tiep o ben trai
        }  
        if(root->key>x) {
            count+=1;
            return search(root->left,x,count);
        }
    }
    return false;
}

void Rotate_LL (Node *&T)
{	
    Node *T1 = T->left;
	T->left = T1->right; T1->right=T;
	switch(T1->bal)
	{
		case 0:	 
                T->bal =0;
                T1->bal=1;
                break;
		case -1: 
                T->bal=0;
                T1->bal=0;
                break;
	}
	// T1->bal=0;
	T=T1;
}

void Rotate_LR(Node *&T)
{
    Node *T1=T->left, *T2=T1->right;
 	T->left=T2->right; T2->right=T;
 	T1->right= T2->left; T2->left = T1;
	switch(T2->bal)
	{	
	    case -1: 	
                // T->bal = 0; 
                T->bal = 1;
				T1->bal= 0;
                break;
 		case 0:     
                T->bal = 0; 
 				T1->bal= 0; 
                break;
		case 1: 
                T->bal = 0; 
				// T1->bal= 0; 
				T1->bal=-1;
                break;
	}	
    T2->bal =0; 
    T=T2;
    //cout<<T->key;
}

void Rotate_RR(Node *&T){
    Node *T1 = T->right;
	T->right = T1->left; 
    T1->left=T;
	switch(T1->bal)
	{
		case 1:	 
                T->bal =0;
                T1->bal=0;
                break;
		case 0: 
                T->bal=0;
                T1->bal=-1;
				break;
	}
	T=T1;
}

void Rotate_RL(Node *&T){
    
    Node *T1= T->right, *T2=T1->left;
	T->right = T2->left; T2->left = T;
	T1->left = T2->right; T2->right = T1;
	switch(T2-> bal)
	{	
        case 1:	
            T-> bal = -1;
			T1-> bal = 0; 
            break;
		case 0:	
            T-> bal = 0; 
			T1-> bal = 0; 
            break;
		case -1:	
            T-> bal = 0; 
			T1-> bal = 1; 
            break;
	}
	T2-> bal =0; 
    T=T2;

}

void printTree(Node *T){
	if (T != NULL){
		printTree(T->left);
		cout << T->key << " ";
		if (T->left != NULL) cout <<T->left->key << " ";
		if (T->right != NULL) cout << T->right->key << " ";
		cout << endl;
		printTree(T->right);
	}
}

// CÂY NHỊ PHÂN
struct Node_NP{
   int key;
   Node *left;
   Node *right;
   Node *parent;
};

struct Tree_NP{
    Node * root;
    int NumberNode;
};

Node* CreateNode_NP(int k){
   Node *n=new Node;
   n->key=k;
   n->left=NULL;
   n->right=NULL;
   n->parent=NULL;
   return n;
}

void InitTree_NP(Tree &T){
   T.root=NULL;
   T.NumberNode=0;
}
bool Put_NP(Node*n,Tree &T){
      Node *p=T.root;
      if(T.root==NULL){
        T.root=n;
        return true;
     }
      while((n->key>p->key&&p->right!=NULL)||(n->key<p->key&&p->left!=NULL)){
        if(n->key==p->key)
            return false;
        else{
        if(n->key>p->key)
            p=p->right;
        else
            p=p->left;}
     }

      if(n->key>p->key)
        p->right=n;
      else
        p->left=n;
       n->parent=p;
      return true;

}
int PutDQ_NP(Node *root, int x)
{
	if(root!=NULL)
	{
		if(root->key == x)return 0;
		if(root->key>x)return PutDQ_NP(root->left, x);
		else return PutDQ_NP(root->right, x);
	}
	root = CreateNode_NP(x);
	return 1;
}

// 

void print(Node *p)
{
    if(p!=NULL)
    {
        print(p->left);
        print(p->right);
        cout<<p->key<<"\n";
    }
}

int main()
{
    Tree AVL;
    InitTree(AVL);

    // int n;
    // cout<<"Nhap n : ";
    // cin>>n;
    // for(int i=0;i<n;i++){
    //     int k;
    //     cout<<"Nhap so thu "<<i+1<<" : ";
    //     cin>>k;
    //     PutNodeTree(AVL,k);
    // }
    //1  3  5  7  9  12  15  17  21  23  25  27

    // a
    // cout<<"<a>"<<endl;

    // PutNodeTree(AVL,1);
    // PutNodeTree(AVL,3);
    // PutNodeTree(AVL,5);
    // PutNodeTree(AVL,7);
    // PutNodeTree(AVL,9);
    // PutNodeTree(AVL,12);
    // PutNodeTree(AVL,15);
    // PutNodeTree(AVL,17);
    // PutNodeTree(AVL,21);
    // PutNodeTree(AVL,23);
    // PutNodeTree(AVL,25);
    // PutNodeTree(AVL,27);

    // print(AVL.root);
    // cout<<"-----------------------"<<endl;

    // int count=0;
    // search(AVL.root,21,count);
    // cout<<count;
    // cout<<endl;

    cout<<"-----------------------"<<endl;
    // b
    cout<<"<b>"<<endl;
    Tree_NP NP;
    InitTree_NP(NP);
    Put_NP(CreateNode_NP(1),NP);
    Put_NP(CreateNode_NP(3),NP);
    Put_NP(CreateNode_NP(5),NP);
    Put_NP(CreateNode_NP(7),NP);
    Put_NP(CreateNode_NP(9),NP);
    Put_NP(CreateNode_NP(12),NP);
    Put_NP(CreateNode_NP(15),NP);
    Put_NP(CreateNode_NP(17),NP);
    Put_NP(CreateNode_NP(21),NP);
    Put_NP(CreateNode_NP(23),NP);
    Put_NP(CreateNode_NP(25),NP);
    Put_NP(CreateNode_NP(27),NP);
    print(NP.root);

    // if(search(AVL.root,2)) cout<<"Tim thay"<<endl;
    // else cout<<"Khong tim thay"<<endl;
    
    return 0;
}
