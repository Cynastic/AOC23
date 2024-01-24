#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int getDigit(char* str)
{
    char digits[][6] = {{"0"}, {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, 
    {"one"}, {"two"}, {"three"}, {"four"}, {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

    for(int i = 0; i < 19; i++)
    {
        if(strcmp(str, digits[i]) == 0)
        {
            if(i < 10) return i;
            else return i - 9;
        }
    }
    return -1;
}

int main()
{
    FILE* inputFile = fopen("input.txt", "r");
    if(inputFile == NULL)
    {
        printf("File could not be opened.\n");
        return -1;
    }

    char* currentLine = malloc(sizeof(char) * 100);
    int sumOfDigits = 0;
    while(fscanf(inputFile, "%s", currentLine) > 0)
    {
        int firstDigit = -1;

        for(int startIndex = 0; startIndex < strlen(currentLine); startIndex++)
        {
            for(int endIndex = startIndex; endIndex < strlen(currentLine); endIndex++)
            {
                char* currentCheck = malloc(sizeof(char) * (endIndex - startIndex));
                for(int curChar = startIndex; curChar <= endIndex; curChar++)
                {
                    currentCheck[curChar - startIndex] = currentLine[curChar];
                }
                currentCheck[endIndex - startIndex + 1] = '\0';
                if(getDigit(currentCheck) != -1) 
                {
                    firstDigit = getDigit(currentCheck);
                    break;
                }
            }
            if(firstDigit != -1) break;
        }


        int secondDigit = -1;
        for(int endIndex = strlen(currentLine) - 1; endIndex >= 0; endIndex--)
        {
            for(int startIndex = endIndex; startIndex >= 0; startIndex--)
            {
                char* currentCheck = malloc(sizeof(char) * (endIndex - startIndex));
                for(int curChar = startIndex; curChar <= endIndex; curChar++)
                {
                    currentCheck[curChar - startIndex] = currentLine[curChar];
                }
                currentCheck[endIndex - startIndex + 1] = '\0';
                if(getDigit(currentCheck) != -1)
                {
                    secondDigit = getDigit(currentCheck);
                    break;
                }
            }
            if(secondDigit != -1) break;
        }
        sumOfDigits += firstDigit * 10;
        sumOfDigits += secondDigit;
    } 
    printf("%d\n", sumOfDigits);
    return 0;
}
