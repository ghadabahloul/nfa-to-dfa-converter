#ifndef PILECHAR_H_INCLUDED
#define PILECHAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct cellule
{
    char val;
    struct cellule *suivant;
};
typedef struct cellule cellule ;

struct Pile
{
    cellule *premier;
    int taille;
    int nbElem;
};
typedef struct Pile Pile ;


void creerPile(Pile *p,int taille)
{
    p->premier = NULL ;
    p->taille = taille ;
    p->nbElem = 0 ;
}
int pileVide(Pile *p)
{
    return (p->premier == NULL);
}

int pilePleine(Pile *p)
{
    return (p->nbElem == p->taille);
}

void empiler(Pile *p,char x)
{
    if (!pilePleine(p))
    {
            cellule *cel = (cellule*)malloc(sizeof(cellule)) ;
            cel->val = x ;
            cel->suivant = NULL;
            (p->nbElem)++ ;

        if(pileVide(p))
        {
            p->premier = cel;
        }else
        {
            cel->suivant = p->premier ;
            p->premier = cel ;
        }
    }
}
char depiler(Pile *p)
{
    if(!pileVide(p))
    {


        char res = p->premier->val ;
        if(p->nbElem == 1)
        {
            free(p->premier);
            p->premier = NULL ;
            (p->nbElem)--;
            return(res) ;
        }
        else
        {
            cellule *cel = p->premier ;
            p->premier = cel->suivant ;
            free(cel) ;
            (p->nbElem)--;
            return (res) ;
        }


    }
    return NULL;
}

#endif // PILECHAR_H_INCLUDED
