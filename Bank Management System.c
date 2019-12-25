#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[100];
    int account_no;
    char account_type[20];
    int balance;
}Account_info;

int add_account();
int edit_existing();
int delete_account();
int total_balance();
int max_balance();
int min_balance();
int view_all_accounts();
int search_account();


int main()//Main Function
{
    Account_info a[100];

    int i,choice,j,b;
    do{
    printf("Welcome To Bank Account Management System!\n\n");
    printf("MENU\n\n");
    printf("1.Add New Account\n");
    printf("2.Display all the Accounts\n");
    printf("3.Edit Existing Account\n");
    printf("4.Delete an Account\n");
    printf("5.Search an Account\n");
    printf("6.Find total balance of all account\n");
    printf("7.Display Maximum Balance Holder\n");
    printf("8.Display Minimum Balance Holder\n");
    printf("9.Exit\n\n");
    printf("Enter choice=");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1: printf("\n Add New account");
            add_account();
            break;

    case 2: printf("\n Display all the accounts\n");
            view_all_accounts();
            break;

    case 3: printf("\n Edit Existing Account\n");
            edit_existing();
            break;

    case 4: printf("\n Delete an Account\n");
            delete_account();
            break;

    case 5: printf("\n Search an account\n");
            search_account();
            break;

    case 6: printf("\n Total Balance of all Account\n");
            total_balance(a);
            break;

    case 7: printf("\n Maximum Balance Holder\n");
            j=max_balance(a,b);
            break;

    case 8: printf("\n Minimum Balance Holder\n");
            j=min_balance(a,b);
            break;


    case 9: printf("\nThank You,Please Come Again\n\n");
             break;
    default: printf("Wrong Input\n");
    }
   }while(choice!=9);
}


int add_account(Account_info a)
{
    FILE *fp;
    printf("\nAccount Holders Name : ");
    fflush(stdin);
    gets(a.name);
    printf("\nAccount No : ");
    scanf("%d",&a.account_no);
    printf("\nAccount Type : ");
    fflush(stdin);
    gets(a.account_type);
    printf("\nBalance : ");
    scanf("%d",&a.balance);
    fp=fopen("Account_Details.txt","a");

    fprintf(fp,"%s\t%d\t%s\t%d\n",a.name,a.account_no,a.account_type,a.balance);

    printf("\nAccount Added Successfully!!!");
    fclose(fp);
}


int view_all_accounts(Account_info a)
{
    FILE*fp;
    fp=fopen("Account_Details.txt","r");

    while(fscanf(fp,"%[a-z A-Z ' ']%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
      printf(" Name : %-16s\n Account No : %-8d\n Account Type : %-8s\n Balance : %-8d\n",a.name,a.account_no,a.account_type,a.balance);
      printf("\n");
    }
    fclose(fp);
}


int edit_existing(Account_info a)
{
    FILE*fp;
    FILE*fp1;
    fp=fopen("Account_Details.txt","r");
    fp1=fopen("temp.txt","w");

    char name1[100],new_name[100],new_account_type[100];
    int new_account_no , new_balance ,flag=0,acc_no;

    printf("\nEnter Account number : ");
    scanf("%d",&acc_no);
    fflush(stdin);

    printf("\nEditing Account Information\n");
    while(fscanf(fp,"%[^\t]%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
       if(acc_no==a.account_no)
       {
        flag=1;
        printf("\nNew account name : ");
        gets(new_name);
        printf("\nNew account no : ");
        fflush(stdin);
        scanf("%d",&new_account_no);
        printf("\nNew account type : ");
        scanf("%s",new_account_type);
        fflush(stdin);
        printf("\nAnd balance : ");
        scanf("%d",&new_balance);
        fprintf(fp1,"%s\t%d\t%s\t%d\n",new_name,new_account_no,new_account_type,new_balance);
        printf("\nAccount Edited Successfully!!");

       }
       else
       {
        fprintf(fp1,"%s\t%d\t%s\t%d\n",a.name,a.account_no,a.account_type,a.balance);
       }
    }
    if(flag==0)
    {
        printf("\nAccount not found. Try again!!\n\n");
    }
    fclose(fp);
    fclose(fp1);
    fp=fopen("Account_Details.txt","w");
    fclose(fp);
    fp=fopen("Account_Details.txt","a");
    fp1=fopen("temp.txt","r");
    while(fscanf(fp1,"%[^\t]%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
        fprintf(fp,"%s\t%d\t%s\t%d\n",a.name,a.account_no,a.account_type,a.balance);
    }
    fclose(fp);
    fclose(fp1);
    fp1=fopen("temp.txt","w");
    fclose(fp1);
}


int delete_account(Account_info a)
{
    FILE*fp;
    FILE*fp1;
    fp=fopen("Account_Details.txt","r");
    fp1=fopen("temp.txt","w");

    char name1[100];
    int new_balance,flag=0,acc_no;

    printf("Enter Account number : ");
    scanf("%d",&acc_no);
    printf("\nEnter Account name : ");
    fflush(stdin);
    gets(name1);

    while(fscanf(fp,"%[^\t]%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
       if(acc_no==a.account_no && strcmp(a.name,name1)==0)
       {
        flag=1;
        printf("\nAccount Deleted Successfully\n");

        continue;

        }
       else
       {
        fprintf(fp1,"%s\t%d\t%s\t%d\n",a.name,a.account_no,a.account_type,a.balance);
       }
    }

    if(flag==0)
    {
        printf("\nAccount Not Found. Try Again!!\n\n");
    }
    fclose(fp);
    fclose(fp1);
    fp=fopen("Account_Details.txt","w");
    fclose(fp);
    fp=fopen("Account_Details.txt","a");
    fp1=fopen("temp.txt","r");
    while(fscanf(fp1,"%[^\t]%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
        fprintf(fp,"%s\t%d\t%s\t%d\n",a.name,a.account_no,a.account_type,a.balance);
    }
    fclose(fp);
    fclose(fp1);
    fp1=fopen("temp.txt","w");
    fclose(fp1);
}

int search_account(Account_info a)
{
   int Number,flag=0;
   char name1[100];
   FILE*fp;
   fp=fopen("Account_Details.txt","r");
   printf("\n Enter Account Number : ");
   scanf("%d",&Number);

   while(fscanf(fp,"%[^\t]%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
        if(Number==a.account_no)
        {
            flag=1;
            break;
        }
    }
        if(flag==1)
            printf(" Name : %-16s\n Account No : %-8d\n Account Type : %-8s\n Balance : %-8d\n",a.name,a.account_no,a.account_type,a.balance);
          else
            printf("\nAccount Not Found\n\n");
    fclose(fp);
}


int total_balance(Account_info a)
{
    int sum=0;
    FILE*fp;
    fp=fopen("Account_Details.txt","r");
    while(fscanf(fp,"%[a-z A-Z ' ']%d%s%d\n",a.name,&a.account_no,a.account_type,&a.balance)!=EOF)
    {
        sum=sum+a.balance;
    }

    printf(" Total Balance : %d Taka\n\n",sum);
    fclose(fp);
    return sum;
}


int max_balance(Account_info a[],int j)
{
    int i=0,max=-1;
    FILE*fp;
    fp=fopen("Account_Details.txt","r");//Write

    while(fscanf(fp,"%[a-z A-Z ' ']%d%s%d\n",a[i].name,&a[i].account_no,a[i].account_type,&a[i].balance)!=EOF)
    {
     if(max<a[i].balance)
        {
            max=a[i].balance;
            j=i;
            i++;
        }
    }
    fclose(fp);

    printf(" Name : %-16s\n Account No : %-8d\n Account Type : %-8s\n Balance : %-8d\n",a[j].name,a[j].account_no,a[j].account_type,a[j].balance);
    printf("\n");

    return j;
}


int min_balance(Account_info a[],int j)
{
    int i=0,min=999999999;
    FILE*fp;
    fp=fopen("Account_Details.txt","r");

    while(fscanf(fp,"%[a-z A-Z ' ']%d%s%d\n",a[i].name,&a[i].account_no,a[i].account_type,&a[i].balance)!=EOF)
    {

     if(min>a[i].balance)
        {
            min=a[i].balance;
            j=i;
            i++;
        }
    }

    fclose(fp);

    printf(" Name : %-16s\n Account No : %-8d\n Account Type : %-8s\n Balance : %-8d\n",a[j].name,a[j].account_no,a[j].account_type,a[j].balance);
    printf("\n");

    return j;
}
