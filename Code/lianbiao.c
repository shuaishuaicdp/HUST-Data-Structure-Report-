/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType;

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct Dnode{
	struct Dnode *next;
    ElemType data;
}Dnode,*LinkList;

typedef struct{  //线性表的集合类型定义  
     struct { 
        char name[30];  
        LinkList L;      
      } elem[10];  
      int length;  
 }LISTS; 
/*--------------------函数--------------------*/
ElemType max(ElemType a,ElemType b)
{
    if(a>b) return a;
    else return b;
}
/*--------------------------------------------*/
status InitList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType* e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType *pre);
status NextElem(LinkList L,ElemType e,ElemType *next);
status ListInsert(LinkList *L,int i,ElemType e);
status ListDelete(LinkList *L,int i,ElemType* e);
status ListTraverse(LinkList L);
status ManyElemInsert(LinkList *L);
status ReverseList(LinkList *L);
status RemoveNthFromEnd(LinkList *L,int n);
status AddList(LISTS *Lists,char ListName[]);
status RemoveList(LISTS *Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
status sortList(LinkList *L);

/*--------------------------------------------*/
void main(void){
int op=1;
/*--------------------------*/
    LinkList LLL=NULL,*L=&LLL;
/*--------------------------*/
    LISTS Lists;
    Lists.length=0;
/*--------------------------*/
while(op){
    printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem        13. ManyElemInsert      19. ReadFile\n");
	printf("    	  2. DestroyList    8. PriorElem         14. ReverseList         20. SaveFile\n");
	printf("    	  3. ClearList      9. NextElem          15. RemoveNthFromEnd    21. sortList\n");
	printf("    	  4. ListEmpty      10. ListInsert       16. AddList\n");
	printf("    	  5. ListLength     11. ListDelete       17. RemoveList\n");
	printf("    	  6. GetElem        12. ListTraverse     18. LocateList\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("请选择你的操作[0~20]:");
	scanf("%d",&op);

    switch(op){
	    case 1:
		    if(InitList(L)==OK) printf("链表创建成功！\n");
		    else printf("链表已存在！\n");
		    getchar();getchar();
		    break;
	    case 2:
		    if(DestroyList(L)==OK) printf("链表销毁成功！\n");
		    else printf("链表不存在！\n");    
		    getchar();getchar();
		    break;
	    case 3:
		    if(ClearList(L)==OK) printf("链表清理成功！\n");
		    else printf("链表不存在！\n");       
		    getchar();getchar();
		    break;
	    case 4:
		    if(ListEmpty(*L)==TRUE) printf("链表为空！\n");
		    else if(ListEmpty(*L)==FALSE)printf("链表不为空！\n");     
		    else printf("链表不存在！\n");
		    getchar();getchar();
		    break;
	    case 5:
		    if(ListLength(*L)!=INFEASIBLE) printf("链表长度为%d！\n",ListLength(*L));
            else printf("链表不存在！\n");     
		    getchar();getchar();
		    break;
	    case 6:{
		    ElemType *e;
            int i;
            printf("输入想要获取的位数：\n");
            scanf("%d",&i);
            if(GetElem(*L,i,e)==INFEASIBLE) printf("链表不存在！\n");
            else if(GetElem(*L,i,e)==ERROR) printf("输入错误！\n");
            else printf("您要获取的数据为%d\n",*e);
		    getchar();getchar();
		    break;}
	    case 7:{
		    ElemType e;
            printf("您要查找的数字是：\n");
            scanf("%d",&e);
            if(LocateElem(*L,e)==INFEASIBLE) printf("链表不存在！\n");
            else if(LocateElem(*L,e)==ERROR) printf("没有找到！\n");
            else printf("找到了！在第%d位\n",LocateElem(*L,e));
		    getchar();getchar();
		     break;}
	    case 8:{
		    ElemType num, *pre = &num, e;
            printf("您要找哪个数的前驱数？");
            scanf("%d",&e);
            if(PriorElem(*L,e,pre)==INFEASIBLE)  printf("链表不存在！\n");
            else if(PriorElem(*L,e,pre)==ERROR) printf("未找到您要查找的数的前驱！\n");
            else printf("前驱数为%d!\n",*pre);
		    getchar();getchar();
		    break;}
	    case 9:{
		    ElemType *next,e;
            printf("您要找哪个数的后驱数？");
            scanf("%d",&e);
            if(NextElem(*L,e,next)==INFEASIBLE)  printf("链表不存在！\n");
            else if(NextElem(*L,e,next)==ERROR) printf("未找到您要查找的数的后驱！\n");
            else printf("后驱数为%d!\n",*next);
		    getchar();getchar();
		    break;}
	    case 10:{
		    ElemType e,i,k;
            printf("请输入您要插入的数以及位置！",&e,&i); 
            scanf("%d %d",&e,&i);
            if((k=ListInsert(L,i,e))==INFEASIBLE)  printf("链表不存在！\n");
            else if(k==ERROR) printf("插入位置不正确！\n");
            else printf("插入成功！\n");
		    getchar();getchar();
		    break;}
	    case 11:{
		    ElemType e,i,k;
            printf("请输入您要删除的数以及位置！",&e,&i); 
            scanf("%d %d",&e,&i);
            if((k=ListInsert(L,i,e))==INFEASIBLE)  printf("链表不存在！\n");
            else if(k==ERROR) printf("删除位置不正确！\n");
            else printf("删除成功！\n");   
		    getchar();getchar();
		    break;}
	    case 12:{
		    if(!ListTraverse(*L)) printf("链表是空表！\n");
		    getchar();getchar();
		    break;}
        case 13:{
            if(ManyElemInsert(L)==INFEASIBLE)  printf("链表不存在！\n");
            else printf("输入完成！");
            getchar();getchar();
            break;
        }
        case 14:{
           int k;
           if((k=ReverseList(L))==INFEASIBLE) printf("链表不存在！\n");
           else if(k==ERROR) printf("链表为空!");
           else printf("反转完成！");
           getchar();getchar();
           break;
        }
        case 15:{
           int n,k;
           printf("输入需要移除的节点倒数位置：");
           scanf("%d",&n);
           if((k=RemoveNthFromEnd(L,n))==INFEASIBLE) printf("链表不存在！\n");
           else if(k==ERROR) printf("输入有误！");
           else printf("已移除！");
           getchar();getchar();
           break;
        }
        case 16:{
           char ListName[30];
            printf("请输入新加入线性表的名字！\n");
            scanf("%s",ListName);
            if(AddList(&Lists,ListName)==ERROR) printf("插入失败！\n");
            else printf("插入成功！\n");
            getchar();getchar();
           break;
        }
        case 17:{
           char ListName[30];
            printf("请输入要删除线性表的名字！\n");
            scanf("%s",ListName);
            if(RemoveList(&Lists,ListName)==ERROR) printf("删除失败！\n");
            else printf("删除成功！\n");
            getchar();getchar();
           break;
        }
        case 18:{
           char ListName[30];
           int k;
            printf("请输入要查找的线性表的名字！\n");
            scanf("%s",ListName);
            if((k=LocateList(Lists,ListName))==ERROR) printf("没有找到！\n");
            else printf("找到了！在第%d个\n",k);
            getchar();getchar();
           break;
        }
        case 19:{
            FILE* fp;
            printf("请输入文件名！\n");
            char FileName[30];
            scanf("%s", FileName);
            fp = fopen(FileName, "r+");
            if(!fp)
                printf("文件未找到！\n");
            else{
                InitList(L);
                int cnt = 0, num ;
                while (fscanf(fp, "%d", &num) != EOF)
                {
                    ListInsert(L, ++cnt, num);
                    
                }
                printf("已完成读取！\n");
            }
            fclose(fp);
            getchar();getchar();
            break;
        }
        case 20:{
            FILE *fp;
            printf("请输入文件名！\n");
            char FileName[30];
            scanf("%s", FileName);
            fp = fopen(FileName, "w+");
            if(L == NULL)
                printf("线性表不存在！\n");
            else{
                LinkList p = (*L)->next;
                while (p)
                {
                    fprintf(fp, "%d ", p->data);
                    p = p->next;
                }
                printf("写入完成！\n");
            }
            getchar();getchar();
           break;
        }
        case 21:{
            int k;
            if((k=sortList(L))==INFEASIBLE) printf("链表不存在！\n");
            else if(k==ERROR) printf("链表为空！");
            else printf("排序完成！");
            getchar();getchar();
            break;
        }
	case 0:
         break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
}//end of main()
/*-----------------page 23 on textbook --------------------*/
status InitList(LinkList *L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/    
    if((*L)!=NULL) return INFEASIBLE;
    (*L)=(LinkList) malloc(sizeof(LinkList));
    (*L)->next=NULL;
    return OK;

    /********** End **********/
}
 
status DestroyList(LinkList *L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if((*L)==NULL) return INFEASIBLE;
    // LinkList  p=(*L);
    // while (p->next)
    // {
    //     p=(*L)->next;
    //     free((*L));
    //     (*L) = p;
    // }
    // free(L);free(p);
    (*L)=NULL;
    return OK;
    /********** End **********/
}
status ClearList(LinkList *L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if((*L)==NULL) return INFEASIBLE;
    LinkList p=(*L)->next,q;
    while(p->next)
    {
        q=p;
        p=q->next;
        free(q);
    }
    free(p);
    (*L)->next=NULL;
    return OK;
    /********** End **********/
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    if(L->next==NULL) return TRUE;
    else return FALSE;

    /********** End **********/
}
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    LinkList p=L;
    int cnt=0;
    while(p->next)
    {
        cnt++;
        p=p->next;
    }
    return cnt;
    /********** End **********/
}
status GetElem(LinkList L,int i,ElemType *e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    if(i<1) return ERROR;
    int cnt=0;
    LinkList p=L;
    while(p->next)
    {
        cnt++;
        p=p->next;
    }
    if(i>cnt||i<1) return ERROR;
    cnt=0;
    p=L;
    while(p->next)
    {
        cnt++;
        p=p->next;
        if(i==cnt) 
        {
            e=p->data;
            break;
        }
    }
    return OK;
    /********** End **********/
}
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    LinkList p=L;
    int cnt=0;
    while(p->next)
    {
        p=p->next;
        cnt++;
        if(e==p->data)
        {
            return cnt;
        }
    }
    return ERROR;
    /********** End **********/
}
status PriorElem(LinkList L,ElemType e,ElemType *pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    LinkList p=L->next,q=L;
    int num=1;
    while(q->next!=NULL && p->data!=e)
    {
        q=p;
        p=p->next;
        num++;
    }
    if(num==1) return ERROR;
    if(p==NULL) return ERROR;
    *pre=q->data;
    return OK;
    /********** End **********/
}
status NextElem(LinkList L,ElemType e,ElemType *next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    LinkList p=L;
    while(p->next)
    {
        p=p->next;
        if(p->data==e)
        {
            break;
        }
    }
    if(p->next==NULL) return ERROR;
    (*next)=(p->next)->data;
    return OK;
    /********** End **********/
}
status ListInsert(LinkList *L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if((*L)==NULL) return INFEASIBLE;
    LinkList p=(*L);
    int cnt=0;
    while(p->next)
    {
        p=p->next;
        cnt++;
    }
    if(i<1||i>cnt+1) return ERROR;
    p=(*L),cnt=0;
    while(p->next&&i-1>cnt)
    {
        p=p->next;
        cnt++;
    }
    LinkList r;
    r=(LinkList)malloc(sizeof(LinkList));
    r->next=p->next;
    p->next=r;
    r->data=e;
    return OK;
    /********** End **********/
}

status ListDelete(LinkList *L,int i,ElemType *e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if((*L)==NULL) return INFEASIBLE;
    int cnt=0;
    LinkList p=(*L),q;
    while(p->next)
    {
        p=p->next;
        cnt++;
    }
    if(i<1||i>cnt) return ERROR;
    cnt=0;p=(*L);
    while(cnt<i-1)
    {
        p=p->next;
        cnt++;
    }
    q=p->next;
    e=q->data;
    p->next=p->next->next;
    free(q);
    return OK;
    /********** End **********/
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return 0;
    LinkList p=L;
    printf("-------------All Elem--------------\n");
    while(p->next)
    {
        p=p->next;
        printf("%d ",p->data);
    }
    printf("\n-------------All Elem--------------\n");
    return OK;
    /********** End **********/
}

status ManyElemInsert(LinkList *L)
{
    if((*L)==NULL) return INFEASIBLE;
    ElemType n,now;
    LinkList p=(*L);
    printf("您要插入的数据有几个？\n");
    scanf("%d",&n);
    printf("输入您要插入的数据：\n");
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&now);
        LinkList q=(LinkList)malloc(sizeof(LinkList));
        p->next=q;
        q->data=now;
        p=q;
    }
    p->next=NULL;
    return OK;
}

status ReverseList(LinkList *L)
{
    if((*L)==NULL) return INFEASIBLE;
    if((*L)->next==NULL) return ERROR;
    LinkList p=(*L)->next,q=(*L),r=(*L)->next->next;
    while(r)
    {
        q=p;
        p=r;
        r=p->next;
        p->next=q;
    }
    ((*L)->next)->next=NULL;
    (*L)->next=p;
    return OK;
}

status RemoveNthFromEnd(LinkList *L,int n)
{
    if((*L)==NULL) return INFEASIBLE;
    int cnt=0,num;
    LinkList p=(*L);
    while(p->next)
    {
        p=p->next;
        cnt++;
    }
    if(n<1||cnt<n) return ERROR;
    num=cnt-n+1;cnt=0; p=(*L);
    while(cnt<num-1)
    {
        p=p->next;
        cnt++;
    }
    p->next=p->next->next;
    return OK;
}
status AddList(LISTS *Lists,char ListName[])
{
    if((*Lists).length>=10) return ERROR;
    (*Lists).elem[(*Lists).length].L=(LinkList) malloc(sizeof(LinkList));
    (*Lists).elem[(*Lists).length].L->next=NULL;
    strcpy((*Lists).elem[(*Lists).length].name,ListName);
    (*Lists).length++;
    return OK;
}
status RemoveList(LISTS *Lists,char ListName[])
{
    int i,j;
    if((*Lists).length==0) return ERROR;
    for(i=0;i<(*Lists).length;i++)
    {
        if(strcmp((*Lists).elem[i].name,ListName)==0)
        {
            for(j=i;j<(*Lists).length-1;j++)
            {
                (*Lists).elem[j]=(*Lists).elem[j+1];
            }
            (*Lists).length--;
            return OK;
        }
    }
    return ERROR;
}
status LocateList(LISTS Lists,char ListName[])
{
    int state=0,i,j;
    for(i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name,ListName)==0) return i+1;
    }
    return 0;
}

status sortList(LinkList *L)
{
    if((*L)==NULL) return INFEASIBLE;
    if((*L)->next==NULL) return ERROR;
    ElemType a[101];
    LinkList p=(*L);
    int cnt=0;
    while(p->next)
    {
        p=p->next;
        cnt++;
        a[cnt]=p->data;
    }
    a[cnt]=p->data;
    for(int i=cnt;i>1;i--)
    {
        for(int j=1;j<i;j++)
        {
            if(a[j]>a[j+1])
            {
                ElemType t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        printf("%d ",a[i]);
    }
    p=(*L);cnt=0;
    while(p->next)
    {
        p=p->next;
        cnt++;
        p->data=a[cnt];
    }
    p->data=a[cnt];
    return OK;
}