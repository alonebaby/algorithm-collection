/*******************************************************************
 * File: perfect_shuffle.cpp
 * Author: 
 * This file includes two implementations for perfect shuffle algorithm,
 * with O(n) time and O(1) space
 * related links:
 *http://my.oschina.net/wizardpisces/blog/209998
 *http://arxiv.org/pdf/0805.1598.pdf
*/
#include <iostream>     // std::cout
#include <algorithm>    // std::rotate
#include <vector>       // std::vector
using namespace std;


//轮换
void Cycle(int Data[],int Lenth,int Start)
{
    int Cur_index,Temp1,Temp2;


      Cur_index=(Start*2)%(Lenth+1);
      Temp1=Data[Cur_index-1];
      Data[Cur_index-1]=Data[Start-1];

  while(Cur_index!=Start)
   {
        Temp2=Data[(Cur_index*2)%(Lenth+1)-1];
        Data[(Cur_index*2)%(Lenth+1)-1]=Temp1;
        Temp1=Temp2;
        Cur_index=(Cur_index*2)%(Lenth+1);
   }
}

//数组循环移位 参考编程珠玑
void Reverse(int Data[],int Len)
{
  int i,Temp;
  for(i=0;i<Len/2;i++)
  {
   Temp=Data[i];
   Data[i]=Data[Len-i-1];
   Data[Len-i-1]=Temp;
  }
}
void ShiftN(int Data[],int Len,int N)
{
   Reverse(Data,Len-N);
   Reverse(&Data[Len-N],N);
   Reverse(Data,Len);

}

//满足Lenth=3^k-1的perfect shfulle的实现
void Perfect1(int Data[],int Lenth)
{
     int i=1;

    if(Lenth==2)
  {
   i=Data[Lenth-1];
   Data[Lenth-1]=Data[Lenth-2];
   Data[Lenth-2]=i;
   return;
  }
    while(i<Lenth)
 {
     Cycle(Data,Lenth,i);
     i=i*3;
 }
}
   //查找最接近N的3^k
int LookUp(int N)
{
   int i=3;
   while(i<=N+1) i*=3;

   if(i>3) i=i/3;

   return i;
}
/*
*array right ratation from middle  to last
*/
void rightShift(int Data[], int first, int middle, int last)
{
    int next=middle;
    while(first !=  next)
    {
       swap(Data[first++],Data[next++]);
       if(next == last)
          next = middle;
       else if(first == middle)
               middle = next;
    }
}
void perfect(int Data[],int Lenth)
{
   int i,startPos=0;
   while(startPos<Lenth)
   {
     i=LookUp(Lenth-startPos);
    
     rightShift(Data,startPos+(i-1)/2,startPos+(Lenth-startPos)/2, startPos +(Lenth-startPos)/2 +(i-1)/2 );
   
     Perfect1(&Data[startPos],i-1);
     startPos+=(i-1);
   }
}
/*
*Another solution with O(n) time,O(1) space, but need extra stack space for perfect shuffle
*/
void shuffle(vector<int>::iterator begin, vector<int>::iterator end)
{
    if( end - begin <= 2)
    {
        return;
    }

    int len = end - begin;
    int halfLen = len >> 1;
    int quaterLen = halfLen >> 1;

    std::rotate(begin+quaterLen, begin+halfLen, begin+halfLen+quaterLen);
    shuffle(begin, begin + quaterLen*2);
    shuffle(begin + quaterLen*2, begin + halfLen*2);
}
int main () {
  int a[]={1,2,3,4,5,6,7,8,9,10};
  cout<<"perfect shuffle1:"<<endl;
 
  vector<int> v(a, a+sizeof(a)/sizeof(int));
  //method 1
  shuffle(v.begin(),v.end());
  
  for(int i=0; i< v.size(); i++)
     cout<<v[i]<<' ';
  cout<<endl;

  cout<<"perfect shuffle2:"<<endl;
  //method 2
  perfect(a,10);
  for(int i=0; i<sizeof(a)/sizeof(int); i++)
    cout<<a[i]<<' ';
  cout<<endl;
  return 0;
}
