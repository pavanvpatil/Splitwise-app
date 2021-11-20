#include"sub_group_details1.h"

void Sub_create_new_group(char passingname[])
{
    char grpname1[60];
    char grp_grpname1[60];
    char subgrpname[60];
    system("cls");
    FILE *f;
    printf("\n********TO CREATE NEW SUB GROUP********\n");
    printf("\nEnter the new sub group name(with no spaces): ");
    scanf("%s",grp_grpname1);
    strcpy(subgrpname,passingname);
    strcat(subgrpname,"subgroup.txt");
    strcpy(grpname1,grp_grpname1);
    strcat(passingname,grpname1);
    strcpy(expensecal, passingname);
    strcat(expensecal, "_expense.txt");
    strcat(passingname,".txt");
    if((f=fopen(passingname,"r"))==NULL)
    {

// AK
        FILE *f;
        f = fopen(expensecal, "wb");
        fclose(f);

//AK
        fclose(f);
        f=fopen(passingname,"w");
        fseek(f,0,SEEK_SET);
        fprintf(f,"`\n");
        fseek(f,1000,SEEK_SET);
        fprintf(f,"\n");
        fprintf(f,"~\n");
        fclose(f);
        char message[50];
        snprintf(message,50,"/*-----%s sub group created-----*/",grpname1);
        MessageBox(0,message, "SPLITWISE",MB_OK);
        f=fopen(subgrpname,"a");
        fprintf(f,"%s\n",grpname1);
        fclose(f);
    }
    else
    {
        snprintf(message,100,"%s sub group already exists\n(Please use other name to create sub group)",grpname1);
        MessageBox(0,message,"SPLITWISE",MB_OK);
    }
}

void sub_delete_group(char passingname[])
{
    char c,grpname1[60],grpname12[60];
    char grp_grpname1[60],grpname123[60];
    strcpy(grpname12,passingname);
    int n,i=0;
    FILE *f,*fp;
    system("cls");
    strcat(passingname,"subgroup.txt");
    f=fopen(passingname,"r");
    fscanf(f,"%c",&c);
    if(!feof(f))
    {
        fclose(f);
        printf("\n********SUB GROUPS AVAILABLE ARE********\n");
        f=fopen(passingname,"r");
        while(!feof(f))
        {
            fgets(grp_grpname1,15,f);
            if(feof(f))
                break;
            printf("%d.%s",++i,grp_grpname1);
        }
        fclose(f);
        fflush(stdin);
        printf("\nEnter the sub group name to delete(with no spaces): ");
        scanf("%s",grp_grpname1);
        strcat(grpname12,grp_grpname1);
        strcpy(expensecal,grpname12);
        strcat(expensecal,"_expense.txt");
        strcat(grpname12,".txt");
        if((f=fopen(grpname12,"r"))!=NULL)
        {
            fclose(f);
            snprintf(message,50, "Are you sure you want to delete %s sub group",grp_grpname1);
            n=MessageBox(0,message, "SPLITWISE",MB_YESNO);
            if(n==6)
            {
                 remove(grpname12);
                 remove(expensecal);
                 f=fopen(passingname,"r");
                 fp=fopen("temp.txt","w");
                 while(!feof(f))
                 {
                      fscanf(f,"%s",grpname123);
                      if(strcmp(grp_grpname1,grpname123)!=0)
                      {
                         if(feof(f))
                            break;
                         fprintf(fp,"%s",grpname123);
                         fprintf(fp,"\n");
                      }
                 }
                 fclose(f);
                 fclose(fp);
                 remove(passingname);
                 rename("temp.txt",passingname);
                 snprintf(message,50,"/*-----%s group successfully deleted-----*/",grp_grpname1);
                 MessageBox(0,message, "SPLITWISE",MB_OK);
             }
             else
             {
                  snprintf(message,50,"/*-----%s sub group not deleted-----*/",grp_grpname1);
                  MessageBox(0,message,"SPLITWISE",MB_ICONERROR);
             }
        }
        else
            MessageBox(0,"/*------SUB GROUP NOT FOUND------*/","SPLITWISE",MB_ICONERROR);
    }
    else
    {
        fclose(f);
        MessageBox(0,"Sub Groups are not available to delete","SPLITWISE",MB_ICONERROR);
    }
}

void sub_display_groups(char passingname[],int peoplea)
{
     char grpa[60],grpb[60],expensecal[60],grpc[60];
     strcpy(grpa,passingname);
     strcpy(grpc,passingname);
     FILE *first;//this is the file related to a group
     int people,i=0,choose;
     long int position;
     float a,rem=0,amount;
     char nam[20],expense[100],c,grpname[60];
     system("cls");
     FILE *f;
     strcat(passingname,"subgroup.txt");
     f=fopen(passingname,"r");
     fscanf(f,"%c",&c);
     if(!feof(f))
     {
         fclose(f);
         printf("\n*********THE SUB GROUPS ARE*********\n");
         f=fopen(passingname,"r");
         while(!feof(f))
         {
              fgets(grp_grpname,15,f);
              if(feof(f))
              break;
              printf("%d.%s",++i,grp_grpname);
         }
         fclose(f);
         printf("\nEnter the sub group name to choose(with no spaces): ");
         scanf("%s",&grp_grpname);
// AK
        strcat(grpa,grp_grpname);
        strcpy(expensecal,grpa);
        strcat(expensecal,"_expense.txt");
// AK
         strcpy(grpname,grp_grpname);
         strcat(grpa,".txt");
         if((f=fopen(grpa,"r"))!=NULL)
         {
             fclose(f);
             system("cls");
             do
             {
                 strcpy(grpb,grpc);
                 people=0;
                 first=fopen(grpa,"r+");
                 fseek(first,0,SEEK_SET);
                 while(strcmp(g[people-1].name,"`")!=0)//when the nam becomes "`" we know end of names
                 {
                     fscanf(first,"%s",g[people].name);
                     people++;
                 }
                 people=people-1;
                 if(people==0)
                 {
                    sub_add_member_first_time(first,grpb,peoplea);
                    continue;
                 }
                 system("cls");
                 printf("\n****%s sub-group details are****\n",grpname);
                 printf("\nChoose an option:\n");
                 printf("\n1.Add expense \n2.Display Activities \n3.Balances ");
                 printf("\n4.Settle-Up \n5.Total \n6.Display sub-group members \n7.Add member\n8.Delete member \n9.Exit \n");
                 printf("\nEnter the choice: ");
                 scanf("%d",&choose);
                 switch(choose)
                 {
                      case 2:sub_display_activities(first);
                        break;
                      case 3:sub_balances(people,expensecal);
                        break;
                      case 5:sub_total(first);
                        break;
                      case 1:sub_add_expense(first,people,expensecal);
                        break;
                      case 7:sub_add_member(first,people,grpb,peoplea,expensecal);
                        break;
                      case 8:sub_Delete_member(first,people,grpa);
                        break;
                      case 6:sub_display_members(first);
                        break;
                      case 4:sub_settle_up(expensecal);
                        break;
                      case 9:break;
                      default:
                            {
                              //Beep(1000,500);
                              MessageBox(0,"/*-------Invalid choice-------*/","SPLITWISE",MB_ICONERROR);
                            }
                 }
                 system("cls");
                 fclose(first);
              }while(choose!=9);
          }
          else
               {
                   //Beep(1000,500);
                   MessageBox(0,"/*------SUB GROUP NOT FOUND------*/", "SPLITWISE",MB_ICONERROR);
                }
     }
     else
     {
         //Beep(1000,500);
         MessageBox(0,"Sub Groups are not created.\nPlease create a sub group!","SPLITWISE",MB_ICONERROR);
         fclose(f);
     }
}
