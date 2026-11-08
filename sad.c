#include <stdio.h>     // For printf, fgets, fopen, fprintf, fclose, rename, remove
#include <stdlib.h>    // For exit()
#include <string.h>    // For strtok, strcmp, strlen, strcspn
#include <dirent.h>    // For opendir, readdir, closedir (for 'dir' command)
#include <direct.h>    // Windows-specific: For _chdir() (for 'cd' command)

// --- FUNCTION PROTOTYPES ---
void cmd_dir();
void cmd_new_item(char *args[]);
void cmd_set_content(char *args[]);
void cmd_rename_item(char *args[]);
void cmd_remove_item(char *args[]);
void cmd_cd(char *args[]);

// --- MAIN FUNCTION ---
int main() {
    char input[256];
    char *args[10];

    while (1) {
        printf(">> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) == 0) continue;

        // Parse input into words using strtok
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < 9) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Route commands to their respective functions
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        else if (strcmp(args[0], "dir") == 0) {
            cmd_dir();
        }
        else if (strcmp(args[0], "new-item") == 0) {
            cmd_new_item(args);
        }
        else if (strcmp(args[0], "set-content") == 0) {
            cmd_set_content(args);
        }
        else if (strcmp(args[0], "rename-item") == 0) {
            cmd_rename_item(args);
        }
        else if (strcmp(args[0], "remove-item") == 0) {
            cmd_remove_item(args);
        }
        else if (strcmp(args[0], "cd") == 0) {
            cmd_cd(args);
        }
        else {
            printf("Unknown command: %s\n", args[0]);
        }
    }

    return 0;
}

// --- COMMAND IMPLEMENTATIONS ---

void cmd_dir() {
    DIR *d;
    struct dirent *dir;
    
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        printf("Error opening directory.\n");
    }
}

void cmd_new_item(char *args[]) {
    if (args[1] == NULL) {
        printf("Error: Missing file name. Usage: new-item <filename>\n");
    } else {
        FILE *file = fopen(args[1], "w");
        if (file != NULL) {
            printf("File '%s' created successfully.\n", args[1]);
            fclose(file);
        } else {
            printf("Error: Could not create file '%s'.\n", args[1]);
        }
    }
}

void cmd_set_content(char *args[]) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Missing filename or data. Usage: set-content <filename> <data>\n");
    } else {
        FILE *file = fopen(args[1], "w");
        if (file != NULL) {
            int j = 2;
            while (args[j] != NULL) {
                fprintf(file, "%s", args[j]);
                if (args[j + 1] != NULL) {
                    fprintf(file, " ");
                }
                j++;
            }
            fprintf(file, "\n");
            fclose(file);
            printf("Data written to '%s' successfully.\n", args[1]);
        } else {
            printf("Error: Could not open file '%s' for writing.\n", args[1]);
        }
    }
}

void cmd_rename_item(char *args[]) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: Missing arguments. Usage: rename-item <old_name> <new_name>\n");
    } else {
        if (rename(args[1], args[2]) == 0) {
            printf("Successfully renamed '%s' to '%s'.\n", args[1], args[2]);
        } else {
            printf("Error: Could not rename file.\n");
        }
    }
}

void cmd_remove_item(char *args[]) {
    if (args[1] == NULL) {
        printf("Error: Missing filename. Usage: remove-item <filename>\n");
    } else {
        if (remove(args[1]) == 0) {
            printf("File '%s' deleted successfully.\n", args[1]);
        } else {
            printf("Error: Could not delete file '%s'.\n", args[1]);
        }
    }
}

void cmd_cd(char *args[]) {
    if (args[1] == NULL) {
        printf("Error: Missing path. Usage: cd <directory>\n");
    } else {
        if (_chdir(args[1]) == 0) {
            printf("Directory changed successfully.\n");
        } else {
            printf("Error: Could not change directory to '%s'.\n", args[1]);
        }
    }
}