#include"BigInteger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BigInteger initialize(char *);
struct node *newNode(int);
void reverse(struct node **);
int calclength(struct node *);
void display(struct BigInteger);
struct BigInteger add(struct BigInteger, struct BigInteger);
struct BigInteger sub(struct BigInteger, struct BigInteger);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
struct BigInteger mod(struct BigInteger, struct BigInteger);
int compare(struct BigInteger ,struct BigInteger );
void swap(struct node **,struct node **);
void remzero(struct BigInteger);

struct node *newNode(int val)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        return;
    }
    else
        temp->data = val;
        temp->next = NULL;
        return temp;
}
void reverse(struct node **head)
{
    struct node *cur = *head, *nxt = NULL, *prev = NULL;
    while (cur != NULL)
    {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    *head = prev;
}
int calclength(struct node *head)
{
    int c = 0;
    while (head)
    {
        c++;
        head = head->next;
    }
    return c;
}
struct BigInteger initialize(char *num)
{
    struct BigInteger new ;
    new.length = 0;
    new.head = NULL; // Initialize head to NULL

    if (!num)
    {
        return new;
    }

    int len;
    for (len = 0; num[len] != '\0'; len++);
    //here new is of type bigint
    
    new.length = len;
    
    struct node *itr = NULL;
    for (int i = len - 1; i >= 0; i--)
    {
        if (new.head == NULL)
        {
            int d = num[i] - '0';
            new.head = newNode(d);
            itr = new.head;
        }
        else
        {
            int d = num[i] - '0';
            itr->next = newNode(d);
            itr = itr->next;
        }
    }

    return new;//returning bigint new
}

void display(struct BigInteger result)
{
    
    //here temp is struct node type
    reverse(&(result.head));
    struct node *temp=result.head;
    if(result.head == NULL)
    {
        printf("linked list is empty \n");
        return;
    }
    while(temp->data==0&&temp->next!=NULL)
    {
        temp=temp->next;
    }
    if(temp==NULL)
    {
        printf("\n0\n");
        return;
    }
    printf("\n");
    while(temp != NULL)
    {
        printf("%d", temp->data); 
        temp = temp->next;                
    }
    reverse(&(result.head));
}

void remzero(struct BigInteger a)//changed
{
    struct node * itr = a.head,*temp=NULL,*prev=NULL;
    
    int f=0;
    while(itr!=NULL)
    {
        if(itr->data==0)
        {
            if(f==0)
            {
                temp=itr;
                f=1;
            }
        }
        else{
            prev=itr;
            temp=NULL;
            f=0;
        }
        itr=itr->next;
    }
    if(temp==a.head)
    {
        a.head=NULL;
        a.head=newNode(0);
        a.length=1;
        return;
    }
    itr=temp;
    prev->next=NULL;
    while(itr!=NULL)
    {
        temp=itr;
        itr=itr->next;
        free(temp);
    }
    
}

int compare(struct BigInteger a,struct BigInteger b)//entire function acc to sir
{
    remzero(a);
    remzero(b);//bi changed
    a.length = calclength(a.head);
    b.length = calclength(b.head);
    if(a.length < b.length)
    {
        return 1;
    }
    if(a.length>b.length)
    {
        return 0;
    }
    struct node * itr1=a.head , *itr2=b.head ;
    
    int flag =0;
    while(itr1)
    {
        if(itr1->data>itr2->data)
        {
            flag=0;
        }
        else if(itr1->data<itr2->data)
        {
            flag=1;
        }
        itr1=itr1->next;
        itr2=itr2->next;
    }
    return flag;
}

void swap(struct node ** n1,struct node ** n2)
{
    struct node*temp;
    temp=*n1;
    *n1=*n2;
    *n2=temp;
}

struct BigInteger add(struct BigInteger num1, struct BigInteger num2)
{
    
    struct BigInteger res;
    res.length = 0;
    res.head = NULL;

    struct node *p1 = num1.head;
    struct node *p2 = num2.head;
    int carry = 0, sum = 0;
    struct node *result = NULL;
    struct node *itr = NULL;

    while (p1 && p2)
    {
        sum = p1->data + p2->data + carry;
        carry = sum / 10;
        sum = sum % 10;

        if (result == NULL)
        {
            result = newNode(sum);
            itr = result;
        }
        else
        {
            itr->next = newNode(sum);
            itr = itr->next;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    // Handle remaining digits in num1 or num2
    struct node *remaining = (p1 ? p1 : p2);
    while (remaining)
    {
        sum = remaining->data + carry;
        carry = sum / 10;
        sum = sum % 10;

        itr->next = newNode(sum);
        itr = itr->next;

        remaining = remaining->next;
    }

    // If there's a carry, add it as a new node
    if (carry != 0)
    {
        itr->next = newNode(carry);
    }

    res.head = result;
    remzero(res);
    return res;
}

struct BigInteger sub(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger res;
    res.length = 0;
    res.head = NULL;
    struct node *p1 = num1.head;
    struct node *p2 = num2.head;
    if(compare(num1,num2)==1)
    {
        swap(&p1,&p2);
    }
    struct node *result = NULL;
    struct node *itr = NULL;
    int diff = 0 ;
    while (p1 && p2)
    {   
        if(p1->data<p2->data)
        {
            p1->data=p1->data+10;
            p1->next->data = p1->next->data - 1;
        }
        diff=p1->data - p2->data;
        if (result == NULL)
        {
            result = newNode(diff);
            itr = result;
        }
        else
        {
            itr->next = newNode(diff);
            itr = itr->next;
        }

        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1 && !p2)
    {
        if(p1->data==-1&&p1->next!=NULL)
        {
            p1->data=p1->data+10;
            p1->next->data = p1->next->data - 1;
        }
        diff=p1->data;

        itr->next = newNode(diff);
        itr = itr->next;
        p1 = p1->next;
    }
    res.head = result;
    remzero(res);
    return res;

}

struct BigInteger mul(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger res;
    res.length = 0;
    res.head = NULL;
    struct node *p1 = num1.head;
    struct node *p2 = num2.head;
    
    int carry = 0, prod = 0;
    struct BigInteger result;
    result.head = NULL;
    struct BigInteger product;
    product.head = NULL;
    struct node *itr = NULL;
    int l2=num2.length;
    int i=0;
    while(p1&&p2)
    {
        carry=0;
        product.head=NULL;
        struct node *n1=p1;
        if(p2->data==0)
        {
            i++;
            p2=p2->next;
            continue;
        }
        if(i<l2)
        {
            for(int j=l2-i;j<l2;j++)
            {
            if (product.head == NULL)
        {
            product.head = newNode(0);
            itr = product.head;
        }
        else
        {
            itr->next = newNode(0);
            itr = itr->next;
        }
        }
        }
        i++;
        while (n1)
        {
        prod = n1->data * p2->data + carry;
        carry = prod / 10;
        prod = prod % 10;

        if (product.head == NULL)
        {
            product.head = newNode(prod);
            itr = product.head;
        }
        else
        {
            itr->next = newNode(prod);
            itr = itr->next;
        }
        n1 = n1->next;
        }
        
        if(carry != 0)
        {
        itr->next = newNode(carry);
        }
        if(result.head==NULL)
        {
            result.head=product.head;
        }
        else
        {
            result=add(result,product);
        }
        p2 = p2->next;
    }
    remzero(result);
    return result;
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger remainder;
    remainder=num1;
    struct BigInteger quotient;
    struct BigInteger plus;
    quotient.head=newNode(0);
    quotient.length=0;
    plus.head=newNode(1);
    if (compare(remainder, num2) == 1) 
    {
        return quotient;  // Division by zero, return 0.
    }
    while(compare(remainder,num2)!=1)
    {
        remainder=sub(remainder,num2);
        quotient=add(quotient,plus);
    }
    remzero(quotient);
    return quotient;

}

struct BigInteger mod(struct BigInteger num1, struct BigInteger num2)
{
    struct BigInteger remainder;
    remainder=num1;
    struct BigInteger quotient;
    struct BigInteger plus;
    quotient.head=newNode(0);
    quotient.length=0;
    
    plus.head=newNode(1);
    if (compare(remainder, num2) == 1) {
        return quotient;  // Division by zero, return 0.
    }
    
    while(compare(remainder,num2)!=1)
    {
        remainder=sub(remainder,num2);
        quotient=add(quotient,plus);
    }
    remzero(remainder);
    return remainder;
}
