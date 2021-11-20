char expensecal[60];
char temp_name[60];
float value_temp;

struct balance
    {
        char name[20];
        float ba;
    };
    long int recsize;
    struct balance bal;

void gotoxy(short int col,short int row)//this function is to place the cursor at given "row" and "col"
{
    HANDLE hStdout= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={col,row};
    SetConsoleCursorPosition(hStdout,position);
}
float scan_float()
{
    float z;

    while(scanf("%f",&z)!=1)
    {
        fflush(stdin);
        printf("\n-> Enter valid number: ");
    }
    return z;
}

FILE *first;
struct details
{
    char name[20];
    float balance;
}g[100];
int people,i=0;
long int position;
float a,rem=0,amount;
char nam[20],expense[100],c,grpname[20];
char grp_grpname[60],message[150];

void display_activities(FILE *first)
{
    int i,people,j=0;
    char expense[60],paid[20],amount[20],person[20],borrowed[20];
    system("cls");
    printf("\n*********Activities*********\n\n");
    fseek(first,1002,SEEK_SET);
    while(1)
    {
    fflush(stdin);
    fgets(expense,25,first);
    j++;
    if(expense[0]=='~')
    {
        if(j==1)
        {
            Beep(1000,500);
            MessageBox(0, "NO ACTIVITIES PERFORMED!", "SPLITWISE", MB_ICONERROR);
        }
        break;
    }

    printf("-> Name of the Expense: %s",expense);

    fscanf(first,"%s",&amount);
    int siz=strlen(amount);
    amount[siz-4]='\0';
    printf("-> Amount spent: $%s\n",amount);
    fscanf(first,"%s",paid);
    printf("-> Person who paid: %s\n",paid);
    fscanf(first,"%d",&people);
    for(i=0;i<people;i++)
    {
        fscanf(first,"%s%s%s\n",person,borrowed,amount);
        int siz=strlen(amount);
        amount[siz-4]='\0';
        printf("-> %s %s $%s\n",person,borrowed,amount);
    }
    printf("\n-----------------------------------------------------------\n\n");
    }
    printf("(Press any key to close)\n");
    fclose(first);
    getch();
}

void Delete_member(FILE *first,int people,char passingname[])
{
        int m,k=0;
        system("cls");
        fseek(first,0,SEEK_SET);
        FILE *temp;
        strcat(passingname,".txt");
        temp=fopen("temp.txt","w+");
        char name[30],ch;
        printf("\n****Members Available to Delete****\n\n");

        for(m=0;m<people;m++)//when the nam becomes "`" we know end of names
        {

            printf("%d.%s\n",m+1,g[m].name);

        }
        do
        {
        printf("\n\nEnter the Name to Delete Member(with no spaces): ");
        scanf("%s",name);
        fseek(first,0,SEEK_SET);
        while(1)
        {
            fscanf(first,"%s\n",g[0].name);
            if((strcmp(name,g[0].name))==0)
                {
                    k=1;
                    break;
                }
            if((strcmp(g[0].name,"`"))==0)
                break;
        }
        if(k==0)
            {    Beep(1000,500);
                MessageBox(0,"Member not found (Please enter the name again)","SPLITWISE",MB_ICONWARNING);
            }
        }while(k!=1);
        fseek(first,0,SEEK_SET);
        strcat(g[people-1].name,"x");//doubt
        while(strcmp(g[people-1].name,"`")!=0)//when the nam becomes "`" we know end of names
        {
                fscanf(first,"%s",g[people].name);
                if(strcmp(g[people].name,name)!=0)
                    fprintf(temp,"%s\n",g[people].name);
                people++;
        }
        fseek(first,999,SEEK_SET);
        fseek(temp,999,SEEK_SET);
        while(1)
        {
            ch=fgetc(first);
            if(ch==EOF)
                break;
            else
                fputc(ch,temp);
        }
        fclose(first);
        fclose(temp);
        remove(passingname);
        rename("temp.txt",passingname);
        MessageBox(0,"/--Member Deleted Successfully--/","SPLITWISE",MB_OK);
}

void total(FILE *first)
{
                     int j=0;
                     system("cls");
                     fseek(first,1002,SEEK_SET);//we go to 1002 as we start to store the details of expenses from there
                     float total=0;
                        while(1)
                        {
                            char paid[20],person[20],borrowed[20];
                            int peo;
                            fflush(stdin);
                            fgets(expense,50,first);
                            j++;
                           if(expense[0]=='~')
                             {
                                  if(j==1)
                                  {
                                    Beep(1000,500);
                                     MessageBox(0, "NO ACTIVITIES PERFORMED!", "SPLITWISE", MB_ICONERROR);
                                   }
                                   break;
                              }
                            if(strcmp("~",expense)==0)
                               break;
                            fscanf(first,"%f",&amount);
                            total= total+amount;
                            fscanf(first,"%s",paid);
                            fscanf(first,"%d",&peo);
                            for(i=0;i<peo;i++)
                            {
                                fscanf(first,"%s",person);
                                fscanf(first,"%s",borrowed);
                                fscanf(first,"%f\n",&amount);
                            }
                         }
                    gotoxy(30,7);//print the amount at the middle of the screen
                    printf("Total Amount Spent: $%.2f",total);
                    gotoxy(32,9);
                    printf("(Press any Key to Close)\n");
                    fclose(first);
                    getch();
}

void add_expense(FILE *first,int people)
{
// AK
                        float balance_fetch;
// AK
                        char name1[20];
                        int h,negetive;
                        int k=0;
                        fseek(first,1001,SEEK_SET);
                        while(1)//for going to end of expenses
                        {
                            fscanf(first,"%s",expense);
                            if(strcmp("~",expense)==0)
                                   break;
                        }
                        system("cls");
                        fseek(first,-1,SEEK_CUR);
                        if(people==0)
                        {
                            MessageBox(0, "NO MEMBERS ARE ADDED", "SPLITWISE", MB_ICONWARNING);
                            return;
                        }
                        printf("\n*******Add Expense*******\n");
                        printf("\n-> Enter name of the Expense: ");
                        fflush(stdin);
                        fgets(expense,98,stdin);
                        fputs(expense,first);
                        printf("\n-> Enter the Amount: ");
                        //scanf("%f",&amount);
                        amount=scan_float();
                        fprintf(first,"%f\n",amount);
                        printf("-> Group members are: \n");
//anand new
                        i=1;
                        while(strcmp(g[i-1].name,"`")!=0)
                        {

                                if(strcmp(g[i-1].name,"`")==0) break;
                                printf("%d.%s\n",i,g[i-1].name);
                                i++;
                        }
                        struct balance
                        {
                            char name[20];
                            float ba;
                        };
                        long int recsize;
                        struct balance bal;
                        recsize=sizeof(bal);
//anand new
                        do
                        {
                        printf("\n-> Paid by: ");
                        scanf("%s",nam);
                        fseek(first,0,SEEK_SET);
                        while(1)
                        {
                            fscanf(first,"%s\n",name1);
                            if((strcmp(nam,name1))==0)
                                {
                                    k=1;
                                    break;
                                }
                            if((strcmp(name1,"`"))==0)
                                break;
                        }
                        if(k==0)
                            {   // Beep(1000,500);
                                MessageBox(0,"Member not found (Please enter the name again)","SPLITWISE",MB_ICONWARNING);
                            }
                        }while(k!=1);
                        fseek(first,-1,SEEK_END);
                        fprintf(first,"%s\n",nam);
                        fprintf(first,"%d\n",people);
                        printf("\n-> Options Available to Distribute Money");
                        printf("\n1.Equally\n2.Un-Equally\n3.By Percentage\n");
                        fflush(stdin);
                        printf("\n-> Choose an option: ");
                        int donee=0;
                        while(donee!=1)
                        {

                        fflush(stdin);
                        scanf("%d",&h);
                        switch(h)
                        {
                        case 1://Equally
                            donee=1;
                            for(int i=0;i<people;i++)
                            {
                                if(strcmp(g[i].name,nam)==0)
                                {
                                    fflush(stdin);
                                    fprintf(first,"%s Lent %f\n",g[i].name,amount-amount/people);
 // AK

                                    FILE *f;

                                    f = fopen(expensecal, "rb+");
                                    rewind(f);
                                    float j;

                                    while(fread(&bal,recsize,1,f)==1)
                                    {
                                        if(strcmp(bal.name,g[i].name)==0)
                                        {
                                            bal.ba=bal.ba+amount-amount/people;
                                            fseek(f,-recsize,SEEK_CUR);
                                            fwrite(&bal,recsize,1,f);
                                            break;
                                        }
                                    }
                                    fclose(f);

                                }

                                else
                                {
                                    fflush(stdin);
                                    fprintf(first,"%s Borrowed %f\n",g[i].name,amount/people);
// AK
                                    FILE *f;
                                    f = fopen(expensecal, "rb+");
                                    rewind(f);
                                    float j;
                                    while(fread(&bal,recsize,1,f)==1)
                                    {
                                        if(strcmp(bal.name,g[i].name)==0)
                                        {
                                            bal.ba=bal.ba-amount/people;
                                            fseek(f,-recsize,SEEK_CUR);
                                            fwrite(&bal,recsize,1,f);
                                            break;
                                        }
                                    }
                                    fclose(f);


                                }

                            }
                            break;
                        case 2://Unequally
                            {
                                donee=1;
                                float a[people];
                                int done=0,tally=0;
                                char don;
                                while(done==0||tally==0)
                                {
                                    tally=0;
                                    rem=0;
                                    system("cls");
                                    gotoxy(30,0);
                                    printf("******Specify Amount Owned by Each Person******");
                                    for(i=0;i<people;i++)
                                    {
                                        gotoxy(0,i+1);
                                        printf("%s:",g[i].name);
                                    }
                                    for(i=0;i<people;i++)
                                    {
                                        gotoxy(20,people+2);

                                        for(int ua=0;ua<50;ua++)
                                        {
                                            printf(" ");
                                        }
                                        gotoxy(20,people+2);
                                        printf("$%.2f Remaining of $%.2f",amount-rem,amount);
                                        gotoxy(20,i+1);
                                        //scanf("%f",&a[i]);
                                        a[i]=scan_float();
                                        if(a[i]<0)
                                        {
                                            negetive=1;
                                            gotoxy(20,people+4);
                                            MessageBox(0,"Please enter  a positive amount","SPLITWISE",MB_OK);
                                            break;
                                        }
                                        else if(a[i]>amount-rem)
                                        {
                                            negetive=1;
                                            MessageBox(0,"amount is exceeding expense amount","SPLITWISE",MB_OK);
                                            break;
                                        }
                                        else
                                            negetive=0;
                                        rem+=a[i];
                                    }
                                    if(negetive==1)
                                    {
                                        continue;
                                    }
                                    gotoxy(20,people+2);
                                    printf("$%.2f Remaining of $%.2f",amount-rem,amount);
                                    if(rem!=amount)
                                    {
                                        gotoxy(20,people+4);
                                        printf("/*---Total Amount is not Tallying---*/");
                                        gotoxy(25,people+6);
                                        printf("(Press any Key)");
                                        getch();
                                    }
                                    else
                                    {
                                        tally=1;
                                        done=MessageBox(0,"Would You Like To Re-enter Amount?","SPLITWISE",MB_YESNO);
                                        if(done==6)
                                            done=0;
                                        fflush(stdin);
                                    }
                                }
                                for(i=0;i<people;i++)
                                {
                                    if(strcmp(g[i].name,nam)==0)
                                        {
                                            fprintf(first,"%s Lent %f\n",g[i].name,amount-a[i]);
                                             FILE *f;
                                            f = fopen(expensecal, "rb+");
                                            rewind(f);
                                            float j;
                                            while(fread(&bal,recsize,1,f)==1)
                                            {
                                                if(strcmp(bal.name,g[i].name)==0)
                                                {
                                                    bal.ba=bal.ba+amount-a[i];
                                                    fseek(f,-recsize,SEEK_CUR);
                                                    fwrite(&bal,recsize,1,f);
                                                    break;
                                                }
                                    }
                                    fclose(f);
                                        }

                                    else
                                       {
                                           fprintf(first,"%s Borrowed %f\n",g[i].name,a[i]);
                                            FILE *f;
                                            f = fopen(expensecal, "rb+");
                                            rewind(f);
                                            float j;
                                            while(fread(&bal,recsize,1,f)==1)
                                            {
                                                if(strcmp(bal.name,g[i].name)==0)
                                                {
                                                    bal.ba=bal.ba-a[i];
                                                    fseek(f,-recsize,SEEK_CUR);
                                                    fwrite(&bal,recsize,1,f);
                                                    break;
                                                }
                                            }
                                            fclose(f);
                                        }

                                }
                            break;

                            //end of add unequally
                            }

                        case 3://add by percentage
                            {
                                donee=1;
                                float a[people];
                                int done=0,tally=0;
                                char don;
                                while(done==0||tally==0)
                                {

                                    tally=0;
                                    rem=0;

                                    system("cls");
                                    gotoxy(24,0);
                                    printf("******Specify the Percentage of Each Person******\n");

                                    for(i=0;i<people;i++)
                                    {
                                        gotoxy(0,i+1);
                                        printf("%s:",g[i].name);
                                    }


                                    for(i=0;i<people;i++)
                                    {
                                        gotoxy(20,people+2);

                                        for(int ua=0;ua<30;ua++)
                                        {
                                            printf(" ");
                                        }
                                        gotoxy(20,people+2);
                                        printf("%.2f remaining of 100",100-rem);


                                        gotoxy(20,i+1);
                                        //scanf("%f",&a[i]);
                                        a[i]=scan_float();
                                        if(a[i]<0)
                                        {
                                            negetive=1;
                                            MessageBox(0,"Please enter  valid number (0-100)","SPLITWISE",MB_OK);
                                            break;
                                        }
                                        else if(a[i]>100-rem)
                                        {
                                            negetive=1;
                                            MessageBox(0,"amount is exceeding expense amount","SPLITWISE",MB_OK);
                                            break;
                                        }
                                        else
                                        {
                                            negetive=0;
                                        }
                                        rem+=a[i];


                                    }
                                    if(negetive==1)
                                    {
                                        continue;
                                    }

                                    gotoxy(20,people+2);
                                    printf("%.2f remaining of 100\n",100-rem);
                                    if(rem!=100)
                                    {
                                        gotoxy(20,people+4);

                                        printf("Total amount is not tallying");
                                        gotoxy(25,people+6);
                                        printf("press any key");
                                        getch();
                                    }
                                    else
                                    {
                                        tally=1;
                                        done=MessageBox(0,"Would You Like To Re-enter Amount?","SPLITWISE",MB_YESNO);
                                        if(done==6)
                                            done=0;
                                        fflush(stdin);
                                    }
                                }
                                for(i=0;i<people;i++)
                                {
                                    if(strcmp(g[i].name,nam)==0)

                                        {
                                            fprintf(first,"%s Lent %f\n",g[i].name,amount-amount*a[i]/100);
                                            FILE *f;
                                            f = fopen(expensecal, "rb+");
                                            rewind(f);
                                            float j;
                                            while(fread(&bal,recsize,1,f)==1)
                                            {
                                                if(strcmp(bal.name,g[i].name)==0)
                                                {
                                                    bal.ba=bal.ba+amount-amount*a[i]/100;
                                                    fseek(f,-recsize,SEEK_CUR);
                                                    fwrite(&bal,recsize,1,f);
                                                    break;
                                                }
                                    }
                                    fclose(f);
                                        }
                                        else
                                        {
                                            fprintf(first,"%s Borrowed %f\n",g[i].name,a[i]*amount/100);
                                            FILE *f;
                                            f = fopen(expensecal, "rb+");
                                            rewind(f);
                                            float j;
                                            while(fread(&bal,recsize,1,f)==1)
                                            {
                                                if(strcmp(bal.name,g[i].name)==0)
                                                {
                                                    bal.ba=bal.ba-a[i]*amount/100;
                                                    fseek(f,-recsize,SEEK_CUR);
                                                    fwrite(&bal,recsize,1,f);
                                                    break;
                                                }
                                            }
                                            fclose(f);
                                        }
                                }
                        break;


//end of add by percentage
                        }
                        default:
                            {
                               // Beep(1000,500);
                                MessageBox(0,"INVALID CHOICE( Please choose the option again)","SPLITWISE",MB_ICONERROR);
/*end of switch*/               printf("\nChoose an option: ");
                            }
                        }
//end of while loop of choice
                     }
                     fprintf(first,"~");//we enter "~" before closing the file
                     fclose(first);
                     MessageBeep(0);
                     MessageBox(0,"Added the Expense","SPLITWISE",MB_ICONASTERISK);
}

void add_member(FILE *first,int people)
{
                        system("cls");
                        printf("***Add member***\n");
                        fseek(first,-1,SEEK_CUR);
                        int k,y=0;
                        do
                        {
                            printf("\nEnter Name of the Person(with no spaces): ");
                            scanf("%s",nam);
                            k=0;
                            for(int i=0;i<people;i++)
                            {
                                if(strcmp(g[i].name,nam)==0)
                                {
                                   k=1;
                                   Beep(1000,500);
                                   MessageBox(0,"Member already exists (Please enter a different name)","SPLITWISE",MB_ICONWARNING);
                                }
                            }

                        }while(k==1);

// AK
                        FILE *f;
                        f = fopen(expensecal, "r+");
                        struct balance
                        {
                            char name[20];
                            float ba;
                        };
                        long int recsize;
                        struct balance bal;
                        recsize=sizeof(bal);
                        while(fread(&bal,recsize,1,f)==1)
                        {
                            if(strcmp(nam,bal.name)==0)
                            {
                               y=1;
                               break;
                            }
                        }
                        if(y==0)
                        {
                            strcpy(bal.name,nam);
                            bal.ba=0;
                            fwrite(&bal,recsize,1,f);
                        }

                        //fprintf(f, "%s\n", nam);
                        //fprintf(f,"%f\n",100000.0);
                        fclose(f);
// AK
                        fprintf(first,"%s\n",nam);
                        fprintf(first,"`\n");
                        printf("\n/*--Member Added Successfully--*/\n");
                        printf("\n(Press any Key)");
                        getch();
                        fclose(first);
}

void display_members(FILE *first)
{
                        int m;
                        system("cls");
                        printf("\n***The Group Members are***\n\n");
                        fseek(first,0,SEEK_SET);
                        strcat(nam,"x");
                        for(m=1;1;m++)
                        {
                            fscanf(first,"%s",nam);
                            if(strcmp(nam,"`")!=0)
                                printf("%d.%s\n",m,nam);
                            else
                                break;
                        }
                        fclose(first);
                        printf("\n(Press any Key to go Back)\n");
                        getch();
}
int check_name(char *name)
{
    int i=0;
    for(i=0;i<people;i++)
    {
        if(strcmp(g[i].name,name)==0)
        {
            return 1;
        }
    }
    return 0;
}


// AK
void balances(char grpname[], int people)
{
     system("cls");
     int i;
    /*FILE *f;
    f = fopen(grpname, "r");
    for (int k=1;k<=people;k++)
    {
        fscanf(f, "%s\n%f\n", temp_name, value_temp);
        printf("Name: %s\t\tBalance: %f\n", temp_name, value_temp);
    }
    fclose(f);*/
    FILE *f;

    struct balance
    {
        char name[20];
        float ba;
    };
    long int recsize;
    struct balance bal;
    recsize=sizeof(bal);
    char group_expense[50];
    strcpy(group_expense, grpname);
    strcat(group_expense, "_expense.txt");
    f=fopen(group_expense,"rb+");
    if(f==NULL)
    {
        exit (3);
    }
    rewind(f);
    i=0;
    printf("\n***Balances of Group members are***\n");
    while(fread(&bal,recsize,1,f)==1)
    {
        i++;
        printf("\n%d.%s: %.2f",i,bal.name,bal.ba);
    }
    printf("\n\n(Press any key to go back)");
    fclose(f);
    getch();
}
//AK

//anand new
void add_member_first_time(FILE *first)
{
    int ok=1;
            while(ok)
            {
                        system("cls");
                        printf("***Adding the Members First Time***\n\n");
                        fseek(first,-1,SEEK_CUR);
                        printf("-> Enter Name of the Person(with no spaces): ");
                        scanf("%s",nam);
// Aditya  // To create a new file to calculate the total individual transaction amount
                        FILE *f;
                        f = fopen(expensecal, "ab");
                        struct balance
                        {
                            char name[20];
                            float ba;
                        };
                        long int recsize;
                        struct balance bal;
                        strcpy(bal.name,nam);
                        bal.ba=0;
                        recsize=sizeof(bal);
                        fwrite(&bal,recsize,1,f);
                        //fprintf(f, "%s\n", nam);
                        //fprintf(f,"%f\n",100000.0);
                        fclose(f);
// Aditya
                        fprintf(first,"%s\n",nam);
                        fprintf(first,"`\n");
                        printf("\n/--%s Added to the Members List--/\n", nam);
                        getch();
                        ok=MessageBox(0,"Would you like to add another member?","SPLITWISE",MB_YESNO);
                        fflush(stdin);
                        if(ok!=6)
                        {
                            ok=0;
                        }
                        else
                        {
                            fseek(first,-2,SEEK_CUR);
                        }
            }
                        fclose(first);


}


void settle_up(char passingname[])
{
    char take_name[50],name_up[50];
    strcpy(name_up, passingname);
    int j,z;
    int i=0;
    FILE *f;
    system("cls");
    fflush(stdin);
    strcat(name_up, "_expense.txt");
    f = fopen(name_up, "rb");
    struct balance up[1000];
    printf("***SPLITWISE***\n");
    printf("\n=>Members of the group: \n");
    while((fread(&up[i], sizeof(up[i]), 1, f)==1))
        {
            printf("%d. %s\n", i+1,up[i].name);
            i++;
        }
    fclose(f);
    fflush(stdin);
    i--;
    int number_of_people = i;
    char input_name[50];
    float val;
    printf("\n-> Enter name(with no spaces): ");
    scanf("%s", input_name);

    int h=0;
    while (h<number_of_people+1)
    {
        if (strcmp(input_name, up[h].name)==0)
        {
            //printf("%s\n", up[i].name);
            break;
        }
        h++;
        if (h > number_of_people)
        {
            MessageBox(0, "Name you entered does not match with the available option names!", "Splitwise", MB_ICONERROR);
            printf("\n-> Re-enter name(with no spaces): ");
            scanf("%s", input_name);
            h=0;
        }

    }

    for (j=0;j<number_of_people; j++)
    {
        if (strcmp(input_name, up[j].name) == 0)
            break;
    }
    printf("\n-> Your balance is %.2f\n", up[j].ba);
    if (up[j].ba > 0)
    {
        printf("-> You have to receive a total amount of $%.2f\n\n",up[j].ba);
        printf("(Press any key to continue)");
        getch();
    }
    if (up[j].ba == 0)
        printf("-> Your money has been settled up!\n-> Thank You for using our application\n");
    if (up[j].ba < 0)
    {
        printf("-> You can pay to: \n\n");
        for (int z=0;z<number_of_people+1;z++)
        {
            if (up[z].ba > 0 )
            {
                printf(">> %s Balance : $%.2f\n",up[z].name, up[z].ba);
            }
        }
        printf("\n-> The maximum value you can pay: $%.2f\n\n", -up[j].ba);
        printf("-> Please enter the name of the person you want to pay(with no spaces): ");
        fflush(stdin);
        scanf("%s", take_name);
        i=0;
        while(i<number_of_people+1)
        {
            if (((strcmp(take_name, up[i].name)==0) && (up[i].ba > 0))==1)
            {
                printf(">> %s\n", up[i].name);
                break;
            }
            i++;
            if (i > number_of_people)
            {
                MessageBox(0, "Name you entered does not match with the available option names!", "Splitwise", MB_ICONERROR);
                printf("\n-> Please enter the name of the person you want to pay(with no spaces): ");
                scanf("%s", take_name);
                i=0;
            }

        }
        while (1)
            {
                printf("\n-> Please enter the amount you want to pay: $");
                fflush(stdin);
               // scanf("%f", &val);
                val = scan_float();
                if (val <= -(up[j].ba))
                {

                    for (z=0; z<number_of_people+1; z++)
                    {
                        if (strcmp(take_name, up[z].name) == 0)
                            {
                                up[z].ba -= val;
                                up[j].ba += val;

                            }
                    }
                    //printf("\n\nAccount has been settled\n");
                    //printf("Press any key to continue");
                    //getch();
                    break;
                }
                else
                {
                    MessageBox(0,"Amount you entered is greater than the maximum you can pay!", "Splitwise", MB_ICONERROR);
                }
            }

    }
/*
    fseek(first, 0, SEEK_END);
 //   fprintf(first, "\n-----------------------------------------------------------\n")
    fprintf(first, "\n%s paid $%.2f to %s\n",up[j].name, val, take_name);
 //   fprintf(first, "\n-----------------------------------------------------------\n");
*/
    f = fopen(name_up, "wb");
    for (i=0; i<number_of_people+1; i++)
    {
        fwrite(&up[i], sizeof(up[i]), 1, f);
    }
    fclose(f);
     MessageBox(0, "Account have been settled!(Refer Balances)", "Splitwise", MB_ICONASTERISK);
    //printf("Press any key to continue");
    //printf("\n-> (If you have made any changes, you can check in balances)");
}

