#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996)
#define PI 3.14159265358979323846



int main_12() {
    FILE* fp;
    unsigned char Readbuf[512][512];
    unsigned char Writebuf[512][512];

    // ���� �б�
    fp = fopen("nightview512gray.raw", "rb");
    for (int i = 0; i < 512; i++) {
        fread(Readbuf[i], 1, 512, fp);
    }
    fclose(fp);

    // ���� �˰���


    

    // ��� ���� ����
    fp = fopen("nightview512gray_Gaussian.raw", "wb");
    for (int i = 0; i < 512; i++) {
        fwrite(Writebuf[i], 1, 512, fp);
    }
    fclose(fp);

    return 0;

}