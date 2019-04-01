#ifndef Load_H
#define Load_H
#include <stdio.h>
#include <string.h>

typedef struct group {
    char praktikum[6];
    char rombongan[2];
}Group;

typedef struct asprak {
    char name [10];
    char code[2];
    char praktikum [6][3];
    char berhalangan [6][3];
}Asprak;

typedef struct lab {
    Group  group;
    Asprak  asprak[2]; 
}Lab;
typedef struct day {
    Lab lab [3];
}Day;

typedef struct week_t {
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

#endif


