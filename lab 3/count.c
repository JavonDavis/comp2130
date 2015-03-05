#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int counter3=0,counter4=0,counter5=0,counter6=0,counter7=0,counter8=0,counter9=0,counter10=0,counter11=0;
	int counter12=0,counter13=0,counter14=0,counter15=0;

	if ( argc != 2 ) 
    {
        
        printf( "Incorrect amount of arguements");
    }
    else 
    {
        FILE *file = fopen( argv[1], "r" );

        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
            char text[80];

			int word_count = 0 ;

			while( fscanf( file, "%s", text) > 0 )
			{
				int len = strlen(text);
				switch(len)
				{
					case 3:
						counter3++;
						break;
					case 4:
						counter4++;
						break;
					case 5:
						counter5++;
						break;
					case 6:
						counter6++;
						break;
					case 7:
						counter7++;
						break;
					case 8:
						counter8++;
						break;
					case 9:
						counter9++;
						break;
					case 10:
						counter10++;
						break;
					case 11:
						counter11++;
						break;
					case 12:
						counter12++;
						break;
					case 13:
						counter13++;
						break;
					case 14:
						counter14++;
						break;
					case 15:
						counter15++;
						break;

				}
			    word_count++ ;
			}

			printf("Total number of words:%d\n",word_count);
			printf("words of length 3:%d\n",counter3);
			printf("words of length 4:%d\n",counter4);
			printf("words of length 5:%d\n",counter5);
			printf("words of length 6:%d\n",counter6);
			printf("words of length 7:%d\n",counter7);
			printf("words of length 8:%d\n",counter8);
			printf("words of length 9:%d\n",counter9);
			printf("words of length 10:%d\n",counter10);
			printf("words of length 11:%d\n",counter11);
			printf("words of length 12:%d\n",counter12);
			printf("words of length 13:%d\n",counter13);
			printf("words of length 14:%d\n",counter14);
			printf("words of length 15:%d\n",counter15);

        }
        fclose(file);
    }
}