#include <stdio.h>
#include <stdlib.h>

#define LAND_MAP_FILENAME "arazi.txt"
#define LAND_HEIGHT 25
#define LAND_WIDTH 80
#define CONVOY_PATTERNS_FILENAME "konvoy_formasyonu.txt"
#define PATTERN_WIDTH 15
#define PATTERN_HEIGHT 15


//TODOOOOOOOOOOOOo
void getRealPatternSize(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int *width, int *height){

    int top=PATTERN_HEIGHT+1, bottom=-1, left=PATTERN_WIDTH+1, right=-1;
    int i,j;
    for(i=0;i<PATTERN_HEIGHT;i++){
        for(j=0;j<PATTERN_WIDTH;j++){
            if(pattern[i][j]!='-'){
                if(i<top)
                    top=i;
                if(i>bottom)
                    bottom=i;
                if(j>right)
                    right = j;
                if(j<left)
                    left=j;
            }
        }
    }
    *width = right-left+1;//PATTERN_WIDTH;
    *height = bottom-top+1;//PATTERN_HEIGHT;
}

int countExcept (char input[PATTERN_HEIGHT][PATTERN_WIDTH], char key){
    int i,j,res=0;
    for(i=0;i<PATTERN_HEIGHT;i++){
        for(j=0;j<PATTERN_WIDTH;j++){
            if(input[i][j] != key)
                res++;
        }
    }
    return res;
}

int findChar(char input[PATTERN_HEIGHT][PATTERN_WIDTH], char key, int startX, int startY, int *x, int *y){
    int i,j;
    for(i=startY;i<PATTERN_HEIGHT;i++){
        for(j=(i==startY?startX:0);j<PATTERN_WIDTH;j++){
           if(input[i][j] == key)    {
                *y=i;
                *x=j;
                if(i>1000)
                    printf("dd");
                return 1;
           }
        }
    }
    return 0;
}

int verifyPattern(char land[LAND_HEIGHT][LAND_WIDTH], char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int startX, int startY){
    if((startX==7) &&( startY ==0))
        printf("DDDD");
    int commanderX, commanderY;
    findChar(pattern,'+',0,0,&commanderX,&commanderY);
    if(land[startY+commanderY][startX+commanderX]=='-') //kesin Yanli?
        return 0;
    else
        printf("dd");

    int soldiersCount = countExcept(pattern,'-');

    int x=-1,y=0;
    int matched=1;//Komutan (commander already matched)
    int searchResult;
    do{

        searchResult = findChar(pattern,'*',x+1,y,&x,&y);
        if(searchResult == 0)
            continue;
        if(land[startY+y][startX+x]=='-') //kesin Yanli?
            return 0;
        else
            printf("dd");
        matched++;
    }while((searchResult != 0) && (matched!=soldiersCount));
    if(matched == soldiersCount)
        return 1;
    else
        return 0;
}

int matchPattern(char land[LAND_HEIGHT][LAND_WIDTH], char pattern[PATTERN_HEIGHT][PATTERN_WIDTH],int realPatternWidth, int realPatternHeight, int *x, int *y){
    int i,j;
    for(i=0;i<(LAND_HEIGHT-realPatternHeight);i++){
        //printf("\n%d\n",i);
        for(j=0;j<(LAND_WIDTH-realPatternWidth);j++){
                //printf("%d ",j);
                if(verifyPattern(land,pattern,j,i) == 1)
                {
                    *x=j;
                    *y=i;
                    return 1;
                }
        }
    }
    return 0;
}

int main()
{
    char Land[LAND_HEIGHT][LAND_WIDTH];
    FILE *landFile = fopen(LAND_MAP_FILENAME , "r");
    int i;
    for(i=0;i<LAND_HEIGHT;i++){
        fscanf(landFile,"%s",Land[i]);
    }

    int patternsCount;
    FILE *convoyPatternsFile = fopen(CONVOY_PATTERNS_FILENAME,"r");
    fscanf(convoyPatternsFile,"%d",&patternsCount);

    for(i=0;i<patternsCount;i++){
        int convoyCode;
        char pattern[PATTERN_HEIGHT][PATTERN_WIDTH];
        fscanf(convoyPatternsFile,"%d",&convoyCode);
        int j;
        for(j=0;j<PATTERN_HEIGHT;j++){
            fscanf(convoyPatternsFile,"%s",pattern[j]);
        }
        int realPatternWidth, realPatternHeight;
        getRealPatternSize(pattern,&realPatternWidth,&realPatternHeight);
if(convoyCode == 12)
    ;//continue;
        int resX, resY;
        matchPattern(Land,pattern,realPatternWidth, realPatternHeight,&resX,&resY);
        printf("X=%d, Y=%d\n",resX,resY);
    }

    return 0;
}
