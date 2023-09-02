#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//set up this dynamically after getting it working normally
#define MAX_LINE_LENGTH 100
#define MAX_SPELLING_WORDS 50
#define MAX_WORD_LENGTH 20

/* This is the standard input file
 * 
 * description : word
 * This:Works
 * This: Aswell
 * Not this    :   Though
 *
 * The EOF should be at the end of the line of the last line
 */

char *removeExtraChars(char *string){
    //check if the last character is blank
    if((string[strlen(string) - 1] == ' ') || (string[strlen(string) - 1] == '\n')){
        string[strlen(string) - 1] = '\0';
    }
    
    return string;
}


int main(int argc, char**argv){

    
    
    FILE *spellingList;
    
    char line[MAX_LINE_LENGTH];
    char *fileName;

    const char *words[MAX_SPELLING_WORDS];
    const char *definitions[MAX_SPELLING_WORDS];

    printf("\x1b[28;39m\nInput the full file name of the spelling test file: ");
   
    //test if macro expansion would work like this
    scanf("%ms", &fileName);

    spellingList = fopen(fileName, "r");

    if(!spellingList){
        printf("\n %s could not be opened",fileName);
        return -1;
    }

    int totalFLines = 0;

    while(fgets(line,MAX_LINE_LENGTH,spellingList) != NULL){

        char *tempLine;
        tempLine = (char*)malloc(strlen(line));
        strcpy(tempLine, line);

        //divide the description from the spelling word
        char *divider = strtok(tempLine, ":");
        

        char *description = removeExtraChars(divider);

        definitions[totalFLines] = description;
        
        //get the word the second token
        divider = strtok(NULL, ":");
        
        //remove the newline character at the end 
       
        
        if(divider[0] == ' '){
            int i;
            for(i = 1; i < strlen(divider); i++){
                divider[i-1] = divider[i];
            }
            divider[strlen(divider) - 1] = '\0';
        }

        words[totalFLines] = removeExtraChars(divider);
        
        totalFLines++; 
    }

    char option;

    srand(time(NULL));

    while(option !=  'q'){
    //randomize the list using the fisher-yates shuffle algorithm
    //before serving to the user
    for(int a = totalFLines  -1; a >= 0; a--){
        int num = rand() % (a+1);

        //shuffle the words
        const char *tempw = words[a];
        words[a] = words[num];
        words[num] = tempw;

        //shuffle the descriptions
        const char *tempd = definitions[a];
        definitions[a] = definitions[num];
        definitions[num] = tempd;

    }
    for(int i = 0; i < totalFLines; i++){
        char *guess;
        printf("\nDescription: %s Answer: ", definitions[i]);
        scanf("%ms", &guess);

        if(strcmp(guess,words[i]) == 0){
            //set up ascii escape codes to color the output
            printf("\n\x1b[32mCorrect!\x1b[0m");
        }else {
            printf("\n\x1b[31mIncorrect!\x1b[0m your answer was \x1b[31m%s\x1b[0m instead of \x1b[32m%s\x1b[0m", guess, words[i]);
    } 
    }
       printf("\ntype q quit otherwise type any character to play another round: ");
       scanf(" %c", &option); 

    }

    //place in a loop to the user can test themselves over and over again
    return 0;
}

