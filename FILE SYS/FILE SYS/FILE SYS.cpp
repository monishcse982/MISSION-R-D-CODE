
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

#define MyFile FILE

MyFile* MyCreateFile(char *iInput);
void MyWrite(MyFile*,char*, char buffer[], int bufferSize,int node);
void MyClose(MyFile *m);
int string_comp(char inp1[], char inp2[]);
void MyRead(MyFile *MyFp, char flname[], int buffersize, int node);
void MyList(MyFile *MyFp, int node);
void MyOpenFile(MyFile *MyFp, char *flname, int node);
void insert_data(MyFile *MyFp, char flname[], char buffer[], int bufferSize, int node);
void delete_file(MyFile *MyFp, char flname[], int node);

struct table
{
	char file_name[10];
	int index;
	 time_t t;
	int iSize;	
};

int main()
{ 
	int iCount = 1,i=0,bufsize=0,j=0;
	char iInput[10],iData[20];
	while (1)
	{
		printf("Enter your choice:\n");
		printf("1.create disk\n");
		printf("2.Create a file\n");
		printf("3.Write data into file\n");
		printf("4.Read the written file\n");
		printf("5.delete a file\n"); 
		printf("6.Print list of files available\n");
		scanf("%d", &i);
		MyFile *fp;
		fp = fopen("divFile", "rb+");
		switch (i)
		{
			case 1:
				fp = MyCreateFile("divFile");
				rewind(fp);
				for (i = 1; i < 2049; i++)
					fputc(48, fp);
				rewind(fp);
				break;
			case 2:
				printf("Enter the file name\n");
				scanf("%s",iInput);
				for (i = 0; iInput[i] != '\0'; i++)
					bufsize++;
				fseek(fp,1,SEEK_SET);
				for (i = 1; i < 2049; i++)
				{
					if (fgetc(fp) == 48)
						break;
				}
				rewind(fp);
				MyWrite(fp, iInput ,"ghj",9,i);
				fseek(fp, i, SEEK_SET);
				fputc(49,fp );
				rewind(fp);
				break;
			case 3:
				printf("Enter data to be written\n");
				scanf("%s",iData);
				insert_data(fp, iInput, iData, strlen(iData), iCount);
				break;
			case 4:
				printf("Enter filename\n");
				scanf("%s",iData);
				MyRead(fp, iData, strlen(iData),iCount);
				break;
			case 5:
				printf("Enter filename to be deleted\n");
				gets(iInput);
				delete_file(fp, iInput,iCount);
				iCount--;
				break;
			case 6:
				MyList(fp, iCount);
				break;
		}
		iCount++;
		bufsize = 0;
	}
	scanf("%d", &iCount);
	return 0;
}

void MyWrite(MyFile *MyFp,char *flname, char *buffer, int bufferSize,int node)
{ 
	rewind(MyFp);
	int i = 0;
	struct table *t = (struct table*)malloc(sizeof(struct table));
	struct table *v = (struct table*)malloc(sizeof(struct table));

	if (MyFp != NULL)
	{
		for (i = 0; flname[i] != '\0'; i++)
		{
			t->file_name[i] = flname[i];
		}
		t->file_name[i] = '\0';
		t->iSize = 4096;
		t->index = node;
		t->t = time(NULL);
		fseek(MyFp, ((node - 1)*sizeof(struct table)+2048), SEEK_SET);
		fwrite(t, sizeof(struct table), 1, MyFp);
		fseek(MyFp,((node-1)*sizeof(struct table)+2048),SEEK_SET);
		fread(v, sizeof(struct table), 1, MyFp);
		printf("%s %d\n", v->file_name,v->index);
	}
	fseek(MyFp, node, SEEK_SET);
	fputc(49, MyFp);
	rewind(MyFp);
}


void MyOpenFile(MyFile *MyFp,char *flname,int node)
{
	int k = 0;
	struct table *t = (struct table*)malloc(sizeof(struct table));
	while (k < node)
	{
		fseek(MyFp, k*sizeof(struct table), SEEK_SET);
		fread(t, sizeof(struct table), 1, MyFp);
		if (string_comp(t->file_name, flname) == 1)
		{
			fseek(MyFp, ((t->index) * 4096)+2048, SEEK_SET);
			char b[10];
			fread(b, sizeof(b), 1, MyFp);
			printf("Memory : %s\n", b);
		}
		k++;
	}
}

MyFile* MyCreateFile(char *iInput)
{
	MyFile *file1 = fopen(iInput, "wb+");
	int iSize = 8*1024*1024, i = 0;
	if (file1 != NULL)
	{
		printf("File created\n");
	}
	while (i < iSize)
	{
		putc(48,file1);
		i++;
	}
	i = ftell(file1);
	printf("size of the file created: %d\n", i);
	rewind(file1);
	for (iSize = 0; iSize < 2049; iSize++)
		fputc(48, file1);
	rewind(file1);
	return file1;
}

void MyClose(MyFile *m)
{
	fclose(m);
}


int string_comp(char inp1[], char inp2[])
{
	int i = 0;
	while ((inp1[i] != NULL) && (inp2[i] != NULL))
	{
		if (inp1[i] == inp2[i])
			i++;
		else
			break;
	}
	if (inp1[i] == NULL && inp2[i] == NULL)
		return 1;
	return 0;
}


void MyRead(MyFile *MyFp,char flname[], int buffersize,int node)
{
	rewind(MyFp);
	int k = 0;
	char buffer[10];
	struct table *t = (struct table*)malloc(sizeof(struct table));
	while (k<10)
	{
		fseek(MyFp, 2048,SEEK_SET);
		fread(t, sizeof(struct table), 1, MyFp);
		if (string_comp(t->file_name, flname) == 1)
		{
			fseek(MyFp, ((k + 1) * 4096)+2048, SEEK_SET);
			fread(buffer, sizeof(buffer), 1, MyFp);
			printf("buffer %s\n", buffer);
			break;
		}
		k++;
	}
}


void MyList(MyFile *MyFp,int node)
{
	int k = 0;
	struct table *t = (struct table*)malloc(sizeof(struct table));
	printf("List of files available:\n");
	while (k < node)
	{
		fseek(MyFp, (k*sizeof(struct table))+2048, SEEK_SET);
		fread(t, sizeof(struct table), 1, MyFp);
		printf("%s\n", t->file_name);
		k++;
	}
}

void insert_data(MyFile *MyFp,char flname[],char buffer[],int bufferSize,int node)
{
	rewind(MyFp);
	int k = 0;
	printf("k node %d %d\n", k, node);
	struct table *t = (struct table*)malloc(sizeof(struct table));
	while (k < node)
	{
		fseek(MyFp, (k*sizeof(struct table))+2048, SEEK_SET);
		fread(t, sizeof(struct table), 1, MyFp);
		if (string_comp(t->file_name, flname) == 1)
		{
			fseek(MyFp, ((k + 1) * 4096)+2048, SEEK_SET);
			int i = fwrite(buffer, bufferSize, 1, MyFp);
			printf("i==%d\n", i);
			char b[10] = "ad";
			fseek(MyFp, ((k + 1) * 4096)+2048, SEEK_SET);
			fread(b, bufferSize, 1, MyFp);
			b[bufferSize] = '\0';
			printf("%s", b);
		}
		k++;
	}
}

void delete_file(MyFile *MyFp, char flname[],int node)
{
	rewind(MyFp);
	int k = 0,r=0;
	printf("k node %d %d\n", k, node);
	struct table *t = (struct table*)malloc(sizeof(struct table));
	while (k<10)
	{
		fseek(MyFp, (k*sizeof(struct table)) + 2048, SEEK_SET);
		fread(t, sizeof(struct table), 1, MyFp);
		if (string_comp(t->file_name, flname) == 1)
		{
			fseek(MyFp, (k*sizeof(struct table)) + 2048, SEEK_SET);
			printf("entered");
			for (r = 0; r < sizeof(struct table); r++)
				fputc(48,MyFp);
			fseek(MyFp, ((k + 1) * 4096) + 2048, SEEK_SET);
			for (k = 0; k < 4096; k++)
				fputc(48, MyFp);
			fseek(MyFp, t->index, SEEK_SET);
			fputc(48, MyFp);
			rewind(MyFp);
			break;
		}
		k++;
	}
}