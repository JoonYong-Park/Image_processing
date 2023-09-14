#include <stdio.h>

#pragma warning(disable:4996) // ��� �޽��� 4996�� �����ϴ� pragma ���ù�

int main() {

	FILE* fp; // ���� ������ ����

	unsigned char Readbuf[256][256]; // 256x256 ũ���� 8��Ʈ �迭 ����
	unsigned char Writebuf[256][256]; // 256x256 ũ���� 8��Ʈ �迭 ����

	// ���� �б�
	fp = fopen("LENA_256x256_8bit.raw", "rb"); // "LENA_256x256_8bit.raw" ������ �б� ���� ����
	for (int i = 0; i < 256; i++)
		fread(Readbuf[i], 1, 256, fp); // ���Ͽ��� ������ �о�� Readbuf �迭�� ����
	fclose(fp); // ���� �ݱ�

	// ���� ����: ������ �������� ������
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			Writebuf[j][i] = Readbuf[256 - j][256 - i]; // Readbuf�� ���� ������ Writebuf�� ����

	// ���� ����
	fp = fopen("LENA_256x256_8bit_up_down_left_right.raw", "wb"); // "LENA_256x256_8bit_new.raw" ������ ���� ���� ����
	for (int i = 0; i < 256; i++)
		fwrite(Writebuf[i], 1, 256, fp); // Writebuf �迭�� �����͸� ���Ͽ� ����
	fclose(fp); // ���� �ݱ�

	return 0; // ���α׷� ����
}
