#include "utils.h"

/// REMINDER FREE AND CHECK ALOCARE DINAMICA

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};



char *fromEnumtoString(PlayerRoles playerRole)

{

	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));

	switch(playerRole)

	{

		case Rotator:

			str = strcpy(str, "Rotator");

			break;

		case Decoder:

			str = strcpy(str, "Decoder");

			break;

		case Invertor:

			str = strcpy(str, "Invertor");

			break;

		case Impostor:

			str = strcpy(str, "Impostor");

			break;

	}

	return str;

}



//Task 1

void *RotateMatrix(void *input)

{

	// TODO

	int n;

	n = *(int *)input;



	//SAU 5 MERGE// n * n * (dim * 2 + 1)

	char *mat = malloc(MAX_LEN_STR_OUT * sizeof(char)); // aloc memoria necesara retinerii matricei ca sir singular de caractere



	if(mat == NULL)

	{

		//eroare de alocare

		return NULL;

	}



	for(int j = 1; j <= n; j++)

	{

		for(int i = n; i > 0; i--) // construiesc matricea

		{

			char *nr = malloc(50 * sizeof(char));

			if(nr == NULL)

			{

				//eroare de alocare

				return NULL;

			}



			if(i == n && j == 1)

			{

				sprintf(mat, "%d%d", i,j);

			}

			else

			{

			sprintf(nr, "%d%d", i,j);

            if(i != n) // verific daca nr nu este primul de pe linia sa

            {

                strcat(mat, " ");

            }

            strcat(mat, nr);	

			}

			

			free(nr);

		}

		if(j != n) // verific sa nu ne aflam pe ultima linie🐼

		{

			strcat(mat,"\n");

		}

	}







	return mat;

}



//Task 2

void *DecodeString(void *input)

{

	// TODO

	char *str = (char *)input;

	char *part; // pentru desartirea numerelor



	int suma = 0;



	part = strtok(str, "_");

	while (part != NULL)

    {

    	int nr = (atoi)(part);

		suma += nr;

    	part = strtok (NULL, "_");

    }



    char *rez = malloc(MAX_LEN_STR_OUT * sizeof(char));

	if(rez == NULL) //verific alocarea

	{

		return NULL;

	}



    sprintf(rez,"%d", suma);



	free(part);



	return rez;

}



//Task 3

void *InvertArray(void *input)

{

	// TODO

	int *array = (int *)input;

	int first = array[0];



	if(first % 2 == 0)

	{

		for(int i = 0; i < first/2; i++)

		{

			int aux = array[2 * i + 1];

			array[2 * i + 1] = array[2 * i + 2];

			array[2 * i + 2] = aux;

		}

	}

	else

	{

		for(int i = 0; i < first/2; i++)

		{

			int aux = array[i + 1];

			array[i + 1] = array[first - i];

			array[first - i] = aux;

		}

	}

	

	char *rez_array = malloc(first * sizeof(int));

	if(rez_array == NULL)

	{

		//eroare de alocare

		return NULL;

	} 



	char *buffer = malloc(MAX_LEN_STR_OUT * sizeof(char));

	if(buffer == NULL)

	{

		//eroare de alocare

		return NULL;

	}



	sprintf(rez_array,"%d ", array[1]); //pt initializarea lui rez_array

	for(int i = 2; i <= first; i++)

	{

		sprintf(buffer,"%d", array[i]);

		strcat(rez_array, buffer);

		if(i != first)

		{

			strcat(rez_array, " ");

		}

	}

	free(buffer);

	return rez_array;

}



//Task 4

Player *allocPlayer()

{

	// TODO

	Player *ply = malloc(sizeof(struct _player)); // alocarea structurii

	ply->name = malloc(MAX_LEN_STR_ATR * sizeof(char));

	ply->color = malloc(MAX_LEN_STR_ATR * sizeof(char));

	ply->hat = malloc(MAX_LEN_STR_ATR * sizeof(char));

	ply->alive = 1;

	return ply;

}



//Task 4

Game *allocGame()

{

	// TODO

	Game *gm = malloc(sizeof(struct _game));

	gm->name = malloc(MAX_LEN_STR_ATR * sizeof(char));

	return gm;

}



//Task 5

Player *ReadPlayer(FILE *inputFile)

{

	// TODO

	Player *ply = allocPlayer();

	fscanf(inputFile, "%s", ply->name);

	fscanf(inputFile, "%s", ply->color);

	fscanf(inputFile, "%s", ply->hat);

	fscanf(inputFile, "%d\n", &ply->numberOfLocations);

	ply->indexOfLocation = 0;

	int nr = ply->numberOfLocations; // PENTRU UTILIZARE MAI LEJERA 	

	ply->locations = malloc(nr * sizeof(struct _location)); // EVENTUAL MAI  MINIMALIZEAZA LUNGIMEA 



	for(int i = 0; i < nr; i++)

	{ 	

		char *loc_list = malloc(MAX_LEN_STR_LOC * sizeof(char)); // aloc memorie pt citirea unui ansamblu (a,b)	

		if(loc_list == NULL)

		{

			//eroare de alocare

			exit(1);

		}

		fscanf(inputFile, "%s", loc_list);



		char *token = strtok(loc_list, "(),");

		ply->locations[i].x = (atoi)(token);

		token = strtok(NULL, "(),");

		ply->locations[i].y = (atoi)(token);

		

		free(loc_list);

	}





	char role[8]; // pentru citirea rolului

	fscanf(inputFile, "%s", role);

	if (strcmp(role, "Rotator") == 0) 

	{

		ply->playerRole = Rotator;

		ply->ability = Abilities[Rotator];	

	} 

	else if (strcmp(role, "Decoder") == 0)

	{

		ply->playerRole = Decoder;

		ply->ability = Abilities[Decoder];

	}

	else if (strcmp(role, "Invertor") == 0)

	{

		ply->playerRole = Invertor;

		ply->ability = Abilities[Invertor];

	}

	else if (strcmp(role, "Impostor") == 0)

	{

		ply->playerRole = Impostor;

		ply->ability = Abilities[Impostor];

	}



	return ply;

}



// Task 5

Game *ReadGame(FILE *inputFile)

{

	// TODO

	Game *gm = allocGame();

	fscanf(inputFile, "%s", gm->name);

	fscanf(inputFile, "%d", &gm->killRange);

	fscanf(inputFile, "%d", &gm->numberOfCrewmates);

	gm->crewmates = malloc(gm->numberOfCrewmates * sizeof(struct _player)); // aloc memorie pentru vectorului de playeri



	for(int i = 0; i < gm->numberOfCrewmates; i++) // citesc fiecare player + impostor

	{

		gm->crewmates[i] = ReadPlayer(inputFile);

	}



	gm->impostor = ReadPlayer(inputFile);

	return gm;

}



// Task 6

void WritePlayer(Player *player, FILE *outputFile)

{

	// TODO

	char *emunToStr;

	emunToStr = fromEnumtoString(player->playerRole);

	fprintf(outputFile, "Player %s with color %s", player->name, player->color);

	fprintf(outputFile, ", hat %s and role %s ", player->hat, emunToStr);

	fprintf(outputFile, "has entered the game.\n");

	free(emunToStr);



	fprintf(outputFile, "Player's locations:");

	for(int i = 0; i < player->numberOfLocations; i++)

	{

		int x = player->locations[i].x;

		int y = player->locations[i].y;

		fprintf(outputFile, " (%d,%d)", x, y);

	}

	fprintf(outputFile, "\n");

	return;

}



// Task 6

void WriteGame(Game *game, FILE *outputFile)

{

	// TODO

	fprintf(outputFile, "Game %s has just started!\n", game->name);

	fprintf(outputFile, "	Game options:\n");

	fprintf(outputFile, "Kill Range: %d\n", game->killRange);

	fprintf(outputFile, "Number of crewmates: %d\n", game->numberOfCrewmates);

	fprintf(outputFile, "\n");

	fprintf(outputFile, "	Crewmates:\n");

	

	for(int i = 0; i < game->numberOfCrewmates; i++)

	{

		WritePlayer(game->crewmates[i], outputFile);

	}



	fprintf(outputFile, "\n");

	fprintf(outputFile, "	Impostor:\n");



	WritePlayer(game->impostor, outputFile);



	return;

}



//Aditional Task 7

int Dist(Location impostor, Location crewmate)

{

	int x = impostor.x - crewmate.x;

	int y = impostor.y - crewmate.y;

	return sqrt(x * x) + sqrt(y * y);

}



//Task 7

void *KillPlayer(void *input)

{

	// TODO

	Game *game = (Game *)input;

	int loc = game->impostor->indexOfLocation;

	Location impostor = game->impostor->locations[loc];



	int best_dist = game->killRange; // retine cea mai mica distanta & prin combinarea asta verific o singura conditie in loc de 2 

	int crw_index = -1; // retine nr de index al crewmatului care va fi ucis // initiez cu un nr de index inexistent pentru retinerea cazului in care nu se poate omora.



	for(int i = 0; i < game->numberOfCrewmates; i++)

	{

		Player *mate = game->crewmates[i];

		if(mate->alive) // verific doar in cazu in care este inca in viata

		{

			loc = mate->indexOfLocation;

			Location crewmate = mate->locations[loc];

			int dist = Dist(impostor, crewmate);



			if(dist <= best_dist)

			{

				crw_index = i;

				best_dist = dist;

			}

		}

	}



	char *rez_array = malloc(MAX_LEN_STR_OUT * sizeof(char));



	if(rez_array == NULL)

	{

		//eroare de alocare

		return NULL;

	}

	

	if(crw_index != -1)

	{

		game->crewmates[crw_index]->alive = 0;

		char *buffer = malloc(MAX_LEN_STR_OUT * sizeof(char));

		if(buffer == NULL)

		{

			//eroare de alocare

			return NULL;

		}



		sprintf(rez_array, "Impostor %s has just ", game->impostor->name);

		

		

		sprintf(buffer, "killed crewmate %s ", game->crewmates[crw_index]->name);

		strcat(rez_array, buffer);



		sprintf(buffer, "from distance %d.", best_dist);

		strcat(rez_array, buffer);



		free(buffer);



		return rez_array;

	}

	

	//daca nu intra in if inseamna ca nu a gasit

	sprintf(rez_array, "Impostor %s couldn't kill anybody.", game->impostor->name);



	return rez_array;

	



}



// Task 8

void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)

{

	// TODO

	

	Player *player;

	char *output;

	int loc, x, y;

	//crewmates

	for(int i = 0; i < game->numberOfCrewmates; i++)

	{

		player = game->crewmates[i];

		if(player->alive != 1)

		{

			fprintf(outputFile, "Crewmate %s is dead.\n", player->name);

		}

		else 

		{

			loc = player->indexOfLocation + 1; // indicele urmatoarei locatii

			if(loc == player->numberOfLocations)

				loc = 0; // se repeta ciclul locatiilor

			x = player->locations[loc].x;

			y = player->locations[loc].y;

			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n", player->name, x, y);

			player->indexOfLocation = loc; // modivic indexul



			void *input = inputMatrix[i]; 

			output = player->ability(input);

			fprintf(outputFile, "Crewmate %s's output:\n", player->name);

			fprintf(outputFile, "%s\n", output);

			free(output);

			

		}



	}



	//impostor here

	player = game->impostor;

	loc = player->indexOfLocation + 1; // indicele urmatoarei locatii

	if(loc == player->numberOfLocations)

			loc = 0; // se repeta ciclul locatiilor

	x = player->locations[loc].x;

	y = player->locations[loc].y;

	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n", player->name, x, y);

	player->indexOfLocation = loc; // modivic indexul



	fprintf(outputFile, "Impostor %s's output:\n", player->name);

	output = KillPlayer((void *)game);

	fprintf(outputFile, "%s\n", output);

	free(output);



	return;

}



// Task 9

void FreePlayer(Player *player)

{

	// TODO

	//free(player->ability);

	free(player->locations);

	free(player->name);

	free(player->color);

	free(player->hat);

	free(player);

	return;

}



// Task 9

void FreeGame(Game *game)

{

	// TODO

	free(game->name);

	for(int i = 0; i < game->numberOfCrewmates; i++)

	{

		FreePlayer(game->crewmates[i]);

	}

	free(game->crewmates);

	FreePlayer(game->impostor);

	free(game);

	return;

}