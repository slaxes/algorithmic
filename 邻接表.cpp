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
typedef char VertexType;                                    //����Ԫ�����Ͷ���

#define MAX_VERTEX_NUM 20                                   //����������

typedef struct ArcNode{
    int adjvex;                                             //�û���ָ��Ľ���λ��
    struct ArcNode *nextarc;                                //ָ����һ������ָ��
} ArcNode;
typedef struct VNode{
    int num;                                                //�������
    VertexType data;                                        //������Ϣ(char)
    ArcNode *firstarc;                                      //ָ���һ�������ö���Ļ���ָ��
} VNode;
typedef struct{
    int vexnum, arcnum;                                     //ͼ�ĵ�ǰ�������ͻ���
} ALGraph;
status CreateGraph(char *vex, char *arc);                   //����ͼ
status DestroyGraph();                                      //����ͼ
int LocateVex(VertexType u);                                //���Ҷ���
VertexType GetVex(int x);                                   //��ö���ֵ(���ݴ��λ��)
VertexType GetVex2(int x);                                  //��ö���ֵ(��������)
void PutVex(int v,VertexType value);                        //���㸳ֵ
int FirstAdjVex(int v);                                     //��õ�һ�ڽӵ�
int NextAdjVex(int v, int w);                               //�����һ�ڽӵ�
status InsertVex(VertexType v);                             //���붥��
status DeleteVex(VertexType v);                             //ɾ������
status InsertArc(VertexType v, VertexType u);               //���뻡
status DeleteArc(VertexType v, VertexType u);               //ɾ����
status DFSTraverse();                                       //���������������
status BFSTraverse();                                       //�����������������
void ShowVexArc();                                          //��ʾ�����뻡
void save(char filename[20]);
void read(char filename[20]);
ALGraph G={};
VNode AdjList[MAX_VERTEX_NUM];
int main(void)
{
    FILE *fp = NULL;
    char filename[20];
/*�û�ָ���ļ���ͼ���г�ʼ��*/
    printf("�Ƿ�ָ���ļ���ͼ��ʼ����[n]/y\n");
    if (getchar() == 'y')
    {
        printf("Input filename:");
        scanf("%s", filename);
        if (fp = fopen(filename, "r")){
            fclose(fp);
            read(filename);
        }
        else{
            printf("�޷�������ļ���ͼδ��ʼ����\n");
            system("pause");
        }
    }
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("                     �ڽӱ� �˵�                 \n");
        printf("-------------------------------------------------\n");
        printf("    	 1. ����ͼ             9. ɾ������\n");
        printf("    	 2. ����ͼ            10. ���뻡\n");
        printf("    	 3. ���Ҷ���          11. ɾ����\n");
        printf("    	 4. ��ö���ֵ        12. ���������������\n");
        printf("    	 5. ���㸳ֵ          13. �����������������\n");
        printf("    	 6. ��õ�һ�ڽӵ�    14. ��ʾ�����뻡\n");
        printf("    	 7. �����һ�ڽӵ�    15. �л�ͼ\n");
        printf("         8. ���붥��           0. �˳�\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        /*����ͼ*/
        case 1:{
            char vex[100];
            printf("�����������:\n");
            fgets(vex,100,stdin);
            char arc[200];
            printf("������ߵļ��ϣ��ñߵĶ����ʾ���ɣ�ʾ������a->b,c->d,����abcd���ɣ�:\n");
            fgets(arc,200,stdin);
            if(CreateGraph(vex, arc)==OK){
                printf("�����ɹ���\n");
            }
            else{
                printf("����ʧ�ܣ�\n");
            }
            system("pause");
            break;
        }
        /*����ͼ*/
        case 2:{
            DestroyGraph();
            printf("���ٳɹ���\n");
            system("pause");
            break;
        }
        /*���Ҷ���*/
        case 3:{
            printf("��������Ҷ�������ݣ�\n");
            VertexType u;
            scanf("%c",&u);
            int result=LocateVex(u);
            if(result==INFEASTABLE)
                printf("δ�ҵ���Ӧ�ڵ㣡\n");
            else{
                printf("�ڵ�%c�����˳��Ϊ%d��\n",u,result+1);
            }
            system("pause");
            break;
        }
        /*��ö���ֵ*/
        case 4:{
            int x;
            VertexType result;
            printf("���������ֵ��\n");
            scanf("%d",&x);
            result=GetVex(x-1);
            if(result!=ERROR)
                printf("���ҵ�������Ϊ%c��\n",result);
            else printf("�Ҳ�����Ӧ�Ľڵ㣡\n");
            system("pause");
            break;
        }
        /*���㸳ֵ*/
        case 5:{
            int v;VertexType value;
            printf("�����붥�㴢���λ�ã�\n");
            scanf("%d",&v);getchar();
            printf("������������ֵ��\n");
            scanf("%c",&value);
            PutVex(v,value);
            system("pause");
            break;
        }
        /*��õ�һ�ڽӵ�*/
        case 6:{
            printf("�������ŵ�λ�ã�\n");
            int loca;
            scanf("%d",&loca);
            int result=FirstAdjVex(loca);
            if(result==ERROR)
                printf("��������ȷ��λ�ã�\n");
            else if(result==INFEASTABLE)
                printf("�ýڵ����ڽӽڵ㣡\n");
            else
                printf("�ýڵ��λ��Ϊ%d��\n",result);
            system("pause");
            break;
        }
        /*�����һ�ڽӵ�*/
        case 7:{
            int v,w;
            printf("�����붥��洢λ�ã�\n");
            scanf("%d",&v);
            printf("�������ڽӽڵ���ţ�\n");
            scanf("%d",&w);
            int result=NextAdjVex(v,w);
            if(result==-1)
                printf("��һ�ڽӽڵ㲻���ڣ�\n");
            else if(result==ERROR)
                printf("ԭ�ڵ����ڽӽڵ㣡\n");
            else printf("��һ�ڽӽڵ�λ��Ϊ%d\n",result);
            system("pause");
            break;
        }
        /*���붥��*/
        case 8:{
            VertexType v;
            printf("��������Ҫ����Ķ��㣡\n");
            scanf("%c",&v);
            int result=InsertVex(v);
            if(result==ERROR)
                printf("�ö����Ѵ��ڣ�\n");
            else printf("����ɹ���\n ");
            system("pause");
            break;
        }
        /*ɾ������*/
        case 9:{
            VertexType v;
            printf("��������Ҫɾ���Ķ��㣡\n");
            scanf("%c",&v);
            int result=DeleteVex(v);
            if(result==OK)
                printf("ɾ���ɹ���\n");
            else printf("ɾ��ʧ�ܣ�\n");
            system("pause");
            break;
        }
        /*���뻡*/
        case 10:{
            VertexType v,u;
            printf("��ѡ����뻡�Ķ��㣡(���磺a b)\n");
            scanf("%c %c",&v,&u);
            int result=InsertArc(v,u);
            if(result==ERROR)
                printf("����ʧ�ܣ�\n");
            else
                printf("����ɹ���\n");
            system("pause");
            break;
        }
        /*ɾ����*/
        case 11:{
            VertexType v,u;
            printf("��������Ҫɾ���Ļ�(���磺a b)��\n");
            scanf("%c %c",&v,&u);
            int result=DeleteArc(v,u);
            if(result==ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            else
                printf("ɾ���ɹ���\n");
            system("pause");
            break;
        }
        /*���������������*/
        case 12:{
            int result=DFSTraverse();
            if(result==ERROR)
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        }
        /*�����������������*/
        case 13:{
            int result=BFSTraverse();
            if(result==ERROR)
                printf("ͼ�����ڣ�\n");
            system("pause");
            break;
        }
        /*��ʾ�����뻡*/
        case 14:{
            ShowVexArc();
            system("pause");
            break;
        }
        /*�л�ͼ*/
        case 15:{
            printf("�Ƿ�Ҫ����ͼ���ݣ�y/[n]\n");
            if (getchar() == 'y')
            {
                printf("�������ļ�����");
                if (scanf("%s", filename)){
                    save(filename);
                }
                else{
                    printf("����ʧ�ܣ�\n");
                }
            }
            printf("�Ƿ�ָ���ļ���ͼ��ʼ����[n]/y\n");getchar();
            if (getchar() == 'y')
            {
                printf("Input filename:");
                scanf("%s", filename);
                if (fp = fopen(filename, "r")){
                    fclose(fp);
                    read(filename);
                }
                else{
                    printf("�޷�������ļ���ͼδ��ʼ����\n");
                    system("pause");
                }
            }
                system("pause");
                break;
            }
        /*�˳�*/
        case 0:{
            printf("�Ƿ�Ҫ����ͼ���ݣ�y/[n]\n");
            if (getchar() == 'y')
            {
                printf("�������ļ�����");
                if (scanf("%s", filename)){
                    save(filename);
                }
                else{
                    printf("����ʧ�ܣ�\n");
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

//�����û�Ҫ����ͼ
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

//��ʼ������ͼG���ڡ�
//�������������ͼG��
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

//��ʼ������ͼG���ڣ�u��G�еĶ��������ͬ������
//�����������u��ͼG�д��ڣ����ض���u��λ����Ϣ�����򷵻�-1��
int LocateVex(VertexType u){
    int i=0;
    while(i<G.vexnum){
        if(AdjList[i].data==u)
            return i;
        i++;
    }
    return INFEASTABLE;
}

//��ʼ������ͼG���ڣ�x��G�е�ĳ��������λ��.
//������������ض���ֵ��
VertexType GetVex(int x){
    if(x<0||x>G.vexnum-1) return ERROR;
    else return AdjList[x].data;
}

//��ʼ������ͼG���ڣ�x��G�е�ĳ����������.
//�������������v����ֵ��
VertexType GetVex2(int x){
    int i=0;
    for(i=0;i<G.vexnum;i++){
        if(AdjList[i].num==x)
            return AdjList[i].data;
    }
    if((i==G.vexnum-1)&&(AdjList[i].num!=x))
        return ERROR;
}

//��ʼ������ͼG���ڣ�v��G�е�ĳ�����㡣
//�����������v��ֵvalue��
void PutVex(int v,VertexType value){
    if(v>=1&&v<=G.vexnum){
        AdjList[v-1].data=value;
        printf("��ֵ�ɹ���\n");
    }
}

//��ʼ������ͼG���ڣ�v��G�е�ĳ�����㡣
//�������������v�ĵ�һ���ڽӶ����λ�ã����vû���ڽӶ��㣬����INFEASTABLE��
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

//��ʼ������ͼG���ڣ�v��G��һ������λ��, w��v���ڽӶ����λ�á�
//�������������v�ģ������w����һ���ڽӶ����λ�ã����w�����һ���ڽӶ��㣬����-1
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

//��ʼ������ͼG���ڣ�v��G�еĶ��������ͬ������
//�����������ͼG�������¶���v��
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

//��ʼ������ͼG���ڣ�v��G��һ�����㡣
//�����������ͼG��ɾ������v����v��صĻ���
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

//��ʼ������ͼG���ڣ�v��w��G�Ķ��㡣
//�����������ͼG�����ӻ�<v, w>
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

//��ʼ������ͼG���ڣ�v��w��G�Ķ��㡣
//�����������ͼG��ɾ����<v, w>
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

//������ȱ����ĸ�������
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

//��ʼ������ͼG���ڡ�
//�����������ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú�
//          ��printf����һ�Σ��ҽ�����һ�Ρ�
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

//��ʼ������ͼG���ڡ�
//�����������ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú�
//          ��printf����һ�Σ��ҽ�����һ�Ρ�
status BFSTraverse(){
    if(G.vexnum==0) return ERROR;
    printf("����������������Ľ��Ϊ��\n");
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

//��ʼ������ͼG����
//�����������ʾͼ�����еĽ��ͱ�
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
