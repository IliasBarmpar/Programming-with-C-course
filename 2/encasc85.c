#include <stdio.h>
#include <math.h>

int main(void){
	int i , y , j , k; /* no specific names assigned since most of them are for for()'s */
	int ch, linechange=1 , curr_quot;
	unsigned int input=0;
	
	// Start of printed file
	putchar('<'); putchar('~'); putchar('\n');
	
	// Reading till EOF
	while (ch != EOF){
		
		//	Getchar for the first 4 bytes
		for(i=3; i>=0 ; i--){																																				
			ch= getchar();
			if(ch==EOF)
				break; /* breaks keeping the i */
				
			//	transform them into integer
			input += ch*pow(256,i);
		}
		
		//	if there are 4 consecutive zeroes translate them to z
		if(input==0){
			putchar('z');
			linechange++;	
			if(linechange==51){
				printf("\n");
				linechange=1;
			}
			continue;
		}
		
		//	transform input into a 5digit number of the 85system
		for(j=4; j>=1+i; j--){ /* using the i once break takes place makes sure the printer prints only the necessary characters */
			// This process takes the input, finds and removes its remainder and then divides to find the quotient we need (curr_quot)
			k= pow(85,j);
			curr_quot = (input - input % k)/k;
			// printer
			putchar(curr_quot+33);
			linechange++;
			if(linechange==51){
				printf("\n");
				linechange=1;
			}
			// preparing the next printed character
			input = input % k;
		}
		// Reset
		input = 0;
	}
	// End of printed file
	putchar('~'); putchar('>'); putchar('\n');
}
