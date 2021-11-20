#include"group_details.h"
#include"sub_group.h"

void display_groups()
{
     char passingname[60];
     FILE *first;//this is the file related to a group
     int people,i=0,choose;
     long int position;
     float a,rem=0,amount;
     char nam[20],expense[100],c,grpname[60],grp_grpname[60];
     system("cls");
     FILE *f;
     f=fopen("group.txt","r");
     fscanf(f,"%c",&c);
     if(!feof(f))
     {
         fclose(f);
         printf("\n*********THE GROUPS ARE*********\n");
         f=fopen("group.txt","r");

         while(!feof(f))
         {
              fgets(grp_grpname,15,f);
              if(feof(f))
              break;
              printf("%d.%s",++i,grp_grpname);
         }
         fclose(f);
         printf("\nEnter the group name to choose(with no spaces): ");
         scanf("%s",&grp_grpname);
// AK
        strcpy(expensecal, grp_grpname);
        strcat(expensecal, "_expense.txt");
// AK
         strcpy(grpname,grp_grpname);
         strcat(grp_grpname,".txt");
         if((f=fopen(grp_grpname,"r"))!=NULL)
         {
             fclose(f);
             system("cls");
             do
             {
                 strcpy(passingname,grpname);
                 people=0;
                 first=fopen(grp_grpname,"r+");
                 fseek(first,0,SEEK_SET);
                 while(strcmp(g[people-1].name,"`")!=0)//when the nam becomes "`" we know end of names
                 {
                     fscanf(first,"%s",g[people].name);
                     people++;
                 }
                 people=people-1;
                 if(people==0)
                 {
                    add_member_first_time(first);
                    continue;
                 }
                 system("cls");
                 printf("\n****%s group details are****\n",grpname);
                 printf("\nChoose an option:\n");
                 printf("\n1.Add expense \n2.Display Activities \n3.Balances \n4.Settle-Up \n5.Total \n6.Display group members \n7.Add member");
                 printf("\n8.Delete member \n9.Display sub-groups \n10.Create sub-group \n11.Delete sub-group \n12.Exit \n");
                 printf("\nEnter the choice: ");
                 fflush(stdin);
                 scanf("%d",&choose);
                 switch(choose)
                 {
                      case 2:display_activities(first);
                        break;
                      case 3:balances(grpname,people);
                        break;
                      case 5:total(first);
                        break;
                      case 9:sub_display_groups(passingname,people);
                        break;
                      case 11:sub_delete_group(passingname);
                        break;
                      case 10:Sub_create_new_group(passingname);
                        break;
                      case 1:add_expense(first,people);
                        break;
                      case 7:add_member(first,people);
                        break;
                      case 8:Delete_member(first,people,passingname);
                        break;
                      case 6:display_members(first);
                        break;
                      case 4:settle_up(passingname);
                        break;
                      case 12:break;
                      default:
                          {
                             // Beep(1000,500);
                              MessageBox(0,"/*-------Invalid choice-------*/","SPLITWISE",MB_ICONERROR);
                            }
                 }
                 system("cls");
                 fclose(first);
              }while(choose!=12);
          }
          else
               {
                   //Beep(1000,500);
                   MessageBox(0,"/*------GROUP NOT FOUND------*/", "SPLITWISE",MB_ICONERROR);
                }
     }
     else
     {
         //Beep(1000,500);
         MessageBox(0,"Groups are not created.\nPlease create a group!","SPLITWISE",MB_ICONERROR);
         fclose(f);
     }
}
void create_new_group()
{
    char grpname[20],grpa[20];
    system("cls");
    FILE *f;
    printf("\n********TO CREATE NEW GROUP********\n");
    printf("\nEnter the new group name(with no spaces): ");
    scanf("%s",grp_grpname);

    strcpy(grpname,grp_grpname);
    strcat(grp_grpname,".txt");
    if((f=fopen(grp_grpname,"r"))==NULL)
    {

// AK
        strcpy(grpa,grpname);
        strcat(grpa,"subgroup.txt");
        f=fopen(grpa,"w");
        fclose(f);
        strcpy(expensecal, grpname);
        strcat(expensecal, "_expense.txt");
        f = fopen(expensecal, "wb");
        fclose(f);

//AK
        fclose(f);
        f=fopen(grp_grpname,"w");
        fseek(f,0,SEEK_SET);
        fprintf(f,"`\n");
        fseek(f,1000,SEEK_SET);
        fprintf(f,"\n");
        fprintf(f,"~\n");
        fclose(f);
        char message[50];
        snprintf(message,50,"/*-----%s group is created-----*/",grpname);

        MessageBeep(0);
        MessageBox(0,message, "SPLITWISE",MB_ICONASTERISK);
        f=fopen("group.txt","a");
        fprintf(f,"%s\n",grpname);
        fclose(f);
    }
    else
    {   snprintf(message,100,"%s group already exists\nPlease use some other name for the group",grpname);
        Beep(1000,500);
        MessageBox(0,message,"SPLITWISE",MB_ICONSTOP);
    }
}
void delete_group()
{
    char c,grpname[20],grpa[20],grpb[20],grpexpense[20];
    int n,i=0;
    FILE *f,*fp;
    system("cls");
    f=fopen("group.txt","r");
    fscanf(f,"%c",&c);
    if(!feof(f))
    {
        fclose(f);
        printf("\n********GROUPS AVAILABLE ARE********\n");
        f=fopen("group.txt","r");
        while(!feof(f))
        {
            fgets(grp_grpname,15,f);
            if(feof(f))
                break;
            printf("%d.%s",++i,grp_grpname);
        }
        fclose(f);
        printf("\nEnter the group name to delete(with no spaces): ");
        scanf("%s",grp_grpname);
        char grpexpense[50];
        strcpy(grpname,grp_grpname);
        strcpy(grpexpense,grp_grpname);
        strcat(grpexpense,"_expense.txt");
        strcat(grp_grpname,".txt");
        if((f=fopen(grp_grpname,"r"))!=NULL)
        {
            fclose(f);
            snprintf(message,50, "Are you sure you want to delete %s group",grpname);
            n=MessageBox(0,message, "SPLITWISE",MB_YESNO);
            if(n==6)
            {
                 remove(grp_grpname);
                 remove(grpexpense);
                 f=fopen("group.txt","r");
                 fp=fopen("temp.txt","w");
                 while(!feof(f))
                 {
                      fscanf(f,"%s",grp_grpname);
                      if(strcmp(grp_grpname,grpname)!=0)
                      {
                         if(feof(f))
                            break;
                         fprintf(fp,"%s",grp_grpname);
                         fprintf(fp,"\n");
                      }
                 }
                 fclose(f);
                 fclose(fp);
                 remove("group.txt");
                 rename("temp.txt","group.txt");
                 strcpy(grp_grpname,grpname);
                 strcat(grp_grpname,"subgroup.txt");
                 f=fopen(grp_grpname,"r");
                 while(!feof(f))
                 {
                     strcpy(grpa,grpname);
                     if(feof(f))
                        break;
                     fscanf(f,"%s\n",grpb);
                     strcat(grpa,grpb);
                     strcpy(grpexpense,grpa);
                     strcat(grpexpense,"_expense.txt");
                     remove(grpexpense);
                     strcat(grpa,".txt");
                     remove(grpa);
                 }
                 fclose(f);
                 remove(grp_grpname);
                 snprintf(message,50,"/*-----%s group is successfully deleted-----*/",grpname);
                 MessageBeep(0);
                 MessageBox(0,message, "SPLITWISE",MB_ICONEXCLAMATION);
             }
             else
             {
                  snprintf(message,50,"/*-----%s group is not deleted-----*/",grpname);
                 // MessageBeep(0);
                  MessageBox(0,message,"SPLITWISE",MB_ICONERROR);
             }
        }
        else

            {
               // Beep(1000,500);
                MessageBox(0,"/*------GROUP NOT FOUND------*/","SPLITWISE",MB_ICONWARNING);
            }
    }
    else
    {
        fclose(f);
       // Beep(1000,500);
        MessageBox(0,"Groups are not available to delete","SPLITWISE",MB_ICONWARNING);
    }
}
