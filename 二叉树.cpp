#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef char TElemType;   /*����Ԫ�����Ͷ���*/

#define LIST_INIT_SIZE 100  //�������ʼ��С
#define LISTINCREMENT 10    //��������������

//��������ʽ�洢�ṹ
typedef struct BiTNode {
    TElemType data;
    int key;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//��������Ϣ�ṹ
typedef struct {
    char name[40];
    BiTree T;
} InfoNode;

//������ṹ
typedef struct {
    InfoNode * elem;
    int length;
    int size;
} PNode;

status InitBiTree(PNode &P, char *name);
status DestroyBiTree(PNode &P, char *name);
status CreateBiTree(BiTree &T, char *definition, int &index);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
status Root(BiTree T, TElemType &e);
BiTNode *Value(BiTree T, int x);
status Assign(BiTree T, int x, TElemType value);
BiTNode *Parent(BiTree T, TElemType e);
BiTNode *LeftChild(BiTree T, int x);
BiTNode *RightChild(BiTree T, int x);
BiTNode *LeftSibling(BiTree T, TElemType e);
BiTNode *RightSibling(BiTree T, TElemType e);
status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c);
status DeleteChild(BiTree T, BiTNode *p, int LR);
status PreOrderTraverse(BiTree T);
status InOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
status LevelOrderTraverse(BiTree T);
status Display(BiTree T, int depth);
InfoNode *SearchBiTree(PNode P, char *name);
status LoadFile(PNode &P, char *filename);
status SaveFile(PNode P, char *filename);
status fprintfDefinition(BiTree T, FILE *fp);


int main(int argc, char *argv[])
{
    char fileName[40];      //�ļ���
    char treeName[40];      //����������
    PNode P;                //������ṹ
    InfoNode *I;            //��������Ϣ�ṹ
    BiTree T = NULL;        //������
    BiTree c;               //����
    BiTNode *node = NULL;   //���������
    TElemType e, e2;
    char definition[256];   //����������
    int index = 0;
    int LR;                 //0Ϊ��1Ϊ��

    //��ʼ��������
    P.elem = (InfoNode *)malloc(sizeof(InfoNode) * LIST_INIT_SIZE);
    P.size = LIST_INIT_SIZE;
    P.length = 0;

    //�û�ָ���ļ��Զ�������ʼ��
    printf("�Ƿ�ָ���ļ��Զ�������ʼ����[n]/y\n");
    if (getchar() == 'y')
    {

        printf("Input filename:");
        scanf("%s", fileName);
        if (LoadFile(P, fileName))
        {
            printf("���������سɹ���\n");
        }
        else
        {
            printf("����������ʧ�ܣ�\n");
        }
        system("pause");
    }

    //�Զ���������
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("                      Menu                  \n");
        printf("-------------------------------------------------\n");
        printf("         1. InitBiTree       12. RightChild\n");
        printf("         2. DestroyBiTree    13. LeftSibling\n");
        printf("         3. CreateBiTree     14. RightSibling\n");
        printf("         4. ClearBiTree      15. InsertChild\n");
        printf("         5. BiTreeEmpty      16. DeleteChild\n");
        printf("         6. BiTreeDepth      17. PreOrderTraverse\n");
        printf("         7. Root             18. InOrderTraverse\n");
        printf("         8. Value            19. PostOrderTraverse\n");
        printf("         9. Assign           20. LeverOrderTraverse\n");
        printf("        10. Parent           \n");
        printf("        11. LeftChild         0. exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
            /*��ʼ��������*/
        case 1:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (InitBiTree(P, treeName) == OK)
            {
                printf("��������ʼ���ɹ���\n");
            }
            else
            {
                printf("��������ʼ��ʧ�ܣ�\n");
            }
            system("pause");
            break;

            /*���ٶ�����*/
        case 2:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (DestroyBiTree(P, treeName) == OK)
            {
                printf("���������ٳɹ���\n");
            }
            else
            {
                printf("����������ʧ�ܣ�\n");
            }
            system("pause");
            break;

            /*����������*/
        case 3:
            index=0;
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("Please input definition:\n");
                fgets(definition, 256, stdin);
                if (CreateBiTree(I->T, definition, index))
                {
                    printf("�����������ɹ���\n");
                }
                else
                {
                    printf("����������ʧ�ܣ�\n");
                }
            }
            system("pause");
            break;

            /*��ն�����*/
        case 4:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (ClearBiTree(I->T))
                {
                    printf("��������ճɹ���\n");
                }
                else
                {
                    printf("���������ʧ�ܣ�\n");
                }
            }
            system("pause");
            break;

            /*�������Ƿ�Ϊ��*/
        case 5:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (BiTreeEmpty(I->T))
                {
                    printf("������Ϊ�գ�\n");
                }
                else
                {
                    printf("�������ǿգ�\n");
                }
            }
            system("pause");
            break;

            /*���������*/
        case 6:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("�����������Ϊ%d.\n", BiTreeDepth(I->T));
            }
            system("pause");
            break;

            /*�������ĸ�*/
        case 7:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (Root(I->T, e))
                {
                    printf("����Ԫ��ֵΪ%c.\n", e);
                }
                else
                {
                    printf("��Ϊ������\n");
                }
            }
            system("pause");
            break;

            /*�ҵ����(Value)*/
        case 8:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("������Ԫ��������");
                int x;scanf("%d",&x);
                if (node = Value(I->T, x))
                {
                    printf("���ҵ��ý�㣬��ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("δ�ҵ��ý�㡣\n");
                }
            }
            system("pause");
            break;

            /*����㸳ֵ*/
        case 9:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("����������ֵ��");
                int x;scanf("%d",&x);
                getchar();
                printf("�������µ�Ԫ��ֵ��");
                e2 = getchar();
                if (Assign(I->T, x, e2))
                {
                    printf("��ֵ�ɹ���\n");
                }
                else
                {
                    printf("��ֵʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*�ҵ����ĸ�ĸ*/
        case 10:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("������Ԫ��ֵ��");
                e = getchar();
                if (node = Parent(I->T, e))
                {
                    printf("������ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*Ѱ������*/
        case 11:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("����������ֵ��");
                int x;scanf("%d",&x);
                if (node = LeftChild(I->T, x))
                {
                    printf("���ӵ�ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*Ѱ���Һ���*/
        case 12:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("����������ֵ��");
                int x;scanf("%d",&x);
                if (node = RightChild(I->T, x))
                {
                    printf("�Һ��ӵ�ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*Ѱ�����ֵ�*/
        case 13:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("������Ԫ��ֵ��");
                e = getchar();
                if (node = LeftSibling(I->T, e))
                {
                    printf("���ֵܵ�ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*Ѱ�����ֵ�*/
        case 14:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("������Ԫ��ֵ��");
                e = getchar();
                if (node = RightSibling(I->T, e))
                {
                    printf("���ֵܵ�ֵΪ%c.\n", node->data);
                }
                else
                {
                    printf("����ʧ�ܡ�\n");
                }
            }
            system("pause");
            break;

            /*��������*/
        case 15:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("����������ֵ��");
                int x;scanf("%d" ,&x);
                if (node = Value(I->T, x))
                {
                    printf("Ҫ����������(0)����������(1)��");
                    scanf("%d", &LR);
                    getchar();
                    printf("�����������Ķ��壺");
                    fgets(definition, 256, stdin);
                    index = 0;
                    CreateBiTree(c, definition, index);
                    if (InsertChild(I->T, node, LR, c))
                    {
                        printf("����ɹ���\n");
                    }
                    else
                    {
                        printf("����ʧ�ܡ�\n");
                    }
                }
                else
                {
                    printf("δ�ҵ��ý�㡣\n");
                }
            }
            system("pause");
            break;

            /*ɾ������*/
        case 16:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("����������ֵ��");
                int x;scanf("%d" ,&x);
                if (node = Value(I->T, x))
                {
                    printf("Ҫɾ��������(0)����������(1)��");
                    scanf("%d", &LR);
                    if (DeleteChild(I->T, node, LR))
                    {
                        printf("ɾ���ɹ���\n");
                    }
                    else
                    {
                        printf("ɾ��ʧ�ܡ�\n");
                    }
                }
                else
                {
                    printf("δ�ҵ��ý�㡣\n");
                }
            }
            system("pause");
            break;

            /*�������������*/
        case 17:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("��������Ľ��Ϊ��\n");
                PreOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*�������������*/
        case 18:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("��������Ľ��Ϊ��\n");
                InOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*�������������*/
        case 19:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("��������Ľ��Ϊ��\n");
                PostOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*�������������*/
        case 20:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("��������Ľ��Ϊ��\n");
                LevelOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*����չʾ������*/
        case 21:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("������������ʾ��\n");
                Display(I->T, 0);
            }
            system("pause");
            break;

            /*�˳�*/
        case 0:
            printf("�Ƿ�Ҫ�����������y/[n]\n");
            if (getchar() == 'y')
            {
                printf("�������ļ�����");
                if (scanf("%s", fileName) && SaveFile(P, fileName))
                {
                    printf("����ɹ���\n");
                }
                else
                {
                    printf("����ʧ�ܣ�\n");
                }
                system("pause");
            }
            break;
        default:
            break;
        }
    }
}
status InitBiTree(PNode &P, char *name)
{
    if (P.length >= P.size)
    {
        InfoNode *newbase;
        newbase = (InfoNode *)realloc(P.elem, (P.size + LISTINCREMENT) * sizeof(InfoNode));
        if (!newbase)
        {
            return OVERFLOW;
        }
        P.elem = newbase;
        P.size += LISTINCREMENT;
    }

    strcpy(P.elem[P.length].name, name);
    P.elem[P.length].T = NULL;
    P.length++;
    return OK;
}
status DestroyBiTree(PNode &P, char *name)
{
    for (int i = 0; i < P.length; i++)
    {
        if (strcmp(P.elem[i].name, name) == 0)
        {
            ClearBiTree(P.elem[i].T);
            for (;i < P.length - 1; i++)
            {
                strcpy(P.elem[i].name, P.elem[i + 1].name);
                P.elem[i].T = P.elem[i + 1].T;
            }
            P.length--;
            return OK;
        }
    }
    return ERROR;
}
status CreateBiTree(BiTree &T, char *defination, int &index)
{
    if (defination[index++] != ' ' && defination[index - 1] != '\n')
    {
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        {
            exit(OVERFLOW);
        }
        T->data = defination[index - 1];
        T->key = index;
        T->lchild = NULL;
        T->rchild = NULL;
        CreateBiTree(T->lchild, defination, index);
        CreateBiTree(T->rchild, defination, index);
    }
    return OK;
}
status ClearBiTree(BiTree &T)
{
    if (T)
    {
        ClearBiTree(T->lchild);
        ClearBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return OK;
}
status BiTreeEmpty(BiTree T)
{
    if (T == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int BiTreeDepth(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    int leftDepth = BiTreeDepth(T->lchild);
    int rightDepth = BiTreeDepth(T->rchild);
    return (leftDepth >= rightDepth) ? leftDepth + 1 : rightDepth + 1;
}
status Root(BiTree T, TElemType &e)
{
    if (T)
    {
        e = T->data;
        return OK;
    }
    return ERROR;
}
BiTNode * Value(BiTree T, int x)
{
    if (T == NULL)
    {
        return NULL;
    }
    if (T->key == x)
    {
        return T;
    }
    BiTNode *node;
    if (node = Value(T->lchild, x))
    {
        return node;
    }
    else
    {
        return Value(T->rchild, x);
    }
}
status Assign(BiTree T,int x, TElemType value)
{
    BiTNode *node;
    if (node = Value(T, x))
    {
        node->data = value;
        return OK;
    }
    return ERROR;
}
BiTNode *Parent(BiTree T, TElemType e)
{
    if (T == NULL)
    {
        return NULL;
    }
    BiTNode *node;
    BiTNode *result;
    if (node = T->lchild)
    {
        if (node->data == e)
        {
            return T;
        }
        else if (result = Parent(node, e))
        {
            return result;
        }
    }
    if (node = T->rchild)
    {
        if (node->data == e)
        {
            return T;
        }
        else if (result = Parent(node, e))
        {
            return result;
        }
    }
    return NULL;
}
BiTNode *LeftChild(BiTree T, int x)
{
    BiTNode *node = Value(T, x);
    if (node)
    {
        return node->lchild;
    }
    return NULL;
}
BiTNode *RightChild(BiTree T, int x)
{
    BiTNode *node = Value(T, x);
    if (node)
    {
        return node->rchild;
    }
    return NULL;
}
BiTNode *LeftSibling(BiTree T, TElemType e)
{
    BiTNode *node = Parent(T, e);
    if (node && node->lchild && node->lchild->data != e)
    {
        return node->lchild;
    }
    return NULL;
}
BiTNode *RightSibling(BiTree T, TElemType e)
{
    BiTNode *node = Parent(T, e);
    if (node && node->rchild && node->rchild->data != e)
    {
        return node->rchild;
    }
    return NULL;
}
status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c)
{
    if (!c || c->rchild)
    {
        return ERROR;
    }
    if (LR == 0)
    {
        c->rchild = p->lchild;
        p->lchild = c;
    }
    else
    {
        c->rchild = p->rchild;
        p->rchild = c;
    }
    return OK;
}
status DeleteChild(BiTree T, BiTNode *p, int LR)
{
    if (LR == 0)
    {
        ClearBiTree(p->lchild);
    }
    else
    {
        ClearBiTree(p->rchild);
    }
    return OK;
}
status PreOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return OK;
    }
    BiTNode *node;
    BiTNode *stack[80];
    stack[0] = T;
    int length = 1;
    while (length > 0)
    {
        length--;
        node = stack[length];
        printf("%c ", node->data);
        if (stack[length] = node->rchild)
        {
            length++;
        }
        if (stack[length] = node->lchild)
        {
            length++;
        }
    }
    return OK;
}
status InOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return OK;
    }
    InOrderTraverse(T->lchild);
    printf("%c ", T->data);
    InOrderTraverse(T->rchild);
    return OK;
}
status PostOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return OK;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c ", T->data);
    return OK;
}
status LevelOrderTraverse(BiTree T)
{
    BiTNode *queue[300];
    BiTNode *node;
    int head = 0, rear = 0;
    if (T == NULL)
    {
        return OK;
    }
    queue[head++] = T;
    while (head > rear)
    {
        if (node = queue[rear]->lchild)
        {
            queue[head++] = node;
        }
        if (node = queue[rear]->rchild)
        {
            queue[head++] = node;
        }
        printf("%c ", queue[rear++]->data);
    }
    return OK;
}
status Display(BiTree T, int depth)
{
    if (T == NULL)
    {
        return OK;
    }
    for (int i = 0; i < depth; i++)
    {
        putchar('\t');
    }
    printf("%c\n", T->data);
    Display(T->lchild, depth + 1);
    Display(T->rchild, depth + 1);
    return OK;
}
InfoNode *SearchBiTree(PNode P, char *name)
{
    for (int i = 0; i < P.length; i++)
    {
        if (strcmp(P.elem[i].name, name) == 0)
        {
            return P.elem + i;
        }
    }
    printf("δ�ҵ���������\n");
    return NULL;
}
status LoadFile(PNode &P, char *filename)
{
    FILE *fp;
    char treeName[40];
    char definition[256];
    int index;

    if (fp = fopen(filename, "r"))
    {
        getc(fp);
        while (!feof(fp))
        {
            if (fscanf(fp, "%s", treeName) != -1)
            {
                InitBiTree(P, treeName);
                getc(fp);
                fgets(definition, 256, fp);
                index = 0;
                CreateBiTree(P.elem[P.length - 1].T, definition, index);
            }
            getc(fp);
        }
        fclose(fp);
        return OK;
    }
    else
    {
        return ERROR;
    }
}
status SaveFile(PNode P, char *filename)
{
    FILE *fp;
    if (fp = fopen(filename, "w"))
    {
        int index;
        for (index = 0; index < P.length; fputc('\n', fp), index++)
        {
            fprintf(fp, " %s ", P.elem[index].name);
            fprintfDefinition(P.elem[index].T, fp);
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
}
status fprintfDefinition(BiTree T, FILE *fp)
{
    if (T)
    {
        fputc(T->data, fp);
        fprintfDefinition(T->lchild, fp);
        fprintfDefinition(T->rchild, fp);
    }
    else
    {
        fputc(' ', fp);
    }
    return OK;
}
