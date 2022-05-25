#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
typedef struct
{
    KeyType key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode
{                            //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode *nextarc; //下一个表结点指针
} ArcNode;
typedef struct VNode
{                      //头结点及其数组类型定义
    VertexType data;   //顶点信息
    ArcNode *firstarc; //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                       //邻接表的类型定义
    AdjList vertices;   //头结点数组
    int vexnum, arcnum; //顶点数、弧数
    GraphKind kind;     //图的类型
} ALGraph;

typedef struct 
{
    ALGraph elem[10];
    char name[10][20];
    int length;
} GRAPHS;

void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}

status CreateCraph(ALGraph *G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph *G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph *G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph *G, VertexType v);
status DeleteVex(ALGraph *G, KeyType v);
status InsertArc(ALGraph *G, KeyType v, KeyType w);
status DeleteArc(ALGraph *G, KeyType v, KeyType w);
status DFSTraverse(ALGraph *G, void (*visit)(VertexType));
status BFSTraverse(ALGraph *G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph *G, char FileName[]);
int* VerticesSetLessThanK(ALGraph G,KeyType e,int d);
int ShortestPathLength(ALGraph G,KeyType v,KeyType w);
status ConnectedComponentsNums(G);

int main(void)
{
    ALGraph G_L,*G=&G_L,*Original_G;
    G->vexnum = 0;
    G->arcnum = 0;
    G->kind = 1;
    GRAPHS GG;
    GG.length = 0;
    int op = 1,state=0;
    while (op)
    {
        printf("1. CreateGraph      2. DestroyGraph       3. LocateVex\n");
        printf("4. PutVex           5. FirstAdjVex        6. NextAdjVex\n");
        printf("7. InsertVex        8. DeleteVex          9. InsertArc\n");
        printf("10. DeleteArc       11. DFSTraverse       12. BFSTraverse\n");
        printf("13. SaveGraph       14. LoadGraph         15. AddGraph\n");
        printf("16. DeleteGraph     17. LocateGraph       18. SwitchGraph\n");
        printf("19. VerticesSetLessThanK          20. ShortestPathLength\n");
        printf("21.ConnectedComponentsNums        22. SwitchGraph");
        printf("Please choose one you like from 1 to ?:\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
        {
            printf("Please Input the vexs and arcs:\n");
            VertexType V[10];
            KeyType VR[100][2];
            int a=1, b, cnt = 0;
            char c[20];
            while (a != -1)
            {
                scanf("%d %s", &a, c);
                V[cnt].key = a;
                strcpy(V[cnt++].others, c);
            }
            cnt = 0;a=1;
            while (a != -1)
            {
                scanf("%d %d", &a, &b);
                VR[cnt][0] = a;
                VR[cnt++][1] = b;
            }
            int k;
            if ((k=CreateCraph(G, V, VR)) == OK)
                printf("Success!");
            else if(k == ERROR) printf("ERROR INPUT!");
            else printf("Already exist!");
            getchar();
            getchar();
            break;
        }
        case 2:
        {
            if (DestroyGraph(G) == OK)
                printf("Success!");
            else
                printf("Graph not exist!");
            getchar();
            getchar();
            break;
        }
        case 3:
        {
            int u;
            printf("Input the key:\n");
            scanf("%d", &u);
            if (LocateVex(*G, u) == ERROR)
                printf("Not found!");
            else
                printf("Found!It's the %d one!", LocateVex(*G, u));
            getchar();
            getchar();
            break;
        }
        case 4:
        {
            VertexType T;
            KeyType d;
            printf("Input the key you want to change and the value you want to input:\n");
            scanf("%d %d %s", &d, &T.key, T.others);
            if (PutVex(G, d, T) == OK)
                printf("Success!");
            else
                printf("Fail!");
            getchar();
            getchar();
            break;
        }
        case 5:
        {
            printf("Input the key:");
            int u;
            scanf("%d", u);
            if (FirstAdjVex(*G, u) != ERROR)
                printf("Found! It's %d.", FirstAdjVex(*G, u));
            else
                printf("Not found!");
            getchar();
            getchar();
            break;
        }
        case 6:
        {
            printf("Input the key and the adj key you want to find:");
            int u, v;
            scanf("%d %d", &u, &v);
            if (NextAdjVex(*G, u, v) != ERROR)
                printf("It's %d.", NextAdjVex(*G, u, v));
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 7:
        {
            printf("Input the value you want to add:\n");
            VertexType T;
            scanf("%d %s", &T.key, T.others);
            if (InsertVex(G, T) == OK)
                printf("Success!");
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 8:
        {
            printf("Input the key:");
            KeyType v;
            scanf("%d", &v);
            if (DeleteVex(G, v) == OK)
                printf("Success!\n");
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 9:
        {
            printf("Input the key1 and key2:\n");
            KeyType u, v;
            scanf("%d %d", &u, &v);
            if (InsertArc(G, u, v) == OK)
                printf("Success!");
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 10:
        {
            printf("Input the key1 and key2:\n");
            KeyType u, v;
            scanf("%d %d", &u, &v);
            if (DeleteArc(G, u, v) == OK)
                printf("Success!");
            else
                printf("Failed");
            getchar();
            getchar();
            break;
        }
        case 11:
        {
            DFSTraverse(G, visit);
            getchar();
            getchar();
            break;
        }
        case 12:
        {
            BFSTraverse(G, visit);
            getchar();
            getchar();
            break;
        }
        case 13:
        {
            printf("Input the filename:\n");
            char filename[20];
            scanf("%s",filename);
            if (SaveGraph(*G, filename) == OK)
                printf("Success!");
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 14:
        {
            printf("Input the filename:\n");
            char filename[20];
            scanf("%s",filename);
            if (LoadGraph(G, filename) == OK)
                printf("Success!");
            else
                printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 15:
        {
            int type;
            char name[20];
            printf("Input the type of Graph:0.DG,1.DN,2.UDG,3.UDN\n");
            scanf("%d",&type);
            if(type>3||type<0) printf("Wrong Input!");
            else 
            {
                printf("Input the name of graph:");
                scanf("%s",name);
                if(AddGraph(&GG,type,name)==OK) printf("Success!");
                else printf("Failed!");
            }
            getchar();
            getchar();
            break;
        }
        case 16:
        {
            char name[20];
            printf("Input the name of graph:");
            scanf("%s",name);
            if(DeleteGraph(&GG,name)==OK) printf("Success!");
            else printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 17:
        {
            char name[20];
            printf("Input the name of graph:");
            scanf("%s",name);
            if(LocateGraph(GG,name)!=ERROR) printf("It's the %d one!",LocateGraph(GG,name));
            else printf("Failed!");
            getchar();
            getchar();
            break;
        }
        case 18:
        {
            char graphname[10];
            printf("Input the graph you want to switch:\ntype 0 to switch to the original graph:");
            scanf("%s",graphname);
            if(strcmp(graphname,"0")==0)
            {
                G=Original_G;
                printf("Success!");
            }
            else{
                Original_G=G;
                G=&GG.elem[LocateGraph(GG,graphname)-1];
                printf("Success!");
            }
            getchar();
            getchar();
            break;
        }
        case 19:
        {
            int e,d,*vex,i=0;
            vex=(int *)malloc(sizeof(int)*10);
            printf("Input the key and the distance:");
            scanf("%d %d",&e,&d);
            vex = VerticesSetLessThanK(*G,e,d);
            while(*(vex+i)!=e)
            {
                
                printf("%d ",*(vex+i));
                i++;
            }
            getchar();
            getchar();
            break;
        }
        case 20:
        {
            int e,d,i=0,state1=0,state2=0;
            printf("Input the keys:");
            scanf("%d %d",&e,&d);
            for(i=0;i<G->vexnum;i++)
            {
                if(G->vertices[i].data.key==e) state1=1;
                if(G->vertices[i].data.key==d) state2=1;
            }
            if(state1&&state2) 
                printf("%d",ShortestPathLength(*G,e,d));
            else printf("Error Input!");
            getchar();
            getchar();
            break;
        }
        case 21:
        {
            printf("ConnectedComponentsNums is %d",ConnectedComponentsNums(*G));
            getchar();
            getchar();
            break;
        }
        }
    }
}

status CreateCraph(ALGraph *G, VertexType V[], KeyType VR[][2])
{
    int i = 0;
    if ((*G).vexnum > 0)
        return INFEASIBLE;
    while (V[i].key != -1)
    {
        (*G).vertices[i].data.key = V[i].key;
        strcpy((*G).vertices[i].data.others, V[i].others);
        (*G).vertices[i].firstarc = NULL;
        i++;
    }
    int j = 0, n = i;
    while (VR[j][0] != -1)
    {
        int i, k;
        for (i = 0; i < n; i++)
        {
            if ((*G).vertices[i].data.key == VR[j][0])
                break;
        }
        if (i == n)
            return ERROR;
        for (k = 0; k < n; k++)
        {
            if ((*G).vertices[k].data.key == VR[j][1])
                break;
        }
        if (i == n)
            return ERROR;

        if ((*G).vertices[i].firstarc == NULL)
        {
            (*G).vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[i].firstarc->nextarc = NULL;
            (*G).vertices[i].firstarc->adjvex = k;
        }
        else
        {
            ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode)), *q = (*G).vertices[i].firstarc;
            p->nextarc = q;
            p->adjvex = k;
            (*G).vertices[i].firstarc = p;
        }
        if ((*G).vertices[k].firstarc == NULL)
        {
            (*G).vertices[k].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[k].firstarc->nextarc = NULL;
            (*G).vertices[k].firstarc->adjvex = i;
        }
        else
        {
            ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode)), *q = (*G).vertices[k].firstarc;
            p->nextarc = q;
            p->adjvex = i;
            (*G).vertices[k].firstarc = p;
        }
        j++;
    }
    (*G).vexnum = n;
    (*G).arcnum = j;
    if (n > 20 || n <= 0)
        return ERROR;
    return OK;
}

status DestroyGraph(ALGraph *G)
{
    if ((*G).vexnum == 0)
        return INFEASIBLE;
    for (int i = 0; i < (*G).vexnum; i++)
    {
        ArcNode *p = (*G).vertices[i].firstarc, *q = NULL;
        if (p == NULL)
            continue;
        while (p->nextarc)
        {
            q = p;
            p = p->nextarc;
            free(q);
        }
        free(p);
        (*G).vertices[i].firstarc = NULL;
    }
    (*G).vexnum = 0;
    (*G).arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
            return i;
    }
    return ERROR;
}

status PutVex(ALGraph *G, KeyType u, VertexType value)
{
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if ((*G).vertices[i].data.key == value.key)
            return ERROR;
    }
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if ((*G).vertices[i].data.key == u)
        {
            (*G).vertices[i].data.key = value.key;
            strcpy((*G).vertices[i].data.others, value.others);
            return OK;
        }
    }
    return ERROR;
}

int FirstAdjVex(ALGraph G, KeyType u)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
        {
            if (G.vertices[i].firstarc == NULL)
                return ERROR;
            return G.vertices[i].firstarc->adjvex;
        }
    }
    return ERROR;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *p = G.vertices[i].firstarc;
            while (p)
            {
                if (G.vertices[p->adjvex].data.key == w)
                {
                    p = p->nextarc;
                    if (p == NULL)
                        return -1;
                    else
                    {
                        return p->adjvex;
                    }
                }
                p = p->nextarc;
            }
            return -1;
        }
    }
    return -1;
}

status InsertVex(ALGraph *G, VertexType v)
{
    if ((*G).vexnum >= 20)
        return ERROR;
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if ((*G).vertices[i].data.key == v.key)
            return ERROR;
    }
    (*G).vertices[(*G).vexnum].data.key = v.key;
    strcpy((*G).vertices[(*G).vexnum].data.others, v.others);
    (*G).vexnum++;
    return OK;
}

status DeleteVex(ALGraph *G, KeyType v)
{
    int i, j;
    ArcNode *p, *q;
    j = LocateVex((*G), v);
    if (j == -1) //要删除的顶点不存在
        return ERROR;
    else if ((*G).vexnum == 1) //只剩下一个顶点
        return ERROR;
    p = (*G).vertices[j].firstarc;
    while (p)
    {
        q = p;
        p = p->nextarc;
        free(q);
        (*G).arcnum--;
    } //顶点相关的弧删除完成
    (*G).vexnum--;
    for (i = j; i < (*G).vexnum; i++)
        (*G).vertices[i] = (*G).vertices[i + 1];
    for (i = 0; i < (*G).vexnum; i++)
    {
        p = (*G).vertices[i].firstarc;
        while (p)
        {
            if (p->adjvex == j)
            {
                if (p == (*G).vertices[i].firstarc)
                {
                    (*G).vertices[i].firstarc = p->nextarc;
                    free(p);
                    p = (*G).vertices[i].firstarc;
                }
                else
                {
                    q->nextarc = p->nextarc;
                    free(p);
                    p = q->nextarc;
                }
            }
            else
            {
                if (p->adjvex > j)
                    p->adjvex--; //顶点的位置编号减1
                q = p;
                p = p->nextarc; //只要没找到v顶点,q在p前一个位置
            }
        }
    }
    return OK;
}

status InsertArc(ALGraph *G, KeyType v, KeyType w)
{
    int a = -1, b = -1;
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if ((*G).vertices[i].data.key == v)
            a = i;
        if ((*G).vertices[i].data.key == w)
            b = i;
    }
    if (a == -1 || b == -1)
        return ERROR;
    ArcNode *r = (*G).vertices[a].firstarc;
    while (r)
    {
        if (r->adjvex == b)
            return ERROR;
        r = r->nextarc;
    }
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = b;
    p->nextarc = (*G).vertices[a].firstarc;
    (*G).vertices[a].firstarc = p;
    ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
    q->adjvex = a;
    q->nextarc = (*G).vertices[b].firstarc;
    (*G).vertices[b].firstarc = q;
    (*G).arcnum++;
    return OK;
}

status DeleteArc(ALGraph *G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int a = -1, b = -1;
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if ((*G).vertices[i].data.key == v)
            a = i;
        if ((*G).vertices[i].data.key == w)
            b = i;
    }
    if (a == -1 || b == -1)
        return ERROR;
    ArcNode *r = (*G).vertices[a].firstarc;
    int state = 0;
    while (r)
    {
        if (r->adjvex == b)
            state = 1;
        r = r->nextarc;
    }
    (*G).arcnum--;
    if (state == 0)
        return ERROR;
    else
    {
        ArcNode *p = (*G).vertices[a].firstarc;
        if (p->adjvex == b)
        {
            (*G).vertices[a].firstarc = (*G).vertices[a].firstarc->nextarc;
            free(p);
        }
        else
        {
            while (p->nextarc)
            {
                if (p->nextarc->adjvex == b)
                {
                    ArcNode *s = p->nextarc;
                    p->nextarc = p->nextarc->nextarc;
                    free(s);
                }
                else
                    p = p->nextarc;
            }
        }
        ArcNode *q = (*G).vertices[b].firstarc;
        if (q->adjvex == a)
        {
            (*G).vertices[b].firstarc = (*G).vertices[b].firstarc->nextarc;
            free(q);
        }
        else
        {
            while (q->nextarc)
            {
                if (q->nextarc->adjvex == a)
                {
                    ArcNode *s = q->nextarc;
                    q->nextarc = q->nextarc->nextarc;
                    free(s);
                }
                else
                    q = q->nextarc;
            }
        }
    }
    return OK;
}

int state[10];
status DFS(ALGraph *G, int i, void (*visit)(VertexType))
{
    if (state[i] == 0)
    {
        state[i] = 1;
        visit((*G).vertices[i].data);
    }
    ArcNode *p = (*G).vertices[i].firstarc;
    while (p)
    {
        if (state[p->adjvex] == 0)
        {
            DFS(&(*G), p->adjvex, visit);
        }
        else
            p = p->nextarc;
    }
}

status DFSTraverse(ALGraph *G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < (*G).vexnum; i++)
    {
        DFS(&(*G), i, visit);
    }
    /********** End **********/
}

int state2[10];
int queue[10], top = 0, tail = 0;
status BFSTraverse(ALGraph *G, void (*visit)(VertexType))
{
    for (int i = 0; i < (*G).vexnum; i++)
    {
        if (state2[i] == 0)
        {
            state2[i] = 1;
            queue[tail++] = i;
        }
        while (top < tail)
        {
            ArcNode *p = (*G).vertices[top++].firstarc;
            while (p)
            {
                if (state2[p->adjvex] == 0)
                {
                    state2[p->adjvex] = 1;
                    queue[tail++] = p->adjvex;
                }
                p = p->nextarc;
            }
        }
    }
    for (int i = 0; i < (*G).vexnum; i++)
    {
        visit((*G).vertices[queue[i]].data);
    }
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp;
    if ((fp = fopen(FileName, "w+")) == NULL)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, " -1 nil ");
    int vv[100][2], fin[100][2], cnt = 0, num = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        if (p == NULL)
            continue;
        else
        {
            while (p != NULL)
            {
                vv[cnt][0] = G.vertices[i].data.key;
                vv[cnt++][1] = G.vertices[p->adjvex].data.key;
                p = p->nextarc;
            }
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        if (vv[i][0] > vv[i][1])
        {
            vv[i][0] = 0;
            vv[i][1] = 0;
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        if (vv[i][0] != 0)
        {
            fin[num][0] = vv[i][0];
            fin[num++][1] = vv[i][1];
        }
    }
    for (int i = num - 1; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (fin[j][0] > fin[j + 1][0])
            {
                int a = fin[j][0], b = fin[j][1];
                fin[j][0] = fin[j + 1][0];
                fin[j][1] = fin[j + 1][1];
                fin[j + 1][0] = a;
                fin[j + 1][1] = b;
            }
            else if (fin[j][0] == fin[j + 1][0])
            {
                if (fin[j][1] > fin[j + 1][1])
                {
                    int a = fin[j][0], b = fin[j][1];
                    fin[j][0] = fin[j + 1][0];
                    fin[j][1] = fin[j + 1][1];
                    fin[j + 1][0] = a;
                    fin[j + 1][1] = b;
                }
            }
        }
    }
    for (int i = 0; i < num; i++)
    {
        fprintf(fp, " %d %d ", fin[i][0], fin[i][1]);
    }
    fprintf(fp, " -1 -1 ");
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadGraph(ALGraph *G, char FileName[])
{
    (*G).vexnum=0;
    (*G).arcnum=0;
    FILE *fp;
    if((fp=fopen(FileName,"r+"))==NULL) return ERROR;
    int a;
    char ch[20];
    fscanf(fp,"%d %s", &a,ch);
    while(a!=-1)
    {
        (*G).vertices[(*G).vexnum].data.key=a;
        strcpy((*G).vertices[(*G).vexnum].data.others,ch);
        (*G).vertices[(*G).vexnum].firstarc=NULL;
        (*G).vexnum++;
        fscanf(fp,"%d %s", &a,ch);
    }
    int b;
    fscanf(fp, "%d %d", &a, &b);
    while(a!=-1)
    {
        int i,j;
        for(i=0;i<(*G).vexnum;i++)
        {
            if((*G).vertices[i].data.key==a) break;
        }
        for(j=0;j<(*G).vexnum;j++)
        {
            if((*G).vertices[j].data.key==b) break;
        }
        ArcNode *p=(*G).vertices[i].firstarc;
        if(p==NULL)
        {
            p=(ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[i].firstarc=p;
            p->nextarc=NULL;
            p->adjvex=j;
        }
        else
        {
            p=(*G).vertices[i].firstarc;
            (*G).vertices[i].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[i].firstarc->nextarc=p;
            (*G).vertices[i].firstarc->adjvex=j;
        }
        ArcNode *q=(*G).vertices[j].firstarc;
        if(q==NULL)
        {
            q=(ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[j].firstarc=q;
            q->nextarc=NULL;
            q->adjvex=i;
        }
        else
        {
            q=(*G).vertices[j].firstarc;
            (*G).vertices[j].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
            (*G).vertices[j].firstarc->nextarc=q;
            (*G).vertices[j].firstarc->adjvex=i;
        }
        (*G).arcnum++;
        fscanf(fp, "%d %d", &a, &b);
    }
    for(int i=0;i<(*G).vexnum;i++)
    {
        printf("%d %s ",(*G).vertices[i].data.key,(*G).vertices[i].data.others);
        ArcNode *p=(*G).vertices[i].firstarc;
        while(p!=NULL)
        {
            printf(" %d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
    fclose(fp);
    return OK;
}

status AddGraph(GRAPHS *GG,int type,char name[])
{
    if(GG->length>10) return INFEASIBLE;
    ALGraph *p;
    p = (ALGraph *)malloc(sizeof(ALGraph));
    p->kind=type;
    p->arcnum=0;
    p->vexnum=0;
    GG->elem[GG->length]=(*p);
    strcpy(GG->name[GG->length],name);
    (GG->length)++;
    return OK;
}

status DeleteGraph(GRAPHS *GG, char name[])
{
    int i;
    for(i=0;i<GG->length;i++)
    {
        if(strcmp(GG->name[i],name)==0) break;
    }
    if(i == GG->length) return ERROR;
    for(int j=i;j<GG->length;j++)
    {
        GG->elem[j]=GG->elem[j+1];
        strcpy(GG->name[j],GG->name[j+1]);
    }
    GG->length--;
    return OK;
}

status LocateGraph(GRAPHS GG, char name[])
{
    int i;
    for(i=0;i<GG.length;i++)
    {
        if(strcmp(GG.name[i],name)==0) break;
    }
    if(i == GG.length) return ERROR;
    return i+1;
}

int cnt=0;
int vex_[10],v_a[10];
int * VerticesSetLessThanK(ALGraph G,KeyType e,int d)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key == e) break;
    }
    if(d < 0||v_a[i]==1) return NULL;
    ArcNode *p=G.vertices[i].firstarc;
    while(p)
    {
        VerticesSetLessThanK(G,G.vertices[p->adjvex].data.key,d-1);
        p=p->nextarc;
    }
    vex_[cnt++]=G.vertices[i].data.key;
    v_a[i]=1;
    return vex_;
}

int v_b[10];
int ShortestPathLength(ALGraph G,KeyType v,KeyType w)
{
    if(v==w) return 0;
    int i,k;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key == v) break;
    }
    if(v_b[i]!=0) return 100;
    v_b[i]=1;
    ArcNode *p=G.vertices[i].firstarc;
    int min=100;
    while(p)
    {
        min=(min<(k=ShortestPathLength(G,G.vertices[p->adjvex].data.key,w)) ? min : k);
        p=p->nextarc;
    }
    v_b[i]=0;
    return 1+min;
}

int v_c[10];

int  FindConnected(ALGraph G,int i)
{
    if(v_c[i]!=0) return 0;
    v_c[i]=1; 
    ArcNode *p=G.vertices[i].firstarc;
    while(p)
    {
        FindConnected(G,p->adjvex);
        p=p->nextarc;
    }
    return 1;
}
status ConnectedComponentsNums(ALGraph G)
{
    int num=0;
    for(int i=0;i<G.vexnum;i++)
    {
        num+=FindConnected(G,i);
    }
    return num;
}