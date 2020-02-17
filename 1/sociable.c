#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define minNUM 10000000
#define minCYC 28

int main(void){
	int min=0;
	int cyc=1 ,j;
	int sum=1;
	int numb, pos_div;
	int sum_per=0, sum_ami=0 ,sum_rest=0;
	int curr_numb;

	for(numb=2 ; numb <= minNUM ; numb++){
		//Set/Reset-ing values which need to be reset for each new Number we examine.

		curr_numb=numb;
		cyc=1;
		min=numb;
		
		//The first thing we do is make sure 1) We haven't surpassed the number of allowed cycles and 2) only printing cycles
		// on the biggest number within the cycle.
		while(cyc<=minCYC && curr_numb <= numb){
			
			//Our first function finds the summary of divisors
			/*1 Start*/
			for(pos_div=2 ; pos_div*pos_div <= curr_numb ; pos_div++){
				if((curr_numb % pos_div)==0){
					sum += pos_div + curr_numb/pos_div;
				}
			}
			if( (pos_div*pos_div)==curr_numb ){
				sum -= pos_div;
			}
			/*1 End*/
			
			//Our second function checks if we have found a cycle (if the current sum we are searching is equal to the number we examine)
			if(sum==numb){
				printf("Cycle of length ");
				
				if( cyc==1){	//If Perfect
					sum_per++;
					printf("%d: %d %d\n", cyc , min , numb);				
				}else if( cyc>1){	//If not Perfect but sociable
					if(cyc==2) { //if amicable
						sum_ami++;
						printf("%d: %d %d %d\n" , cyc , min , numb , curr_numb);
					}
					else{
						sum_rest++;	
						printf("%d: %d" , cyc , min);
						// if cyc>2 it prints by finding for each sum the next one untill it has exhausted the cycle
						for(j=1 ; j<=cyc ; j++){
							sum=1;
							printf(" %d",curr_numb);
							for(pos_div=2 ; pos_div*pos_div <= curr_numb ; pos_div++){
								if((curr_numb % pos_div)==0)
									sum += pos_div + curr_numb/pos_div;
							}
							if( (pos_div*pos_div)==curr_numb ){
								sum -= pos_div;
							}	
							curr_numb=sum;
						}
						printf("\n");
					}
				}
			}else{
				//if we don't have a cycle yet
					curr_numb=sum;
					if( min>curr_numb )
						min=curr_numb;
					cyc++;
					sum=1;
			}
		}
	}
	printf("\n\nFound %d cycles including\n%d cycles with perfect numbers and\n%dcycles with amicable numbers\n" , sum_per+sum_ami+sum_rest , sum_per , sum_ami);
	return EXIT_SUCCESS;
}

