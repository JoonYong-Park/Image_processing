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
//double theta = PI / 4;      // 세타 값 (예: 45도)
//double filter[11][11];      // 가우시안 필터
//
//
//float S[256][256];  // 에지 강도 맵
//float D[256][256];  // 에지 방향 맵
//
//double sigma = 1.0;
//int Tlow = 50;
//int Thigh = 150;
//
//double gaussian(double x, double y) {
//    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
//}
//
//// 세타 값에 따른 가우시안 필터 생성
//void createGaussianFilter(double theta, double sigma, double filter[11][11]) {
//    double centerX = 5.0, centerY = 5.0; // 필터의 중심 좌표
//    double cosTheta = cos(theta), sinTheta = sin(theta);
//
//    printf("가우시안 ");
//    for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            // 회전 변환을 적용하여 x, y 좌표를 구합니다.
//            double dx = cosTheta * (x - centerX) + sinTheta * (y - centerY);
//            double dy = -sinTheta * (x - centerX) + cosTheta * (y - centerY);
//
//            // 가우시안 함수를 적용하여 필터 값을 계산합니다.
//            filter[y][x] = gaussian(dx, dy);
//        }
//    }
//    // 가우시안 스무딩 적용
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
//// 에지 추적 (재귀)
//void follow_edge(int y, int x) {
//    printf("에지 추적(재귀)  ");
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
//    // 영상 읽기
//    fp = fopen("LENA_256x256_8bit.raw", "rb");
//    for (int i = 0; i < 256; i++) {
//        fread(Readbuf[i], 1, 256, fp);
//    }
//    fclose(fp);
//
//
//    // 세타 값에 따른 가우시안 필터를 생성
//    createGaussianFilter(theta, sigma, filter);
//
//    // 필터 값을 출력
//    /*for (int y = 0; y < 11; y++) {
//        for (int x = 0; x < 11; x++) {
//            printf("%f ", filter[y][x]);
//        }
//        printf("\n");
//    }*/
//
//
//    // 소벨  필터를 적용
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
//    // 소벨 필터 적용하여 에지 강도 맵S, 에지 방향 맵 D를 얻는다.
//    printf("소벨 ");
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
//            S[i][j] = sqrt((float)sumX * sumX + sumY * sumY); // 에지 강도 맵
//            //D[i][j] = atan2(sumY, sumX) * 180.0 / PI;  // 에지 방향 맵
//
//            // 에지 방향
//            double angle = atan2(sumY, sumX) * 180 / PI;
//
//            angle = (angle < 0) ? (180.0 + angle) : angle;
//
//            // 에지 방향 0, 45, 90, 135
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
//    // 비최대억제
//    printf("비최대억제");
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
//    // 에지 추적(재귀)
//    for (int i = 0; i < 256; i++) {
//        for (int j = 0; j < 256; j++) {
//            printf("%d ", S[i][j]);
//            if (S[i][j] > Thigh && visited[i][j] == 0) {
//                printf("에지 추적 ");
//                follow_edge(i, j);
//            }
//        }
//    }
//    printf(" 종료\n");
//
//    // 결과 영상 쓰기
//    fp = fopen("LENA_256x256_8bit_CannyEdge!!!!!!!!!!!!!!!!!!!!.raw", "wb");
//    for (int i = 0; i < 256; i++) {
//        fwrite(EdgeMap[i], 1, 256, fp);
//    }
//    fclose(fp);
//
//    return 0;
//}