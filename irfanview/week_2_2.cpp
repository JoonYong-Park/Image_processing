#include <stdio.h>

#pragma warning(disable:4996) // 경고 메시지 4996을 무시하는 pragma 지시문

int main() {

    ////////// 2. 히스토그램 평활화 //////////

    FILE* fp;                         // 파일 포인터 선언
    unsigned char Readbuf[256][256];  // 256x256 크기의 8비트 배열 선언
    unsigned char Writebuf[256][256]; // 256x256 크기의 8비트 배열 선언
    double Histogram[256] = { 0 };    // 256개 요소를 가지는 배열로 히스토그램을 저장할 예정입니다.
    double cnt[256] = { 0 };          // 이미지 픽셀 개수를 세기 위한 변수입니다.

    // 영상 읽기
    fp = fopen("AVE256.RAW", "rb");
    for (int i = 0; i < 256; i++){
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);
    
    // 히스토그램을 생성
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Histogram[Readbuf[i][j]]++; //이건 무슨 배열이야?
        }
    }
    // 히스토그램 출력
    for (int i = 0; i < 256; i++)
        printf("%d: %f\n", i, Histogram[i]); // 히스토그램 출력


    // 히스토그램 정규화
    for (int i = 0; i < 256; i++)
        Histogram[i] /= (256 * 256); // 정규화 

    // 누적합
    for (int i = 0; i < 256; i++) {
        printf("%d: %f\n", i, Histogram[i]);
        if(i == 0) 
            cnt[i] = Histogram[i];
		else 
            cnt[i] = Histogram[i] + cnt[i - 1];
        
    }
    // 누적합 출력
    printf("총합: %f\n", cnt[255]);


    ////// 대비를 높이기 위한 히스토그램 평활화 //////
    
    // 영상 펼활화
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[i][j] = cnt[Readbuf[i][j]] * 255; // 히스토그램 평활화 (정규화 * 255) 누적합 안에 영상을 적용한다.

    // 영상 저장
    fp = fopen("AVE256_new.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    

    return 0;
}