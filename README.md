# C-Linked-Lists
Implementation  of  Linked  Lists  and  moving  Nodes  within  them.   
A linked list is a data structure. A data structure is nothing but how we organize and store the data in memory.
A linked list consists of various nodes, and each node contains two things: One is the data, and the other is the pointer, which will point to the next node. A linked list basically can have n nodes, and each node is connected to its next node with the help of a pointer. There are two types of linked lists: singly linked lists (SLL) and doubly linked lists (DLL).
In a SLL, we have a single pointer that’ll point to the next node and, therefore, it is called a singly linked list. In a DLL, we have two pointers: One pointer will point to the next node, and another will point to the previous node. That’s why we call it a doubly linked list.
In C programming, we use structures to create a linked list. The structure is a data type inside which we can define variables with different data types (e.g., int, char, pointer, etc.).
For creating a linked list, we’ll define the structure of our linked list (using the struct data type), which will represent what a single node in a linked list will look like. And then we’ll actually create a linked list by assigning memory to use using the malloc() function.
Structure of a linked list:   

struct node
{
    int data;
    struct node *p;
};

<img src="Linked-Lists/A single node in a linked list.png"  />

The above code represents the structure for our linked list which contains two things. 
First is a variable, data, which will hold the integer value inside it. 
And the second is struct node *p, which is a pointer that’ll point to the next node in a linked list. Here, struct represents the structure data type, and node is the name of that structure. You can give whatever name you want to the structure.
Now, you may be having a question: Why does the pointer have the same data type as the structure? The reason behind this is the nodes in a linked list are self-referential, which simply means the pointer in a node will point to another node of the same type (in this case, the struct node).
Note that after writing the above code, the linked list won’t be created — nor will any memory be assigned to it. It’s just a template that’ll define the structure of our linked list (how our linked list will look like).
Now, let’s write a code to create a linked list by assigning it some memory using the malloc() function.
       
       struct node *new = (struct node *) malloc(sizeof(struct node));

The above line of code will create a node in memory followed by a pointer called new, which will be pointing to the newly created node.
Previously, while creating a template for our node, we have given its name as a struct node. Thus, to allocate the memory, first we have to find out the size of that data type and then pass it to the malloc function to allocate memory for it.
After that, we can create a new pointer called *new and assign the output of the malloc function to that pointer by using typecasting. The malloc function by default returns void, but our pointer new is of the type struct node; therefore, we have to typecast it.
This is how it’ll look like.

A single node in a linked list
Operations Performed on an SLL
1. Insert an element in the linked list
Before inserting a node (element) into a linked list, you first have to create a node by using malloc.
Also, before inserting a node (element), you first have to check whether the head is pointing to the NULL or not — otherwise, it will give a segmentation fault.

Consider the following example:

Example of a linked list
Now, there are three ways in which we can insert this node in the above linked list
a. Insert node at the beginning
For inserting a node that we’ve created that’s being pointed by a pointer called new at the beginning of the linked list, we have to write the following code.

What this will do is: It’ll first store the starting address of the node that’s being pointed by the pointer head into the node that’s being pointed by pointer new. And then it’ll assign the address of the new pointer to the head pointer.

Insert node at the beginning
If you directly assign the address of new pointer to the head pointer to insert the node at the beginning before storing the address of the head pointer to the new pointer, then the entire linked list will be lost because, in this case, there’s no pointer that’ll be pointing to that memory location where the starting node of our linked list is present.
This might be somewhat confusing at first to understand, so I suggest you read it a number of times and try to understand it visually.
b. Insert node in the middle
Now to insert the node in the middle, we first have to think about where we’ll be inserting the new node.
Let say we want to insert the newly created node after the second node in the above linked list. For that, we have to reach the second node and then store whatever the second node is pointing too into the new->link. And then, we’ll insert the node at the location.




Insert node in the middle

c. Insert node at the end
For inserting a node at the end, we first have to find the end of the linked list. The ending node or the last node in a linked list will always have a NULL (also represented as \0) in this next part. From the above linked list, we can say the node that has a value of 5 is the last node because its next is NULL.
To reach the end, we first have to check whether t->next is null of not. If null, then we can insert the node at the position. Otherwise, keep moving forward until we reach t-> next is null.


Insert node at the end

2. Traversing a linked list
Traversing means visiting every node in a linked list.
For traversing, instead of using the actual pointer, which is currently pointing to the linked list, we have to create another pointer (say, t). By using that, we can traverse the list. Because if we move the current pointer, then there’s a chance we may lose some of the nodes in a linked list.
Let’s understand this with an example. Say we have a linked list, as shown below. So let’s traverse it.

Example of a linked list
Code for traversing the above linked list:

Output:

Here, first, we have a template for our node which defines what we have in our linked list. Secondly, we have the main function inside, for which we’ve created a new pointer t of type struct node (a pointer that we’ll use to traverse the list) and a while loop which will print the data inside the list and then increment the pointer.
In this, we are now touching the head pointer. If we do this, then we may lose some of the nodes inside our linked list as we have no pointer at the starting position of the list.
After creating another pointer — say, t — you have a choice. You can either move t or head. it doesn’t matter which because now you have two pointers at the starting position of the linked list.
3. Delete an element from the linked list
Before deleting a node (element), you first have to check whether the head is pointing to the NULL or not. Otherwise, it’ll give a segmentation fault.
Whenever you’re deleting an element from the linked list that you’ve created using the malloc() function, you also have to free it up by using a free() function. It’s not compulsory to free the space after deleting an element, but it’s a good practice to do so.
Also, create a temporary pointer — say, t — to hold the node that you want to delete, and then do the other operations. Otherwise, the node that you want to delete will get lost.
Conditions to check:

There are three ways to delete a node in the same way as insertion.
a. Delete the node at the beginning
To delete the node at the beginning, create a new pointer t, and make it point to the head. Now, we have to move the position of the head pointer one step ahead using head = head->next. Then free up the t to delete the first element in a linked list.


Delete the node at the beginning

b. Delete the node in the middle
Here, we have to identify which node we want to delete. After that, create a new pointer, and make it point to the position where the head pointer is pointing.
Let say we want to delete a node whose data part has the value 3. Then, check if t->next->data is 3 or not. If the data part, has a value of 3, then create another pointer — say, p — to hold the next part of the node whose value is 3. After that, free the location that’s currently pointed by the t pointer, and then assign the address of pointer p to t->next.



Delete the node in the middle

c. Delete the node at the end
When we’re deleting a node at the end, then we have to stand two steps back and check whether the second element is null or not.

The figure below explains the above code:


Delete node at the end
Searching for an element in a linked list takes a longer time O(n) because in the worst case, we have to traverse n elements. And in the best case, we can find the element in the first attempt, so time complexity will be O(1).
When searching for an element in an array, it takes O(1) times (considering the array is sorted); otherwise, it’ll take O(n) times only.
For more such blogs visit LionGuest Studios.
Thanks for reading.
