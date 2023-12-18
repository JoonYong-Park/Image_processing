#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996)
#define PI 3.14159265358979323846

double gaussian(double x, double y, double sigma) {
    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
}

// ��Ÿ ���� ���� ����þ� ���� ����
void createGaussianFilter(double theta, double sigma, double filter[11][11]) {
    double centerX = 5.0, centerY = 5.0; // ������ �߽� ��ǥ
    double cosTheta = cos(theta), sinTheta = sin(theta);

    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            // ȸ�� ��ȯ�� �����Ͽ� x, y ��ǥ�� ���մϴ�.
            double dx = cosTheta * (x - centerX) + sinTheta * (y - centerY);
            double dy = -sinTheta * (x - centerX) + cosTheta * (y - centerY);

            // ����þ� �Լ��� �����Ͽ� ���� ���� ����մϴ�.
            filter[y][x] = gaussian(dx, dy, sigma);
        }
    }
}


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


    double theta = PI / 4; // ��Ÿ �� (��: 45��)
    double sigma = 1.0; // �ñ׸� ��
    double filter[11][11]; // ����þ� ����

    // ��Ÿ ���� ���� ����þ� ���͸� �����մϴ�.
    createGaussianFilter(theta, sigma, filter);

    // ���� ���� ����մϴ�.
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            printf("%f ", filter[y][x]);
        }
        printf("\n");
    }

  

    // ����þ� ���͸� ����
    for (int y = 5; y < 507; y++) {
        for (int x = 5; x < 507; x++) {
			double sum = 0;
            for (int k = -5; k <= 5; k++) {
                for (int j = -5; j <= 5; j++) {
					sum += Readbuf[y + j][x + k] * filter[j + 5][k + 5];
				}
			}
			Writebuf[y][x] = (unsigned char)sum;
		}
	}

    //// ���ö�þ� ���͸� ����
    //int dx[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
    //int dy[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
    //int mask[9] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };

    //for (int y = 1; y < 511; y++) {
    //    for (int x = 1; x < 511; x++) {
    //        int sum = 0;
    //        for (int i = 0; i < 9; i++) {
    //            int nx = x + dx[i];
    //            int ny = y + dy[i];
    //            if (nx >= 0 && nx < 512 && ny >= 0 && ny < 512) {
    //                sum += Writebuf[ny][nx] * mask[i];
    //            }
    //        }
    //        Writebuf[y][x] = (unsigned char)abs(sum);
    //    }
    //}


    // ��� ���� ����
    fp = fopen("nightview512gray_Gaussian.raw", "wb");
    for (int i = 0; i < 512; i++) {
        fwrite(Writebuf[i], 1, 512, fp);
    }
    fclose(fp);

    return 0;

}