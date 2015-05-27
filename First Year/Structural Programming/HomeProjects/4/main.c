#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 20
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

Student readNewStudentData(){
    Student retVal;

    printf("\nLutfen ogrencinin adi giriniz : ");
    scanf("%s",retVal.FirstName);

    printf("\nLutfen ogrencinin Soy adi giriniz : ");
    scanf("%s",retVal.LastName);
    int i;

    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        retVal.SubscribedLessons[i]=-1;
    }
    return retVal;
}

Lesson readNewLessonData(){
    Lesson retVal;

    printf("\nLutfen dersin adi giriniz : ");
    scanf("%s",retVal.Name);

    return retVal;
}

static int CreateFileIfNotExisted(char *filename){
    FILE *file;
    if((file=fopen(filename,"r"))==NULL){
        file=fopen(filename,"a");
        fwrite(0,sizeof(int),1,file);
        fclose(file);
    }

}

void appendStudent (Student student, int updateCount){
    FILE *studentsFile;
    CreateFileIfNotExisted(STUDENTS_FILENAME);
    if((studentsFile=fopen(STUDENTS_FILENAME,"r+b"))==NULL){
        printf("Hata oldu, \"%s\" dosyasi acilamadi\n",STUDENTS_FILENAME);
        exit (-500);
    }
    else{

        fseek(studentsFile,sizeof(int) + sizeof(student)*(student.Number-1),SEEK_SET);
        fwrite(&student,sizeof(student),1,studentsFile);

        if(updateCount){
            fseek(studentsFile,0,SEEK_SET);
            fwrite(&student.Number,sizeof(int),1,studentsFile);
        }
        fclose(studentsFile);
    }
}

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

void printStudentsList(int studentsCount){
    int i;
    printf("\n");
    for(i=0;i<studentsCount;i++){
        Student s = getStudentByNumber(i+1);

        char fullName[40]="";
        strcat(fullName,s.FirstName);
        strcat(fullName," ");
        strcat(fullName,s.LastName);

        printf("%2d-%-32s  ",s.Number,fullName);
        printf(((i+1)%2==0)?"\n":"");
    }
    printf("\n");
}

void printLessonssList(int lessonsCount){
    int i;
    printf("\n");
    for(i=0;i<lessonsCount;i++){
        Lesson l = getLessonByNumber(i+1);
        printf("%2d-%-20s",l.Code,l.Name);
        printf(((i+1)%3==0)?"\n":"    ");
    }
    printf("\n");
}


/*
Returned Value :
    -2    :  Bu derste zaten kayitli
    -1    :  daha bir ders eklenmez
    1     :  Success
*/
int subscribeToLesson(Student *student, int lessonCode){
    int i;
    int subscribedLessonsCount=0;
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){

        if(student->SubscribedLessons[i] == -1)
            break;

        if(student->SubscribedLessons[i]==lessonCode)
            return -2;

        subscribedLessonsCount++;
    }

    if(subscribedLessonsCount == MAX_LESSONS_PER_STUDENT){
        return -1;
    }

    student->SubscribedLessons[i] = lessonCode;
    return 1;
}

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
void listSubscribedLessons(Student student){
    int i;
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        if(student.SubscribedLessons[i]==-1)
            break;
        Lesson currentLesson = getLessonByNumber(student.SubscribedLessons[i]);
        printf("%s\n",currentLesson.Name);
    }
    if(i==0)//Hic dersler yok ise
        printf("Bu ogrenci hic bir derste kayitli degil\n");
}

int isExisted(int list[MAX_LESSONS_PER_STUDENT], int key){
    int i;
    for(i=0;i<MAX_LESSONS_PER_STUDENT;i++){
        if(list[i]==key)
            return 1;
    }
    return 0;
}

void listLessonSubscribers(int lessonCode, int studentsCount){
    int subscribersCount = 0;
    int i;
    for(i=0;i<studentsCount;i++){
        Student student = getStudentByNumber(i+1);
        if(isExisted(student.SubscribedLessons, lessonCode)){
            subscribersCount++;
            char fullName[40]="";
            strcat(fullName,student.FirstName);
            strcat(fullName," ");
            strcat(fullName,student.LastName);
            printf("%2d-%-41\n",student.Number,fullName);
        }
    }
    if(subscribersCount==0){
        printf("Bu derste hic bir ogrencinin kayidi yok");
    }
}

int main()
{
    int studentsCount, lessonsCount;
    studentsCount = GetStudentsCount();
    lessonsCount = GetLessonsCount();

    int option;
    do{
        printf("\n%s\n%s\n%s\n%s\n%s\n%s\n>",
               "1 - Ogrenci Ekle",
               "2 - Ders Ekle",
               "3 - Ogrenciyi derse kaydet",
               "4 - Ogrenci derslerini listle",
               "5 - Dersi alan ogrenciler listle",
               "6 - Cikis");
        scanf("%d",&option);
        switch(option){
            case 1:{
                Student newStudent = readNewStudentData();
                newStudent.Number = ++studentsCount;
                appendStudent (newStudent,1);
                break;
            }
            case 2:{
                Lesson newLesson = readNewLessonData();
                newLesson.Code = ++lessonsCount;
                appendLesson(newLesson,1);
                break;
            }
            case 3:{
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
            case 4:{
                if(studentsCount == 0){
                   printf("Hic ogrenciler yok, lutfen once ogrenciler ekleyiniz.\n");
                   break;
                }
                int studentNumber = askForStudent("Hangi ogrencinin dersleri listleyeceksiniz (Numarasini giriniz lutfen) : ",studentsCount) ;
                Student selectedStudent = getStudentByNumber(studentNumber);
                listSubscribedLessons(selectedStudent);
            }
            case 5:{
                if(lessonsCount == 0){
                   printf("Hic dersler yok, lutfen once dersler ekleyiniz.\n");
                   break;
                }
                int lessonNumber = askForLesson("Hangi dersin ogrencileri listleyeceksiniz (Kodunu giriniz lutfen) : ", lessonsCount);
                listLessonSubscribers(lessonNumber, studentsCount);
            }
        }
    }while(option != 6);

    return 0;
    FILE *ff ;
    ff=fopen("a.bin","w+");
    fseek(ff,300,SEEK_SET);
    int x=10;
    fwrite(&x,sizeof(int),1,ff);
    fclose(ff);
    return 0;
}
