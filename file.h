//Ion Alexandra-Gabreila, 331CC
#ifndef __FILE_H__
#define __FILE_H__

typedef struct Directory {
	// The name of the directory
	char *name;

	// TODO: The list of files of the current directory
	struct ListOfFile *fileList;

	// TODO: The list of directories of the current directory
	struct ListOfDir *dirList;

	//The parent directory of the current directory (NULL for the root dir)
	struct Directory *parentDir;
} Directory;

// DO NOT MODIFY THIS STRUCTURE
typedef struct File {
	// The name of the file
	char *name;

	// The size of the file
	int size;

	// The content of the file
	char *data;

	// The directory in which the file is located
	Directory *dir;
} File;

typedef struct ListOfDir {
	//current directory
	Directory *dir;

	//next directory
	struct ListOfDir *nextDir;

	//previous directory
	struct ListOfDir *prevDir;
} ListOfDir;

typedef struct ListOfFile {
	//current file
	File *file;

	//next file
	struct ListOfFile *nextFile;

} ListOfFile;

//structura ajutatoare pt pwd
typedef struct Path {
	char *name;
	struct Path *next;
} Path;

void insertFile(Directory **currentDir, char *filename, char *content);
void deleteFile(Directory **currentDir, char *filename);
void insertDirectory(Directory **currentDir, char *dirname);
void deleteDirectory(Directory **currentDir, char *dirname);
void insert(Path **pwd, char *dirname);
void delete(Path **pwd);

#endif /* __FILE_H__ */
