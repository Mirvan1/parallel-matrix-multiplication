#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include <pthread.h>


int main(int argc, char* argv[]){
struct timeval start,stop,startTotal,stopTotal;
gettimeofday(&startTotal,NULL);
int **a,**b,**mul;
int r,c;
int j,k;
char read_c[100];
FILE *a_read;
if((a_read=fopen(argv[1],"r"))==NULL){
printf("%s","error,can not open a.txt file");
}
fscanf(a_read,"%[^\n]",read_c);
fclose(a_read);
FILE *b_read;
if((b_read=fopen(argv[2],"r"))==NULL){
printf("%s","error,can not open b.txt file");
}
fscanf(b_read,"%[^\n]",read_c);
fclose(b_read);


r=atoi(read_c);
int num_threads=atoi(argv[3]);
FILE *result_p;
char result_name[80]="";
strcat(result_name,"resultparallel");
strcat(result_name,read_c);
strcat(result_name,".txt");
result_p=fopen(result_name,"w");

a=(int**)malloc(sizeof(int *)*r);
b=(int**)malloc(sizeof(int *)*r);
mul=(int**)malloc(sizeof(int *)*r);

gettimeofday(&start,NULL);
for(int i=0;i<r;i++)
   a[i]=(int*)malloc(sizeof(int)*r);
for(int i=0;i<r;i++)
   b[i]=(int*)malloc(sizeof(int)*r);
for(int i=0;i<r;i++)
   mul[i]=(int*)malloc(sizeof(int)*r);

for(int i=0;i<r;i++){
   for(int j=0;j<r;j++){
      a[i][j]=i+j;
	
 }
}

for(int i=0;i<r;i++){
   for(int j=0;j<r;j++){
      b[i][j]=i+j;

 }

}



gettimeofday(&stop,NULL);
printf("Allocation time: %3.5f seconds\n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);
gettimeofday(&start,NULL);

int bigA[r];
int bigB[r];

	#pragma omp parellel
	{
	for(int m=0;m<r;m++){
	   for(int n=0;n<r;n++){
		bigA[m+n]=a[m][n];
		bigB[n+m]=b[m][n];
		
		
	}

     }
omp_set_num_threads(num_threads);

}
int z,x,y,iOff,jOff,tot;
#pragma omp paralel shared(mul) shared(iOff,jOff,z,x,y,tot)  num_threads(num_threads)
{
	//#pragma omp for schedule(static)
	for(z=0;z<r;z++){
 	iOff=z*r;
   	for(y=0;y<r;y++){
		jOff=y*r;
      		
		int pa=bigA[y+z];
		for(x=0;x<r;x++){
          	mul[z][x]+=pa*bigB[y+x];	
	}
      }
    }

//printf(" %d",omp_get_max_threads());
}

gettimeofday(&stop,NULL);

printf("Cache and decomposition method time: %3.5f seconds\n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);

gettimeofday(&start,NULL);
for(int v=0;v<10;v++){
	for(int b=0;b<10;b++){
	
           	fprintf(result_p,"%4d",mul[v][b]);
	}

}
fprintf(result_p,"\n");
fclose(result_p);
gettimeofday(&stop,NULL);

printf("Load result parallel file: %3.5f seconds \n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);


gettimeofday(&stopTotal,NULL);
printf("Total time to do job: %3.5f seconds \n",((stopTotal.tv_sec-startTotal.tv_sec)*1000000+stopTotal.tv_usec-startTotal.tv_usec)/1000000.0);
return(0);
}
