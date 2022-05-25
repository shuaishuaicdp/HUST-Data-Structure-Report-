/*-----------------头文件引用--------------------*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*--------------------定义--------------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int KeyType;
typedef struct
{ //二叉数结点数据类型定义
    KeyType key;
    char others[20];
} TElemType;
int state1 = 0, state2 = 0;
typedef struct BiTNode
{ //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct
{ //线性表的集合类型定义
    struct
    {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
} TREES;
TElemType definition[LIST_INIT_SIZE];
int num, state = 0;
/*--------------------函数--------------------*/
ElemType max(ElemType a, ElemType b)
{
    if (a > b)
        return a;
    else
        return b;
}
void visit(BiTree T)
{
    if (T == NULL)
        return;
    printf(" %d,%s", T->data.key, T->data.others);
}
void fvisit(BiTree T, FILE *fp)
{
    if (T == NULL)
        return;
    fprintf(fp, " %d,%s", T->data.key, T->data.others);
}
/*-------------------函数声明----------------------*/
status CreateBiTree(BiTree *T, TElemType definition[], int n);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree *T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
status Assign(BiTree *T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree *T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree *T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
int MaxPathSum(BiTree T);
BiTNode *LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree *T);
status AddTree(TREES *Trees, char TreeName[]);
status RemoveTree(TREES *Trees, char TreeName[]);
status LocateTree(TREES Trees, char TreeName[]);
status fPreOrderTraverse(BiTree T, FILE *fp, void (*fvisit)(BiTree, FILE *));
/*--------------------------------------------*/

void main(void)
{
    int op = 1;
    /*--------------------------*/
    BiTree TT = NULL;
    BiTree *T = &TT;
    /*--------------------------*/
    TREES Trees;
    Trees.length = 0;
    /*--------------------------*/
    while (op)
    {
        printf("\n\n");
        printf("                               Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("    	  1. CreateBiTree     7. Assign              13. PostOrderTraverse       19. RemoveTree\n");
        printf("    	  2. DestroyBiTree    8. GetSibling          14. LevelOrderTraverse      20. LocateTree\n");
        printf("    	  3. ClearBiTree      9. InsertNode          15. MaxPathSum              21. ReadFile\n");
        printf("    	  4. BiTreeEmpty      10. DeleteNode         16. LowestCommonAncestor    22. SaveFile\n");
        printf("    	  5. BiTreeDepth      11. PreOrderTraverse   17. InvertTree              23. SwitchTree\n");
        printf("    	  6. LocateNode       12. InOrderTraverse    18. AddTree\n");
        printf("    	  0. Exit\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("请选择你的操作[0~23]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
        {
            printf("请输入数据：\n");
            for (num = 0; definition[num - 1].key != -1; num++)
            {
                int a;
                char c[20];
                scanf("%d %s", &a, c);
                definition[num].key = a;
                strcpy(definition[num].others, c);
            }
            int k = CreateBiTree(T, definition, num);
            if (k == OK)
                printf("树创建成功！\n");
            else if (k == INFEASIBLE)
                printf("树已存在！\n");
            else
                printf("数据错误\n");
            getchar();
            getchar();
            break;
        }
        case 2:
        {
            if (DestroyBiTree(T) == OK)
                printf("树已删除！\n");
            else
                printf("树不存在！\n");
            getchar();
            getchar();
            break;
        }
        case 3:
        {
            if (ClearBiTree(T) == OK)
                printf("清空树成功！\n");
            else
                printf("树不存在！\n");
            getchar();
            getchar();
            break;
        }
        case 4:
        {
            if (BiTreeEmpty(*T) == OK)
                printf("树为空！\n");
            else if (BiTreeEmpty(*T) == INFEASIBLE)
                printf("树不存在！\n");
            else
                printf("树不为空！");
            getchar();
            getchar();
            break;
        }
        case 5:
        {
            int k;
            if (k = BiTreeDepth(*T))
                printf("树的深度为%d!\n", k);
            else
                printf("树不存在！\n");
            getchar();
            getchar();
            break;
        }
        case 6:
        {
            KeyType e;
            printf("您要查找的数是：\n");
            scanf("%d", &e);
            BiTree p = LocateNode(*T, e);
            if (p == NULL)
                printf("未找到！\n");
            else
            {
                printf("找到了！ 是%d,%s！\n", p->data.key, p->data.others);
            }
            getchar();
            getchar();
            break;
        }
        case 7:
        {
            int e, k;
            TElemType p;
            state1 = 0, state2 = 0;
            printf("要赋值的节点是：\n");
            scanf("%d", &e);
            printf("赋值的点和名称是:\n");
            scanf("%d %s", &p.key, &p.others);
            if ((k = Assign(T, e, p)) == OK)
                printf("赋值成功！\n");
            else if (k == INFEASIBLE)
                printf("树不存在！\n");
            else
                printf("赋值失败！\n");
            getchar();
            getchar();
            break;
        }
        case 8:
        {
            ElemType e;
            state1 = 0, state2 = 0;
            printf("请输入您要查找的节点的关键字：\n");
            scanf("%d", &e);
            if (T == NULL)
                printf("树不存在！");
            else
            {
                if (LocateNode(*T, e) != NULL)
                {
                    BiTree p = GetSibling(*T, e);
                    if (p)
                        printf("兄弟找到了！是%d,%s\n", p->data.key, p->data.others);
                    else
                        printf("独生子女！\n");
                }
                else
                    printf("输入错误！");
            }
            getchar();
            getchar();
            break;
        }
        case 9:
        {
            int e, LR, state = 0, state3 = 0;
            TElemType c;
            printf("输入想要插入节点的关键字和位置：\n");
            scanf("%d %d", &e, &LR);
            printf("输入插入节点的关键字和名字：\n");
            scanf("%d %s", &c.key, c.others);
            if (T != NULL)
            {
                for (int i = 0; i < num; i++)
                {
                    if (definition[i].key == c.key)
                        state = 1;
                    if (definition[i].key == e)
                        state3 = 1;
                }
                if (state || !state3)
                    printf("插入失败~~~~~~\n");
                if (!state && state3 && LR != -1)
                {
                    InsertNode(T, e, LR, c);
                    printf("插入完成了！\n");
                    definition[num].key = c.key;
                    strcpy(definition[num].others, c.others);
                    num++;
                }
                else if (LR == -1)
                {
                    definition[num].key = c.key;
                    strcpy(definition[num].others, c.others);
                    num++;
                    InsertNode(T, e, LR, c);
                    printf("插入完成了！\n");
                }
            }
            else
                printf("树不存在！");
            getchar();
            getchar();
            break;
        }
        case 10:
        {
            int e, state = 0;
            if (T != NULL)
            {
                printf("输入您要删除节点的关键字：\n");
                scanf("%d", &e);
                for (int i = 0; i < num; i++)
                {
                    if (definition[i].key == e)
                        state = 1;
                }
                DeleteNode(T, e);
                if (state == 1)
                    printf("删除成功！！\n");
                else
                    printf("删除失败！\n");
            }
            else
                printf("树不存在！");
            getchar();
            getchar();
            break;
        }
        case 11:
        {
            if (PreOrderTraverse(*T, (*visit)) == OK)
                ;
            else
                printf("树不存在？！？！\n");
            getchar();
            getchar();
            break;
        }
        case 12:
        {
            if (InOrderTraverse(*T, (*visit)) == OK)
                ;
            else
                printf("树不存在？！？！\n");
            getchar();
            getchar();
            break;
        }
        case 13:
        {
            if (PostOrderTraverse(*T, (*visit)) == OK)
                ;
            else
                printf("树不存在？！？！\n");
            getchar();
            getchar();
            break;
        }
        case 14:
        {
            if (LevelOrderTraverse(*T, (*visit)) == OK)
                ;
            else
                printf("树不存在？！？！\n");
            getchar();
            getchar();
            break;
        }
        case 15:
        {
            if (MaxPathSum(*T) == 0)
                printf("树不存在！\n");
            else
                printf("最大路径和为：%d\n", MaxPathSum(*T));
            getchar();
            getchar();
            break;
        }
        case 16:
        {
            KeyType e1, e2;
            if (T != NULL)
            {
                printf("输入想要查找的两个节点的关键字：\n");
                scanf("%d %d", &e1, &e2);
                if (LowestCommonAncestor(*T, e1, e2))
                    printf("找到了,它的关键字是%d!\n", LowestCommonAncestor(*T, e1, e2)->data.key);
                else
                    printf("没找到哦！！\n");
            }
            else
                printf("树不存在！");
            getchar();
            getchar();
            break;
        }
        case 17:
        {
            if (*T != NULL)
            {
                if (InvertTree(T))
                    printf("翻转成功！\n");
            }
            else
                printf("树不存在！\n");
            getchar();
            getchar();
            break;
        }
        case 18:
        {
            char TreeName[30];
            printf("请输入新加入线性表的名字！\n");
            scanf("%s", TreeName);
            if (AddTree(&Trees, TreeName) == ERROR)
                printf("插入失败！\n");
            else
                printf("插入成功！\n");
            getchar();
            getchar();
            break;
        }
        case 19:
        {
            char TreeName[30];
            printf("请输入要删除线性表的名字！\n");
            scanf("%s", TreeName);
            if (RemoveTree(&Trees, TreeName) == ERROR)
                printf("删除失败！\n");
            else
                printf("删除成功！\n");
            getchar();
            getchar();
            break;
        }
        case 20:
        {
            char TreeName[30];
            int k;
            printf("请输入要查找的线性表的名字！\n");
            scanf("%s", TreeName);
            if ((k = LocateTree(Trees, TreeName)) == ERROR)
                printf("没有找到！\n");
            else
                printf("找到了！在第%d个\n", k);
            getchar();
            getchar();
            break;
        }
        case 21:
        {
            FILE *fp;
            printf("输入想要读取的文件名！\n");
            char FILENAME[30];
            scanf("%s", FILENAME);
            if ((fp = fopen(FILENAME, "r+")) != NULL)
            {
                DestroyBiTree(T);
                for (num = 0; definition[num - 1].key != -1; num++)
                {
                    int a;
                    char c[20];
                    fscanf(fp, "%d %s", &a, c);
                    definition[num].key = a;
                    strcpy(definition[num].others, c);
                }
                int k = CreateBiTree(T, definition, num);
                if (k == OK)
                    printf("树创建成功！\n");
                else if (k == INFEASIBLE)
                    printf("树已存在！\n");
                else
                    printf("数据错误\n");
            }
            else
                printf("文件不存在！");
            getchar();
            getchar();
            break;
        }
        case 22:
        {
            FILE *fp;
            printf("输入想要输入的文件名！\n");
            char FILENAME[30];
            scanf("%s", FILENAME);
            if (*T != NULL)
            {
                if ((fp = fopen(FILENAME, "w+")) != NULL)
                {
                    fPreOrderTraverse(*T, fp, fvisit);
                    printf("存储成功！");
                }
                else
                    printf("文件不存在！");
            }
            else
                printf("树不存在！");
            getchar();
            getchar();
            break;
        }
        case 23:
        {
            char Treename[10];
            printf("输入你想要切换的树：\n输入0来切换到最初的树:");
            scanf("%s", Treename);
            if (strcmp(Treename, "0") == 0)
            {
                *T = TT;
                printf("Success!");
                state = 0;
            }
            else
            {
                if (LocateTree(Trees, Treename) != ERROR)
                {
                    if (state == 0)
                    {
                        TT = *T;
                    }
                    state = 1;
                    T = &Trees.elem[LocateTree(Trees, Treename) - 1].T;
                    printf("Success!");
                }
                else
                    printf("Failed!Can't find Tree called %s\n", Treename);
            }
            getchar();
            getchar();
            break;
        }
        case 0:
            break;
        default:
            printf("输入格式错误，请重新输入！\n");
            break;
        } // end of switch
    }     // end of while
    printf("欢迎下次再使用本系统！\n");
} // end of main()
int cnt = -1;
status CreateBiTree(BiTree *T, TElemType definition[], int n)
{
    if ((*T) != NULL)
        return INFEASIBLE;
    if (definition[++cnt].key)
    {
        (*T) = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data.key = definition[cnt].key;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        strcpy((*T)->data.others, definition[cnt].others);
        CreateBiTree(&(*T)->lchild, definition, n);
        CreateBiTree(&(*T)->rchild, definition, n);
    }
    else
        (*T) = NULL;
    return OK;
}

status DestroyBiTree(BiTree *T)
{
    if ((*T) == NULL)
        return INFEASIBLE;
    if ((*T))
    {
        if ((*T)->lchild)
            DestroyBiTree(&(*T)->lchild);
        if ((*T)->rchild)
            DestroyBiTree(&(*T)->rchild);
        free((*T));
        (*T) = NULL;
    }
    return OK;
}

status ClearBiTree(BiTree *T)
{
    if ((*T) == NULL)
        return INFEASIBLE;
    if ((*T))
    {
        ClearBiTree(&(*T)->lchild);
        ClearBiTree(&(*T)->rchild);
        (*T)->data.key = 0;
        strcpy((*T)->data.others, " ");
    }
    return OK;
}

status BiTreeEmpty(BiTree T)
{
    if (T == NULL)
        return INFEASIBLE;
    else
    {
        if (T->lchild == NULL && T->rchild == NULL)
            return OK;
    }
    return ERROR;
}

int BiTreeDepth(BiTree T)
{
    if (T == NULL)
        return 0;
    int n = 1;
    n += max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));
    return n;
}

BiTNode *LocateNode(BiTree T, KeyType e)
{
    if (T)
    {
        if (T->data.key == e)
            return T;
        else if (LocateNode(T->lchild, e))
            return LocateNode(T->lchild, e);
        else if (LocateNode(T->rchild, e))
            return LocateNode(T->rchild, e);
    }
    return NULL;
}

status Assign(BiTree *T, KeyType e, TElemType value)
{
    if ((*T) == NULL)
        return INFEASIBLE;
    if ((*T))
    {
        if ((*T)->data.key == value.key)
            state1 = 1;
        if ((*T)->data.key == e && (*T)->data.key == value.key)
        {
            (*T)->data.key = value.key;
            strcpy((*T)->data.others, value.others);
            state2 = 1;
            state1 = 0;
        }
        if ((*T)->data.key == e)
        {
            (*T)->data.key = value.key;
            strcpy((*T)->data.others, value.others);
            state2 = 1;
        }
        Assign(&(*T)->lchild, e, value);
        Assign(&(*T)->rchild, e, value);
    }
    if (state1)
        return ERROR;
    else if (state2)
        return OK;
    else
        return ERROR;
}

BiTNode *GetSibling(BiTree T, KeyType e)
{
    if (T)
    {
        if (T->lchild)
            if (T->lchild->data.key == e)
                return T->rchild;
        if (T->rchild)
            if (T->rchild->data.key == e)
                return T->lchild;
        if (GetSibling(T->lchild, e))
            return GetSibling(T->lchild, e);
        if (GetSibling(T->rchild, e))
            return GetSibling(T->rchild, e);
    }
    return NULL;
}

status InsertNode(BiTree *T, KeyType e, int LR, TElemType c)
{
    if (LR == -1)
    {
        BiTree p = NULL;
        p = (BiTree)malloc(sizeof(BiTNode));
        p->lchild = NULL;
        p->data.key = c.key;
        strcpy(p->data.others, c.others);
        p->rchild = (*T);
        (*T) = p;
        return OK;
    }
    else
    {
        if ((*T))
        {
            if ((*T)->data.key == e)
            {

                BiTNode *p = NULL;
                p = (BiTree)malloc(sizeof(BiTree));
                p->lchild = NULL;
                p->data.key = c.key;
                strcpy(p->data.others, c.others);
                if (LR == 0)
                {
                    p->rchild = (*T)->lchild;
                    (*T)->lchild = p;
                }
                else if (LR == 1)
                {
                    p->rchild = (*T)->rchild;
                    (*T)->rchild = p;
                }
            }
            else
            {
                InsertNode(&(*T)->lchild, e, LR, c);
                InsertNode(&(*T)->rchild, e, LR, c);
            }
        }
    }
    return OK;
}

BiTree FindRightestDnode(BiTree T)
{
    if (T->rchild == NULL)
        return T;
    if (T->rchild)
        return FindRightestDnode(T->rchild);
}

status DeleteNode(BiTree *T, KeyType e)
{
    if ((*T))
    {
        if ((*T)->data.key == e)
        {
            BiTree *p = T;
            if ((*T)->lchild && !(*T)->rchild)
            {
                (*T) = (*T)->lchild;
                free(*p);
                return OK;
            }
            else if (!(*T)->lchild && (*T)->rchild)
            {

                (*T) = (*T)->rchild;
                free(*p);
                return OK;
            }
            else if ((*T)->lchild && (*T)->rchild)
            {
                BiTree q = FindRightestDnode((*T)->lchild);
                q->rchild = (*T)->rchild;
                (*T) = (*T)->lchild;
                free(p);
                return OK;
            }
        }
        else
        {
            DeleteNode(&(*T)->lchild, e);
            DeleteNode(&(*T)->rchild, e);
        }
    }
    return 0;
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        visit(T);
        if (T->lchild)
            PreOrderTraverse(T->lchild, visit);
        if (T->rchild)
            PreOrderTraverse(T->rchild, visit);
        return OK;
    }
    return INFEASIBLE;
}

status fPreOrderTraverse(BiTree T, FILE *fp, void (*fvisit)(BiTree, FILE *))
//前序遍历二叉树T
{
    if (T)
    {
        fvisit(T, fp);
        if (T->lchild)
            fPreOrderTraverse(T->lchild, fp, fvisit);
        if (T->rchild)
            fPreOrderTraverse(T->rchild, fp, fvisit);
        return OK;
    }
    else
    {
        fprintf(fp, " 0 0 NULL ");
    }
    return INFEASIBLE;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T
{
    if (T)
    {
        if (T->lchild)
            InOrderTraverse(T->lchild, visit);
        visit(T);
        if (T->rchild)
            InOrderTraverse(T->rchild, visit);
        return 1;
    }
    return 0;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T
{
    if (T)
    {
        if (T->lchild)
            PostOrderTraverse(T->lchild, visit);
        if (T->rchild)
            PostOrderTraverse(T->rchild, visit);
        visit(T);
        return 1;
    }
    return 0;
}

BiTree a[100];
int front = 0, tail = 0;
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T
{
    if (T == NULL)
        return INFEASIBLE;
    a[front++] = T;
    while (front > tail)
    {
        if (a[tail])
        {
            visit(a[tail]);
            a[front++] = a[tail]->lchild;
            a[front++] = a[tail]->rchild;
        }
        tail++;
    }
    return OK;
}

status find(BiTree T, KeyType e)
{
    if (T)
    {
        if (T->data.key == e)
            return OK;
        else
        {
            if (T->lchild)
                if (find(T->lchild, e))
                    return OK;
            if (T->rchild)
                if (find(T->rchild, e))
                    return OK;
        }
    }
    return 0;
}

BiTNode *LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
    if (T)
    {
        if (find(T->lchild, e1) && find(T->rchild, e2))
            return T;
        else if (find(T->lchild, e2) && find(T->rchild, e1))
            return T;
        else
        {
            if (T->lchild)
            {
                if (LowestCommonAncestor(T->lchild, e1, e2))
                    return LowestCommonAncestor(T->lchild, e1, e2);
            }
            if (T->rchild)
            {
                if (LowestCommonAncestor(T->rchild, e1, e2))
                    return LowestCommonAncestor(T->rchild, e1, e2);
            }
        }
    }
    return NULL;
}

status InvertTree(BiTree *T)
{
    if (*T == NULL)
        return INFEASIBLE;
    if ((*T))
    {
        BiTree p = (*T)->lchild;
        (*T)->lchild = (*T)->rchild;
        (*T)->rchild = p;
        InvertTree(&(*T)->lchild);
        InvertTree(&(*T)->rchild);
    }
}

int MaxPathSum(BiTree T)
{
    if (T)
    {
        return max(MaxPathSum(T->lchild), MaxPathSum(T->rchild)) + T->data.key;
    }
    return 0;
}

status AddTree(TREES *Trees, char TreeName[])
{
    if ((*Trees).length >= 10)
        return ERROR;
    (*Trees).elem[(*Trees).length].T = (BiTree)malloc(sizeof(BiTree));
    (*Trees).elem[(*Trees).length].T = NULL;
    strcpy((*Trees).elem[(*Trees).length].name, TreeName);
    (*Trees).length++;
    return OK;
}

status RemoveTree(TREES *Trees, char TreeName[])
{
    int i, j;
    if ((*Trees).length == 0)
        return ERROR;
    for (i = 0; i < (*Trees).length; i++)
    {
        if (strcmp((*Trees).elem[i].name, TreeName) == 0)
        {
            for (j = i; j < (*Trees).length - 1; j++)
            {
                (*Trees).elem[j] = (*Trees).elem[j + 1];
            }
            (*Trees).length--;
            return OK;
        }
    }
    return ERROR;
}

status LocateTree(TREES Trees, char TreeName[])
{
    int state = 0, i, j;
    for (i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, TreeName) == 0)
            return i + 1;
    }
    return 0;
}