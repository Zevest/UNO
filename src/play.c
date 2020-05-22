#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pile.h"
#include "joueur.h"
#include "carte.h"
#include "csvloader.h"
#include "play.h"
#include "util.h"

#define N 13

static int g_Sens = 1;	 // Sens du deroulement de la partie
static int g_Tour = 0;	 // Le nombre de mains passé
static int g_Compte = 0; // Comptabilise le nombre de cartes a piocher apres le +2 ou/et +4

/// Passe au tour suivant
void play_Next()
{
	g_Tour += g_Sens;
}

/// Renvoie la numero du tour
int play_GetTour()
{
	return g_Tour;
}

/// Modifie la valeur du tour
void play_SetTour(int n)
{
	g_Tour = n;
}
/// Change le sens du jeu
void play_Inverse()
{
	g_Sens *= -1;
}

/*A TESTER*/
/// Vérifie si la carte peut être jouée
bool play_IsCardPlayable(card_t *testedCard, card_t *lastPlayedCard)
{

	bool b1 = (lastPlayedCard->num == 10);		   // +2 sur le jeu
	bool b2 = (b1 || (lastPlayedCard->num == 14)); // +2 ou +4 sur le jeu
	bool a1 = ((testedCard->num == 10) && b1);	   // +2 dans la main et +2 sur le jeu
	bool a2 = ((testedCard->num == 14) && b2);	   // +2 ou +4 dans la main et +2 ou +4 sur le jeu
	bool a = (a1 || a2);
	bool b = (g_Compte == 0) && (testedCard->num == lastPlayedCard->num || testedCard->color == lastPlayedCard->color || testedCard->num >= 13);

	return (a ? a : b);
}

/// Vérifie qu'un joueur puisse jouer
bool play_CanPlay(pile_t *playerCards, card_t *lastPlayedCard)
{
	int i;

	for (i = 0; i < playerCards->_TOP + 1; ++i)
		if (play_IsCardPlayable(playerCards->_DATA[i], lastPlayedCard))
			return true;

	return false;
}

/// Compte le nombre de points d'un joueur
int play_CountPoint(player_t *players, int playerNumber)
{
	int i;
	int score = 0;

	for (i = 0; i < players[playerNumber].cards->_TOP + 1; i++)
		switch (players[playerNumber].cards->_DATA[i]->num)
		{
		default:
			score += players[playerNumber].cards->_DATA[i]->num;
			break;
		case 10:
		case 11:
		case 12:
			score += 20;
			break;
		case 13:
		case 14:
			score += 50;
			break;
		}

	return score;
}

/// Additionne les points des perdants pour les attribuer au gagnant
int play_EndGame(player_t *players, int playerNumber)
{
	int i, j = -1, score = 0;

	for (i = 0; i < playerNumber; ++i)
		if (pile_Empty(players[i].cards))
			j = i;

	if (j != -1)
	{
		for (i = 0; i < playerNumber; ++i)
			if (j != i)
				score += play_CountPoint(players, i);

		players[j].score += score;
	}
	return players[j].score;
}

/// Fait jouer le joueur et applique les règles associée à la carte qu'il joue
void play_GameCardRule(player_t *players, pile_t *package, int playerNumber, csv_t *csv)
{
	char buf[50];
	char pickedColor;
	int i;

	// Sélection de la carte à jouer
	do
	{
		util_JumpLine(2);
		util_Ask(csv->data[8].message, buf, util_IsNumeric);
		i = atoi(buf);
	} while (i > players[playerNumber].cards->_TOP || !(play_IsCardPlayable(players[playerNumber].cards->_DATA[i], pile_GetTop(package))));

	// Pose la carte sur le jeu
	pile_Push(package, players[playerNumber].cards->_DATA[i]);
	pile_Remove(players[playerNumber].cards, i);

	// Applique les règles du jeu
	switch (pile_GetTop(package)->num)
	{
	default:
		break;
	case 10:
		g_Compte += 2;
	case 11:
		play_Inverse();
		break;
	case 12:
		printf(csv->data[9].message, NULL);
		util_JumpLine(1);
		play_Next();
		sleep(1);
		break;
	case 14:
		g_Compte += 4;
	case 13:
		printf(csv->data[10].message, NULL);
		util_JumpLine(1);

		do
		{
			pickedColor = '\0';
			scanf("%c", &pickedColor);
		} while (!(pickedColor == 'J' || pickedColor == 'R' || pickedColor == 'B' || pickedColor == 'V'));

		util_ClearInputBuffer();
		pile_GetTop(package)->color = pickedColor;
		break;
	}
}

/// Fonction Principale du jeu
int play_Play(player_t *players, pile_t *package, pile_t *deck, int playerNumber, int playerCount, csv_t *csv)
{
	int i, playableCardCount = 0;

	// Affiche les cartes du joueur
	for (i = 0; i < players[playerNumber].cards->_TOP + 1; ++i)
	{
		card_Display(players[playerNumber].cards->_DATA[i]);
		printf(" ");
	}
	util_JumpLine(2);
	printf(csv->data[5].message, NULL);
	card_Display(pile_GetTop(package));
	util_JumpLine(2);
	printf(csv->data[6].message, NULL);

	// Affiche les cartes jouables
	for (i = 0; i < players[playerNumber].cards->_TOP + 1; ++i)
		if (play_IsCardPlayable(players[playerNumber].cards->_DATA[i], pile_GetTop(package)) == 1)
		{
			playableCardCount++;
			printf("(%d: ", i);
			card_Display(players[playerNumber].cards->_DATA[i]);
			printf(") ");
		}

	// +2 ou/et +4 et le joueur n'a pas de +2 ni de +4 donc il est obligé de piocher
	if (g_Compte > 0 && !playableCardCount)
	{
		printf(csv->data[7].message, players[playerNumber].name, g_Compte);
		util_JumpLine(1);
		pile_Distribute(g_Compte, deck, players[playerNumber].cards);
		/*{
			pile_Shuffle(package, deck, 1);
			pile_Distribute(g_Compte, deck, players[playerNumber].cards);
		}*/
		g_Compte = 0;
		sleep(1);
	}

	// +2 ou/et +4 et le joueur possède +2/+4 donc il peut jouer
	else if (playableCardCount && g_Compte >= 0)
		play_GameCardRule(players, package, playerNumber, csv);

	// le joueur n'a pas de cartes à jouer, il doit piocher
	else
	{
		printf(csv->data[11].message, players[playerNumber].name);
		util_JumpLine(1);
		pile_Distribute(1, deck, players[playerNumber].cards);
		/*	;
		{
			pile_Shuffle(package, deck, 10);
			pile_Distribute(1, deck, players[playerNumber].cards);
		}*/
		sleep(1);
	}

	// tour suivant
	if (pile_Empty(players[playerNumber].cards))
	{
		int point = play_EndGame(players, playerCount);
		//printf(csv->data[12].message, point);
		//util_JumpLine(1);
		return point;
	}

	play_Next();

	if (g_Tour < 0)
		g_Tour += 4;
	return 0;
}
