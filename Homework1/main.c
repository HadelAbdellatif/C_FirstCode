#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct aword
{
    char word[25];
    char meaning[100];
} WORD;

int read(FILE *fp, WORD dict[])
{
    char c = fgetc(fp);
    int wCount=-1;
    while (c != EOF)
    {
        if(c>='0' && c<='9')
        {
            // do nothing
        }
        else if(c == '.')
        {
            wCount++;
        }
        else if(c == '\t' || c == ' ')
        {
            // do nothing
        }
        else
        {
            int i=0;
            while(c!=EOF && c!=':')
            {
                if(c != ' ')
                    dict[wCount].word[i++] = c;
                c = fgetc(fp);
            }
            dict[wCount].word[i] = '\0';
            i=0;
            while(c!=EOF && !(c>='0' && c<='9'))
            {
                dict[wCount].meaning[i++] = c;
                c = fgetc(fp);
            }
            dict[wCount].word[i] = '\0';
        }
        if(c!=EOF)
            c = fgetc(fp);
    }
    return wCount;
}

void search(WORD dict[], char word[], int wc)
{
    for(int i=0; i<=wc; i++)
    {
        if(!strcmp(dict[i].word, word))
        {
            printf("Found:\n");
            printf("%s%s\n", dict[i].word, dict[i].meaning);
            return;
        }
    }
    printf("Word \'%s\' not found in the dictionary!\n", word);
}

void searchC(WORD dict[], char c, int wc)
{
    int notFound = 1;
    for(int i=0; i<=wc; i++)
    {
        if(dict[i].word[0] == c)
        {
            notFound = 0;
            printf("%s%s\n", dict[i].word, dict[i].meaning);
        }
    }
    if(notFound)
        printf("No word starting with character \'%c\' found!\n", c);
}

void save(FILE *fp, WORD dict[], int initialwc, int wc)
{
    for(int i=initialwc; i<=wc; i++)
    {
        fprintf(fp, "\t%d. %s: %s\t", i+1, dict[i].word, dict[i].meaning);
    }
}

int main()
{
    FILE *fp;
    int choice, wordCount=0, initialWordCount;
    WORD dict[1000];
    char tword[25], tmeaning[100], tc;
    while(1)
    {
        printf("Please select an option\n  1-Read File and build the dictionary\n  2-Search for a specific word\n  3-Search for all words that start with a character\n  4-Insert new word to the dictionary\n  5-Save the dictionary back to the file\n  6-Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fp = fopen("inputWords.txt", "r");
            if(fp == NULL)
            {
                printf("Cannot open file!\n");
                exit(0);
            }
            wordCount = read(fp, dict);
            initialWordCount = wordCount + 1;
            fclose(fp);
            break;

        case 2:
            printf("Enter the word to be searched: ");
            scanf("%s", tword);
            search(dict, tword, wordCount);
            break;

        case 3:
            printf("Enter the char to search for all the words starting with that character: ");
            scanf("%s", &tc);
            searchC(dict, tc, wordCount);
            break;

        case 4:
            printf("Enter the word to be inserted: ");
            scanf("%s", tword);
            printf("Enter its meaning: ");
            scanf("\n%[^\n]%*c", tmeaning);
            strcpy(dict[++wordCount].word, tword);
            strcpy(dict[wordCount].meaning, tmeaning);
            break;

        case 5:
            fp = fopen("inputWords.txt", "a");
            if(fp == NULL)
            {
                printf("Cannot open file!\n");
                exit(0);
            }
            save(fp, dict, initialWordCount, wordCount);
            fclose(fp);
            break;

        case 6:
            exit(0);

        default:
            break;
        }
    }
}
