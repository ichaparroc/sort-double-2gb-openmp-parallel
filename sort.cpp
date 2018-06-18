#include<random>
#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<fstream>
#include<math>

#define INFINITO 2.0

#define TAMAÑO 120000000

	using namespace std;

template<class RandomAccessIterator>
void print(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void insert_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void merge(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last);

template<class RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
RandomAccessIterator partition_quick_sort(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
bool issorted(RandomAccessIterator first, RandomAccessIterator last);

template<class RandomAccessIterator>
void read_data(RandomAccessIterator first);

int main(int argc,char** argv)
{
	thread_count=strtol(argv[1],NULL,10);
	vector<double>lista(TAMAÑO),lista2(TAMAÑO);
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

	//secuencial quicksort
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando QuickSort";
	start = std::chrono::system_clock::now();
	quick_sort(lista.begin(),lista.end());
	end = std::chrono::system_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	if(!issorted(lista.begin(),lista.end()))
		throw "merge-sort not working";
	cout<<"\nTime with secuencial quicksort: "<<t<<"\n";
*/
	//paralell quimer_sort
	read_data(lista.begin());
	cout<<"\nLectura terminada, probando QuiMerSort";
	#pragma omp parallel for num_threads(thread_counts) shared(lista,thread_count) private(my_rank)
	{
		int my_rank=omp_get_thread_num();
		quick_sort(lista.begin()+my_rank*TAMAÑO/thread_count,lista.begin()+(my_rank+1)*TAMAÑO/thread_count);
	}
	#pragma omp parallel for num_threads(thread_counts) private(my_rank)
	{
		int my_rank=omp_get_thread_num();
		for(int i=0;i<(int)log2(num_threads-1)+1;i++)
			for(int i=0;i+pow(2,i)<num_threads;i+=pow(2,i+1))
				if(my_rank=i)
				{
					int inicio1=my_rank*TAMAÑO/thread_count;
					int fin1=(my_rank+pow(2,i))*TAMAÑO/thread_count;
					int inicio2=(my_rank+pow(2,i))*TAMAÑO/thread_count;
					int fin2=(my_rank+2*pow(2,i))*TAMAÑO/thread_count;

					for(int i=inicio1;i<fin2;i++)
					{
						if(
					}
					RandomAccessIterator Index,L_Index,R_Index;

					vector<double>L(last-middle+1);
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
	}



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

		cout<<n<<":  "<<t1<<";"<<t2<<";"<<t3<<endl;
  }

  return 0;
}*/

template<class RandomAccessIterator>
void merge(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last)
{
	RandomAccessIterator Index,L_Index,R_Index;

	vector<double>L(last-middle+1);
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
	myReadFile.open("list.txt");
	if(myReadFile.is_open())
	{
		while(!myReadFile.eof())
		{
			myReadFile>>*first;
			first++;
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

