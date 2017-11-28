/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义  24字节
	ElemType * elem;
	int length;
	int listsize;
}SqList;
SqList data[5];
/*-----page 19 on textbook ---------*/
status IntiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType & e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
status NextElem(SqList L,ElemType cur,ElemType & next_e);
status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L,int i,ElemType & e);
status ListTrabverse(SqList L);  //简化过
int read_data(void);
int save_data(void);
/*--------------------------------------------*/
int main(void){
    FILE *_fp=fopen(".\\data.bin","rb");
    if(_fp==NULL)
    {
        printf("File open error\n");
        return ERROR;
    }
    fclose(_fp);
    read_data();
    SqList L;int op=1;
    ElemType e=0,pre_e=0,next_e=0;
    while(op){
    	system("cls");
    	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty       10. ListInsert\n");
		printf("    	  5. ListLength      11. ListDelete\n");
		printf("    	  6. GetElem         12. ListTrabverse\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~12]:");
		scanf("%d",&op);
    	switch(op){
	   	case 1:{//ok
			int rank=0;
			while(rank<5)
			{
				if(data[rank].listsize!=0)
					rank++;
				else
					break;
			}
			if(rank==5&&data[4].listsize!=0)
				printf("线性表创建失败！\n");
			else
                if(IntiaList(data[rank])==OK)
                    printf("线性表创建成功,这是第%d个线性表！\n",rank+1);
            system("pause");
			break;
		}
	    case 2:{//ok
	    	printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
	   			printf("\n该表不存在！\n");
			else
			{
				DestroyList(data[x-1]);
				printf("\n该表已销毁！\n");
		 	}
		 	system("pause");
            break;
        }
	    case 3:{//ok
	    	printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
	   			printf("\n该表不存在！\n");
            else if(data[x-1].length==0)
	   			printf("\n该表已为空！\n");
			else
            {
                ClearList(data[x-1]);
	 			printf("\n该表已清空！\n");
	 		}
	 		system("pause");
            break;
	 	}
	   	case 4:{//ok
	   		printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(ListEmpty(data[x-1])==0)
	 			printf("\n该表不是空表！\n");
			else if(ListEmpty(data[x-1])==1)
				printf("\n该表是空表！\n");
			else
				printf("\n该表不存在！\n");
	 		system("pause");
	 		break;
	 	}
	   	case 5:{//ok
	   		printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(ListLength(data[x-1])<0)
	   			printf("\n该表不存在！\n");
			else
	   			printf("\n该表长度为%d！\n",ListLength(data[x-1]));
	 		system("pause");
            break;
	 	}
		case 6:{//ok
		    printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n该表不存在！\n");
                system("pause");
                break;
            }
	   		printf("请选择提取位置！");
	   		int i;
	   		scanf("%d",&i);
	   		status result = GetElem(data[x-1],i,e);
	 		if(result==0) printf("\n提取位置错误！\n");
	 		else
                printf("\n该元素值为%d\n",e);
	 		system("pause");
	 		break;
        }
	   	case 7:{//ok
	   	    printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n该表不存在！\n");
            else
            {
                if(data[x-1].length==0)
                    printf("\n该表是空表！\n");
                else
                {
                    printf("请选择查询元素！");
                    int e;
                    scanf("%d",&e);
                    LocateElem(data[x-1],e);
                }
            }
	 		system("pause");
	 		break;
        }
	   	case 8:{//ok
	 		printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n该表不存在！\n");
            else
            {
                printf("请选择查找的元素！");
                int cur;
                scanf("%d",&cur);
                status result = PriorElem(data[x-1],cur,pre_e);
                if(result==ERROR)
                    printf("找不到该元素！\n");
                else if(result==INFEASTABLE)
                    printf("该元素在首节点！\n");
                else
                    printf("该元素前驱节点为%d！\n",pre_e);
            }
	 		system("pause");
	 		break;
	   	}
	   	case 9:{//ok
	 		printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n该表不存在！\n");
            else
            {
                printf("请选择查找的元素！");
                int cur;
                scanf("%d",&cur);
                status result = NextElem(data[x-1],cur,next_e);
                if(result==ERROR)
                    printf("找不到该元素！\n");
                else if(result==INFEASTABLE)
                    printf("该元素在尾节点！\n");
                else
                    printf("该元素后继节点为%d！\n",next_e);
            }
	 		system("pause");
	 		break;
	   	}
	   	case 10:{//ok
	   	    printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n该表不存在！\n");
                system("pause");
                break;
            }
	   		printf("请选择插入位置！");
	   		int i;
	   		scanf("%d",&i);
	   		printf("请选择插入元素！");
	   		int e;
	   		scanf("%d",&e);
	   		status result = ListInsert(data[x-1],i,e);
		 	if(result==ERROR) printf("\n插入位置错误！\n");
            else
                printf("\n插入成功！\n");
			system("pause");
            break;
        }
	   	case 11:{//ok
	 		 printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n该表不存在！\n");
                system("pause");
                break;
            }
	   		printf("请选择删除位置！");
	   		int i;
	   		scanf("%d",&i);
	   		status result = ListDelete(data[x-1],i,e);
	   		if(result==ERROR) printf("\n删除失败！\n");
	   		else
                printf("\n已删除元素%d！\n",e);
	 		system("pause");
	 		break;
        }
	   	case 12:{//ok
	 		printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = ListTrabverse(data[x-1]);
	 		if(result<0) printf("\n该表不存在！\n");
	 		if(result=0) printf("\n该表是空表！\n");
            system("pause");
            break;
        }
	   	case 0:
       		break;
		}//end of switch
	}//end of while
    save_data();
  	printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList & L){//初始化表 -------1
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}
status DestroyList(SqList & L){//销毁列表 -------2
    ElemType *p =&(L.elem[L.length-1]);
	ElemType *q = p;
	for(int i=1;i<L.length;i++)
	{
		--p;
		free(q);
		q=p;
	}
	free(L.elem);
	L.length=0;
	L.listsize=0;
	return OK;
}
status ClearList(SqList &L){//清空列表 -------3
	int SqList_num = 0;
	ElemType *p =&(L.elem[L.length-1]);
	ElemType *q = p;
	for(int i=1;i<L.length;i++)
	{
		--p;
		free(q);
		q=p;
	}
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=0;
	return OK;
}
status ListEmpty(SqList L){//是否为空表 -------4
	if(L.listsize==0) return INFEASTABLE;
	else
	{
		if(L.length!=0) return FALSE;
		else return TRUE;
	}
}
int ListLength(SqList L){//获取长度-------5
	if(L.listsize==0) return INFEASTABLE;
	return L.length;
}
status GetElem(SqList L,int i,ElemType & e){//获取元素-------6
    if(i<1||i>L.length) return ERROR;
    e = L.elem[i-1];
    return OK;
}
status LocateElem(SqList L,ElemType e){//寻找位置-------7
	int x=0;
    while(x<L.length){
        if(L.elem[x]==e)
            break;
        x++;
    }
    if(x==L.length&&L.elem[x-1]!=e)
        printf("找不到该元素！\n");
    else
        printf("优先匹配到的是第%d个元素！\n",x+1);
    return OK;
}
status PriorElem(SqList L,ElemType cur,ElemType & pre_e){//前驱节点-------8
	int flag = 0;
	int x = 0;
    for(x=0;x<L.length;x++){
        if(L.elem[x]==cur){
            flag = 1;
            break;
        }
    }
    if(flag == 0) return ERROR;
    if(x == 0) return INFEASTABLE;
    pre_e = L.elem[x-1];
    return OK;
}
status NextElem(SqList L,ElemType cur,ElemType & next_e){//后继节点-------9
	int flag = 0;
	int x = 0;
    for(x=0;x<L.length;x++){
        if(L.elem[x]==cur){
            flag = 1;
            break;
        }
    }
    if(flag == 0) return ERROR;
    if(x == L.length-1) return INFEASTABLE;
    next_e = L.elem[x+1];
    return OK;
}
status ListInsert(SqList & L,int i,ElemType e){//插入元素 -------10
	ElemType * newbase = NULL;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length >= L.listsize)
	{
		newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType *q = &(L.elem[i-1]);
	ElemType *p = &(L.elem[L.length-1]);
	for(p = &(L.elem[L.length-1]); p >= q; --p)
		*(p+1) = *p;
	*q = e;
	L.length+=1;
	return OK;
}
status ListDelete(SqList & L,int i,ElemType & e){//删除元素 -------11
	if(i<1||i>L.length) return ERROR;
	ElemType *q = &(L.elem[i-1]);
	e=L.elem[i-1];
	ElemType *p = &(L.elem[L.length-1]);
	for(q=&(L.elem[i-1]);q<p;q++)
        *q=*(q+1);
    free(p);
    L.length-=1;
    return OK;
}
status ListTrabverse(SqList L){//输出元素 -------12
    int i=1;
    if(L.listsize==0) return INFEASTABLE;
    if(L.length!=0)
    {
        for(;i<=L.length;i++)
        {
            printf("该表的第%d个元素为%d\n",i,L.elem[i-1]);
        }
    }
    return L.length;
}
int read_data(){
    int amount=0;
    FILE *fp=NULL;
    fp=fopen(".\\data.bin","rb");
    if(!feof(fp)){
        fscanf(fp,"%d",&amount);
        for(int i=0;i<amount;i++)
        {
            fread(&data[i],sizeof(SqList),1,fp);
            data[i].elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
            fread(&data[i].elem[0],sizeof(ElemType),data[i].length,fp);
        }
    }
    fclose(fp);
    return OK;
}
int save_data(){
    int amount=0;
    for(int i=0;i<=4;i++)
    {
        if(data[i].listsize==0) continue;
        else
            amount++;
    }
    FILE *fp;
    fp=fopen(".\\data.bin","wb");
    fprintf(fp,"%d",amount);
    for(int i=0;i<=4;i++)
    {
        if(data[i].listsize==0) continue;
        else{
            fwrite(&data[i],sizeof(SqList),1,fp);
            fwrite(data[i].elem,sizeof(ElemType),data[i].length,fp);
        }
    }
    fclose(fp);
    return OK;
}
