#include <stdio.h>
#include <stdlib.h>

int NUMBER; // Global variable for divisor for remainder

// structure to store the numbers
struct node
{
    int data;
    struct node *next;
};

typedef struct node *Node; // typecasting for struct node

// structure for remainder store and struct node linkage and next structure link
struct valueNode
{
    int value;
    struct node *node;
    struct valueNode *next;
};

typedef struct valueNode *ValueNode; // typecasting for struct valueNode

// Dynamic memory allocation for struct node
Node createLocationNode(Node temp)
{
    temp = (Node)malloc(1 * sizeof(struct node));
    return temp;
}

// Dynamic memory allocation for struct Vlauenode
ValueNode createlLocationValuenode(ValueNode temp)
{
    temp = (ValueNode)malloc(1 * sizeof(struct valueNode));
    return temp;
}

// Dynamic Creation of Valuenodes upon User range assigning initial values;
ValueNode CreateInitial(int rem, int re[])
{
    ValueNode temp[rem];
    int i;
    for (i = 0; i < rem; i++)
    {
        temp[i] = createlLocationValuenode(temp[i]);
        temp[i]->node = NULL;
        temp[i]->value = re[i];
        if (i > 0)
        {
            temp[i - 1]->next = temp[i];
        }
    }
    temp[i - 1]->next = NULL;

    return temp[0];
}

// Inserting at last Implementation
void Insert(int num, ValueNode root)
{
    int rem = num % 10;
    ValueNode current = root;
    Node temp;
    while (current != NULL && current->value != rem) // Identify the correct remainder valued ValueNode to inserting Node
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Invalid Value\n");
    }
    else
    {
        temp = createLocationNode(temp); // dynamically allocating memory for node
        temp->data = num;
        temp->next = NULL;
        if (current->node == NULL)//checking for No-node;
        {
            current->node = temp;
        }
        else
        {
            Node temp1 = current->node;
            while (temp1->next != NULL)//traversing for last node
            {
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
    }
}

//Searing the value and getting corresponding output
void Search(int num, ValueNode root)
{
    int rem = num % NUMBER;
    ValueNode current = root;
    while (current != NULL && current->value != rem)// Identifying correct ValueNode based on remainder
    {
        current = current->next;
    }
    if (current == NULL)//identify remainder is with repect to ValueNode
    {
        printf("Not found Value\n");
    }
    else
    {
        Node temp = current->node;
        while (temp != NULL && temp->data != num)//traverse for required value;
        {
            temp = temp->next;
        }
        if (temp != NULL)//finding the value
        {
            printf("Found Value\n");
        }
        else
        {
            printf("Not found Value\n");
        }
    }
}

//Deleting the node based on the values
void Delete(int num, ValueNode root)
{
    int rem = num % 10;
    ValueNode current = root;
    while (current != NULL && current->value != rem)//identifying the ValueNode based on remiander
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("No such Value Found to delete\n");
    }
    else
    {
        Node temp = current->node, prev = NULL, next = NULL;
        while (temp != NULL && temp->data != num)   //traverse nade for data
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)   //absent of Value
        {
            printf("No such Value Found to delete\n");
        }
        else
        {
            if (temp->next == NULL && prev == NULL)//checking for Single Node
            {
                free(temp);
                current->node = NULL;
            }
            else
            {
                if (temp->next != NULL && prev == NULL)//checking for first-node deletion
                {
                    next = temp->next;
                    current->node = next;
                }
                else if (temp->next != NULL && prev != NULL)//checking for b/w node deletion
                {
                    next = temp->next;
                    prev->next = next;
                }
                else //checking for rear node deletion
                {
                    prev->next = NULL;
                }
                free(temp);
            }
            printf("Value deleted\n");
        }
    }
}

//Displaying the values based on remainder-values individually
void Display(ValueNode root)
{
    ValueNode current = root;
    Node temp = NULL;
    while (current != NULL) // loop for ValueNOde
    {
        temp = current->node;
        printf("%d %%=\t", current->value);//printing remainder values
        if (temp == NULL)
        {
            printf("Empty");
        }
        else
        {
            while (temp != NULL) //loop for node
            {
                printf("%d\t", temp->data);//printing values
                temp = temp->next;
            }
        }
        printf("\n");
        current = current->next;
    }
    return;
}

//Main function
void main()
{
    int choice, num, rem, re[10];
    printf("Enter the Divisor Number for remainder\n"); //Divisor input for Remainder
    scanf("%d", &NUMBER);
    printf("Enter the How Many Remainder Needs Store\n");//asking for Number of remainder to required
    scanf("%d", &rem);
    printf("Enter the remainders\n");
    for (int i = 0; i < rem; i++)
    {
        scanf("%d", &re[i]);//accepting all remainders
    }
    ValueNode root = CreateInitial(rem, re);
    while (1)
    {
        printf("Enter the choice\n");
        printf("1=>Insert\t2=>Search\t3=>Delete\t4=>Display\t5->Exit\n");
        scanf("%d", &choice);
        if (choice > 0 && choice < 4) //taking input for insert or search or delete
        {
            printf("Enter the Number\n");
            scanf("%d", &num);
        }
        switch (choice)
        {
        case 1:
            Insert(num, root); //insert function calling
            break;
        case 2:
            Search(num, root);//search function calling
            break;
        case 3:
            Delete(num, root);//Delete function calling
            break;
        case 4:
            Display(root);//Display function calling
            break;
        case 5:
            printf("Exited\n");
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}