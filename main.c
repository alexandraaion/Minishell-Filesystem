//Ion Alexandra-Gabreila, 331CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"

int main(void)
{
	//variabile care ne ajuta la citirea comenzilor de la tastatura
	char *line = NULL;
	size_t len = 0;
	int lineSize = 0;

	//variabile care ne ajuta la parsarea comenzilor
	char *name;
	char *content;
	char *command;
	int max_depth;
	int min_size;
	int max_size;

	//directorul curent
	Directory *currentDir = NULL;
	//radacina sistemului de fisiere
	Directory *head;
	//lista in care introducem directoarele prin care ne-am plimbat
	Path *Pwd = (Path *)malloc(sizeof(Path));

	//citim comenzile de la stdin
	while (1) {
		//citim o comanda
		lineSize = getline(&line, &len, stdin);
		line[lineSize - 1] = '\0';

		if (strcmp(line, "create fs") == 0) {
			head = (Directory *)malloc(sizeof(Directory));
			Pwd = NULL;
			createFS(&currentDir, &head);
		} else if (strcmp(line, "delete fs") == 0) {
			free(head->parentDir);
			free(head->name);

			free(head);
			break;
		}
		//in functie de ce comanda avem, parsam restul argumentelor
		//si apelam functia corespunzatoare
		command = strtok(line, " ");

		if (strcmp(command, "touch") == 0) {
			name = strtok(NULL, " ");
			content = strtok(NULL, " ");
			touch(&currentDir, name, content);
		} else if (strcmp(command, "mkdir") == 0) {
			name = strtok(NULL, " ");
			mkdir(&currentDir, name);
		} else if (strcmp(command, "ls") == 0) {
			ls(currentDir);
		} else if (strcmp(command, "pwd") == 0) {
			pwd(Pwd);
		} else if (strcmp(command, "cd") == 0) {
			name = strtok(NULL, " ");
			cd(&currentDir, name, &Pwd);
		} else if (strcmp(command, "tree") == 0) {
			//indexul de identare pentru printare
			int index = 0;

			tree(currentDir, index);
		} else if (strcmp(command, "rm") == 0) {
			name = strtok(NULL, " ");
			rm(&currentDir, name);
		} else if (strcmp(command, "rmdir") == 0) {
			name = strtok(NULL, " ");
			rmdir(&currentDir, name);
		} else if (strcmp(command, "find") == 0) {
			max_depth = atoi(strtok(NULL, " "));
			min_size = atoi(strtok(NULL, " "));
			max_size = atoi(strtok(NULL, " "));
			content = strtok(NULL, " ");
			find(max_depth, min_size, max_size, content);
		}
	}

	free(Pwd);

	return 0;
}
