#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#ifndef func
#define func

// Deklarasi Struct Membuka Login Logout
typedef struct user_login {
	char username[10][10];
	char password[12];
	char pass[12];
	int charPosition;
	int status;
	int anim;
}Login;

// Deklarasi Menduplikat Data Kendaraan
struct DuplikasiKendaraan {
	int id;
	char plat[50];
	char karcis[50];
};

// Asumsi penggunaan variabel kendaraan mobil dan motor
typedef struct mtr_mbl {
	int count;
	int temp;
	int loop;
	char plat[50][50];
	char duplicatePlat[50][50];
	char karcis[50][50];
}kendaraan;

// Implementasi data dari variabal yang akan dipakai
typedef struct data {
	int sentinel;
	int loop; 
	int x; 
	int y; 
	int jenis;
	int nominal;
	int bayar;
	float parkir;
	char tanya;
}Data;

// Node untuk Linked List
struct linkedList_Node { 
	struct DuplikasiKendaraan kendaraan;
	struct linkedList_Node *lnjtPtr;
};
typedef struct linkedList_Node linkedList_Node; 
typedef linkedList_Node *ListNodePtr;

// Deklarasi struct pada binary tree
struct BinaryTree {
    struct DuplikasiKendaraan kendaraan;
    struct BinaryTree *right_child, *left_child; 
};

//Function untuk membuat BinaryTree binary tree
struct BinaryTree* new_node(struct DuplikasiKendaraan kendaraan) {
    struct BinaryTree *makeNew;
    makeNew = malloc(sizeof(struct BinaryTree));
    makeNew->kendaraan = kendaraan;
    makeNew->left_child = NULL;
    makeNew->right_child = NULL;
    return makeNew;
}

//Menyisipkan data pada binary tree
struct BinaryTree* insertTree(struct BinaryTree *root, struct DuplikasiKendaraan kendaraan) {
    if(root==NULL) {
        return new_node(kendaraan);
	}
    else if(kendaraan.id>root->kendaraan.id) {
		root->right_child = insertTree(root->right_child, kendaraan);   	
	}
    else {
    	root->left_child = insertTree(root->left_child,kendaraan);
	}   
    return root;
}

//Function untuk elakukan searching pada binary tree
struct BinaryTree* search(struct BinaryTree *root, int x, char *jenis) {
	struct BinaryTree *temp;
	temp = root;
	
	while (temp != NULL) {
		if(temp->kendaraan.id==x){
	    	printf("\nRincian Kendaraan yang Parkir:\n");
	       	printf("------------------------------\n");
			printf("Jenis Kendaraan = %s\n", jenis);
			printf("Id Kendaraan = %d\nNomor Plat = %s\nNomor Karcis = %s\n------------------------------", temp->kendaraan.id, temp->kendaraan.plat, temp->kendaraan.karcis);
			return (temp);
		}
		else{
			if(temp->kendaraan.id>x){
				temp = temp->left_child;
			}
			else {
				temp = temp->right_child;
			}
		}
	}
	printf("Id %s Tidak Ditemukan!", jenis);
}

// Minimalisasi pada binary tree agar dapat diketahui nilai minimumnya
struct BinaryTree* find_minimum(struct BinaryTree *root) {
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL)
        return find_minimum(root->left_child);
    return root;
}

// Function untuk melakukan deleteTreeNode pada node binary tree
struct BinaryTree* deleteTreeNode(struct BinaryTree *root, int id)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (id > root->kendaraan.id)
        root->right_child = deleteTreeNode(root->right_child, id);
    else if(id<root->kendaraan.id)
        root->left_child = deleteTreeNode(root->left_child, id);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct BinaryTree *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            	free(root);
            	return temp;
        }
        //Two Children
        else
        {
            struct BinaryTree *temp = find_minimum(root->right_child);
            root->kendaraan = temp->kendaraan;
            root->right_child = deleteTreeNode(root->right_child, temp->kendaraan.id);
        }
    }
    return root;
}

//Implementasi Fungsi Prototype
void menuAnimation(int a, int b, int c, int d, int e, int f);
void animIntro();
void main_menu();
void pilihan_menu();
void skipStruk();
void cetakStruk (kendaraan motor_mobil, Data input, int loop, char* kategori, int tagihan);
void guideUser();
void kendaraanKosong();
void validasiPassword(struct user_login *cek);
void pilihanPlat_Kendaraan(struct mtr_mbl *cekPlat, char kendaraan[]);
void salahInput_karcis();
void insert( ListNodePtr *sPtr, struct DuplikasiKendaraan kendaraan);
void printList( ListNodePtr skrgPtr, struct mtr_mbl *kendaraan, char *jenis, int kapasitas );
int hapus1( ListNodePtr *sPtr, struct DuplikasiKendaraan kendaraan, int id);
void inorder(struct BinaryTree *root);
void preOrder(struct BinaryTree *root);
void postOrder(struct BinaryTree *root);
int adlhKosong( ListNodePtr sPtr );
int stringAnimation_exitProgram();
int validasiPlat(kendaraan motor_mobil, char *jenis, int kapasitas, int* temp, int* loop);
int mtr (int a);
int mbl (int b);

// Lakukan null ketika data kosong
int adlhKosong( ListNodePtr sPtr ) { 
	return sPtr == NULL;
}

// Mengurutkan binary tree
void inorder(struct BinaryTree *root) {
    if(root!=NULL){
        inorder(root->left_child);
        printf(" %d ", root->kendaraan.id);
        inorder(root->right_child);
    } 
	else {
		printf('\0');
	}
}

// Menampilkan id binary tree dengan pre order
void preOrder(struct BinaryTree *root) { 
	if ( root != NULL ) { 
		printf( " %d ", root->kendaraan.id); 
		preOrder(root->left_child); 
		preOrder(root->right_child); 
	} else {
		printf('\0');
	}
}

// Menampilkan id binary tree dengan post order
void postOrder(struct BinaryTree *root) {
	if ( root != NULL ) { 
		postOrder(root->left_child); 
		postOrder(root->right_child); 
		printf( " %d ", root->kendaraan.id); 
	} else {
		printf('\0');
	}
}

// Memasukkan suatu node baru ke menggunakan struct
void insert( ListNodePtr *sPtr, struct DuplikasiKendaraan kendaraan) { 
	ListNodePtr baruPtr;
	ListNodePtr sblmPtr;
	ListNodePtr skrgPtr;
	baruPtr = malloc( sizeof( linkedList_Node ) ); 
	
	if ( baruPtr != NULL ) {
		baruPtr->kendaraan = kendaraan;
		baruPtr->lnjtPtr = NULL; 
		
		sblmPtr = NULL; 
		skrgPtr = *sPtr; 
		
		while ( skrgPtr != NULL ) { 
			sblmPtr = skrgPtr;
			skrgPtr = skrgPtr->lnjtPtr;
		}
		if ( sblmPtr == NULL ) { 
			baruPtr->lnjtPtr = *sPtr; 
			*sPtr = baruPtr; 
		}
		else {
			sblmPtr->lnjtPtr = baruPtr; 
			baruPtr->lnjtPtr = skrgPtr; 
		}
	} else { 
		printf( "Tidak Ada Memori Yang Tersedia\n"); 
	}
}

// Melakukan penghapusan node yang telah dibuat menggunakan struct
int hapus1( ListNodePtr *sPtr, struct DuplikasiKendaraan kendaraan, int id) { 
	ListNodePtr sblmPtr;
	ListNodePtr skrgPtr;
	ListNodePtr tempPtr;
	
	if ( id == ( *sPtr )->kendaraan.id ) { 
		tempPtr = *sPtr; 
		*sPtr = ( *sPtr )->lnjtPtr;
		free( tempPtr );
		return id; 
	}
	
	else { 
		sblmPtr = *sPtr; 
		skrgPtr = ( *sPtr )->lnjtPtr; 
		
		while ( skrgPtr != NULL && skrgPtr->kendaraan.id != id ) { 
			sblmPtr = skrgPtr;
			skrgPtr = skrgPtr->lnjtPtr;
		}
		
		if ( skrgPtr != NULL ) { 
			tempPtr = skrgPtr; 
			sblmPtr->lnjtPtr = skrgPtr->lnjtPtr; 
			free( tempPtr ); 
			return id; 
		}
	}
	return '\0'; 
}

// Menampilkan data data kita setelah adanya motor maupun mobil yang masuk
void printList( ListNodePtr skrgPtr, struct mtr_mbl *kendaraan, char *jenis, int kapasitas ) {
	char change [kapasitas];
	if ( skrgPtr == NULL ) {
		printf("\n\nKapasitas %s yang Tersisa: %d", jenis, kapasitas - kendaraan->count);
		printf("\nInformasi %s Terkini:\n", jenis);
		printf("+------------------------------------------------------------------------+\n");
		printf("|      Id       |          Plat %s         |          Karcis          |\n", jenis);
		printf("+------------------------------------------------------------------------+\n");
		printf("+             Kendaraan %s Sedang Kosong Untuk Saat Ini               +\n", jenis);
		printf("+------------------------------------------------------------------------+\n");
	}
	else {
		printf("\n\nKapasitas %s yang Tersisa: %d", jenis, kapasitas - kendaraan->count);
		printf("\nInformasi %s Terkini:\n", jenis);
		printf("+------------------------------------------------------------------------+\n");
		printf("|      Id       |          Plat %s         |          Karcis          |\n", jenis);
		printf("+------------------------------------------------------------------------+\n");
		while ( skrgPtr != NULL ) {
			snprintf(change, 10, "%d", skrgPtr->kendaraan.id);
			printf( "|%8.17s%-7.15s|%10.17s%-19.15s|%7.17s%-19.15s|\n", change, "", "", skrgPtr->kendaraan.plat, "",  skrgPtr->kendaraan.karcis); 
			skrgPtr = skrgPtr->lnjtPtr; 
		}
		printf("+------------------------------------------------------------------------+\n");
	}
}

// Fungsi Cek Ke-valid-an Username dan Password
void validasiPassword(struct user_login *cek){
	if(strcmp(*cek->username, "operator")==0 && strcmp (cek->password, "operator")==0){
      	cek->status = 3;
      	Sleep(5);
      	printf("\n\n\n\n\t\t\t\t\tAKSES DITERIMA\n\n");
    	Sleep(500);
        printf("\t\t\t\t\tLoading");
         	
        for (cek->anim = 0; cek->anim < 5; cek->anim++){
         	Sleep(850);
			printf(".");
		}
    } 
		
	else{
        printf("\n---- Username dan Password Salah ----\n\n");
        cek->status++;
		if(cek->status == 3){
			system ("cls");
			printf("\n\t\t\t##############################################################");
			printf("\n\t\t\t#   Anda Memasukkan User dan Password Lebih dari Tiga Kali!  #");
			printf("\n\t\t\t#   Akses ditolak                                            #");
			printf("\n\t\t\t##############################################################\n");
            exit(0);
        }
    }	
}

// Fungsi untuk mendapatkan karcis
void pilihanPlat_Kendaraan(struct mtr_mbl *cekPlat, char kendaraan[]){
	strcpy(cekPlat->duplicatePlat[cekPlat->count], cekPlat->plat[cekPlat->count]);
	srand(time(NULL));
	snprintf(cekPlat->karcis[cekPlat->count], 20, "#karcis%d", rand()  % 99999 + 10000); //Tiket Random 10000...99999 (5 digit)
	printf("Karcis Anda\t: %s", cekPlat->karcis[cekPlat->count]);
	printf("\n------------------------------\n");
	printf("Total %s\t: %d\n\n", kendaraan, cekPlat->count - cekPlat->temp);	
}

//Animasi Program dengan Huruf "="
void animIntro(){
	Data i;
	for (i.loop = 0; i.loop < 59; i.loop++){
		printf("=");
		Sleep(2); 
	}
}

//Fungsi Judul Program
void menuAnimation(int a, int b, int c, int d, int e, int f){
	Data j;
	
	printf("\t\t\t");
	for (j.loop = 0; j.loop < 70; j.loop++){
		printf("=");
		Sleep(a);
	}
	
	printf("\n");
    Sleep(b);
    printf("\t\t\t|                                                                    |\n");
    Sleep(c);
    printf("\t\t\t|                    -  PROGRAM LINK IN PARK  -                      |\n");
    Sleep(d);
    printf("\t\t\t|                                                                    |\n");
    Sleep(e);
    
    printf("\t\t\t");
    for (j.loop = 0; j.loop < 70; j.loop++){
		printf("=");
		Sleep(f);
	}
	
    printf("\n");
}

//Fungsi Pemrosesan Menu yang Dipilih User
void main_menu(){
	struct DuplikasiKendaraan motor_linked;
	struct DuplikasiKendaraan mobil_linked;
	
	struct BinaryTree *rootMotor = NULL;
	struct BinaryTree *rootMobil = NULL;

	rootMotor = new_node(motor_linked);
	rootMobil = new_node(mobil_linked);
	
	// Melakukan deleteTreeNode node binary tree agar semua node pada mobil kosong
	deleteTreeNode(rootMobil, 6029427);
	
	int id_motor[100] = {0};
	int id_mobil[100] = {0};
	
	Data input;
	kendaraan motor;
	kendaraan mobil;
	
	motor_linked.id = 0;
	mobil_linked.id = 0;
	
	ListNodePtr startPtrMotor = NULL;
	ListNodePtr startPtrMobil = NULL;
	
	char* input_karcis = calloc(4096,sizeof(char));
	
	int *pilih, pilihan;
	pilih = &pilihan;
	motor.temp = 0;
	mobil.temp = 0;
	motor.count = 0;
	mobil.count = 0;
	motor.loop = 0;
	mobil.loop = 0;
	
	pilihan_menu();
    
	do{
    	printf(">> ");
    	scanf("%d", pilih);
    	
    	if (*pilih < 1 || *pilih > 7){
    		printf("\nMasukkan Angka yang Sesuai!\n");
		}
		
		switch (*pilih){

			case 1:
		        if(motor.count < 50 + motor.temp){
		        	motor.count++;
		            printf("Plat Motor\t: ");
		            scanf(" %255[^\n]s", &motor.plat[motor.count]);
					fflush(stdin);
					
					if(validasiPlat(motor, "Motor", 50, &motor.temp, &motor.count)){		
						pilihanPlat_Kendaraan(&motor, "Motor");
						motor_linked.id = rand()  % 999 + 100;
						id_motor[motor.count] = motor_linked.id;
						strcpy(motor_linked.plat, motor.plat[motor.count]);
						strcpy(motor_linked.karcis, motor.karcis[motor.count]);
						insert( &startPtrMotor, motor_linked );
						insertTree(rootMotor, motor_linked);
					}
					
		        }
		        else{
		            printf("Tempat Parkir Motor Penuh\n\n");
		        }
		        break;
		        
			case 2:
		        if(mobil.count < 10 + mobil.temp){
		        	mobil.count++;
		            printf("Plat Mobil\t: ");
		            scanf(" %255[^\n]s", &mobil.plat[mobil.count]);
		            fflush(stdin);
		            
			        if(validasiPlat(mobil, "Mobil", 10, &mobil.temp, &mobil.count)){		
						pilihanPlat_Kendaraan(&mobil, "Mobil");
						mobil_linked.id = rand()  % 999 + 100;
						id_mobil[mobil.count] = mobil_linked.id;
						strcpy(mobil_linked.plat, mobil.plat[mobil.count]);
						strcpy(mobil_linked.karcis, mobil.karcis[mobil.count]);
						insert( &startPtrMobil, mobil_linked );
						insertTree(rootMobil, mobil_linked);
					}
					
		        }
		        else{
		            printf("Tempat Parkir Mobil Penuh\n\n");
		        }
		        break;
		        
		    case 3:
		    	system("cls");
		    	printList( startPtrMotor, &motor, "Motor", 50+motor.temp);
		    	printList( startPtrMobil, &mobil, "Mobil", 10+mobil.temp);
		    	printf("\n\n");
		    	system("pause");
		    	system("cls");
				menuAnimation(0, 0, 0, 0, 0, 0);
				pilihan_menu();
		    	break;
		    
			//Payment Menu (Implementasi Searching)
			case 4:
				if(motor.count != motor.temp || mobil.count != mobil.temp){
					system("cls");
		            printf ("\n		    ============================================================================   ");
		            printf ("\n					    Jenis Kendaraan dan Tarif Parkir                                   ");
		            printf ("\n			    1. Motor : Rp. 2000 untuk 1 Jam Pertama, Rp. 1000/jam berikutnya.          ");
		            printf ("\n			    2. Mobil : Rp. 5000 untuk 1 Jam Pertama, Rp. 4000/jam berikutnya.          ");
		            printf ("\n			    0. Kembali ke Menu Awal                                                    ");
		            printf ("\n		    ============================================================================   ");
		            printf ("\n		               Masukkan Kategori Kendaraan (Berdasarkan Nomor Pilihan)         \n\n");
		            
		            do{
		            	printf("Pilih : ");
		            	scanf("%d", &input.jenis);
		            	if(input.jenis<0 || input.jenis>2){
		            		printf("Masukkan Input yang Sesuai\n\n");
						}
					}while(input.jenis < 0 || input.jenis > 2);
					
		            switch (input.jenis){
		            	
		            	case 0:
		            		system("cls");
		            		menuAnimation(0, 0, 0, 0, 0, 0);
							pilihan_menu();
		            		break;
		            		
		            	case 1:
		            		if(motor.count==motor.temp){
					            kendaraanKosong();
				                system("pause");
								system("cls");
		            			menuAnimation(0, 0, 0, 0, 0, 0);
								pilihan_menu();
							}
							else {
								input.sentinel = 0;
								printf("\nMasukkan Karcis Anda (misal : #karcis24122) : ");
								
								do{
									input.sentinel++;
						        	scanf(" %255[^\n]s", input_karcis);
									for (input.loop = 1; input.loop <= 50 + motor.temp; input.loop++){
								       	if (strcmp(input_karcis, motor.karcis[input.loop])==0){
								       		printf ("Id Kendaraan\t\t\t\t    : %d\n", id_motor[input.loop]);
											printf ("Plat Motor\t\t\t\t    : %s\n", motor.plat[input.loop]);
											printf ("Lama Parkir (per jam)?\t\t\t    : ");
                        					scanf  ("%f", &input.parkir);
											printf ("Total Tagihan\t\t\t\t    : %d", mtr(input.parkir));
                        					printf ("\nTotal Pembayaran\t\t\t    : " );
                        					scanf  ("%d", &input.nominal);
											input.y = input.nominal - mtr(input.parkir);
											printf("\n");
											
				                            while (input.y < 0){
				                                printf ("Total Uang yang Dimasukkan\t\t    : %d\n", input.nominal);
				                                printf ("\n----------------- Maaf, Uang Tidak Mencukupi --------------------\n\n");
				                                printf ("Tambahkan Uang untuk Mencukupi Pembayaran   : " );
				                                scanf  ("%d", &input.x);
				                                printf("\n");
				                                input.nominal += input.x;
				                                input.y = input.nominal - mtr(input.parkir);
				                            }
				                            
				                            printf ("\nKembalian\t\t\t\t    : %d", input.y);
				                            printf("\n=================================================================");				                            
											printf ("\nCetak Struk? (Y/N) : ");
											
											do{
												scanf ("%s", &input.tanya);
												if (input.tanya=='Y' || input.tanya=='y'){
													system("cls");
													cetakStruk (motor, input, input.loop, "Motor", mtr(input.parkir));
												}
												else if(input.tanya == 'N' || input.tanya == 'n'){
													system("cls");
													skipStruk();
												}
												else {
													printf("\nHuruf Tidak valid, Coba Lagi!");
													printf ("\nCetak Struk? (Y/N)\n>> ");
												}
											}while(input.tanya != 'y' && input.tanya != 'Y' && input.tanya != 'n' && input.tanya != 'N');
											
											strncpy(motor.plat[input.loop],"   (-)",20);
											strncpy(motor.duplicatePlat[input.loop],"",20);
											strncpy(motor.karcis[input.loop],"    (-)",20);
											motor.temp++;
											input.sentinel = -1;
											hapus1( &startPtrMotor, motor_linked, id_motor[input.loop]);
											deleteTreeNode(rootMotor, id_motor[input.loop]);
											id_motor[input.loop] = '\0';
											break;
								      	}
										else {
											continue;
										}
									}
									if(input.loop == 51 + motor.temp && input.sentinel != 5){
								      	printf("\nKarcis Salah, Silakan Input Ulang Karcis (misal: #karcis24122)\n>> ");
									}
								}while(input.sentinel != 5 && input.sentinel != -1); 
								
								if(input.sentinel == 5){
									system("cls");
									salahInput_karcis();
									system("pause");
									system("cls");
			            			menuAnimation(0, 0, 0, 0, 0, 0);
									pilihan_menu();	
								} 
								else {
									system("pause");
									system("cls");
			            			menuAnimation(0, 0, 0, 0, 0, 0);
									pilihan_menu();
								}
							}
		            		break;
		            		
						case 2:
							
							if(mobil.count==mobil.temp){
					            kendaraanKosong();
				                system("pause");
								system("cls");
		            			menuAnimation(0, 0, 0, 0, 0, 0);
								pilihan_menu();
							}
							
							else {
								input.sentinel = 0;
								printf("\nMasukkan Karcis Anda (misal: #karcis24122) : ");
								do{
									input.sentinel++;
						        	scanf(" %255[^\n]s", input_karcis);
									for (input.loop = 1; input.loop <= 50 + motor.temp; input.loop++){
								       	
										if (strcmp(input_karcis, mobil.karcis[input.loop])==0){
											printf ("Id Kendaraan\t\t\t\t   : %d\n", id_mobil[input.loop]);
											printf ("Plat Mobil \t\t\t\t   : %s\n", mobil.plat[input.loop]);
											printf ("Lama Parkir (per jam)?\t\t\t   : ");
                        					scanf  ("%f", &input.parkir);
											printf ("Total Tagihan\t\t\t\t   : %d", mbl(input.parkir));
                        					printf ("\nTotal Pembayaran\t\t\t   : " );
                        					scanf  ("%d", &input.nominal);
											input.y = input.nominal - mbl(input.parkir);
											printf("\n");
				                            
											while (input.y < 0){
				                                printf ("Total Uang yang Dimasukkan\t\t   : %d\n", input.nominal);
				                                printf ("\n----------------- Maaf, Uang Tidak Mencukupi --------------------\n\n");
				                                printf ("Tambahkan Uang untuk Mencukupi Pembayaran  : " );
				                                scanf  ("%d", &input.x);
				                                printf("\n");
				                                input.nominal += input.x;
				                                input.y = input.nominal - mbl(input.parkir);
				                            }
				                            
											printf ("\nKembalian\t\t\t\t   : %d", input.y);
				                            printf("\n=================================================================");
				                            printf ("\nCetak Struk? (Y/N) : ");
				                            
											do{
				                            	scanf ("%s", &input.tanya);
					                            if (input.tanya=='Y' || input.tanya=='y'){
					                                system("cls");
					                                cetakStruk (mobil, input, input.loop, "Mobil", mbl(input.parkir));
	                                			}
	                               				else if(input.tanya == 'N' || input.tanya == 'n'){
					                                system("cls");
					                                skipStruk();
	                                			}
												else {
					                                printf("\nHuruf Tidak valid, Coba Lagi!");
					                                printf ("\nCetak Struk? (Y/N)\n>> ");
					                            }
											}while(input.tanya != 'y' && input.tanya != 'Y' && input.tanya != 'n' && input.tanya != 'N');
											
											strncpy(mobil.plat[input.loop],"   (-)",20);
											strncpy(mobil.duplicatePlat[input.loop],"",20);
											strncpy(mobil.karcis[input.loop],"    (-)",20);
											mobil.temp++;
											input.sentinel = -1;
											hapus1( &startPtrMobil, mobil_linked, id_mobil[input.loop]);
											id_mobil[input.loop] = '\0';
											deleteTreeNode(rootMobil, id_mobil[input.loop]);
											break;
								      	}
										else {
											continue;
										}
									}
									if(input.loop == 51 + motor.temp && input.sentinel != 5){
								      	printf("\nKarcis Salah, Silakan Input Ulang Karcis (Misal: #karcis24122)\n>> ");
									}
								}while(input.sentinel != 5 && input.sentinel != -1);
								
								if(input.sentinel == 5){
									system("cls");
									salahInput_karcis();
									system("pause");
									system("cls");
			            			menuAnimation(0, 0, 0, 0, 0, 0);
									pilihan_menu();	
								}
								else {
									system("pause");
									system("cls");
			            			menuAnimation(0, 0, 0, 0, 0, 0);
									pilihan_menu();	
								}
							}
		            		break;
		    			}
				}
				else {
					system("cls");
					kendaraanKosong();
					system("pause");
					system("cls");
	                menuAnimation(0, 0, 0, 0, 0, 0);
					pilihan_menu();
				}
				break;
				
			case 5:
				guideUser();
		    	menuAnimation(0, 0, 0, 0, 0, 0);
				pilihan_menu();
			    break;
			    
			case 6:
				system("cls");
				printf( "\n\nBerikut Daftar Implementasi Binary Tree:\n" ); 
			    printf("[1]  List Id Kendaraan Motor yang Masih Ada\n");
			    printf("[2]  List Id Kendaraan Mobil yang Masih Ada\n");
			    printf("[3]  Searching Plat dan Karcis Menggunakan Id Kendaraan\n");
			    printf("[4]  Back\n");
			    printf("Pilih Angka yang Ingin Anda Masukkan:\n");
			    
			    do{
			    	printf(">> ");
			    	scanf("%d", &input.x);
			    	if (input.x < 0 || input.x >4){
						printf("\nMasukkan Angka Yang Sesuai!\n");
					}
			    	else if (input.x == 1){
			    		printf("\nLIST ID KENDARAAN MOTOR YANG ADA DIDALAM: (ada %d motor)\n", motor.count - motor.temp);
			    		printf("--- InOrder Transversal ---\n");
			    		inorder(rootMotor);
			    		printf("\n\n");
			    		printf("--- PreOrder Transversal ---\n");
			    		preOrder(rootMotor);
			    		printf("\n\n");
			    		printf("--- PostOrder Transversal ---\n");
			    		postOrder(rootMotor);
						printf("\n\n");
					}
					
					else if (input.x == 2){
			    		printf("\nLIST ID KENDARAAN MOBIL YANG ADA DIDALAM: (ada %d mobil)\n", mobil.count - mobil.temp);
			    		printf("--- InOrder Transversal ---\n");
			    		inorder(rootMobil);
			    		printf("\n\n");
			    		printf("--- PreOrder Transversal ---\n");
			    		preOrder(rootMobil);
			    		printf("\n\n");
			    		printf("--- PostOrder Transversal ---\n");
			    		postOrder(rootMobil);
						printf("\n\n");
					}
					
					else if (input.x == 3){
			    		printf("\nApa yang ingin di searching?:\n1. Motor\n2. Mobil\n");
			    		do{
			    			printf(">> ");
			    			scanf("%d", &input.x);
			    			if (input.x < 0 || input.x >2){
								printf("\nMasukkan Angka Yang Sesuai!\n");
							}
			    			else if (input.x == 1){
			    				printf("\nMasukkan Id Motor : ");
								scanf("%d", &input.y);
								search(rootMotor, input.y, "Motor");
							}
							else if (input.x == 2){
								printf("\nMasukkan Id Mobil : ");
								scanf("%d", &input.y);
								search(rootMobil, input.y, "Mobil");
							}
						}while(input.x != 1 && input.x != 2);
						printf("\n\n");
					}
				}while(input.x != 4);
						
				printf("\n\n");
				system("cls");
				menuAnimation(0, 0, 0, 0, 0, 0);
				pilihan_menu();
			    break;	
						
			case 7:
		    	stringAnimation_exitProgram();
			    break;
			}				
					
	}while(*pilih != 7);
	
	free(input_karcis);
}

//Fungsi Pilihan Menu dalam Program
void pilihan_menu(){
	printf("\n\nBerikut daftar menu yang tersedia: \n");
    printf("[1]  Kendaraan Motor Masuk\n");
    printf("[2]  Kendaraan Mobil Masuk\n");
    printf("[3]  Daftar Kendaraan dan Kapasitas\n");
    printf("[4]  Kendaraan Keluar\n");
    printf("[5]  Panduan Penggunaan Program\n");
    printf("[6]  Implementasi Search Binary Tree (Menggunakan Id Kendaraan)\n");
    printf("[7]  Keluar dari Program\n");
    printf("Pilih Angka yang Ingin Anda Masukkan:\n");
}

//Fungsi Pengecekan Plat Kendaraan
int validasiPlat(kendaraan motor_mobil, char *jenis, int kapasitas, int* temp, int* loop){
	Data input;
	for (input.loop = 1; input.loop <= kapasitas + *temp; input.loop++){
		if (strcmp(motor_mobil.plat[*loop], motor_mobil.duplicatePlat[input.loop])==0){
			printf("Plat %s Tidak Boleh Sama\n\n", jenis);
			*loop-=1;
			return 0;
			break;
		}		
		else {
			continue;
		}
	}
	return 1;
}

//Fungsi Pencetakan Struk Pembayaran Parkir
void cetakStruk(kendaraan motor_mobil, Data input, int loop, char* kategori, int tagihan){
	printf("\n\n");
	printf ("          --------------------------------------------------------------------------\n");
	printf ("                       Nomor Karcis                 : %s              \n", motor_mobil.karcis[loop]);
	printf ("                       Nomor Plat Kendaraan         : %s              \n", motor_mobil.plat[loop]);
	printf ("                       Jenis kendaraan              : %s              \n", kategori);
	printf ("                       Durasi Parkir (per jam)      : %.2f Jam            \n", input.parkir);
	printf ("                       Total Tagihan Parkir         : %d              \n", tagihan);
	printf ("                       Total Pembayaran             : %d              \n", input.nominal);
	printf ("                       Kembalian                    : %d              \n", input.y);
	printf ("\n          --------------------------------------------------------------------------\n");
	printf ("                         TERIMAKASIH TELAH MENGGUNAKAN PELAYANAN KAMI                    ");
	printf ("\n          --------------------------------------------------------------------------\n\n");	
}

//Fungsi Output ketika User Memilih untuk Tidak Mencetak Struk Pembayaran
void skipStruk(){
	printf ("\n                    --------------------------------------------------------------------------\n");
	printf ("                                  TERIMAKASIH TELAH MENGGUNAKAN PROGRAM LINK IN PARK              ");
	printf ("\n                    --------------------------------------------------------------------------\n\n");
}

//Fungsi Panduan Penggunaan Program
void guideUser(){
    system("cls");
    printf ("\n\t\t+-------------------------------------------------------------------------------------------+\n");
    printf ("\t\t|                          PANDUAN PENGGUNAAN PROGRAM LINK-IN PARK                          |\n");
    printf ("\t\t|                                                                                           |\n");
    printf ("\t\t|   1. Program Berfungsi untuk Mengetahui Ketersediaan Lahan dan Menghitung Tarif Parkir.   |\n");
    printf ("\t\t|   2. Menu 1 untuk Memasukkan Data Motor Masuk.                                            |\n");
    printf ("\t\t|   3. Menu 2 untuk Memasukkan Data Mobil Masuk.                                            |\n");
    printf ("\t\t|   4. Menu 3 untuk Melihat Daftar Kendaraan yang Terparkir dan Kapasitas Tersisa.          |\n");
    printf ("\t\t|   5. Menu 4 untuk Menghitung Tarif Parkir dan Mendata Kendaraan Keluar.                   |\n");
    printf ("\t\t|   6. Menu 5 untuk Melihat Panduan Penggunaan                                              |\n");
    printf ("\t\t|   7. Menu 6 untuk Keluar Program.                                                         |\n");
    printf ("\t\t+-------------------------------------------------------------------------------------------+\n\n");

    system("pause");
    system("cls");
}

void salahInput_karcis(){
	printf("\n\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t\t\t|   Anda Salah Memasukkan Karcis Sebanyak Lima Kali   |\n");
	printf("\t\t\t|    Silakan Input Ulang Melalui Main Menu Kembali    |\n");
	printf("\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");	
}

//Fungsi Output ketika Exit Program
int stringAnimation_exitProgram(){
	
	Data k;
	char* animationString = (char*) malloc (53 * sizeof(int));
	
	system ("cls");
	animationString = "\t\t\t   Terimakasih Telah Menggunakan Program Ini ^_^   \n";
	printf("\t\t\t");
    for (k.loop=0;k.loop<26;k.loop++){
    	printf("+-");
    	usleep(1000);
	}
	printf("+\n");
    for (k.loop=0;k.loop<53;k.loop++){
    	printf("%c", animationString[k.loop]);
   		usleep(10000);
	}
	printf("\n");
	printf("\t\t\t");
    for (k.loop=0;k.loop<26;k.loop++){
   		printf("+-");
    	usleep(1000);
	}
	printf("+\n\n");
	
	system ("pause");
	return 0;
	
	free(animationString);

}

//Fungsi Output ketika Tempat Parkir Kosong
void kendaraanKosong(){
	printf ("\n\t\t\t--------------------------------------------------------------------------\n");
	printf ("\t\t\t                   Tidak Ada Kendaraan di Tempat Parkir                       ");
	printf ("\n\t\t\t--------------------------------------------------------------------------\n\n");	
}

// Fungsi Perhitungan Pembayaran Parkir Motor
int mtr (int a){
	int bayar = 2000;
	int i;
	if (a == 1){
		bayar = 2000;
	}
    else{
	    for (i = 1; i < a; i++){
		    bayar += 1000;
	    }
    }
	return bayar;
}

// Fungsi Perhitungan Pembayaran Parkir Mobil
int mbl (int b){
	int bayar = 5000;
	int i;
	if (b == 1){
		bayar = 5000;
	}
    else{
	    for (i = 1; i < b; i++){
		    bayar += 4000;
	    }
    }
	return bayar;
}

#endif
