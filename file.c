//Ion Alexandra-Gabreila, 331CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"

//functia insereaza un fisier cu numele filename si continutul content
//in lista de fisiere a directorului currentDir
void insertFile(Directory **currentDir, char *filename, char *content)
{
	//lista de fisiere a directorului
	ListOfFile *list = (*currentDir)->fileList;

	//cream o noua intrare in lista de fisiere pe care vedem unde o inseram
	File *aux = (File *)malloc(sizeof(File));

	aux->name = malloc(sizeof(strlen(filename)));
	strcpy(aux->name, filename);
	aux->data = content;
	aux->dir = *currentDir;
	aux->size = strlen(content);
	ListOfFile *listAux = (ListOfFile *)malloc(sizeof(ListOfFile));

	listAux->file = aux;
	listAux->nextFile = NULL;

	//daca lista de fisiere e nula
	if (list == NULL) {
		(*currentDir)->fileList = listAux;
		return;
	}
	ListOfFile *lista = list;	//lista de fisiere ale dir curent
	File *current = lista->file;

	//inserare la inceput in lista de fisiere
	if (strcmp(current->name, filename) > 0) {
		listAux->nextFile = lista;
		(*currentDir)->fileList = listAux;
		return;
	}

	//inserare dupa un element dat, retinut in list
	while (lista->nextFile != NULL &&
	strcmp(lista->nextFile->file->name, filename) < 0)
		lista = lista->nextFile;
	listAux->nextFile =  lista->nextFile;
	lista->nextFile = listAux;
	return;

}

//functia sterge fisierul cu numele filename din lista de fisiere a
//directorului currentDir
void deleteFile(Directory **currentDir, char *filename)
{
	ListOfFile *auxList = (*currentDir)->fileList;

	//daca lista de fisiere este goala
	if (auxList == NULL) {
		printf("Cannot remove '%s': No such file!\n", filename);
		return;
	}
	File *current = auxList->file;

	//daca trebuie sa stergem primul fisier
	if (strcmp(current->name, filename) == 0) {
		ListOfFile *aux = auxList->nextFile;
		(*currentDir)->fileList = aux;

		free(auxList);
		return;
	}

	ListOfFile *prevList = auxList;

	auxList = auxList->nextFile;
	current = auxList->file;

	while (auxList != NULL) {
		current = auxList->file;
		if (strcmp(current->name, filename) == 0) {
			prevList->nextFile = auxList->nextFile;

			free(auxList);
			return;
		}
		prevList = auxList;
		auxList = auxList->nextFile;
	}
	printf("Cannot remove '%s': No such file!\n", filename);
}

//functia insereaza un director cu numele dirname
//in lista de directoare a directorului currentDir
void insertDirectory(Directory **currentDir, char *dirname)
{
	//lista de directoare a directorului curent
	ListOfDir *list = (*currentDir)->dirList;

	//cream o noua intrare in lista de dir pe care vedem unde o inseram
	Directory *aux = (Directory *)malloc(sizeof(Directory));

	aux->name = malloc(sizeof(strlen(dirname)));
	strcpy(aux->name, dirname);
	aux->parentDir = *currentDir;
	aux->fileList = NULL;
	aux->dirList = NULL;
	ListOfDir *listAux = (ListOfDir *)malloc(sizeof(ListOfDir));

	listAux->dir = aux;
	listAux->nextDir = NULL;
	listAux->prevDir = NULL;

	//daca lista de directoare e nula
	if (list == NULL) {
		(*currentDir)->dirList = listAux;

		return;
	}

	ListOfDir *lista = list;  //lista de directoare ale dir curent
	Directory *current = lista->dir;

	//inserare la inceput in lista de directoare
	if (strcmp(current->name, dirname) > 0) {
		listAux->nextDir = lista;
		lista->prevDir = listAux;
		(*currentDir)->dirList = listAux;
		return;
	}

	//inserare dupa un element dat, retinut in lista
	while (lista->nextDir != NULL
	&& strcmp(lista->nextDir->dir->name, dirname) < 0)
		lista = lista->nextDir;

	listAux->nextDir =  lista->nextDir;
	listAux->prevDir = lista;

	//daca nu il introducem la final
	if (lista->nextDir != NULL)
		lista->nextDir->prevDir = listAux;
	lista->nextDir = listAux;


}

//functia sterge directorul cu numele dirname din lista de directoare a
//directorului currentDir
void deleteDirectory(Directory **currentDir, char *dirname)
{
	//lista de directoare a directorului curent
	ListOfDir *auxList = (*currentDir)->dirList;

	//daca lista de directoare e goala
	if (auxList == NULL) {
		printf("Cannot remove '%s': No such directory!\n", dirname);
	return;
	}
	Directory *current = auxList->dir;

	//daca trebuie sa stergem primul director
	if (strcmp(current->name, dirname) == 0) {
		//daca e singurul director
		if (auxList->nextDir == NULL) {
			(*currentDir)->dirList = NULL;

			free(auxList);
			return;
		}

		auxList->nextDir->prevDir = NULL;
		(*currentDir)->dirList = auxList->nextDir;

		free(auxList);
		return;
	}

	ListOfDir *prev = auxList;

	auxList = auxList->nextDir;
	current = auxList->dir;

	while (auxList != NULL) {
		current = auxList->dir;
		if (strcmp(current->name, dirname) == 0) {
			//daca stergem ultimul element
			if (auxList->nextDir == NULL) {
				auxList->prevDir->nextDir = NULL;
				free(auxList);
				return;
			}

			prev->nextDir = auxList->nextDir;

			free(auxList);
			return;
		}
		prev = auxList;
		auxList = auxList->nextDir;
	}
	printf("Cannot remove '%s': No such directory!\n", dirname);
}

//functia insereaza numele unui director in lista caii relative pana la
//directorul curent
void insert(Path **pwd, char *dirname)
{
	Path *new = (Path *)malloc(sizeof(Path));

	new->name = malloc(30);
	strcpy(new->name, dirname);
	new->next = NULL;

	//daca lista e goala
	if (*pwd == NULL) {
		*pwd = new;
		return;
	}

	Path *aux = *pwd;

	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;

}

//functia sterge numele unui director din lista caii relative pana la
//directorul curent
void delete(Path **pwd)
{
	Path *aux = *pwd;

	//daca lista are doar un singur element
	if (aux->next == NULL) {
		*pwd = NULL;
		return;
	}
	Path *prev = aux;

	aux = aux->next;

	while (aux->next != NULL) {
		prev = aux;
		aux = aux->next;
	}
	prev->next = NULL;
}
