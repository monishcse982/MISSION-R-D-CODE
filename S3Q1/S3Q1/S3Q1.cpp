#include<stdio.h>
#include<conio.h>
#include<stdlib.h>   //This is the library that contains the malloc, calloc and realloc functions.

struct NODE
{
	int data;
	NODE *next;
};

NODE* insert_at_middle(NODE *head, int position, int data)
{
    if(position == 0)
    {
        printf("INVALID POSITION INPUT.");
        return head;
    }
    if(position == 1)
    {
        NODE *new_node = (NODE*)malloc(sizeof(NODE));
        new_node->data = data;
        new_node->next = head;
        return new_node;
    }
    if(head == NULL)                                  //Just checking if the list exists or not, if yes a new node is created with the data and that node is returned.
    {
        NODE *new_node = (NODE*)malloc(sizeof(NODE));
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
    }
    NODE *temp = head;
    while(position>1 && temp->next!=NULL)
    {
        temp = temp->next;
        position = position - 1;
    }
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = temp->next;
    temp->next = new_node;
    return head;
}

NODE* insert_at_end(NODE *head, int data)
{
    if(head == NULL)                                  //Just checking if the list exists or not, if yes a new node is created with the data and that node is returned.
    {
        NODE *new_node = (NODE*)malloc(sizeof(NODE));
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
    }
    NODE *temp = head;
    while(temp->next !=NULL)
    {
        temp = temp->next;
    }
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = data;
    temp->next = new_node;
    return head;
}


NODE* insert_node_at_the_beginning(NODE *head, int data)
{
    if(head == NULL)                                  //Just checking if the list exists or not, if yes a new node is created with the data and that node is returned.
    {
        NODE *new_node = (NODE*)malloc(sizeof(NODE));
        new_node->data = data;
        new_node->next = NULL;
        return new_node;
    }
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = head;
    return new_node;
}

NODE* delete_node_from_linked_list(NODE* head, int delete_data)                         //The return type is NODE because i might have to delete the first node itself and the pointer the calling function will have no data(this is called dangling pointer error) so i am sending the reference to the modified node.
{
    NODE *temp = head;
    if(temp->data == delete_data)
    {
        head = head->next;
        free(temp);
        return head;
    }
    while(temp->next->data == delete_data)
    {
        NODE *delete_node = temp->next;
        temp->next = delete_node->next;
        free(delete_node);
        return head;
    }
    return head;
}

void display_linked_list(NODE* head)
{
    NODE *temp = head;                                  //Temp variable because i am passing the head pointer using call by reference so if i move the same pointer then i will not be able to get back to the first node in the calling function.
    while(temp!=NULL)
    {
        prinft("%d   ",temp->data);
        temp = temp->next;
    }
}

NODE* create_linked_list()                              //Function creates a linked list with the user input array and returns a pointer to the head.
{
    int size_of_linked_list, iter_loop;                 //TIP: Never name your loop iteration variables i, j and all they should make sense so i used iter_loop.
    printf("ENTER SIZE OF THE LINKED LIST: ");
    scanf("%d",&size_of_linked_list);
    printf("\nENTER ELEMENTS IN THE LINKED LIST: \n");
    int *input_array = (int*)malloc(size_of_linked_list*sizeof(int));
    for(iter_loop=0;iter_loop<size_of_linked_list;iter_loop++)
    {
        scanf("%d",&input_array[iter_loop]);
    }

    iter_loop=0;
    NODE *head = (NODE*)malloc(sizeof(NODE));               //The head node.
    head->data = input_array[iter_loop];
    NODE* temp = head;
    head->next = NULL;
    iter_loop++;
    while(iter_loop<size_of_linked_list)                    //Loop to create the linked list.
    {
        NODE* new_node = (NODE*)malloc(sizeof(NODE));       //New node.
        new_node->data = input_array[iter_loop];            //Temp keeps track of he previous node every time so that the link can be established.
        temp->next = new_node;                              //Now temp's next pointer points to the new node.
        temp = new_node;                                    //Moving the temp pointer so that i can repeat the process
        temp->next = NULL;
        iter_loop++;
    }
    return head;
}

linked_list_operations()         //All the operations are performed here.
{


}

int main()
{
    linked_list_operations();
    getchar();
    return 0;
}
