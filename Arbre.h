#ifndef Arbre
#define Arbre



struct noeud
{
    struct noeud *gauche ;
    char val ;
    struct noeud *droite ;

	int premier[100];
	int dernier[100];
	int num;
};

typedef struct noeud noeud ;

struct arbre
{
    struct noeud *tete;
};
typedef struct arbre arbre ;


void creerArbre(arbre *A,int x)
{
    noeud *n = (noeud*)malloc(sizeof(noeud)) ;
    n->val = x ;
    n->droite = NULL ;
    n->gauche = NULL ;
    A->tete = n ;
}

noeud *creerNoeud(int val,noeud *g,noeud *d)
{
    noeud *n = (noeud*)malloc(sizeof(noeud));
    n->droite = d ;
    n->gauche = g ;
    n->val = val ;
	return n ;
}

void attacherGauche(noeud *A,noeud *n)
{
    A->gauche = n;
}
void attacherDroite(noeud *A,noeud *n)
{
    A->droite = n;
}

void suppGauche(noeud *A)
{
    attacherGauche(A,NULL) ;
}
void suppDroite(noeud *A)
{
    attacherDroite(A,NULL) ;
}

void visitePr(noeud *A)
{
    if (A!=NULL)
    {
        printf("%c ",A->val) ;
        visitePr(A->gauche);
        visitePr(A->droite);
    }
}
void visiteInfix(noeud *A)
{
    if (A!=NULL)
    {
        visiteInfix(A->gauche);
        printf("%c ",A->val) ;
        visiteInfix(A->droite);
    }
}
void visitePostFix(noeud *A)
{
    if (A!=NULL)
    {

        visitePostFix(A->gauche);
        visitePostFix(A->droite);
        printf("%c ",A->val) ;
    }
}

int nbNoeud(noeud *A)
{
    if (A != NULL)
    {
        return (1+nbNoeud(A->gauche)+nbNoeud(A->droite) );
    }
    else return 0;
}

int nFeuille(noeud *A)
{
    if (A != NULL)
    {
		if(A->gauche==NULL && A->droite == NULL)
			return (1+nFeuille(A->gauche)+nFeuille(A->droite) );
		else
			return (nFeuille(A->gauche)+nFeuille(A->droite) );
    }
    else return 0;
}


#endif // Arbre
