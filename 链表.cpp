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
status ListTrabverse(ListHead L);  //�򻯹�
int read_data(void);
int save_data(void);
int main(void){
    int option;
    system("cls");
    printf("�Ƿ��ȡ�ļ���(0:����ȡ,1:��ȡ)");
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
		printf("    ��ѡ����Ĳ���[0~12]:");
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
				printf("���Ա���ʧ�ܣ�\n");
			else
                if(IntiaList(data[rank])==OK)
                    printf("���Ա����ɹ�,���ǵ�%d�����Ա�\n",rank+1);
            system("pause");
			break;
		}
	    case 2:{
	        printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = DestroyList(data[x-1]);
	   		if(result==OK) printf("�ñ������٣�\n");
		 	system("pause");
            break;
        }
	    case 3:{
	        printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = ClearList(data[x-1]);
	   		if(result==OK) printf("�ñ�����գ�\n");
	 		system("pause");
            break;
	 	}
	   	case 4:{
	   	    printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		ListEmpty(data[x-1]);
	 		system("pause");
	 		break;
	 	}
	   	case 5:{
	   	    printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].exist==0) printf("�ñ����ڣ�\n");
	   		else printf("��%d����ĳ���Ϊ%d!\n",x,ListLength(data[x-1]));
	 		system("pause");
            break;
	 	}
		case 6:{
		    int x,i;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("������Ԫ��λ�ã�");
	   		scanf("%d",&i);
	   		status result = GetElem(data[x-1],i,e);
	   		if(result==OK) printf("��ȡ��Ԫ��ֵΪ%d��\n",e);
	 		system("pause");
	 		break;
        }
	   	case 7:{
	   	    int x,i;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("��������ҵ�Ԫ�أ�");
	   		scanf("%d",&i);
	   		LocateElem(data[x-1],i);
	 		system("pause");
	 		break;
        }
	   	case 8:{
	   	    int x,cur;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("������Ԫ��ֵ��");
	   		scanf("%d",&cur);
	   	    status result = PriorElem(data[x-1],cur,pre_e);
	   	    if(result==OK) printf("��Ԫ��ǰ���ڵ�Ϊ%d��\n",pre_e);
	 		system("pause");
	 		break;
	   	}
	   	case 9:{
	   	    int x,cur;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("������Ԫ��ֵ��");
	   		scanf("%d",&cur);
	   	    status result = NextElem(data[x-1],cur,next_e);
	   	    if(result==OK) printf("��Ԫ�غ�̽ڵ�Ϊ%d��\n",next_e);
	 		system("pause");
	 		break;
	   	}
	   	case 10:{
	   	    int x,i;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("���������λ�ã�");
	   		scanf("%d",&i);
	   		printf("���������Ԫ�أ�");
	   		scanf("%d",&e);
	   		status result = ListInsert(data[x-1],i,e);
	   		if(result==OK) printf("����ɹ���\n");
			system("pause");
            break;
        }
	   	case 11:{
	   	    int x,i;
		    printf("��ѡ���б���ţ�[1-5]");
	   		scanf("%d",&x);
	   		printf("������ɾ��λ�ã�");
	   		scanf("%d",&i);
	   		status result = ListDelete(data[x-1],i,e);
	   		if(result==OK) printf("ɾ���ɹ���\n");
	 		system("pause");
	 		break;
        }
	   	case 12:{
	   	    int x;
		    printf("��ѡ���б���ţ�[1-5]");
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
    printf("�˳�ǰ�Ƿ񱣴棿(0:������,1:����)");
    scanf("%d",&option);
    if(option==1)
        save_data();
  	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
status IntiaList(ListHead &L){
    L.exist=1;
	L.next=NULL;
	L.length=0;
	return OK;
}
status DestroyList(ListHead &L){
    if(L.exist==0){
        printf("�ñ����ڣ�\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ���Ϊ�գ�\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0)
        printf("�ñ��ǿձ�\n");
    else printf("�ñ��ǿձ�\n");
    return OK;
}
int ListLength(ListHead L){
    return L.length;
}
status GetElem(ListHead L,int i,ElemType & e){
    if(L.exist==0){
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length){
        printf("��ȡλ�ô���\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
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
            printf("�Ҳ�����Ԫ�أ�\n");
        else
            printf("����ƥ�䵽���ǵ�%d��Ԫ�أ�\n",x+1);
            return OK;
    }
}
status PriorElem(ListHead L,ElemType cur,ElemType & pre_e){
    if(L.exist==0){
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
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
        printf("�Ҳ�����Ԫ�أ�\n");
        return ERROR;
    }
    else if(x == 0){
        printf("��Ԫ�����׽ڵ㣡\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
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
        printf("�Ҳ�����Ԫ�أ�\n");
        return ERROR;
    }
    else if(x == L.length-1){
        printf("��Ԫ����β�ڵ㣡\n");
        return INFEASTABLE;
    }
    else next_e = p->next->elem;
    return OK;
}
status ListInsert(ListHead & L,int i,ElemType e){
    if(L.exist==0){
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length+1){
        printf("����λ�ô���\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
        return INFEASTABLE;
    }
    else if(i<1||i>L.length){
        printf("ɾ��λ�ô���\n");
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
        printf("�ñ����ڣ�\n");
        return INFEASTABLE;
    }
    else if(L.length==0){
        printf("�ñ��ǿձ�\n");
        return INFEASTABLE;
    }
    SqList *p = L.next;
    for(int x=0;x<L.length;x++){
        printf("�ñ�ĵ�%d��Ԫ��Ϊ%d\n",x+1,p->elem);
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
