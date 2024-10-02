#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


void clear();
int main()
{
    typedef struct
    {
        int length;
        char columnName[50];

    }STRING;

    typedef struct
    {
        int upperLimit;
        int lowerLimit;
        char columnName[50];

    }INTIGER;

    typedef struct
    {
        char columnName[50];

    }BOOLEAN;

    typedef struct
    {
        float upperLimit;
        float lowerLimit;
        char columnName[50];

    }DECIMAL;

    char inputChar;
    char tableName[50];
    int rowsNumber=0;
    int columnNumber=0;

    srand(time(NULL));

    int stringNumber=0;
    STRING * stringArray = (STRING *)malloc(sizeof(STRING));

    int intigerNumber=0;
    INTIGER * intigerArray = (INTIGER *)malloc(sizeof(INTIGER));

    int booleanNumber=0;
    BOOLEAN * booleanArray = (BOOLEAN *)malloc(sizeof(BOOLEAN));

    int decimalNumber=0;
    DECIMAL * decimalArray = (DECIMAL * )malloc(sizeof(DECIMAL));

    printf("Enter the name of a table: ");
    scanf("%s", tableName);
    clear();

    do
    {
        do
        {
            printf("ADD COLUMN\n\n");
            printf("1 - string\n");
            printf("2 - intiger\n");
            printf("3 - boolean\n");
            printf("4 - decimal (float or double)\n\n");
            printf("q - end\n\n");
            scanf(" %c", &inputChar);
            clear();
        }while(inputChar!='1' && inputChar!='2' && inputChar!='3' && inputChar!='4' && inputChar != 'q' && inputChar != 'Q');

        if(inputChar == '1')
        {
            columnNumber++;
            stringArray = (STRING *)realloc(stringArray, sizeof(STRING) * (stringNumber+1));
            printf("Enter the name of a column: ");
            scanf("%s", stringArray[stringNumber].columnName);
            clear();

            printf("Enter the length of a columns: ");
            scanf("%d", &stringArray[stringNumber].length);
            clear();

            stringNumber++;
        }
        else if(inputChar == '2')
        {
            columnNumber++;
            intigerArray = (INTIGER *)realloc(intigerArray, sizeof(INTIGER) * (intigerNumber+1));
            printf("Enter the name of a column: ");
            scanf("%s", intigerArray[intigerNumber].columnName);
            clear();

            printf("Enter the lower limit of a number: ");
            scanf("%d", &intigerArray[intigerNumber].lowerLimit);
            clear();

            printf("Enter the upper limit of a number: ");
            scanf("%d", &intigerArray[intigerNumber].upperLimit);
            clear();

            intigerNumber++;
        }
        else if(inputChar == '3')
        {
            columnNumber++;
            booleanArray = (BOOLEAN *)realloc(booleanArray, sizeof(BOOLEAN) * (booleanNumber+1));
            printf("Enter the name of a column: ");
            scanf("%s", booleanArray[booleanNumber].columnName);
            clear();

            booleanNumber++;
        }
        else if(inputChar == '4')
        {
            columnNumber++;
            decimalArray = (DECIMAL *)realloc(decimalArray, sizeof(DECIMAL) * (decimalNumber+1));
            printf("Enter the name of a column: ");
            scanf("%s", decimalArray[decimalNumber].columnName);
            clear();

            printf("Enter the lower limit of a number: ");
            scanf("%f", &decimalArray[decimalNumber].lowerLimit);
            clear();

            printf("Enter the upper limit of a number: ");
            scanf("%f", &decimalArray[decimalNumber].upperLimit);
            clear();

            decimalNumber++;
        }

    }while(inputChar != 'q' && inputChar != 'Q');

    printf("Enter the number of records (rows) you want to insert: ");
    scanf("%d", &rowsNumber);
    clear();

    int counter=0;
    FILE * file;
    file = fopen("script.sql", "w");
    if(file == NULL)
    {
        printf("Something went wrong with creating script.sql");
    }

    printf("CREATING script.sql.\n");
    fprintf(file, "INSERT INTO %s(", tableName);
    for (int i = 0; i < stringNumber; i++)
    {
        counter++;
        fprintf(file, "%s", stringArray[i].columnName);
        if(counter != columnNumber)
        {
            fprintf(file, ", ");
        }
    }

    for (int i = 0; i < intigerNumber; i++)
    {
        counter++;
        fprintf(file, "%s", intigerArray[i].columnName);
        if(counter != columnNumber)
        {
            fprintf(file, ", ");
        }
    }

    for (int i = 0; i < booleanNumber; i++)
    {
        counter++;
        fprintf(file, "%s", booleanArray[i].columnName);
        if(counter != columnNumber)
        {
            fprintf(file, ", ");
        }
    }

    for (int i = 0; i < decimalNumber; i++)
    {
        counter++;
        fprintf(file, "%s", decimalArray[i].columnName);
        if(counter != columnNumber)
        {
            fprintf(file, ", ");
        }
    }
    counter = 0;
    fprintf(file, ")\n");


    fprintf(file, "VALUES\n");
    for (int i = 0; i < rowsNumber; i++)
    {
        counter = 0;
        fprintf(file, "(");
        for (int j = 0; j < stringNumber; j++)
        {
            counter++;
            int length = stringArray[j].length;
            char * word = malloc(sizeof(char) * (length+1));
            for (int k = 0; k < length; k++)
            {
                word[k] = rand()%(126-40+1)+40;
            }
            word[length] = '\0';
            fprintf(file, "'%s'", word);
            if(counter != columnNumber)
            {
                fprintf(file, ", ");
            }

            free(word);
        }

        for (int j = 0; j < intigerNumber; j++)
        {
            counter++;
            int number = rand()%(intigerArray[j].upperLimit-intigerArray[j].lowerLimit+1)+intigerArray[j].lowerLimit;
            fprintf(file, "%d", number);
            if(counter != columnNumber)
            {
                fprintf(file, ", ");
            }
        }

        for (int j = 0; j < booleanNumber; j++)
        {
            counter++;
            int number = rand()%(1-0+1)+0;
            fprintf(file, "%d", number);
            if(counter != columnNumber)
            {
                fprintf(file, ", ");
            }
        }

        for (int j = 0; j < decimalNumber; j++)
        {
            counter++;
            float scale = rand() / (float)RAND_MAX;
            float number = decimalArray[j].lowerLimit + scale * (decimalArray[j].upperLimit - decimalArray[j].lowerLimit);
            fprintf(file, "%f", number);
            if(counter != columnNumber)
            {
                fprintf(file, ", ");
            }
        }
        fprintf(file, ")");
        if(i+1!=rowsNumber)
        {
            fprintf(file, ",\n");
        }
        else
        {
            fprintf(file, ";");
        }
    }


    fclose(file);
    free(stringArray);
    free(intigerArray);
    free(booleanArray);
    free(decimalArray);
    return 0;
}

void clear()
{

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
