#include "tests.h"


void debug_files(t_file *file_list)
{
    while (file_list)
    {
        printf("File:\n");
        if (file_list->read)
            printf("  Read: %s\n", file_list->read);
        if (file_list->write)
            printf("  Write: %s\n", file_list->write);
        printf("  Delimiter: %d\n", file_list->delimiter);
        file_list = file_list->next;
    }
}

void debug_commands(t_cmd *cmd_list)
{
    int cmd_num = 1;

    while (cmd_list)
    {
        printf("Command %d:\n", cmd_num++);
        if (cmd_list->input)
            printf("  Input: %s\n", cmd_list->input);
        if (cmd_list->file)
        {
            printf("  Files:\n");
            debug_files(cmd_list->file);
        }
        else
        {
            printf("  No files associated.\n");
        }
        cmd_list = cmd_list->next;
    }
}