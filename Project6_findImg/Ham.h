typedef unsigned char uint8;
typedef unsigned short uint16;

#include <stdio.h>
#include <math.h>
#include "list.h"

class Ham{
    
    int _dist(uint8 a, uint8 b){ 
        uint8 x= a^b, n= 0;
        for(int i= 0; i< 8; i++){
            n+= x&1;
            x >>= 1;
        }
        return n;
    }

    int _dist16(uint16 a, uint16 b){
        uint8* pa= (uint8*)&a;
        uint8* pb= (uint8*)&b;
        return _dist(*pa, *pb) + _dist (*(pa+1), *(pb+1));
    }

    void _printArr(int* arr, int len, int num){
        for(int i= 0; i < len; i++){
            if(num & 1)
                printf("%d, ", arr[i]);
            num >>= 1;
        }
    }

    void _temp(list* l, int len, int m, int n, int i){

        if(l->hd->v == 0){
            l->push_back(i);
            return;
        }
            
        for(node* p = l->hd; p ; p= p->next){
            int dist = _dist16(p->v, i);
            if( dist < (m-n) * 2 )
                return;                
        }
        l->push_back(i);
        return;
    }


    public:



    void combi(int* arr, int len, int m){
        int cnt = 1;
        int a = pow(2.0, len); 

        for(int i=0; i < a; i++){
            if(_dist16(a-1, i) == len - m){
                _printArr(arr, len, i);
                printf("cnt = %d \n", cnt++);
            }
        }
    }


    void combi2(int* arr, int len, int m, int n){
        list l;
        int cnt = 1;
        int a = pow(2.0, len); 

        for(int i=0; i < a; i++){
            if(_dist16(a-1, i) == len - m)
                _temp(&l, len, m, n, i);
        }

        for(node* p = l.hd; p; p= p->next){
            _printArr(arr, len, p->v);            
            printf("cnt = %d \n", cnt++);
        }
    }
};