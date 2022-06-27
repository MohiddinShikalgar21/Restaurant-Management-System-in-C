#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char food_item[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head_cus = NULL, *new_node, *tail_cus = NULL;
struct node *head_admin = NULL, *tail_admin = NULL;
struct node *head_sales;


void admin_menu()
{
    printf("\n\n\t\t\t    ------------------------------------------------\n");
    printf("\t\t\t\t\t     ADMIN SECTION\n");
    printf("\t\t\t    ------------------------------------------------\n");
    printf("\n\t\t\t\t 1. View total sales\n");
    printf("\t\t\t\t 2. Add new items in the order menu\n");
    printf("\t\t\t\t 3. Delete items from the order menu\n");
    printf("\t\t\t\t 4. Display order menu\n");
    printf("\t\t\t\t 5. Back To Main Menu \n\n");
    printf("\t\t\t\t    Enter Your Choice ---> ");
}


void customer_menu()
{
    printf("\n\n\t\t\t    ----------------------------------------------\n");
    printf("\t\t\t\t\t     CUSTOMER SECTION\n");
    printf("\t\t\t    ----------------------------------------------\n");
    printf("\n\t\t\t\t 1. Place your order\n");
    printf("\t\t\t\t 2. View your ordered items\n");
    printf("\t\t\t\t 3. Delete an item from order\n");
    printf("\t\t\t\t 4. Display final bill\n");
    printf("\t\t\t\t 5. Back To Main Menu \n\n");
    printf("\t\t\t\t    Enter Your Choice ---> ");
}


struct node* create_admin(struct node *head,int data, char food_item[25], float price)
{
    new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = data;
    new_node->price = price;
    new_node-> quantity = 0;
    strcpy(new_node->food_item,food_item);
    new_node->next = NULL;
    new_node->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        {
            head_admin = tail_admin = new_node;
        }

    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=new_node;
        new_node->prev = tail_admin;
        tail_admin = new_node;
    }

    return head_admin;
}


struct node* create_customer(struct node *head, int data, int quantity)
{
    new_node = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = head_admin;

    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        new_node->data = data;
        new_node->price = quantity*(temp1->price);
        new_node-> quantity = quantity;
        strcpy(new_node->food_item,temp1->food_item);
        new_node->next = NULL;
        new_node->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            {
                head_cus = tail_cus = new_node;
            }
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=new_node;
            new_node->prev = tail_cus;
            tail_cus = new_node;
        }
        printf("\n\n\t\t\t\t\t Item ordered successfully!!");
        printf("\n\n\t\t\t\t\t Press any key to return....");
        getch();
        system("cls");

    }
    else
    {
        printf("\n\t\t\t\t This item is not present in the menu!\n");
        printf("\n\n\t\t\t\t\t Press any key to return and try again....");
        getch();
        system("cls");
    }
    return head_cus;
}


void displayList(struct node *head)
{
    struct node *temp1 = head;

    if(temp1==NULL)
    {
        printf("\n\n\n\t\t\t\t List is empty!!\n\n");
    }
    else
    {

        printf("\n\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
            {
                printf("\t\t\t\t %d. %s--------%0.2f\n",temp1->data,temp1->food_item, temp1->price);
            }
            else
            {
                printf("\t\t\t\t %d. %s--------%d---%0.2f\n",temp1->data,temp1->food_item, temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
    }

}


struct node* total_sales(int data,int quantity)
{
    new_node = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = head_admin;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    new_node->data = data;
    new_node->price = quantity*(temp1->price);
    new_node-> quantity = quantity;
    strcpy(new_node->food_item,temp1->food_item);
    new_node->next = NULL;
    new_node->prev = NULL;

    struct node *temp = head_sales;

    if(temp==NULL)
        {
            head_sales = new_node;
        }
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += new_node-> quantity;
            temp->price += new_node->price;
        }
        else
        {
            temp->next=new_node;
        }
    }

    return head_sales;
}


void total_sales_func()
{
    struct node *temp = head_cus;
    while(temp!=NULL)
    {
        head_sales = total_sales(temp->data, temp->quantity);
        temp=temp->next;
    }
}


struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t List is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}


int delete_admin()
{
    int num;
    displayList(head_admin);
    printf("\n\n\n\t\t\t Enter serial no. of the food item to be deleted: ");
    scanf("%d",&num);

    struct node* temp = head_admin;

    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_admin = delete(num, head_admin, tail_admin);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}


int delete_customer()
{
    int num;
    displayList(head_cus);
    printf("\n\t\t\t Enter serial no. of the food item to be deleted: ");
    scanf("%d",&num);

    struct node* temp = head_cus;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_cus = delete(num, head_cus, tail_cus);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}


void display_bill()
{
    displayList(head_cus);
    struct node *temp = head_cus;
    float total_amt = 0;
    while (temp!=NULL)
    {
        total_amt +=temp->price;
        temp = temp->next;
    }

    printf("\n\t\t\t\t Total Payable Amount: %0.02f\n",total_amt);

}


struct node* delete_List(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}


void admin()
{
    while(1)
    {
        admin_menu();

        int opt;
        scanf("%d",&opt);
        system("cls");
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                printf("\n\n\n\t\t\t\t\t\t ### Total Sales ###\n");
                displayList(head_sales);
                printf("\n\t\t\t\t Press any key to return....");
                getch();
                system("cls");
                break;

            case 2:
                printf("\n\n\n\t\t\t\t\t\t ### Order menu ###\n");
                displayList(head_admin);
                printf("\n\n\n\t\t\t\t\t Enter unique item no. of new food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = head_admin;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t Food item with given item number already exists!!\n");
                        printf("\n\t\t\t\t Press any key to return to menu....");
                        getch();
                        system("cls");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\t\t\t\t\t Enter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t Enter price: ");
                scanf("%f",&price);

                head_admin = create_admin(head_admin, num, name, price);
                printf("\n\n\t\t\t\t\t New food item added to the list!!\n");
                printf("\n\t\t\t\t\t Press any key to return....");
                getch();
                system("cls");
                break;

            case 3:
                printf("\n\n\n\t\t\t\t\t\t ### Order menu ###\n");
                if(delete_admin())
                {
                    printf("\n\t\t\t\t Item deleted successfully!!");
                    printf("\n\n\t\t\t\t\t   ### Updated Order menu ###");
                    displayList(head_admin);
                    printf("\n\t\t\t\t Press any to return....");
                    getch();
                    system("cls");
                }
                else
                {
                    printf("\n\t\t\t\t Food item with given serial number does not exist!\n\n");
                }
                break;

            case 4:
                printf("\n\n\n\t\t\t\t\t\t ### Order menu ###\n");
                displayList(head_admin);
                printf("\n\t\t\t\t Press any to return....");
                getch();
                system("cls");
                break;

            default:
                admin_menu();
                printf("\n\n\t\t\t\t Wrong Input !! PLease choose valid option (1-5)\n");
                printf("\n\t\t\t\t\t Press any key to try again....");
                getch();
                system("cls");
                break;
        }
    }
}


void customer()
{
    int flag=0,j=1;
    char ch;

    while(1)
    {
        customer_menu();

        int opt;
        scanf("%d",&opt);
        system("cls");
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                printf("\n\n\n\t\t\t\t\t\t ### Order menu ###\n");
                displayList(head_admin);

                int num;
                int quantity;

                printf("\n\t\t\t\t Enter number corresponding to the item you want to order: ");
                scanf("%d",&num);

                printf("\t\t\t\t Enter quantity: ");
                scanf("%d",&quantity);

                head_cus = create_customer(head_cus, num, quantity);
                break;

            case 2:
                printf("\n\n\t\t\t\t\t ### List of ordered items ###");
                displayList(head_cus);
                printf("\n\t\t\t\t Press any key to return....");
                getch();
                system("cls");
                break;

            case 3:
                printf("\n\n\t\t\t\t\t ### List of ordered items ###");
                if(delete_customer())
                {
                    printf("\n\t\t\t\t Item deleted successfully!!");
                    printf("\n\n\t\t\t\t ### Updated List of ordered items ###");
                    displayList(head_cus);
                    printf("\n\t\t\t\t Press any to return....");
                    getch();
                    system("cls");
                }
                else
                    printf("\n\t\t\t\t Food item with given serial number doesn't exist!!\n");
                break;

            case 4:
                total_sales_func();
                printf("\n\n\n\t\t\t\t\t ### Final Bill ###\n");
                display_bill();
                head_cus = delete_List(head_cus);
                printf("\n\t\t\t\t Press any key to return to main menu...");
                getch();
                system("cls");
                flag=1;
                break;

            default:
                customer_menu();
                printf("\n\n\t\t\t\t Wrong Input !! PLease choose valid option (1-5)\n");
                printf("\n\t\t\t\t\t Press any key to try again....");
                getch();
                system("cls");
                break;
        }
        if(flag==1)
            break;
    }
}

void main_menu()
{
    printf("\n\n\n                      ********************************************************************\n");
    printf("                                      WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
    printf("                      ********************************************************************\n\n\n");
    printf("\t\t\t\t\t 1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t 2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t 3. Exit--> \n\n");
    printf("\t\t\t\t\t Enter Your Choice ---> ");
}

int main()
{
    head_admin = create_admin(head_admin,1,"Paneer Tikka Masala",160);
    head_admin = create_admin(head_admin,2,"Hot Chocolate (with Vanilla topping)",200);
    head_admin = create_admin(head_admin,3,"Grilled Veg Cheese Sandwich",150);
    head_admin = create_admin(head_admin,4,"Fried Schezwan Rice",180);
    head_admin = create_admin(head_admin,5,"Manchow Soup",80);

    while(1)
    {
        main_menu();

        int choice;
        scanf("%d",&choice);
        system("cls");
        if(choice==3)
        {
            printf("\n\n\n\n\t\t\t\t\t **********Thank you!!**********\n\n\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;

            default:

                main_menu();
                printf("\n\n\t\t\t\t Wrong Input !! PLease choose valid option\n");
                printf("\n\t\t\t\t\t Press any key to try again....");
                getch();
                system("cls");
                break;
        }
    }
}
