#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_7() {
    ////////// �߰��� ���� //////////

    FILE* fp;                         // ���� ������ ����

    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    unsigned char Writebuf[256][256]; // ����   �� �迭 ����
    double Histogram[256] = { 0 };    // ������׷� �迭 ����
    double cnt[256] = { 0 };          // �̹��� �ȼ� ������ ���� ���� �����Դϴ�.

    // ���� �б�
    fp = fopen("������-LENA_256x256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);// (������ �ּ�, ������ ũ��, ������ ����, ����������)
    }
    fclose(fp);

    // �޵�� ����: 3x3
    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
			unsigned char temp[9] = { 0 };
			temp[0] = Readbuf[i - 1][j - 1];
			temp[1] = Readbuf[i - 1][j];
			temp[2] = Readbuf[i - 1][j + 1];
			temp[3] = Readbuf[i][j - 1];
			temp[4] = Readbuf[i][j];
			temp[5] = Readbuf[i][j + 1];
			temp[6] = Readbuf[i + 1][j - 1];
			temp[7] = Readbuf[i + 1][j];
			temp[8] = Readbuf[i + 1][j + 1];

            for (int k = 0; k < 9; k++) {
                for (int l = 0; l < 9 - k - 1; l++) {
                    if (temp[l] > temp[l + 1]) {
						unsigned char tmp = temp[l];
						temp[l] = temp[l + 1];
						temp[l + 1] = tmp;
					}
				}
			}

			Writebuf[i][j] = temp[4];
		}
	}

    // ���� ����
    fp = fopen("������-LENA_256x256_new.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}