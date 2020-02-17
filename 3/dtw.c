#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "dtwfunc.h"

int main(int argc, char* argv[]){
	int limit;
	if( argc == 2) {
		limit = atoi(argv[1]);
	}else if(argc > 2){
		return 0;
	}else{
		limit = INT_MAX;
	}
	
	// Scanf Train Series
	int i,j;
	int trainingSet_count,trainingSet_length;
	scanf("%d",&trainingSet_count); 
	scanf("%d",&trainingSet_length); 
	
	double **timeseries_Train = (double**)malloc(sizeof(double*)*trainingSet_count);
	int timeseries_TrainType[trainingSet_count];
	for(i=0; i<trainingSet_count; i++){
		timeseries_Train[i] = (double*) malloc(sizeof(double)*trainingSet_length);
		scanf("%d", &timeseries_TrainType[i]);
		for(j=0; j<trainingSet_length; j++){
			scanf("%lf" , &timeseries_Train[i][j]);
		}
	}
	// Scanf Test Series
	int testSet_count,testSet_length;
	
	scanf("%d",&testSet_count); 
	scanf("%d",&testSet_length); 
	double **timeseries_Test = (double**)malloc(sizeof(double*)*testSet_count);
	int timeseries_TestType[testSet_count];
	for(i=0; i<testSet_count; i++){
		timeseries_Test[i] = (double*)malloc(sizeof(double)*testSet_length);
		scanf("%d", &timeseries_TestType[i]);
		for(j=0; j<testSet_length; j++){
			scanf("%lf" , &timeseries_Test[i][j]);
		}	
	} 
	
	// Check for an error in the lengths of train/test series
	if(testSet_length!=trainingSet_length){
		printf("The lengths of both the training set and the test set are supposed to be the same.\n");
		return 0;
	}
	//Setting limit
	
	#ifdef REC
		for(i=0; i<testSet_count; i++)
			for(j=0 ; j<trainingSet_count; j++){
				int sum=0;
				printf("Distance of time series is =%lf\n" ,dtwrec(trainingSet_length, testSet_length, timeseries_Test[i],timeseries_Train[j],sum,limit) );
			}
		
	#else
		int errorsmade=0;
		clock_t c0, c1;
		double t;
		c0 = clock(); //Start clock
		
		if(limit >= testSet_length)
			limit = testSet_length-1;
		
		double min_dist = (1.0/0.0) , tempp;
		int min_pos=0;
	
		double *dtwArray = (double*)malloc(sizeof(double)*testSet_length);
		for(i=0;i<testSet_length;i++)
			dtwArray[i] = INT_MAX;
		
		//Starts the process of finding to each test timeserie its closest train timeserie
		for(i=0; i<testSet_count; i++){
			for(j=0 ; j<trainingSet_count; j++){
				
				tempp = dtwdp(trainingSet_length, timeseries_Test[i],timeseries_Train[j], limit , dtwArray);
				if(tempp <= min_dist){
					min_dist = tempp;
					min_pos = j;
				}
			}
			if(timeseries_TestType[i]!=timeseries_TrainType[min_pos]) 
				errorsmade++;
			printf("Series %d (class %d) is nearest (distance %lf) to series %d (class %d)\n" , i+1 , timeseries_TestType[i], min_dist  , min_pos+1 , timeseries_TrainType[min_pos] );
			min_dist = (1.0/0.0);
		}
		// Error Rate and CPU time print
		c1 = clock();
		t = (c1-c0)/ (double)CLOCKS_PER_SEC;
		double errorratio=0;
		errorratio = (double)errorsmade / (double)testSet_count;
		fprintf(stderr, "Error rate: %1.3lf\n" ,errorratio);
		fprintf(stderr,"CPU time = %lf\n", t);
	#endif
	
}
