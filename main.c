#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcije.h"



typedef struct obaveze {
	int br;
	char obaveza[200];
}OBAVEZE;

static int BrojObaveze;
static int brojac;
int izbornik();
void stvori_datoteku();
void naslov();
void dodaj();
void prikaz();


//Funkcije za kalendar
void kalendar();
char* mjeseci[] =
{
	" ",
	"\n\n\nSijecanj",
	"\n\n\nVeljaca",
	"\n\n\nOzujak",
	"\n\n\nTravanj",
	"\n\n\nSvibanj",
	"\n\n\nLipanj",
	"\n\n\n",
	"\n\n\n",
	"\n\n\n",
	"\n\n\n",
	"\n\n\n",
	"\n\n\n"

};


int main(void) {

	stvori_datoteku();
	naslov();
	izbornik();
	
	
	return 0;
}


void naslov() {
	printf("\t\t\t\t\t\t** To-Do Lista **\n\n");
}

int izbornik() {
	int opcija;
	do {
		
		printf("\n\t\t\t\t\t\t1. Dodaj obavezu\n\n");
		printf("\t\t\t\t\t\t2. Izbrisi obavezu\n\n");
		printf("\t\t\t\t\t\t3. Uredi postojecu obavezu\n\n");
		printf("\t\t\t\t\t\t4. Prikaz obaveza\n\n");
		printf("\t\t\t\t\t\t5. Prikazi kalendar\n\n");
		printf("\t\t\t\t\t\t6. Izadji iz programa\n\n");

		printf("\nOdabir opcije: ");
		scanf("%d", &opcija);
		


		
		switch (opcija) {
		case 1:
			dodaj();
			break;
		case 2:
			printf("\nIzbrisi obavezu broj:  ");
			break;
		case 3:
			printf("\nUredi postojecu obavezu broj: ");
			break;
		case 4:
			prikaz();
			break;
		case 5:
			printf("\nKalendar:\n");
			kalendar();
			break;
		case 6:
			system("cls");
			printf("\nIzlazenje iz programa!");
			exit(0);
			
		default:
			break;
		}

	} while (opcija != 6);
	return opcija;

}


void stvori_datoteku() {
	char* datoteka = "to do list.txt";
	FILE* mapa = NULL;
	mapa = fopen(datoteka, "a");

	if (mapa == NULL) {
		perror("Problem: ");
	}
	else {
		printf("\nDatoteka napravljena");
	}
	
}

void dodaj() {
	system("cls");
	
	FILE* fp = NULL;
	fp = fopen("to do list.txt","a");

	if (fp == NULL) {
		perror("dodavanje clanova error");
		
	}
	else {
		printf("\nDATOTEKA ZA DODAVANJE CLANOVA UCITANA");
	}

	OBAVEZE* pok = NULL;
	pok = (OBAVEZE*)malloc(sizeof(OBAVEZE));
	if (pok == NULL) {
		perror("Pokreska kod zauzimanja memorije za strukturu");
	}
	fread(&BrojObaveze, sizeof(int),1, fp);
	printf("\nbroj obaveze: %d\n", BrojObaveze);
	pok->br = BrojObaveze;
	
	printf("\nUnesite obavezu: ");
	getchar();
	scanf("%[^\n]",&pok->obaveza);
	printf("%s",pok->obaveza);
	
	fprintf(fp, "%d. %s\n", pok->br, pok->obaveza);
	
	system("pause");
	BrojObaveze++;
	system("cls");
	fclose(fp);
}
 


void prikaz() {
	system("cls");
	FILE* fp = NULL;
	fp = fopen("to do list.txt", "r");

	if (fp == NULL) {
		perror("citanje clanova error");
		printf("Nema obaveza! Probajte dodati koju obavezu.");
	}
	else {

		printf("Vase obaveze su:\n\n");
		char c;
		c = fgetc(fp);
		while (c != EOF) {
			printf("%c",c);
			c = fgetc(fp);
		}
		
		printf("\n\n\n");
		system("pause");
		system("cls");
		fclose(fp);
	}
}

void kalendar() {
	system("cls");

	int godina;
	printf("\nUnos godine: ");
	scanf("%d", &godina);


	system("pause");
	system("cls");

}