#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char* get_file_name(const char* file_path)
{
    int lastSlashIndex = -1;
    for (int i = 0; i < (int)strlen(file_path); i++)
    {
        if (file_path[i] == '/')
        {
            lastSlashIndex = i;
        }
    }
    if (lastSlashIndex == -1)
    {
        return file_path;
    }
    return (file_path + lastSlashIndex + 1);
}

void handle_directory(const char* directory_path)
{
    struct stat st = { 0 };
    if (stat(directory_path, &st) == -1)
    {
        printf("Creating mount directory\n");
        char* command = (char*)calloc(1, strlen("mkdir ") + strlen(directory_path) + 1);
        strcat(command, "mkdir ");
        strcat(command, directory_path);
        system(command);
        free(command);
    }
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: fmount <file_name>\n");
        return EXIT_FAILURE;
    }

    const char* file_path = argv[1];
    const char* file_name = get_file_name(file_path);
    char* directory_path = (char*)calloc(1, strlen("/home/ugklp/Desktop/") + strlen(file_name) + strlen("_Mount") + 1);
    strcat(directory_path, "/home/ugklp/Desktop/");
    strcat(directory_path, file_name);
    strcat(directory_path, "_Mount");

    //Command: mount file_path directory_path
    char* command = (char*)calloc(1, strlen("sudo mount ") + strlen(file_path) + strlen(" ") + strlen(directory_path) + 1);
    strcat(command, "sudo mount ");
    strcat(command, file_path);
    strcat(command, " ");
    strcat(command, directory_path);

    handle_directory(directory_path);

    printf("Mounting\n");
    system(command);

    free(command);
    free(directory_path);
    return EXIT_SUCCESS;
}