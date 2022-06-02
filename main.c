#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funkcije.h"
#include "struktura.h"



char* datoteka = "to do list.txt";

int BrObaveze;



void naslov();
int izbornik();
void stvori_datoteku();
int BrojacDat();
void dodaj();
void prikaz();
void IzbrisiDatoteku();
OBAVEZE* zauzimanje(int);
void UnosPolje(OBAVEZE*,int);
void IzbrisiObavezu(OBAVEZE*, int);
void UrediObavezu(OBAVEZE*, int broj);


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

		int broj = BrojacDat();
		static OBAVEZE* PoljeObaveza = NULL;
		PoljeObaveza = zauzimanje(broj);
		UnosPolje(PoljeObaveza, broj);

		printf("\n\t\t\t\t\t\t1. Dodaj obavezu\n\n");
		printf("\t\t\t\t\t\t2. Izbrisi obavezu\n\n");
		printf("\t\t\t\t\t\t3. Uredi postojecu obavezu\n\n");
		printf("\t\t\t\t\t\t4. Prikaz obaveza\n\n");
		printf("\t\t\t\t\t\t5. Prikazi kalendar\n\n");
		printf("\t\t\t\t\t\t6. Izbrisi cijelu listu\n\n");
		printf("\t\t\t\t\t\t7. Izadji iz programa\n\n");

		printf("\nOdabir opcije: ");
		scanf("%d", &opcija);
		
		

		
		switch (opcija) {
		case 1:
			dodaj();
			break;
		case 2:
			IzbrisiObavezu(PoljeObaveza,broj);
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
	fclose(mapa);
}


int BrojacDat() {
	int br=0;
	FILE* Brf = NULL;
	
	Brf = fopen("br.txt", "r+");
	if (Brf == NULL) {
		perror("Problem kod stvaranje datoteke za brojac");
	}
	
	
	fscanf(Brf,"%d", &br);
	fclose(Brf);
	return br;
}

void dodaj() {
	system("cls");
	
	FILE* fp = NULL;
	fp = fopen(datoteka,"a");

	if (fp == NULL) {
		perror("dodavanje clanova error");
		exit(EXIT_FAILURE);
		
	}



	BrObaveze = BrojacDat();
	
	BrObaveze++;
	printf("\nBroj iz br.txt : %d", BrObaveze);

	FILE* x = NULL;
	x = fopen("br.txt","r+");
		if (x == NULL) {
			perror("Zapisivanje u br.txt error");
		}
	rewind(x);
	fprintf(x,"%d", BrObaveze);
	fclose(x);

	
	OBAVEZE *temp=NULL;

	temp = (OBAVEZE*)calloc(BrObaveze,sizeof(OBAVEZE));
	if (temp == NULL) {
		return NULL;
	}

	
	
	printf("\nUnesite obavezu: ");
	
	getchar();
	int br2 = BrObaveze;
	BrObaveze--;
	scanf("%199[^\n]", temp[BrObaveze].obaveza);
	printf("%s", temp[BrObaveze].obaveza);
	temp[BrObaveze].br = br2;
	fprintf(fp, "%d. %s\n\n", temp[BrObaveze].br, temp[BrObaveze].obaveza);
	

	   
	fclose(x);
	fclose(fp);
	system("cls");
}
 


void prikaz() {
	system("cls");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");

	if (fp == NULL) {
		perror("citanje clanova error");
	}

	


	else {

		
		char c;
		c = fgetc(fp);
		while (c != EOF) {
			printf("%c",c);
			c = fgetc(fp);
		}

		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		if (size == 0) {
			printf("\nNema unesenih obaveza! Probajte upisati koju obavezu..");
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

	FILE* x = NULL;
	x = fopen("br.txt", "w");
		if (x == NULL) {
			perror("Brisanje br.txt");
		}
	fprintf(x,"%d",0);
	fclose(x);
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

OBAVEZE* zauzimanje(int broj) {
	OBAVEZE* polje = NULL;
	polje = (OBAVEZE*)calloc(broj,sizeof(OBAVEZE));
	if (polje == NULL) {
		return NULL;
		perror("Zauzimanje polja");
	}
	else {
		return polje;
	}

}

void UnosPolje(OBAVEZE* ob, int broj) {
	
	FILE* fp = NULL;
	fp = fopen(datoteka,"r");
	if (fp == NULL) {
		perror("otvaranje datoteke kod unosa podataka u polje");
	}

	

	int i;
	for(i=0; i<broj; i++){
		fscanf(fp, "%d%*c %199[^\n]", &ob[i].br, ob[i].obaveza);
	}




	fclose(fp);
}

void IzbrisiObavezu(OBAVEZE* p, int broj) {
	int num,i;
	char YesNo;
	system("cls");

	do {
		printf("\nJeste li sigurni da zelite izbrisati obavezu, pritisnite n za povratak! y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {

		do {
			printf("\nUnesite broj obaveze koji zelite izbrisati: ");
			scanf("%d", &num);

			if (num > broj || num <= 0) {
				printf("\nNe postoji obaveza pod tim brojem!");
			}
		} while (num > broj || num <= 0);


		for (i = num - 1; i < broj - 1; i++) {
			p[i] = p[i + 1];
		}

		broj--;
		FILE* fp = NULL;
		fp = fopen("br.txt", "r+");
		if (fp == NULL) {
			exit(EXIT_FAILURE);
		}
		rewind(fp);
		fprintf(fp, "%d", broj);
		fclose(fp);



		FILE* np = NULL;
		np = fopen(datoteka, "w+");
		if (np == NULL) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < broj; i++) {
			p[i].br = i + 1;
			fprintf(np, "%d. %s\n\n", p[i].br, p[i].obaveza);
		}
		fclose(np);
		system("cls");
	}
	system("cls");
}

void UrediObavezu(OBAVEZE* p, int broj) {

}