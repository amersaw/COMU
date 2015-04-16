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

//Bu fonksiyon bir tane char * matristen belli bir yerden bir yere
//kadar kesiyor integer olarak ve onun degere donduruyor
//Parametters :
    //input : nerden keselecek
    //from  : başlangıç
    //to    : nereye kadar keseecek
//Returned Value:
    //Değerin int'd çevirdikten sonra
int splitInt(char *input,int from, int to){
    int retVal=0,i;
    for(i=from;i<to;i++){
        retVal *= 10;

        //Basit bir yönetim kullanarak herhangi bir char sayı integere dönderiyoruz
        //çünkü bütün sayılar char olarak sırayle saklanılıyor
        retVal += (*(input+i)-'0');
    }
    return retVal;
}


//Bu fonksiyon bir tane char * matristen belli bir yerden bir yere
//kadar kesiyor ve onu başka verilen bir matris içinde saklanıyor
//Her harf alıyoruz ve sonuç matrisine ekliyoruz
//Parametters :
    //input : nerden keselecek
    //retVal: Sonuç nerde saklanılacak
    //from  : başlangıç
    //to    : nereye kadar keseecek
//Returned Value: YOK
void splitChars(char *input,char *retVal,int from, int to){
    int i;
    int retValIndex =0;
    for(i=from;i<to;i++,retValIndex++){
        *(retVal+retValIndex) = *(input+i);
    }
    *(retVal+retValIndex)='\0';
}


//Bu fonksiyon bir coordination alıyor char * olarak (G10 mesala)
//ve onu hangi stun ve hangi satır olduğunu dönduruyor
//Parametreler :
    //input : Giriş char matris olarak
    //x     : Çikiş parametre olarak, onunle hangi satır oldugunu dönderiyoruz
    //y     : Çikiş parametre olarak, onunle hangi sutun oldugunu dönderiyoruz
//Returned Value: YOK
void getCoordinates(char *input, int *x, int *y){
    //strtol function can be used
    //long x = strtol( string, &remainderPtr, 0 );
    int j=(*input)-'A';

    int i=*(input+1)-'0';

    if(*(input+2) != '\0'){ //Eğer ikinci basamak varsa onu da alıyoruz
        i*=10;
        i += (*(input+2))-'0';
    }

    i--; //Because 0-Based index

    *x = i;
    *y = j;
}
//Bu fonksiyon char matris alıyor ve içerdeki hücre adresini yerinde onun gerçek değeri atıyor.
//Parametreler :
    //part : hücrenin değeri, ayni zamanda hücrenin değeri getirdikten sonra bu matris içinde saklanılacak
//Returned Value (Error Code):
    //Başarlı oldugunu ya da başarsız olduğunu ve sebebi
    // 0    : başarsız, çünkü getirelecek hücrenin değeri hala bir formuladır
    // -1   : bu hücre tablonun dışında ve değer olarak $ verildi
    // 1    : başarıyla tamamlandı
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

//Bu fonksiyon bi matematik işlem yapıyor
//Parametreler :
    //operand : hangi işlem yapılacak
    //n1 : birinci sayı
    //n2 : ikinci sayı
//Returned Value:
    //işlemin sonucu (int olarak)
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

//Bu fonksiyon bir matris içinde arama yapıyor, bir yerden itibaran başlıyor ve ya sonra ya da önce'ye gidiyor
//Parametreler :
    //parts : nerede arama yapılacak
    //size : parts'ın boyutu
    //increment : artım kaç olacak, ya 1 sonra için, ya da -1 önce için
    //startFrom : nerden başlayacak
//Bu fonksiyon eğer # symbol varsa onu yok sayıor ve sonraki ya da önceki elemana devam ediyor
//yani # olan hücreler sanki boş bir hücreler
int findNumberIndex(char parts[][MAX_CHARS],int size, int increment,int startFrom){
    int i;
    for(i=startFrom+increment;i<size;i+=increment){
        char firstChar = *(*(parts+i));
        if(firstChar != '#'){
            return i;
        }
    }
}


//Bu fonksiyon bir formula parçalar alıyor ve matematik işlemin indexi alıyor ve bu işlemin iki sayıları
//buluyor ve hesaplıyor, ve sayıların yerine # koyuyor, sonuç ise işlemin bulunduğu yerde saklanılyor

//Eğer birinci yada ikinci sayı getirirken bu sayı tablonun dışında olduğu zamanda onun yerine bir
//değer koyalacak (1 çarp ve bölüme için ve 0 artırma ve eksik işlemler için) ve bu şekilde işlem
//normal olarak devam edebilir

//Parametreler:
    //parts : formulanın parçaları
    //partsCount : parts'ın boyutu
    //opIndex : matematik işlemi bulunduğu index

void calcOperand(char parts[][MAX_CHARS],int partsCount,int opIndex){

    int defaultValue = 0;
    char operation = *(*(parts+opIndex));

    if((operation=='*') || (operation=='/'))
        defaultValue=1;

    int firstNumberIndex = findNumberIndex(parts,partsCount,-1,opIndex);
    int secondNumberIndex = findNumberIndex(parts,partsCount,+1,opIndex);
    int firstNumber ;
    int secondNumber ;

    if((*(*(parts+firstNumberIndex)) == '$'))//Tablu dışında
        firstNumber=defaultValue;
    else
        firstNumber = atoi(*(parts+firstNumberIndex));

    if((*(*(parts+secondNumberIndex)) == '$'))//Tablu dışında
        secondNumber=defaultValue;
    else
        secondNumber= atoi(*(parts+secondNumberIndex));

    int result = mathCalculate(operation, firstNumber, secondNumber);

    itoa(result, parts+opIndex, 10);

    strcpy(parts+firstNumberIndex,"#");
    strcpy(parts+secondNumberIndex,"#");

}

//Bu fonksiyon bir fomula parçaları ve bir matematik işlem alıyor,
//ve bu parçalar içinde her bu matematik işlem görundu zamanda calcOperand fonksiyonu çağırıyor.

//Parametreler:
    //parts : formulanın parçaları
    //partsCount : parts'ın boyutu
    //operand : matematik işlemin symbolu
void applyOperand(char parts[][MAX_CHARS],int size, char operand){
    int i;
    for(i=0;i<size;i++){
        char currPartFirstChar=*(*(parts+i));
        if(currPartFirstChar == operand){
                calcOperand(parts, size ,i);
        }
    }
}

//Bu fonksiyon verildigi harf matematik işlem symbol ise (* / - +) 1 donduruyor yoksa 0.
//Parametreler:
    //chr : kontrol edilecek harf

//Returned Valued :
    //1 : Eğer bir matematik işlem.
    //0 : Eğer değil.
int isMathOperand(char chr){
    return ((chr=='*') || (chr=='/') || (chr=='+') || (chr=='-'))?1:0;
}


//Bu fonksiyon verildigi bir formula parçalanıyor, her matematik işlem görduğu zamanda yeni bir parça alıyor
//ve matematik işlemi kendi için ayrı bir parça alıyor. sonuç ise retVal çıkış parametre içinde saklanıyor
//Parametreler :
    //form  : parçalanacak formu.
    //retVal : iki boyutlu bir matris içinde parçalandığı parçalar saklanılacak
//Returned Value :
    //kaç parça oldu döndürelecek.
int seperateFormula(char form[MAX_CHARS], char retVal[MAX_CHARS][MAX_CHARS]){
    int len=strlen(form);
    int i;
    int lastSplitter = 0;
    int partsIndex=0;
    for(i=1;i<len;i++){
        char currChar = *(form+i);
        if(isMathOperand(currChar)){
                splitChars(form,retVal+(partsIndex++),lastSplitter+1,i);

                lastSplitter=i;

                splitChars(form,retVal+(partsIndex++),lastSplitter,i+1);
           }
           if((len-1)==i){
                splitChars(form,retVal+partsIndex,lastSplitter+1,i+1);
           }
    }
    return partsIndex+1;
}

//Bu fonksiyon bir formula alıyor ve onun gerçek değeri hasapladıktan sonra dönderiyor.
//Eğer bir hücrenin değeri hala hesaplanmadı ise bu fonksiyon başarsız olacak ve değer döndürmeyecek.
//Parametreler:
    //form : değerlendirelecek formu.
    //retval : verildiği formu değerledikten sonra kaç olduğunu dönderelecek.
//Retruned Value :
    //başarlı ya da başarsız olduğunu söylüyor:
    //0 : Başarsız, bir tane kullanıldı hücrenin değeri hala hesaplanmadı demektir
    //1 : Başarlı oldu ve değer döndürdü
int evaluate(char form[MAX_CHARS],int *retval){

    char parts[MAX_CHARS][MAX_CHARS];//diyelim 1024 tane hucre kullanacagiz, her tane 1024 karakter

    //Formula Parçalanıyor
    int partsCount = seperateFormula(form,parts);

    //Formulanın parçaları değerlendiriyor, bir tane başarsız kalırsa, bu fonksiyon bitecek
    int i;
    for(i=0;i<partsCount;i++){
        char currPartFirstChar=*(*(parts+i));
        if(!isMathOperand(currPartFirstChar)){  //matematik işlem değilse yani bir hücrenin adresi
            int success = bringCellValue(parts+i);
            if(success==0) //not evaluated yet
                return 0; //İşlem başarsız olduğunu dönderiyoruz
        }
    }

    //Parçalar içinde matematek işlemler SIRAİLE yapılıyor
    applyOperand(parts, partsCount, '*');
    applyOperand(parts, partsCount, '/');
    applyOperand(parts, partsCount, '-');
    applyOperand(parts, partsCount, '+');


    //Sonuç almak için boş (yani # olmayan) olmayan tek bir hücre kaldı, onun değeri alıyoruz
    int resIndex = findNumberIndex(parts,partsCount,1,-1);
    *retval =  atoi(*(parts+resIndex));
    return 1;
}

//Bu fonksiyon kullancı girdiği tablonun değerleri kendi yerinde dolduryor

//Ayne zamanda ilk iki sayılar (kaç stun ve kaç satır gösteren sayılar)
//Height ve Width değişkenler içinde saklanıyor

//Sonuç inputTable içinde saklanılacak
//Parametreler :
    //input : kullancı girdiği data
void createTable(char *input){
    int i,j;
    int current= -2; //-2 ile başlıyoruz çünkü ilk iki sayılar tabluadışında bir sayılar
    int lastComma=-1; //-1 ile başlıyoruz çünkü ilk defa 0 olması lazım
    int len=strlen(input);
    for(i=0;i<len;i++){
        if((*(input+i)==',') || (i==len-1)){ // Virgül gördük ya da sona erdik
            if(current == -2) //Split the Width
            {
                Width=splitInt(input,lastComma+1,i);
                if(Width>MAX_COLUMNS){ //kontrol gerek yoktu, kullancıya göveniyoruz :D
                    printf("%d'den fazla sutun olmaz!",MAX_COLUMNS);
                    break;
                }
            }
            else if(current == -1) //split the Height
            {
                Height=splitInt(input,lastComma+1,i);
                if(Height>MAX_ROWS){ //kontrol gerek yoktu, kullancıya göveniyoruz :D
                    printf("%d'den fazla satir olmaz!",MAX_ROWS);
                    break;
                }
            }
            else //normal cell
            {
                int I,J;
                I=current/Width;
                J=current%Width;

                if(i==len-1)//eğer son harfa erdik ise, son harf alabilmek için i'ye 1 ekliyoruz
                    i++;

                splitChars(input,(*(inputTable+I))+J,lastComma+1,i);
            }
            lastComma=i;
            current++; //sadece virgül görduğumuz zamanda artırıyoruz onu demek ki başka bir hücre'ye gittik
        }
    }
}

//Bu fonksiyon kullancıdan alındığı vergiler'den butün hücreler içinde dulaşıyor
//ve her hücrenin tıpı ayrı (ama aynı boyutlar) bir matris (cellsTypes) içinde saklanıyor
//cellsTypes içinde üç değerler bulunabilir :
    //f     :   Formula
    //n     :   Numara
    //e     :   Değerlendi (Evaluated) bir formula ve onun sonucu "evaluated" matris içinde sakland
//Ayne zamanda bu fonksiyon kullancıdan aldığı gerçek sayılar (formula olmayan hücreler) "evaluated" matrisinde
//kendi yerlerinde saklanıyor (int olarak)

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

//Bu fonksiyon verildiği iki boyutlu bir matris içinde kaç tane bir değer sayıyor ve onların sayısı dönderiyor
//Parametreler :
    //arr       :   arayacak array içinde
    //key       :   aramak anahtarı
//Returned Value :
    //Kaç tane buldu. (int olarak)
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


//Bu fonksiyon butun inputTable'deki hücreler için "evaluate" fonksiyon çağırıyor,
//ve hesaplandığı değer (Başarlı olursa) "evaluated" matrisinde saklanıyor.
//başarlı olmadığı zamanda onu atlıyor.

//Her zaman Bu operatıon yaptıktan sonra kaç hesaplanmadığı formula kaldı sayır,
//daha kaldı ise, yeniden onu tekrarlanıyor (hesaplanmayan hücreler sadece, yani 'f' olan hücreler)
//Kalan hesaplanmayan hücreler sıfır olduğu zamanda demek ki her şey hesaplandı.

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


//Bu fonksiyon 2 int boyutlu bir matris ekrana yazdırıyor.
//Parametreler :
    //input : yazılacak matrıs.
void print2DIntArray(int input[MAX_ROWS][MAX_COLUMNS]){
    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
                printf("%d\t",*(*(input+i)+j));
        }
        printf("\n");
    }
}

//Bu fonksiyon 2 string boyutlu bir matris ekrana yazdırıyor.
//Parametreler :
    //input : yazılacak matrıs.
void print2DStringArray(char input[MAX_ROWS][MAX_COLUMNS][MAX_CHARS]){
    int i,j;
    for(i=0;i<Height;i++){
        for(j=0;j<Width;j++){
                printf("%15s",*(*(input+i)+j));
        }
        printf("\n");
    }
}


//Bu fonksiyon kullancıya seçebilecek seçenekler ekrana yazıyor.
void printMenuOptions(){
    printf("\nLutfen asagidaki seceneklerden bir secenk seciniz :");
    printf("\n\t1 - Formul hesaplama");
    printf("\n\t2 - Satir ekleme");
    printf("\n\t3 - Satir silme");
    printf("\n\t4 - Hucre degeri guncelleme");
    printf("\n\t5 - Veri filterleme");
    printf("\n\t0 - Cikis\n");
}

//Bu fonksiyon, kullancıdan "Width" kadar hücrelerin değerleri okuyor.
//Parametreler:
    //retval    :   Kullancı verdiği değerler (Çıkış parametre)
void getLineContent(char retVal[MAX_COLUMNS][MAX_CHARS]){
    int i;
    for(i=0;i<Width;i++){
        printf("\n Lutfen yeni satirinda %d. stunun degeri giriniz :",i);
        scanf("%s",(retVal+i));
    }
}

//Bu fonksiyon iki matris alıyor ve "destination" matris içinde "source" matris elemanların değerleri kopylanıyor
//Parametreler:
    //source    :    Elemanlar nereden okunalacak.
    //destination : Elemanlar nerede yazılacak
void copyLine(char source[MAX_COLUMNS][MAX_CHARS], char destination[MAX_COLUMNS][MAX_CHARS]){
    int i;
    for(i=0;i<Width;i++){
        strcpy(destination+i,source+i);
    }
}

//Bu fonksiyon copyLine fonksiyonu kullanarak 2 boyoutlu matris içinde bir satır ekliyor.
//Son satır itibaren her satır için sonraki stır'a kopylanıyor. sonra yeni satır kendi yerinde kopylanıyor.
//Böylece bizim ekleyeceğğimiz satır döğru yerinde olacak
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

    printf("\n\n\n################################################################################");
    printf("Asil Matrisi :\n----------------------------------\n");
    print2DStringArray(inputTable);
    printf("\n----------------------------------\nDegerlendiren Matris :\n----------------------------------\n");
    print2DIntArray(evaluated);
    printf("\n################################################################################");
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
            if(*((*(cellsTypes+i))+j) == 'n') //filterenebilir bir sayı
            {
                if(currNumber<=filter)
                    printf("!\t");
                else
                    printf("%d\t",currNumber);
            }else   // filterenmez bir sayı (formula olduğu için)
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
