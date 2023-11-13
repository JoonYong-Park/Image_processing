#include <stdio.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main_10() {
    FILE* fp; // ���� ������ ����
    unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
    unsigned char Writebuf[256][256]; // ���� �� �迭 ����

    // ���� �б�
    fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit_1.raw" ������ �б� ���� ����
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);

    // ���� ȸ��(���� ��ȯ) ���� ���
    





    /*for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			int x = (int)(i * 0.8660254 + j * 0.5);
			int y = (int)(-i * 0.5 + j * 0.8660254);
			if (x >= 0 && x < 256 && y >= 0 && y < 256) {
				Writebuf[i][j] = Readbuf[x][y];
			}
			else {
				Writebuf[i][j] = 0;
			}
		}
	}*/
    // ������ �߽��� �������� ȸ��(������) ���� ��� �˰���
    //for (int i = 0; i < 256; i++) {
    //    for (int j = 0; j < 256; j++) {
    //        
    //        int x = (int)((i - 128) * 0.8660254 + (j - 128) * 0.5 + 128);  // �Է� ������ �ȼ��� ���ο� x ��ǥ�� ���
    //        int y = (int)((-i + 128) * 0.5 + (j - 128) * 0.8660254 + 128); // �Է� ������ �ȼ��� ���ο� y ��ǥ�� ���

    //        // ���ο� ��ǥ�� ������ ���� ���� �ִ��� Ȯ���մϴ�.
    //        if (x >= 0 && x < 256 && y >= 0 && y < 256) {
    //            // ���ο� ��ǥ�� ������ ���� ���� ������, �б� ������ �ȼ� ���� ���� ���ۿ� �����մϴ�.
    //            Writebuf[i][j] = Readbuf[x][y];
    //        }
    //        else {
    //            // ���ο� ��ǥ�� ������ ���� ���� ������, �ȼ� ���� 0���� �����մϴ�.
    //            Writebuf[i][j] = 0;
    //        }
    //    }
    //}

    // ������ 2�� Ȯ��(�ֱٹ� �̿� ������) ���� ���
    /*for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            int x = (int)(i * 0.5);
            int y = (int)(j * 0.5);
            if (x >= 0 && x < 256 && y >= 0 && y < 256) {
                 Writebuf[i][j] = Readbuf[x][y];
            }
            else {
                Writebuf[i][j] = 0;
            }
        }
    }*/

    // ������ 2�� ���(burt����) �������
    for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {

			int x = (int)(i * 2);
			int y = (int)(j * 2);
			if (x >= 0 && x < 256 && y >= 0 && y < 256) {
				Writebuf[i][j] = Readbuf[x][y];
			}
			else {
				Writebuf[i][j] = 0;
			}
		}
	}








    

    // ���� ����
    fp = fopen("LENA_256x256_8bit_2_up_down3333333333333333.raw", "wb");
    for (int i = 0; i < 256; i++) {
        fwrite(Writebuf[i], 1, 256, fp);
    }
    fclose(fp);

    return 0;
}
