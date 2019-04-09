#include <stdio.h>
#include "Load.h"
#include "Load.c"

void print_strip(int x);

void print_asisten(Schedule jadwal)
{
     int i; int j;  int k; int x; int p; //p pencacah lab
      char karakter;
     

    printf("|-------------------------------------------------------------------------------|\n");
    printf("|   Ruang Praktikum          | LAB1       | LAB2       | LAB3       | LSS       |\n");
    printf("|   Minggu   |     Hari      |------------|------------|------------|-----------|\n");
    printf("|------------|-------------- |------------|------------|------------|-----------|\n");

    for(i =0; i<12; i++)
    {
        jadwal.week[i].element =i+3;
        for(j=0; j<5; j++)
        {
            printf("|------%d-----|", jadwal.week[i].element);
            
            if(j==0)
            {
                jadwal.week[i].day[j].element = calloc(6, sizeof(char));
                jadwal.week[i].day[j].element = "senin";
            }
            else if(j==1)
            {
                jadwal.week[i].day[j].element = calloc(7, sizeof(char));
                jadwal.week[i].day[j].element = "selasa";
            }
            else if(j==2)
            {
                jadwal.week[i].day[j].element = calloc(5, sizeof(char));
                jadwal.week[i].day[j].element = "Rabu";
            }
            else if(j==3)
            {
                jadwal.week[i].day[j].element = calloc(6, sizeof(char));
                jadwal.week[i].day[j].element = "kamis";
            }
            else {
                jadwal.week[i].day[j].element = calloc(6, sizeof(char));
                jadwal.week[i].day[j].element = "jumat";
            }

            printf("-------%s", jadwal.week[i].day[j].element);
            int q;
            q=strlen(jadwal.week[i].day[j].element);
            print_strip(q);
            int k=1;
            //jadwal.week[i].day[i].lab[k].asprak = calloc(2, sizeof(Asprak));        // untuk buat memori asprak yang tentatif(sesuai input asprak berapa)
            //jadwal.week[i].day[i].lab[k].asprak->code = calloc(2, sizeof(char));    // udh ada pas assign di print_asisten
            

            
            for(k=0; k<4; k++)                                       //untuk pencacah ada 4 lab
                {
                    for(p=0; p<2; p++)                              // untuk pencacah berapa banyak asisten di satu lab
                    {
                        printf("       ");  int karakter=0;         //karakter adalah karakter yang di print di kolom lab(kode asisten)
                        if(jadwal.week[i].day[j].lab[k].group.praktikum=NULL)
                        {
                            if(karakter>=1)
                            {
                                printf(",");
                            }
                            printf("%c", jadwal.week[i].day[j].lab[k].asprak[p].code);
                            karakter =karakter+1;
                        }
                    }  
                    print_strip(karakter);                                   
                }
            
            printf("\n");

        }
    }
   
}

void print_strip(int x)                                              //x adalah panjang string
{
    int i;                                                            

    for(i=1; i<=(7-x); i++)
    {
        printf(" ");
    }
    printf(" ");
}

