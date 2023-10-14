#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_62() {
    ////////// �������� //////////

    FILE* fp;                         // ���� ������ ����

    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    unsigned char Writebuf[256][256]; // ����   �� �迭 ����
    double Histogram[256] = { 0 };    // ������׷� �迭 ����
    double cnt[256] = { 0 };          // �̹��� �ȼ� ������ ���� ���� �����Դϴ�.

    // ���� �б�
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (������ �ּ�, ������ ũ��, ������ ����, ����������)
    }
    fclose(fp);

    // ��������
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // �������� 1.5�� �����մϴ�.
            Writebuf[i][j] = (unsigned char)(255 * (pow((double)Readbuf[i][j]/255, 5.1)));

            // �ȼ��� ���� �����մϴ�.
            if (Writebuf[i][j] > 255) {
                Writebuf[i][j] = 255;
                printf("������");
            }
            else if (Writebuf[i][j] < 0) {
                Writebuf[i][j] = 0;
                printf("��ο��");
            }
        }
    }

    // �ռ���
    /*for (int i = 1; i < 255; i++) {
    		for (int j = 1; j < 255; j++) {
            			Writebuf[i][j] = (Readbuf[i - 1][j - 1] + Readbuf[i - 1][j] + Readbuf[i - 1][j + 1] + Readbuf[i][j - 1] + Readbuf[i][j] + Readbuf[i][j + 1] + Readbuf[i + 1][j - 1] + Readbuf[i + 1][j] + Readbuf[i + 1][j + 1]) / 9;
                        		}
    }*/

    // ���� ����
    fp = fopen("AVE256_Gamma.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}