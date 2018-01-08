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
typedef char TElemType;   /*数据元素类型定义*/

#define LIST_INIT_SIZE 100  //索引表初始大小
#define LISTINCREMENT 10    //索引表扩大增量

//二叉树链式存储结构
typedef struct BiTNode {
    TElemType data;
    int key;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//二叉树信息结构
typedef struct {
    char name[40];
    BiTree T;
} InfoNode;

//索引表结构
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
    char fileName[40];      //文件名
    char treeName[40];      //二叉树名称
    PNode P;                //索引表结构
    InfoNode *I;            //二叉树信息结构
    BiTree T = NULL;        //二叉树
    BiTree c;               //子树
    BiTNode *node = NULL;   //二叉树结点
    TElemType e, e2;
    char definition[256];   //二叉树定义
    int index = 0;
    int LR;                 //0为左，1为右

    //初始化索引表
    P.elem = (InfoNode *)malloc(sizeof(InfoNode) * LIST_INIT_SIZE);
    P.size = LIST_INIT_SIZE;
    P.length = 0;

    //用户指定文件对二叉树初始化
    printf("是否指定文件对二叉树初始化？[n]/y\n");
    if (getchar() == 'y')
    {

        printf("Input filename:");
        scanf("%s", fileName);
        if (LoadFile(P, fileName))
        {
            printf("二叉树加载成功！\n");
        }
        else
        {
            printf("二叉树加载失败！\n");
        }
        system("pause");
    }

    //对二叉树操作
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
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
            /*初始化二叉树*/
        case 1:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (InitBiTree(P, treeName) == OK)
            {
                printf("二叉树初始化成功！\n");
            }
            else
            {
                printf("二叉树初始化失败！\n");
            }
            system("pause");
            break;

            /*销毁二叉树*/
        case 2:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (DestroyBiTree(P, treeName) == OK)
            {
                printf("二叉树销毁成功！\n");
            }
            else
            {
                printf("二叉树销毁失败！\n");
            }
            system("pause");
            break;

            /*创建二叉树*/
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
                    printf("二叉树创建成功！\n");
                }
                else
                {
                    printf("二叉树创建失败！\n");
                }
            }
            system("pause");
            break;

            /*清空二叉树*/
        case 4:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (ClearBiTree(I->T))
                {
                    printf("二叉树清空成功！\n");
                }
                else
                {
                    printf("二叉树清空失败！\n");
                }
            }
            system("pause");
            break;

            /*二叉树是否为空*/
        case 5:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (BiTreeEmpty(I->T))
                {
                    printf("二叉树为空！\n");
                }
                else
                {
                    printf("二叉树非空！\n");
                }
            }
            system("pause");
            break;

            /*二叉树深度*/
        case 6:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("二叉树的深度为%d.\n", BiTreeDepth(I->T));
            }
            system("pause");
            break;

            /*二叉树的根*/
        case 7:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                if (Root(I->T, e))
                {
                    printf("树根元素值为%c.\n", e);
                }
                else
                {
                    printf("此为空树。\n");
                }
            }
            system("pause");
            break;

            /*找到结点(Value)*/
        case 8:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入元素索引：");
                int x;scanf("%d",&x);
                if (node = Value(I->T, x))
                {
                    printf("已找到该结点，其值为%c.\n", node->data);
                }
                else
                {
                    printf("未找到该结点。\n");
                }
            }
            system("pause");
            break;

            /*给结点赋值*/
        case 9:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入索引值：");
                int x;scanf("%d",&x);
                getchar();
                printf("请输入新的元素值：");
                e2 = getchar();
                if (Assign(I->T, x, e2))
                {
                    printf("赋值成功。\n");
                }
                else
                {
                    printf("赋值失败。\n");
                }
            }
            system("pause");
            break;

            /*找到结点的父母*/
        case 10:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入元素值：");
                e = getchar();
                if (node = Parent(I->T, e))
                {
                    printf("父结点的值为%c.\n", node->data);
                }
                else
                {
                    printf("查找失败。\n");
                }
            }
            system("pause");
            break;

            /*寻找左孩子*/
        case 11:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入索引值：");
                int x;scanf("%d",&x);
                if (node = LeftChild(I->T, x))
                {
                    printf("左孩子的值为%c.\n", node->data);
                }
                else
                {
                    printf("查找失败。\n");
                }
            }
            system("pause");
            break;

            /*寻找右孩子*/
        case 12:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入索引值：");
                int x;scanf("%d",&x);
                if (node = RightChild(I->T, x))
                {
                    printf("右孩子的值为%c.\n", node->data);
                }
                else
                {
                    printf("查找失败。\n");
                }
            }
            system("pause");
            break;

            /*寻找左兄弟*/
        case 13:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入元素值：");
                e = getchar();
                if (node = LeftSibling(I->T, e))
                {
                    printf("左兄弟的值为%c.\n", node->data);
                }
                else
                {
                    printf("查找失败。\n");
                }
            }
            system("pause");
            break;

            /*寻找右兄弟*/
        case 14:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入元素值：");
                e = getchar();
                if (node = RightSibling(I->T, e))
                {
                    printf("右兄弟的值为%c.\n", node->data);
                }
                else
                {
                    printf("查找失败。\n");
                }
            }
            system("pause");
            break;

            /*插入子树*/
        case 15:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入索引值：");
                int x;scanf("%d" ,&x);
                if (node = Value(I->T, x))
                {
                    printf("要插入左子树(0)还是右子树(1)？");
                    scanf("%d", &LR);
                    getchar();
                    printf("请输入子树的定义：");
                    fgets(definition, 256, stdin);
                    index = 0;
                    CreateBiTree(c, definition, index);
                    if (InsertChild(I->T, node, LR, c))
                    {
                        printf("插入成功。\n");
                    }
                    else
                    {
                        printf("插入失败。\n");
                    }
                }
                else
                {
                    printf("未找到该结点。\n");
                }
            }
            system("pause");
            break;

            /*删除子树*/
        case 16:
            printf("Please input tree name:");
            scanf("%s", treeName);
            getchar();
            if (I = SearchBiTree(P, treeName))
            {
                printf("请输入索引值：");
                int x;scanf("%d" ,&x);
                if (node = Value(I->T, x))
                {
                    printf("要删除左子树(0)还是右子树(1)？");
                    scanf("%d", &LR);
                    if (DeleteChild(I->T, node, LR))
                    {
                        printf("删除成功。\n");
                    }
                    else
                    {
                        printf("删除失败。\n");
                    }
                }
                else
                {
                    printf("未找到该结点。\n");
                }
            }
            system("pause");
            break;

            /*先序遍历二叉树*/
        case 17:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("先序遍历的结果为：\n");
                PreOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*中序遍历二叉树*/
        case 18:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("中序遍历的结果为：\n");
                InOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*后序遍历二叉树*/
        case 19:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("后序遍历的结果为：\n");
                PostOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*层序遍历二叉树*/
        case 20:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("层序遍历的结果为：\n");
                LevelOrderTraverse(I->T);
            }
            system("pause");
            break;

            /*形象展示二叉树*/
        case 21:
            printf("Please input tree name:");
            scanf("%s", treeName);
            if (I = SearchBiTree(P, treeName))
            {
                printf("二叉树如下所示：\n");
                Display(I->T, 0);
            }
            system("pause");
            break;

            /*退出*/
        case 0:
            printf("是否要保存二叉树？y/[n]\n");
            if (getchar() == 'y')
            {
                printf("请输入文件名：");
                if (scanf("%s", fileName) && SaveFile(P, fileName))
                {
                    printf("保存成功！\n");
                }
                else
                {
                    printf("保存失败！\n");
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
    printf("未找到二叉树！\n");
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
