#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 21 //Cunku son harf her zaman \0 harfi ve bu harf sayilmaz
#define MAX_LESSONS_PER_STUDENT 10
#define MAX_STUDENTS_COUNT 100
#define MAX_LESSONS_COUNT 20

#define STUDENTS_FILENAME "Ogrenci.bin"
#define LESSONS_FILENAME "Dersler.bin"

struct student{
    char FirstName[MAX_STRING_LENGTH];
    char LastName[MAX_STRING_LENGTH];
    int Number;
    int SubscribedLessons[MAX_LESSONS_PER_STUDENT];
};


struct lesson{
    char Name[MAX_STRING_LENGTH];
    int Code;
};

typedef struct student Student;
typedef struct lesson Lesson;

/*
    Bu fonksiyon aldığı öğrencinin numarası karşıya öğrencinin bilgileri döndüruruyor.
Parametreler :
    num :   öğrencinin numarası
Returned Value :
    Bu numara sahip olan öğrenci (Student struct olarak)
*/
Student getStudentByNumber(int num){
    FILE *studentsFile;
    if((studentsFile=fopen(STUDENTS_FILENAME,"rb"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",STUDENTS_FILENAME);
        exit(-3324442);
    }
    else{
        Student retval;
        fseek(studentsFile,sizeof(int)+sizeof(Student)*(num-1),SEEK_SET);//Cunku ilk 4 byte kac ogrenci var saklaniyoruz
        fread(&retval,sizeof(Student),1,studentsFile);
        fclose(studentsFile);
        return retval;
    }
}

/*
    Bu fonksiyon aldığı dersin numarası karşıya dersin bilgileri döndüruruyor.
Parametreler :
    num :   dersin numarası
Returned Value :
    Bu numara sahip olan ders (Ders struct olarak)
*/
Lesson getLessonByNumber(int num){
    FILE *lessonsFile;
    if((lessonsFile=fopen(LESSONS_FILENAME,"rb"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",LESSONS_FILENAME);
        exit(-3324442);
    }
    else{
        Lesson retval;
        fseek(lessonsFile,sizeof(int)+sizeof(Lesson)*(num-1),SEEK_SET);//Cunku ilk 4 byte kac ogrenci var saklaniyoruz
        fread(&retval,sizeof(Lesson),1,lessonsFile);
        fclose(lessonsFile);
        return retval;
    }
}

/*
    Bu fonksiyon dersler dosyasından ilk 4 byte yer alan derslerin sayısı okuyup, bu sayı donduruyor
Parametreler:
    YOK
Returned Value :
    Derslerin sayısı
*/
int GetLessonsCount(){
    FILE *lessonssFile;
    if((lessonssFile=fopen(LESSONS_FILENAME,"rb"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",LESSONS_FILENAME);
        return 0;
    }
    else{
        //fseek(lessonssFile,-4,SEEK_END);
        int retVal;
        fread(&retVal,sizeof(int),1,lessonssFile);
        fclose(lessonssFile);
        return retVal;
    }
}

/*
    Bu fonksiyon öğrencilerin dosyasından ilk 4 byte yer alan öğrencilerin sayısı okuyup, bu sayı donduruyor
Parametreler:
    YOK
Returned Value :
    Öğrencilerin sayısı
*/
int GetStudentsCount(){
    FILE *studentsFile;
    if((studentsFile=fopen(STUDENTS_FILENAME,"rb"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",STUDENTS_FILENAME);
        return 0;
    }
    else{
        //fseek(studentsFile,-4,SEEK_END);
        int retVal;
        fread(&retVal,sizeof(int),1,studentsFile);
        fclose(studentsFile);
        return retVal;
    }
}

/*
    Bu fonksiyon kunnalncıdan öğrencilerin detayları okuyor ve onu donduruyor.
Parametreler:
    YOK
Returned Value:
    Öğrencinin bilgileri (Studett struct olarak)
*/
Student readNewStudentData(){
    Student retVal;

    printf("\nLutfen ogrencinin adi giriniz : ");
    scanf("%s",retVal.FirstName);

    printf("\nLutfen ogrencinin Soy adi giriniz : ");
    scanf("%s",retVal.LastName);
    int i;

    //Default olarak butun aldığı dersler -1 yapıyoruz
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        retVal.SubscribedLessons[i]=-1;
    }
    return retVal;
}

/*
    Bu fonksiyon kullancıdan yeni ders bilgileri okuyor ve onu donduruyor
Parametreler:
    YOK
Returned Value:
    Dersin bilgileri (Lesson struct olarak)
*/
Lesson readNewLessonData(){
    Lesson retVal;

    printf("\nLutfen dersin adi giriniz : ");
    scanf("%s",retVal.Name);

    return retVal;
}

/*
    Bu fonksiyon aldığı dosya ismi, mevcud değil ise, yeni boş bir dosya yapıyor
Parametreler:
    filename    :   Dosyanın ismi
Returned value :
    YOK
*/
static void CreateFileIfNotExisted(char *filename){
    FILE *file;
    if((file=fopen(filename,"r"))==NULL){//demek ki mevcud değil
        file=fopen(filename,"a");//append mode olarak açtığımızda yeni bir dosya oluşturacak
        fwrite(0,sizeof(int),1,file);//0 yazıyorum çünkü bu sayı (dosyanın ilk 4 byte) bu dosyada kaç record (öğrenci ya da ders) var gösteriyor
        fclose(file);
    }

}

/*
    Bu fonksiyon öğrencilerin dosyasında verilen öğreci bilgileri kendi yerinde yazdırıyor, önceden varsa onu güncelleniyor, eğer yoksa yeniden yazdırıyor
Parametreler :
    student     :   Öğrencinin bilgileri
    updateCount :   Dosyanın başlangıçta bulunan 4 byte'lik sayısı öğrencilerin sayısı güncelleme yada güncelememesi gösteriyor
*/
void appendStudent (Student student, int updateCount){
    FILE *studentsFile;
    CreateFileIfNotExisted(STUDENTS_FILENAME);
    if((studentsFile=fopen(STUDENTS_FILENAME,"r+b"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",STUDENTS_FILENAME);
        exit (-500);//program bitiriyoruz çünkü daha yapabilecek bir şey yok
    }
    else{

        //ilk önce dosyanın pointeri doğru yerinde aktarıyoruz
        //ilk sizeof(int) çünkü öğrencilerin sayısı dosyanın başında var.
        fseek(studentsFile,sizeof(int) + sizeof(student)*(student.Number-1),SEEK_SET);
        fwrite(&student,sizeof(student),1,studentsFile);

        if(updateCount){
            fseek(studentsFile,0,SEEK_SET);
            fwrite(&student.Number,sizeof(int),1,studentsFile);
        }

        fclose(studentsFile);
    }
}

/*
    Bu fonksiyon derslerin dosyasında verilen ders bilgileri kendi yerinde yazdırıyor, önceden varsa onu güncelleniyor, eğer yoksa yeniden yazdırıyor
Parametreler :
    lesson     :   ders bilgileri
    updateCount :   Dosyanın başlangıçta bulunan 4 byte'lik sayısı derslerin sayısı güncelleme yada güncelememesi gösteriyor
*/
void appendLesson (Lesson lesson, int updateCount){
    FILE *lessonsFile;
    CreateFileIfNotExisted(LESSONS_FILENAME);
    if((lessonsFile=fopen(LESSONS_FILENAME,"r+b"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",LESSONS_FILENAME);
        exit (-500);
    }
    else{

        fseek(lessonsFile,sizeof(int) + sizeof(lesson)*(lesson.Code-1),SEEK_SET);
        fwrite(&lesson,sizeof(lesson),1,lessonsFile);

        if(updateCount){
            fseek(lessonsFile,0,SEEK_SET);
            fwrite(&lesson.Code,sizeof(int),1,lessonsFile);
        }
        fclose(lessonsFile);
    }
}

/*
    Bu fonksiyon aldiğı öğrenci yapı'den isim ve soyisimini birlişip donduruyor
Parametreler:
    student :   student yapı
Returned Value :
    fullname: (çıkış parametre) isim parçaların birleştikten sonra
*/
void getFullName(Student student, char fullName[MAX_STRING_LENGTH*2+1]){
    strcpy(fullName,"");
    //char fullName[MAX_STRING_LENGTH*2]="";
    strcat(fullName,student.FirstName);
    strcat(fullName," ");
    strcat(fullName,student.LastName);
    return fullName;
}


/*
    Bu fonksiyon öğrencilerin dosyasında bulunan butun öğrencilerin kayıtları birer birer okuyup ekrana yazdırıyor
Parametreler:
    studentsCount   :   Bu dosyada kaç tane öğrenci var
*/
void printStudentsList(int studentsCount){
    int i;
    if(studentsCount == 0){
        printf("\n\nSistemde hic ogrenciler yok.\n");
        return;
    }
    printf("\n\nSistem'deki bulunan Ogrenciler:\n");
    for(i=0;i<studentsCount;i++){
        Student s = getStudentByNumber(i+1);

        char fullName[40]="";
        strcat(fullName,s.FirstName);
        strcat(fullName," ");
        strcat(fullName,s.LastName);

        printf("%2d-%-32s  ",s.Number,fullName);
        printf(((i+1)%2==0)?"\n":"");
    }
    printf("\n\n");
}

/*
    Bu fonksiyon derslerin dosyasında bulunan butun derslerin kayıtları birer birer okuyup ekrana yazdırıyor
Parametreler:
    lessonsCount   :   Bu dosyada kaç tane ders var
*/
void printLessonssList(int lessonsCount){
    int i;
    if(lessonsCount == 0){
        printf("\n\nSistemde hic dersler yok.\n");
        return;
    }
    printf("\n\nSistem'deki bulunan dersler:\n");
    for(i=0;i<lessonsCount;i++){
        Lesson l = getLessonByNumber(i+1);
        printf("%2d-%-20s",l.Code,l.Name);
        printf(((i+1)%3==0)?"\n":"    ");
    }
    printf("\n");
}


/*
    Bu fonksiyon aldığı öğrencinin kayıta, aldığı ders kodu öğrencini derslere ekliyor
Parametreler :
    student     :   Eklenecek öğrencinin kayıta bir işaretçi
    lessonCode  :   dersin kodu
Returned Value :
    -2    :  Bu derste zaten kayitli
    -1    :  Daha bir ders eklenmez, maximum ulaştı
    1     :  Başarıyla eklendi
*/
int subscribeToLesson(Student *student, int lessonCode){
    int i;
    int subscribedLessonsCount=0;
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){

        //-1 demek boş olan bir ders
        if(student->SubscribedLessons[i] == -1)
            break;

        //Ekleyeceğiz dersi bulduk ise
        if(student->SubscribedLessons[i]==lessonCode)
            return -2;

        //Derslerin sayısı
        subscribedLessonsCount++;
    }

    //bu öğrencinin aldığı derslerden fazla alamaz
    if(subscribedLessonsCount == MAX_LESSONS_PER_STUDENT){
        return -1;
    }

    student->SubscribedLessons[i] = lessonCode;
    return 1;
}

/*
    Bu fonksiyon kullancıdan ders kodu isteyecek, ve doğru ders kodu okudu kadar yeniden soracak
Parametreler:
    message :   Ekrana her zamam yazılacak messag
    lessonsCount    : şimdiye kadar kaç tane ders kayıtlı (dersin kodu doğru ya da yanlış olduğunu kontrol etmek için bize lazım)
Returned Value:
    Dersin kodu
*/
int askForLesson(char *message, int lessonsCount){
    printLessonssList(lessonsCount);
    int lessonNumber;
    do{
        printf("%s",message);
        scanf("%d",&lessonNumber);
        if((lessonNumber>lessonsCount) || (lessonNumber<1)){
            printf("Bu ders mevcut degil.\n");
        }
    }while((lessonNumber>lessonsCount) || (lessonNumber<1));
    return lessonNumber;
}


/*
    Bu fonksiyon kullancıdan öğrenci numara isteyecek, ve doğru ders kodu okudu kadar yeniden soracak
Parametreler:
    message :   Ekrana her zamam yazılacak messag
    studentsCount    : şimdiye kadar kaç tane öğrenci kayıtlı (öğreninin numarası doğru ya da yanlış olduğunu kontrol etmek için bize lazım)
Returned Value:
    Öğrencinin numarası
*/
int askForStudent(char *message, int studentsCount){
    printStudentsList(studentsCount);
    int studentNumber;
    do{
        printf("%s",message);
        scanf("%d",&studentNumber);
        if((studentNumber>studentsCount) || (studentNumber<1)){
            printf("Bu ogrenci mevcut degil.\n");
        }
    }while((studentNumber>studentsCount) || (studentNumber<1));
    return studentNumber;
}

/*
    Bu fonksiyon bir student yapı alıyor, ve onun içindeki bulunan derslerin kodları birer birer alıp, dersin ismi ekrana yazdırıyor
Parametreler:
    student :   öğrencinin detayları
*/
void listSubscribedLessons(Student student){
    int i;
    char fullName[MAX_STRING_LENGTH*2+1];
    getFullName(student,fullName);
    printf("\n\n%s 'nin aldigi dersler :\n",fullName);
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        if(student.SubscribedLessons[i]==-1)
            break;
        Lesson currentLesson = getLessonByNumber(student.SubscribedLessons[i]);
        printf("\t>%2d-%s\n",currentLesson.Code, currentLesson.Name);
    }
    if(i==0)//Hic dersler yok ise
        printf("Bu ogrenci hic bir derste kayitli degil\n");
}

/*
    Bu fonksiyon aldığı int listede bir anahtara arıyor
Parametreler :
    list    :   int listesi
    key     :   Hangi anahtara arayacak.
Returned Value :
    1   :   Bulundu ise
    0   :   Bulunmadı ise
*/
int isExisted(int list[MAX_LESSONS_PER_STUDENT], int key){
    int i;
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        if(list[i]==key)
            return 1;
    }
    return 0;
}

/*
    Bu fonksiyon butun öğrencilere dolaşıp ve bu öğrecini eğer bu ders alıyorrsa ismini ekrana yazdıracak.
Parametreler :
    lessonCode  :   Hangi ders kodu hakkında arıyoruz.
    studentsCount   :   Öğrencilerin sayısı
*/
void listLessonSubscribers(int lessonCode, int studentsCount){
    int subscribersCount = 0;
    int i;
    printf("\n");
    for(i=0;i<studentsCount;i++){
        Student student = getStudentByNumber(i+1);
        if(isExisted(student.SubscribedLessons, lessonCode)){
            subscribersCount++;
            char fullName[MAX_STRING_LENGTH*2+1];
            getFullName(student,fullName);
            printf("\t>%2d-%s\n",student.Number,fullName);
        }
    }
    if(subscribersCount==0){
        printf("Bu derste hic bir ogrencinin kayidi yok");
    }
}

int main(){
    //Program başlandığımızda kaç öğrenci/ders var olduğunu okuyoruz, çünkü bundan sonra devam edeceğiz
    int studentsCount, lessonsCount;
    studentsCount = GetStudentsCount();
    lessonsCount = GetLessonsCount();

    int option;
    do{
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n>",
               "----------------------------------------------------",
               "1 - Ogrenci Ekle",
               "2 - Ders Ekle",
               "3 - Ogrenciyi derse kaydet",
               "4 - Ogrenci derslerini listle",
               "5 - Dersi alan ogrenciler listle",
               "6 - Dersler listle",
               "7 - Ogrenciler listle",
               "0 - Cikis");
        scanf("%d",&option);
        switch(option){
            case 1:{//Ogrenci Ekle
                Student newStudent = readNewStudentData();
                newStudent.Number = ++studentsCount;
                appendStudent (newStudent,1);
                break;
            }
            case 2:{//Ders Ekle
                Lesson newLesson = readNewLessonData();
                newLesson.Code = ++lessonsCount;
                appendLesson(newLesson,1);
                break;
            }
            case 3:{//Ogrenciyi derse kaydet
                if(studentsCount == 0){
                   printf("Hic ogrenciler yok, lutfen once ogrenciler ekleyiniz.\n");
                   break;
                }
                if(lessonsCount == 0){
                   printf("Hic dersler yok, lutfen once dersler ekleyiniz.\n");
                   break;
                }

                int studentNumber = askForStudent("Hangi ogrenciye dersi ekleyeceksiniz (Numarasini giriniz lutfen) :",studentsCount);
                int lessonNumber = askForLesson("Hangi ders ekleyeceksiniz (Kodunu giriniz lutfen) : ",lessonsCount);

                Student selectedStudent = getStudentByNumber(studentNumber);

                int res = subscribeToLesson(&selectedStudent,lessonNumber);

                if(res == -1) printf("Bu Ogrenci daha bir ders alamaz.\n");
                if(res == -2) printf("Bu ogrenci bu ders'te zaten kayitli\n");
                if(res == 1){
                    appendStudent(selectedStudent,0);
                    printf("Basariliyla bu ders kayidedildi\n");
                }
                break;
            }
            case 4:{//Ogrenci derslerini listle
                if(studentsCount == 0){
                   printf("Hic ogrenciler yok, lutfen once ogrenciler ekleyiniz.\n");
                   break;
                }
                int studentNumber = askForStudent("Hangi ogrencinin dersleri listleyeceksiniz (Numarasini giriniz lutfen) : ",studentsCount) ;
                Student selectedStudent = getStudentByNumber(studentNumber);
                listSubscribedLessons(selectedStudent);
                break;
            }
            case 5:{//Dersi alan ogrenciler listle
                if(lessonsCount == 0){
                   printf("Hic dersler yok, lutfen once dersler ekleyiniz.\n");
                   break;
                }
                int lessonNumber = askForLesson("Hangi dersin ogrencileri listleyeceksiniz (Kodunu giriniz lutfen) : ", lessonsCount);
                listLessonSubscribers(lessonNumber, studentsCount);
                break;
            }
            case 6:
                printLessonssList(lessonsCount);
                break;
            case 7:
                printStudentsList(studentsCount);
                break;
        }
    }while(option != 0);
    return 0;
}
