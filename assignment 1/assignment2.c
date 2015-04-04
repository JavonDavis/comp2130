/*********************************************
/* Name: Caryl Ford (620047701)              *
/* Course: Systems Programming               *                     *
/*********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100000

FILE *actualOutput;

/*Function to remove white spaces
* Help Source: stackoverflow
*/
char* removeIt(char* input)
{
		int  ip_ind = 1;
  char *ptr;

  if(*input)
    return input;

  /* In place removal of duplicate spaces*/
  while(*(input + ip_ind))
  {
    if ( (*(input + ip_ind) == *(input + ip_ind - 1)) && (*(input + ip_ind)==' ') )
    {
        ptr = input + ip_ind;
        //Functionality for removal of spaces.
        do{
           *(ptr-1) = *ptr;
        }while(*ptr++ != '\0');


    }
    else //Inc only if deletion is not done.
    ip_ind++;
  }

 /* After above step add end of string*/
  *(input + ip_ind) = '\0';

 return input;
	}

/*Find a substring ofn length of a word*/
char *subString(char *someString, int n) 
{
   char *newPossibility = malloc(sizeof(char)*n+1);
   strncpy(newPossibility, someString, n);
   newPossibility[n] = '\0';
   return newPossibility;
}


/*Based on substring, compare it to words in dictionary
* If match, store in dictionary
*/
void getWords(char* word, char *wordlist[], int dictlent)
{
	char suggestion[MAX];//Stores possible words
	int i, option;
	int index = 0;

	
		int n = (strlen(word)) - 1;

	  while(n > 0 && index<=10)
		{	
			for (i = 0; i < dictlent; ++i)
	{
			
			//strcpy(suggestions[,(subString( word, n)));
			
			/*if(strcmp(subString( word, n), wordlist[i])  ==0)  //logic was incorrect you were matching a substring to a word in the dictionary so you wouldn't really get more than one suggestion*/
			if(strstr(wordlist[i],subString(word,n))!=NULL)
			{
				//strncpy(suggestion,word, n);
				//suggestion[n] ='\0';
				printf("Suggestion #%d: %s\n",index+1, wordlist[i]); 
				//Menu
				printf("Enter [1] to pick this suggestion \n");
				printf("Enter [2] to keep original word\n");
				printf("Enter [0] to get a next suggestion\n");
				scanf("%d", &option);
				switch (option)
				{
					case 2: fprintf(actualOutput, "%s\n", word); //keep original
					case 1: fprintf(actualOutput, "%s\n", wordlist[i]); //Writes suggestion to file
					case 0: index++;
				}
				
			}

			
	
		}
		printf("%s\n",subString(word,n));
		printf("%d,%d\n",n,index);
		n --;

	}
	fclose(actualOutput);//Closes outputfile
}


int main(int argc, char *argv[])
{

	FILE *input; //file pointer for input text file
	FILE *output;//file pointer for output text file
	FILE *words; //library for words

	char* wordStore[MAX]; //stores the words from linux.words file
	char* inputStore[MAX]; //stores the words from input file given
	char buffer[100];
	char** suggestions; //Stores word suggestions
	int n,word_count=0,in_word_count=0,count,count2,matches=1;

	if (argc!=3)//Print error if incorrect arguments given
	{
		printf("Make sure to enter an input and output file\n");
		perror(argv[1]);
	}


	words =fopen("linux.words","r");//Opens dictionary
	/*Gets words line by line and stores it in it's desginated array
	**Stores the length of each word*/
	while(fgets(buffer,sizeof buffer, words) != NULL) {
    wordStore[word_count] = malloc(strlen(buffer) + 1);
    strcpy(wordStore[word_count], buffer);
		int num = strlen(wordStore[word_count]);

		if( isalpha(wordStore[word_count][num -1]) == 0) 
				wordStore[word_count][num -1] = '\0';
    word_count++;
	}
	fclose(words);

	input =fopen(argv[1],"r");  //open a file a read the input file

	if(input==NULL) //If empty
		{
				printf("No file");
		}



	/*Gets words line by line and stores it in it's desginated array
	**Stores the length of each word*/
	while(fgets(buffer,sizeof buffer, input) != NULL)
	{
	    inputStore[in_word_count] = malloc(strlen(buffer) + 1);
	    strcpy(inputStore[in_word_count], buffer);
			int num = strlen(inputStore[in_word_count]);

			int n =  strlen(inputStore[in_word_count]);	
			if( isalpha(inputStore[in_word_count][n -1]) == 0) 
				inputStore[in_word_count][n -1] = '\0';

	    in_word_count++;
	}

	for (count=0;count<word_count;count++)
	{
		printf("Words to look for:%s\n", inputStore[count]);//Prints words in input file
		matches = 1; //sets match to false initially

		/*for every word in the dictionary*/
		for (count2=0; count2<word_count;count2++)
		{
			
			if(strcmp(inputStore[count], wordStore[count2])==0) //If words match, match=0
			{
				matches=0;
				count2 = word_count;
			}

		}

		
		output= fopen(argv[2],"w"); //output from command line which is then assigned to a global variable
		actualOutput=output;

		if(matches == 1) 
			{
			
					printf("Words not in dictionary: %s\n", inputStore[count]);//Display words currently not in dictionary
		      getWords(inputStore[count], wordStore, word_count ); //Gets suggestions
			}


	}
	
	fclose(input);
	return 0;
}




