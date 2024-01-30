#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int getDigit(char* str)
{
    int n = strlen(str);
    int ret = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        ret += (str[i] - 48) * (int)pow(10, (double)(n - i - 1));
    }
    return ret;
}

int getGameID(char* str)
{
    int n = strlen(str);
    int index = 0;
    while(str[index] != ' ')
    {
        index++;
    }
    char idAsString[5];
    for(int i = 1; i < strlen(str) - index; i++)
    {
        idAsString[i-1] = str[i + index];
    }
    idAsString[strlen(str) - index] = '\0';
    return getDigit(idAsString);
}

int main()
{
    FILE* inputFile = fopen("input2.txt", "r");
    if(inputFile == NULL) 
    {
        printf("Couldn't open input File\n");
        return -1;
    }

    int sumOfId = 0;
    int sumOfPowers = 0;
    char currentLine[400];
    while(fgets(currentLine, 400, inputFile) != NULL)
    {
        char* currentPart = strtok(currentLine, ",;:\n");
        int gameID = getGameID(currentPart);
        bool addToSum = true;

        int redMax = 0;
        int blueMax = 0;
        int greenMax = 0;
        int powerOfSet = 0;

        currentPart = strtok(NULL, ",;:\n");
        while(currentPart != NULL)
        {
            char* amountAsString = malloc(sizeof(char) * 4);
            int i = 1;
            while(currentPart[i] != ' ')
            {
                amountAsString[i-1] = currentPart[i];
                i++;
            }
            amountAsString[i-1] = '\0';
            int amount = getDigit(amountAsString);

            switch(currentPart[i + 1])
            {
                case 'r':
                    if(amount > 12) addToSum = false;
                    if(amount > redMax) redMax = amount;
                    break;
                case 'g':
                    if(amount > 13) addToSum = false;
                    if(amount > greenMax) greenMax = amount;
                    break;
                case 'b':
                    if(amount > 14) addToSum = false;
                    if(amount > blueMax) blueMax = amount;
                    break;
            }

            currentPart = strtok(NULL, ",;:\n");
        }
        if(addToSum == true)
        {
            sumOfId += gameID;
        }
        powerOfSet = redMax * blueMax * greenMax;
        sumOfPowers += powerOfSet;
    }
    printf("Sum of valid IDs: %d\n", sumOfId);
    printf("Sum of Powers: %d\n", sumOfPowers);
    fclose(inputFile);
    return 0;
}
