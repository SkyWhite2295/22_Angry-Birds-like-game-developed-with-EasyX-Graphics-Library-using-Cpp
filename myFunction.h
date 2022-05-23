#pragma once

//�Զ���ṹ�壺�û���Ϣ
typedef struct info {
	char id[50];
	char passward[50];
	int score;
	int extra_HE;
	int extra_AP;
}info;

//�Զ���ṹ�壺Ŀ����Ϣ
typedef struct target {
	char img_Path[50];
	int img_x;
	int img_y;
	int mid_x;
	int mid_y;
	int isArmed;
}target;

//�Զ���ṹ�壺Ŀ������
typedef struct NODE
{
	target t;
	struct NODE* next;
}NODE;

//����û���Ϣ����
int checkInfo(info inputInfo) {

	char F_PATH[] = "./data.txt";
	FILE* fp;
	errno_t err;
	info temp;

	err = fopen_s(&fp, F_PATH, "r");

	if (err) {
		printf("fail to open file when checking");
		exit(0);
	}

	while (fread(&temp, sizeof(info), 1, fp)) {
		if (strcmp(inputInfo.id, temp.id) == 0) {
			if (strcmp(inputInfo.passward, temp.passward) == 0) {
				fclose(fp);
				return 1;																					//�˺Ŵ��ڣ�������ȷ������1
			}
			else
			{
				fclose(fp);
				return 0;																					//�˺Ŵ��ڣ�������󣬷���0
			}
		}
	}
	fclose(fp);
	return 2;																								//�˺Ų����ڣ�����2

}

//�����û���Ϣ����
info loadInfo(info inputInfo) {

	char F_PATH[] = "./data.txt";
	FILE* fp;
	errno_t err;
	info temp,record;

	err = fopen_s(&fp, F_PATH, "r");

	if (err) {
		printf("fail to open file when loading");
		exit(0);
	}

	while (fread(&temp, sizeof(info), 1, fp)) {
		if (strcmp(inputInfo.id, temp.id) == 0) {
			record = temp;		
		}
	}
	fclose(fp);
	return record;

}

//ע���û���Ϣ����
void setInfo(info inputInfo) {

	char F_PATH[] = "./data.txt";
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, F_PATH, "a+");

	if (err) {
		printf("fail to open file when setting");
		exit(0);
	}
	fwrite(&inputInfo, sizeof(info), 1, fp);

	fclose(fp);

}

//�浵����
void saveInfo(info inputInfo) {

	char F_PATH[] = "./data.txt";
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, F_PATH, "a+");

	if (err) {
		printf("fail to open file when setting");
		exit(0);
	}
	fwrite(&inputInfo, sizeof(info), 1, fp);

	fclose(fp);

}

//��ظ߶��ж�����
int toGround_1(double x,double y){

	if (x >= 0 && x < 560 || x>760 &&x<=1600) {
		return 610 - (int)y;
	}
	else if (x >= 560 && x <= 760) {
		return 450 - (int)y;
	}

}

int toGround_2(double x, double y) {

		return 610 - (int)y;

}

/*int toGround_3(double x, double y) {

	if (x >= 0 && x < 700) {
		return 610 - (int)y;
	}
	else if (x >= 700 && x < 800) {
		return -(int)x + 1300 - (int)y;
	}
	else if (x >= 800 && x < 1000) {
		return 400 - (int)y;
	}
	else if (x >= 1000 && x < 1050) {
		return (int)x - 500 - (int)y;
	}
	else if (x >= 1050 && x < 1200) {
		return 550 - (int)y;
	}
	else if (x >= 1200 && x <= 1600) {
		return 500 - (int)y;
	}

}
*/
//��ɱ�ж�����
/**/int isKilled(int targetArm, int shellType) {

	//srand((unsigned)time(NULL));
	int p;
	if (targetArm == 0 && shellType == 0) {
		p = rand() % 100 + 1;
		//printf("%d\n", p);
		if (p <= 90) {
			return 1;
		}
		else {
			return 0;
		}
	}

	if (targetArm == 0 && shellType == 1) {
			return 1;
	}

	if (targetArm == 1 && shellType == 0) {
		p = rand() % 100 + 1;
		//printf("%d\n", p);
		if (p <= 20) {
			return 1;
		}
		else {
			return 0;
		}
	}

	if (targetArm == 1 && shellType == 1) {
		p = rand() % 100 + 1;
		//printf("%d\n", p);
		if (p <= 70) {
			return 1;
		}
		else {
			return 0;
		}
	}

}

/*int isKilled(int targetArm, int shellType) {
	return 1;
}*/
//����pngͼƬ��������������
void drawAlpha( int  picture_x, int picture_y,IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//����
int height() {
	static int h = 720;
	return h;
}

int width() {
	static int w = 1600;
	return w;
}

double PI() {
	static double pi=3.14159;
	return pi;
}

/*int name(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}*/
//����

//ҳ����ת
int page(int toPage, int isChange) {
	static int p;
	if (isChange) {
		p = toPage;
	}
	else {
		return p;
	}
}

//�ж��ڵ��Ƿ��ڷ���״̬
int isFlying(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ж��ڵ��Ƿ�����
int isHit(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isHit_show(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//��¼�ڵ�����
int HE_num(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int AP_num(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//��¼�ڵ�����
int shell_Type(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ڵ��ٶ�
double shell_v(double new_data, int isChange) {
	static double a=5;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ڵ�����
double shell_x(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
double shell_y(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ڵ��Ƕ�
double angle(double new_data, int isChange) {
	static double a=40.0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ڵ��������
double hit_x(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
double hit_y(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//�ڵ�xy�����ٶȷ���
double shell_vx(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
double shell_vy(double new_data, int isChange) {
	static double a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

int isPass1_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass1_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass1_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass2_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass2_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass2_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass3_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass3_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isPass3_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

int isFailed1_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed1_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed1_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed2_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed2_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed2_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed3_1(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed3_2(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
int isFailed3_3(int new_data, int isChange) {
	static int a;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}
