#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binary_search(char *list[],char value[],int first,int last)
{	
	
	int mid = (int) ((first+last)/2);
	if(first>last)
		return 0;
	else if(strcmp(value,list[mid])==0)
		return 1;
	else if(strcmp(value,list[mid])>0)
		return binary_search(list,value,mid+1,last);
	else if(strcmp(value,list[mid])<0)
		return binary_search(list,value,first,mid-1);	
}

int main(int argc, char *argv[])
{
	char *words[45427];
	char text[80];
	FILE *fpt;
	int i =0;
	
	fpt = fopen("linux.words","r");
	while(fscanf(fpt,"%s",text)!=EOF)
	{
		words[i] = malloc(strlen(text)+1);	
		strcpy(words[i],text);
		i++;
	}
	
	int result = binary_search(words,"Aarhus",0,45427);

	printf("Aarhus found:%d\n",result);

	fpt = fopen(argv[1],"r");

	while(fscanf("",""))
	{
		
	}
}
