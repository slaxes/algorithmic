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
typedef int ElemType;
typedef struct _list{
	ElemType elem;
	_list *next;
}SqList;
typedef struct{
	int length;
	int exist;
	_list *next;
}ListHead;
ListHead data[5];
status IntiaList(ListHead & L);
status DestroyList(ListHead & L);
status ClearList(ListHead &L);
status ListEmpty(ListHead L);
int ListLength(ListHead L);
status GetElem(ListHead L,int i,ElemType & e);
status LocateElem(ListHead L,ElemType e);
status PriorElem(ListHead L,ElemType cur,ElemType & pre_e);
status NextElem(ListHead L,ElemType cur,ElemType & next_e);
status ListInsert(ListHead & L,int i,ElemType e);
status ListDelete(ListHead & L,int i,ElemType & e);
status ListTrabverse(ListHead L);  //简化过
int read_data(void);
int save_data(void);
int main(void){
    int option;
    system("cls");
    printf("是否读取文件？(0:不读取,1:读取)");
    scanf("%d",&option);
    if(option==1)
    {
        FILE *_fp=fopen(".\\data.bin","rb");
        if(_fp==NULL)
        {
            printf("File open error\n");
            return ERROR;
        }
        fclose(_fp);
        read_data();
    }
	int op=1;
	ElemType e=0,pre_e=0,next_e=0;
    while(op){
    	system("cls");
    	printf("\n\n");
		printf("      Menu for Chain Table On Sequence Structure \n");
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
	   	case 1:{
	   	    int rank=0;
			while(rank<5)
			{
				if(data[rank].exist!=0)
					rank++;
				else
					break;
			}
			if(rank==5&&data[4].exist!=0)
				printf("线性表创建失败！\n");
			else
                if(IntiaList(data[rank])==OK)
                    printf("线性表创建成功,这是第%d个线性表！\n",rank+1);
            system("pause");
			break;
		}
	    case 2:{
	        printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = DestroyList(data[x-1]);
	   		if(result==OK) printf("该表已销毁！\n");
		 	system("pause");
            break;
        }
	    case 3:{
	        printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = ClearList(data[x-1]);
	   		if(result==OK) printf("该表已清空！\n");
	 		system("pause");
            break;
	 	}
	   	case 4:{
	   	    printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		ListEmpty(data[x-1]);
	 		system("pause");
	 		break;
	 	}
	   	case 5:{
	   	    printf("请选择列表序号！[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].exist==0) printf("该表不存在！\n");
	   		else printf("第%d个表的长度为%d!\n",x,ListLength(data[x-1]));
	 		system("pause");
            break;
	 	}
		case 6:{
		    int x,i;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入元素位置！");
	   		scanf("%d",&i);
	   		status result = GetElem(data[x-1],i,e);
	   		if(result==OK) printf("获取的元素值为%d！\n",e);
	 		system("pause");
	 		break;
        }
	   	case 7:{
	   	    int x,i;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入查找的元素！");
	   		scanf("%d",&i);
	   		LocateElem(data[x-1],i);
	 		system("pause");
	 		break;
        }
	   	case 8:{
	   	    int x,cur;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入元素值！");
	   		scanf("%d",&cur);
	   	    status result = PriorElem(data[x-1],cur,pre_e);
	   	    if(result==OK) printf("该元素前驱节点为%d！\n",pre_e);
	 		system("pause");
	 		break;
	   	}
	   	case 9:{
	   	    int x,cur;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入元素值！");
	   		scanf("%d",&cur);
	   	    status result = NextElem(data[x-1],cur,next_e);
	   	    if(result==OK) printf("该元素后继节点为%d！\n",next_e);
	 		system("pause");
	 		break;
	   	}
	   	case 10:{
	   	    int x,i;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入插入位置！");
	   		scanf("%d",&i);
	   		printf("请输入插入元素！");
	   		scanf("%d",&e);
	   		status result = ListInsert(data[x-1],i,e);
	   		if(result==OK) printf("插入成功！\n");
			system("pause");
            break;
        }
	   	case 11:{
	   	    int x,i;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   		printf("请输入删除位置！");
	   		scanf("%d",&i);
	   		status result = ListDelete(data[x-1],i,e);
	   		if(result==OK) printf("删除成功！\n");
	 		system("pause");
	 		break;
        }
	   	case 12:{
	   	    int x;
		    printf("请选择列表序号！[1-5]");
	   		scanf("%d",&x);
	   	    ListTrabverse(data[x-1]);
            system("pause");
            break;
        }
	   	case 0:
       		break;
		}//end of switch
	}//end of while
    //save_data();
    system("cls");
    printf("退出前是否保存？(0:不保存,1:保存)");
    scanf("%d",&option);
    if(option==1)
        save_data();
  	printf("欢迎下次再使用本系统！\n");
}//end of main()
status IntiaList(ListHead &L){
    L.exist=1;
	L.next=NULL;
	L.length=0;
	return OK;
}
status DestroyList(ListHead &L){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
	if(L.length!=0){
        SqList *p=L.next;
        SqList *q=L.next;
        for(int x=0;x<L.length;x++)
        {
            q=p->next;
            free(p);
            p=q;
        }
	}
	L.exist=0;
	return OK;
}
status ClearList(ListHead &L){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表已为空！\n");
        return ERROR;
    }
	else{
        SqList *p=L.next;
        SqList *q=L.next;
        for(int x=0;x<L.length;x++)
        {
            q=p->next;
            free(p);
            p=q;
        }
        return OK;
	}
}
status ListEmpty(ListHead L){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0)
        printf("该表是空表！\n");
    else printf("该表不是空表！\n");
    return OK;
}
int ListLength(ListHead L){
    return L.length;
}
status GetElem(ListHead L,int i,ElemType & e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length){
        printf("获取位置错误！\n");
        return ERROR;
    }
    else{
        SqList *p=L.next;
        for(int x=0;x<i-1;x++){
            p=p->next;
        }
        e=p->elem;
        return OK;
    }
}
status LocateElem(ListHead L,ElemType e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    else{
        int x=0;SqList *p=L.next,*q=L.next;
        while(x<L.length){
            if(p->elem==e)
                break;
            q=p;
            p=p->next;
            x++;
        }
        if(x==L.length&&q->elem!=e)
            printf("找不到该元素！\n");
        else
            printf("优先匹配到的是第%d个元素！\n",x+1);
            return OK;
    }
}
status PriorElem(ListHead L,ElemType cur,ElemType & pre_e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    int flag=0,x = 0;
    SqList *p=L.next,*q=L.next;
    for(x=0;x<L.length;x++){
        if(p->elem==cur){
            flag = 1;
            break;
        }
        p=p->next;
    }
    if(flag == 0){
        printf("找不到该元素！\n");
        return ERROR;
    }
    else if(x == 0){
        printf("该元素在首节点！\n");
        return INFEASTABLE;
    }
    else{
        for(int y=0;y<x-1;y++) q=q->next;
        pre_e = q->elem;
    }
    return OK;
}
status NextElem(ListHead L,ElemType cur,ElemType & next_e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    int flag=0,x = 0;
    SqList *p=L.next;
    for(x=0;x<L.length;x++){
        if(p->elem==cur){
            flag = 1;
            break;
        }
        p=p->next;
    }
    if(flag == 0){
        printf("找不到该元素！\n");
        return ERROR;
    }
    else if(x == L.length-1){
        printf("该元素在尾节点！\n");
        return INFEASTABLE;
    }
    else next_e = p->next->elem;
    return OK;
}
status ListInsert(ListHead & L,int i,ElemType e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length+1){
        printf("插入位置错误！\n");
        return INFEASTABLE;
    }
    else{
        SqList *p = L.next;
        SqList *ins = (SqList*)malloc(sizeof(SqList));
        if(i==1){
            L.next=ins;
            ins->next=p;
        }
        else{
            for(int x=0;x<i-2;x++) p=p->next;
            ins->next=p->next;
            p->next=ins;
        }
        ins->elem=e;
        L.length++;
        return OK;
    }
}
status ListDelete(ListHead & L,int i,ElemType & e){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length){
        printf("删除位置错误！\n");
        return INFEASTABLE;
    }
    SqList *p = L.next,*q;
    if(i==1){
        L.next=p->next;
        e=p->elem;
        free(p);
        L.length--;
    }
    else{
        for(int x=0;x<i-2;x++) p=p->next;
        q=p->next;
        p->next=q->next;
        e=q->elem;
        free(q);
        L.length--;
    }
    return OK;
}
status ListTrabverse(ListHead L){
    if(L.exist==0){
        printf("该表不存在！\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("该表是空表！\n");
        return INFEASTABLE;
    }
    SqList *p = L.next;
    for(int x=0;x<L.length;x++){
        printf("该表的第%d个元素为%d\n",x+1,p->elem);
        p=p->next;
    }
    return OK;
}
int read_data(){
    int amount=0;
    int length=0;
    FILE *fp=NULL;
    fp=fopen(".\\data.bin","rb");
    if(!feof(fp)){
        fscanf(fp,"%d",&amount);
        for(int i=0;i<amount;i++)
        {
            fread(&data[i],sizeof(ListHead),1,fp);
            SqList *q = NULL,*p = NULL;
            while(length<data[i].length){
                q=(SqList*)malloc(sizeof(SqList));
                fread(q,sizeof(SqList),1,fp);
                if(length==0){
                    data[i].next=q;
                    p=q;
                    q=NULL;
                }
                else{
                    p->next=q;
                    p=q;
                    q=NULL;
                }
                length++;
            }
        }
    }
    fclose(fp);
    return OK;
}
int save_data(){
    int amount=0;
    for(int i=0;i<=4;i++)
    {
        if(data[i].exist==0) continue;
        else
            amount++;
    }
    FILE *fp;
    fp=fopen(".\\data.bin","wb");
    fprintf(fp,"%d",amount);
    for(int i=0;i<=4;i++)
    {
        if(data[i].exist==0) continue;
        else{
            fwrite(&data[i],sizeof(ListHead),1,fp);
            SqList *q = data[i].next;
            for(int j=0;j<data[i].length;j++){
                fwrite(q,sizeof(SqList),1,fp);
                q=q->next;
            }
        }
    }
    fclose(fp);
    return OK;
}
