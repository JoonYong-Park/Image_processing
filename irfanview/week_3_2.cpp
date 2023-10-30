#include <stdio.h>
#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main() {
    ////////// 2. ������׷� ��Ȱȭ //////////

    FILE* fp;                         // ���� ������ ����

    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    unsigned char Writebuf[256][256]; // ����   �� �迭 ����
    double Histogram[256] = { 0 };    // ������׷� �迭 ����
    double cnt[256] = { 0 };          // �̹��� �ȼ� ������ ���� ���� �����Դϴ�.

    // ���� �б�
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++){
        fread(Readbuf[i], 1, 256, fp);// (������ �ּ�, ������ ũ��, ������ ����, ����������)
    }
    fclose(fp);
    
    // ������׷��� �ۼ�
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Histogram[Readbuf[i][j]]++; 
        }
    }

    // ������׷� ����ȭ
    for (int i = 0; i < 256; i++) {
        Histogram[i] /= (256 * 256); // ����ȭ 
    }

    // ������׷� ���
    for (int i = 0; i < 256; i++)
        printf("%3d: %3f\n", i, Histogram[i]); // ������׷� ���

    /*********************************************/
    // ������
    for (int i = 0; i < 256; i++) {
        if(i == 0) 
            cnt[i] = Histogram[i];
		else 
            cnt[i] += Histogram[i] + cnt[i - 1];
        
    }
    // ������ L-1��° �� ���
    printf("����: %f\n", cnt[255]);

    ////// ��� ���̱� ���� ������׷� ��Ȱȭ //////
   
    // ���� ��Ȱȭ
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[i][j] = cnt[Readbuf[i][j]] * 255; 

    // ��Ȱȭ ��.�� ���� ���
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            printf("%d X %d = %d \n", i, j, Readbuf[i][j]);    // ��Ȱȭ �ȵ� ���� ���
            printf("%d X %d = %d \n\n", i, j, Writebuf[i][j]); // ��Ȱȭ ��   ���� ���
        }
    }

    // ���� ����
    fp = fopen("AVE256_Smoothing.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}