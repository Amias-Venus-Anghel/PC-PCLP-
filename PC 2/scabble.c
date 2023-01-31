#include <stdio.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#include <stdlib.h>
#include <string.h>

void InitBoard(char board[15][15])
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j <15; j++)
            board[i][j] = '.';
}

void ExtractInfo( char word[15],int *line,int *col,int *dir)
{
    char string[30];
    fgets(string, 30, stdin);

    char *token;
    token = strtok(string," ");
    *line = atoi(token);
    
    token = strtok(NULL," ");
    *col = atoi(token);

    token = strtok(NULL," ");
    *dir = atoi(token);

    token = strtok(NULL,"\n");
    strcpy(word, token);
    
}

void ExtractInfoPrime(char XX[4], char YY[4], int *N)
{
    char string[30];
    fgets(string, 30, stdin);
    strcpy(XX, strtok(string,"\n")); //folosesc strtok pt a nu copia si elementul \n in XX 

    strcpy(string,"");
    fgets(string, 30, stdin);
    strcpy(YY,strtok(string,"\n"));

    strcpy(string,"");
    fgets(string, 30, stdin);
    *N = atoi(string);
}

void PlaceWord(char board[15][15], char word[15], int dir, int col, int line)
{ 
    //functie care aseaza cuvantul pe tabla
    if(dir == 0)
        {
            for(unsigned int j = col; j - col < strlen(word); j++)
                board[line][j] = word[j - col];
        }
        else
        {
            for(unsigned int j = line; j - line < strlen(word); j++)
                board[j][col] = word[j - line]; // folosesc contorul pentru a tine minste simultan pozitia si numarul de contor al cuvantului
        }
}

int WordScore(char word[15])
{
    //vector identificare punctajului pt fiecare litera
    int punctaj[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    int scor = 0;
    for(unsigned int i = 0; i < strlen(word); i++)
    {
        scor += punctaj[(int)(word[i] - 'A')];
    }

    return scor;

}

int SubstringCheck(char word[15], char string[4], int where)
{
    //where primeste 1 sau 2 in functie de bonusul pentru care se verifica
    if(where == 1 && strstr(word, string) != NULL )
        return 0;
        
    if(where == 2 && !strcmp(word + strlen(word)-2, string)) 
        return 0;
    // daca cuv nu e eligibil pt bonus se returneaza 1
    return 1;
}

int WordScoreBonus(char c_Info[100], int c_Int)
{
    char word[15], XX[4], YY[4];
    int line, col, dir, scor = 0;
    char *token;

    token = strtok(c_Info, " ");
    strcpy(word, token);

    token = strtok(NULL," ");
    strcpy(XX, token);

    token = strtok(NULL," ");
    strcpy(YY, token);

    dir = c_Int % 10;
    col = c_Int / 10 %100;
    line = c_Int / 1000;

    if(dir == 0)
        {
            int multiplicator = 1; // retine factorul de multiplicare al scorului cuvantului dat
            for(unsigned int j = col; j - col < strlen(word); j++)
            {
                    if(bonus_board[line][j] == 1)
                        if(!SubstringCheck(word, XX, 1))
                            multiplicator *= 2;
                        
                    if(bonus_board[line][j] == 2)
                        if(!SubstringCheck(word, YY, 2))
                            multiplicator *= 3;          
            }
            scor = WordScore(word) * multiplicator;
      
        }
        else
        {
            int multiplicator = 1;
            for(unsigned int j = line; j - line < strlen(word); j++)
            {
                    if(bonus_board[j][col] == 1)
                        if(!SubstringCheck(word, XX, 1))
                            multiplicator *= 2;

                    if(bonus_board[j][col] == 2)
                        if(!SubstringCheck(word, YY, 2))
                            multiplicator *= 3;
            }
            scor = WordScore(word) * multiplicator;
        }

    return scor;
}

int CheckSpace(char c_Info[100], int c_Int, char board[15][15], int write)
{
    //write 1 --> printeaza cuv pe tabla altfel nu (adaptare pentru a utiliza functia si la task 5)
    char word[15], copyInfo[100];
    strcpy(copyInfo, c_Info); //copiez sirul pentru a ramane neafectat
    strcpy(word, strtok(copyInfo," ")); // extrag cuvantul

    int length = strlen(word);
    int free = 0; //retine daca este suficient spatiu pentru cuvant
    int col = c_Int / 10 %100;
    int line = c_Int / 1000;

    // orizontala
    if(length > 15 - col)
    {
        free = 1;
    }
    else
    {
        for(int i = 1; i < length; i++)
        {
            if(board[line][i + col] != '.')
            {
                free = 1;
            }
        }
    }

    if(!free && write) 
    {
        PlaceWord(board, word, 0, col, line);
        return 0;
    }
    else if(!free && !write)
    {
        int scor = WordScoreBonus(c_Info, c_Int);
        return scor << 4;
    }
    
    free = 0; //resetare

    // verticala
    if(length > 15 - line)
    {
        free = 1;
    }
    else
    {
        for(int i = 1; i < length; i++)
        {
            if(board[i + line][col] != '.')
            {
                free = 1;
            }
        }
    }
    
    if(!free && write)
    {
        PlaceWord(board, word, 1, col, line);
        return 0;
    }
    else if(!free && !write)
    {
        c_Int++;
        int scor = WordScoreBonus(c_Info, c_Int);
        return (scor << 4) + 1;
    }

    return 1; 
}

long int BestPosibleWord(char board[15][15], int UsedWord[100], char XX[4], char YY[4])
{ 
    long int index = -1; // retine numarul de index al cuv, coordonatele si scorul
    int bestWordScore = 0;

   for(int i = 0; i < 100; i++)
    {
        if(!UsedWord[i]) // vefic ca acest cuv sa nu fie pe tabla
        {   
            for(int h = 0; h < 15; h++)
                for(int j =0; j < 15; j++)
                {
                
                    // verifica daca prima litera a cuv se afla pe tabla 
                    if(words[i][0] == board[h][j]) 
                    { 
                        char c_Info[100]; //Crez un sir de caractere pentru a trimite informatile catre functie
                        int c_Int = 0;//Crez un nr pentru a trimite informatile catre functie
                        strcpy(c_Info, words[i]);
                        strcat(c_Info," ");
                        strcat(c_Info, XX);
                        strcat(c_Info, " ");
                        strcat(c_Info, YY);
                        strcat(c_Info, " ");
                        c_Int = h * 1000 + j * 10;

                        int wordScore = 0;
                        wordScore = CheckSpace(c_Info, c_Int, board, 0);
                        
                        int dir = 0;
                        if(wordScore % 2 == 1)
                        {
                            dir = 1;
                        }

                        wordScore = wordScore >> 4 ;
                        
                        if(wordScore >= bestWordScore)
                        {  
                            int col = index / 10000 % 100;
                            int line = index / 1000000 % 100; 
                            //gasim positia optima a cuvantului
                            if(wordScore > bestWordScore)
                            {    
                                index = i * 100000;
                                index += h * 1000;
                                index += j * 10 + dir;     
                                bestWordScore = wordScore;                                
                                index *= 1000;
                                index += bestWordScore;                               
                            }
                            else if(h < line)
                                {
                                    index = i * 100000;
                                    index += h * 1000;
                                    index += j * 10 + dir;     
                                    bestWordScore = wordScore;                                  
                                    index *= 1000;
                                    index += bestWordScore;                                  
                                }
                                else if(h == line && j < col)
                                {
                                    index = i * 100000;
                                    index += h * 1000;
                                    index += j * 10 + dir;     
                                    bestWordScore = wordScore;                                    
                                    index *= 1000;
                                    index += bestWordScore; 
                                }
                            
                        }
                    }
                    
                }
        }
    } 

    return index;
}

void DoTask0(char board[15][15])
{
    InitBoard(board);
    print_board(board);
}

void DoTask1(char board[15][15])
{
    InitBoard(board);
    
    char string[30];
    fgets(string, 30, stdin);

    int N = 0; //numarul de cuvinte
    N = atoi(string);

    for(int i = 0; i < N; i++)
    {
        int line = 0, col = 0, dir = 0;
        char word[15];

        ExtractInfo(word, &line, &col, &dir);

        PlaceWord(board, word, dir, col, line);
    }

    print_board(board);
}

void DoTask2()
{
    char string[30];
    fgets(string, 30, stdin);

    int N = 0; //numarul de cuvinte
    N = atoi(string);

    int p1_scor = 0, p2_scor = 0;

    for(int i = 0; i < N; i++)
    {
        int line = 0, col = 0, dir = 0;
        char word[15];
        ExtractInfo( word, &line, &col, &dir);
        
        if( i%2 == 0) // verific carui jucator ii apartine cuvantul
            p1_scor += WordScore(word);
        else
            p2_scor += WordScore(word);
        
    }

    printf("Player 1: %d Points\nPlayer 2: %d Points\n", p1_scor, p2_scor);
    
}

void DoTask3()
{
    char XX[4], YY[4];
    int N = 0; 
    
    ExtractInfoPrime(XX, YY, &N);

    int p1_scor = 0, p2_scor = 0;

    for(int i = 0; i < N; i++)
    {
        int line = 0, col = 0, dir = 0;
        char word[15];

        ExtractInfo(word, &line, &col, &dir);

        char c_Info[100];
        int c_Int = 0;
        strcpy(c_Info, word);
        strcat(c_Info," ");
        strcat(c_Info, XX);
        strcat(c_Info, " ");
        strcat(c_Info, YY);
        strcat(c_Info, " ");

        c_Int = line * 1000 + col * 10 + dir;

        if(i % 2 == 0) // verific carui jucator ii apartine cuvantul;
            p1_scor += WordScoreBonus(c_Info, c_Int);
        else
            p2_scor += WordScoreBonus(c_Info, c_Int);
    }

    printf("Player 1: %d Points\nPlayer 2: %d Points\n", p1_scor, p2_scor);
}

void DoTask4(char board[15][15])
{
    int N = 0;
    char XX[4], YY[4];
    int UsedWord[100] = {0}; //vector care retine indexul cuvintelor folosite din vectorul words
    int search = 1; //parametru pentru determinarea momentului cand nu mai cautam cuvant

    InitBoard(board);

    ExtractInfoPrime(XX, YY, &N);

    for(int i = 0; i < N; i++)
    {
        char word[15];
        int line, col, dir;

        ExtractInfo(word, &line, &col, &dir);


        for(int j = 0; j < 100; j++)
        {
            if(!strcmp(word, words[j]))
            {
                UsedWord[j] = 1;
                break;
            }
        }
        PlaceWord(board, word, dir, col, line);
    }

    for(int i = 0; i < 100 && search; i++)
    {
        if(!UsedWord[i]) // vefic ca acest cuv sa nu fie pe tabla
        {
            for(int h = 0; h < 15 && search; h++)
                for(int j =0; j < 15 && search; j++)
                {
                    // verifica daca pozitia e ocupata si prima litera a cuv se afla pe tabla
                    if(board[h][j] != '.' && (words[i][0] == board[h][j]) ) 
                    { 
                        char c_Info[100];//Crez un sir de caractere pentru a trimite informatile catre functie
                        int c_Int = 0;//Crez un nr pentru a trimite informatile catre functie
                        strcpy(c_Info, words[i]);
                        c_Int = h * 1000 + j * 10;
                        
                        //seach devine 0 daca un cuvant a fost printat altfel ramane 1
                        search = CheckSpace(c_Info, c_Int, board, 1);
                    }
                    
                }
        }
    }
    
    print_board(board);
    
}

void DoTask5(char board[15][15])
{
    int N = 0;
    char XX[4], YY[4];
    int UsedWord[100] = {0}; 
    int p1_scor = 0, p2_scor = 0;

    long int index = -1; // retine numarul de index al cuv, coordonatele si scorul

    InitBoard(board);

    ExtractInfoPrime(XX, YY, &N);

    for(int i = 0; i < N; i++)
    {
        char word[15];
        int line, col, dir;

        ExtractInfo(word, &line, &col, &dir);

        for(int j = 0; j < 100; j++)
        {
            if(!strcmp(word, words[j]))
            {
                UsedWord[j] = 1;
                break;
            }
        }

        char c_Info[100];//Crez un sir de caractere pentru a trimite informatile catre functie
        int c_Int = 0;//Crez un nr pentru a trimite informatile catre functie
        
        strcpy(c_Info, word);
        strcat(c_Info," ");
        strcat(c_Info, XX);
        strcat(c_Info, " ");
        strcat(c_Info, YY);
        strcat(c_Info, " ");

        c_Int = line * 1000 + col * 10;
        
        PlaceWord(board, word, dir, col, line);
        if(dir == 0)
        {   
            if(i % 2 == 0)
                p1_scor += WordScoreBonus(c_Info, c_Int);
            else
                p2_scor += WordScoreBonus(c_Info, c_Int);
        }
        else
        {
            c_Int++;
            if(i % 2 == 0)
                p1_scor += WordScoreBonus(c_Info, c_Int);
            else
                p2_scor += WordScoreBonus(c_Info, c_Int); 
        }

        
    }
    //caut cuvantul care aduce cel mai mare scor posibil
    index = BestPosibleWord(board, UsedWord, XX, YY);

    //extrag informatile primite 
    int scor = index % 1000;
    index /= 1000;
    int dir = index % 10;
    int col = index / 10 % 100;
    int line = index / 1000 % 100;
    int i = index / 100000;

    //verific daca cuvantul indeplineste conditia de win
    if(p1_scor <= p2_scor + scor)
    {
        PlaceWord(board, words[i], dir, col, line);
        print_board(board);
    }
    else
    {
        printf("Fail!\n");
    }
}

void DoTask6(char board[15][15])
{
    int N = 0;
    char XX[4], YY[4];
    int UsedWord[100] = {0}; 
    int p1_scor = 0, p2_scor = 0;

    InitBoard(board);
    ExtractInfoPrime(XX, YY, &N);

    for(int i = 0; i < N; i++)
    {
        char word[15];
        int line, col, dir;
        long int index = -1;

        char c_Info[100];
        int c_Int = 0;
        //Player 1 word
        ExtractInfo(word, &line, &col, &dir);

        for(int j = 0; j < 100; j++)
        {
            if(!strcmp(word, words[j]))
            {
                UsedWord[j] = 1;
                break;
            }
        }  
        
        strcpy(c_Info, word);
        strcat(c_Info," ");
        strcat(c_Info, XX);
        strcat(c_Info, " ");
        strcat(c_Info, YY);
        strcat(c_Info, " ");

        c_Int = line * 1000 + col * 10;
        
        PlaceWord(board, word, dir, col, line);
        if(dir == 0)
        {   
            p1_scor += WordScoreBonus(c_Info, c_Int);
        }
        else
        {
            c_Int++;
            p1_scor += WordScoreBonus(c_Info, c_Int);
        }

        //Player 2 word
        index = BestPosibleWord(board, UsedWord, XX, YY);
        int scor = index % 1000;
        index /= 1000;
        int dir2 = index % 10;
        int col2 = index / 10 % 100;
        int line2 = index / 1000 % 100;
        int nr = index / 100000;
        
        PlaceWord(board, words[nr], dir2, col2, line2);
        UsedWord[nr] = 1;
        p2_scor += scor;
    }

    print_board(board);
    if(p1_scor > p2_scor)
        printf("Player 1 Won!\n");
    else
        printf("Player 2 Won!\n"); 
}

int main()
{
    char board[15][15];

    int task = 0;
    char string[15];
    fgets(string, 15, stdin);
    task = atoi(string);
    
    //functii separate pentru fiecare tase
    if(task == 0)
    {
        DoTask0(board);
        return 0;
    }
    if(task == 1)
    {
        DoTask1(board);
        return 0;
    }
    if(task == 2)
    {
        DoTask2();
        return 0;
    }
    if(task == 3)
    {
        DoTask3();
        return 0;
    }
    if(task == 4)
    {
        DoTask4(board);
        return 0;
    }
    if(task == 5)
    {
        DoTask5(board);
        return 0;
    }
    if(task == 6)
    {
        DoTask6(board);
        return 0;
    }

    return 0;
}