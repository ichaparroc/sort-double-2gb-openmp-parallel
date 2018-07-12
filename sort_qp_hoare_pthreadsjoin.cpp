#include<iostream>
#include<chrono>
#include<fstream>
#include<pthread.h>
#include<sys/mman.h>
#define FILE "list.txt"

#define TAMANHO 120000000
//#define TAMANHO 2000000

using namespace std;

void *quick_sort_iterative(void *threadarg);

void *quick_sort_iterative_pthread_2(void *threadarg);

void *quick_sort_iterative_pthread_4(void *threadarg);

void quick_sort_iterative_pthread_8(void *threadarg);

void insert_sort(double lista[],long long l,long long h);

bool issorted(double lista[]);

void read_data(double lista[]);

double* lista=new double[TAMANHO];

struct thread_data
{
	int tipo,level;
	long long l;
	long long h;
};

int main(int argc,char** argv)
{
	mlock(&lista[0],TAMANHO);
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

	struct thread_data td;
	td.l=0;
	td.h=TAMANHO-1;
	td.tipo=0;
	td.level=4;

	printf("\n Iniciando ordenamiento");

	start = std::chrono::system_clock::now();

	quick_sort_iterative_pthread_2((void *)&td);

	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	printf("\n Ordenamiento Terminado");
	if(!issorted(lista))
		throw "quick-sort-iterative not working";
	printf("\nTime with secuencial quicksort iterative: %d",t);

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

	int flag; //4 hoare partition

	double x,aux;

	double key;//insertionsort

   	stack[++top]=l;
   	stack[++top]=h;

	while(top>=0)
	{
    	h=stack[top--];
        l=stack[top--];

		x=lista[l];
		i=l-1;
		j=h+1;

		flag=1;

		while(flag)
		{
			do
			{
				i++;
			}
			while(lista[i]<x);
			do
			{
				j--;
			}
			while(lista[j]>x);
			if(i>=j)
			{
				p=j;
				flag=0;
			}
			else
			{
				aux=lista[i];
				lista[i]=lista[j];
				lista[j]=aux;
			}
		}


/*		x=lista[h];
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
*/
        //if(p-1>l)
        if(p>l)
        {
            if(p-l<17)
            {
            	//insert_sort(lista,l,p-1);
				//for (i=l+1;i<=p-1;i++)
				for (i=l+1;i<=p;i++)
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
           	else
           	{
    	        	stack[++top]=l;
        	    	stack[++top]=p;
        	}
        }
        if(p+1<h)
        {
            if(h-p<19)
			{
				//insert_sort(lista,p+1,h);
				for (i=p+2;i<=h;i++)
				{
					key=lista[i];
					j=i-1;

					while(j>=p+1 && lista[j]>key)
					{
						lista[j+1]=lista[j];
    	    		    j=j-1;
					}
			        lista[j+1]=key;
				}
            }
            else
            {
            	stack[++top]=p+1;
            	stack[++top]=h;
        	}
        }
    }
	//pthread_exit(NULL);
}

//void quick_sort_iterative_pthread(long long l,long long h)
void *quick_sort_iterative_pthread_2(void *threadarg)
{
	//read args l,h
	struct thread_data *my_data;
	my_data=(struct thread_data *)threadarg;
	long long l=my_data->l,h=my_data->h;
	int tipo=my_data->tipo,level=my_data->level;

	struct thread_data td[2];

	long long p,i,j;
	double x,aux;

	x=lista[l];
	i=l-1;
	j=h+1;
	int flag=1;
	while(flag)
	{
		do
		{
			i++;
		}
		while(lista[i]<x);
		do
		{
			j--;
		}
		while(lista[j]>x);
		if(i>=j)
		{
			p=j;
			flag=0;
		}
		else
		{
			aux=lista[i];
			lista[i]=lista[j];
			lista[j]=aux;
		}
	}


/*	x=lista[h];

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
*/
	td[0].l=l;
	td[0].h=p;
	td[0].level=level-1;
	td[0].tipo=0;

	td[1].l=p+1;
	td[1].h=h;
	td[1].level=level-1;
	td[1].tipo=0;

	if(level>0)
	{
		td[0].tipo=1;

		pthread_t thread;
		int rc;

		rc=pthread_create(&thread,NULL,quick_sort_iterative_pthread_2,(void *)&td[0]);
		if(rc)
		{
			printf("Error:unable to create thread, %d",rc);
	        exit(-1);
		}

		quick_sort_iterative_pthread_2((void *)&td[1]);

		pthread_join(thread,NULL);

	}
	else
	{
		quick_sort_iterative((void *)&td[0]);
		quick_sort_iterative((void *)&td[1]);
	}

	if(tipo==1)
		pthread_exit(NULL);
}
