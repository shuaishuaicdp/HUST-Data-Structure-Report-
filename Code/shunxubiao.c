/*-------------------头文件引用-----------------*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*-------------------定义----------------------*/
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
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

typedef struct
{ //线性表的集合类型定义
    struct
    {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;
int state = 0;
/*--------------------函数------------------------*/
ElemType max(ElemType a, ElemType b)
{
    if (a > b)
        return a;
    else
        return b;
}
/*-------------------函数声明----------------------*/
status InitList(SqList *L);
status DestroyList(SqList *L);
status ClearList(SqList *L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType *e);
status LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType cur, ElemType *pre);
status NextElem(SqList L, ElemType cur, ElemType *next);
status ListInsert(SqList *L, int i, ElemType e);
status ListDelete(SqList *L, int i, ElemType *e);
status ListTrabverse(SqList L);
status MaxSubArray(SqList L);
status SubArrayNum(SqList L, ElemType k);
status sortList(SqList L);
status AddList(LISTS *Lists, char ListName[]);
status RemoveList(LISTS *Lists, char ListName[]);
status LocateList(LISTS Lists, char ListName[]);

/*--------------------------------------------*/
void main(void)
{
    int op = 1;
    /*--------------------------*/
    SqList LL, *L = &LL;
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    /*--------------------------*/
    LISTS Lists;
    Lists.length = 0;
    /*--------------------------*/
    while (op)
    {
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem        13.MaxSubArray       19.ReadFile\n");
        printf("    	  2. DestroyList    8. PriorElem         14.SubArrayNum       20.SaveFile\n");
        printf("    	  3. ClearList      9. NextElem          15.sortList          21.ChangeList\n");
        printf("    	  4. ListEmpty      10. ListInsert       16.AddList\n");
        printf("    	  5. ListLength     11. ListDelete       17.RemoveList\n");
        printf("    	  6. GetElem        12. ListTrabverse    18. LocateList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~21]:");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            if (InitList(L) == OK)
                printf("线性表创建成功！\n");
            else
                printf("线性表创建失败！\n");
            getchar();
            getchar();
            break;
        case 2:
            if (DestroyList(L) == OK)
                printf("线性表销毁成功！\n");
            else
                printf("线性表不存在！\n");
            getchar();
            getchar();
            break;
        case 3:
            if (ClearList(L) == OK)
                printf("线性表清理成功！\n");
            else
                printf("线性表不存在！\n");
            getchar();
            getchar();
            break;
        case 4:
            if (ListEmpty(*L) == TRUE)
                printf("线性表为空！\n");
            else if (ListEmpty(*L) == FALSE)
                printf("线性表不为空！\n");
            else
                printf("线性表不存在！\n");
            getchar();
            getchar();
            break;
        case 5:
            if (ListLength(*L) != INFEASIBLE)
                printf("线性表长度为%d！\n", ListLength(*L));
            else
                printf("线性表不存在！\n");
            getchar();
            getchar();
            break;
        case 6:
        {
            ElemType e = 0;
            int i;
            printf("输入想要获取的位数：\n");
            scanf("%d", &i);
            if (GetElem(*L, i, &e) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (GetElem(*L, i, &e) == ERROR)
                printf("输入错误！\n");
            else
                printf("您要获取的数据为%d\n", e);
            getchar();
            getchar();
            break;
        }
        case 7:
        {
            ElemType e;
            printf("您要查找的数字是：\n");
            scanf("%d", &e);
            if (LocateElem(*L, e) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (LocateElem(*L, e) == ERROR)
                printf("没有找到！\n");
            else
                printf("找到了！在第%d位\n", LocateElem(*L, e));
            getchar();
            getchar();
            break;
        }
        case 8:
        {
            ElemType pre, e;
            printf("您要找哪个数的前驱数？");
            scanf("%d", &e);
            if (PriorElem(*L, e, &pre) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (PriorElem(*L, e, &pre) == ERROR)
                printf("未找到您要查找的数的前驱！\n");
            else
                printf("前驱数为%d!\n", pre);
            getchar();
            getchar();
            break;
        }
        case 9:
        {
            ElemType next, e;
            printf("您要找哪个数的后驱数？");
            scanf("%d", &e);
            if (NextElem(*L, e, &next) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (NextElem(*L, e, &next) == ERROR)
                printf("未找到您要查找的数的后驱！\n");
            else
                printf("后驱数为%d!\n", next);
            getchar();
            getchar();
            break;
        }
        case 10:
        {
            ElemType e, i, k;
            printf("请输入您要插入的数以及位置！", &e, &i);
            scanf("%d %d", &e, &i);
            if ((k = ListInsert(L, i, e)) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (k == ERROR)
                printf("插入位置不正确！\n");
            else
                printf("插入成功！\n");
            getchar();
            getchar();
            break;
        }
        case 11:
        {
            ElemType e, i, k;
            printf("请输入您要删除的位置！", &i);
            scanf("%d", &i);
            if ((k = ListDelete(L, i, &e)) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (k == ERROR)
                printf("删除位置不正确！\n");
            else
                printf("删除成功！\n");
            getchar();
            getchar();
            break;
        }
        case 12:
        {
            if (!ListTrabverse(*L))
                printf("线性表是空表！\n");
            getchar();
            getchar();
            break;
        }
        case 13:
        {
            if (MaxSubArray(*L) == INFEASIBLE)
                printf("线性表不存在！\n");
            else if (MaxSubArray(*L) == ERROR)
                printf("线性表是空表！\n");
            else
                printf("最大连续子数组和为%d", MaxSubArray(*L));
            getchar();
            getchar();
            break;
        }
        case 14:
        {
            ElemType k;
            printf("请输入K：\n");
            scanf("%d", &k);
            if (SubArrayNum(*L, k) == INFEASIBLE)
                printf("线性表不存在！\n");
            else
                printf("找到了%d个子数组的和等于%d！", SubArrayNum(*L, k), k);
            getchar();
            getchar();
            break;
        }
        case 15:
        {
            if (sortList(*L) == INFEASIBLE)
                printf("线性表不存在！\n");
            else
                printf("排序完成！");
            getchar();
            getchar();
            break;
        }
        case 16:
        {
            char ListName[30];
            printf("请输入新加入线性表的名字！\n");
            scanf("%s", ListName);
            if (AddList(&Lists, ListName) == ERROR)
                printf("插入失败！\n");
            else
                printf("插入成功！\n");
            getchar();
            getchar();
            break;
        }
        case 17:
        {
            char ListName[30];
            printf("请输入要删除线性表的名字！\n");
            scanf("%s", ListName);
            if (RemoveList(&Lists, ListName) == ERROR)
                printf("删除失败！\n");
            else
                printf("删除成功！\n");
            getchar();
            getchar();
            break;
        }
        case 18:
        {
            char ListName[30];
            int k;
            printf("请输入要查找的线性表的名字！\n");
            scanf("%s", ListName);
            if ((k = LocateList(Lists, ListName)) == ERROR)
                printf("没有找到！\n");
            else
                printf("找到了！在第%d个\n", k);
            getchar();
            getchar();
            break;
        }
        case 19:
        {
            FILE *fp;
            printf("请输入文件名！\n");
            char FileName[30];
            scanf("%s", FileName);
            if ((fp = fopen(FileName, "r+")) == NULL)
            {
                printf("文件不存在！");
            }
            else
            {
                int e, i = 0;
                if (InitList(L) == ERROR)
                    printf("线性表已存在！\n");
                else
                {
                    while (fscanf(fp, "%d ", &e) != EOF)
                    {
                        int result = ListInsert(L, ++i, e);
                        if (result == OK)
                            continue;
                        else if (result == ERROR)
                        {
                            printf("读入失败！\n");
                            break;
                        }
                        else if (result == INFEASIBLE)
                        {
                            printf("线性表不存在！\n");
                            break;
                        }
                    }
                    printf("读取成功！\n");
                }
            }
            getchar();
            getchar();
            break;
        }
        case 20:
        {
            FILE *fp;
            printf("请输入文件名！\n");
            char FileName[30];
            scanf("%s", FileName);
            fp = fopen(FileName, "w+");
            if (L->elem == NULL)
                printf("线性表不存在！\n");
            else
            {
                for (int i = 0; i < L->length - 1; i++)
                {
                    fprintf(fp, "%d ", L->elem[i]);
                }
                if (L->length != 0)
                    fprintf(fp, "%d", L->elem[L->length - 1]);
                printf("写入完成！\n");
            }
            getchar();
            getchar();
            break;
        }
        case 21:
        {
            char ch[20];
            printf("请输入想切换的线性表名称，\n如果要切换回一开始的请输入0；");
            scanf("%s", ch);
            if (strcmp(ch, "0") == 0)
            {
                L = &LL;
                printf("操作成功！");
                state = 0;
            }
            else
            {
                int k;
                if ((k = LocateList(Lists, ch)) == ERROR)
                    printf("没有找到！\n");
                else
                {
                    if (state == 0)
                    {
                        LL = *L;
                    }
                    L = &Lists.elem[k - 1].L;
                    printf("操作成功！");
                    state = 1;
                }
            }
            getchar();
            getchar();
            break;
        }
        case 0:
            break;
        } // end of switch
    }     // end of while
    printf("欢迎下次再使用本系统！\n");
} // end of main()

status InitList(SqList *L)
{
    if ((*L).elem != NULL)
        return ERROR;
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if ((*L).elem == NULL)
        exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}

status ListTrabverse(SqList L)
{
    int i;
    printf("\n-----------all elements -----------------------\n");
    for (i = 0; i < L.length; i++)
        printf("%d ", L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}

status DestroyList(SqList *L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if ((*L).elem == NULL)
        return INFEASIBLE;
    free((*L).elem);
    (*L).elem = NULL;
    (*L).listsize = 0;
    (*L).length = 0;
    return OK;
}

status ClearList(SqList *L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if ((*L).elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < (*L).length; i++)
    {
        (*L).elem[i] = 0;
    }
    (*L).length = 0;
    return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    else
        return L.length;
}

status GetElem(SqList L, int i, ElemType *e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    if (i > L.length || i < 1)
        return ERROR;
    else
    {
        *e = L.elem[i - 1];
        return OK;
    }
}

int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            return i + 1;
    }
    return ERROR;
}

status PriorElem(SqList L, ElemType e, ElemType *pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            break;
    }
    if (i == 0)
        return ERROR;
    if (L.elem[i] == e)
    {
        *pre = L.elem[i - 1];
        return OK;
    }
    else
        return ERROR;
}

status NextElem(SqList L, ElemType e, ElemType *next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            break;
    }
    if (i >= L.length - 1)
        return ERROR;
    else
    {
        *next = L.elem[i + 1];
        return OK;
    }
}

status ListInsert(SqList *L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if ((*L).elem == NULL)
        return INFEASIBLE;
    if (i - 1 > (*L).length || i <= 0)
        return ERROR;
    if ((*L).length >= (*L).listsize)
    {
        (*L).elem = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        (*L).listsize += LISTINCREMENT;
    }
    for (int j = (*L).length; j >= i; j--)
    {
        (*L).elem[j] = (*L).elem[j - 1];
    }
    (*L).elem[i - 1] = e;
    (*L).length++;
    return OK;
}

status ListDelete(SqList *L, int i, ElemType *e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if ((*L).elem == NULL)
        return INFEASIBLE;
    if (i > (*L).length || i <= 0)
        return ERROR;
    *e = (*L).elem[i - 1];
    for (int j = i - 1; j < (*L).length; j++)
    {
        (*L).elem[j] = (*L).elem[j + 1];
    }
    (*L).length--;
    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length - 1; i++)
    {
        printf("%d ", L.elem[i]);
    }
    if (L.length != 0)
        printf("%d", L.elem[L.length - 1]);
    return OK;
}

status MaxSubArray(SqList L)
{
    if (L.elem == NULL)
        return INFEASIBLE;
    if (L.length == 0)
        return ERROR;
    ElemType a[101];
    for (int i = 0; i < L.length; i++)
    {
        a[i] = 0;
    }
    a[0] = L.elem[0];
    for (int i = 1; i < L.length; i++)
    {
        a[i] = max(a[i - 1] + L.elem[i], L.elem[i]);
    }
    ElemType ans = a[0];
    for (int i = 0; i < L.length; i++)
    {
        if (a[i] > ans)
            ans = a[i];
    }
    return ans;
}

status SubArrayNum(SqList L, ElemType k)
{
    if (L.elem == NULL)
        return INFEASIBLE;
    int cnt = 0, sum = 0;
    for (int i = 0; i < L.length; i++)
    {
        for (int j = i; j < L.length; j++)
        {
            for (int k = i; k <= j; k++)
            {
                sum += L.elem[k];
            }
            if (sum == k)
                cnt++;
            sum = 0;
        }
    }
    return cnt;
}

status sortList(SqList L)
{
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = L.length - 1; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (L.elem[j] > L.elem[j + 1])
            {
                ElemType t;
                t = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = t;
            }
        }
    }
    return OK;
}

status AddList(LISTS *Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    if ((*Lists).length >= 10)
        return ERROR;
    for (int i = 0; i < (*Lists).length; i++)
    {
        if (strcmp((*Lists).elem[i].name, ListName) == 0)
            return ERROR;
    }
    ElemType *newbase;
    newbase = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!newbase)
        return ERROR;
    (*Lists).elem[(*Lists).length].L.elem = newbase;
    (*Lists).elem[(*Lists).length].L.length = 0;
    (*Lists).elem[(*Lists).length].L.listsize = LIST_INIT_SIZE;
    for (int i = 0; i < 30; i++)
    {
        (*Lists).elem[(*Lists).length].name[i] = ListName[i];
    }
    (*Lists).length++;
    return OK;
}

status RemoveList(LISTS *Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i, j;
    if ((*Lists).length == 0)
        return ERROR;
    for (i = 0; i < (*Lists).length; i++)
    {
        if (strcmp((*Lists).elem[i].name, ListName) == 0)
        {
            for (j = i; j < (*Lists).length - 1; j++)
            {
                (*Lists).elem[j] = (*Lists).elem[j + 1];
            }
            (*Lists).length--;
            return OK;
        }
    }
    return ERROR;
}

status LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int state = 0, i, j;
    for (i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return i + 1;
    }
    return 0;
}