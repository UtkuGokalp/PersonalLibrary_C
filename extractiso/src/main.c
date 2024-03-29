#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ArraySize(a) (sizeof(a) / sizeof(a[0]))

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

char* get_directory_path(const char* file_path)
{
    const char* file_name = get_file_name(file_path);
    size_t directory_path_length = strlen(file_path) - strlen(file_name) + 1;
    char* directory_path = (char*)calloc(directory_path_length, 1);
    for (size_t i = 0; i < directory_path_length - 1; i++) //-1 to allow for '\0'
    {
        directory_path[i] = file_path[i];
    }
    return directory_path;
}

char* create_string(const char* pieces[], size_t length)
{
    size_t string_length = 0;
    for (size_t i = 0; i < length; i++)
    {
        string_length += strlen(pieces[i]);
    }

    char* string = (char*)calloc(1, string_length + 1);//+1 for '\0'
    for (size_t i = 0; i < length; i++)
    {
        strcat(string, pieces[i]);
    }
    return string;
}

void execute_command(const char* command_pieces[], size_t length)
{
    char* command = create_string(command_pieces, length);
    printf("%s\n", command);
    system(command);
    printf("\n");
    free(command);
}

void handle_mount_directory(const char* directory_path)
{
    struct stat st = { 0 };
    if (stat(directory_path, &st) == -1)
    {
        const char* command_pieces[] = { "mkdir ", directory_path };
        printf("Creating mount directory\n");
        execute_command(command_pieces, ArraySize(command_pieces));
    }
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: extractiso <file_name>\n");
        return EXIT_FAILURE;
    }

    const char* iso_file_path = argv[1];
    const char* iso_file_name = get_file_name(iso_file_path);
    char* parent_path = get_directory_path(iso_file_path);

    //Create mount directory
    const char* directory_path_pieces[] = { parent_path, iso_file_name, "_Mount" };
    char* mount_directory_path = create_string(directory_path_pieces, ArraySize(directory_path_pieces));
    handle_mount_directory(mount_directory_path);

    //Mount
    const char* mount_command_pieces[] = { "sudo mount ", iso_file_path, " ", mount_directory_path };
    printf("Mounting\n");
    execute_command(mount_command_pieces, ArraySize(mount_command_pieces));

    //Copy data to a new (non-mounted) directory
    const char* extract_mount_data_command_pieces[] = { "cp -r ", parent_path, iso_file_name, "_Mount", " ", parent_path, iso_file_name, "_MountData"};
    printf("Extracting mount data\n");
    execute_command(extract_mount_data_command_pieces, ArraySize(extract_mount_data_command_pieces));

    //Change permissions for the extracted data directory
    const char* change_permissions_command_pieces[] = { "chmod +rw ", parent_path, iso_file_name, "_MountData" };
    printf("Changing permissions - Step #1\n");
    execute_command(change_permissions_command_pieces, ArraySize(change_permissions_command_pieces));

    //Change permissions for the directories in the extracted data directory
    const char* change_directory_permissions_in_data_directory_command_pieces[] = { "find ", parent_path, iso_file_name, "_MountData -type d -exec chmod +rw {} +" };
    printf("Changing permissions - Step #2\n");
    execute_command(change_directory_permissions_in_data_directory_command_pieces, ArraySize(change_directory_permissions_in_data_directory_command_pieces));

    //Change permissions for the files in the extracted data directory
    const char* change_file_permissions_in_data_directory_command_pieces[] = { "find ", parent_path, iso_file_name, "_MountData -type f -exec chmod +rw {} +" };
    printf("Changing permissions - Step #3\n");
    execute_command(change_file_permissions_in_data_directory_command_pieces, ArraySize(change_file_permissions_in_data_directory_command_pieces));

    //Unmount the mount directory
    const char* unmount_command_pieces[] = { "sudo umount ", mount_directory_path };
    printf("Unmounting mount directory\n");
    execute_command(unmount_command_pieces, ArraySize(unmount_command_pieces));

    //Remove mount directory
    const char* remove_mount_dir_command_pieces[] = { "rmdir ", mount_directory_path };
    printf("Deleting mount directory\n");
    execute_command(remove_mount_dir_command_pieces, ArraySize(remove_mount_dir_command_pieces));

    free(mount_directory_path);
    free(parent_path);
    return EXIT_SUCCESS;
}