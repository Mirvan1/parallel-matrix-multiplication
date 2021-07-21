#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


int main(int argc, char* argv[]){
struct timeval start,stop,startTotal,stopTotal;
int **a,**b,**mul;
int r,c;
int i,j,k;
FILE *a_file;
gettimeofday(&startTotal,NULL);
r=atoi(argv[1]);
char str[80]="";
strcat(str,"a");
strcat(str,argv[1]);
strcat(str,".txt");
a_file=fopen(str,"w");


a=(int**)malloc(sizeof(int *)*r);
b=(int**)malloc(sizeof(int *)*r);
mul=(int**)malloc(sizeof(int *)*r);

gettimeofday(&start,NULL);
for(i=0;i<r;i++)
   a[i]=(int*)malloc(sizeof(int)*r);
for(i=0;i<r;i++)
   b[i]=(int*)malloc(sizeof(int)*r);
for(i=0;i<r;i++)
   mul[i]=(int*)malloc(sizeof(int)*r);

for(i=0;i<r;i++){
   for(j=0;j<r;j++){
      a[i][j]=(rand()%(r+1+0)-0);
 }
}
fprintf(a_file,"%4d",r);
fprintf(a_file,"\n");
fclose(a_file);
FILE *b_file;
char str2[800]="";
strcat(str2,"b");
strcat(str2,argv[1]);
strcat(str2,".txt");

b_file=fopen(str2,"w");

//if(b_file!=NULL){
//printf("createdB\n");
//}
for(i=0;i<r;i++){
   for(j=0;j<r;j++){
      b[i][j]=(rand()%(r+1+0)-0);
	
 }

}
fprintf(b_file,"%4d",r);
fprintf(b_file,"\n");
fclose(b_file);

gettimeofday(&stop,NULL);
printf("Allocation time: %3.5f seconds\n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);


gettimeofday(&start,NULL);
FILE *result_file;
char result[80]="";
strcat(result,"result");
strcat(result,argv[1]);
strcat(result,".txt");
result_file=fopen(result,"w");

for(i=0;i<r;i++){
 for(j=0;j<r;j++){
  mul[i][j]=0;
	for(k=0;k<r;k++){
        mul[i][j]+=a[i][k]*b[k][j];
		
}
}

}
gettimeofday(&stop,NULL);

printf("Normal method: %3.5f seconds \n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);



gettimeofday(&start,NULL);
for(i=0;i<r;i++){
	for(j=0;j<r;j++){
		fprintf(result_file,"%d",mul[i][j]);
	}
fprintf(result_file,"\n");
}
fclose(result_file);

gettimeofday(&stop,NULL);

printf("Loading result file: %3.5f seconds \n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);




gettimeofday(&start,NULL);

   for(i=0;i<r;i++){
for(k=0;k<r;k++){
	int e=a[i][k];     
	for(j=0;j<r;j++){
          mul[i][j]+=e*b[k][j];
}
 }
}

gettimeofday(&stop,NULL);
printf("Cache friendly method: %3.5f seconds \n",((stop.tv_sec-start.tv_sec)*1000000+stop.tv_usec-start.tv_usec)/1000000.0);


gettimeofday(&stopTotal,NULL);
printf("Total time to do job: %3.5f seconds \n",((stopTotal.tv_sec-startTotal.tv_sec)*1000000+stopTotal.tv_usec-startTotal.tv_usec)/1000000.0);
return(0);
}
