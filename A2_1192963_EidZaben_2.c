/*
*   Eid Zaben
*   1192963
*   Section 4
*/

#include <stdlib.h>
#include <stdio.h>

char line[100];
int len;

int count = 0;
char *lines[100];

char *undone[100];
int undoCount = 0;

void save();
void clearUndo();
void undo();
void redo();
void print();
void addLine(char *words);

void clearUndo()
{
    for (int i = 0; i < 100; i++)
    {
        undone[i] = NULL;
        undoCount = 0;
    }
}

void undo()
{
    if (count > 0)
    {
        undone[undoCount] = lines[count - 1];
        lines[count - 1] = NULL;
        count--;
        undoCount++;
    }
}

void redo()
{
    if (undoCount > 0)
    {
        lines[count] = undone[undoCount - 1];
        undone[undoCount - 1] = NULL;
        undoCount--;
        count++;
    }
}

void print()
{
    for (int i = 0; i < 100; i++)
    {
        if (lines[i] != NULL)
        {
            printf("%s\n", lines[i]);
        }
    }
}

void addLine(char *words)
{
    lines[count] = strdup(words);
    count++;
    clearUndo();
}

void save()
{
    FILE *fPointer;
    fPointer = fopen("output.txt", "w");
    if (lines[0] != NULL)
    {
        fprintf(fPointer, "%s", lines[0]);
    }
    fclose(fPointer);
    if (lines[1] != NULL)
    {
        fPointer = fopen("output.txt", "a");
        for (int i = 1; i < 100; i++)
        {
            if (lines[i] != NULL)
            {
                fprintf(fPointer, "\n%s", lines[i]);
            }
        }
        fclose(fPointer);
    }

    return;
}

int main()
{

    while (strcmp(line, "quit"))
    {
        printf("Enter a special command, text or quit\n");
        printf("Special commands are: undo, redo, print & save\n");

        fgets(line, 100, stdin);

        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        if (!strcmp(line, "undo"))
        {
            undo();
        }
        else if (!strcmp(line, "redo"))
        {
            redo();
        }
        else if (!strcmp(line, "print"))
        {
            print();
        }
        else if (!strcmp(line, "save"))
        {
            save();
        }
        else
        {

            addLine(line);
        }
    }

    printf("Good Bye!\n");
    return 0;
}
