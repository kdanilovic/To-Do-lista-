#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

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
			IzbrisiObavezu(PoljeObaveza, broj);
			break;
		case 3:
			UrediObavezu(PoljeObaveza, broj);
			break;
		case 4:
			prikaz();
			break;
		case 5:
			kalendar();
			break;
		case 6:
			IzbrisiDatoteku();
			break;
		case 7:
			system("cls");
			printf("\t\t\t\t\t\tIzlazenje iz programa!\n\n\n");
			free(PoljeObaveza);
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

	FILE* mapa2 = NULL;
	mapa2 = fopen("br.txt", "a");

	if (mapa2 == NULL) {
		perror("Problem: ");
		exit(EXIT_FAILURE);
	}
	fclose(mapa2);
}


int BrojacDat() {
	int br = 0;
	FILE* Brf = NULL;

	Brf = fopen("br.txt", "r+");
	if (Brf == NULL) {
		perror("Problem kod stvaranje datoteke za brojac");
	}


	fscanf(Brf, "%d", &br);
	fclose(Brf);
	return br;
}

void dodaj() {
	system("cls");

	FILE* fp = NULL;
	fp = fopen(datoteka, "a");

	if (fp == NULL) {
		perror("dodavanje obaveza error");
		exit(EXIT_FAILURE);

	}



	BrObaveze = BrojacDat();

	BrObaveze++;
	printf("\nUnosite obavezu broj %d.", BrObaveze);

	FILE* x = NULL;
	x = fopen("br.txt", "r+");
	if (x == NULL) {
		perror("Zapisivanje u br.txt error");
	}
	rewind(x);
	fprintf(x, "%d", BrObaveze);
	fclose(x);


	printf("\nUnesite obavezu: ");
	char obaveza[200];
	getchar();
	scanf("%199[^\n]", obaveza);
	fprintf(fp, "%d. %s\n\n", BrObaveze, obaveza);


	fclose(x);
	fclose(fp);
	system("cls");
}



void prikaz() {
	system("cls");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");

	if (fp == NULL) {
		perror("citanje obaveza error");
	}


	else {


		char c;
		c = fgetc(fp);
		while (c != EOF) {
			printf("%c", c);
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
	fprintf(x, "%d", 0);
	fclose(x);
	system("cls");
}



OBAVEZE* zauzimanje(int broj) {
	OBAVEZE* polje = NULL;
	polje = (OBAVEZE*)calloc(broj, sizeof(OBAVEZE));
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
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		perror("otvaranje datoteke kod unosa podataka u polje");
	}



	int i;
	for (i = 0; i < broj; i++) {
		fscanf(fp, "%d%*c %199[^\n]", &(ob + i)->br, (ob + i)->obaveza);
	}




	fclose(fp);
}

void IzbrisiObavezu(OBAVEZE* p, int broj) {
	int num, i;
	char YesNo;
	system("cls");

	do {
		printf("\nJeste li sigurni da zelite izbrisati obavezu, pritisnite n za povratak! y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {
		system("cls");
		FILE* pp = NULL;
		pp = fopen(datoteka, "r");
		if (pp == NULL) {
			perror("Problem kod citanja sadrzaja datoteke");
		}
		else {
			printf("\n\n");
			char c;
			c = fgetc(pp);
			while (c != EOF) {
				printf("%c", c);
				c = fgetc(pp);
			}

			fseek(pp, 0, SEEK_END);
			int size = ftell(pp);
			if (size == 0) {
				printf("\nNema unesenih obaveza! Probajte upisati koju obavezu..");
			}

			fclose(pp);

			if (size != 0) {
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
					(p + i)->br = i + 1;
					fprintf(np, "%d. %s\n\n", (p + i)->br, (p + i)->obaveza);
				}
				fclose(np);
				system("cls");
			}
			if (size == 0) {
				printf("\n");
				system("pause");
			}
		}
		system("cls");
	}
	system("cls");
}

void UrediObavezu(OBAVEZE* p, int broj) {
	system("cls");
	char YesNo;
	do {
		printf("\nJeste li sigurni da zelite urediti obavezu, pritisnite n za povratak! y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {

		int ObavezaBr;
		char NovaObaveza[200];
		system("cls");
		if (broj != 0) {


			prikaz();


			do {
				printf("\n\nUnesite broj obaveze koji zelite urediti: ");
				scanf("%d", &ObavezaBr);
				if (ObavezaBr > broj || ObavezaBr <= 0) {
					printf("\nNema obaveze pod tim brojem!\n");
				}
			} while (ObavezaBr > broj || ObavezaBr <= 0);

			ObavezaBr--;
			printf("\nPreuredite obavezu: %d. %s\n", (p + ObavezaBr)->br, (p + ObavezaBr)->obaveza);
			getchar();
			scanf("%199[^\n]", &NovaObaveza);

			strcpy((p + ObavezaBr)->obaveza, NovaObaveza);

			int i;
			FILE* np = NULL;
			np = fopen(datoteka, "w+");
			if (np == NULL) {
				exit(EXIT_FAILURE);
			}

			for (i = 0; i < broj; i++) {
				(p + i)->br = i + 1;
				fprintf(np, "%d. %s\n\n", (p + i)->br, (p + i)->obaveza);
			}

			fclose(np);
			prikaz();


		}
		else {
			printf("\nNema unesenih obaveza!\n");
			system("pause");
		}
	}
	system("cls");
}

void kalendar() {
	system("cls");
	int godina, dan, mj;
	int dani_u_mjesecu[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	char* mjeseci[] =
	{
		" ",
		"\n\n\nSijecanj",
		"\n\n\nVeljaca",
		"\n\n\nOzujak",
		"\n\n\nTravanj",
		"\n\n\nSvibanj",
		"\n\n\nLipanj",
		"\n\n\nSrpanj",
		"\n\n\nKolovoz",
		"\n\n\nRujan",
		"\n\n\nListopad",
		"\n\n\nStudeni",
		"\n\n\nProsinac"
	};


	do {
		printf("\nUnos godine: ");
		scanf("%d", &godina);
	} while (godina <= 0);


	int PrviDan;
	PrviDan = ((godina + (godina - 1) / 4 - (godina - 1) / 100 + (godina - 1) / 400) % 7);

	if (godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0) {
		dani_u_mjesecu[2] = 29;
	}


	for (mj = 1; mj <= 12;mj++) {
		printf("%s", mjeseci[mj]);
		printf("\n\nPon  Uto  Sri  Cet  Pet  Sub  Ned\n");

		for (dan = 1;dan <= 1 + PrviDan * 5; dan++) {
			printf(" ");
		}

		for (dan = 1;dan <= dani_u_mjesecu[mj]; dan++) {
			printf("%2d", dan);

			if ((dan + PrviDan) % 7 > 0)
				printf("   ");
			else
				printf("\n ");

		}
		PrviDan = (PrviDan + dani_u_mjesecu[mj]) % 7;
	}

	printf("\n\n");
	system("pause");
	system("cls");
}