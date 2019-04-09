#include "Load.h"
#include "Load.c"
#include <stdlib.h>
#include <stdbool.h>
//#include "Load.c"


void assign_asisten(Schedule *jadwal)
{
    //variabels
    char pilih_asisten[2]; int minggu; int i,j,k; Schedule jadwal;
    char str1[] = "Q";char str2[] = "q"; char strtemp;
    char hari[10]; char ruang[10];
    int nomer_hari, nomer_lab;
    dataAsprak dataAsisten;
    Schedule jadwal;

    printf("[Mode Assign Asisten]\n");
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    printf("Pilih Asisten (A-N): ");
    scanf("%s", &pilih_asisten);
    while(strcmp(pilih_asisten, "Q") && strcmp(pilih_asisten, "q"))
    {
        while((pilih_asisten[0]>=65)&&(pilih_asisten[0]<=78))
        {
            printf("Minggu: ");
            scanf("%d", &minggu);
            while ((minggu <3) || (minggu >14))
            {
                printf("Minggu: ");
                scanf("%d", &minggu);
            }
            i=minggu;
            //untuk masukan hari
            printf("Hari: ");
            scanf("%s", &hari);
            if(strcmp(hari, "senin") ==0)
            {
                nomer_hari = 0;
            }
            else if(strcmp(hari, "selasa")==0)
            {
                nomer_hari = 1;
            }
           else if(strcmp(hari, "rabu")==0)
            {
                nomer_hari =2;
            }
            else if(strcmp(hari, "kamis")==0)
            {
                nomer_hari = 3;
            }
            else if(strcmp(hari, "jumat")==0)
            {
                nomer_hari =4;
            }
                
                while((nomer_hari!=0) && nomer_hari !=1 && nomer_hari !=2 && nomer_hari !=3 && nomer_hari !=4)
                { 
                    printf("masukkan salah, silahkan masukan lagi\n");
                    printf("Hari: ");
                    scanf("%s", &hari);
                        if(strcmp(hari, "senin") ==0)
                        {
                            nomer_hari = 0;
                        }
                        else if(strcmp(hari, "selasa")==0)
                        {
                            nomer_hari = 1;
                        }
                        else if(strcmp(hari, "rabu")==0)
                        {
                            nomer_hari =2;
                        }
                        else if(strcmp(hari, "kamis")==0)
                        {
                            nomer_hari = 3;
                        }
                        else if(strcmp(hari, "jumat")==0)
                        {
                            nomer_hari =4;
                        }
                }
            j=nomer_hari;

            //untuk memasukkan ruang
            printf("Ruang: ");
            scanf("%s", &ruang);
                     if(strcmp(ruang, "LAB1") ==0)
                    {
                        nomer_lab = 0;
                    }
                    else if(strcmp(ruang, "LAB2")==0)
                    {
                        nomer_lab = 1;
                    }
                    else if(strcmp(ruang, "LAB3")==0)
                    {
                        nomer_lab =2;
                    }
                    else if(strcmp(ruang, "LSS")==0)
                    {
                        nomer_lab = 3;
                    }
                    else
                        {
                        nomer_lab =4;   
                            while(nomer_lab !=1 && nomer_lab !=2 && nomer_lab !=3 && nomer_lab !=4)  //cek ke database lab1 == 1... lss==4
                            {
                                printf("Ruang: ");
                                scanf("%s", &ruang);
                                if(strcmp(ruang, "LAB1") ==0)
                                {
                                    nomer_lab = 0;
                                }
                                else if(strcmp(ruang, "LAB2")==0)
                                {
                                    nomer_lab = 1;
                                }
                                else if(strcmp(ruang, "LAB3")==0)
                                {
                                    nomer_lab =2;
                                }
                                else if(strcmp(ruang, "LSS")==0)
                                {
                                    nomer_lab = 3;
                                }
                            }
                        }
            k = nomer_lab;
            //cek ke struktur data yang jadwal praktikum bagian praktikum ada atau tidak
            if(jadwal.week[i].day[j].lab[k].group.praktikum ==NULL)
            {
                printf("Tidak ada praktikum hari itu\n");
            }
            else    //ada praktikum 
            {
                
                
                //Masukin data "pilih_asisten" ke data base. Lalu cek praktikum yg ada di jadwal.week[i].day[j].lab[k].group.praktikum sama ga dengan yang di database
                int index =0; bool cek = false;
                while((index<14) && (cek == false)) //mencari asisten dengan kode
                {
                    if(pilih_asisten[0] == dataAsisten.asprak[index].code)
                    {
                        cek = true;
                        break;
                    }
                    else
                    {
                        index++;    
                    }
                }
                //udah nyimpen index
                int index_praktikum=0; 
                if(cek == true)
                {
                    cek = false;
                    while((index_praktikum<3) && (cek == false))    //mengecek praktikum yang di pegang asisten
                    {
                        if(strcmp(jadwal.week[i].day[j].lab[k].group.praktikum, dataAsisten.asprak[index].praktikum[index_praktikum]) ==0)
                        {
                            cek = true;
                            break;
                        }  
                    }
                }
                
                //Masukin data "pilih_asisten" ke data base. Lalu cek berhalangan atau ga
                int index_berhalangan;
                if(cek == true)
                {
                     //set lagi cek jadi false
                    while ((index_berhalangan<3) && (cek==true))
                    {
                        if(strcmp(hari, dataAsisten.asprak[index].berhalangan[index_berhalangan])==0)   //cocokin hari berhalangan dengan hari masukan
                        {
                            cek = false;
                            break;
                        } 
                        else
                            {
                                cek = true;
                                index_berhalangan++;
                            }
                    }
                }
                else
                        {
                            printf("Asisten tidak terdaftar melakukan praktikum %s", jadwal.week[i].day[j].lab[k].group.praktikum);
                        }
                
                //cek juga udh dua asisten belom di satu ruangan
                int index_asprak;
                if(cek == true)
                {
                        if(IsAvailable(jadwal, minggu, nomer_hari, nomer_lab, pilih_asisten) ==2) //jika keluaran ISAvalaible = 2
                        {
                            printf("Lab pada hari itu penuh\n");
                            cek = false;
                        }
                        else
                        {
                            index_asprak = IsAvailable(jadwal, minggu, nomer_hari, nomer_lab, pilih_asisten);       //merekam indeks asprak ke 1 atau 2 yang avalaible
                        }
                }
                else
                {
                    printf("Pada hari itu asisten berhalangan\n");
                }
                 
                //cek juga si asisten ini udh di assign belom dalam minggu, hari, lab yang sama
                if(cek==true)
                {
                    if(IsDiaSendiri == 0)
                    {
                        printf("Asprak sudah bertugas di lab yang sama\n");
                    } 
                    else
                    {
                        //masukan asprak untuk bertugas pada pada tersebut
                        //assign
                        jadwal.week[i].day[j].lab[k].asprak[index_asprak].code = pilih_asisten;
                    } 
                } 

            }
        printf("Pilih Asisten (A-N): ");
        scanf("%s", &pilih_asisten);
        }
    }
}



int IsAvailable(Schedule jadwal, int minggu, int nomer_hari,int nomer_lab, char pilih_asisten[])  //mengecek udh 2 org atau belum dan bukan dirinya sendiri
{
    //vars
    int i=0; bool cek = false;

    while((i<2) && (cek == false))
    {
        if(jadwal.week[minggu].day[nomer_hari].lab[nomer_lab].asprak[i].code == NULL)
        {
            cek = true;
        }
        else
        {
            cek = false;
            i++;
        }
    }
    return i;
}

int IsDiaSendiri(Schedule jadwal, int minggu, int nomer_hari, int nomer_lab, char pilih_asisten[]) //mengecek dia udh di assign blm di hari yang sama dan lab yang sama
{
    int i=0; bool cek = true;
    while ((i<2) && cek == true)
    {
        if(jadwal.week[minggu].day[nomer_hari].lab[nomer_lab].asprak[i].code == pilih_asisten[0])
        {
            cek = false;
            return 0;
        }
        else
        {
            cek= true;
            i++;
        }
    }
    if(cek == true)
    {
        return 1;
    }
      
}
