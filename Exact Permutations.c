#include <stdio.h>
#include <stdint.h>

long long fac(int n){
    long long result = 1;
    if(n<0) return 0;
    else if(n==0) return 1;
    for(int i=1;i<=n;i++){
        result*=i;
    }
    return result;
}

int main(void){
    int n;
    scanf("%d\n",&n);
    int perm_size = n;
    if(perm_size >= 21) perm_size = 21;
    long long p;
    scanf("%lld\n", &p);
    p--;
    //Scanning
    for(size_t i=1; i<n-perm_size+1; i++){
        printf("%d ",i);
    }
    int x[perm_size];
    int zero[perm_size];
    for (size_t i=0; i<perm_size; i++){
        zero[i] = 0;
        x[i] = n-perm_size+i+1;
    }
    for(size_t i=perm_size;i>0;i--){
        int c=0;
        c=p/fac(i-1);
            p%=fac(i-1);
            int k=0;
            for(size_t j=0; j<perm_size;j++){
                if(zero[j]==0){
                    if(k==c){
                        printf("%d ",x[j]);
                        zero[j]=1;
                        break;
                    }
                    k++;
                }
            }
    }
}