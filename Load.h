#ifndef Load_H
#define Load_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct group {
    char *praktikum;
    char *rombongan;
}Group;

typedef struct asprak {
    char *nama;
    char *code;
    char *praktikum[3];
    char *berhalangan[3];
}Asprak;

typedef struct lab {
    char *element;
    Group  group;
    Asprak  asprak[2]; 
}Lab;
typedef struct day {
    char *element;
    Lab lab [4];
}Day;

typedef struct week_t {
    int element;
    Day day[5];
} Week;

typedef struct schedule_t {
    Week week [12];
} Schedule;

typedef struct temp_t {
    int minggu;
    char hari[6];
    char ruangan [4];
    char kode [6];
    char rombongan [2];
    char lab [4];
} Temp;


void loadData(char * filename, Schedule * jadwal);
void saveData(char const * filename , Schedule jadwal);
void printSchedule(Schedule jadwal);
void FprintSchedule(Schedule jadwal, FILE *file);
char* copyStr(int a, int b,char const * string);

#endif


/*---------------------Cara Akses------------------------*/
/* Membuat Variabel dengan tipe bentukan Schedule
Schedule Jadwal;
Mengakses Minggu
    Jadwal.week[i].element; 
mengakses Hari
    Jadwal.week[i].day[j].element;
mengakses Lab
    Jadwal.week[i].day.[j].lab[k].element; {nama lab}
Mengakses Group praktikum
    Jadwal.week[i].day.[j].lab[k].group.praktikum; {nama praktikum}
    Jadwal.week[i].day.[j].lab[k].group.rombongan; {nama rombongan}
Mengakses Asisten
    Jadwal.week[i].day.[j].lab[k].asprak.nama;
    Jadwal.week[i].day.[j].lab[k].asprak.code;
    Jadwal.week[i].day.[j].lab[k].asprak.praktikum[z];
    Jadwal.week[i].day.[j].lab[k].asprak.berhalangan[z];
Cara assign string
    misal mau ngisi nama praktikum dan rombongan
    
                char const * praktikum;
                char const * rombongan;
                praktikum = "EL2205";
                romgongan = "A1"
                //alokasi memori
                jadwal.week[i].day[j].lab[z].group.praktikum = malloc (strlen(praktikum)+1);
                jadwal.week[i].day[j].lab[z].group.rombongan = malloc (strlen(rombongan)+1);
                //copy ke jadwal
                strcpy(jadwal.week[i].day[j].lab[z].group.rombongan, rombongan);
                strcpy(jadwal.week[i].day[j].lab[z].group.praktikum, praktikum);
