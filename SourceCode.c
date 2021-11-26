
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 2147483647

typedef struct 
{
	int indice;
	int peso;
	
} nodo;

int cmpfunc (const void * c, const void * d) {
   return ( *(int*)c - *(int*)d );}


void MaxHeapify(nodo* maxmucchio,int k,int i){
	
	int l = (2*i+1);
	int r = (2*i+2);
	int big=i;
	if(l<k&&maxmucchio[big].peso<maxmucchio[l].peso) big=l;
	if(r<k&&maxmucchio[big].peso<maxmucchio[r].peso) big=r;
	if(big!=i){
		
		nodo temp;
		temp.peso=maxmucchio[i].peso;
		temp.indice=maxmucchio[i].indice;
		maxmucchio[i].peso=maxmucchio[big].peso;
		maxmucchio[i].indice=maxmucchio[big].indice;
		maxmucchio[big].peso=temp.peso;
		maxmucchio[big].indice=temp.indice;
		MaxHeapify(maxmucchio,k,big);
	
	}
	return;

}
void Inserisci(int indice,int peso,nodo* maxmucchio,int k){
	if(peso<maxmucchio[0].peso){
		
		maxmucchio[0].indice=indice;
		maxmucchio[0].peso=peso;
		MaxHeapify(maxmucchio,k,0);
	
	}
    return;

}
void StampaMatrice(int* matrix, int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",*(matrix+(j+n*i)));
		}
		printf("\n");

	}}

int* CancellaAutoanelli(int* matrix,int n){
	int k,l;
	for(l=0;l<n;l++){
		k=l+n*l;
		*(matrix+k)=0;
	}
	return matrix;

}

int* CreaMatrice(int n){
	//printf("crea");
	int offset;
	int dim=n*n;
	int* matrix=(int*)malloc(dim*sizeof(int)); //offset = i + n * j;
    for(offset=0;offset<dim;offset++){  
    	//printf("scan");
    	if(!scanf("%d,",&matrix[offset])) printf("error while scanning");
        if(matrix[offset]==0) matrix[offset]=INF;}

    matrix=CancellaAutoanelli(matrix,n); 
    //StampaMatrice(matrix,n); 
    
    return matrix;
}

int atoi2( const char * str )
{
    int k = 0;
    while( *str != '\n' && *str != ',' ) {
        k = k*10 + (*str++ - '0');
    }
    return k;
}

char* getnum(char* num){
	
	char c;
	int i=0;
	do{
		c=getchar_unlocked();
		num[i++]=c;


	}while(c!=','&&c!='\n');

	return num;

}


int* CreaMatriceFast(int n){
	//printf("crea");
	int i,j=0;
	char* num=(char*)malloc(15*sizeof(char));
	int* matrix=(int*)malloc(n*n*sizeof(int)); //offset = i + n * j;
    for(i=0;i<n;i++){ 
    		
    		
    		
    			//printf("ff%s",line);
    			for(j=0;j<n;j++){
    				num=getnum(num);
    				matrix[i*n+j]=atoi2(num);
    				//printf("s%ds ",matrix[i*n+j]);
    				
    				if(matrix[i*n+j]==0) matrix[i*n+j]=INF;
    				
    				
    				}}
    free(num);
    matrix=CancellaAutoanelli(matrix,n); 
    //StampaMatrice(matrix,n); 
    return matrix;}


int isEqual(char str1[], char str2[]){
	
	int i;
	for (i=0;str1[i]!='\0';i++){
		if(str1[i]!=str2[i]){
			return 0;}

	}
	return 1;
}
int Minimo(int* dist,int* giaVis,int n){
	int i,index=0,min=INF;
	for(i=0;i<n;i++){
		if(!giaVis[i]&&dist[i]<=min){
			min=dist[i];
			index=i;
		}}
	return index;
	
}


int CalcoloPeso(int* matrix, int n){
	int k,l,val,index;
	int* dist = (int*)malloc(n*sizeof(int));
	int* giaVis = (int*)malloc(n*sizeof(int));

	for(k=1;k<n;k++){
		dist[k]=INF;
		giaVis[k]=0;
	}
	dist[0]=0;
	giaVis[0]=0;

	for(k=0;k<n;k++){
		index=Minimo(dist,giaVis,n);
		giaVis[index]=1;
		for(l=0;l<n;l++){
			val=dist[index]+matrix[l+n*index];
			//printf("%d",val);
			if(!giaVis[l] && val<dist[l] && val>0) dist[l]=val;
		}
		}

		
	val=0;
    for(k=0;k<n;k++){
    	//printf("%d\n",dist[k]);
    	if(dist[k]!=INF){
    		val+=dist[k];
    		
    	}
    }
	free(dist);
	free(giaVis);
    return val;

	}



void AggiungiGrafo(int n,int indice,nodo* mucchio,int k){
	//printf("Inserisci i valori della matrice:\n");  

	int* matrix=CreaMatriceFast(n);
	//printf("(%d ",k);
	int peso = CalcoloPeso(matrix,n);
	                                      
	free(matrix);
   
	Inserisci(indice,peso,mucchio,k);

	return;
}


void TopKOrdered(int k,nodo* maxmucchio){
	int i,count=0;
	for(i=0;i<k;i++){
		if(maxmucchio[i].indice>=0) count++;}
    
    int* newvector = (int*)malloc(count*sizeof(int));
    count=0;
	for(i=0;i<k;i++){
		if(maxmucchio[i].indice>=0){
			newvector[count]=maxmucchio[i].indice;
			count++;
			//printf("%d ",maxmucchio[i].indice);
		}}
	qsort(newvector,count,sizeof(int), cmpfunc);
    for(i=0;i<count-1;i++){
    	printf("%d",newvector[i]);
    	printf(" ");
    }
    if(count!=0) printf("%d",newvector[count-1]);
    free(newvector);
	
	printf("\n");
	return;

}

void TopK(int k,nodo* maxmucchio){
	int i,count=0;
	for(i=0;i<k;i++){
		if(maxmucchio[i].indice>=0) count++;
	}
	for(i=0;i<k;i++){
		if(maxmucchio[i].indice>=0){
			printf("%d",maxmucchio[i].indice);
			count--;
			if(count>0) printf(" ");
			
		}}
	printf("\n");
	return;

}



int main(){

	int n,k=0,i=0,indice=0;
	

	char* com =(char*)malloc(15*sizeof(char));
	char* buff = (char*)malloc(15*sizeof(char));
	int sent=1;
	//printf("inserisci dimensione e lunghezza lista:\n");
	if(!fgets(buff,15,stdin))printf("error while scanning1");
    //printf("as %s\n ",buff);
	n=atoi(buff);

	while(buff[i]!=','&&buff[i]!=' '){
		i++;
	}
	i++;
	//printf("%d",i);
	k=atoi(&buff[i]);


	nodo* mucchio = (nodo*)malloc(k*sizeof(nodo));


	//printf("s%d\n",n);
	//printf("s%d\n",k);

	for(i=0;i<k;i++){
		mucchio[i].indice=-1;
		mucchio[i].peso=INF;
		//printf("%d ",mucchio[i].peso);
	}
	
	while(sent){
		//printf("inserisci il comando:\n");
		strcpy(com,"Exit");
		if(!fgets(com,15,stdin)) sent=0;
		else if(isEqual("AggiungiGrafo",com)){
			//printf("AggiungiGrafo");
			AggiungiGrafo(n,indice,mucchio,k);
			indice++;
		}
		else if(isEqual("TopK",com)){
			TopK(k,mucchio);

		}
		else if(isEqual("Exit",com)){
			sent=0;

			
		}}
		
	free(mucchio);
	free(com);
	free(buff);

    
	return 0;}
		
	


