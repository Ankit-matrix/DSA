#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ssize_t long long

struct node{
    size_t to;
    struct node *next;
};

struct graph{
    struct node **adj;
    size_t n;
};

struct graph *new_graph(size_t n){
    struct graph *g = malloc(sizeof(struct graph));
    g->n=n;
    g->adj=calloc(n, sizeof(struct node *));
    return g;
}

void add_edge(struct graph *g, size_t from, size_t to){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->to = to;
    newNode->next = g->adj[from];
    g->adj[from]=newNode;
}

void dfs(struct graph *g, size_t *d, size_t *f, ssize_t *p){
    bool *visited = calloc(g->n, sizeof(bool));
    size_t timer = 0;

    for(size_t i=0; i<g->n, i++){
        
    }
}

int main(void){
    struct graph *g = new_graph(10);

    add_edge(g, 0, 9);
    add_edge(g, 0, 5);
    add_edge(g, 0, 2);
    add_edge(g, 0, 1);

    add_edge(g, 1, 9);
    add_edge(g, 1, 6);
    add_edge(g, 1, 5);
    add_edge(g, 1, 4);
    add_edge(g, 1, 3);

    add_edge(g, 2, 9);
    add_edge(g, 2, 8);
    add_edge(g, 2, 7);
    add_edge(g, 2, 6);
    add_edge(g, 2, 3);

    add_edge(g, 3, 9);
    add_edge(g, 3, 8);
    add_edge(g, 3, 5);
    add_edge(g, 3, 0);

    add_edge(g, 4, 8);
    add_edge(g, 4, 6);
    add_edge(g, 4, 5);
    add_edge(g, 4, 1);

    add_edge(g, 5, 6);
    add_edge(g, 5, 1);

    add_edge(g, 6, 5);

    add_edge(g, 7, 8);
    add_edge(g, 7, 6);
    add_edge(g, 7, 5);
    add_edge(g, 7, 4);
    add_edge(g, 7, 3);

    add_edge(g, 8, 9);
    add_edge(g, 8, 6);
    add_edge(g, 8, 4);
    add_edge(g, 8, 1);
    add_edge(g, 8, 0);

    add_edge(g, 9, 7);
    add_edge(g, 9, 5);
    add_edge(g, 9, 3);
    add_edge(g, 9, 2);
    add_edge(g, 9, 0);

    size_t *d = malloc(g->n * sizeof(size_t));
    size_t *f = malloc(g->n * sizeof(size_t));
    ssize_t *p = malloc(g->n * sizeof(ssize_t));

    for (size_t i = 0; i < g->n; i++) {
            d[i] = f[i] = SIZE_MAX;
            p[i] = -1;
    }

    dfs(g,d,f,p);
}