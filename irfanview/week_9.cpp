#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_9() {
    ////////// �������� //////////

    FILE* fp;                         // ���� ������ ����

    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    unsigned char Writebuf[256][256]; // ����   �� �迭 ����
    double Histogram[256] = { 0 };    // ������׷� �迭 ����
    double cnt[256] = { 0 };          // �̹��� �ȼ� ������ ���� ���� �����Դϴ�.

    // ���� �б�
    fp = fopen("LENA_256x256_8bit_t_Otsu.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (������ �ּ�, ������ ũ��, ������ ����, ����������)
    }
    fclose(fp);

    // ������ ��â �˰���
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            if (Readbuf[i][j-1] == 255 || Readbuf[i][j] == 255 || Readbuf[i][j+1] == 255) {
				Writebuf[i][j] = 255;
			}
            else {
				Writebuf[i][j] = 0;
			}
		}
	}

    // ������ ħ�� �˰���
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            if (Readbuf[i][j - 1] == 255 && Readbuf[i][j] == 255 && Readbuf[i][j + 1] == 255) {
                Writebuf[i][j] = 255;
            }
            else {
                Writebuf[i][j] = 0;
            }
        }
    }

    // �������� �׶���Ʈ
    for (int i = 1; i < 255; i++) {
    		for (int j = 1; j < 255; j++) {
            			Writebuf[i][j] = Readbuf[i][j] - Readbuf[i][j - 1];
      		}
    }

    








    // ���� ����
    fp = fopen("LENA_256x256_8bit_t_Otsu_morphology.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}