#include <stdio.h>
#include <stdlib.h>

struct hasta
{
    long long int tcKimlik;
    char ad[20];
    char soyad[20];
    char hastalik[20];
};

int secimGir(void);
void textDosya(FILE *);
void yeniKayit(FILE *);
void kayitSil(FILE *);
void listele(FILE *);

int main(void)
{
    FILE *myPtr;
    int secim;
    if((myPtr = fopen("hasta.dat", "r+")) == NULL)
        printf("Dosya acilamadi\n");
    else
    {
        while((secim = secimGir()) != 5)
        {
            switch(secim)
            {
                case 1: textDosya(myPtr);break;
                case 2: yeniKayit(myPtr);break;
                case 3: kayitSil(myPtr);break;
                case 4: listele(myPtr);break;
            }
        }
        fclose(myPtr);
    }
}

int secimGir()
{
    int menuSecim;
    printf("\nSecimini yap"
           "1-hasta.dat dosyasinin icerigini\n"
           "formatli olarak \"hastalar.dat\" dosyasina yaz\n"
           "2-yeni hasta ekle\n"
           "3-hasta sil\n"
           "4-hasta.dat dosyasinin icerigini listele\n"
           "5-cikis\n?");
    scanf("%d", &menuSecim);
    return menuSecim;
}

void textDosya(FILE *okuptr)
{
    FILE *yazptr;
    struct hasta hastaBilgi = {0,"","",""};
    if((yazptr = fopen("hastalar.dat", "w")) == NULL);
        printf("Dosya acilamadi\n");
    else
    {
        rewind(okuptr);
        fprintf(yazptr,"%lld%s%s%s", "TC kimlik", "Ad", "Soyad", "Hastalik");
        while(!feof(okuptr))
        {
            fread(&hastaBilgi, sizeof(struct hasta),1,okuptr);
            if(hastaBilgi.tcKimlik!=0)
            fprintf(yazptr, "%lld%s%s%s\n", hastaBilgi.tcKimlik, hastaBilgi.ad, hastaBilgi.soyad, hastaBilgi.hastalik);
        }
        fclose(yazptr);
    }
}

void kayitSil(FILE *fptr)
{
    struct hasta hastaBilgi, bosHasta = {0, "", "", ""};
    int hastaID;
    printf("Silinecek hastanin TC kimlik giriniz: ");
    scanf("%lld", &hastaID);
    fseek(fptr,(hastaID-1)*sizeof(struct hasta),SEEK_SET);
    fread(&hastaBilgi, sizeof(struct hasta),1,fptr);
    if(hastaBilgi.tcKimlik==0)
        printf("Silinecek hasta yok\n");
    else
    {
        fseek(fptr,(hastaID-1)*sizeof(struct hasta),SEEK_SET);
        fwrite(&bosHasta, sizeof(struct hasta),1,fptr);
    }
}

void yeniKayit(FILE *fptr)
{
    int hastaID;
    struct hasta hastaBilgi = {0, "", "", ""};
    printf("Yeni hastanin TC kimlik giriniz: ");
    scanf("%lld", &hastaID);
    fseek(fptr,(hastaID-1)*sizeof(struct hasta),SEEK_SET);
    fread(&hastaBilgi, sizeof(struct hasta),1,fptr);
    if(hastaBilgi.tcKimlik==0)
        printf("Bu hasta zaten mevcut\n");
    else
    {
        printf("Ad, soyad, hastalik gir: \n");
        scanf("%s%s%s", hastaBilgi.ad, hastaBilgi.soyad, hastaBilgi.hastalik);
        fseek(fptr,(hastaID-1)*sizeof(struct hasta),SEEK_SET);
        fwrite(&hesapBilgi, sizeof(struct hasta),1,fptr);
    }

}

void listele(FILE *fptr)
{
    struct hasta hastaBilgi = {0, "", "", ""};

    printf("%s%s%s%s\n","TC kimlik", "Ad", "Soyad", "Hastalik");
}
