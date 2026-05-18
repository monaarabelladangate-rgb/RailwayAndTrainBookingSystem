#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

struct train
{
    int no,stations;
    char src[30],dest[30],path[10000],distance[10000];
}tr;

struct stations
{
    char stns[10000];
}st;

FILE *fp1,*fp2,*fp3;

void insert()
{
    char Dist [10000];
    fp1 = fopen("train.txt","r");
    while(fread(&tr,sizeof(tr),1,fp1) == 1);
    printf("\nLast train no : %d",tr.no);
    tr.no += 1;
    memset(tr.path, 0, 10000*sizeof(tr.path[0]));
    memset(tr.distance, 0, 10000*sizeof(tr.distance[0]));
    strcpy(tr.distance, "0,");
    printf("\nNew train no : %d",tr.no);
    printf("\nEnter train record to insert : ");
    printf("\nEnter train source : ");
    fflush(stdin);
    gets(tr.src);
    printf("\nEnter train destination : ");
    fflush(stdin);
    gets(tr.dest);
    printf("\nEnter number intermediate stations : ");
    scanf("%d",&tr.stations);
    printf("\nEnter middle stations between source and destination seperated by ',' \n");
    fflush(stdin);
    gets(tr.path);
    printf("\nEnter the distance between stations from source to detination seperated by ',' \n");
    fflush(stdin);
    gets(Dist);
    strcat(tr.distance,Dist);
    printf("\nDistance list : %s",tr.distance);
    fclose(fp1);
    fp1 = fopen("train.txt","a");
    fwrite(&tr,sizeof(tr),1,fp1);
    fclose(fp1);
    printf("\nTrain record added successfully");
}

void modify()
{
    int no1,flag=0;
    fp1 = fopen("train.txt","r");
    fp2 = fopen("trainTemp.txt","w");
    printf("\nEnter train no to modify : ");
    scanf("%d",&no1);
    while(fread(&tr,sizeof(tr),1,fp1) == 1)
    {
        if(tr.no == no1)
        {
            printf("\nEnter train record to modify : ");
            printf("\nEnter train source : ");
            fflush(stdin);
            gets(tr.src);
            printf("\nEnter train destination");
            fflush(stdin);
            gets(tr.dest);
            printf("\nEnter number intermediate stations : ");
            scanf("%d",&tr.stations);
            tr.stations += 2;
            printf("\nEnter middle stations between source and destination seperated by ',' \n");
            fflush(stdin);
            gets(tr.path);
            flag=1;
        }
        fwrite(&tr,sizeof(tr),1,fp2);
    }
    if(flag == 0)
        printf("\nTrain no not found!! modification failed! try again\n");
    else if(flag == 1)
        printf("\nTrain record modified successfully\n");
    fclose(fp1);
    fclose(fp2);
    remove("train.txt");
    rename("trainTemp.txt","train.txt");
}

void delete()
{
    int no1,flag=0;
    fp1 = fopen("train.txt","r");
    fp2 = fopen("trainTemp.txt","w");
    printf("\nEnter train no to delete : ");
    scanf("%d",&no1);
    while(fread(&tr,sizeof(tr),1,fp1) == 1)
    {
        if(tr.no != no1)
            fwrite(&tr,sizeof(tr),1,fp2);
        else if(tr.no == no1)
            flag = 1;
    }
    if(flag == 0)
        printf("\nTrain no not found!! deletion failed! try again\n");
    else if(flag == 1)
        printf("\nTrain record deleted successfully\n");
    fclose(fp1);
    fclose(fp2);
    remove("train.txt");
    rename("trainTemp.txt","train.txt");
}

void search()
{
    int no1,flag = 0;
    printf("Enter train no to search : ");
    scanf("%d",&no1);
    fp1 = fopen("train.txt","r");
    while(fread(&tr,sizeof(tr),1,fp1) == 1)
    {
        if(tr.no == no1)
        {
            printf("\nTrain details : \n");
            printf("Train no : %d\ntotal stations : %d\nTrain source : %s\nTrain destination : %s \npath of the train : %s\nDistance between stations : %s\n",tr.no,tr.stations,tr.src,tr.dest,tr.path,tr.distance);
            memset(tr.path, 0, 10000*sizeof(tr.path[0]));
            flag = 1;
        }
    }
    if(flag == 0)
        printf("\nTrain details not found");
    fclose(fp1);
}

void stationList()
{
    fp1 = fopen("stations.txt","r");
    printf("The available stations are : \n");
    while(fread(&st,sizeof(st),1,fp1) == 1)
    {
        printf("%s\n",st.stns);
    }
    printf("\nEnter new stations to insert to the list seperated by comma : \n");
    fclose(fp1);
    fp1 = fopen("stations.txt","a");
    fflush(stdin);
    gets(st.stns);
    //printf("start%send",st.stns);
    if(st.stns[0] != '\0')
    {
        //printf("Entered");
        fwrite(&st,sizeof(st),1,fp1);
    }
    fclose(fp1);
}

void userSearch()
{
    char temp[1000],src1[100],dest1[100],dist1[1000];
    int flag = 0,count,dist;
    system("cls");
    printf("\n!!!!MESSAGE : from builder of this application.. no ticktes will be required to travel in trains, it's absolutely free :) HAPPY & SAFE JOURNEY\n");
    printf("\nSTATION LIST : \n");
    fp3 = fopen("stations.txt","r");
    while(fread(&st,sizeof(st),1,fp3)==1)
       printf("%s\n",st.stns);
    fclose(fp3);
    printf("\nEnter train source : ");
    fflush(stdin);
    gets(src1);
    printf("\nEnter train destination : ");
    fflush(stdin);
    gets(dest1);
    int i,j=0,m,n;
    fp1 = fopen("train.txt","r");
    while(fread(&tr,sizeof(tr),1,fp1) == 1)
    {
        i=j=count=dist=m=n=0;
        if( strcmp(tr.src,src1) == 0 && strcmp(tr.dest,dest1) == 0 )
        {
            printf("\n\nThis train is available for this source and destination \n");
            while(tr.distance[i] != '\0')
            {
                if(tr.distance[i]==',' || tr.distance[i+1]=='\0')
                {
                    if(tr.distance[i+1] == '\0')
                        dist1[j++] = tr.distance[i++];
                    dist += atoi(dist1);
                    //printf("%d\n",dist);
                    memset(dist1,0,j*sizeof(dist1[0]));
                    j=0;
                    i++;
                }
                else
                    dist1[j++] = tr.distance[i++];
            }
            if(dist%20 != 0)
                dist += 20;
            printf("Train no : %d\nTrain fare : %d Rs.",tr.no,(dist/20)*5);
            flag = 1;
        }
        else if(strcmp(tr.src,src1) == 0)
        {
            //printf("\nSOURCE FOUND\n");
            count=0;
            m=2;
            while(tr.path[i] != '\0')
            {
                //printf("%s",tr.distance);
                if(tr.path[i] == ',')
                {
                    count+=1;
                    temp[j] = '\0';
                    //printf("temp : %s",temp);
                    while(tr.distance[m] != ',')
                    {
                        dist1[n++] = tr.distance[m++];
                    }
                    m++;
                    //printf("m : %d,n : %d",m,n);
                    dist += atoi(dist1);
                    //printf("dist : %d\n",dist);
                    memset(dist1,0,n*sizeof(dist1[0]));
                    if(strcmp(dest1,temp) == 0)
                        {tr.path[i] = '\0';flag=2;break;}
                    memset(temp, 0, j*sizeof(temp[0]));
                    j=n=0;
                    i++;
                }
                else if(tr.path[i+1] == '\0')
                {
                    count+=1;
                    temp[j++] = tr.path[i++];
                    temp[j]='\0';
                    //printf("LASTtemp : %sdest : %s\n",temp,dest1);
                    //printf("m : %d,n : %d",m,n);
                    if(strcmp(dest1,temp) == 0)
                        {tr.path[i] = '\0';
                        while(tr.distance[m] != ',')
                        {
                            dist1[n++] = tr.distance[m++];
                        }
                        m++;
                        dist += atoi(dist1);
                        //printf("LASTdist : %d\n",dist);
                        memset(dist1,0,n*sizeof(dist1[0]));
                        flag=2;break;
                        }
                    memset(temp, 0, j*sizeof(temp[0]));
                    
                    j=n=0;
                    i++;
                }
                else    
                    temp[j++] = tr.path[i++];
                //printf("temp[j] : %c\ts[i] : %c\n",temp[j-1],tr.path[i]);
            }
        }
        else if(strcmp(tr.dest,dest1) == 0)
        {
            int cnt;
            //printf("\nDESTINATION FOUND\n");
            while(tr.distance[m] != ',')
                m++;
            m++;
            while(tr.path[i] != '\0')
            {
                    //printf("temp : %s\n",temp);
                if(tr.path[i] == ',')
                {
                    //printf("%d\n",strlen(temp));
                    temp[j]='\0';
                    if(strcmp(src1,temp) == 0)
                        {flag=2;
                        cnt = count;
                        //printf("INSIDE\ncount : %d\n",cnt);
                        while(cnt>=0)
                        {
                            while(tr.distance[m] != ',')
                                m++;
                            m++;
                            cnt--;
                        }
                        count=0;
                        }
                    else
                        count+=1;
                    if(flag == 2)
                    {
                        while(tr.distance[m] != ',')
                        {
                            dist1[n++] = tr.distance[m++];
                        }
                        m++;
                        //printf("m : %d,n : %d",m,n);
                        dist += atoi(dist1);
                        //printf("dist : %d\n",dist);
                        memset(dist1,0,n*sizeof(dist1[0]));
                    }
                    memset(temp, 0, j*sizeof(temp[0]));
                    j=n=0;
                    i++;
                }
                else if(tr.path[i+1] == '\0')
                {
                    temp[j++] = tr.path[i++];
                    //printf("temp : %s\n",temp);
                    if(strcmp(src1,temp) == 0)
                        {flag=2;
                        cnt = count;
                        //printf("INSIDE\ncount : %d\n",cnt);
                        while(cnt>=0)
                        {
                            while(tr.distance[m] != ',')
                                m++;
                            m++;
                            cnt--;
                        }
                        count=0;}
                    else
                        count+=1;
                    memset(temp, 0, j*sizeof(temp[0]));
                    if(flag==2)
                    {
                    while(tr.distance[m] != '\0')
                    {
                        //printf("m : %d,n : %d",m,n);
                        if(tr.distance[m]==',' || tr.distance[m+1]=='\0')
                        {
                            if(tr.distance[m+1] == '\0')
                                dist1[n++] = tr.distance[m++];
                            dist += atoi(dist1);
                            //printf("INELSEdist : %d\ndist1 : %d",dist,atoi(dist1));
                            memset(dist1,0,n*sizeof(dist1[0]));
                            n=0;
                            m++;
                        }
                        else
                            dist1[n++] = tr.distance[m++];
                    }//marked
                    }
                    j=0;
                    i++;
                }
                else    
                    temp[j++] = tr.path[i++];
                //printf("temp[j] : %c\ts[i] : %c\n",temp[j],tr.path[i]);
            }
            count+=1;
        }
        else if(strcmp(src1,tr.dest) != 0 && strcmp(dest1,tr.src) != 0)
        {
            int cnt;
            while(tr.distance[m] != ',')
                m++;
            m++;
            while(tr.path[i] != '\0')
            {
                if(tr.path[i] == ',')
                {
                    //printf("temp : %s\n",temp);
                    //printf("%d\n",strlen(temp));
                    temp[j] = '\0';
                    if(strcmp(src1,temp) == 0)
                        {
                        //printf("\nMIDDLE FOUND\n");
                            cnt = count;
                            //printf("INSIDE\ncount : %d\n",cnt);
                            while(cnt>=0)
                            {
                                while(tr.distance[m] != ',')
                                    m++;
                                m++;
                                cnt--;
                            }count=0;flag=3;
                        }
                    else if(strcmp(dest1,temp) == 0 && flag == 3)
                        {flag=2;count+=1;tr.path[i]='\0';memset(dist1,0,n*sizeof(dist1[0]));break;}
                    else
                        count+=1;
                    if(flag == 3)
                    {
                        while(tr.distance[m] != ',')
                        {
                            dist1[n++] = tr.distance[m++];
                        }
                        m++;
                        //printf("m : %d,n : %d",m,n);
                        dist += atoi(dist1);
                        //printf("dist : %d\n",dist);
                        memset(dist1,0,n*sizeof(dist1[0]));
                    }
                    memset(temp, 0, j*sizeof(temp[0]));
                    j=n=0;
                    i++;
                }
                else if(tr.path[i+1] == '\0')
                {
                    //printf("temp : %s\n",temp);
                    temp[j++] = tr.path[i++];
                    //printf("temp : %s\n",temp);
                    temp[j] = '\0';
                    if(strcmp(src1,temp) == 0)
                        {
                            cnt = count;
                            //printf("INSIDE\ncount : %d\n",cnt);
                            while(cnt>=0)
                            {
                                while(tr.distance[m] != ',')
                                    m++;
                                m++;
                                cnt--;
                            }
                            count=0;flag=3;
                        }
                    else if(strcmp(dest1,temp) == 0 && flag == 3)
                        {flag=2;count+=1;tr.path[i]='\0';memset(dist1,0,n*sizeof(dist1[0]));break;}
                    else
                        count+=1;
                    if(flag == 3)
                    {
                        while(tr.distance[m] != ',' && tr.distance[m] != '\0')
                        {
                            dist1[n++] = tr.distance[m++];
                        }
                        m++;
                        //printf("m : %d,n : %d",m,n);
                        dist += atoi(dist1);
                        //printf("dist : %d\n",dist);
                        memset(dist1,0,n*sizeof(dist1[0]));
                    }
                    memset(temp, 0, j*sizeof(temp[0]));
                    j=n=0;
                    i++;
                }
                else    
                    temp[j++] = tr.path[i++];
                //printf("temp[j] : %c\ts[i] : %c\n",temp[j],tr.path[i]);
            }
            if(flag == 3)
                flag=0;
        }
    if(flag == 2)
    {    printf("\nTrain found with station distance %d\n",count);
        printf("\n\nThis train is available for this source and destination \n");
        printf("The distance is : %dKM\n",dist);
        if(dist%20 != 0)
            dist += 20; 
        printf("Train no : %d\nTrain fare : %d Rs.",tr.no,(dist/20)*5);
        flag=1;
    }
}
    if(flag == 0 || flag == 3)
        printf("\n\aNo train is avaialble for this source and destination\n");
    }

void main(int argc,char *argv[])
{
    int ch;
    if(strcmp(argv[1],"admin") == 0 && strcmp(argv[2],"admin00") == 0)
    {
        printf("\n\n====WELCOME ADMIN====\n");
        while(1)
        {
            printf("\n\n\t\t\t\t======Train Database======\t");
            printf("\nEnter 1 to insert train details"
            "\nEnter 2 to search train details"
            "\nEnter 3 to modify train details"
            "\nEnter 4 to delete train details"
            "\nEnter 5 to insert new station list"
            "\nEnter 6 to exit"
            "\nEnter your choice : ");
            fflush(stdin);
            if(scanf("%d",&ch) == 1 && getchar() == '\n')
            {switch(ch)
            {
                case 1 :
                    insert();
                    break;
                case 2 : 
                    search();
                    break;
                case 3 : 
                    modify();
                    break;
                case 4 :
                    delete();
                    break;
                case 5 :
                    stationList();
                    break;
                case 6 :
                    exit(0);
                default :
                    printf("\nWrong input\n");
            }
            }
            else
                printf("\nEnter data in correct format\n");
        }
    }
    else if(argc != 0)
    {
        printf("\n\n====WELCOME %s====\n",argv[1]);
        while(1)
        {
            printf("\n\n\t\t\t\t======Train Booking System======\t");
            printf("\nEnter 1 to search for available trains"
            "\nEnter 2 to exit"
            "\nEnter your choice : ");
            fflush(stdin);
            fflush(stdin);
            if(scanf("%d",&ch) == 1 && getchar() == '\n')
            {switch(ch)
            {
                case 1 :
                    userSearch();
                    break;
                case 2 :
                    exit(0);
                default : 
                    printf("\nWrong Input\n"); 
            }
            }
            else
                printf("\nEnter data in correct format\n");
        }
    }
    else
        exit(0);
}
