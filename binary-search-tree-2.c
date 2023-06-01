/*
 * binary-search-tree-2.c
 * 이진 탐색 트리
 * 자료구조 10번째 과제
 * 충북대학교 2017015040 물리학과 강수
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {//노드 구조
	int key;//값
	struct node *left;//작은 값 노드 주소
	struct node *right;//큰 값 노드 주소
} Node;

//iterativeInorder에서 사용할 스택
#define MAX_STACK_SIZE		20//스택의 최대치
Node* stack[MAX_STACK_SIZE];//노드 포인터 스택
int top = -1;//스택 초기화


//levelOrder에서 사용할 큐
#define MAX_QUEUE_SIZE		20//최대치
Node* queue[MAX_QUEUE_SIZE];
int front = -1;//시작
int rear = -1;//끝



int initializeBST(Node** h);//초기화
void recursiveInorder(Node* ptr);//재귀방식 inorder traversal 재귀 중위 순회
int insert(Node* head, int key);//노드추가
int freeBST(Node* head);//메모리 해지


void iterativeInorder(Node* ptr); //iterative inorder traversal  반복적 중위 순회
void levelOrder(Node* ptr);	//level order traversal 레벨 순서 순회 
int deleteNode(Node* head, int key);  //노드삭제
Node* pop();//스택에 사용할 팝
void push(Node* aNode);//스택에 사용할 푸쉬
Node* deQueue();//큐에 사용할 디큐
void enQueue(Node* aNode);//큐에 사용할 인큐



void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
  	printf("[----- [kang su] [2017015040] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);//루트노드 주소부여
			break;
		case 't': case 'T':
			iterativeInorder(head->left);//루트노드 주소 부여
			break;

		case 'l': case 'L':
			levelOrder(head->left);//루트노드 주소 부여
			break;

		case 'p': case 'P':
			printStack();//스택 확인용?
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

    //기존노드가 있으면 해지
	if(*h != NULL)//헤드노드가 있는경우
		freeBST(*h);

	//헤드노드 초기화
	*h = (Node*)malloc(sizeof(Node));// 헤드노드 메모리 할당
	(*h)->left = NULL; //루트노드
	(*h)->right = *h;//
	(*h)->key = -9999;//값

	top = -1;//스택 초기화

	front = rear = -1;//큐 초기화

	return 1;
}



void recursiveInorder(Node* ptr)//재귀
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
    for(;;){//if문 break전까지 반복
        for ( ; node; node=node->left)//node가 NULL일 때까지
            push(node);//스택에 삽입
        node =pop();//스택에서 삭제
        if (!node) break;//node NULL이면 종료
        printf(" [%d] ",node->key);//키값 출력
        node =node->right;//오른족 노드로 이동
        
    }
	
}

void printStack(){//스택 출력

	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}


}

void levelOrder(Node* ptr)//레벨 순서 트리 순회
{
	if(!ptr) return;//주소가 NULL 인경우
	enQueue(ptr);//큐에 fnxm 노드 추가
	for(;;)
	{//if 전 까지 반복:노드가 NULL이면 탈출
		ptr = deQueue();//큐에서 노드 꺼내기
		if(ptr){//노드가 NULL이 아니면
			printf(" [%d] ",ptr->key);//출력
			//큐에서 꺼낸 노드에 왼쪽 노드가 있으면
			if(ptr->left) enQueue(ptr->left);//큐에 저장
			//큐에서 꺼낸 노드에 오른쪽 노드가 있으면
			if(ptr->right) enQueue(ptr->right);//큐에 저장

		}
		else break;
	}



}


int insert(Node* head, int key)//노드 추가
{
	//신노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	//루트노드인경우
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	//루트노드
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		//값이 같은경우 무시
		if(ptr->key == key) return 1;

		//부모노드 기억용도
		parentNode = ptr;

		//비교해서 작으면 왼쪽 크면 오른쪽으로 이동
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	//신노드 넣을 위치 지정 작으면 왼족 크면 오른쪽
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {
		printf("deleteNode(): Nothing to delete!!\n");
		return -1;
	}

	if (!head->left){
		printf("deleteNode(): Node is empty");
		return -1;//NULL이면 탈출
	} 

	Node* node =head->left; //루트노드로 초기화
	Node* pNode =head;//보모 노드를 헤드노드로 초기화
	
	//리프노드의 경우
	for(;;){
		if (!node) break;//NULL이면 탈출
		//printf("deleteNode(): node [ %d : %p ]\n",node->key,node);//노드 확인용
		
		if(node->key==key){//값을 찾으면

			// -----------------case 1 리프노드의 경우--------------
			if(!(node->left)&&!(node->right)){//리프노드의 경우
				//printf("deleteNode(): case 1 : leaf Node ");
				//지울 노드를 가르키는 포인터를 변경
				if(pNode->left==node) pNode->left=NULL;//부모의 왼쪽 자식인 경우 왼쪽 포인터 제거
				else if(pNode->right==node) pNode->right=NULL;//부모의 오른족 자식인 경우 오른쪽 포인터 제거
				else{//오류
					//printf(" : pNode ptr Err\n");
					return 1;
				}	
				free(node);//노드 해지
				//printf(" : delete [ %d ]\n",key);//노드 삭제 알림
				return 1;
			}

			//-----------------case 2 자식이 하나-----------------------
			else if(!(node->left)||!(node->right)){//자식이 둘중 하나가 없는경우
				//printf("deleteNode(): case 2 : one child");
				Node* child;//자식 포인터 저장용

				if(node->left) child=node->left;//왼쪽 자식의 경우 왼쪽 연결
				else if(node->right) child=node->right;//오른쪽 자식의 경우 오른쪽 연결
				else{
						//printf(" : child Err\n");
						return -1;
				}
				//지울노드 대신에 child를 가르키도록 변경
				if(pNode->left==node) pNode->left=child;//왼쪽 자식인 경우 왼쪽에 child 연결
				else if(pNode->right==node) pNode->right=child;//오른족 자식인 경우 오른쪽에 child 연결
				else{//오류
					//printf(" : pNode ptr Err\n");
					return -1;
				}	
				free(node);//노드 해지
				//printf(" : delete [ %d ]\n",key);//노드 삭제 알림
				return 1;

			}

			//-------------------case 3 자식이 2개------------------------
			else{//자식이 둘다 있는 경우
				//printf("deleteNode(): case 3 : two children");
				Node* changeNode=node->right;//삭제한 노드를 바꿀노드,초기화는 오른쪽 자식
				pNode =node;
				for(;;){//오른쪽 자식중 가장작은 자식으로 바꿀 노드를 선택
					if (!changeNode->left) break;//왼쪽 자식이 없으면 탈출
					else{//왼쪽 자식이 있으면
							pNode=changeNode;
							changeNode=changeNode->left;
					}
				}//바꿀노드는 왼쪽 자식이 없음
			
				if(pNode==node){//바꿀노드의 부모가 변경해야할 경우
					pNode->right=changeNode->right;
				}
				else{//바꿀노드의 부모가 변경되지 않을경우
					pNode->left=changeNode->right;
				}
				//노드의 값을 변경
				node->key=changeNode->key;//바꿀노드 값으로 삭제할 노드값을 변경
				free(changeNode);//바꿀노드를 해지
				//printf(" : delete [ %d ]\n",key);//노드 삭제 알림
				return 1;
			}

		}
		else if(node->key>key){//노드가 큰경우
			pNode =node;//부모노드로 설정
			node=node->left;//자식 노드로 이동
		}else{//작은경우
			pNode =node;
			node=node->right;
		}

	}

	return 0;
}


void freeNode(Node* ptr)//재귀 형식으로 노드 해지
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)//전체 노드해지
{

	if(head->left == NULL)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
    if(top>-1){//스택에 유효값이 없는경우
		return stack[top--];//top위치 값 꺼내고 감소
    }
	//printf("pop():stack is eamty\n");
	return NULL;

	
}

void push(Node* aNode)
{
    if(top<MAX_QUEUE_SIZE){
    top++;//값증가
    stack[top]=aNode;//증가된 위치에 저장
    }
    else printf("push():stack is full\n");
}



Node* deQueue()
{
	
	if(front==rear){//값이 같을 경우
		//printf("deQueue():Queue is eamty\n");
		return NULL;//반환 할게 없는경우
	}
	front=(front+1)%MAX_QUEUE_SIZE;//앞으로 이동하다 끝에 도달하면 처음으로
	return queue[front];//반환

}

void enQueue(Node* aNode)
{
	//int bRear=rear;//변경전 값 백업
	rear=(rear+1)%MAX_QUEUE_SIZE;//앞으로 이동하다 끝에 도달하면 처음으로
	if(front==rear){//값이 같을 경우
		printf("enQueue():Queue is full\n");
		//rear=bRear;//큐가찬 상태로 2회 이상 실행시 값을 덮어쓰는 문제 방지용
		return;
	}
	queue[rear]=aNode;//해당 위치에 저장

}




