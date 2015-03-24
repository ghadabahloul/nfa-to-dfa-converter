// TLAprojet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Arbre.h"
#include "PileChar.h"
#include "PileNoeud.h"
#include "FonctionTLA.h"


int _tmain(int argc, _TCHAR* argv[])
{

                printf("\t\t*************************************************");
                printf("\n\t\t \t ***  Projet TLA   ***");
                printf("\n\t\t ************************************************ ");
                printf("\n \n \n");

	char *ch = saisieExpReg() ;

	noeud *tete = expressionToArbre(ch);

	printf("\nAffichage Arbre (PostFixe) ----> \n");
	visitePostFix(tete);
	printf("\n-----------------------------------\n");



	noeud *TabArb[4][100] ;
	initTabArb(TabArb);

	transfertArbTab(tete,TabArb);


	afficheTabArbre(TabArb);


	suivant tablesuivant[100];
	initTabSuivant(tablesuivant);
	positionSuivanteTab(TabArb,tablesuivant);

	int nb = nFeuille(tete);
	afficheTabPos(TabArb,tablesuivant,nb);



	char lang[100] ;
	int nbLg = langage(TabArb,lang);
	triTabChar(lang) ;
	suppOccChar(lang);
	int i = 0;


	//start
	int *Etat[100] ;
	initEtat(Etat);

	Etat[0] = (int*)malloc(sizeof(int)*100) ;
	initTabInt(Etat[0]);
	copieTabInt(Etat[0],tete->premier);





	printf("\n\n \t ************** RESULTAT *****************\n");


	printf("\nLangage ----> { ");

	triTabChar(lang) ;
	suppOccChar(lang);
	i=0;

	while(lang[i] != '\0')
	{
		printf("%c ",lang[i]);
			if(lang[i+1] != 0)
			printf(",");
		i++;
	}
	i=0;
	printf("} \n");
	printf("\n\n -----------------------------------\n");
	printf("ETATS  ----> \n");

	while(Etat[i] != NULL)
	{
		printf("<< Q%d >> { ",i);
		int j=0;
		while(Etat[i][j] != 0)
		{
			printf("%d",Etat[i][j]);
			if(Etat[i][j+1] != 0)
			printf(", ");
			j++;
		}

		i++;
		printf(" }\n");
	}

	i=0;
	printf("\n\n-------------------------------------\n");
	printf("\nstart (Q0) ---->  ");
	printf("{ ");
	while(tete->premier[i] != 0)
	{

		printf("%d",tete->premier[i]);
		if(tete->premier[i+1] != 0)
			printf(", ");
		i++;
	}

	printf(" }\n");
	i=0;
	printf("\n\n------------------------------------------\n");
	printf("\nFinal (F) --->  ");
	printf("{ ");

	int ii = 0,F;
	while(TabArb[0][ii] != NULL)
	{
		if (TabArb[0][ii]->val == '#')
		{
			F= TabArb[0][ii]->num;
			break ;
		}
		ii++;
	}


	while(Etat[i] != NULL)
	{
		ii=0 ;
		while(Etat[i][ii] != 0 )
		{
			if(Etat[i][ii]==F)

				{
					printf("Q%d",i);
					if(Etat[i+1] != NULL)
					 printf(", ");
				}

			ii++;
		}




		i++;
	}

	printf(" }\n");
	printf("\n\n-------------------------------------\n");


	printf("\n\n ****** FIN. ******\n");
	system("PAUSE");
	return 0;
}
