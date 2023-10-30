#include <stdio.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�


int main_2() {
	/////// ���� ��� �� �����¿� ��Ī ///////

	FILE* fp; // ���� ������ ����

	unsigned char Readbuf[256][256];  // ���� ���� �迭 ����
	unsigned char Writebuf[256][256]; // ����   �� �迭 ����


	// ���� �б�
	fp = fopen("LENA_256x256_8bit_1.raw", "rb"); // "LENA_256x256_8bit.raw" ������ �б� ���� ����
	for (int i = 0; i < 256; i++) {
		fread(Readbuf[i], 1, 256, fp);   //	(������ �ּ�, ������ ũ��, ������ ����, ����������)
	}							    	 // ���Ͽ��� ������ �о�� Readbuf �迭�� ����
	fclose(fp); // ���� �ݱ�


	// ���� ����: ������ �������� ������ (Readbuf�� ���� ������ Writebuf�� ����)
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			Writebuf[j][i] = Readbuf[256 - j][i]; // �� �� ������
			//Writebuf[j][i] = Readbuf[j][256 - i]; // �� �� ������
			//Writebuf[j][i] = Readbuf[255 - j][255 - i]; // �����¿� ������


	// ���� ����
	fp = fopen("LENA_256x256_8bit_2_up_down222222.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	//fp = fopen("LENA_256x256_8bit_3_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	//fp = fopen("LENA_256x256_8bit_4_up_down_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	
	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
	fclose(fp); // ���� �ݱ�

	return 0; // ���α׷� ����
}
