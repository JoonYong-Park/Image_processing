#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#pragma warning(disable:4996)
#define PI 3.141592

unsigned char Readbuf[256][256];
unsigned char Writebuf[256][256];
unsigned char EdgeMap[256][256] = { 0 };
int visited[256][256] = { 0 };

float S[256][256];  // 에지 강도 맵
float D[256][256];  // 에지 방향 맵

double theta = PI / 4;      // 세타 값 (예: 45도)
double filter[11][11];      // 가우시안
double sigma = 1.0;         

int Tlow = 50;
int Thigh = 150;

//double gaussian(double x, double y) {
//    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
//}
//
//// 세타 값에 따른 가우시안 필터 생성
//void createGaussianFilter() {
//    double centerX = 5.0, centerY = 5.0; // 필터의 중심 좌표
//    double cosTheta = cos(theta), sinTheta = sin(theta);
//
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
//}


double gaussian(double x, double y) {
    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
}

void GaussianFilter() {
    double centerX = 5.0, centerY = 5.0; // 필터의 중심 좌표
    double cosTheta = cos(theta), sinTheta = sin(theta);

    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            // 회전 변환을 적용하여 x, y 좌표를 구합니다.
            double dx = cosTheta * (x - centerX) + sinTheta * (y - centerY);
            double dy = -sinTheta * (x - centerX) + cosTheta * (y - centerY);

            // 가우시안 함수를 적용하여 필터 값을 계산합니다.
            filter[y][x] = gaussian(dx, dy);
        }
    }
    // 가우시안 스무딩 적용

    int kernelSize = 5;
    int halfSize = kernelSize / 2;
    double sum, weight, gaussianKernel[5][5];

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            sum = 0.0;
            weight = 0.0;
            for (int k = -halfSize; k <= halfSize; k++) {
                for (int l = -halfSize; l <= halfSize; l++) {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && x < 256 && y >= 0 && y < 256) {
                        sum += Readbuf[x][y] * filter[k + halfSize][l + halfSize];
                        weight += filter[k + halfSize][l + halfSize];
                    }
                }
            }
            Writebuf[i][j] = (unsigned char)(sum / weight);
        }
    }
}

 // 에지 추적 (재귀)
void follow_edge( int y, int x) {
    visited[y][x] = 1;
    EdgeMap[y][x] = 255;

    for (int ny = y - 1; ny <= y + 1; ny++) {
        for (int nx = x - 1; nx <= x + 1; nx++) {
            if ( S[ny][nx] > Tlow && visited[ny][nx] == 0) {
                follow_edge(ny, nx);
            }
        }
    }
}

int main() {
    FILE* fp;

    // 영상 읽기
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);

    // 가우시안 스무딩
    //createGaussianFilter();
    GaussianFilter();

    //// 가우시안 필터를 적용
    //int halfSize = 5 / 2;
    //for (int y = 5; y < 507; y++) {
    //    for (int x = 5; x < 507; x++) {
    //        double sum = 0;
    //        double weight = 0;
    //        for (int k = -5; k <= 5; k++) {
    //            for (int j = -5; j <= 5; j++) {
    //                sum += Readbuf[y + j][x + k] * filter[j + 5][k + 5];
    //                weight += filter[k + halfSize][j + halfSize];
    //            }
    //        }
    //        Writebuf[y][x] = (unsigned char)sum;
    //    }
    //}

    fp = fopen("Gaussian2.raw", "wb");
    for (int i = 0; i < 256; i++) {
        fwrite(Writebuf[i], 1, 256, fp);
    }
    fclose(fp);

    // 소벨 마스크
    // 에지 강도 맵 - S
    // 에지 방향 맵 - D
    int maskX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int maskY[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            double dX = 0.0;
            double dY = 0.0;

            // 에지 강도 맵
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    dX += maskX[x + 1][y + 1] * Writebuf[i + x][j + y];
                    dY += maskY[x + 1][y + 1] * Writebuf[i + x][j + y];
                }
            }
            S[i][j] = sqrt((float)(dX * dX + dY * dY)); 
             
            // 에지 방향 맵
            float d = atan2(dY, dX);  // -PI ~ PI
            if(d < 0) {   
				d += PI;      // 0 ~ 2 PI
			}
            d = (int)(round((d / PI) * 4)) % 8;
            D[i][j] = d;
        }
    }

    // 비최대억제
    for (int i = 1; i <255; i++) {
        for (int j = 1; j < 255; j++) {
            if (D[i][j] == 0 || D[i][j] == 4) {
                if (S[i][j] <= S[i][j - 1] || S[i][j] <= S[i][j + 1]) S[i][j] = 0.0;
            }
            else if (D[i][j] == 1 || D[i][j] == 5) {
                if (S[i][j] <= S[i - 1][j - 1] || S[i][j] <= S[i + 1][j + 1]) S[i][j] = 0.0;
            }
            else if (D[i][j] == 2 || D[i][j] == 6) {
                if (S[i][j] <= S[i - 1][j] || S[i][j] <= S[i + 1][j]) S[i][j] = 0.0;
            }
            else if (D[i][j] == 3 || D[i][j] == 7) {
                if (S[i][j] <= S[i - 1][j + 1] || S[i][j] <= S[i + 1][j - 1]) S[i][j] = 0.0;
            }
        }
    }

    // 이력 임계값를 사용하여 에지 추적
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if (S[i][j] > Thigh && visited[i][j] == 0) {
                follow_edge(i, j);
            }
        }
    }

    fp = fopen("Canny2.raw", "wb");
    for (int i = 0; i < 256; i++) {
        fwrite(EdgeMap[i], 1, 256, fp);
    }
    fclose(fp);

    return 0;
}