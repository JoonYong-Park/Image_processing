#include <stdio.h>
#pragma warning(disable:4996)// ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_3(void) {
    ////////// 1. ������׷� ����ȭ //////////

    FILE* fp;  // ���� ������ ����

    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    double Histogram[256] = { 0 };    // ������׷� �迭 ����
    double cnt = 0;                   // ������

    // ���� �б�
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);  // (������ �ּ�, ������ ũ��, ������ ����, ����������)
    }
    fclose(fp);


    // ������׷� �ۼ�
    for (int j = 0; j < 256; j++) {
        for (int i = 0; i < 256; i++) {
            Histogram[Readbuf[j][i]]++; 
        }
    }

    // ������׷� ����ȭ (������׷� �� ���� = 1) - ����ȭ ���ϸ� �������� 256*256���� ����
    for (int i = 0; i < 256; i++) {
        Histogram[i] = Histogram[i] / (256 * 256);
    }

    // ������׷� ���
    for (int i = 0; i < 256; i++)
        printf("%3d: %3f\n", i, Histogram[i]); // ������׷� ���

    // ������׷��� ��
    for (int i = 0; i < 256; i++) {
        cnt += Histogram[i];
    }
    // ������ ���
    printf("����: %f\n", cnt);
    return 0;
}