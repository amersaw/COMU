#include <stdio.h>
#include <stdlib.h>

#define LAND_MAP_FILENAME "arazi.txt"
#define LAND_HEIGHT 25
#define LAND_WIDTH 80

#define CONVOY_PATTERNS_FILENAME "konvoy_formasyonu.txt"
#define PATTERN_WIDTH 15
#define PATTERN_HEIGHT 15


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
    int commanderX, commanderY;
    findChar(pattern,'+',0,0,&commanderX,&commanderY);
    if(land[startY+commanderY][startX+commanderX]=='-') //kesin Yanliş
        return 0;

    int soldiersCount = countExcept(pattern,'-');

    int x=-1,y=0;
    int matched=1;//Komutan (commander already matched)
    int searchResult;
    do{

        searchResult = findChar(pattern,'*',x+1,y,&x,&y);
        if(searchResult == 0)
            continue;
        if(land[startY+y][startX+x]=='-') //Yanliş
            return 0;
        matched++;
    }while((searchResult != 0) && (matched!=soldiersCount));
    if(matched == soldiersCount)
        return 1;
    else
        return 0;
}
void patternMatched(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int convoyCode, int x, int y){
    int commanderX, commanderY;
    findChar(pattern,'+',0,0,&commanderX,&commanderY);
    printf("%5d\t(%d,%d)\n",convoyCode,y+commanderY+1,x+commanderX+1);
    //printf("%d.\t:\tX=%d, Y=%d\n",convoyCode,,);
}
int matchPattern(char land[LAND_HEIGHT][LAND_WIDTH], char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int convoyCode, int realPatternWidth, int realPatternHeight, int *x, int *y){
    int i,j,matchesCount=0;
    for(i=0;i<(LAND_HEIGHT-realPatternHeight);i++){
        //printf("\n%d\n",i);
        for(j=0;j<(LAND_WIDTH-realPatternWidth);j++){
            //printf("%d ",j);
            if(verifyPattern(land,pattern,j,i) == 1)
            {
                *x=j;
                *y=i;
                patternMatched(pattern, convoyCode, j, i);
                matchesCount++;
            }
        }
    }
    return matchesCount;
}

/*
Bu fonksiyon verildigi bir formasyon ve bir satirin indeksi boş olduğunu ya da olmadığını söylüyor
*/
int isEmptyRow(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int index){
    int i;
    for(i=0;i<PATTERN_WIDTH;i++)
        if(pattern[index][i] != '-')
            return 0;
    return 1;
}

/*
Bu fonksiyon verildigi bir formasyon ve bir sütunun indeksi boş olduğunu ya da olmadığını söylüyor
*/
int isEmptyColumn(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH], int index){
    int i;
    for(i=0;i<PATTERN_HEIGHT;i++)
        if(pattern[i][index] != '-')
            return 0;
    return 1;
}

/*
Bu fonksiyon verildiği bir formasyon üzerinde bir satır, başka bir satır yerinde yazdırıyor (kopylanıyor)
*/
void copyRow(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH],int to, int from){
    int i;
    for(i=0;i<PATTERN_WIDTH;i++){
        pattern[to][i]=pattern[from][i];
    }
}

/*
Bu fonksiyon verildiği bir formasyon üzerinde bir sütun, başka bir sütuna yazdırıyor (kopylanıyor)
*/
void copyColumn(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH],int to, int from){
    int i;
    for(i=0;i<PATTERN_WIDTH;i++){
        pattern[i][to]=pattern[i][from];
    }
}


void removeFirstRow(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH]){
    int i;
    for(i=1;i<PATTERN_HEIGHT;i++){
        copyRow(pattern,i-1,i);
    }
    for(i=0;i<PATTERN_WIDTH;i++){
        pattern[PATTERN_HEIGHT-1][i]='-';
    }

}
void removeFirstColumn(char pattern[PATTERN_HEIGHT][PATTERN_WIDTH]){
    int i;
    for(i=1;i<PATTERN_WIDTH;i++){
        copyColumn(pattern,i-1,i);
    }
    for(i=0;i<PATTERN_HEIGHT;i++){
        pattern[i][PATTERN_WIDTH-1]='-';
    }


}
void cleanPattern (char pattern[PATTERN_HEIGHT][PATTERN_WIDTH]){
    int i;
    for(i=0;i<PATTERN_HEIGHT;i++){
        if(isEmptyRow(pattern,i)){
            removeFirstRow(pattern);
            i--;//Çünkü bir satır sildik
        }
        else
            break;
    }
    for(i=0;i<PATTERN_HEIGHT;i++){
        if(isEmptyColumn(pattern,i)){
            removeFirstColumn(pattern);
            i--;//Çünkü bir sutün sildik zaten
        }
        else
            break;
    }
}

int main(){
    char Land[LAND_HEIGHT][LAND_WIDTH];
    FILE *landFile = fopen(LAND_MAP_FILENAME , "r");
    int i;
    for(i=0;i<LAND_HEIGHT;i++){
        fscanf(landFile,"%s",Land[i]);
    }

    int patternsCount;
    FILE *convoyPatternsFile = fopen(CONVOY_PATTERNS_FILENAME,"r");
    fscanf(convoyPatternsFile,"%d",&patternsCount);

    printf("%5s %14s\n%5s %14s\n","Kod ","Koordinatlar ","-----","--------------");
    for(i=0;i<patternsCount;i++){
        int convoyCode;
        char pattern[PATTERN_HEIGHT][PATTERN_WIDTH];
        fscanf(convoyPatternsFile,"%d",&convoyCode);
        int j;
        for(j=0;j<PATTERN_HEIGHT;j++){
            fscanf(convoyPatternsFile,"%s",pattern[j]);
        }
        cleanPattern(pattern);
        int realPatternWidth, realPatternHeight;
        getRealPatternSize(pattern,&realPatternWidth,&realPatternHeight);
        if(convoyCode == 12)
            ;//continue;
        int resX, resY;
        int res = matchPattern(Land, pattern, convoyCode, realPatternWidth, realPatternHeight, &resX, &resY);
        if(res==0)
            printf("%5d\t%12s\n",convoyCode,"BULUNMADI   ");


    }

    return 0;
}
