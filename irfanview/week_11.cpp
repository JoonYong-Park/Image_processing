#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996)

int main_11() {
    FILE* fp;
    unsigned char Readbuf[256][256];
    unsigned char Writebuf[256][256];
    int Gx, Gy, sum; // 소벨 마스크를 적용한 결과를 저장할 변수

    // 소벨 마스크
    int maskX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int maskY[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    // 영상 읽기
    fp = fopen("LENA_256x256_8bit_1.raw", "rb");
    for (int i = 0; i < 256; i++) {
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);

    // 소벨 마스크 적용
    for (int y = 1; y < 255; y++) {
        for (int x = 1; x < 255; x++) {
            Gx = 0;
            Gy = 0;
            for (int k = -1; k <= 1; k++) {
                for (int j = -1; j <= 1; j++) {
                    Gx += Readbuf[y + j][x + k] * maskX[j + 1][k + 1]; 
                    Gy += Readbuf[y + j][x + k] * maskY[j + 1][k + 1];
                }
            }
            sum = abs(Gx) + abs(Gy);
            if (sum > 255) sum = 255;
            if (sum < 0) sum = 0;
            Writebuf[y][x] = sum;
        }
    }

    // 영상 저장
    fp = fopen("LENA_256x256_8bit_mask.raw", "wb");
    for (int i = 0; i < 256; i++) {
        fwrite(Writebuf[i], 1, 256, fp);
    }
    fclose(fp);

    return 0;
}
