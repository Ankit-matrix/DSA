#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

bool ok(size_t *q, size_t n){
    for(size_t i=0; i<n; i++){
        for(size_t j=i+1; j<n; j++){
            size_t d;
            if(q[i]>q[j]){
                d=q[i]-q[j];
            }
            else if(q[j]>q[i]){
                d=q[j]-q[i];
            }
            if(d==(j-i)) return false;
        }
    }
    return true;
}

size_t do_nqueens(size_t n, size_t *q, size_t k){
    if(k==n && ok(q, k)) return 1;
    if(!ok(q,k)) return 0;

    bool *used = malloc(n*sizeof(bool));
    size_t c=0;
    for(size_t i=0; i<n; i++){
        used[i]=false;
    }
    for(size_t i=0; i<k; i++){
        used[q[i]]=true;
    }

    for(size_t i=0; i<n; i++){
        if(!used[i]){
            q[k]=i;
            c+=do_nqueens(n, q, k+1);
        }
    }
    free(used);
    return c;
}

size_t n_queens(size_t n){
    size_t *queens = malloc(n*sizeof(size_t));
    assert(queens);
    size_t c = do_nqueens(n, queens, 0);
    free(queens);
    return c;
}

int main(void){
    size_t n;
    if(scanf("%zu", &n)!=1) return 1;
    printf("%zu\n",n_queens(n));
}