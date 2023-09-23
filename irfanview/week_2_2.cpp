#include <stdio.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main() {

    ////////// 2. ������׷� ��Ȱȭ //////////

    FILE* fp;                         // ���� ������ ����
    unsigned char Readbuf[256][256];  // 256x256 ũ���� 8��Ʈ �迭 ����
    unsigned char Writebuf[256][256]; // 256x256 ũ���� 8��Ʈ �迭 ����
    double Histogram[256] = { 0 };    // 256�� ��Ҹ� ������ �迭�� ������׷��� ������ �����Դϴ�.
    double cnt[256] = { 0 };          // �̹��� �ȼ� ������ ���� ���� �����Դϴ�.

    // ���� �б�
    fp = fopen("AVE256.RAW", "rb");
    for (int i = 0; i < 256; i++){
        fread(Readbuf[i], 1, 256, fp);
    }
    fclose(fp);
    
    // ������׷��� ����
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            Histogram[Readbuf[i][j]]++; //�̰� ���� �迭�̾�?
        }
    }
    // ������׷� ���
    for (int i = 0; i < 256; i++)
        printf("%d: %f\n", i, Histogram[i]); // ������׷� ���


    // ������׷� ����ȭ
    for (int i = 0; i < 256; i++)
        Histogram[i] /= (256 * 256); // ����ȭ 

    // ������
    for (int i = 0; i < 256; i++) {
        printf("%d: %f\n", i, Histogram[i]);
        if(i == 0) 
            cnt[i] = Histogram[i];
		else 
            cnt[i] = Histogram[i] + cnt[i - 1];
        
    }
    // ������ ���
    printf("����: %f\n", cnt[255]);


    ////// ��� ���̱� ���� ������׷� ��Ȱȭ //////
    
    // ���� ��Ȱȭ
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            Writebuf[i][j] = cnt[Readbuf[i][j]] * 255; // ������׷� ��Ȱȭ (����ȭ * 255) ������ �ȿ� ������ �����Ѵ�.

    // ���� ����
    fp = fopen("AVE256_new.raw", "wb");
    for (int i = 0; i < 256; i++)
        fwrite(Writebuf[i], 1, 256, fp);
    fclose(fp);

    

    return 0;
}