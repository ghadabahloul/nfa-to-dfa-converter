#ifndef FonctionTla
#define FonctionTla
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include "Arbre.h"
#include "PileChar.h"
#include "PileNoeud.h"


void initPremDernN(noeud *n);
void positionPremiere(noeud *n);
void numeroterArbre(noeud *n);
void premDernierPosArbre(noeud *n);
void triTabInt(int *tabInt);



/*
struct sigma
{
	int etat ;
	char symbole ;
	int etatSuiv ;

};

*/


struct suivant
{
	char car ;
	int num;
	int psuivant[100];
};
typedef struct suivant suivant;





// *** FONCTION TLA ***
void inversChaine(char *ch)
{
	int lngCh=0,i=0;
	while(ch[i]!='\0')
		i++;
	lngCh = i ;

	int j=lngCh-1;
	for(i=0;i<lngCh/2;i++)
	{
		char aux ;
		aux   = ch[i];
		ch[i] = ch[j];
		ch[j] = aux ;
		j--;
	}

}


//(a*.b*)
//

char *expressionToPostfix(char *re)
{
	Pile *pileOp = (Pile*)malloc(sizeof(Pile)) ;
	Pile *PileExp = (Pile*)malloc(sizeof(Pile)) ; ;

	creerPile(pileOp,100);
	creerPile(PileExp,100);

	int i = 0;
	char c = NULL ;
	while(re[i] != '\0')
	{

		if(re[i]=='(' || re[i]=='.' || re[i]== 'U')
		{
			empiler(pileOp,re[i]);
		}else
		{
			if(re[i] != ')')
			{
				empiler(PileExp,re[i]);
			}
			else
			{
				do
				{
					c = depiler(pileOp) ;
					if(c!=NULL)
					{
						if(c=='.' || c=='U')
							empiler(PileExp,c) ;
					}
				}while(c != '(');
			}
		}
		i++;
	}
	
	//Empilement des derniere Op.. dans Exp
	char c2;
	do
	{
		c2 = depiler(pileOp) ;
		if(c2!=NULL)
			empiler(PileExp,c2);
	}while(!pileVide(pileOp));


	char *tabCh = (char*)malloc(sizeof(char)*100);
	int j = 0;
	do
	{
		tabCh[j] = depiler(PileExp);
		j++;
	}while(!pileVide(PileExp));
	tabCh[j] = '\0';

	inversChaine(tabCh);
	free(PileExp);
	free(pileOp);

	return tabCh;
}

noeud* expressionToArbre(char *rexp)
{
	rexp = expressionToPostfix(rexp) ;

	PileN *pile1 = (PileN*)malloc(sizeof(PileN));
	creerPileN(pile1,100);

	int i = 0 ;
	while(rexp[i] != '\0')
	{
		if(rexp[i] == 'U' || rexp[i] == '.')
		{
			noeud *n = (noeud*)malloc(sizeof(noeud)) ;
			n->val = rexp[i] ;

			n->droite = depilerN(pile1);
			n->gauche = depilerN(pile1);
			empilerN(pile1,n);
		}else 
		{
			if(rexp[i] == '*')
			{
				noeud *n = (noeud*)malloc(sizeof(noeud)) ;
				n->val = rexp[i] ;
				n->droite = NULL ;
				n->gauche = depilerN(pile1);
				empilerN(pile1,n);
			}
			else
			{
				//a,b,c,#...
				noeud *n = (noeud*)malloc(sizeof(noeud)) ;
				n->val = rexp[i] ;
				n->droite = NULL ;
				n->gauche = NULL ;
				empilerN(pile1,n);
			}

		}
		i++;
	}

	noeud *tete = depilerN(pile1) ;
	initPremDernN(tete);//initialisation  
	numeroterArbre(tete); 
	premDernierPosArbre(tete);

	return tete ;
}


//*********Reste


int annulable (noeud *n)
{
	if(n->val=='*')
		return 1 ;
	else if(n->val=='U')
		return(annulable(n->gauche) || annulable(n->droite));
	else if(n->val=='.')
		return(annulable(n->gauche) && annulable(n->droite));
	else 
		return 0;
}


void positionPremiere(noeud *n)
{
	int i,k;
	if(n->val=='U')
	{
		k=0;
		i=0;
		while(n->gauche->premier[i]!=0)
		{
			n->premier[k]=n->gauche->premier[i];
			k++;
			i++;
		}
		i=0;
		while(n->droite->premier[i]!=0)
		{
			n->premier[k]=n->droite->premier[i];
			k++;
			i++;
		}
	}

	else if(n->val=='.')
	{

		if(!annulable(n->gauche))
		{ 
			i=0; 
			while(n->gauche->premier[i]!=0)
			{
				n->premier[i]=n->gauche->premier[i];
				i++;
			}
		}
		else
		{
			i=0; k=0;
			while(n->droite->premier[i]!=0)
			{
				n->premier[k]=n->droite->premier[i];
				i++;
				k++;
			}
			i=0;
			while(n->gauche->premier[i]!=0)
			{
				n->premier[k]=n->gauche->premier[i];
				i++;
				k++;
			}
		}
	}
	else if (n->val=='*')
	{
		i=0; 
		while(n->gauche->premier[i]!=0)
		{
			n->premier[i]=n->gauche->premier[i];
			i++;
		}
	}
	else
	{
		n->premier[0]=n->num;
	}
}
void positionDerniere(noeud *n)
{
	int i,k;
	if(n->val=='U')
	{
		k=0;
		i=0;
		while(n->gauche->dernier[i]!=0)
		{
			n->dernier[k]=n->gauche->dernier[i];
			k++;
			i++;
		}
		i=0;
		while(n->droite->dernier[i]!=0)
		{
			n->dernier[k]=n->droite->dernier[i];
			k++;
			i++;
		}
	}
	else if(n->val=='.')
	{
		if(!annulable(n->droite))
		{ 
			i=0; 
			while(n->droite->dernier[i]!=0)
			{
				n->dernier[i]=n->droite->dernier[i];
				i++;
			}
		}
		else
		{
			i=0,k=0;
			while(n->droite->dernier[i]!=0)
			{
				n->dernier[k]=n->droite->dernier[i];
				i++;
				k++;
			}
			i=0;
			while(n->gauche->dernier[i]!=0)
			{
				n->dernier[k]=n->gauche->dernier[i];
				i++;
				k++;
			}
		}
	}
	else if (n->val=='*')
	{
		i=0; 
		while(n->gauche->dernier[i]!=0)
		{
			n->dernier[i]=n->gauche->dernier[i];
			i++;
		}
	}
	else
	{
		n->dernier[0]=n->num;
	}
}

int numi=1;

void numNoeud(noeud *n)
{
	if (n!= NULL)
	{ 

		if(n->val=='U' || n->val=='*' || n->val=='.')
		{
			n->num=0;
		}
		else
		{
			n->num=numi;
			numi++;
		}
	}
}

void numeroterArbre(noeud *n)
{
	if(n!=NULL)
	{
		numeroterArbre(n->gauche);
		numeroterArbre(n->droite);
		numNoeud(n);
	}
}


void initPremDernN(noeud *n)
{
	if(n!=NULL)
	{
		
		initPremDernN(n->gauche);
		initPremDernN(n->droite);

		int i;
		for(i=0;i<100;i++)
		{
			n->premier[i]=0;
			n->dernier[i]=0;
		}
	}
}
void premDernierPosArbre(noeud *n)
{
	if(n!=NULL)
	{
		premDernierPosArbre(n->gauche);
		premDernierPosArbre(n->droite);
		positionPremiere(n);
		positionDerniere(n);
	}
}

void pereNoeud(noeud *n,noeud *arb,noeud **pere)
{
	if(arb!=NULL)
	{

		if(n == arb->gauche || n == arb->droite)
		{
			*pere = arb ;
			
		}
		else
		{
			pereNoeud(n,arb->gauche,pere);
			pereNoeud(n,arb->droite,pere);
		}

	}

}

void initTabArb(noeud *tab[][100])
{
	int i = 0,j=0;
	for(i=0;i<4;i++)
		for(j=0;j<100;j++)
			tab[i][j] = NULL ;
}
int numN = 0;

void transfertArbTab(noeud *n,noeud *tab[][100])
{
	if(n!=NULL)
	{
		tab[0][numN] = n ;
		tab[1][numN] = n->gauche ;
		tab[2][numN] = n->droite ;
		numN++ ;
		transfertArbTab(n->gauche,tab);
		transfertArbTab(n->droite,tab);
	}
	}

//*******************************


void initTabSuivant(suivant *tablesuivant)
{
	int i = 0; 
	for (i=0;i<100;i++)
	{
		tablesuivant[i].num = 0 ;
		int j = 0; 
		for (j=0;j<100;j++)
			tablesuivant[i].psuivant[j] = 0 ;
	}
}

int rechCar(suivant tabSui , int car)
{
	int i = 0;
	for (i=0;i<100;i++)
	{
		//printf("TROUVEEE");
		if(tabSui.psuivant[i] == car)
			return 1 ;
	}
	return 0 ;
}

int rechExist(noeud *n,int pos)
{
	int i = 0;
	while(n->dernier[i] != 0)
	{
		if(n->dernier[i] == pos )
			return 1 ;
		i++ ;
	}
	return 0 ;
}

void positionSuivanteTab(noeud *tab[][100],suivant *tablesuivant)
{
	int cari = -1 ;
	int i = 0; 
	while(tab[0][i] != NULL )
	{
		
			
		if(tab[0][i]->val != 'U' && tab[0][i]->val != '.' && tab[0][i]->val != '*' )//&& tab[0][i]->val != '#')
		{
			cari++ ;
			tablesuivant[cari].car = tab[0][i]->val ;
			tablesuivant[cari].num = tab[0][i]->num ;
			int k = 0;
			noeud *car = tab[0][i] ;
			noeud *pr = NULL ;
			//printf("Car !!  %c \n",tab[0][i]->val);
			pere:
			do
			{
				pr = NULL ;
				pereNoeud(car,tab[0][0],&pr);
				
				if(pr!= NULL)
				{
					car = pr ;
					if(pr->val == 'U')
					{
						if(rechExist(car,tab[0][i]->num)) 
							goto pere ;
						else
							goto fin ;
					
						
					}
					if(pr->val == '.')
					{
						int kk = 0; 
						
						if(rechExist(car->gauche,tab[0][i]->num))
						{
							
							while(car->droite->premier[kk] != 0 )
							{
								
								tablesuivant[cari].psuivant[k] = car->droite->premier[kk] ;
								//printf("%d,",car->droite->premier[k]);
								
								k++ ;
								kk++;
								
							}
							
						}
					}
					if(pr->val == '*')
					{
						if(rechExist(car,tab[0][i]->num))
						{
							int kk=0;
							
							while(car->premier[kk] != 0 )
							{
								tablesuivant[cari].psuivant[k] = car->premier[kk] ;
								//printf("%d,",car->dernier[kk]);
								k++ ;
								kk++ ;
							}
							printf("\n");
						}
						
					}
				}
				else 
				{//pere null => .# 
					if(rechExist(car->gauche,tab[0][i]->num))
					{
						if(rechCar(tablesuivant[cari],tab[0][i]->num)) 
							tablesuivant[cari].psuivant[k] = car->droite->num ;
					}
				}
			}while(pr != NULL );
	
		}

fin:
	i++ ;
	
	}

}

void afficheTabArbre(noeud *TabArb[][100])
{
	int i = 0; 
	printf("\n \n \t ****   Affichage Tableau de  l'Aarbre   **** \n \n");
	
	while(TabArb[0][i] != NULL)
	{
		triTabInt(TabArb[0][i]->premier);
		triTabInt(TabArb[0][i]->dernier);
		int j = 0;
		if(TabArb[0][i] != NULL)
		{
		printf("Noeud %d   \n",i);
		printf("Numero = %d \n",TabArb[0][i]->num );
		if(TabArb[0][i] != NULL)
		{
		printf("Noeud = %c\n",TabArb[0][i]->val );
		j=0;
		printf("Premier ---->  ");

		while(TabArb[0][i]->premier[j] != 0)
		{
			printf("%d ,",TabArb[0][i]->premier[j] );
			j++ ;
		}

		printf("\nDernier ----> ");
		j=0;
		while(TabArb[0][i]->dernier[j] != 0)
		{
			printf("%d ,",TabArb[0][i]->dernier[j] );
			j++ ;
		}
		printf("\n");


		}
		if(TabArb[1][i] != NULL)
		{
		printf("Gauche = %c\n",TabArb[1][i]->val );

		}
		if(TabArb[2][i] != NULL)
		{
			printf("Droite = %c\n",TabArb[2][i]->val );
		}
		i++ ;
		printf("------------------------------------------------------\n");
		}
	}

	
}

void afficheTabPos(noeud *tab[][100] ,suivant *tabPos, int n)
{
	int i=0,j=0; 
	printf("\n\n \t **** Affichage du Tableau Pos/NextPos ****  \n\n");
	for (i=0;i<n;i++)
	{
		int k=0,car;
		j=0;
		
	while(tab[0][k] != NULL && tab[0][k]->num != tabPos[i].num)
			k++ ;
			
		printf("%c | %d | ",tab[0][k]->val,tabPos[i].num) ;
		triTabInt(tabPos[i].psuivant);
		int tabBuff[100] ;
		int ii ;
		for (ii=0;ii<100;ii++)
			tabBuff[ii] = 0 ; 

		ii=0;
		while(tabPos[i].psuivant[j] != 0)
		{

			if(tabPos[i].psuivant[j] != tabPos[i].psuivant[j+1]) 
			{
				printf("%d,",tabPos[i].psuivant[j]) ;
				tabBuff[ii] = tabPos[i].psuivant[j] ;
				ii++; 
			}
			j++;
		}

		for (ii=0;ii<100;ii++)
		 tabPos[i].psuivant[ii] = tabBuff[ii]; 

		printf("\n");
		
	}
	
}


void triTabInt(int *tabInt)
	//le tableaux doit finir par un 0 
{
	
	int i = 0 , j = 0 ; 
	while(tabInt[i] != 0)
	{
		j=0;

		while(tabInt[j] != 0)
		{
			if(tabInt[j]>tabInt[i])
			{
				int aux ;
				aux = tabInt[j] ;
				tabInt[j] = tabInt[i] ;
				tabInt[i] = aux ;
			}
				j++;
		}
		i++;
	}

	
}

void suppOccChar(char *tabInt)
{
	int i = 0 , j = 0 ; 
	char *charbff = (char*)malloc(sizeof(char)*100) ;
	while(tabInt[i] != '\0')
	{
		if(tabInt[i] != tabInt[i+1] )
		{
			charbff[j] = tabInt[i] ;
			j++ ;
		}
		i++;
	}
	charbff[j] = '\0';
	strcpy(tabInt,charbff);
}

void triTabChar(char *tabInt)
	//le tableaux doit finir par un 0 
{
	
	int i = 0 , j = 0 ; 
	while(tabInt[i] != '\0')
	{
		j=0;

		while(tabInt[j] != '\0')
		{
			if(tabInt[j]>tabInt[i])
			{
				int aux ;
				aux = tabInt[j] ;
				tabInt[j] = tabInt[i] ;
				tabInt[i] = aux ;
			}
				j++;
		}
		i++;
	}


	
}



void initEtat(int *tab[])
{
	int i = 0; 
	for (i=0;i<100;i++)
			tab[i] = NULL ;
			
}

void copieTabInt(int *tabDest,int *tabSrc)
{
	int i = 0;
	while(tabSrc[i] != 0) 
	{
		tabDest[i] = tabSrc[i] ;
		i++;
	}
}



int TabVide(int *tab)
{
	int i = 0; 
	for (i=0;i<99;i++)
	{
		if(tab[i] != 0)
			return 0 ;
	}
	return 1 ;
}

int compareTab(int *tab1,int *tab2)
{
	int i = 0; 
	while(tab1[i] == tab2[i] && i<99)
		i++ ;

	if(tab1[i] == 0 && tab2[i] == 0 )
		return 1 ;

	return 0 ;
}


int existTabInt(int *tabInt , int n)
{
	int i = 0 ;
	for (i=0;i<100;i++)
	{
		if(tabInt[i] == n ) 
			return 1 ;
	}
	return 0 ;
}

void initTabInt(int *tab)
{
	int i = 0;
	for (i=0;i<100;i++)
		tab[i] = 0 ;
}

char *saisieExpReg()
{
	char *ch = (char*) malloc(sizeof(char)*100) ;
	printf("\t Entrer l'expression Reguliaire  ---->   ");
	scanf("%s",ch);

	char deb[110] ,fin[100];

	strcpy(deb,"(");
	strcpy(fin,").#");
	strcat(deb,ch);
	strcat(deb,fin);

	
	strcpy(ch,deb) ;
	printf(" \n \t La nouvelle chaine est  ---->     %s\n",ch);
	return ch ;
}

int langage(noeud *TabArb[][100],char *lang)
{

	int i = 0, k = 0;
	while(TabArb[0][i] != NULL )
	{
		if(TabArb[0][i]->val != '.' && TabArb[0][i]->val != 'U' && TabArb[0][i]->val != '*' && TabArb[0][i]->val != '#')
		{
			lang[k] = TabArb[0][i]->val ;
			k++ ;
		}
		i++ ;
	}
	lang[k] = '\0' ;
	return k ;
}


	
#endif