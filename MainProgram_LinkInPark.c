#include "func.h"
#include <stdio.h>

//Main program
int main(){
	Login log;
	log.status = 0;
	
	// Animasi intro saat pembukaan program
	printf("\t\t\t");
	animIntro();
    printf("\n");
    Sleep(100);
    printf("\t\t\t|  Selamat Datang di Proyek Algoritma dan Pemrograman ^_^ |\n");
    Sleep(100);
    printf("\t\t\t|                      Created By :                       |\n");
    Sleep(100);
    printf("\t\t\t|      1. Bima Adinata Namara        (2006574566)         |\n");
    Sleep(100);  
    printf("\t\t\t|      2. Muhammad Brian Naiman Hadi (2006574534)         |\n");
    Sleep(100);
    printf("\t\t\t|      3. Tio Larizky                (2006574433)         |\n");
    Sleep(100);   
    printf("\t\t\t");
	animIntro();
    Sleep(100);
    printf("\n\n");
	
	// Agar dapat masuk ke program selanjutkan, maka diperlukan username dan password
	while(log.status != 3){
    	printf("Masukkan Username : ");
      	gets(*log.username);
      	printf("Masukkan Password : ");
      	
		while(1){
			*log.pass = getch(); // digunakan untuk menyimpan password (karakter satu persatu) 
			
			if (*log.pass == 13){	//ketika user menekan tombol enter maka akan langsung selesai looping
				log.password[log.charPosition] = '\0';
				break;
			}
			
			else if (*log.pass == 8){	//ketika user menekan tombol backspace maka akan terhapus satu huruf
				if (log.charPosition > 0){
					log.charPosition--;
					log.password[log.charPosition] = '\0';
					printf("\b \b"); //untuk menghilangkan karakter bintang (*)
				}
			}
			
			else if (*log.pass == 127){	//ketika user menekan tombol ctrl + Backspace maka akan terhapus semua
				if (log.charPosition > 0){
					for(log.status=0;log.status < log.charPosition;log.status++){
						printf("\b \b");
					}
					log.charPosition-=log.charPosition;
					log.password[log.charPosition] = '\0';
				}
			}
			
			else if(*log.pass > 0 && *log.pass < 33){	//ketika user menekan tombol (ASCII (1-32)) yang tidak terdapat keyboard akan skip
				continue;
			} 
			
			else {
				log.password[log.charPosition] = *log.pass;
				log.charPosition++;
				printf("*");
			}
		}
		
		log.password[log.charPosition]='\0';	//supaya dia null kembali atau menghindari adanya error
      	validasiPassword(&log);
		log.charPosition-=log.charPosition;	//agar password dapat tercetak jadi awal lagi
	}
   	system("cls");
    
	menuAnimation(2, 100, 100, 100, 100, 2);
	
	main_menu();
	
	return 0;
}
