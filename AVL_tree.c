#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tree{
	int data;
	int weight;
	struct tree *left;
	struct tree *right;
};
// print functions
void inorder(struct tree *root){
	if(root == NULL) return;
	inorder(root->left);
	printf("%d w:%d\n",root->data,root->weight);
	inorder(root->right);
}
void preorder(struct tree *root){
	if(root == NULL) return;
	printf("%d\n",root->data);
	preorder(root->left);
	preorder(root->right);
}
void postorder(struct tree *root){
	if(root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d\n",root->data);
}
int height(struct tree *root){
	if(root == NULL) return 0;
	else{
		int l = height(root->left);
		int r = height(root->right);
		if(l>r) return l+1;
		else return r+1;
	}
}

void measure(struct tree *root){
	if(root == NULL) return;
	root->weight = height(root->left) - height(root->right);
	measure(root->left);
	measure(root->right);
}
struct tree *LL(struct tree *root){
	struct tree *temp = root;
	struct tree *temp2 = root->left->right;
	root = root->left;
	temp->left = NULL;
	temp->left = temp2;
	root->right = temp;
	return root;
}
struct tree *RR(struct tree *root){
	struct tree *temp = root;
	struct tree *temp2 = root->right->left;
	root = root->right;
	temp->right = NULL;
	temp->right = temp2;
	root->left = temp;
	return root;
}
struct tree *LR(struct tree *root){
	struct tree *temp = root;
	struct tree *temp2 = root->left;
	root->left = root->left->right;
	root->left->left = temp2;
	temp2->right = NULL;
	root = LL(root);
	root->right = temp;
	return root;
}
struct tree *RL(struct tree *root){
	struct tree *temp = root;
	struct tree *temp2 = root->right;
	root->right = root->right->left;
	root->right->right = temp2;
	temp2->left = NULL;
	root = RR(root);
	root->left = temp;
	return root;
}
struct tree * balance(struct tree *root,struct tree *proot,struct tree *orginal){
	if(root == NULL) return NULL;
	measure(orginal);
	root->right = balance(root->right,root,orginal);
	root->left = balance(root->left,root,orginal);
	if(root->weight > 1 && root->left->right != NULL && proot->weight <-1){ 
		//printf("2-%d\n",root->data);
		root = LR(root);
		measure(orginal);
		//return root;
	}
	else if(root->weight > 1 && root->left->left != NULL){ 
		//printf("1-%d\n",root->data);
		root = LL(root);
		measure(orginal);
		//return root;
	}
	else if(root->weight < -1 && root->right->left != NULL && proot->weight >1){ 
		root = RL(root);
		measure(orginal);
		//return root;
	}
	else if(root->weight < -1 && root->right->right != NULL){ 
		//printf("3-%d\n",root->data);
		root = RR(root);
		measure(orginal);
		//return root;
	}
	return root;
}

struct tree *insert(struct tree *root,int data){
	struct tree* newnode = (struct tree*)malloc(sizeof(struct tree));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = data;
	newnode->weight = 0;
	if(root == NULL) return newnode;
	else{
		struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
		cpy = root;
		while(1){
			if(cpy->left == NULL && data < cpy->data){ 
				cpy->left = newnode; 
				measure(root);
				root = balance(root,root,root);
				return root;
			}
			else if(cpy->right == NULL && data >= cpy->data){ 
				cpy->right = newnode; 
				measure(root);
				root = balance(root,root,root);
				return root;
			}
			else if(data < cpy->data) cpy = cpy->left;
			else cpy = cpy->right;
		}
	}
}

/*void delete(struct tree *root,struct tree *pre,struct tree *orignal,int d,int data){
	struct tree* tmp = root;
	if(root == NULL) return;
	if(root->data == data){
		if(root->left == NULL && root->right == NULL){
			if(d) pre->right = NULL;
			else pre->left = NULL;
		}
		else if(root->left != NULL && root->right == NULL){
			root->data = root->left->data;
			root->left = NULL;
		}
		else if(root->left == NULL && root->right != NULL){
			root->data = root->right->data;
			root->right = NULL;
		}
		else if(root->left != NULL && root->right != NULL){
			struct tree* cpy = (struct tree*)malloc(sizeof(struct tree));
			cpy = findpredecessor(root->left);
			if(cpy->right !=NULL){
				root->data= cpy->right->data;
				 cpy->right->data = -1;
				delete(tmp,tmp,orignal,0,cpy->right->data);
			}
			else{
			 root->data= cpy->data;
			cpy->data = -1;
			measure(orignal);
			delete(tmp,tmp,orignal,0,cpy->data);
			orignal = balance(orignal,orignal);
			preorder(orignal);
			printf("---\n");
			}
		}
		return;
	}
	delete(root->left,root,orignal,0,data);
	delete(root->right,root,orignal,1,data);

}*/

struct tree *search(struct tree *root,int data){
	if(root == NULL || root->data == data) return root;
	search(root->left,data);
	search(root->right,data);
}
void print(struct tree *root,struct tree *proot,int level,int cur,int d,char *str){
	char *tmp = (char*)malloc(sizeof(char)*1000);
	if(root == NULL) return;
	if(cur == level){
	sprintf(tmp,"%d (%d %c) ",root->data,proot->data,d);
	strcat(str,tmp);
	}
	print(root->left,root,level,cur+1,'L',str);
	print(root->right,root,level,cur+1,'R',str);
	return;
}
void print_level(struct tree *root,int max){	
	printf("%d\n",root->data);
	for(int i=1;i<max;i++){
		char *str = (char*)malloc(sizeof(char)*1000);
		print(root,root,i,0,'L',str);
		while(*(str+1) != '\0') {printf("%c",(*str)); str++;}
		printf("\n");
	}
}

int main()
{
	struct tree *root = (struct tree *)malloc(sizeof(struct tree));
	root = NULL;
	int id;
	do{
		scanf("%d",&id);
		if(id!= -1)root = insert(root,id);	
	}while(id != -1);
	inorder(root);
	int h = height(root);
	printf("\n");
	print_level(root,h);
    return 0;
}

