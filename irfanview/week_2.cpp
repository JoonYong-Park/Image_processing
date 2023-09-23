#include <stdio.h>

#pragma warning(disable:4996)// ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_2(void) {

    ////////// 1. ������׷� ����ȭ //////////

    FILE* fp;  // ���� ������ ����
    unsigned char Readbuf[256][256];// 256x256 ũ���� 8��Ʈ �迭 ����
    double Histogram[256] = { 0 };  
    double cnt = 0;                 

    // ���� �б�
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);


    // ������׷� �ۼ�
    for (int j = 0; j < 256; j++) {
        for (int i = 0; i < 256; i++) {
            Histogram[Readbuf[j][i]]++; 
        }
    }
    // ������׷� ����ȭ (������׷� �� ���� = 1)
    // ����ȭ ���ϸ� �������� 256*256���� ����
    for (int i = 0; i < 256; i++) {
        Histogram[i] = Histogram[i] / (256 * 256);
    }

    // ������
    for (int i = 0; i < 256; i++) {
        printf("%d : %f \n",i, Histogram[i]);
        cnt += Histogram[i];
    }
    // ������ ���
    printf("����: %f\n", cnt);
    return 0;
}