#include<random>
#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<fstream>
#include "omp.h"
//#include<math>

#define INFINITO 2.0

#define FILE "list.txt"

//#define TAMANHO 120000000
#define TAMANHO 100
using namespace std;

template<class RandomAccessIterator>
void print(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void insert_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void merge(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last);

template<class RandomAccessIterator>
void merge_unbalanced(RandomAccessIterator first_destination,RandomAccessIterator first_origin,int first,int middle, int last);

template<class RandomAccessIterator>
void merge_inplace(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last);

template<class RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void quick_sort_iterative(RandomAccessIterator first,RandomAccessIterator last);

template<class RandomAccessIterator>
RandomAccessIterator partition_quick_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
bool issorted(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void read_data(RandomAccessIterator first);

template<class RandomAccessIterator>
void insert_sort(RandomAccessIterator first, RandomAccessIterator last);

int main(int argc,char** argv)
{
	int thread_count=strtol(argv[1],NULL,10);
	vector<double>lista(TAMANHO),listaa(TAMANHO);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	int t;
/*
	//secuencial mergesort
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando MergeSort:";
	start = std::chrono::system_clock::now();
	merge_sort(lista.begin(),lista.end());
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	if(!issorted(lista.begin(),lista.end()))
		throw "merge-sort not working";
	cout<<"\nTime with secuencial megesort: "<<t<<"\n";
*/

	//secuencial insert
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando InsertSort";
	start = std::chrono::system_clock::now();
	insert_sort(lista.begin(),lista.end());
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	if(!issorted(lista.begin(),lista.end()))
		throw "insert-sort not working";
	cout<<"\nTime with secuencial insertsort: "<<t<<"\n";


	//secuencial quicksort
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando QuickSort";
	start = std::chrono::system_clock::now();
	quick_sort(lista.begin(),lista.end());
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	if(!issorted(lista.begin(),lista.end()))
		throw "quick-sort not working";
	cout<<"\nTime with secuencial quicksort: "<<t<<"\n";

	cin>>t;

/*	//secuencial quicksort iterative
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando QuickSort";
	start = std::chrono::system_clock::now();
	quick_sort_iterative(lista.begin(),lista.end());
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	if(!issorted(lista.begin(),lista.end()))
		throw "quick-sort-iterative not working";
	cout<<"\nTime with secuencial quicksort iterative: "<<t<<"\n";
*/
/*
	//psrs
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando Parallel Sorting by Regular Sampling";

	vector<double>samples,pivotes;

	start = std::chrono::system_clock::now();

	int quota=TAMANHO/thread_count;

#	pragma omp parallel num_threads(thread_count) shared(lista,quota)
	{
		int my_rank=omp_get_thread_num();
		quick_sort(lista.begin()+my_rank*quota,lista.begin()+(my_rank+1)*quota);
	}

	int w=quota/thread_count;

/*	int index=0;
	for(int i=0;i<thread_count;i++)
		for(int j=0;j<3;j++)
			samples.push_back(*(lista.begin()+w*j+i*quota));


	samples.push_back(*(lista.begin()+7500000));
	samples.push_back(*(lista.begin()+15000000));
	samples.push_back(*(lista.begin()+22500000));

	samples.push_back(*(lista.begin()+37500000));
	samples.push_back(*(lista.begin()+45000000));
	samples.push_back(*(lista.begin()+52500000));

	samples.push_back(*(lista.begin()+67500000));
	samples.push_back(*(lista.begin()+75000000));
	samples.push_back(*(lista.begin()+82500000));

	samples.push_back(*(lista.begin()+97500000));
	samples.push_back(*(lista.begin()+105000000));
	samples.push_back(*(lista.begin()+112500000));

	quick_sort(samples.begin(),samples.end());

for(int i=0;i<thread_count*3;i++) cout<<"\n ---"<<samples[i];

/*	for(int i=0;i<thread_count-1;i++)
		pivotes.push_back(*(samples.begin()+(i+1)*thread_count+(thread_count/2)));


	pivotes.push_back(*(samples.begin()+3));
	pivotes.push_back(*(samples.begin()+6));
	pivotes.push_back(*(samples.begin()+9));

	cout<<"\n\n";

	for(int i=0;i<thread_count-1;i++) cout<<"\n ---"<<pivotes[i];

	vector<int>init0(4),init1(4),init2(4),init3(4);

#	pragma omp parallel num_threads(thread_count) shared(lista,quota)
	{
		int my_rank=omp_get_thread_num();
		vector<string>::iterator it
		quick_sort(lista.begin()+my_rank*quota,lista.begin()+(my_rank+1)*quota);
	}
*/

	//pivotes=p-1
	//posiciones:p+p,2p+p,p(p-1)+p

/*	//paralell quimer_sort
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando QuiMerSort";

	start = std::chrono::system_clock::now();

	int quota=TAMANHO/thread_count;
	cout<<"\nquota = "<<quota;

	vector<int>merged1(thread_count);
	vector<int>merged2(thread_count);
	for(int i=0;i<thread_count;i++)
	{
		merged1[i]=i;
		merged2[i]=quota;
	}
	merged2[thread_count-1]+=TAMANHO-(thread_count*quota);

	cout<<"\n"; for(vector<int>::const_iterator i=merged1.begin();i!=merged1.end();i++) cout<<" "<<*i;
	cout<<"\n"; for(vector<int>::const_iterator i=merged2.begin();i!=merged2.end();i++) cout<<" "<<*i;

	//cout<<"\n"; for(vector<double>::const_iterator i=lista.begin();i!=lista.end();i++) cout<<" "<<*i;

#	pragma omp parallel num_threads(thread_count) shared(lista,quota)
	{
		int my_rank=omp_get_thread_num();
		quick_sort(lista.begin()+my_rank*quota,lista.begin()+my_rank*quota+merged2[my_rank]);
	}

	//cout<<"\n"; for(vector<double>::const_iterator i=lista.begin();i!=lista.end();i++) cout<<" "<<*i;

	int count=0;
	while(merged1.size()!=1)
	{
		cout<<"\n"; for(vector<int>::const_iterator i=merged1.begin();i!=merged1.end();i++) cout<<" "<<*i;
		cout<<"\n"; for(vector<int>::const_iterator i=merged2.begin();i!=merged2.end();i++) cout<<" "<<*i;

		cout<<"\nReduction level: "<<count++;
		#	pragma omp parallel num_threads(thread_count) shared(count,lista,listaa,quota,merged1,merged2)
		{
			int my_rank=omp_get_thread_num();
			for(int i=0;(unsigned int)(i+1)<merged1.size();i+=2)
			{
				if(my_rank==merged1[i])
				{
					int inicio=merged1[i]*quota;
					int medio=merged1[i]*quota+merged2[i];
					int fin=merged1[i+1]*quota+merged2[i+1];
					printf("\nmy_rank= %d; El thread %d se une con %d, inicio=%d, medio=%d, fin=%d",my_rank,merged1[i],merged1[i+1],inicio,medio,fin);
					merge_unbalanced(listaa.begin(),lista.begin(),inicio,medio,fin);
					//merge_inplace(lista.begin()+inicio,lista.begin()+medio,lista.begin()+fin);
				}
			}
		}
		for(int i=0;(unsigned int)(i+1)<merged1.size();i++)
		{
			merged2[i]+=merged2[i+1];
			merged1.erase(merged1.begin()+i+1);
			merged2.erase(merged2.begin()+i+1);
		}

		//cout<<"\n"; for(vector<double>::const_iterator i=lista.begin();i!=lista.end();i++) cout<<" "<<*i;
	}

	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	if(!issorted(listaa.begin(),listaa.end()))
	//if(!issorted(lista.begin(),lista.end()))
		throw "merge-sort not working";

	cout<<"\nTime with secuencial quicksort: "<<t<<"\n";
*/
	return 0;
}

/*int main(int argc,char** argv)
{
	int ns[] = {100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
	int t1,t2,t3;
	for (auto n: ns)
	{
		vector<double>a(n),aa(n);
		generate_data(a.begin(),a.end(),n);

		aa=a;
		start = std::chrono::system_clock::now();
		merge_sort(aa.begin(),aa.end());
		end = std::chrono::system_clock::now();
		t2=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		if(!issorted(aa.begin(),aa.end()))
			throw "merge-sort not working";

		aa=a;
		start = std::chrono::system_clock::now();
		quick_sort(aa.begin(),aa.end());
	 	end = std::chrono::system_clock::now();
		t3=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		if(!issorted(aa.begin(),aa.end()))
			throw "quicksort not working";

		cout<<n<<": "<<t1<<";"<<t2<<";"<<t3<<endl;
 }

 return 0;
}*/

template<class RandomAccessIterator>
void insert_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	int key;
	RandomAccessIterator i,j;
	for(j=first+1;j!=last;j++)
	{
		key=*j;
		i=j-1;
		while(i!=first-1&&*i>key)
		{
			*(i+1)=*i;
			i--;
		}
		*(i+1)=key;
	}
}

template<class RandomAccessIterator>
void merge(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last)
{
	RandomAccessIterator Index,L_Index,R_Index;

	vector<double>L(middle-first+1);
	vector<double>R(last-middle+1);
	L_Index=L.begin();
	R_Index=R.begin();

	for(Index=first;Index!=middle;Index++,L_Index++)
		*L_Index=*Index;
	*L_Index=INFINITO;

	for(Index=middle;Index!=last;Index++,R_Index++)
		*R_Index=*Index;
	*R_Index=INFINITO;
	L_Index=L.begin();
	R_Index=R.begin();
	for(Index=first;Index!=last;Index++)
	{
		if(*L_Index<=*R_Index)
		{
			*Index=*L_Index;
			L_Index++;
		}
		else
		{
			*Index=*R_Index;
			R_Index++;
		}
	}
}

template<class RandomAccessIterator>
void merge_inplace(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last)
{
	cout<<"\nWelcome to merge_inplace";
	cout<<"\nPosition of R: "<<middle-first;
	RandomAccessIterator L_Index=first,R_Index=middle,aux;
	double temp;
	while(L_Index!=R_Index)
	{
		cout<<"\nPosition of L: "<<L_Index-first;
		if(*L_Index<=*R_Index)
		{
			L_Index++;
		}
		else
		{
			temp=*L_Index;
			*L_Index=*R_Index;
			aux=R_Index;
			while((aux+1)!=last && temp>*(aux+1))
			{
				*aux=*(aux+1);
				aux++;
			}
			*aux=temp;
			L_Index++;
		}
	}
	cout<<"End of inplace merge";
}

template<class RandomAccessIterator>
void merge_unbalanced(RandomAccessIterator first_destination,RandomAccessIterator first_origin,int first,int middle,int last)
{
	RandomAccessIterator Index=first_destination+first,L_Index=first_origin+first,R_Index=first_origin+middle;

	while(L_Index!=first_origin+middle && R_Index!=first_origin+last)
	{
		if(*L_Index<=*R_Index)
		{
			*Index=*L_Index;
			L_Index++;
		}
		else
		{
			*Index=*R_Index;
			R_Index++;
		}
		Index++;
	}

	while(L_Index!=first_origin+middle)
	{
		*Index=*L_Index;
		L_Index++;
		Index++;
	}
	while(R_Index!=first_origin+last)
	{
		*Index=*R_Index;
		R_Index++;
		Index++;
	}

	Index=first_destination+first;
	L_Index=first_origin+first;
	while(Index!=first_destination+last)
	{
		*L_Index=*Index;
		L_Index++;
		Index++;
	}
}

template<class RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if(last-first>1)
	{
		RandomAccessIterator middle=first+(last-first)/2;
		merge_sort(first,middle);
		merge_sort(middle,last);
		merge(first,middle,last);
	}
}

template<class RandomAccessIterator>
bool issorted(RandomAccessIterator first, RandomAccessIterator last)
{
	int flag=1;
	RandomAccessIterator Index;
	for(Index=first;Index+1!=last;Index++)
		if(*Index>*(Index+1))
			flag=0;
	return flag;
}

template<class RandomAccessIterator>
void read_data(RandomAccessIterator first)
{
	ifstream myReadFile;
	myReadFile.open(FILE);
	int count=0;
	if(myReadFile.is_open())
	{
		while(!myReadFile.eof())
		{
			myReadFile>>*first;
			first++;
			count++;
		}
	}
}


template<class RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if(last-first>1)
	{
		RandomAccessIterator middle=partition_quick_sort(first,last);
		quick_sort(first,middle);
		quick_sort(middle+1,last);
	}
}

template<class RandomAccessIterator>
RandomAccessIterator partition_quick_sort(RandomAccessIterator first,RandomAccessIterator last)
{
	double x=*(last-1),aux;
	RandomAccessIterator j,i=first-1;
	for(j=first;j!=last-1;j++)
		if(*j<=x)
		{
			i++;
			aux=*i;
			*i=*j;
			*j=aux;
		}
	aux=*(i+1);
	*(i+1)=*(last-1);
	*(last-1)=aux;
	return i+1;
}

/*template<class RandomAccessIterator>
void quick_sort_iterative(RandomAccessIterator first,RandomAccessIterator last)
{
	RandomAccessIterator stack[last-first+1],l=first,h=last,p;
	int top=-1;

	stack[++top]=l;
	stack[++top]=h;

  	while(top >=0)
  	{
    	h=stack[top--];
    	l=stack[top--];

 		p=partition_quick_sort(l,h);

		if(p-l-1>0)
		{
			stack[++top]=l;
			stack[++top]=p-1;
		}
		if(p-h+1<0)
		{
			stack[++top]=p+1;
			stack[++top]=h;
		}
	}
}
*/
