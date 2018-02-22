#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	FILE *empdata,*emptmp;
	char ch,tch;
	struct employee
	{
		char name[50];
		char eid[10];
		int age;
		float salary;
	};
	struct employee e;
	char empname[50];
	long int rsize;
	empdata=fopen("EMP.DATA","rb+");
	if(empdata==NULL)
	{
		empdata=fopen("EMP.DATA","wb+");
		if(empdata==NULL)
		{
			printf("File cannot be opened");
			exit(1);
		}
	}
	rsize=sizeof(e);
	while(1)
	{
		system("cls");
		printf("1.ADD RECORD\n");
		printf("2.VIEW RECORD\n");
		printf("3.MODIFY RECORD\n");
		printf("4.DELETE RECORD\n");
		printf("5.EXIT MENU\n");
		printf("ENTER YOUR CHOICE:-\n");
		scanf("%c",&ch);
		switch(ch)
		{
			case '1':
				system("cls");
				fseek(empdata,0,SEEK_END);
				tch= 'Y';
				while(tch== 'Y')
				{
					printf("\nENTER EMPLOYEE ID:- ");
					scanf("%s",e.eid);
					printf("\nENTER EMPLOYEE NAME:- ");
					scanf("%s",e.name);
					printf("\nENTER EMPLOYEE AGE:- ");
					scanf("%d",&e.age);
					printf("\nENTER EMPLOYEE SALARY:- ");
					scanf("%f",&e.salary);
					fwrite(&e,rsize,1,empdata);
					printf("\nADD ANOTHER RECORD(Y/N):- ");
				    tch=getch();
				    printf("\n");
				}
				break;
			case '2':
				system("cls");
				rewind(empdata);
				printf("E.ID\tE.NAME\tE.AGE\tE.SALARY");
				while(fread(&e,rsize,1,empdata)==1)
                {
                    printf("\n%s\t%s\t%d\t%.2f",e.eid,e.name,e.age,e.salary);
                }
                getch();
                break;
		    case '3':
		    	system("cls");
		    	tch= 'Y';
		    	while(tch== 'Y')
				{
				printf("ENTER THE EMPLOYEE NAME TO MODIFY:- ");
                scanf("%s", empname);
		    	rewind(empdata);
		    	while(fread(&e,rsize,1,empdata)==1)
		    	{
                    if(strcmp(e.name,empname) == 0)  ///if entered name matches with that in file
                    {
                        printf("\nENTER NEW ID,NAME,AGE AND SALARY: ");
                        scanf("%s%s%d%f",e.eid,e.name,&e.age,&e.salary);
                        fseek(empdata,-rsize,SEEK_CUR);
                        fwrite(&e,rsize,1,empdata);
                        break;
                    }
                }
                printf("\nMODIFY ANOTHER RECORD(Y/N):- ");
                tch=getch();
                }
                break;
            case '4':
            	system("cls");
            	tch = 'Y';
                while(tch == 'Y')
                {
                printf("\nENTER THE EMPLOYEE NAME WHOSE RECORD IS TO BE DELETED:- ");
                scanf("%s",empname);
                emptmp = fopen("TEMP.DATA","wb");
                rewind(empdata);
                while(fread(&e,rsize,1,empdata) == 1)
                {
                    if(strcmp(e.name,empname) != 0)
                    {
                        fwrite(&e,rsize,1,emptmp);
                    }
                }
                fclose(empdata);
                fclose(emptmp);
                remove("EMP.DATA");
                rename("TEMP.DATA","EMP.DATA");
                empdata = fopen("EMP.DATA", "rb+");
                printf("DELETE ANOTHER RECORD(Y/N):- ");
                tch=getch();
                }
                break;
            case '5':
            	fclose(empdata);
            	exit(0);
                break;
		}
	}
	return 0;
}

