
#include "dtwfunc.h"

//TODO na min exw tslenghtA kai B
double dtwdp(int timeSeriesSize, double *timeserie_A, double *timeserie_B, int limit , double* dtwArray){
	int i,j, k, max_j;
	double a,b,c,min,diagonal;
	
	for(k=0;k<timeSeriesSize;k++)
		dtwArray[k] = INT_MAX;
			
	// First Row		
	dtwArray[0] = ( (timeserie_A[0]-timeserie_B[0]) * (timeserie_A[0]-timeserie_B[0]) );
	for(j=1; j<=limit; j++)
		dtwArray[j] = ( (timeserie_A[0]-timeserie_B[j]) * (timeserie_A[0]-timeserie_B[j]) ) + dtwArray[j-1];
	
	// All other rows 
	for(i=1; i<timeSeriesSize; i++){
		//set starting point for j
		j=i-limit;
		if(j<=0){
			j=0;
		}else{
			diagonal = dtwArray[j-1];	
			dtwArray[j-1] = INT_MAX;
		}
		//set ending point for j
		max_j=i+limit;
		if(max_j>=timeSeriesSize)
			max_j = timeSeriesSize-1;
		
		for(; j<=max_j;j++){
			if(j==0){
				diagonal = dtwArray[j];
				dtwArray[j]= ( (timeserie_A[i]-timeserie_B[0]) * (timeserie_A[i]-timeserie_B[0]) ) + diagonal;
			}else{
				a = dtwArray[j];
				b = diagonal;
				c = dtwArray[j-1];
				min = a;
				if(min>b)
					min = b;
				if(min>c)
					min = c;
					
				diagonal = a;
				dtwArray[j] = ( (timeserie_A[i]-timeserie_B[j]) *  (timeserie_A[i]-timeserie_B[j]) ) + min;
			}
		}
	}
	return dtwArray[timeSeriesSize-1];
}

double dtwrec(int tslength_A, int tslength_B, double *timeserie_A, double *timeserie_B , int s, int z){
	double a, b, c , min;
	int check2=z, check;
	int sum;
	sum = s;
	check = abs(tslength_A-tslength_B);
	
	//printf("We are in i=%d and j=%d\n", tslength_A, tslength_B);
	if((check == check2)&&tslength_A!=1&&tslength_B!=1){
		if(tslength_A==tslength_B){
			a = dtwrec(tslength_A-1, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
			sum+= ( ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) * ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) ) +a;
		}else if(tslength_A>tslength_B){
			a = dtwrec(tslength_A-1, tslength_B, timeserie_A, timeserie_B , sum, check2);
			b = dtwrec(tslength_A-1, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
			if(a<b)
				min = a;
			else
				min = b;	
			sum+= ( ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) * ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) ) +min;
		}else if(tslength_A<tslength_B){
			a = dtwrec(tslength_A, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
			b = dtwrec(tslength_A-1, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
			if(a<b)
				min = a;
			else
				min = b;	
			sum+= ( ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) * ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) ) +min;
		}
		return sum;
	}
	if(tslength_A == 1 && tslength_B==1){
		sum += ( *(timeserie_A+0) - *(timeserie_B+0) ) * ( *(timeserie_A+0) - *(timeserie_B+0) );
		return sum;
	}else if(tslength_A == 1){
		a = dtwrec(1, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
		sum +=( ( *(timeserie_A+0) - *(timeserie_B+ (tslength_B-1))) * ( *(timeserie_A+0) - *(timeserie_B+ (tslength_B-1))) )+a;
		return sum;
	}else if(tslength_B ==1){
		a = dtwrec(tslength_A-1, 1, timeserie_A, timeserie_B , sum, check2);
		sum +=( ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B + 0)) * ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B + 0)) ) +a;
		return sum;
	}else{
		a = dtwrec(tslength_A-1, tslength_B, timeserie_A, timeserie_B , sum, check2);
		b = dtwrec(tslength_A, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
		c = dtwrec(tslength_A-1, tslength_B-1, timeserie_A, timeserie_B , sum, check2);
		if(a<b && a<c){
			min = a;
		}else if(b<c && b<a){
			min = b;
		}else{
			min =c;
		}
		sum += ( ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) * ( *(timeserie_A+(tslength_A-1)) - *(timeserie_B+ (tslength_B-1))) ) +min;
		return sum;
	}
}

