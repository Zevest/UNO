#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/pile.h"
#include "include/carte.h"
#include "include/joueur.h"
#include "include/csvloader.h"
#include "include/play.h"

#define N 13

static int g_Sens = 1;	 // Sens du deroulement de la partie
static int g_Tour = 0;	 // Le nombre de mains passé
static int g_Compte = 0; // Comptabilise le nombre de cartes a piocher apres le +2 ou/et +4

/// Passe au tour suivant
void next()
{
	g_Tour += g_Sens;
}

/// Renvoie la valeur des tours jouer
int getTour()
{
	return g_Tour;
}

/// Modifie la valeur de tour
void setTour(int n)
{
	g_Tour = n;
}
/// Change de sens
void inverse()
{
	g_Sens *= -1;
}

/// Verifie si la carte peut etre jouer
int can_play_carte(card_t *carte_A, card_t *carte_B)
{

	bool b1 = (carte_B->num == 10);			// +2 sur le jeu
	bool b2 = (b1 || (carte_B->num == 14)); // +2 ou +4 sur le jeu
	bool a1 = ((carte_A->num == 10) && b1); // +2 dans la main et +2 sur le jeu
	bool a2 = ((carte_A->num == 14) && b2); // +2 ou +4 dans la main et +2 ou +4 sur le jeu
	bool a = (a1 || a2);
	bool b = (g_Compte == 0) && (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num >= 13);

	return (a ? a : b);
}

/// Verifie si un joueur peut jouer
int can_play(pile_t *main, card_t *carte)
{
	int i;

	for (i = 0; i < main->_TOP + 1; ++i)
	{
		if (can_play_carte(main->_DATA[i], carte))
			return 1;
	}
	return 0;
}

/// Compte le nombre de points d'un joueur
int G_point(player_t *g, int joueur)
{
	int i;
	int s = 0;

	for (i = 0; i < g[joueur].cards->_TOP + 1; i++)
	{
		switch (g[joueur].cards->_DATA[i]->num)
		{
		default:
			s += g[joueur].cards->_DATA[i]->num;
			break;
		case 10:
		case 11:
		case 12:
			s += 20;
			break;
		case 13:
		case 14:
			s += 50;
			break;
		}
	}
	return s;
}

/// Additionne les points des perdants pour les atribuer au gagnant
int fin_jeux(player_t *g, int joueur)
{
	int i, j = -1, s = 0;

	for (i = 0; i < joueur; ++i)
	{
		if (pile_Empty(g[i].cards))
			j = i;
	}
	if (j != -1)
	{

		for (i = 0; i < joueur; ++i)
		{
			if (j != i)
				s += G_point(g, i);
		}
		g[j].score += s;
	}
	return g[j].score;
}

/// Boucle principale du jeu
int play(player_t *joueurs, pile_t *paquets, pile_t *pioches, int joueur_1, int nb, csv_t *csv)
{
	int i;
	char a;
	int tmp = 0;

	// affiche les cartes du joueur
	for (i = 0; i < joueurs[joueur_1].cards->_TOP + 1; ++i)
	{

		card_Display(joueurs[joueur_1].cards->_DATA[i]);
		printf(" ");
	}
	jumpLine(2);
	printf(csv->data[5].message, NULL);
	card_Display(pile_GetTop(paquets));
	jumpLine(2);
	printf(csv->data[6].message, NULL);

	// affiche les cartes jouables
	for (i = 0; i < joueurs[joueur_1].cards->_TOP + 1; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].cards->_DATA[i], pile_GetTop(paquets)) == 1)
		{
			tmp++;
			printf("(%d: ", i);
			card_Display(joueurs[joueur_1].cards->_DATA[i]);
			printf(") ");
		}
	}

	// +2 ou/et +4 et le joueur n'a pas de +2 ni de +4 donc il est obligé de piocher
	if (g_Compte > 0 && !tmp)
	{
		//printf("%s pioche %d cartes!!\n", joueurs[joueur_1].name, g_Compte);
		printf(csv->data[7].message, joueurs[joueur_1].name, g_Compte);
		jumpLine(1);
		pile_Distribute(g_Compte, pioches, joueurs[joueur_1].cards);
		g_Compte = 0;
	}

	// +2 ou/et +4 et le joueur possède +2/+4 donc il peut jouer
	else if (tmp && g_Compte >= 0)
	{
		do
		{

			//printf("\n\nQuel carte jouer?\n");
			jumpLine(2);
			printf(csv->data[8].message, NULL);
			scanf("%d", &i);

		} while (i > joueurs[joueur_1].cards->_TOP || !(can_play_carte(joueurs[joueur_1].cards->_DATA[i], pile_GetTop(paquets))));

		// pose la carte sur le jeu
		pile_Push(paquets, joueurs[joueur_1].cards->_DATA[i]);
		pile_Remove(joueurs[joueur_1].cards, i);

		// applicationdes règles du jeu
		switch (pile_GetTop(paquets)->num)
		{
		default:
			break;
		case 10:
			g_Compte += 2;
		case 11:
			inverse();
			break;
		case 12:
			//printf("oups ton tour est passé \n");
			printf(csv->data[9].message, NULL);
			jumpLine(1);
			next();
			sleep(1);
			break;
		case 14:
			g_Compte += 4;
			//printf("quelle couleur ? (B,J,R,V)\n");
			printf(csv->data[10].message, NULL);
			jumpLine(1);
			do
			{

				a = '\0';

				scanf("%c", &a);
			} while (!(a == 'J' || a == 'R' || a == 'B' || a == 'V'));
			pile_GetTop(paquets)->color = a;
			break;
		case 13:
			//printf("quelle couleur ? (B,J,R,V)\n");
			printf(csv->data[10].message, NULL);
			jumpLine(1);
			do
			{
				a = '\0';

				scanf("%c", &a);
			} while (!(a == 'J' || a == 'R' || a == 'B' || a == 'V'));
			pile_GetTop(paquets)->color = a;
			break;
		}
	}
	// le joueur n'a pas de cartes a joué, il doit piocher
	else
	{
		printf(csv->data[11].message, joueurs[joueur_1].name);
		jumpLine(1);
		//printf("%s a pioché \n", joueurs[joueur_1].name);
		pile_Distribute(1, pioches, joueurs[joueur_1].cards);
		sleep(1);
	}

	// tour suivant
	if (pile_Empty(joueurs[joueur_1].cards))
	{
		printf(csv->data[12].message, fin_jeux(joueurs, nb));
		jumpLine(1);
		//printf("point %d\n", fin_jeux(joueurs, nb));
		return joueurs[joueur_1].score;
	}

	next();

	if (g_Tour < 0)
		g_Tour += 4;
	return 0;
}
