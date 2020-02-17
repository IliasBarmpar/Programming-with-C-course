#include <stdio.h>
#include <math.h>
int main(void){
	int ch, curr_quot, end_flag=0, conszero_flag=0 ;
	int i, x, j, k; /* no specific names assigned since most of them are for for()'s */
	unsigned int input=0;
	
	// Checking for bad start
	for(i=1;i<=2;i++){
		ch=getchar();
		if(i==1&&ch!='<'){
			fprintf(stderr,"Bad start!\n");
			return 0;
		}else if(i==2&&ch!='~'){
			fprintf(stderr,"Bad start\n");
			return 0;
		}
	}
	
	// Reading till EOF
	while(ch != EOF){
		
		// Getchar for the first 5 bytes
		for(i=4; i>=0 ; i--){
			// Add a correct character
			ch= getchar();
			while(ch==' '||ch=='\t'||ch=='\n'){
				ch=getchar();
			}
			input += (ch-33)*pow(85,i);
			
			// Bad input character / Approaching end of file / Consecutive zeroes
			if(ch>=118){
				if(ch=='z'){ /* Bad input  or consecutive zeroes*/
					if(i!=4){
						fprintf(stderr, "Bad input character\n" , i);
						return 0;	
					}else{ 
						conszero_flag=1;
						break;
					}
					
				// Approaching end of file
				}else if(ch=='~'){
					ch=getchar();
					if(ch!='>'){
						fprintf(stderr,"Bad end\n");
						return 0;
					}
					
					ch=getchar(); /* Look for EOF after > */
					while(ch==' '||ch=='\t'||ch=='\n'){
						ch=getchar();
					}
					if(ch!=EOF){
						fprintf(stderr,"Unnecessary input\n");
						return 0;
					}
					end_flag=1;
				}else{ 
					fprintf(stderr, "Bad input character\n");
					return 0;
				}
			}
			if(ch==EOF){ /* Found EOF */
				if(end_flag==0){ /* EOF without proper ending */
					fprintf(stderr,"Bad end\n");
					return 0;
				}
				if(i==4) /* In case everything before EOF has been printed end the program*/
					return 0; 
				for(x=i; x>=0; x--) /* Or add the necessary 'u' 's */
					input += 84*pow(85,x);
				break;
			}
		}
		
		// Printer
		if(conszero_flag==1){
			for(j=3; j>=0; j--)
				putchar(0);
		}else{
			for(j=3; j>=(1+i); j--){
				k= pow(256,j);
				curr_quot = (input - input % k)/k;
				putchar(curr_quot);
				input=input%k;
			}
		}
		// Reset
		input = 0;
		conszero_flag=0;
	}
	if(ch==EOF&&end_flag==0)
		fprintf(stderr,"Bad end\n");
}
