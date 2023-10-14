#include <stdio.h>
#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_6() {
    ////////// ������ //////////

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

    // ������(���)
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Writebuf[i][j] = Readbuf[i][j] + 20;
            
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
    // ������(��Ӱ�)
    /*for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Writebuf[i][j] = Readbuf[i][j] - 5;
            
            if (Writebuf[i][j] > 255) {  //�ǹ� ����
			    Writebuf[i][j] = 255;
                printf("������");
            }
            else if (Writebuf[i][j] < 0) {
                Writebuf[i][j] = 0;
                printf("������");
            }
        }
	}*/
    
    // ���� ����
    fp = fopen("AVE256_1_point.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}