//Ion Alexandra-Gabreila, 331CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"

//functia creeaza radacina sistemului de fisiere
void createFS(Directory **currentDir, Directory **head)
{
	(*head)->dirList = NULL;
	(*head)->fileList = NULL;
	(*head)->name = malloc(sizeof(strlen("/")));
	strcpy((*head)->name, "/");
	(*head)->parentDir = NULL;

	*currentDir = *head;
}

//functia creeaza fisierul cu numele filename si continutul content
//in directorul currentDir
void touch(Directory **currentDir, char *filename, char *content)
{
	insertFile(currentDir, filename, content);
}

//functia creeaza directorul cu numele dirname in directorul currentDir
void mkdir(Directory **currentDir, char *dirname)
{
	insertDirectory(currentDir, dirname);
}

//functia printeaza fisierele si directoarele din currentDir
void ls(Directory *currentDir)
{
	//daca directorul este gol
	if (currentDir->fileList == NULL && currentDir->dirList == NULL) {
		printf("\n");
	} else {
		//daca directorul contine fisiere, iteram prin ele si le printam
		if (currentDir->fileList != NULL) {
			ListOfFile *list = currentDir->fileList;

			while (list->nextFile != NULL) {
				printf("%s ", list->file->name);
				list = list->nextFile;
			}
			printf("%s", list->file->name);
		}
		//daca directorul contine directoare, iteram si le printam
		if (currentDir->dirList != NULL) {
			if (currentDir->fileList != NULL)
				printf(" ");
			ListOfDir *list = currentDir->dirList;

			while (list->nextDir != NULL) {
				printf("%s ", list->dir->name);
				list = list->nextDir;
			}

			if (list != NULL && list->dir != NULL)
				printf("%s", list->dir->name);
		}
		printf("\n");
	}
}

//functia printeaza calea absoluta pana la directorul curent
void pwd(Path *pwd)
{
	Path *aux = pwd;

	//daca lista e goala
	if (aux == NULL) {
		printf("/\n");
	} else {
		// iteram prin elementele ei si le printam separate de "/"
		while (aux != NULL) {
			printf("/");
			printf("%s", aux->name);
			aux = aux->next;
		}
		printf("\n");
	}
}

//functia schimba directorul curent in directorul dirname
//si actualizeaza calea pana la acesta
void cd(Directory **currentDir, char *dirname, Path **pwd)
{
	if (strcmp(dirname, "..") == 0) {
		//ne intoarcem in directorul parinte
		*currentDir = (*currentDir)->parentDir;

		//actualizam path-ul
		delete(pwd);

		return;
	}
	ListOfDir *auxList = (*currentDir)->dirList;

	//daca lista de directoare este goala
	if (auxList == NULL) {
		printf("Cannot move to '%s': No such directory!\n", dirname);

		return;
	}

	Directory *current = auxList->dir;

	//iteram prin lista de directoare pentru a vedea daca gasim directorul
	while (auxList->nextDir != NULL) {
		if (strcmp(current->name, dirname) == 0) {
			*currentDir = current;

			//actualizam path-ul
			insert(pwd, dirname);

			return;
		}
		auxList = auxList->nextDir;
		current = auxList->dir;
	}

	if (strcmp(current->name, dirname) == 0) {
		*currentDir = current;

		//actualizam path-ul
		insert(pwd, dirname);

		return;
	}
	printf("Cannot move to '%s': No such directory!\n", dirname);

}

//functia afiseaza recursiv continutul sistemului de fisiere
void tree(Directory *currentDir, int index)
{
	//afisam directorul
	int i;

	for (i = 0; i < index; i++)
		printf(" ");

	printf("%s\n", currentDir->name);
	index += 4;

	//daca directorul contine fisiere, iteram prin acestea si le printam
	if (currentDir->fileList != 0) {
		ListOfFile *auxListF = currentDir->fileList;

		while (auxListF != NULL) {
			for (i = 0; i < index; i++)
				printf(" ");
			printf("%s\n", auxListF->file->name);
			auxListF = auxListF->nextFile;
		}
	}

	//daca directorul contine directoare, apelam recursiv functia tree
	//pe fiecare director in parte
	if (currentDir->dirList != 0) {
		ListOfDir *auxListD = currentDir->dirList;

		while (auxListD != NULL) {
			tree(auxListD->dir, index);
			auxListD = auxListD->nextDir;
		}
	}

}

//functia sterge un fisier din directorul currentDir
void rm(Directory **currentDir, char *filename)
{
	deleteFile(currentDir, filename);
}

//functia sterge un director din directorul currentDir
void rmdir(Directory **currentDir, char *dirname)
{
	deleteDirectory(currentDir, dirname);
}

void find(int max_depth, int min_size, int max_size, char *subcontent)
{
}
