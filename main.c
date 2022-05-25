#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcije.h"
#include "struktura.h"




char* datoteka = "to do list.txt";

static int BrojObaveze=1;



void naslov();
int izbornik();
void stvori_datoteku();
void dodaj();
void* ucitaj();	
void prikaz();
void IzbrisiDatoteku();

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
		printf("\t\t\t\t\t\t6. Izbrisi cijelu listu\n\n");
		printf("\t\t\t\t\t\t7. Izadji iz programa\n\n");

		printf("\nOdabir opcije: ");
		scanf("%d", &opcija);
		

		static OBAVEZE* PoljeObaveza = NULL;
		static OBAVEZE* TrazenaObaveza = NULL;

		
		switch (opcija) {
		case 1:
			dodaj();
			break;
		case 2:
			//printf("\nIzbrisi obavezu broj:  ");
			break;
		case 3:
			//printf("\nUredi postojecu obavezu broj: ");
			break;
		case 4:
			prikaz();
			break;
		case 5:
			printf("\nKalendar:\n");
			kalendar();
			break;
		case 6:
			IzbrisiDatoteku();
			break;
		case 7:
			system("cls");
			printf("\nIzlazenje iz programa!");
			exit(0);
			
		default:
			break;
		}

	} while (opcija != 7);
	return opcija;

}


void stvori_datoteku() {
	
	FILE* mapa = NULL;
	mapa = fopen(datoteka, "a");

	if (mapa == NULL) {
		perror("Problem: ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("\nDatoteka napravljena");
	}
	
	fclose(mapa);
}



void dodaj() {
	system("cls");
	
	FILE* fp = NULL;
	fp = fopen(datoteka,"a");

	if (fp == NULL) {
		perror("dodavanje clanova error");
		exit(EXIT_FAILURE);
		
	}
	else {
		printf("\nDATOTEKA ZA DODAVANJE CLANOVA UCITANA");
	}

	
	
	OBAVEZE temp = { 0 };

	fread(&BrojObaveze, sizeof(int),1, fp);
	temp.br = BrojObaveze;
	
	printf("\nUnesite obavezu: ");
	getchar();
	scanf("%199[^\n]", temp.obaveza);
	printf("%s", temp.obaveza);
	
	fprintf(fp, "%d. %s\n\n", temp.br, temp.obaveza);
	

	BrojObaveze++;
	
	fclose(fp);
	system("cls");
}
 
void* ucitaj() {
	FILE* fpp = NULL;
	fpp = fopen(datoteka,"r");
	if (fpp == NULL) {
		perror("Ucitavanje obaveza error");
		exit(EXIT_FAILURE);
	}

	fread(&BrojObaveze, sizeof(int), 1, fpp);
	printf("\nBroj obaveza unesenih: %d\n",BrojObaveze);
	
	OBAVEZE* PoljeObaveza = (OBAVEZE*)calloc(BrojObaveze, sizeof(OBAVEZE));
	if (PoljeObaveza == NULL) {
		perror("Problem kod zauzimanja memorije za polje obaveza");
		exit(EXIT_FAILURE);
	}

	fread(PoljeObaveza,sizeof(OBAVEZE),BrojObaveze,fpp);
	return PoljeObaveza;
	fclose(fpp);
}

void prikaz() {
	system("cls");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");

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

void IzbrisiDatoteku() {
	
	char YesNo;
	

	do {
		printf("\nJeste li sigurni da zelite izbrisati postojecu listu, te stvoriti novu? y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {
		FILE* fp = NULL;
		fp = fopen(datoteka, "w");

		if (fp == NULL) {
			perror("Problem kod brisanja datoteke");
		}
		fclose(fp);
	}
	system("cls");
}

void kalendar() {
	system("cls");

	int godina;
	printf("\nUnos godine: ");
	scanf("%d", &godina);


	system("pause");
	system("cls");

}