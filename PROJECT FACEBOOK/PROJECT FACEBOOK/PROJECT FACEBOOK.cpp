// fb.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "io.h"

struct USERS
{
	char user_name[40];
	char passwd[40];
	int user_id;
	int friendlist[10];
};

struct POST
{
	int post_id;
	int no_of_likes;
	char post_text[128];
	char comment_text[10][128];
	int comment_user_id[10];
};

void create_hard_drive(FILE* fp)
{
	int iter_loop =10*1024*1024;
	while(iter_loop>0)
	{
		fputc('0',fp);
		fflush(fp);
		iter_loop--;
	}
}

int check_availability(char* user_name,FILE* fp,int count)
{
	 USERS *users=(USERS*)malloc(sizeof(USERS));
	 int temp=0;
	 fseek(fp,sizeof(count),SEEK_SET);
	 while(temp<=count)
	 {
		 fread(users,sizeof(USERS),1,fp);
	 if(strcmp(user_name,users->user_name)==0)
		 {
			 return -1;
		 }
	 temp++;
	 }
	return 1;
}

void sign_up(FILE* fp ,int count)
{
	char *user_name = (char*)calloc(40,sizeof(char));
	USERS* users=(USERS*)malloc(sizeof(struct USERS));
	memset(users->user_name,'\0',40*sizeof(char));
	memset(users->passwd,'\0',40*sizeof(char));
	fseek(fp,sizeof(int),SEEK_SET);
	printf("USER NAME AND PASSWORD MUST BE NOT MORE THAN 40 CHARACTERS.\n");
	printf("ENTER USER NAME: ");
	fflush(stdin);
	gets(user_name);
	while (check_availability(user_name,fp,count) == -1)
	{
		printf("INVALID CREDENTIALS A USER WITH THE SAME NAME ALREADY EXISTS. ENTER USER NAME: ");
		fflush(stdin);
		gets(user_name);
	}
	for(int iter_loop=0;user_name[iter_loop-1]!='\0';iter_loop++)
	{
		users->user_name[iter_loop] = user_name[iter_loop];
	}
	printf("ENTER PASSWORD: ");
	gets(users->passwd);
	users->user_id = count+1;
	fseek(fp,sizeof(int)+count*sizeof(USERS),0);
	for(int iter_loop=0;iter_loop<10;iter_loop++)
	{
		users->friendlist[iter_loop]=0;
	}
	fwrite(users,sizeof(USERS),1,fp);
	fflush(fp);
	printf("REGISTRATION DONE!!!\n");
}

int display_users(FILE *fp,int count)
{
	int iter_loop=0, count_users = 0;
	fseek(fp,sizeof(int),0);
	USERS *buffer=(USERS*)malloc(sizeof(USERS));
	for(iter_loop=0;iter_loop<count;iter_loop++)
	{
		count_users++;
		fseek(fp,(sizeof(USERS)*iter_loop)+sizeof(int),0);
		fread(buffer,sizeof(USERS),1,fp);
		printf("%s<----->%d \n",buffer->user_name,buffer->user_id);
	}
	free(buffer);
	return count_users;
}

void display_users_friendslist(FILE* fp,int count,int u_id, int my_id)
{
	int temp = 0,curr_position = ftell(fp),index=0;
	fseek(fp,sizeof(int),0);
	USERS *users = (USERS*)calloc((count+1),sizeof(USERS));
	while(temp<count)
	{
		fread(&users[index],sizeof(USERS),1,fp);
		index++;
		temp++;
		printf("ENTERED %d\n",index+1);
	}

	int iter_loop = 0;
	while(users[my_id-1].friendlist[iter_loop]!=0)
	{
		iter_loop++;
		printf("ENTERED %d\n",iter_loop+1);
	}
	users[my_id-1].friendlist[iter_loop] = u_id;
	fseek(fp,((my_id-1)*sizeof(USERS)+sizeof(int)),0);
	printf("ABOUT TO WRITE.\n");
	fwrite(&users[my_id-1],sizeof(USERS),1,fp);
	fflush(fp);
	iter_loop = 0;
	while(users[u_id-1].friendlist[iter_loop]!=0)
	{
		iter_loop++;
	}
	users[u_id-1].friendlist[iter_loop] = my_id;
	fwrite(&users[u_id-1],sizeof(USERS),1,fp);
	fflush(fp);
	iter_loop = 0;
	while(users[my_id-1].friendlist[iter_loop]!=0)
	{
		printf("%d",users[my_id-1].friendlist[iter_loop]);
		iter_loop++;
	}
	iter_loop = 0;
	while(users[u_id-1].friendlist[iter_loop]!=0)
	{
		printf("%d",users[u_id-1].friendlist[iter_loop]);
		iter_loop++;
	}
	free(users);
}

void display_all_posts_by_user(FILE *fp, int user_id)
{
	fseek(fp,(user_id*1024)+(1024*1024),0);
	char ch = fgetc(fp);
	if(ch=='0')
	{
		printf("USER %d HAS NO POSTS\n", user_id);
		return;
	}
	POST *post = (POST*)malloc(sizeof(POST));
	while(ch!='0')
	{
		fseek(fp,ftell(fp)-1,0);
		fread(post,sizeof(POST),1,fp);
		printf("\nPOST NO %d:  %s",post->post_id,post->post_text);
		ch = fgetc(fp);
	}
	free(post);
}

void show_posts_by_friends(FILE *fp, int count, int user_id)
{
	fseek(fp,sizeof(int),SEEK_SET);
	USERS *buffer=(USERS*)malloc(sizeof(USERS));
	for(int iter_loop=0;iter_loop<count;iter_loop++)
	{
		fseek(fp,(sizeof(USERS)*iter_loop)+sizeof(int),SEEK_SET);
		fread(buffer,sizeof(USERS),1,fp);
		if(buffer->user_id == user_id)
		{
			break;
		}
	}
	for(int iter_loop=0;buffer->friendlist[iter_loop]!='0';iter_loop++)
	{
		display_all_posts_by_user(fp,buffer->friendlist[iter_loop]);
	}
	free(buffer);
}

void add_posts(FILE *fp, int user_id)
{
	system("cls");
	fseek(fp,(user_id*1024)+(1024*1024),0);
	char ch = fgetc(fp);
	int post_count = 0;
	if(ch =='0')
	{
		post_count = 1;
	}
	else 
	{
		fseek(fp,(user_id*1024)+(1024*1024),0);
		fread(&post_count,sizeof(int),1,fp);
		post_count++;
	}
	fseek(fp,(user_id*1024)+(1024*1024),0);
	//fread(&count,sizeof(int),1,fp);
	fwrite(&post_count,sizeof(int),1,fp);
	fflush(fp);
	POST *post = (POST*)malloc(sizeof(POST));
	char *post_buffer = (char*)calloc(128,sizeof(char));
	printf("ENTER THE POST, IT SHOULDN'T BE MORE THAN 128 CHARACTERS:   ");
	fflush(stdin);
	gets(post_buffer);
	for(int iter_loop=0;post_buffer[iter_loop-1]!='\0';iter_loop++)
	{
		post->post_text[iter_loop] = post_buffer[iter_loop];
	}
	memset(post->comment_text,0,(10*128)*sizeof(char));
	memset(post->comment_user_id,0,10);
	post->no_of_likes = 0;
	post->post_id = post_count;
	printf("\nPOST ID IS: %d\n",post_count);
	if(post_count>0)
	{
		fseek(fp,(((user_id*1024)+(1024*1024))+((post_count-1)*sizeof(POST))),0);
	}
	else if(post_count==0)
	{
		fseek(fp,(((user_id*1024)+(1024*1024))+((post_count)*sizeof(POST))),0);
	}
	int current_address = ftell(fp);
	fwrite(post,sizeof(POST),1,fp);
	fflush(fp);
	fseek(fp,current_address,0);
	free(post);
	/*post = (POST*)malloc(sizeof(POST));
	fread(post, sizeof(POST),1,fp);
	printf("\nPOST DATA IS: %s\n",post->post_text);
	free(post);*/
	free(post_buffer);
	display_all_posts_by_user(fp,user_id);
}

void add_friends(FILE* fp,int count, int user_id)
{
	struct USERS* users=(struct USERS*)malloc(sizeof(struct USERS));
	fseek(fp,sizeof(int),0);
	int u_id=0,temp=0;
	printf("LIST OF USERS\n");
	if(display_users(fp,count)==0)
	{
		printf("YOU ARE THE ONLY USER IN FACEBOOK.\n");
		return;
	}
	printf("ENTER THE USER ID OF THE PERSON.");
	scanf("%d",&u_id);
	if(u_id == user_id)
	{
		return;
	}
	display_users_friendslist(fp,count,u_id,user_id);
}

void sign_in(FILE* fp,int count)
{
	system("cls");
	char user_name[40],passwd[40];
	int temp=0,choice=0,status=0;
	fseek(fp,sizeof(int),0);
	printf("ENTER USER NAME:  ");
	fflush(stdin);
	gets(user_name);
	printf("ENTER PASSWORD:  ");
	fflush(stdin);
	gets(passwd);
	USERS* users=(USERS*)malloc(sizeof(struct USERS));
	while(temp<=count)
	{
		fread(users,sizeof(USERS),1,fp);
		if(!((strcmp(user_name,users->user_name)==0) && (strcmp(passwd,users->passwd)==0)))
		{
			temp++;
			continue;
		}
		else 
		{
			status++;
			break;
		}
	}
	if(status == 1)
	{
			printf("LOGIN SUCCESFULL.\n");
			while(1)
			{	printf("TO ADD FRIENDS PRESS 1\nTO VIEW POSTS PRESS 2\nTO LOGOUT PRESS 3\nTO VIEW POST BY FRIENDS PRESS 4\n");
				printf("ENTER YOUR CHOICE:  ");
				scanf("%d",&choice);
				system("cls");
				if(choice==1)
				{
					add_friends(fp,count,users->user_id);
				}
				if(choice==2)
				{
					add_posts(fp,users->user_id);
				}
				if(choice==3)
				{
					break;
				}
				if(choice == 4)
				{
					show_posts_by_friends(fp,count,users->user_id);
				}
			}
	}
	else if(status == 0)
	{
		printf("INVALID CREDENTIALS.");
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int choice=0,count=0;
	FILE*fp;
	if(_access("D:\\MISSION R&D\\C ONLINE COURSE\\PROJECT FACEBOOK\\PROJECT FACEBOOK\\FB_DRIVE.txt",0)==-1)
	{
		count=0;
		fp=fopen("D:\\MISSION R&D\\C ONLINE COURSE\\PROJECT FACEBOOK\\PROJECT FACEBOOK\\FB_DRIVE.txt","wb+");
		create_hard_drive(fp);
		fseek(fp,0,SEEK_SET);
		fwrite(&count,sizeof(int),1,fp);
	}
	else 
		fp=fopen("D:\\MISSION R&D\\C ONLINE COURSE\\PROJECT FACEBOOK\\PROJECT FACEBOOK\\FB_DRIVE.txt","rb+");
	fseek(fp,0,0);
	fread(&count,sizeof(int),1,fp);
	printf("NO OF USERS: %d\n",count);
	printf("PRESS 1 TO SIGNUP.\n PRESS 2 TO LOGIN.");
	printf("\nENTER YOUR CHOICE:  ");
	scanf("%d",&choice);
	while(1)
	{
		system("cls");
		if(choice == 1)
		{
				sign_up(fp,count);
				count++;
		}
		if(choice==2)
		{
			sign_in(fp,count);
		}
		if(choice ==3)
		{
			break;
		}
		system("cls");
		printf("NO OF USERS: %d\n",count);
		printf("PRESS 1 TO SIGNUP.\n PRESS 2 TO LOGIN.\nPRESS 3 TO LOGOUT.");
		printf("\nENTER YOUR CHOICE:  ");
		fflush(stdin);
		scanf("%d",&choice);
	}
	printf("%d ",count);
	fseek(fp,0,0);
	fwrite(&count,sizeof(count),1,fp);
	fclose(fp);
	return 0;
}