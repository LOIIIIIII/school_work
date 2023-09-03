#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<string>
using namespace std;
typedef struct		//图书信息定义
{
	char no[20];		//图书ISBN
	char name[50];	//图书名字
	float price; 	//图书价格
}Book;

typedef struct LNode
{
	Book data;
	struct LNode* next;
}LNode,*LinkList;

typedef struct LinkBook
{
    LinkList head;
    LinkList rear;
    int length = 0;
}LinkBook;



void showBookList() {
    printf("1.图书浏览\n");
    printf("2.图书统计\n");
    printf("3.图书插入\n");
    printf("4.图书删除\n");
    printf("5.图书查找\n");
    printf("6.价格更新\n");
    printf("7.价格排序\n");
    printf("8.逆序存储\n");
    printf("9.退出\n");
    printf("请选择选项:\n");
}

//创建链表元素
void createNode(LinkBook& Lbook, Book book)
{
    if (Lbook.head == NULL)//当链表为空时，将头尾链表同时指向一个节点
    {
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = NULL;
        Lbook.head = Lbook.rear = booknode;
        Lbook.length++;
    }
    else {//当链表不为空时，头指针不变，尾指针指向末尾
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = NULL;
        Lbook.rear->next = booknode;
        Lbook.rear = Lbook.rear->next;
        Lbook.length++;
    }
}
//清空链表
void clear(LinkBook& Lbook)
{
    if (Lbook.head == NULL)
    {
        return;
    }
    LNode* current = Lbook.head;
    LNode* nextNode = NULL;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    Lbook.head = Lbook.rear = NULL;
    Lbook.length = 0;
}
//打印链表
void PrintLink(LinkList& head)
{
    LNode* current = head;
    printf("北京林业大学图书馆计算机类图书采购列表\n");
    printf("ISBN\t书名\t定价\n");
    while (current!=NULL)
    {
        printf("%s\t%s\t%.2f\n",current->data.no,current->data.name,current->data.price);
        current = current->next;
    }
    return;
}
//文件读取存入链表
void FileReadBook(LinkBook& Lbook)
{
    FILE* fp = fopen("book.txt", "r");
    if (fp == NULL)
    {
        printf("无法打开文件\n");
        return;
    }
    // 跳过前两行（标题和类名）
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);
    //清空链表：为重新读取做准备
    clear(Lbook);
    Book book;
    while (fscanf(fp, "%s %s %f", book.no, book.name, &book.price) != EOF) {
        createNode(Lbook, book);
    }
    fclose(fp);
}
//图书呈现:
void DisplayBook(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    PrintLink(Lbook.head);
}
//图书统计:
int GetLength(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    return Lbook.length;
}
//信息输入
Book InputInfm()
{
    Book book;
    printf("ISBN:");
    scanf("%s", book.no);
    printf("书名:");
    scanf("%s", book.name);
    printf("定价:");
    scanf("%f", &book.price);
    return book;
}
//图书插入函数
void InsertNode(LinkBook& Lbook,Book book,int pos)
{
    if (pos <= 0 || pos > Lbook.length+1)
    {
        printf("无效插入位置");
        return;
    }
    //设置虚拟头结点
    LNode dummy;
    dummy.next = Lbook.head;
    //插入的前一个结点
    LNode* pre = &dummy;
    for (int i = 1; i < pos; i++)
    {
        pre = pre->next;
    }
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = book;
    newNode->next = pre->next;
    pre->next = newNode;
    if (newNode->next == NULL)
    {
        Lbook.rear = newNode;
    }
    Lbook.head = dummy.next;
    Lbook.length++;
}
//写入txt文件
void FileWriteBook(LinkBook& Lbook,const char str[])
{
    FILE* fp = fopen(str, "w");
    if (fp == NULL)
    {
        printf("无法打开文件\n");
        return;
    }
    // 写入标题和类名
    fprintf(fp, "北京林业大学图书馆计算机类图书采购列表\n");
    fprintf(fp, "ISBN\t书名\t价钱\n");
    LNode* current = Lbook.head;
    while (current)
    {
        fprintf(fp, "%s\t%s\t%.2f\n", current->data.no, current->data.name, current->data.price);
        current = current->next;
    }
    fclose(fp);
}
//图书插入操作
void InsertBook(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    Book book;
    int pos = 0;
    printf("请输入插入信息:\n");
    printf("插入位置:");
    scanf("%d", &pos);
    book = InputInfm();
    InsertNode(Lbook, book, pos);
    FileWriteBook(Lbook,"book.txt");
    PrintLink(Lbook.head);
}
//图书删除
void DeleteNode(LinkBook& Lbook, int pos)
{
    if (pos <= 0 || pos > Lbook.length)
    {
        printf("无效删除位置。\n");
        return;
    }
    LNode dummy ;
    dummy.next = Lbook.head;
    LNode* pre = &dummy;
    for (int i = 1; i < pos; i++)
    {
        pre = pre->next;
    }
    LNode* toDeleteNode = pre->next;
    pre->next = toDeleteNode->next;
    if (toDeleteNode->next = NULL)
    {
        Lbook.rear = pre;
    }        
    free(toDeleteNode);
    Lbook.head = dummy.next;
    Lbook.length--;
    PrintLink(Lbook.head);
}
void DeleteBook(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    int pos;
    printf("请输入删除的位置:\n");
    scanf("%d", &pos);
    DeleteNode(Lbook, pos);
    FileWriteBook(Lbook, "book.txt");
}
//图书查找
//pos查询
void SearchPos(LinkBook& Lbook,int pos)
{
    if (pos <= 0 || pos > Lbook.length)
    {
        printf("查找范围无效。\n");
        return ;
    }
    LNode* current;
    current = Lbook.head;
    for (int i = 1; i < pos; i++)
    {
        current = current->next;
    }
    printf("查询结果:%s\t%s\t%.2f\n", current->data.no, current->data.name, current->data.price);
    return;
}
//name查询
void FindNode(LinkBook& Lbook, char name[])
{
    if (Lbook.head == NULL)
    {
        printf("查询无果。\n");
        return;
    }
    printf("查询结果：\n");
    LinkBook Linktemp;
    Linktemp.head = NULL;
    Linktemp.rear = NULL;
    LNode* current = Lbook.head;
    while (current!=NULL)
    {
        if (strcmp(current->data.name, name) == 0)
        {
            createNode(Linktemp, current->data);
        }
        current = current->next;
    }
    PrintLink(Linktemp.head);
    clear(Linktemp);
    return;
}
void Findsituation(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    int choice = 0;
    do {

        printf("请选择查找方式:\n1.按位置进行查找\n2.按书名进行查找\n3.退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            int pos;
            printf("请选择查找位置:");
            scanf("%d", &pos);
            SearchPos(Lbook, pos);
            break;
        case 2:
            char name[50];
            printf("请输入书名:");
            scanf("%s", name);
            FindNode(Lbook, name);
            break;
        case 3:
            printf("退出\n");
            break;
        default:
            printf("选择错误，请重新选择\n");
            break;
        }
    } while (choice==1||choice==2);
}
//价格更新
void UpdatePrice(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    if (Lbook.head == NULL)
        return;
    LNode* current = Lbook.head;
    while (current)
    {
        if (current->data.price < 45.0)
        {
            current->data.price *= 1.2;
        }
        else {
            current->data.price *= 1.1;
        }
        current = current->next;
    }
    FileWriteBook(Lbook, "book.txt");
    PrintLink(Lbook.head);
    return;
}
//价格排序
LNode* merage(LNode* l1, LNode* l2)
{
    LNode dummy;
    LNode* tail = &dummy;
    while (l1 && l2)
    {
        if (l1->data.price < l2->data.price)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
LNode* merageSort(LNode* head)
{
    if (!head || !head->next)
        return head;
    //寻找链表中点
    LNode* slow = head, * fast = head;
    LNode* prev = NULL;
    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    //分割链表
    prev->next = NULL;
    //递归排序两个子链表
    LNode* l1 = merageSort(head);
    LNode* l2 = merageSort(slow);
    //合并两个有序链表
    return merage(l1, l2);
}
void sortPriceList(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    Lbook.head = merageSort(Lbook.head);
    FileWriteBook(Lbook, "book-newsort.txt");
    PrintLink(Lbook.head);
}
//逆序存储
void createRNode(LinkBook& Rbook, Book book)
{
    if (Rbook.head == NULL)//当链表为空时，将头尾链表同时指向一个节点
    {
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = NULL;
        Rbook.head = Rbook.rear = booknode;
        Rbook.length++;
    }
    else {
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = Rbook.head;
        Rbook.head = booknode;
        Rbook.length++;
    }
}
void ReverseOrder(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    if (Lbook.head == NULL)
        return;
    LNode* current = Lbook.head;
    LinkBook Rbook;
    Rbook.head = NULL;
    Rbook.rear = NULL;
    while (current)
    {
        createRNode(Rbook, current->data);
        current = current->next;
    }
    PrintLink(Rbook.head);
    FileWriteBook(Rbook,"book-newprice.txt");
    clear(Rbook);
}
int main()
{
    SetConsoleOutputCP(936);
    printf("欢迎来到校园图书管理系统\n");
    //设置选项
    int choice = 0;
    //设置头尾指针
    LinkBook LBook;
    LBook.head = LBook.rear = NULL;
    do {
        showBookList();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            DisplayBook(LBook);
            break;
        case 2:
            printf("计算机类图书总数为：%d\n",GetLength(LBook));
            break;
        case 3:
            InsertBook(LBook);
            break;
        case 4:
            DeleteBook(LBook);
            break;
        case 5:
            Findsituation(LBook);
            break;
        case 6:
            UpdatePrice(LBook);
            break;
        case 7:
            sortPriceList(LBook);
            break;
        case 8:
            ReverseOrder(LBook);
            break;
        case 9:
            printf("即将退出系统。\n");
            Sleep(1000);
            break;
        default:
            printf("无效选项，请重新选择。\n");
            break;
        }
        //每次操作清空一次链表
        clear(LBook);
        char ss[10];
        if (choice != 9)
        {
            printf("是否继续\n");
            scanf("%s", ss);
        }
        if (strcmp(ss, "是")==0)
        system("cls");
        else {
            clear(LBook);
            choice = 9;
        }
    } while (choice != 9);
    return 0;
}