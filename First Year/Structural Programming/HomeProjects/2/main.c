#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define MAX_CHARS 1024

char girdi[MAX_CHARS];
char inputTable [MAX_ROWS][MAX_COLUMNS][MAX_CHARS];
int evaluated[MAX_ROWS][MAX_COLUMNS];
char cellsTypes[MAX_ROWS][MAX_COLUMNS];

int Height,Width;


int splitInt(char *input,int from, int to){
    int retVal=0,i;
    for(i=from;i<to;i++){
        retVal *= 10;
        retVal += (*(input+i)-'0');
    }
    return retVal;
}

void splitChars(char *input,char *retVal,int from, int to){
    int i;
    int retValIndex =0;
    for(i=from;i<to;i++,retValIndex++){
        *(retVal+retValIndex) = *(input+i);
    }
    *(retVal+retValIndex)='\0';
}

void getCoordinates(char *input, int *x, int *y){
    //strtol function can be used
    //long x = strtol( string, &remainderPtr, 0 );
    int j=(*input)-'A';

    int i=*(input+1)-'0';
    if(*(input+2) != '\0'){
        i*=10;
        i += (*(input+2))-'0';
    }
    i--; //Because 0-Based index

    *x = i;
    *y = j;
}

int bringCellValue(char *part){
    int i,j;
    getCoordinates(part,&i,&j);

    if(*(*(cellsTypes+i)+j) == 'f'){
        return 0; // Not calculated yet
    }

    if(   (i>=Height) || (j>=Width) )
    {
        strcpy(part,"$");
        return -1;//Removed Cell
    }

    itoa(*(*(evaluated+i)+j), part, 10); // 10 - decimal;
    return 1; //success
}

int mathCalculate(char operand, int n1, int n2){

    switch  (operand){
        case '+':
            return n1+n2;
        case '-':
            return n1-n2;
        case '*':
            return n1*n2;
        case '/':
            if(n2==0){
                printf("!!!!!!!!!DIVIDE BY ZERO EXCEPTION!!!!!!!!!!!!!!!!\nWILL CONTINUE AS ZERO\n");
                return 0;
            }
            return n1/n2;
    }
    return 0;
}

int findNumberIndex(char parts[][MAX_CHARS],int size, int increment,int startFrom, int defaultValue){

    int i;
    for(i=startFrom+increment;i<size;i+=increment){
        char firstChar = *(*(parts+i));
        if(firstChar != '#'){
            return i;
        }
    }
}

void calcOperand(char parts[][MAX_CHARS],int partsCount,int opIndex){

    int defaultValue = 0;
    char operation = *(*(parts+opIndex));
    if((operation=='*') || (operation=='/'))
        defaultValue=1;

    int firstNumberIndex = findNumberIndex(parts,partsCount,-1,opIndex, defaultValue);
    int secondNumberIndex = findNumberIndex(parts,partsCount,+1,opIndex, defaultValue);

    if((*(*(parts+firstNumberIndex)) == '$') || (*(*(parts+firstNumberIndex)) == '$'))
    {
        itoa(defaultValue, parts+opIndex, 10);
        strcpy(parts+firstNumberIndex,"#");
        strcpy(parts+secondNumberIndex,"#");
    }
    else
    {
        int firstNumber = atoi(*(parts+firstNumberIndex));
        int secondNumber = atoi(*(parts+secondNumberIndex));

        int result = mathCalculate(operation, firstNumber, secondNumber);

        itoa(result, parts+opIndex, 10);

        strcpy(parts+firstNumberIndex,"#");
        strcpy(parts+secondNumberIndex,"#");
    }
}

void applyOperand(char parts[][MAX_CHARS],int size, char operand){
    int i;
    for(i=0;i<size;i++){
        char currPartFirstChar=*(*(parts+i));
        if(currPartFirstChar == operand){
                calcOperand(parts, size ,i);
        }
    }
}

int evaluate(char form[MAX_CHARS],int *retval){

    char parts[MAX_CHARS][MAX_CHARS];//diyelim 1024 tane hucre kullanacagiz, her tane 1024 karakter
    int partsIndex = 0;

    int len=strlen(form);
    int i;
    int lastSplitter = 0;
    for(i=1;i<len;i++){
        char currChar = *(form+i);
        if((currChar=='*') || (currChar=='/') || (currChar=='+') || (currChar=='-')){
                splitChars(form,parts+partsIndex,lastSplitter+1,i);
                partsIndex++;
                lastSplitter=i;
                parts[partsIndex++][0]=currChar;
                parts[partsIndex][1]='\0';
           }
           if((len-1)==i){
                splitChars(form,parts+partsIndex,lastSplitter+1,i+1);
           }
    }
    int partsCount = partsIndex+1;


    for(i=0;i<partsCount;i++){
        char currPartFirstChar=*(*(parts+i));
        if((currPartFirstChar!='*') && (currPartFirstChar!='/') && (currPartFirstChar!='+') && (currPartFirstChar!='-')){
            int success = bringCellValue(parts+i);
            if(success==0) //not evaluated yet
                return 0;
        }
    }

    applyOperand(parts, partsCount, '*');
    applyOperand(parts, partsCount, '/');
    applyOperand(parts, partsCount, '-');
    applyOperand(parts, partsCount, '+');

    int resIndex = findNumberIndex(parts,partsCount,1,-1, 0);
    *retval =  atoi(*(parts+resIndex));
    return 1;
}

void createTable(char *input){
    int i,j;
    int current= -2;
    int lastComma=-1;
    int len=strlen(input);
    for(i=0;i<len;i++){
        if((*(input+i)==',') || (i==len-1)){
            if(current == -2) //Split the Width
            {
                Width=splitInt(input,lastComma+1,i);
                if(Width>MAX_COLUMNS){
                    printf("%d'den fazla sutun olmaz!",MAX_COLUMNS);
                    break;
                }
            }
            else if(current == -1) //split the Height
            {
                Height=splitInt(input,lastComma+1,i);
                if(Height>MAX_ROWS){
                    printf("%d'den fazla satir olmaz!",MAX_ROWS);
                    break;
                }
            }
            else //normal cell
            {
                int I,J;
                I=current/Width;
                J=current%Width;
                if(i==len-1)
                    i++;

                splitChars(input,(*(inputTable+I))+J,lastComma+1,i);
            }
            lastComma=i;
            current++;
        }
    }
}

void determineCellTypesAndFillEvaluated(){

    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
            if(*(*((*(inputTable+i))+j))=='='){
                *((*(cellsTypes+i))+j)='f';//Formula
            }
            else{
                *((*(cellsTypes+i))+j)='n';//Number
                *(*(evaluated+i)+j) = atoi(*((*(inputTable+i))+j));
            }
        }
    }
}

int countOf(char arr[MAX_ROWS][MAX_COLUMNS], char key){
    int res = 0;
    int i,j;
    for(i=0;i<MAX_ROWS;i++){
        for(j=0;j<MAX_COLUMNS;j++){
                if(  *(*(arr+i)+j) == key)
                    res++;
        }
    }
    return res;
}

void evaluateAllCells(){
    int remainingFormulas;
    do{
        int i,j;
        for(i=0;i<Height;i++){
            for(j=0;j<Width;j++){
                if(  *(*(cellsTypes+i)+j) == 'f' ){
                    int evaluatedValue;
                    int success = evaluate((*(inputTable+i))+j,&evaluatedValue);
                    if(success!=1)
                        continue;
                    *(*(evaluated+i)+j)=evaluatedValue;
                    *(*(cellsTypes+i)+j)='e';
                  //  printf("\n[%d][%d]=%d\n",i,j,evaluatedValue);
                }
            }
        }
        remainingFormulas=countOf(cellsTypes,'f');

    }while(remainingFormulas>0);
}

void print2DIntArray(int input[MAX_ROWS][MAX_COLUMNS]){
    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
                printf("%d\t",*(*(input+i)+j));
        }
        printf("\n");
    }
}
void print2DStringArray(char input[MAX_ROWS][MAX_COLUMNS][MAX_CHARS]){
    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
                printf("%15s",*(*(input+i)+j));
        }
        printf("\n");
    }
}

void printMenuOptions(){
    printf("\nLutfen asagidaki seceneklerden bir secenk seciniz :");
    printf("\n\t1 - Formul hesaplama");
    printf("\n\t2 - Satir ekleme");
    printf("\n\t3 - Satir silme");
    printf("\n\t4 - Hucre degeri guncelleme");
    printf("\n\t5 - Veri filterleme");
    printf("\n\t0 - Cikis\n");
}

void getLineContent(char retVal[MAX_COLUMNS][MAX_CHARS]){
    int i;
    for(i=0;i<Width;i++){
        printf("\n Lutfen yeni satirinda %d. stunun degeri giriniz :",i);
        scanf("%s",(retVal+i));
    }
}

void copyLine(char source[MAX_COLUMNS][MAX_CHARS], char destination[MAX_COLUMNS][MAX_CHARS]){
    int i;
    for(i=0;i<Width;i++){
        strcpy(destination+i,source+i);
    }
}

void insertLine (char destination[MAX_ROWS][MAX_COLUMNS][MAX_CHARS], int index, char line[MAX_COLUMNS][MAX_CHARS]){
    int i;
    for(i=Height;i>index;i--){
        copyLine(destination+i-1,destination+i);
    }
    copyLine(line,destination+index);
}

void calculateAndPrint(){
    determineCellTypesAndFillEvaluated();

    evaluateAllCells();


    printf("\n##################################");
    printf("\nAsil Matrisi :\n----------------------------------\n");
    print2DStringArray(inputTable);
    printf("\n----------------------------------\nDegerlendiren Matris :\n----------------------------------\n");
    print2DIntArray(evaluated);
    printf("\n##################################");
}


void removeLine(char table[MAX_ROWS][MAX_COLUMNS][MAX_CHARS], int index){
    int i;
    for(i=index;i<Height;i++){
        copyLine(table+i+1,table+i);
    }
}

void readCoordinates(int *i,int *j){
    printf("\nLutfen sutun giriniz [A-J] arasinda :");//todo: make it dynamic, not only till J
    char col;
    scanf(" %c", &col);
    *j = col-'A';

    printf("\nLutfen satir giriniz [1-%d] arasinda :",Height);
    scanf("%d",i);
    (*i)--;//Because 0-based index

}
void printFilteredArray (int filter){
    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
            int currNumber = *(*(evaluated+i)+j);
            if(*((*(cellsTypes+i))+j) == 'n') //number that can be filltered
            {
                if(currNumber<=filter)
                    printf("!\t");
                else
                    printf("%d\t",currNumber);
            }else
                printf("%d\t",currNumber);
        }
        printf("\n");
    }
}
int main(){

    int option;
    do{
        printMenuOptions();
        scanf("%d",&option);
        switch(option)
        {
            case 0://Exit
                break;
            case 1:
            {
                printf("\nLutfen tablonun degeri giriniz :\n");
                scanf("%s",girdi);

                if(strcmp(girdi,"default")==0)
                    strcpy(girdi,"4,3,10,34,37,=A1+B1+C1,40,17,34,=A2+B2+C2,=A1+A2,=B1+B2,=C1+C2,=D1+D2");

                createTable(girdi);

                calculateAndPrint();

                printf("\n\n\n");


                break;
            }
            case 2:
            {
                int newLineIndex;
                do{
                    printf("\nLutfen ekleyeceksin satir hangi satirdan sonra giriniz (0-%d) arasinda : ",Height);
                    scanf("%d",&newLineIndex);
                    if(newLineIndex>Height){
                        printf("\nSu kadar satirlar zaten yok, lutfen %d dan daha az degerler giriniz",Height);
                    }
                    if(newLineIndex<0){
                        printf("\nSifir yada sifirdan daha buyuk bir sayi giriniz.");
                    }
                }while((newLineIndex>Height) || (newLineIndex<0));
                char newLine[MAX_COLUMNS][MAX_CHARS] ;
                getLineContent(newLine);
                insertLine(inputTable,newLineIndex,newLine);
                Height++;

                calculateAndPrint();

                break;

            }
            case 3:
            {
                int lineToRemoveIndex;
                do{
                    printf("\nLutfen sileceksiniz satirin indexi giriniz (1-%d) arasinda :",Height);
                    scanf("%d",&lineToRemoveIndex);
                    //lineToRemoveIndex--;//Because 0-based index
                    if((lineToRemoveIndex>Height) || (lineToRemoveIndex<=0)){
                            printf("\nDogru bir satir indexi giriniz lutfen.\n");
                    }
                }while((lineToRemoveIndex>Height) || (lineToRemoveIndex<=0));

                removeLine(inputTable, lineToRemoveIndex-1);//Because 0-based index
                Height--;
                calculateAndPrint();
                break;
            }
            case 4:
            {
                int i,j;
                do{
                    readCoordinates(&i,&j);
                    if((i>Height) || (i<0) || (j>Width) || (j<0)){
                        printf("\nBoyle bir hucre bulunmadi. Lutfen yeniden giriniz.");
                    }
                }while((i>Height) || (i<0) || (j>Width) || (j<0));

                char cell[MAX_CHARS];
                printf("\nLutfen hucrenin yeni degeri giriniz :");
                scanf("%s",cell);
                strcpy( (*(inputTable+i))+j,cell);

                calculateAndPrint();
                break;

            }
            case 5:
            {
                int filter;
                printf("\nHangi sayi'ye gore filterleyeceksiniz :");
                scanf("%d",&filter);
                printFilteredArray(filter);
                break;
            }

        }
    }while(option!=0);

    return 0;
}
