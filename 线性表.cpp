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
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���  24�ֽ�
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
status ListTrabverse(SqList L);  //�򻯹�
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
		printf("    ��ѡ����Ĳ���[0~12]:");
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
				printf("���Ա���ʧ�ܣ�\n");
			else
                if(IntiaList(data[rank])==OK)
                    printf("���Ա����ɹ�,���ǵ�%d�����Ա�\n",rank+1);
            system("pause");
			break;
		}
	    case 2:{//ok
	    	printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
	   			printf("\n�ñ����ڣ�\n");
			else
			{
				DestroyList(data[x-1]);
				printf("\n�ñ������٣�\n");
		 	}
		 	system("pause");
            break;
        }
	    case 3:{//ok
	    	printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
	   			printf("\n�ñ����ڣ�\n");
            else if(data[x-1].length==0)
	   			printf("\n�ñ���Ϊ�գ�\n");
			else
            {
                ClearList(data[x-1]);
	 			printf("\n�ñ�����գ�\n");
	 		}
	 		system("pause");
            break;
	 	}
	   	case 4:{//ok
	   		printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(ListEmpty(data[x-1])==0)
	 			printf("\n�ñ��ǿձ�\n");
			else if(ListEmpty(data[x-1])==1)
				printf("\n�ñ��ǿձ�\n");
			else
				printf("\n�ñ����ڣ�\n");
	 		system("pause");
	 		break;
	 	}
	   	case 5:{//ok
	   		printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(ListLength(data[x-1])<0)
	   			printf("\n�ñ����ڣ�\n");
			else
	   			printf("\n�ñ���Ϊ%d��\n",ListLength(data[x-1]));
	 		system("pause");
            break;
	 	}
		case 6:{//ok
		    printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n�ñ����ڣ�\n");
                system("pause");
                break;
            }
	   		printf("��ѡ����ȡλ�ã�");
	   		int i;
	   		scanf("%d",&i);
	   		status result = GetElem(data[x-1],i,e);
	 		if(result==0) printf("\n��ȡλ�ô���\n");
	 		else
                printf("\n��Ԫ��ֵΪ%d\n",e);
	 		system("pause");
	 		break;
        }
	   	case 7:{//ok
	   	    printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n�ñ����ڣ�\n");
            else
            {
                if(data[x-1].length==0)
                    printf("\n�ñ��ǿձ�\n");
                else
                {
                    printf("��ѡ���ѯԪ�أ�");
                    int e;
                    scanf("%d",&e);
                    LocateElem(data[x-1],e);
                }
            }
	 		system("pause");
	 		break;
        }
	   	case 8:{//ok
	 		printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n�ñ����ڣ�\n");
            else
            {
                printf("��ѡ����ҵ�Ԫ�أ�");
                int cur;
                scanf("%d",&cur);
                status result = PriorElem(data[x-1],cur,pre_e);
                if(result==ERROR)
                    printf("�Ҳ�����Ԫ�أ�\n");
                else if(result==INFEASTABLE)
                    printf("��Ԫ�����׽ڵ㣡\n");
                else
                    printf("��Ԫ��ǰ���ڵ�Ϊ%d��\n",pre_e);
            }
	 		system("pause");
	 		break;
	   	}
	   	case 9:{//ok
	 		printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
                printf("\n�ñ����ڣ�\n");
            else
            {
                printf("��ѡ����ҵ�Ԫ�أ�");
                int cur;
                scanf("%d",&cur);
                status result = NextElem(data[x-1],cur,next_e);
                if(result==ERROR)
                    printf("�Ҳ�����Ԫ�أ�\n");
                else if(result==INFEASTABLE)
                    printf("��Ԫ����β�ڵ㣡\n");
                else
                    printf("��Ԫ�غ�̽ڵ�Ϊ%d��\n",next_e);
            }
	 		system("pause");
	 		break;
	   	}
	   	case 10:{//ok
	   	    printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n�ñ����ڣ�\n");
                system("pause");
                break;
            }
	   		printf("��ѡ�����λ�ã�");
	   		int i;
	   		scanf("%d",&i);
	   		printf("��ѡ�����Ԫ�أ�");
	   		int e;
	   		scanf("%d",&e);
	   		status result = ListInsert(data[x-1],i,e);
		 	if(result==ERROR) printf("\n����λ�ô���\n");
            else
                printf("\n����ɹ���\n");
			system("pause");
            break;
        }
	   	case 11:{//ok
	 		 printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		if(data[x-1].listsize==0)
            {
                printf("\n�ñ����ڣ�\n");
                system("pause");
                break;
            }
	   		printf("��ѡ��ɾ��λ�ã�");
	   		int i;
	   		scanf("%d",&i);
	   		status result = ListDelete(data[x-1],i,e);
	   		if(result==ERROR) printf("\nɾ��ʧ�ܣ�\n");
	   		else
                printf("\n��ɾ��Ԫ��%d��\n",e);
	 		system("pause");
	 		break;
        }
	   	case 12:{//ok
	 		printf("��ѡ���б���ţ�[1-5]");
	   		int x;
	   		scanf("%d",&x);
	   		status result = ListTrabverse(data[x-1]);
	 		if(result<0) printf("\n�ñ����ڣ�\n");
	 		if(result=0) printf("\n�ñ��ǿձ�\n");
            system("pause");
            break;
        }
	   	case 0:
       		break;
		}//end of switch
	}//end of while
    save_data();
  	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList & L){//��ʼ���� -------1
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}
status DestroyList(SqList & L){//�����б� -------2
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
status ClearList(SqList &L){//����б� -------3
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
status ListEmpty(SqList L){//�Ƿ�Ϊ�ձ� -------4
	if(L.listsize==0) return INFEASTABLE;
	else
	{
		if(L.length!=0) return FALSE;
		else return TRUE;
	}
}
int ListLength(SqList L){//��ȡ����-------5
	if(L.listsize==0) return INFEASTABLE;
	return L.length;
}
status GetElem(SqList L,int i,ElemType & e){//��ȡԪ��-------6
    if(i<1||i>L.length) return ERROR;
    e = L.elem[i-1];
    return OK;
}
status LocateElem(SqList L,ElemType e){//Ѱ��λ��-------7
	int x=0;
    while(x<L.length){
        if(L.elem[x]==e)
            break;
        x++;
    }
    if(x==L.length&&L.elem[x-1]!=e)
        printf("�Ҳ�����Ԫ�أ�\n");
    else
        printf("����ƥ�䵽���ǵ�%d��Ԫ�أ�\n",x+1);
    return OK;
}
status PriorElem(SqList L,ElemType cur,ElemType & pre_e){//ǰ���ڵ�-------8
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
status NextElem(SqList L,ElemType cur,ElemType & next_e){//��̽ڵ�-------9
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
status ListInsert(SqList & L,int i,ElemType e){//����Ԫ�� -------10
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
status ListDelete(SqList & L,int i,ElemType & e){//ɾ��Ԫ�� -------11
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
status ListTrabverse(SqList L){//���Ԫ�� -------12
    int i=1;
    if(L.listsize==0) return INFEASTABLE;
    if(L.length!=0)
    {
        for(;i<=L.length;i++)
        {
            printf("�ñ�ĵ�%d��Ԫ��Ϊ%d\n",i,L.elem[i-1]);
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
