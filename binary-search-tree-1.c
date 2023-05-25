/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
void freeNode(Node* ptr);  //노드의 메모리를 반환하는 함수
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
        printf("              [----- [이찬희] [2019068057] -----]                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

//재귀적 반복을 통한 트리 출력

void inorderTraversal(Node* ptr)
{
    if(ptr) {
        inorderTraversal(ptr->left);
        printf(" [%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr)
{
    printf(" [%d] ", ptr->key);
    preorderTraversal(ptr->left);
    preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
    postorderTraversal(ptr->left);
    postorderTraversal(ptr->right);
    printf(" [%d] ", ptr->key);
}


int insert(Node* head, int key)
{
    Node* new = (Node*)malloc(sizeof(Node));  //key값을 가진 새로운 노드 new 메모리 할당
    new->key = key;
    new->left = NULL;
    new->right = NULL;

    if(head->left == NULL) {  //만약 트리가 비어있었으면 헤드노드의 left가 new를 가리키게 설정 = new를 root로 설정
        head->left = new;
        return 0;
    }

    Node* now = head->left;  //트리를 타고 다닐 now
    Node* parent = NULL;  //now를 따라다닐 parent

    while(now != NULL) {
        if(new->key == now->key) {
            return 1;
        }
        parent = now;  //now를 따라 parent 이동

        if(new->key < now->key) {  //입력한 key가 현재 노드의 key보다 작으면 좌측 child로 이동
            now = now->left;
            }
        else {  //입력한 key가 현재 노드의 key보다 크면 우측 child로 이동
            now = now->right;
            }
    }

    if(new->key < parent->key) {  //key 값에 따라 parent의 child로 new 배치
        parent->left = new;
    }
    else {
        parent->right = new;
    }

    return 1;

}

int deleteLeafNode(Node* head, int key)
{
	if(head == NULL) {  //트리 자체와 root가 없으면 오류 메시지 출력
		printf("nothing to delete");
		return 0;
	}

	if(head->left == NULL) {
		printf("nothing to delete");
		return 0;
	}
	
	Node* now = head->left;  //트리를 타고다닐 now
	Node* parent = head;  //now를 뒤따라다닐 parent

	while(now != NULL) {  //now가 NULL이 아닐때까지 반복
		if(now->key == key) {  //입력한 key를 가진 now를 찾았을 때
			if(now->left == NULL && now->right == NULL) {  //만약 now가 리프 노드였다면
				if(parent == head) {  //만약 now가 root였다면
					head->left = NULL;  //head노드에서 root를 끊는다
				}

				if(parent->left == now) {  //parent의 왼쪽 child가 now였다면
					parent->left = NULL;  //parent의 왼쪽 child는 없던 것으로
				}
				else {  //오른쪽 child가 now였으면 오른쪽 child를 없던 것으로
					parent->right = NULL;
				}
				free(now);  //now 메모리 반환
			}
			else {
				printf("node is not a leaf node");  //리프 노드가 아니라면 오류메시지 출력
			}
			return 1;
		}

		parent = now;  //parent를 now를 따라 한 칸 이동

		if(now->key < key) {  //now의 key가 입력된 key값에 따라 왼쪽, 오른쪽 child로 이동
			now = now->right;
		}
		else {
			now = now->left;
		}
	}

	printf("cannot find the node for key");  //now가 NULL, 즉 입력한 key를 가진 노드 발견 실패 시 오류메시지 출력
	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) {
		return NULL;
	}

	if(ptr->key < key) {  //입력된 노드의 key보다 입력한 key가 더 크면
		ptr = searchRecursive(ptr->right, key);  //우측 child로 재귀적 탐색
	}
	else if(ptr->key > key) {  //반대의 경우 좌측 child로 재귀적 탐색
		ptr = searchRecursive(ptr->left, key);
	}
	else {
		return 0;
	}
}

Node* searchIterative(Node* head, int key)
{
	Node* now = head->left;  //트리를 타고다닐 now

	while(now != NULL) {
		if(now->key == key) {  //now의 key가 입력한 key와 같다면 now 리턴
			return now;
		}
		if(now->key < key) {  //now의 key가 입력한 key보다 작다면 오른쪽 child로, 반대면 왼쪽 child로 이동
			now = now->right;
		}
		else {
			now = now->left;
		}
	}
	return NULL;
}

void freeNode(Node* ptr) {  //노드의 메모리를 반환하는 함수 선언
	if(ptr) {
		freeNode(ptr->left);  //좌측, 우측 child에 대해 재귀적으로 먼저 반환
		freeNode(ptr->right);
		free(ptr);  //입력된 노드 반환
	}
}


int freeBST(Node* head)
{
	if(head->left == head) {  //만약 트리가 비어있다면 head노드를 메모리 반환
		free(head);
		return 1;
	}

	Node* root = head->left;  //root 노드
	freeNode(root);

	return 1;
}