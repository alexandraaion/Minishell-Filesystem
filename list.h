//Ion Alexandra-Gabreila, 331CC
#ifndef __LIST_H__
#define __LIST_H__

#include "file.h"

void createFS(Directory * *currentDir, Directory * *head);
void deleteFS(void);
void touch(Directory **currentDir, char *filename, char *content);
void mkdir(Directory **currentDir, char *dirname);
void ls(Directory *currentDir);
void pwd(Path *pwd);
void cd(Directory **currentDir, char *dirname, Path **pwd);
void tree(Directory *currentDir, int index);
void rm(Directory **currentDir, char *filename);
void rmdir(Directory **currentDir, char *dirname);
void find(int max_depth, int min_size, int max_size, char *subcontent);


#endif /* __LIST_H__ */
