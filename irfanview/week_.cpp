//#include <stdio.h>
//#include <math.h>
//
//#pragma warning(disable:4996)
//#define PI 3.141592
//
//unsigned char Readbuf[256][256];
//unsigned char Writebuf[256][256];
//
//int visited[256][256] = { 0 };
//int EdgeMap[256][256] = { 0 };
//
//double theta = PI / 4;      // ��Ÿ �� (��: 45��)
//double filter[11][11];      // ����þ� ����
//
//
//float S[256][256];  // ���� ���� ��
//float D[256][256];  // ���� ���� ��
//
//double sigma = 1.0;
//int Tlow = 50;
//int Thigh = 150;
//
//double gaussian(double x, double y) {
//    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
//}
//
//// ��Ÿ ���� ���� ����þ� ���� ����
//void createGaussianFilter(double theta, double sigma, double filter[11][11]) {
//    double centerX = 5.0, centerY = 5.0; // ������ �߽� ��ǥ
//    double cosTheta = cos(theta), sinTheta = sin(theta);
//
//    printf("����þ� ");
//    for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            // ȸ�� ��ȯ�� �����Ͽ� x, y ��ǥ�� ���մϴ�.
//            double dx = cosTheta * (x - centerX) + sinTheta * (y - centerY);
//            double dy = -sinTheta * (x - centerX) + cosTheta * (y - centerY);
//
//            // ����þ� �Լ��� �����Ͽ� ���� ���� ����մϴ�.
//            filter[y][x] = gaussian(dx, dy);
//        }
//    }
//    // ����þ� ������ ����
//    double sum = 0.0;
//    for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            sum += filter[y][x];
//        }
//    }
//    for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            filter[y][x] /= sum;
//        }
//    }
//
//
//
//}
//
//
//
//
//
//
//
//
//// ���� ���� (���)
//void follow_edge(int y, int x) {
//    printf("���� ����(���)  ");
//    visited[y][x] = 1;
//    EdgeMap[y][x] = 255;
//
//    int dy[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
//    int dx[8] = { -1, 0,   1, -1, 1, -1, 0, 1 };
//
//    for (int ny = y - 1; ny <= y + 1; ny++) {
//        for (int nx = x - 1; nx <= x + 1; nx++) {
//            if (ny >= 0 && ny < 256
//                && nx >= 0 && nx < 256
//                && S[ny][nx] > Tlow
//                && visited[ny][nx] == 0) {
//                follow_edge(ny, nx);
//
//            }
//        }
//    }
//}
//
//int main_9516() {
//    FILE* fp;
//
//    // ���� �б�
//    fp = fopen("LENA_256x256_8bit.raw", "rb");
//    for (int i = 0; i < 256; i++) {
//        fread(Readbuf[i], 1, 256, fp);
//    }
//    fclose(fp);
//
//
//    // ��Ÿ ���� ���� ����þ� ���͸� ����
//    createGaussianFilter(theta, sigma, filter);
//
//    // ���� ���� ���
//    /*for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            printf("%f ", filter[y][x]);
//        }
//        printf("\n");
//    }*/
//
//
//    // �Һ�  ���͸� ����
//    double sobelX[3][3] = {
//        {-1.0, 0.0, 1.0},
//        {-2.0, 0.0, 2.0},
//        {-1.0, 0.0, 1.0}
//    };
//    double sobelY[3][3] = {
//        {-1.0, -2.0, -1.0},
//        {0.0, 0.0, 0.0},
//        {1.0, 2.0, 1.0}
//    };
//
//    // �Һ� ���� �����Ͽ� ���� ���� ��S, ���� ���� �� D�� ��´�.
//    printf("�Һ� ");
//    for (int i = 1; i < 256; i++) {
//        for (int j = 1; j < 256; j++) {
//            double sumX = 0.0;
//            double sumY = 0.0;
//
//            for (int x = 0; x < 3; x++) {
//                for (int y = 0; y < 3; y++) {
//                    int imgX = i + x - 1;
//                    int imgY = j + y - 1;
//
//                    sumX += filter[imgX][imgY] * sobelX[x][y];
//                    sumY += filter[imgX][imgY] * sobelY[x][y];
//                }
//            }
//
//
//            S[i][j] = sqrt((float)sumX * sumX + sumY * sumY); // ���� ���� ��
//            //D[i][j] = atan2(sumY, sumX) * 180.0 / PI;  // ���� ���� ��
//
//            // ���� ����
//            double angle = atan2(sumY, sumX) * 180 / PI;
//
//            angle = (angle < 0) ? (180.0 + angle) : angle;
//
//            // ���� ���� 0, 45, 90, 135
//            if (angle >= 0 && angle < 22.5)
//                D[i][j] = 0;
//            else if (angle >= 22.5 && angle < 67.5)
//                D[i][j] = 45;
//            else if (angle >= 67.5 && angle < 112.5)
//                D[i][j] = 90;
//            else if (angle >= 112.5 && angle < 157.5)
//                D[i][j] = 135;
//            else
//                D[i][j] = 0;
//        }
//    }
//
//    // ���ִ����
//    printf("���ִ����");
//    for (int y = 1; y < 256; y++) {
//        for (int x = 1; x < 256; x++) {
//            float currentPixel = S[y][x];
//            int direction = D[y][x];
//
//            float neighbor1 = 0.0;
//            float neighbor2 = 0.0;
//
//            switch (direction) {
//            case 0:
//                neighbor1 = S[y][x - 1];
//                neighbor2 = S[y][x + 1];
//                break;
//            case 45:
//                neighbor1 = S[y - 1][x + 1];
//                neighbor2 = S[y + 1][x - 1];
//                break;
//            case 90:
//                neighbor1 = S[y - 1][x];
//                neighbor2 = S[y + 1][x];
//                break;
//            case 135:
//                neighbor1 = S[y - 1][x - 1];
//                neighbor2 = S[y + 1][x + 1];
//                break;
//            default:
//                continue;
//            }
//
//            if (currentPixel <= neighbor1 || currentPixel <= neighbor2) {
//                S[y][x] = 0;
//            }
//        }
//    }
//
//
//
//    // ���� ����(���)
//    for (int i = 0; i < 256; i++) {
//        for (int j = 0; j < 256; j++) {
//            printf("%d ", S[i][j]);
//            if (S[i][j] > Thigh && visited[i][j] == 0) {
//                printf("���� ���� ");
//                follow_edge(i, j);
//            }
//        }
//    }
//    printf(" ����\n");
//
//    // ��� ���� ����
//    fp = fopen("LENA_256x256_8bit_CannyEdge!!!!!!!!!!!!!!!!!!!!.raw", "wb");
//    for (int i = 0; i < 256; i++) {
//        fwrite(EdgeMap[i], 1, 256, fp);
//    }
//    fclose(fp);
//
//    return 0;
//}