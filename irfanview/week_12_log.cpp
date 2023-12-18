#include <stdio.h>
#include <math.h>
#include <Windows.h>

#pragma warning(disable:4996)


#define W 512
#define H 512
#define Pi 3.141592
#define e 2.71828

int main_12log() {
    FILE* fp;
    unsigned char** Readbuf = (unsigned char**)malloc(sizeof(unsigned char*) * H);
    unsigned char** Writebuf = (unsigned char**)malloc(sizeof(unsigned char*) * H);
    double** tmp = (double**)malloc(sizeof(double*) * H);


    for (int i = 0; i < H; i++) {
        Readbuf[i] = (unsigned char*)malloc(sizeof(unsigned char) * W);
    }

    for (int i = 0; i < H; i++) {
        Writebuf[i] = (unsigned char*)malloc(sizeof(unsigned char) * W);
    }

    for (int i = 0; i < H; i++) {
        tmp[i] = (double*)malloc(sizeof(double) * W);
    }

    fp = fopen("nightview512gray.raw", "rb");

    for (int i = 0; i < H; i++)
        fread(Readbuf[i], 1, W, fp);
    fclose(fp);



    double sigma = 0.5;

    int end = 0;



    if ((int)(sigma * 6) % 2 == 0) end = (int)(sigma * 6) + 1;

    else end = (int)(sigma * 6);



    double** gausian = (double**)malloc(sizeof(double*) * end);



    for (int i = 0; i < end; i++) {

        gausian[i] = (double*)malloc(sizeof(double) * end);

    }



    for (int i = 0; i < end; i++) {

        for (int j = 0; j < end; j++) {

            gausian[i][j] = (1.0 / 2.0 * Pi * pow(sigma, 2)) * pow(e, -1 * (pow(j, 2) + pow(i, 2) / 2 * pow(sigma, 2)));

            printf("%lf ", gausian[i][j]);

        }

        printf("\n");

    }



    // LoG filter

    double filter[3][3] = {

        {0.4038, 0.8012, 0.4038},

        {0.8021, -4.8233, 0.8021},

        {0.4038, 0.8021, 0.4038}

    };



    for (int i = 1; i < H - 1; i++) {

        for (int j = 1; j < W - 1; j++) {

            double ans = 0.0;



            for (int x = 0; x < 3; x++) {

                for (int y = 0; y < 3; y++) {

                    int imgX = i + x - 1;

                    int imgY = j + y - 1;



                    ans += (double)Readbuf[imgX][imgY] * filter[x][y];

                }

            }



            tmp[i][j] = ans;

        }

    }



    // 임계값

    double T = 35.0;



    int a[8][2] = {

        {-1, -1}, {1, 1},

        {-1, 1}, {1, -1},

        {0, -1}, {0, 1},

        {-1, 0}, {1, 0}

    };



    for (int i = 1; i < H - 1; i++) {

        for (int j = 1; j < W - 1; j++) {

            int over = 1;



            for (int k = 0; k < 4; k++) {

                int idx = k * 2;



                int x1 = i + a[idx][0];

                int y1 = j + a[idx][1];



                int x2 = i + a[idx + 1][0];

                int y2 = j + a[idx + 1][1];



                // 0은 부호 다르다고 하지 않음

                if (tmp[x1][y1] == 0.0 || tmp[x2][y2] == 0.0) continue;



                // 부호 판별

                int p1 = tmp[x1][y1] > 0 ? 1 : 0;

                int p2 = tmp[x2][y2] > 0 ? 1 : 0;



                if (p1 = !p2) {

                    double diff = fabs(tmp[x1][y1] - tmp[x2][y2]);



                    if (diff <= T) {

                        over = 0;

                        break;

                    }

                }

            }





            if (over) Writebuf[i][j] = 255;

            else Writebuf[i][j] = 0;

        }

    }



    fp = fopen("log_filterT=35.raw", "wb");



    for (int i = 0; i < H; i++) {

        fwrite(Writebuf[i], 1, W, fp);

    }

    fclose(fp);



    for (int i = 0; i < H; i++) {

        free(Readbuf[i]);

    }

    free(Readbuf);



    for (int i = 0; i < H; i++) {

        free(Writebuf[i]);

    }

    free(Writebuf);



    for (int i = 0; i < H; i++) {

        free(tmp[i]);

    }

    free(tmp);



    return 0;

}