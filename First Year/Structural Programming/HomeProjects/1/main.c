/*
	Name : Amer Sawan
	Student Number : 130401073
	Project No : 1
	Project Name : Çark Oyunu
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
This will contain the current wheel face, where each face represented with a number between 0 and 5 as following:
    0	: +50 puan
    1	: +100 puan
    2	: +250 puan
    3	: PAS
    4	: IFLAS
    5	: PUAN AZALTMA
*/
int currentWheelStatus;



//This variable will hold the current points that the user have.
int currentPoints = 250;

//These 4 variables will be used to store the random generated numbers.
int rand1, rand2, rand3, rand4;


/*
This function will print the current wheel face that is stored in the general variable "currentWheelStatus".
*/
void printWheelStatus (){
    printf("Bu defa cark (((");
    switch (currentWheelStatus){
        case 0:
            printf("+50");
            break;
        case 1:
            printf("+100");
            break;
        case 2:
            printf("+250");
            break;
        case 3:
            printf("PAS");
            break;
        case 4:
            printf("IFLAS");
            break;
        case 5:
            printf("PUAN AZALTMA");
            break;
    }
    printf("))) Cikti.\n");
}

int sayi_uret(int from, int to){
    return from + ( rand() % (to-from+1) );
}

/*
This function will simulate wheeling the wheel, by generating a random number between 0 and 5.
Each number represent one face on the wheel(mentioned above).
it'll use the general variable "currentWheelStatus" to store the final value.
*/
void cark_cevir(){
    currentWheelStatus = sayi_uret(0,5);
}


/*
This function will return weather if the given number same as one of the 4 variables (rand1, rand2, rand3 and rand4).
When the given number get equals to one of these rand numbers it'll remove it by setting its value to -1 so later it'll not used.
*/
int checkGuess(int guess){
    if(guess==-1)
        return 0;
    if(guess==rand1){
        rand1=-1;
        return 1;
    }
    if(guess==rand2){
        rand2=-1;
        return 1;
    }
    if(guess==rand3){
        rand3=-1;
        return 1;
    }
    if(guess==rand4){
        rand4=-1;
        return 1;
    }
    return 0;
}

/*
This function will ask the user to enter 4 guesses.
    Return Value : The count of the correct guesses compared to the 4 general variables (rand1, rand2, rand3 and rand4).
*/
int tahmin_gir(){

    printf("tahminleriniz 4 sayi olarak giriniz :\n");
    int n1,n2,n3,n4;
    scanf("%d%d%d%d",&n1,&n2,&n3,&n4);

    int retVal=0;

	retVal+=checkGuess(n1);
	retVal+=checkGuess(n2);
	retVal+=checkGuess(n3);
	retVal+=checkGuess(n4);

    return retVal;
}

/*
This function will generate a new random number that is different
from the value of the 4 general variables (rand1, rand2, rand3 and rand4).
*/
int generateUniqueRandom(){
    int res;
    do {
        res = sayi_uret(1,10);
    }while (res==rand1 || res == rand2 || res==rand3 || res== rand4);
    return res;
}


/*
This function will give a random value for the 4 general variables (rand1, rand2, rand3 and rand4).
The generated numbers are written on the screen only for diagnose reasons.
*/
void generateRandoms(){
    rand1=rand2=rand3=rand4=-1;
    rand1=generateUniqueRandom();
    rand2=generateUniqueRandom();
    rand3=generateUniqueRandom();
    rand4=generateUniqueRandom();
    printf("\n\n            CHEAAAAT (OYUN DISINDA) - SECILMIS RASGEL SAYILAR : %d %d %d %d\n\n",rand1,rand2,rand3,rand4);
}

/*
This function will print the current amount of points that the user have currently.
*/
void printCurrentPoints(){
    printf(" > > > > Simdi sizde %d puan var. < < < <\n",currentPoints);
}

/*
This function will tell the user that he won a specified amount of points, where :
    - correctGusses :   The number of the correct guesses that the user entered.
    - points        :   The ammount of the points that the user earned.
*/
void printPointsEarned(int correctGuesses, int points){
    printf("Tebrikler %d tahmin dogrudur. ve bunlar %d puan kazanmak icin yeterli.\n\n\t$~$~$~$~$~$~$~$~$~$  +%d Puan KAZANDINIZ!!  $~$~$~$~$~$~$~$~$~$\n\n",correctGuesses,points,points);
}


/*
This function will write an explanation in case if the user didn't achieve the required guesses for the current points, where :
    - correctGusses     :   The number of the correct guesses that the user entered.
    - points            :   The ammount of the points that the user was going to take.
    - requiredGuesses   :   How many guesses the user shall correctly enter to be able to won those points.
*/
void printNotEnougthGuesses(int correctGusses, int points,int requiredGuesses){
    printf("Maalesef sadece %d dogru tahmin ettiniz. %d puan kazanabilmek icin en az %d tane tahmin yapmaniz lazim.\n\n",correctGusses,points,requiredGuesses);
}


int main()
{
    srand( time( NULL ) );
    char option;
    do{
        printCurrentPoints();
        printf("\n===================================================\n");
        printf("Lutfen seceneginiz yazin ('c' devam icin, 's' durdurmak icin) : ");
        scanf(" %c",&option);
		switch(option){
			case 'c':
			{
				cark_cevir();
				printWheelStatus();
				if((currentWheelStatus==0) || (currentWheelStatus==1) || (currentWheelStatus==2)){ //puan kazanmak
					generateRandoms();
					printf("Bu puan kazanabilmek icin lutfen 4 sayi icin 1-10 arasinda tahminiz yazin. ");
					int correctGuesses = tahmin_gir();
					switch (currentWheelStatus){
						case 0://50 puan
							if(correctGuesses>=1){
								currentPoints += 50;
								printPointsEarned(correctGuesses,50);
							} //end if enough guesses
							else {
								printNotEnougthGuesses(correctGuesses,50,1);
							} // end if not enough guesses
							break;
						case 1://100 puan
							if(correctGuesses>=2){
								currentPoints += 100;
								printPointsEarned(correctGuesses,100);
							} //end if enough guesses
							else {
								printNotEnougthGuesses(correctGuesses,100,2);
							} // end if not enough guesses
							break;
						case 2://250 puan
							if(correctGuesses>=3){
								currentPoints += 250;
								printPointsEarned(correctGuesses,250);
							} //end if enough guesses
							else {
								printNotEnougthGuesses(correctGuesses,250,3);
							} // end if not enough guesses
							break;
					} // end of switch
				} // end if points increment
				else if (currentWheelStatus == 3){ //PAS
					printf("Puaniniz etkelenmeyecek.\n");
				} //end if PAS
				else if (currentWheelStatus == 4){ //IFLAS
					printf("#############   IFLAS OLDUNUZ MAALESEF!   #############\n");
					currentPoints=0;
				} //end if insolvency
				else if (currentWheelStatus == 5){ //PUAN AZALTMA
					printf("&&&&&&&&&&&&& PUANINIZDAN 25%% KESELECEK!   &&&&&&&&&&&&&\n");
					currentPoints*=0.75;
				} // end if points decrease
				break;
			} // end of the case 'c'
			case 's':
			{
				printf("Oyun sonlandirilmaya sectiniz.\n");
				break;
			} //end of the case 's'
			default:
			{
				printf("Yanlis secenek yazdiniz, devam etmek icin \"c\" yaziniz ya da \"s\" durdurmak icin.\n");
				break;
			} // end of switch's default
		} //end of switch
        if(currentPoints==0){
            printf("Puaniniz 0 oldugu icin oyun sonlandirilacak.");
        }
    }while((option != 's') && (currentPoints!=0));
    printf("\n\n###############################################\n\t\tOYUN BITTI\n###############################################\n\n");
    return 0; // Terminate the program with exit code: 0
} //end of the main function
