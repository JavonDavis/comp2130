//returns 1 if the String is an integer 0 otherwise
// does not work for numbers >= 10*10^14
int isInteger(char word[])
{
	int i;
	for(i=0;i<strlen(word);i++)
	{
		
		char c = word[i];
		if(!isdigit(c))
		{
			//check for negative number
			if(i==0)	
			{
				if(c == '-')
					continue;
			}
			else
				return 0;
		}
	}
	return 1;
}

