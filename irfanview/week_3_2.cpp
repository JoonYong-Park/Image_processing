#include <stdio.h>
#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main() {
    ////////// 2. 히스토그램 평활화 //////////

    FILE* fp;                         // 파일 포인터 선언

    unsigned char Readbuf[256][256];  // 영상 읽을 배열 선언
    unsigned char Writebuf[256][256]; // 영상   쓸 배열 선언
    double Histogram[256] = { 0 };    // 히스토그램 배열 선언
    double cnt[256] = { 0 };          // 이미지 픽셀 개수를 세기 위한 변수입니다.

    // 영상 읽기
    fp = fopen("AVE256.raw", "rb");
    for (int i = 0; i < 256; i++){
        fread(Readbuf[i], 1, 256, fp);// (저장할 주소, 데이터 크기, 데이터 개수, 파일포인터)
    }
    fclose(fp);
    
    // 히스토그램을 작성
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Histogram[Readbuf[i][j]]++; 
        }
    }

    // 히스토그램 정규화
    for (int i = 0; i < 256; i++) {
        Histogram[i] /= (256 * 256); // 정규화 
    }

    // 히스토그램 출력
    for (int i = 0; i < 256; i++)
        printf("%3d: %3f\n", i, Histogram[i]); // 히스토그램 출력

    /*********************************************/
    // 누적합
    for (int i = 0; i < 256; i++) {
        if(i == 0) 
            cnt[i] = Histogram[i];
		else 
            cnt[i] += Histogram[i] + cnt[i - 1];
        
    }
    // 누적합 L-1번째 값 출력
    printf("총합: %f\n", cnt[255]);

    ////// 대비를 높이기 위한 히스토그램 평활화 //////
   
    // 영상 펼활화
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[i][j] = cnt[Readbuf[i][j]] * 255; 

    // 평활화 전.후 영상 출력
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            printf("%d X %d = %d \n", i, j, Readbuf[i][j]);    // 평활화 안된 영상 출력
            printf("%d X %d = %d \n\n", i, j, Writebuf[i][j]); // 평활화 된   영상 출력
        }
    }

    // 영상 저장
    fp = fopen("AVE256_Smoothing.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    return 0;
}