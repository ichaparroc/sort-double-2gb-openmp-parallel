#include<random>
#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<fstream>
#include <pthread.h>
//#include "omp.h"
//#include<math>

#define INFINITO 2.0

#define FILE "list.txt"

#define TAMANHO 120000000
//#define TAMANHO 2000000

using namespace std;

void *quick_sort_iterative(void *threadarg);

void quick_sort_iterative_pthread_2(void *threadarg);

void insert_sort(double lista[],long long l,long long h);

bool issorted(double lista[]);

void read_data(double lista[]);

double* lista=new double[TAMANHO];

struct thread_data
{
	long long l;
	long long h;
};

int main(int argc,char** argv)
{
	int thread_count=strtol(argv[1],NULL,10);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	int t;

	//double* lista=new double[TAMANHO];

/*read_data(lista);
	printf("\n Iniciando ordenamiento");
	start = std::chrono::system_clock::now();
	insert_sort(lista,0,TAMANHO-1);
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
	cout<<"\n Ordenamiento Terminado";
	if(!issorted(lista))
		throw "quick-sort-iterative not working";
	cout<<"\nTime with secuencial insertsort: "<<t<<"\n";*/


read_data(lista);
	printf("\n Iniciando ordenamiento");
	start = std::chrono::system_clock::now();

	struct thread_data td;
	td.l=0;
	td.h=TAMANHO-1;

	quick_sort_iterative_pthread_2((void *)&td);

	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	printf("\n Ordenamiento Terminado");
	if(!issorted(lista))
		throw "quick-sort-iterative not working";
	printf("\nTime with secuencial quicksort iterative: %d",t);


/*#	pragma omp parallel num_threads(thread_count) shared(lista,quota)
	{
		int my_rank=omp_get_thread_num();
		//quick_sort(lista.begin()+my_rank*quota,lista.begin()+my_rank*quota+merged2[my_rank]);
		quick_sort(lista.begin()+my_rank*quota,lista.begin()+my_rank*quota+merged2[my_rank]);
	}
*/
	return 0;
}

void insert_sort(double lista[],long long l,long long h)
{
	long long i,j;
	double key;
	for (i=l+1;i<=h;i++)
	{
		key=lista[i];
		j=i-1;

		while(j>=l && lista[j]>key)
		{
			lista[j+1]=lista[j];
            j=j-1;
		}
        lista[j+1]=key;
	}
}

bool issorted(double lista[])
{
	int flag=1;
	for(int i=0;i<TAMANHO-1;i++)
		if(lista[i]>lista[i+1])
			flag=0;
	return flag;
}

void read_data(double lista[])
{
	ifstream myReadFile;
	myReadFile.open(FILE);
	int count=0;
	if(myReadFile.is_open())
	{
		//while(!myReadFile.eof())
		while(count<TAMANHO)
		{
			myReadFile>>lista[count];
			count++;
		}
	}
}

//void quick_sort_iterative(long long l,long long h)
void *quick_sort_iterative(void *threadarg)
{
	//read args l,h
	struct thread_data *my_data;
	my_data=(struct thread_data *)threadarg;
	long long l=my_data->l,h=my_data->h;

	long long* stack=new long long [h-l+1];
   	long long top=-1,p,i,j;

	double x,aux;

   	stack[++top]=l;
   	stack[++top]=h;

	while(top>=0)
	{
    	h=stack[top--];
        l=stack[top--];

		x=lista[h];
		i=(l-1);

		for(j=l;j<=h-1;j++)
        	if(lista[j]<=x)
	        {
				i++;
        	    aux=lista[i];
            	lista[i]=lista[j];
	            lista[j]=aux;
			}
		p=i+1;
		aux=lista[p];
		lista[p]=lista[h];
		lista[h]=aux;

//		cout<<p<<" ";

        if(p-1>l)
        {
            if(p-l<17)
            	insert_sort(lista,l,p-1);
            else
            {
            	stack[++top]=l;
            	stack[++top]=p-1;
        	}
        }
        if(p+1<h)
        {
            if(h-p<19)
            	insert_sort(lista,p+1,h);
            else
            {
            	stack[++top]=p+1;
            	stack[++top]=h;
        	}
        }
    }
	pthread_exit(NULL);
}

//void quick_sort_iterative_pthread(long long l,long long h)
void quick_sort_iterative_pthread_2(void *threadarg)
{
	//read args l,h
	struct thread_data *my_data;
	my_data=(struct thread_data *)threadarg;
	long long l=my_data->l,h=my_data->h;

	struct thread_data td[2];

	long long p,i,j;
	double x,aux;

	x=lista[h];

	i=(l-1);

	for(j=l;j<=h-1;j++)
       	if(lista[j]<=x)
        {
			i++;
       	    aux=lista[i];
           	lista[i]=lista[j];
            lista[j]=aux;
		}
	p=i+1;
	aux=lista[p];
	lista[p]=lista[h];
	lista[h]=aux;

	td[0].l=l;
	td[0].h=p-1;

	td[1].l=p+1;
	td[1].h=h;

	pthread_t thread[2];
	int rc;

	rc=pthread_create(&thread[0],NULL,quick_sort_iterative,(void *)&td[0]);
	if(rc)
	{
		cout<<"Error:unable to create thread,"<<rc<<endl;
        exit(-1);
	}

	rc=pthread_create(&thread[1],NULL,quick_sort_iterative,(void *)&td[1]);
	if(rc)
	{
		cout<<"Error:unable to create thread,"<<rc<<endl;
        exit(-1);
	}

	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);

}
