#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;
ifstream f("date.in");
ofstream g("date.out");
int v[1000000], c[1000000], fr[1000000];
void BubbleSort(int v[],int n)
{
    int i,j,aux;
    int ok;
    do
    {ok=1;
        for(i=0;i<n-1;i++)
            if(v[i]>v[i+1])
            {
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok=0;
            }
    }
    while(ok==0);
}
void CountSort(int note[],int n)
{
    int max1 = 0;
    for(int i=0;i<=n-1;i++)
        if (note[i] > max1)
            max1 = note[i];
    for(int i=0;i<=n-1;i++)
        fr[note[i]]++;
    int index = 0;
    for(int i=0;i<= max1;i++)
        for (int j=1;j<=fr[i];j++)
            note[index++] = i;
}
void InsertionSort(int v[],int n)
{
    int i,j,pivot;
    for(j=1;j<n;j++)
    {pivot=v[j];
        i=j-1;
        while(i>=0 && v[i]>pivot)
        {
            v[i+1]=v[i];
            i--;
        }
        v[i+1]=pivot;
    }

}
void RadixSort(int v[],int nr)
{
    int p=0;
    vector <int> bucket[256];
    int max1=0,nr_cifre=0;
    for(int i=0;i<nr;i++)
    {
        if(v[i]>max1)
            max1=v[i];
    }
    while(max1!=0)
    {
        nr_cifre++;
        max1 = max1 / 256;
    }
    for(int k=0;k<nr_cifre;k++)
    {
        for(int i=0;i<nr;i++)
            bucket[(v[i]>>p) % 256].push_back(v[i]);
        nr=0;
        for(int i=0;i<256;i++)
        {
            for(size_t j=0;j<bucket[i].size();j++)
                v[nr++]=bucket[i][j];
            bucket[i].clear();
        }
        p= p + 8 ;
    }
}
void interclasare(int v[], int left, int m, int right) {
    int i, j, k, nl, nr;
    nl = m-left+1; nr = right-m;
    int leftv[nl], right_v[nr];
    for(i = 0; i<nl; i++)
        leftv[i] = v[left+i];
    for(j = 0; j<nr; j++)
        right_v[j] = v[m+1+j];
    i = 0; j = 0; k = left;
    while(i < nl && j<nr) {
        if(leftv[i] <= right_v[j]) {
            v[k] = leftv[i];
            i++;
        }else{
            v[k] = right_v[j];
            j++;
        }
        k++;
    }
    while(i<nl) {
        v[k] = leftv[i];
        i++; k++;
    }
    while(j<nr) {
        v[k] = right_v[j];
        j++; k++;
    }
}
void MergeSort(int v[], int left, int right) {
    if(left < right) {
        int m = left+(right-left )/2;
        MergeSort(v, left, m);
        MergeSort(v, m+1, right);
        interclasare(v, left, m, right);
    }
}
int pozitie(int v[],int st, int dr)
{
    int x = v[dr], i = st, j;
    for (j = st; j <= dr - 1; j++)
        if (v[j] <= x)
        {swap(v[i], v[j]); i++;}

    swap(v[i], v[dr]);
    return i;
}
void QuickSort(int v[],int st, int dr)
{
    if (st<dr)
    {
        int i=pozitie(v,st,dr);
        QuickSort(v,st, i-1);
        QuickSort(v,i+1, dr);
    }
}
void generare ( int n, int nr_max, int v[])
{
    for ( int i = 0; i < n;i ++ )
        v[i] = rand()%nr_max;
}
void copie( int v[], int n, int c[])
{
    for ( int i = 0; i < n; i ++)
        c[i] = v[i];
}
void e_sortat( int v[], int n){
    for ( int i = 0; i< n - 1; i ++ )
        if ( v[i] > v[i +  1])
        {
            g << "Vectorul nu e sortat" << "\n";
            return;
        }
    g << "Vectorul e sortat"  << "\n";
}
int main() {
    int nr_teste;
    f >> nr_teste;
    for ( int i = 0;i < nr_teste; i ++ )
    {
        g << "Testul"<<i + 1 << "\n" << "\n";
        clock_t start,end;
        int n, nr_max;
        f >> n >> nr_max;
        generare(n,nr_max,v);

        if ( n <= 20000)
        {
            copie(v, n, c);
            start = clock();
            BubbleSort(c, n);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            g << "BubbleSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
            e_sortat(c, n);
        } else
            g << "Sunt prea multe numere pentru a fi sortate cu BubbleSort" << "\n";
        g << "\n";

        if ( n <= 20000)
        {
            copie(v, n, c);
            start = clock();
            InsertionSort(c, n);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            g << "InsertionSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
            e_sortat(c, n);
        } else
            g << "Sunt prea multe numere pentru a fi sortate cu InsertionSort" << "\n";
        g << "\n";

        if ( nr_max <= 1000000){
            copie(v, n, c);
            start = clock();
            CountSort(c,n);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            g << "CountSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
            e_sortat(c, n);
        } else
            g << "Sunt numere prea mari pentru a le sorta cu CountSort" << "\n";
        g <<"\n";

        copie(v, n, c);
        start = clock();
        RadixSort(c,n);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        g << "RadixSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
        e_sortat(c, n);
        g <<"\n";

        copie(v, n, c);
        start = clock();
        QuickSort(c,0, n);
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        g << "QuickSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
        e_sortat(c, n);
        g <<"\n";

        copie(v, n, c);
        start = clock();
        MergeSort(c,0,n);
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        g << "MergeSort a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
        e_sortat(c, n);
        g <<"\n";

        copie(v, n, c);
        start = clock();
        sort(c,c + n);
        end = clock();
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        g << "Sortarea implicita a sortat in  : " << fixed << time_taken << setprecision(5) << " sec " << "\n";
        e_sortat(c, n);
        g <<"\n";

    }
    return 0;
}