#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	char contest_name[26];
	char contest_name2[26];
	int contest_age;
	int contest_score;
	char contest_gender[21];
	char contest_song[21];
	int height;
	Node* left,* right;
};
int contest_score;
int ful (int a, int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}
int getHeg(Node *root){
	if(root==NULL){ 
		return 0;
	}
	return root->height;
}
int getBF(Node *root){
	if(root==NULL){
		return 0;
	}
	return getHeg(root->left) - getHeg(root->right);
}
void updateHeg(Node *root){
	root->height = ful(getHeg(root->left), getHeg(root->right) + 1);
}
Node* rotateRight(Node *root){
	Node *x = root->left;
	Node *B = x->right;
	x->right = root;
	root->left = B;
	updateHeg(root);
	updateHeg(x);
	return x;
}
Node* rotateLeft(Node *root){
	Node *x = root->right;
	Node *B = x->left;
	x->left = root;
	root->right = B;
	updateHeg(root);
	updateHeg(x);
	return x;
}
Node *rebalance(Node *root){
	int bf = getBF(root);
	if(bf < -1){
		if(getBF(root->right)>0){
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}else if(bf > 1){
		if(getBF(root->left)<0){
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	return root;
}
Node *predecessor(Node *root){
	root = root->left;
	while(root->right){
		root=root->right;
	}
	return root;
}
Node *createNode(char contest_name[26],int contest_age, char contest_gender[21], char contest_song[21]){
	Node* newNode = (Node*) malloc(sizeof(Node));
	strcpy(newNode->contest_name,contest_name);
	newNode->contest_age=contest_age;
	strcpy(newNode->contest_gender,contest_gender);
	strcpy(newNode->contest_song,contest_song);
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Node* insert(Node *root,char contest_name[26], int contest_age, char contest_gender[21], char contest_song[21]){
	if(root  == NULL){
		return createNode(contest_name,contest_age, contest_gender, contest_song);
	}
	if(strcmp(contest_name,root->contest_name) < 0){
		root->left = insert(root->left,contest_name, contest_age, contest_gender, contest_song);
	}else if(strcmp(contest_name,root->contest_name) > 0){
		root->right = insert(root->right,contest_name, contest_age, contest_gender, contest_song);
	}
	updateHeg(root);
	return rebalance (root);
}
Node *searchCon(Node *root, char contest_name[26]){
	if(root == NULL){
		return NULL;
	}
	if(strcmp(contest_name, root->contest_name) < 0){
		return searchCon(root->left,contest_name);
	}else if(strcmp(contest_name, root->contest_name) > 0){
		return searchCon(root->right,contest_name);
	}else{
		return root;
	}
}
void inorder_traversal(Node* root) {
	if (root == NULL) return;
	inorder_traversal(root->left);
	printf("| %s \t| %s\t| %d | %s\n",root->contest_name,root->contest_gender,root->contest_age,root->contest_song);
	inorder_traversal(root->right);
}
void preorder_traversal(Node* root) {
	if (root == NULL) return;
	printf("| %s \t| %s\t| %d | %s\n",root->contest_name,root->contest_gender,root->contest_age,root->contest_song);
	preorder_traversal(root->left);
	preorder_traversal(root->right);
}
void postorder_traversal(Node* root) {
	if (root == NULL) return;
	postorder_traversal(root->left);
	postorder_traversal(root->right);
	printf("| %s \t| %s\t| %d | %s|\n",root->contest_name,root->contest_gender,root->contest_age,root->contest_song);
}
void viewContest(Node* root){
	if(root==NULL){
		printf("There is no contestant\nPress Any Key To Continue\n");
		getchar();
		return;
	}
	char order[5];
	do{
		printf("Choose order [Pre | In | Post]: ");
		scanf("%s", order);
		getchar();
		if(strcmp(order,"Pre")==0 || strcmp(order,"In")==0 || strcmp(order,"Post")==0){
			break;
		}
	}while(true);
	printf("| Name \t\t| Gender\t| Age | Song\n");
	if(strcmp(order,"Pre")==0){
		preorder_traversal(root);
	}
	if(strcmp(order,"In")==0){
		inorder_traversal(root);
	}
	if(strcmp(order,"Post")==0){
		postorder_traversal(root);
	}
	getchar();
}
Node *regisContest(Node *root){
	char contest_name[26];
	do{
		printf("Input contestant name: ");
		scanf("%[^\n]", contest_name);
		getchar();
		int alph = 0, space = 0;
		for(int i=0;contest_name[i]!=NULL;i++){
			if(contest_name[i]>='0' && contest_name[i]<='9')
				alph++;
		}
		for(int i=0;contest_name[i]!=NULL;i++){
			if(contest_name[i]>=' ')
				space++;
		}
		if(strlen(contest_name)>=6 && strlen(contest_name)<=20 && alph == 0 && space != 0 && contest_name[0] <= 97){
			break;
		}
		alph = 0, space = 0;
	}while(true);
	char contest_gender[8];
	do{
		printf("Input Gender [male | female]: ");
		scanf("%[^\n]", contest_gender);
		getchar();
		if(strcmp(contest_gender, "female")==0 || strcmp(contest_gender, "male")==0){
			break;
		}
	}while(true);
	int contest_age;
	do{
		printf("Input Age [6 - 59]: ");
		scanf("%d", &contest_age);
		getchar();
		if(contest_age>=6 && contest_age<=59){
			break;
		}
	}while(true);
	char contest_song[21];
	int count = 0;
	do{
		printf("Input Song: ");
		scanf("%[^\n]", contest_song);
		getchar();
		if(strlen(contest_song)>=1){
			break;
		}
	}while(true);
	root = insert (root,contest_name, contest_age, contest_gender,contest_song);
	printf("Insert Success\nPress Any Key To Continue\n");
	getchar();
	return root;
}
Node *deletecont(Node* root, char contest_name[26]){
	if(root ==NULL){
		return NULL;
	}
	if(strcmp(contest_name,root->contest_name) < 0){
		root->left = deletecont(root->left, contest_name);
	}else if(strcmp(contest_name,root->contest_name) > 0){
		root->right = deletecont(root->right, contest_name);
	}else{
		if(root->left == NULL && root->right == NULL){
			root = NULL;
			free(root);
			return NULL;
		}else if(root->left == NULL){
			Node* child = root->right;
			root = NULL;
			free(root);
			return child;
		}else if(root->right == NULL){
			Node* child = root->left;
			root = NULL;
			free(root);
			return child;
		}else{
			Node *pre = predecessor(root);
			strcpy(root->contest_name,pre->contest_name);
			root->contest_age=pre->contest_age;
			strcpy(root->contest_gender,pre->contest_gender);
			strcpy(root->contest_song,pre->contest_song);
			root->left = deletecont(root->left, pre->contest_name);
		}
	}
	updateHeg(root);
	return rebalance(root);
}

Node *callContest(Node *root){
	if(root  == NULL){
		printf("There is no contestant");
		getchar();
		return NULL;
	}
	char contest_name[26];
	Node *found = NULL;
	do{
		printf("Input contestant name: ");
		scanf("%[^\n]", contest_name);
		getchar();
		found = searchCon(root,contest_name);
		if(!found){
			printf("Contestant Not Found\nPress Any Key To Continue\n");
			getchar();
			break;
		}
	}while(!found);
	printf("Input Score [1-100]: ");
	scanf("%d", contest_score);
	return deletecont(root,contest_name);
}
Node *endAudi(Node *root){
	if(root == NULL){
		return NULL;
	}
	do{
		char gendss[5];
		for (int=0; i++){
			if (strcmp(contest_gender, "male")=0){
				strcpy(Mr, gendss);
			}
			else if (strcmp(contest_gender, "female")=0){
				strcpy(Mrs, gendss);
			}
			printf("%d. %s %s %d", i+1, gends, contest_name, contest_score)
		}
		while(root){
		root = deletecont(root, root->contest_name);
		}
	}while(!root)
	return root;
}
int main(){
	Node *root = NULL;
	int chs;
	do{
		system("CLS");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWAK-Audition\n");
		printf("1. View Contestant\n");
		printf("2. Register Contestant\n");
		printf("3. Call Contestant\n");
		printf("4. End Audition\n");
		printf(">> ");
		scanf("%d", &chs);
		getchar();
		if(chs==1){
			viewContest(root);
		}else if (chs==2){
			root = regisContest(root);
		}else if(chs==3){
			root = callContest(root);
		}else if(chs==4){
			root = endAudi(root);
			break;
		}
	}while(chs!=4);
	return 0;
}
