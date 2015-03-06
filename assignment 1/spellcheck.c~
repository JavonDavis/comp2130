#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search(char *list[],char word[])
{	
	int i;
	for(i=0;i<45427;i++)
	{
		if(strcmp(list[i],word)==0)
			return 1;
	}
	return 0;
}

char* findReplacement(char *list[],char word[])
{
	int n,i,numSugg =0;
	char *suggestions[10];
	char *answer;
	
 	n = sizeof(word)-1;
	while(n>0)
	{
		char repl[n];
		for(i=0;i<n;i++)
		{
			repl[i] = word[i];
		}
		repl[n] = '\0';
		
		for(i=0;i<45427;i++)
		{
			if(numSugg==10)
				break;
			if(strstr(list[i],repl)!=NULL)
			{
				suggestions[numSugg] = malloc(strlen(list[i])+1);
				printf("%s\n",list[i]);
				strcpy(suggestions[numSugg],list[i]);
				printf("%s\n",suggestions[numSugg]);
				numSugg++;
				
			}
			
		}
		
		n--;
	}
	int key;
	printf("The word %s is not found in the dictionary\n",word);
	for(i=0;i<numSugg;i++)
	{
		printf("%d - %s\n",i+1,suggestions[numSugg]);
	}
	scanf("%d",&key);
	return answer;
	
}

int main(int argc, char *argv[])
{
	char *words[45427];
	char text[80];
	FILE *fpt,*fpt2;
	int i =0;
	
	fpt = fopen("linux.words","r");
	while(fscanf(fpt,"%s",text)!=EOF)
	{
		words[i] = malloc(strlen(text)+1);	
		strcpy(words[i],text);
		i++;
	}
	
	int result = search(words,"apple");

	printf("apple found:%d\n",result);

	fpt = fopen(argv[1],"r");
	fpt2 = fopen(argv[2],"w");

	while(fscanf(fpt,"%s",text)!=EOF)
	{
		if(search(words,text))
		{
			fprintf(fpt2,"%s",text);
		}
		else
		{
			findReplacement(words,text);
		}
	}
}
