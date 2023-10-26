#ifndef BigInteger_h
#define BigInteger_h
struct node{
    int data;
    struct node *next;
};
struct BigInteger
{
    struct node *head;
    int length;
    //int size; 
};
struct BigInteger initialize(char * );
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
struct BigInteger mod(struct BigInteger, struct BigInteger);
void display(struct BigInteger);
#endif