#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"group.h"

int main()
{
    FILE *fg;
    int choose,n;
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 10);
    if((fg=fopen("group.txt","r"))==NULL)
        fg=fopen("group.txt","w");
    fclose(fg);
    MessageBeep(0);
    MessageBox(0,"WELCOME TO SPLITWISE APP","SPLITWISE",MB_ICONASTERISK);
//    Beep(1000,500);
    do
    {
        printf("*******************SPLITWISE*******************\n");
        printf("\nChoose the option:\n");
        printf("\n1.Display groups \n2.Create new group \n3.Delete group \n4.Exit \n");
        printf("\nEnter the choice: ");
        fflush(stdin);
        scanf("%d",&choose);
        switch(choose)
        {
            case 1:display_groups();
                   break;
            case 2:create_new_group();
                   break;
            case 3:delete_group();
                   break;
            case 4:
                {
                    Beep(100,500);
                    n=MessageBox(0,"Are you sure you want to exit 'SPLITWISE' app","SPLITWISE",MB_YESNO);
                   break;
                }
            default:
                {
                    //Beep(100,500);
                    MessageBox(0,"/*-------Invalid choice-------*/","SPLITWISE",MB_ICONERROR);
                }
        }
        system("cls");
    }while(n!=6);
    MessageBox(0,"'SPLITWISE' app closed successfully","SPLITWISE",MB_ICONASTERISK);
    return 0;
}
