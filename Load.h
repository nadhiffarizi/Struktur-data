#ifndef Load_H
#define Load_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct group_t {
    char *praktikum; //nama praktikum
    char *rombongan; //nama rombongan
}Group;

typedef struct asprak_t {
    char *nama; //nama asprak
    char code; //kode asprak
    char *praktikum[3];//tiap asprak bisa megang 3 praktikum
    char *berhalangan[3]; //tiap asprak bisa punya 3 hari halangan
}Asprak;

typedef struct lab_t {
    char *element; //nama lab
    Group  group; //tiap lab cuma ada 1 rombongan
    Asprak  asprak[2]; //tiap lab ada dua asprak
}Lab;

typedef struct day_t {
    char *element; //nama hari
    Lab lab [4]; //tiap hari ada 4 lab
}Day;

typedef struct week_t {
    int element; //nama minggu salam integer
    Day day[5]; //tiap mingu ada 5 hari
} Week;

typedef struct schedule_t {
    Week week [12]; //dalam jadwal ada 12 minggu
} Schedule;


//structur data asisten
//buat struktur data asisten sebagai database berisi data-data asisten
typedef struct dataAsprak_t {
   Asprak asprak [14]; //
} dataAsprak;


void loadJadwal(char * filename, Schedule * jadwal);
void loadStatus( char * filename, Schedule * jadwal);
void saveJadwal(char const * filename , Schedule jadwal);
void saveStatus(char const * filename , Schedule jadwal);
void FprintSchedule(Schedule jadwal, FILE *file);
void FprintStatus(Schedule jadwal, FILE *file);
char* copyStr(int a, int b,char const * string);
void shift(char buff[],int *cursor_str, int *cursor_end, char sep_1, char sep_2, char sep_3);
void assignWeek(Schedule ** jadwal,int i_minggu, int cursor_str, int cursor_end, char buff[]);
void assignDay(Schedule ** jadwal,int i_minggu,int i_hari, int cursor_str, int cursor_end, char buff[]);
void assignPraktikum(Schedule ** jadwal,int i_minggu,int i_hari,int z, int cursor_str, int cursor_end, char buff[]);
void assignRombongan(Schedule ** jadwal,int i_minggu,int i_hari,int z, int cursor_str, int cursor_end, char buff[]);
void isPraktikumEmpty(bool *isEmpty,char buff[],int *cursor_str, int* cursor_end);
bool isStringNull( const char * string);
void assignDataAsprak (dataAsprak *Asprak);
void printDataAsprak ( dataAsprak Asprak);
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
                
/*-------------Cara akses database asisten-----------------/*
/*berikut bukan data yang akan dicetak atau disimpan ke dalam file, namun digunakan untuk menyimpan data-data asisten
//deklarasi
    database Asprak;
//akses nama
    Asprak.asprak[i].nama;
//akses code
    Asprak.asprak[i].code;
//akses paktikum yang dihandle asisten
    Asprak.asprak[i].praktikum[j;
//akses hari halangan asisten
    Asprak.asprak[i].berhalangan[j];

*****TIDAK PERLU ASSIGN ULANG KARENA SUDAH DI ISI PAKE PROSEDUR VOID AssignDataAsprak(dataAsprak *Asprak) *********************
