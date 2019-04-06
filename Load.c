//Implementasi Load.H
#include "Load.h"

void loadJadwal(char * filename, Schedule *jadwal){
    // Schedule jadwal;
    FILE *file;
    char buff[71];

    file = fopen(filename, "r" );
    int count=0;
    int i_minggu = 0, i_hari= 0, i_lab;
    while (fgets(buff, 71, file) != NULL){
        count++;
        int cursor_str = 0;
        int cursor_end = 0;

        //printf("%d\n", count);
        //bagian ambil data
        if ((count >=11)&&(count %2 == 1)&&(*(buff+1) != '-')){
        //parsing minggu
            shift(buff,&cursor_str, &cursor_end, '|',' ',' ');
            // salin minggu ke variabel minggu
            assignWeek(&jadwal, i_minggu, cursor_str, cursor_end, buff);
           
        //parsing hari
            //cursor geser dulu
            shift(buff,&cursor_str,&cursor_end, '|',' ',' ');
            //salin hari ke variabel hari
            assignDay(&jadwal, i_minggu, i_hari, cursor_str, cursor_end, buff);

        //parsing lab
            for (int z = 0; z<4; z++){
                //cursor geser dulu sampe ketemu separator |
                shift(buff,&cursor_str, &cursor_end, ' ',' ','|');
                bool isEmpty = false;
                isPraktikumEmpty(&isEmpty,buff, &cursor_str, &cursor_end);
                if (isEmpty== true) {
                    //assign praktikum dan rombongan dengan NULL
                    jadwal->week[i_minggu].day[i_hari].lab[z].group.praktikum = NULL;
                    jadwal->week[i_minggu].day[i_hari].lab[z].group.rombongan = NULL;
                }
                else {
                    shift(buff,&cursor_str, &cursor_end, '|',' ','-');
                    assignPraktikum(&jadwal, i_minggu, i_hari,z, cursor_str, cursor_end, buff);
                
                    ///geser cursor buat dapetin rombongan
                    shift(buff,&cursor_str,&cursor_end, '|','-',' ');
                    assignRombongan(&jadwal, i_minggu, i_hari,z, cursor_str, cursor_end, buff);

                }
                
            }
            i_hari ++;
            if (i_hari >4){
                i_hari = 0;
                i_minggu ++;
            }

        }
    }
    fclose(file);
}

void loadStatus( char * filename, Schedule * jadwal){
    // Schedule jadwal;
    FILE *file;
    char buff[71];

    file = fopen(filename, "r" );
    int count=0;
    int i_minggu = 0, i_hari= 0, i_lab;
    while (fgets(buff, 71, file) != NULL){
        count++;
        int cursor_str = 0;
        int cursor_end = 0;

        //printf("%d\n", count);
        //bagian ambil data
        if ((count >=11)&&(count %2 == 1)&&(*(buff+1) != '-')){
        //parsing minggu
            shift(buff,&cursor_str, &cursor_end, '|',' ',' ');
            // salin minggu ke variabel minggu
            assignWeek(&jadwal, i_minggu, cursor_str, cursor_end, buff);
           
        //parsing hari
            //cursor geser dulu
            shift(buff,&cursor_str,&cursor_end, '|',' ',' ');
            //salin hari ke variabel hari
            assignDay(&jadwal, i_minggu, i_hari, cursor_str, cursor_end, buff);

        //parsing lab
            for (int z = 0; z<4; z++){
                //cursor geser dulu sampe ketemu separator |
                shift(buff,&cursor_str, &cursor_end, ' ',' ','|');
                bool isEmpty = false;
                isPraktikumEmpty(&isEmpty,buff, &cursor_str, &cursor_end);
                if (isEmpty== true) {
                    //assign praktikum dan rombongan dengan NULL
                    jadwal->week[i_minggu].day[i_hari].lab[z].asprak[0].code = '\0';
                    jadwal->week[i_minggu].day[i_hari].lab[z].asprak[1].code = '\0';
                }
                else {
                    shift(buff,&cursor_str, &cursor_end, '|',' ',',');
                    jadwal->week[i_minggu].day[i_hari].lab[z].asprak[0].code = buff[cursor_str];
                    ///geser cursor buat dapetin rombongan
                    shift(buff,&cursor_str,&cursor_end, '|',',',' ');
                    jadwal->week[i_minggu].day[i_hari].lab[z].asprak[1].code = buff[cursor_str];

                }
                
            }
            i_hari ++;
            if (i_hari >4){
                i_hari = 0;
                i_minggu ++;
            }

        }
    }
    fclose(file);
}

void isPraktikumEmpty(bool *isEmpty,char buff[], int *cursor_str, int * cursor_end){
    *cursor_str +=1;
    //printf("\ncursor str awal %d", *cursor_str);
    //printf("\nbuff %c\n", buff[*cursor_str]);
    while (buff[*cursor_str] == ' '){
        *cursor_str +=1;
    }
    // printf("cursor str akhir %d\n", *cursor_str);
    if (buff[*cursor_str] == buff[*cursor_end]){
        //printf("str %c end %c", buff[*cursor_str], buff[*cursor_end]);
        *isEmpty = true;
        *cursor_end = *cursor_str;
        //printf("\ncursor end true : %d %d", *cursor_str, *cursor_end);
    }
    else { //tidak kosong maka kembalikan cursor str ke semula
        *isEmpty = false;
        //lanjut element berikutnya
        *cursor_str = *cursor_end;
        //printf("\ncursor end  false: %d", *cursor_end);

    }
}

char* copyStr(int a, int b,char const * string){
    const char* from = string;
    char *to = (char*) malloc(b-a);
    strncpy(to, from+a, b-a);
    return to;
}

void saveJadwal(char const * filename, Schedule jadwal){
    FILE *file;
    file = fopen(filename, "w");
    FprintSchedule(jadwal, file);
    fclose(file);
}

void saveStatus( char const *filename, Schedule jadwal){
    FILE *file;
    file = fopen(filename, "w");
    FprintStatus(jadwal, file);
    fclose(file);
}
void printSchedule(Schedule jadwal){
    //mencetak header
    printf("|----------------|------------|------------|------------|------------|");
    //|Ruang Praktikum | LAB1 | LAB2 | LAB3 | LSS |
    printf("\n|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |");
    //mencetak header
    printf("\n|----------------|------------|------------|------------|------------|");
    //|Minggu | Hari |------------|------------|------------|-----------|
    printf("\n|Minggu |  Hari  |------------|------------|------------|------------|\n");
    printf("|----------------|------------|------------|------------|------------|");
    for (int i = 0; i< 12; i++){
        printf("\n");
        //separator
        for (int j = 0; j < 5; j++){
            //print minggu
            printf("|%4d%4c",jadwal.week[i].element,'|');
            //print hari
            int space = 8 - strlen(jadwal.week[i].day[j].element);
            printf(" %s%*c",jadwal.week[i].day[j].element,space,'|');
            //print rombongan
            for (int k = 0; k <4; k++){
                int space_p = 6;
                int space_r = 5;
                if (isStringNull(jadwal.week[i].day[j].lab[k].group.praktikum)){

                }
                else {
                     space_p = 6 - strlen(jadwal.week[i].day[j].lab[k].group.praktikum);
                }
                if (isStringNull(jadwal.week[i].day[j].lab[k].group.rombongan)){

                }
                else {
                     space_p =  - strlen(jadwal.week[i].day[j].lab[k].group.rombongan);
                }
        
                if ((space_p + space_r) >=11){
                    printf(" %*c",space_r+space_p+1,'|');
                }
                else {
                    printf(" %s-%s%*c",jadwal.week[1].day[j].lab[k].group.praktikum,jadwal.week[i].day[j].lab[k].group.rombongan,space_r+space_p,'|');
                }
            }
            printf("\n");
        }
        printf("|----------------|------------|------------|------------|------------|");
    }
}

void printStatus(Schedule jadwal){
    //mencetak header
    printf("|----------------|------------|------------|------------|------------|");
    //|Ruang Praktikum | LAB1 | LAB2 | LAB3 | LSS |
    printf("\n|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |");
    //mencetak header
    printf("\n|----------------|------------|------------|------------|------------|");
    //|Minggu | Hari |------------|------------|------------|-----------|
    //                            |------------|
    printf("\n|Minggu |  Hari  |------------|------------|------------|------------|\n");
    printf("|----------------|------------|------------|------------|------------|");
    for (int i = 0; i< 12; i++){
        printf("\n");
        //separator
        for (int j = 0; j < 5; j++){
            //print minggu
            printf("|%4d%4c",jadwal.week[i].element,'|');
            //print hari
            int space = 8 - strlen(jadwal.week[i].day[j].element);
            printf(" %s%*c",jadwal.week[i].day[j].element,space,'|');
            //print asisten di lab
            for (int k = 0; k <4; k++){
            /*  
                int space_p = 6;
                int space_r = 5;
                if (isStringNull(jadwal.week[i].day[j].lab[k].asprak[0].code)){

                }
                else {
                     space_p = 6 - strlen(jadwal.week[i].day[j].lab[k].group.praktikum);
                }
                if (isStringNull(jadwal.week[i].day[j].lab[k].group.rombongan)){

                }
                else {
                     space_p =  - strlen(jadwal.week[i].day[j].lab[k].group.rombongan);
                }
        
                if ((space_p + space_r) >=11){
                    printf(" %*c",space_r+space_p+1,'|');
                }
                else {
                    printf("%5s-%s%*c",jadwal.week[1].day[j].lab[k].group.praktikum,jadwal.week[i].day[j].lab[k].group.rombongan,space_r+space_p,'|');
                }
            */
                if (jadwal.week[i].day[j].lab[k].asprak[0].code == '\0'){
                    //cetak separator saja
                    printf("%13c", '|');
                }
                else{
                    printf("%5c,%c%6c",jadwal.week[i].day[j].lab[k].asprak[0].code,jadwal.week[i].day[j].lab[k].asprak[1].code,'|');

                }
            }
            printf("\n");
        }
        printf("|----------------|------------|------------|------------|------------|");
    }
}

bool isStringNull(const char * string){
    if (string == NULL){
        return true;
    }
    else
    {
        return false;
    }
    
}

void FprintStatus(Schedule jadwal, FILE * file){
    //mencetak header
    fprintf(file,"|----------------|------------|------------|------------|------------|");
    //|Ruang Praktikum | LAB1 | LAB2 | LAB3 | LSS |
    fprintf(file,"\n|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |");
    //mencetak header
    fprintf(file,"\n|----------------|------------|------------|------------|------------|");
    //|Minggu | Hari |------------|------------|------------|-----------|
    fprintf(file,"\n|Minggu |  Hari  |------------|------------|------------|------------|");
    fprintf(file,"\n|----------------|------------|------------|------------|------------|");
    for (int i = 0; i< 12; i++){
        fprintf(file,"\n");
        //separator
        for (int j = 0; j < 5; j++){
            //print minggu
            fprintf(file,"|%4d%4c",jadwal.week[i].element,'|');
            //print hari
            int space = 8 - strlen(jadwal.week[i].day[j].element);
            fprintf(file," %s%*c",jadwal.week[i].day[j].element,space,'|');
            //print rombongan
            for (int k = 0; k <4; k++){
                if (jadwal.week[i].day[j].lab[k].asprak[0].code == '\0'){
                    //cetak separator saja
                    fprintf(file,"%13c", '|');
                }
                else{
                    fprintf(file,"%5c,%c%6c",jadwal.week[i].day[j].lab[k].asprak[0].code,jadwal.week[i].day[j].lab[k].asprak[1].code,'|');
                }
            }
            fprintf(file,"\n");
        }
        fprintf(file,"|----------------|------------|------------|------------|------------|");
    }
}

void FprintSchedule(Schedule jadwal, FILE *file){
    //mencetak header
    fprintf(file,"|----------------|------------|------------|------------|------------|");
    //|Ruang Praktikum | LAB1 | LAB2 | LAB3 | LSS |
    fprintf(file,"\n|Ruang Praktikum |    LAB1    |    LAB2    |    LAB3    |    LSS     |");
    //mencetak header
    fprintf(file,"\n|----------------|------------|------------|------------|------------|");
    //|Minggu | Hari |------------|------------|------------|-----------|
    fprintf(file,"\n|Minggu |  Hari  |------------|------------|------------|------------|");
    fprintf(file,"\n|----------------|------------|------------|------------|------------|");
    for (int i = 0; i< 12; i++){
        fprintf(file,"\n");
        //separator
        for (int j = 0; j < 5; j++){
            //print minggu
            fprintf(file,"|%4d%4c",jadwal.week[i].element,'|');
            //print hari
            int space = 8 - strlen(jadwal.week[i].day[j].element);
            fprintf(file," %s%*c",jadwal.week[i].day[j].element,space,'|');
            //print rombongan
            for (int k = 0; k <4; k++){
                int space_p = 6;
                int space_r = 5;
                //cek apa isinya kosong
                if (isStringNull(jadwal.week[i].day[j].lab[k].group.praktikum)){
                    //do nothing
                }
                else {
                     space_p = 6 - strlen(jadwal.week[i].day[j].lab[k].group.praktikum);
                }
                if (isStringNull(jadwal.week[i].day[j].lab[k].group.rombongan)){
                    //do nothing
                }
                else {
                     space_p =  - strlen(jadwal.week[i].day[j].lab[k].group.rombongan);
                }
        
                if ((space_p + space_r) >=11){
                    fprintf(file," %*c",space_r+space_p+1,'|');
                }
                else {
                    fprintf(file," %s-%s%*c",jadwal.week[1].day[j].lab[k].group.praktikum,jadwal.week[i].day[j].lab[k].group.rombongan,space_r+space_p,'|');
                }
            }
            fprintf(file,"\n");
        }
        fprintf(file,"|----------------|------------|------------|------------|------------|");
    }
}

void shift(char buff[],int *cursor_str, int *cursor_end, char sep_1, char sep_2, char sep_3){
    *cursor_str = *cursor_end;
    while ((buff[*cursor_str] == sep_1 )||(buff[*cursor_str] == sep_2 ) ){
        (*cursor_str) ++;
    }
    *cursor_end = *cursor_str;
    while(buff[*cursor_end] != sep_3){
         (*cursor_end) ++;
    }
}

void assignWeek(Schedule ** jadwal,int i_minggu, int cursor_str, int cursor_end, char buff[]){
   char *temp = copyStr(cursor_str, cursor_end, buff);
   (*jadwal)->week[i_minggu].element = atoi(temp);
}

void assignDay(Schedule ** jadwal,int i_minggu,int i_hari, int cursor_str, int cursor_end, char buff[]){
    (*jadwal)->week[i_minggu].day[i_hari].element = malloc (strlen(copyStr(cursor_str,cursor_end,buff)));
    (*jadwal)->week[i_minggu].day[i_hari].element = copyStr(cursor_str, cursor_end, buff);
}

void assignPraktikum(Schedule ** jadwal,int i_minggu,int i_hari,int z, int cursor_str, int cursor_end, char buff[]){
    (*jadwal)->week[i_minggu].day[i_hari].lab[z].group.praktikum = malloc (strlen(copyStr(cursor_str,cursor_end,buff)));
    (*jadwal)->week[i_minggu].day[i_hari].lab[z].group.praktikum = copyStr(cursor_str,cursor_end,buff);
}
void assignRombongan(Schedule ** jadwal,int i_minggu,int i_hari,int z, int cursor_str, int cursor_end, char buff[]){
    (*jadwal)->week[i_minggu].day[i_hari].lab[z].group.rombongan = malloc (strlen(copyStr(cursor_str,cursor_end,buff))-1);
    (*jadwal)->week[i_minggu].day[i_hari].lab[z].group.rombongan = copyStr(cursor_str,cursor_end,buff);
}

void assignDataAsprak (dataAsprak *Asprak){
    char const * nama;
    char const *praktikum;
    char const * berhalangan;
    int index;
// isi nama Amir
    index = 0;
    nama = "Amir";
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'A';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Rabu";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
        
    }
// isi nama Budi
    nama = "Budi";
    index = 1;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'B';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Senin";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }
// isi nama Cici
    nama = "Cici";
    index = 2;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'C';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Selasa";
        }
        else if (i == 1 ){
            berhalangan = "Rabu";
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
        
    }
// isi nama Doni
    nama = "Doni";
    index = 3;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'D';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Senin";
        }
        else if (i == 1 ){
            berhalangan = "Rabu";
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }
// isi nama Endang
    nama = "Endang";
    index = 4;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'E';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = "EL2208";
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = NULL;
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Fadel
    nama = "Fadel";
    index = 5;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'F';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Selasa";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }    

// isi nama Gilang
    nama = "Gilang";
    index = 6;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'G';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = "EB2200";
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Kamis";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Hero
    nama = "Hero";
    index = 7;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'H';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Kamis";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Intan
    nama = "Intan";
    index = 8;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'I';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2205";
        }
        else if (i == 1 ){
            praktikum = "EL2208";
        }
        else {
            praktikum = "EB2200";
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Rabu";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Joko
    nama = "Joko";
    index = 9;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'J';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Jumat";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Kiki
    nama = "Kiki";
    index = 10;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'K';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Jumat";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Luis
    nama = "Luis";
    index = 11;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'L';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = NULL;
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

// isi nama Mini
    nama = "Mini";
    index = 12;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'M';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = NULL;
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Rabu";
        }
        else if (i == 1 ){
            berhalangan = "Kamis";
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }   
    
// isi nama Nina
    nama = "Nina";
    index = 13;
    Asprak->asprak[index].nama = malloc(strlen(nama)+1);
    strcpy(Asprak->asprak[index].nama,nama);
    //isi kode
    Asprak->asprak[index].code = 'N';
    //isi praktikum
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            praktikum = "EL2208";
        }
        else if (i == 1 ){
            praktikum = "EB2200";
        }
        else {
            praktikum = NULL;
        }

        if(praktikum == NULL){
            Asprak->asprak[index].praktikum[i] = NULL;
        }
        else{
            Asprak->asprak[index].praktikum[i] = malloc(strlen(praktikum)+1);
            strcpy(Asprak->asprak[index].praktikum[i],praktikum);
        }
        
    }

    // isi berhalangan
    for (int i = 0; i<3 ; i++){
        if (i == 0) {
            berhalangan = "Selasa";
        }
        else if (i == 1 ){
            berhalangan = NULL;
        }
        else {
            berhalangan = NULL;
        }

        if(berhalangan == NULL){
            Asprak->asprak[index].berhalangan[i] = NULL;
        }
        else{
            Asprak->asprak[index].berhalangan[i] = malloc(strlen(berhalangan)+1);
            strcpy(Asprak->asprak[index].berhalangan[i],berhalangan);
        }
    }

}

void printDataAsprak ( dataAsprak Asprak){
    for ( int index = 0; index <14; index++){
        printf("%s\n", Asprak.asprak[index].nama);
        printf("%c\n", Asprak.asprak[index].code);
        for (int i = 0; i < 3 ; i++){
            if (Asprak.asprak[index].praktikum[i] != NULL){
               printf("%s ", Asprak.asprak[index].praktikum[i]);
           }
       } 
       printf("\n");
        for (int i = 0; i < 3 ; i++){
            if (Asprak.asprak[index].berhalangan[i] != NULL){
               printf("%s ", Asprak.asprak[index].berhalangan[i]);
           }
       }
       printf("\n\n");
   }

}