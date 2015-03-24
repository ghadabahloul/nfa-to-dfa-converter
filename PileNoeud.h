#ifndef PileNoeud
#define PileNoeud

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct celluleN
{
	noeud *val;
    struct celluleN *suivant;
};
typedef struct celluleN celluleN ;

struct PileN
{
    celluleN *premier;
    int taille;
    int nbElem;
};
typedef struct PileN PileN ;


void creerPileN(PileN *p,int taille)
{
    p->premier = NULL ;
    p->taille = taille ;
    p->nbElem = 0 ;
}
int pileVideN(PileN *p)
{
    return (p->premier == NULL);
}

int pilePleineN(PileN *p)
{
    return (p->nbElem == p->taille);
}

void empilerN(PileN *p,noeud *x)
{
    if (!pilePleineN(p))
    {
            celluleN *cel = (celluleN*)malloc(sizeof(celluleN)) ;
            cel->val = x ;
            cel->suivant = NULL;
            (p->nbElem)++ ;

        if(pileVideN(p))
        {
            p->premier = cel;
        }else
        {
            cel->suivant = p->premier ;
            p->premier = cel ;
        }
    }
}
noeud *depilerN(PileN *p)
{
    if(!pileVideN(p))
    {


        noeud *res = p->premier->val ;
        if(p->nbElem == 1)
        {
            free(p->premier);
            p->premier = NULL ;
            (p->nbElem)--;
            return(res) ;
        }
        else
        {
            celluleN *cel = p->premier ;
            p->premier = cel->suivant ;
            free(cel) ;
            (p->nbElem)--;
            return (res) ;
        }


    }
    
}

#endif // PILECHAR_H_INCLUDED
