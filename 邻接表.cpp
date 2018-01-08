#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef char VertexType;                                    //数据元素类型定义

#define MAX_VERTEX_NUM 20                                   //顶点最大个数

typedef struct ArcNode{
    int adjvex;                                             //该弧所指向的结点的位置
    struct ArcNode *nextarc;                                //指向下一条弧的指针
} ArcNode;
typedef struct VNode{
    int num;                                                //顶点序号
    VertexType data;                                        //顶点信息(char)
    ArcNode *firstarc;                                      //指向第一条依附该顶点的弧的指针
} VNode;
typedef struct{
    int vexnum, arcnum;                                     //图的当前顶点数和弧数
} ALGraph;
status CreateGraph(char *vex, char *arc);                   //创建图
status DestroyGraph();                                      //销毁图
int LocateVex(VertexType u);                                //查找顶点
VertexType GetVex(int x);                                   //获得顶点值(根据存放位置)
VertexType GetVex2(int x);                                  //获得顶点值(根据索引)
void PutVex(int v,VertexType value);                        //顶点赋值
int FirstAdjVex(int v);                                     //获得第一邻接点
int NextAdjVex(int v, int w);                               //获得下一邻接点
status InsertVex(VertexType v);                             //插入顶点
status DeleteVex(VertexType v);                             //删除顶点
status InsertArc(VertexType v, VertexType u);               //插入弧
status DeleteArc(VertexType v, VertexType u);               //删除弧
status DFSTraverse();                                       //深度优先搜索遍历
status BFSTraverse();                                       //广深度优先搜索遍历
void ShowVexArc();                                          //显示顶点与弧
void save(char filename[20]);
void read(char filename[20]);
ALGraph G={};
VNode AdjList[MAX_VERTEX_NUM];
int main(void)
{
    FILE *fp = NULL;
    char filename[20];
/*用户指定文件对图进行初始化*/
    printf("是否指定文件对图初始化？[n]/y\n");
    if (getchar() == 'y')
    {
        printf("Input filename:");
        scanf("%s", filename);
        if (fp = fopen(filename, "r")){
            fclose(fp);
            read(filename);
        }
        else{
            printf("无法打开相关文件，图未初始化！\n");
            system("pause");
        }
    }
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("                     邻接表 菜单                 \n");
        printf("-------------------------------------------------\n");
        printf("    	 1. 创建图             9. 删除顶点\n");
        printf("    	 2. 销毁图            10. 插入弧\n");
        printf("    	 3. 查找顶点          11. 删除弧\n");
        printf("    	 4. 获得顶点值        12. 深度优先搜索遍历\n");
        printf("    	 5. 顶点赋值          13. 广深度优先搜索遍历\n");
        printf("    	 6. 获得第一邻接点    14. 显示顶点与弧\n");
        printf("    	 7. 获得下一邻接点    15. 切换图\n");
        printf("         8. 插入顶点           0. 退出\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        /*创建图*/
        case 1:{
            char vex[100];
            printf("请给出各顶点:\n");
            fgets(vex,100,stdin);
            char arc[200];
            printf("请给出边的集合，用边的顶点表示即可（示例：边a->b,c->d,输入abcd即可）:\n");
            fgets(arc,200,stdin);
            if(CreateGraph(vex, arc)==OK){
                printf("创建成功！\n");
            }
            else{
                printf("创建失败！\n");
            }
            system("pause");
            break;
        }
        /*销毁图*/
        case 2:{
            DestroyGraph();
            printf("销毁成功！\n");
            system("pause");
            break;
        }
        /*查找顶点*/
        case 3:{
            printf("请输入查找顶点的数据！\n");
            VertexType u;
            scanf("%c",&u);
            int result=LocateVex(u);
            if(result==INFEASTABLE)
                printf("未找到相应节点！\n");
            else{
                printf("节点%c储存的顺序为%d！\n",u,result+1);
            }
            system("pause");
            break;
        }
        /*获得顶点值*/
        case 4:{
            int x;
            VertexType result;
            printf("请输入查找值！\n");
            scanf("%d",&x);
            result=GetVex(x-1);
            if(result!=ERROR)
                printf("查找到的数据为%c！\n",result);
            else printf("找不到相应的节点！\n");
            system("pause");
            break;
        }
        /*顶点赋值*/
        case 5:{
            int v;VertexType value;
            printf("请输入顶点储存的位置！\n");
            scanf("%d",&v);getchar();
            printf("请输入所赋的值！\n");
            scanf("%c",&value);
            PutVex(v,value);
            system("pause");
            break;
        }
        /*获得第一邻接点*/
        case 6:{
            printf("请输入存放的位置！\n");
            int loca;
            scanf("%d",&loca);
            int result=FirstAdjVex(loca);
            if(result==ERROR)
                printf("请输入正确的位置！\n");
            else if(result==INFEASTABLE)
                printf("该节点无邻接节点！\n");
            else
                printf("该节点的位置为%d！\n",result);
            system("pause");
            break;
        }
        /*获得下一邻接点*/
        case 7:{
            int v,w;
            printf("请输入顶点存储位置！\n");
            scanf("%d",&v);
            printf("请输入邻接节点序号！\n");
            scanf("%d",&w);
            int result=NextAdjVex(v,w);
            if(result==-1)
                printf("下一邻接节点不存在！\n");
            else if(result==ERROR)
                printf("原节点无邻接节点！\n");
            else printf("下一邻接节点位置为%d\n",result);
            system("pause");
            break;
        }
        /*插入顶点*/
        case 8:{
            VertexType v;
            printf("请输入需要插入的顶点！\n");
            scanf("%c",&v);
            int result=InsertVex(v);
            if(result==ERROR)
                printf("该顶点已存在！\n");
            else printf("插入成功！\n ");
            system("pause");
            break;
        }
        /*删除顶点*/
        case 9:{
            VertexType v;
            printf("请输入需要删除的顶点！\n");
            scanf("%c",&v);
            int result=DeleteVex(v);
            if(result==OK)
                printf("删除成功！\n");
            else printf("删除失败！\n");
            system("pause");
            break;
        }
        /*插入弧*/
        case 10:{
            VertexType v,u;
            printf("请选择插入弧的顶点！(例如：a b)\n");
            scanf("%c %c",&v,&u);
            int result=InsertArc(v,u);
            if(result==ERROR)
                printf("插入失败！\n");
            else
                printf("插入成功！\n");
            system("pause");
            break;
        }
        /*删除弧*/
        case 11:{
            VertexType v,u;
            printf("请输入需要删除的弧(例如：a b)！\n");
            scanf("%c %c",&v,&u);
            int result=DeleteArc(v,u);
            if(result==ERROR)
                printf("删除失败！\n");
            else
                printf("删除成功！\n");
            system("pause");
            break;
        }
        /*深度优先搜索遍历*/
        case 12:{
            int result=DFSTraverse();
            if(result==ERROR)
                printf("图不存在！\n");
            system("pause");
            break;
        }
        /*广深度优先搜索遍历*/
        case 13:{
            int result=BFSTraverse();
            if(result==ERROR)
                printf("图不存在！\n");
            system("pause");
            break;
        }
        /*显示顶点与弧*/
        case 14:{
            ShowVexArc();
            system("pause");
            break;
        }
        /*切换图*/
        case 15:{
            printf("是否要保存图数据？y/[n]\n");
            if (getchar() == 'y')
            {
                printf("请输入文件名：");
                if (scanf("%s", filename)){
                    save(filename);
                }
                else{
                    printf("保存失败！\n");
                }
            }
            printf("是否指定文件对图初始化？[n]/y\n");getchar();
            if (getchar() == 'y')
            {
                printf("Input filename:");
                scanf("%s", filename);
                if (fp = fopen(filename, "r")){
                    fclose(fp);
                    read(filename);
                }
                else{
                    printf("无法打开相关文件，图未初始化！\n");
                    system("pause");
                }
            }
                system("pause");
                break;
            }
        /*退出*/
        case 0:{
            printf("是否要保存图数据？y/[n]\n");
            if (getchar() == 'y')
            {
                printf("请输入文件名：");
                if (scanf("%s", filename)){
                    save(filename);
                }
                else{
                    printf("保存失败！\n");
                }
                system("pause");
            }
            break;
        }
        default:
            break;
        }
    }
}

//根据用户要求构造图
status CreateGraph(char *vex, char *arc){
    if(G.arcnum!=0||G.vexnum!=0)
        return ERROR;
    int i=0;
    while(vex[i]!='\n'){
        AdjList[i].data=vex[i];
        AdjList[i].firstarc=NULL;
        AdjList[i].num=i++;
        G.vexnum++;
    }
    int j=0;
    while(arc[j]!='\n'){
        InsertArc(arc[j],arc[j+1]);
        j+=2;
    }
    return OK;
}

//初始条件：图G存在。
//操作结果：销毁图G。
status DestroyGraph(){
    ArcNode *p=NULL,*q=NULL;
    for(int i=0;i<G.vexnum;i++){
        p=AdjList[i].firstarc;
        q=p;
        while(p){
            p=p->nextarc;
            free(q);
            q=p;
        }
        AdjList[i]={0};
    }
    G.arcnum=0;G.vexnum=0;
    return OK;
}

//初始条件：图G存在，u和G中的顶点具有相同特征。
//操作结果：若u在图G中存在，返回顶点u的位置信息，否则返回-1。
int LocateVex(VertexType u){
    int i=0;
    while(i<G.vexnum){
        if(AdjList[i].data==u)
            return i;
        i++;
    }
    return INFEASTABLE;
}

//初始条件：图G存在，x是G中的某个顶点存放位置.
//操作结果：返回顶点值。
VertexType GetVex(int x){
    if(x<0||x>G.vexnum-1) return ERROR;
    else return AdjList[x].data;
}

//初始条件：图G存在，x是G中的某个顶点索引.
//操作结果：返回v顶点值。
VertexType GetVex2(int x){
    int i=0;
    for(i=0;i<G.vexnum;i++){
        if(AdjList[i].num==x)
            return AdjList[i].data;
    }
    if((i==G.vexnum-1)&&(AdjList[i].num!=x))
        return ERROR;
}

//初始条件：图G存在，v是G中的某个顶点。
//操作结果：对v赋值value。
void PutVex(int v,VertexType value){
    if(v>=1&&v<=G.vexnum){
        AdjList[v-1].data=value;
        printf("赋值成功！\n");
    }
}

//初始条件：图G存在，v是G中的某个顶点。
//操作结果：返回v的第一个邻接顶点的位置，如果v没有邻接顶点，返回INFEASTABLE。
int FirstAdjVex(int v){
    if(v>0&&v<=G.vexnum){
        ArcNode *p = AdjList[v-1].firstarc;
        if(p){
            VertexType x=GetVex2(p->adjvex);
            return LocateVex(x)+1;
        }
        else return INFEASTABLE;
    }
    else
        return ERROR;
}

//初始条件：图G存在，v是G的一个顶点位置, w是v的邻接顶点的位置。
//操作结果：返回v的（相对于w）下一个邻接顶点的位置，如果w是最后一个邻接顶点，返回-1
int NextAdjVex(int v, int w){
    int flag=1;
    ArcNode *p=AdjList[v-1].firstarc;
    if(p==NULL) return ERROR;
    else{
        if(w==0){
            return LocateVex(GetVex2(p->adjvex))+1;
        }
        else{
            while(p){
                if(flag==w){
                    if(p->nextarc)
                        return LocateVex(GetVex2(p->nextarc->adjvex))+1;
                    else return -1;
                }
                else{
                    flag++;
                    p=p->nextarc;
                }
            }
            return -1;
        }
    }
}

//初始条件：图G存在，v和G中的顶点具有相同特征。
//操作结果：在图G中增加新顶点v。
status InsertVex(VertexType v){
    int flag=0;
    for(int i=0;i<G.vexnum;i++){
        flag = (flag>AdjList[i].num)?flag:AdjList[i].num;
        if(AdjList[i].data==v)
            return ERROR;
    }
    AdjList[G.vexnum].data=v;
    AdjList[G.vexnum].num=flag+1;
    G.vexnum++;
    return OK;
}

//初始条件：图G存在，v是G的一个顶点。
//操作结果：在图G中删除顶点v和与v相关的弧。
status DeleteVex(VertexType v){
    int v_index=LocateVex(v);
    if(v_index==-1)
        return ERROR;
    else{
        for(int i=0;i<G.vexnum;i++)
            DeleteArc(v,AdjList[i].data);
        for(int i=v_index;i<G.vexnum-1;i++){
            AdjList[i]=AdjList[i+1];
        }
        AdjList[G.vexnum-1]={};
        G.vexnum--;

    }
    return OK;
}

//初始条件：图G存在，v、w是G的顶点。
//操作结果：在图G中增加弧<v, w>
status InsertArc(VertexType v, VertexType u){
    int v_loc=LocateVex(v);
    int u_loc=LocateVex(u);
    if(v_loc==u_loc||v_loc==-1||u_loc==-1)
        return ERROR;
    int v_index=AdjList[v_loc].num;
    int u_index=AdjList[u_loc].num;
    {
        ArcNode *newarc1=(ArcNode*)malloc(sizeof(ArcNode));
        newarc1->adjvex=u_index;
        newarc1->nextarc=NULL;
        ArcNode *p=AdjList[v_loc].firstarc;              //v->u
        if(p==NULL)
            AdjList[v_loc].firstarc=newarc1;
        else if(p->nextarc==NULL){
            if(u_index==p->adjvex)
                return ERROR;
            else if(u_index<p->adjvex)
                p->nextarc=newarc1;
            else{
                newarc1->nextarc=p;
                AdjList[v_loc].firstarc=newarc1;
            }
        }
        else{
            if(u_index>p->adjvex){
                newarc1->nextarc=p;
                AdjList[v_loc].firstarc=newarc1;
            }
            else if(u_index==p->adjvex) return ERROR;
            else{
                while(p->nextarc){
                    if(p->nextarc->adjvex<u_index){
                        newarc1->nextarc=p->nextarc;
                        p->nextarc=newarc1;
                        break;
                    }
                    else p=p->nextarc;
                }
                if(p->adjvex!=u_index)
                    p->nextarc=newarc1;
            }
        }
    }
    {
        ArcNode *newarc2=(ArcNode*)malloc(sizeof(ArcNode));
        newarc2->adjvex=v_index;
        newarc2->nextarc=NULL;
        ArcNode *q=AdjList[u_loc].firstarc;              //v->u
        if(q==NULL)
            AdjList[u_loc].firstarc=newarc2;
        else if(q->nextarc==NULL){
            if(v_index==q->adjvex)
                return ERROR;
            else if(v_index<q->adjvex)
                q->nextarc=newarc2;
            else{
                newarc2->nextarc=q;
                AdjList[u_loc].firstarc=newarc2;
            }
        }
        else{
            if(v_index>q->adjvex){
                newarc2->nextarc=q;
                AdjList[u_loc].firstarc=newarc2;
            }
            else if(v_index==q->adjvex) return ERROR;
            else{
                while(q->nextarc){
                    if(q->nextarc->adjvex<v_index){
                        newarc2->nextarc=q->nextarc;
                        q->nextarc=newarc2;
                        break;
                    }
                    else q=q->nextarc;
                }
                if(q->adjvex!=v_index)
                    q->nextarc=newarc2;
            }
        }
    }
    G.arcnum++;
    return OK;
}

//初始条件：图G存在，v、w是G的顶点。
//操作结果：在图G中删除弧<v, w>
status DeleteArc(VertexType v, VertexType u){
    int v_index=LocateVex(v);
    int u_index=LocateVex(u);
    if(v_index==-1||u_index==-1) return ERROR;
    {
        ArcNode *p=AdjList[v_index].firstarc;
        while(p){
            if(GetVex2(p->adjvex)!=u){
                p=p->nextarc;
            }
            else break;
        }
        if(!p) return ERROR;
        else if(p->nextarc==NULL&&GetVex2(p->adjvex)!=u)
            return ERROR;
        else{
            if(p==AdjList[v_index].firstarc){
                AdjList[v_index].firstarc=p->nextarc;
                free(p);
            }
            else{
                ArcNode *q=AdjList[v_index].firstarc;
                while(q->nextarc!=p) q=q->nextarc;
                q->nextarc=p->nextarc;
                free(p);
            }
        }
    }
    {
        ArcNode *p=AdjList[u_index].firstarc;
        while(p){
            if(GetVex2(p->adjvex)!=v)
                p=p->nextarc;
            else break;
        }
        if(!p) return ERROR;
        else if(p==AdjList[u_index].firstarc){
            AdjList[u_index].firstarc=p->nextarc;
            free(p);
        }
        else{
            ArcNode *q=AdjList[u_index].firstarc;
            while(q->nextarc!=p) q=q->nextarc;
            q->nextarc=p->nextarc;
            free(p);
        }

    }
    G.arcnum--;
    return OK;
}

//深度优先遍历的辅助函数
void DFS(int v,int *flag){
    flag[v]=1;
    printf("%c ",AdjList[v].data);
    for(ArcNode *p= AdjList[v].firstarc;p;p=p->nextarc)
    {
        if (!flag[p->adjvex])
        {
            DFS(p->adjvex,flag);
        }
    }
}

//初始条件：图G存在。
//操作结果：对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函
//          数printf访问一次，且仅访问一次。
status DFSTraverse(){
    if(G.vexnum==0) return ERROR;
    int flag[20]={0};
    for(int i=G.vexnum-1;i>=0;i--){
        if(!flag[i])
        {
            DFS(i,flag);
        }
    }
    return OK;
}

//初始条件：图G存在。
//操作结果：对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函
//          数printf访问一次，且仅访问一次。
status BFSTraverse(){
    if(G.vexnum==0) return ERROR;
    printf("广度优先搜索遍历的结果为：\n");
    int flag[20]={0};
    VertexType Queue[20]={};
    ArcNode *p=NULL;
    char *rear=&Queue[0];
    *rear=AdjList[G.vexnum-1].data;
    rear++;
    flag[G.vexnum-1]=1;
    for(int i=0;i<G.vexnum;i++){
        if(!Queue[i]){
            for(int j=G.vexnum-1;j>=0;j--){
                if(flag[j]==1)
                    continue;
                else{
                    Queue[i]=AdjList[j].data;
                    flag[j]=1;
                    rear++;
                    break;
                }
            }
        }
        p=AdjList[LocateVex(Queue[i])].firstarc;

        while(p){
            if(flag[LocateVex(GetVex2(p->adjvex))]!=1){
                flag[LocateVex(GetVex2(p->adjvex))]=1;
                *rear=GetVex2(p->adjvex);
                rear++;
            }
            p=p->nextarc;
        }
        printf("%c ",Queue[i]);
    }
    printf("\n");
    return OK;
}

//初始条件：图G存在
//操作结果：显示图中所有的结点和边
void ShowVexArc(){
    for(int i=0;i<G.vexnum;i++){
        ArcNode *p=AdjList[i].firstarc;
        printf("%c: ",AdjList[i].data);
        while(p){
            printf("%c->%c ",AdjList[i].data,GetVex2(p->adjvex));
            p=p->nextarc;
        }
        printf("\n");
    }
}
void save(char *filename){
    FILE *fp=NULL;
    fp=fopen(filename,"wb");
    ArcNode *p=NULL;
    fprintf(fp,"%d %d ",G.vexnum,G.arcnum);
    for(int i=0;i<G.vexnum;i++)
        fprintf(fp,"%c",AdjList[i].data);
    for(int i=0;i<G.vexnum;i++){
        p=AdjList[i].firstarc;
        while(p){
            fprintf(fp,"%c%c",AdjList[i].data,GetVex2(p->adjvex));
            p=p->nextarc;
        }
    }
    fclose(fp);
}
void read(char *filename){
    FILE *fp=fopen(filename,"rb");
    int vexnum=0,arcnum=0;
    fscanf(fp,"%d %d ",&vexnum,&arcnum);
    char vex[100]={};
    char arc[200]={};
    for(int i=0;i<vexnum;i++){
        fscanf(fp,"%c",&vex[i]);
        InsertVex(vex[i]);
    }
    for(int i=0;i<4*arcnum;i=i+2){
        fscanf(fp,"%c%c",&arc[i],&arc[i+1]);
        InsertArc(arc[i],arc[i+1]);
    }
    fclose(fp);
}
