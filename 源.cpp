#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<string>
using namespace std;
typedef struct		//ͼ����Ϣ����
{
	char no[20];		//ͼ��ISBN
	char name[50];	//ͼ������
	float price; 	//ͼ��۸�
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
    printf("1.ͼ�����\n");
    printf("2.ͼ��ͳ��\n");
    printf("3.ͼ�����\n");
    printf("4.ͼ��ɾ��\n");
    printf("5.ͼ�����\n");
    printf("6.�۸����\n");
    printf("7.�۸�����\n");
    printf("8.����洢\n");
    printf("9.�˳�\n");
    printf("��ѡ��ѡ��:\n");
}

//��������Ԫ��
void createNode(LinkBook& Lbook, Book book)
{
    if (Lbook.head == NULL)//������Ϊ��ʱ����ͷβ����ͬʱָ��һ���ڵ�
    {
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = NULL;
        Lbook.head = Lbook.rear = booknode;
        Lbook.length++;
    }
    else {//������Ϊ��ʱ��ͷָ�벻�䣬βָ��ָ��ĩβ
        LNode* booknode = (LNode*)malloc(sizeof(LNode));
        booknode->data = book;
        booknode->next = NULL;
        Lbook.rear->next = booknode;
        Lbook.rear = Lbook.rear->next;
        Lbook.length++;
    }
}
//�������
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
//��ӡ����
void PrintLink(LinkList& head)
{
    LNode* current = head;
    printf("������ҵ��ѧͼ��ݼ������ͼ��ɹ��б�\n");
    printf("ISBN\t����\t����\n");
    while (current!=NULL)
    {
        printf("%s\t%s\t%.2f\n",current->data.no,current->data.name,current->data.price);
        current = current->next;
    }
    return;
}
//�ļ���ȡ��������
void FileReadBook(LinkBook& Lbook)
{
    FILE* fp = fopen("book.txt", "r");
    if (fp == NULL)
    {
        printf("�޷����ļ�\n");
        return;
    }
    // ����ǰ���У������������
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);
    //�������Ϊ���¶�ȡ��׼��
    clear(Lbook);
    Book book;
    while (fscanf(fp, "%s %s %f", book.no, book.name, &book.price) != EOF) {
        createNode(Lbook, book);
    }
    fclose(fp);
}
//ͼ�����:
void DisplayBook(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    PrintLink(Lbook.head);
}
//ͼ��ͳ��:
int GetLength(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    return Lbook.length;
}
//��Ϣ����
Book InputInfm()
{
    Book book;
    printf("ISBN:");
    scanf("%s", book.no);
    printf("����:");
    scanf("%s", book.name);
    printf("����:");
    scanf("%f", &book.price);
    return book;
}
//ͼ����뺯��
void InsertNode(LinkBook& Lbook,Book book,int pos)
{
    if (pos <= 0 || pos > Lbook.length+1)
    {
        printf("��Ч����λ��");
        return;
    }
    //��������ͷ���
    LNode dummy;
    dummy.next = Lbook.head;
    //�����ǰһ�����
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
//д��txt�ļ�
void FileWriteBook(LinkBook& Lbook,const char str[])
{
    FILE* fp = fopen(str, "w");
    if (fp == NULL)
    {
        printf("�޷����ļ�\n");
        return;
    }
    // д����������
    fprintf(fp, "������ҵ��ѧͼ��ݼ������ͼ��ɹ��б�\n");
    fprintf(fp, "ISBN\t����\t��Ǯ\n");
    LNode* current = Lbook.head;
    while (current)
    {
        fprintf(fp, "%s\t%s\t%.2f\n", current->data.no, current->data.name, current->data.price);
        current = current->next;
    }
    fclose(fp);
}
//ͼ��������
void InsertBook(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    Book book;
    int pos = 0;
    printf("�����������Ϣ:\n");
    printf("����λ��:");
    scanf("%d", &pos);
    book = InputInfm();
    InsertNode(Lbook, book, pos);
    FileWriteBook(Lbook,"book.txt");
    PrintLink(Lbook.head);
}
//ͼ��ɾ��
void DeleteNode(LinkBook& Lbook, int pos)
{
    if (pos <= 0 || pos > Lbook.length)
    {
        printf("��Чɾ��λ�á�\n");
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
    printf("������ɾ����λ��:\n");
    scanf("%d", &pos);
    DeleteNode(Lbook, pos);
    FileWriteBook(Lbook, "book.txt");
}
//ͼ�����
//pos��ѯ
void SearchPos(LinkBook& Lbook,int pos)
{
    if (pos <= 0 || pos > Lbook.length)
    {
        printf("���ҷ�Χ��Ч��\n");
        return ;
    }
    LNode* current;
    current = Lbook.head;
    for (int i = 1; i < pos; i++)
    {
        current = current->next;
    }
    printf("��ѯ���:%s\t%s\t%.2f\n", current->data.no, current->data.name, current->data.price);
    return;
}
//name��ѯ
void FindNode(LinkBook& Lbook, char name[])
{
    if (Lbook.head == NULL)
    {
        printf("��ѯ�޹���\n");
        return;
    }
    printf("��ѯ�����\n");
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

        printf("��ѡ����ҷ�ʽ:\n1.��λ�ý��в���\n2.���������в���\n3.�˳�\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            int pos;
            printf("��ѡ�����λ��:");
            scanf("%d", &pos);
            SearchPos(Lbook, pos);
            break;
        case 2:
            char name[50];
            printf("����������:");
            scanf("%s", name);
            FindNode(Lbook, name);
            break;
        case 3:
            printf("�˳�\n");
            break;
        default:
            printf("ѡ�����������ѡ��\n");
            break;
        }
    } while (choice==1||choice==2);
}
//�۸����
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
//�۸�����
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
    //Ѱ�������е�
    LNode* slow = head, * fast = head;
    LNode* prev = NULL;
    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    //�ָ�����
    prev->next = NULL;
    //�ݹ���������������
    LNode* l1 = merageSort(head);
    LNode* l2 = merageSort(slow);
    //�ϲ�������������
    return merage(l1, l2);
}
void sortPriceList(LinkBook& Lbook)
{
    FileReadBook(Lbook);
    Lbook.head = merageSort(Lbook.head);
    FileWriteBook(Lbook, "book-newsort.txt");
    PrintLink(Lbook.head);
}
//����洢
void createRNode(LinkBook& Rbook, Book book)
{
    if (Rbook.head == NULL)//������Ϊ��ʱ����ͷβ����ͬʱָ��һ���ڵ�
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
    printf("��ӭ����У԰ͼ�����ϵͳ\n");
    //����ѡ��
    int choice = 0;
    //����ͷβָ��
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
            printf("�������ͼ������Ϊ��%d\n",GetLength(LBook));
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
            printf("�����˳�ϵͳ��\n");
            Sleep(1000);
            break;
        default:
            printf("��Чѡ�������ѡ��\n");
            break;
        }
        //ÿ�β������һ������
        clear(LBook);
        char ss[10];
        if (choice != 9)
        {
            printf("�Ƿ����\n");
            scanf("%s", ss);
        }
        if (strcmp(ss, "��")==0)
        system("cls");
        else {
            clear(LBook);
            choice = 9;
        }
    } while (choice != 9);
    return 0;
}