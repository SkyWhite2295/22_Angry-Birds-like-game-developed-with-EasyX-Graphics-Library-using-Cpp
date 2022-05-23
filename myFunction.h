#pragma once

//自定义结构体：用户信息
typedef struct info {
	char id[50];
	char passward[50];
	int score;
	int extra_HE;
	int extra_AP;
}info;

//自定义结构体：目标信息
typedef struct target {
	char img_Path[50];
	int img_x;
	int img_y;
	int mid_x;
	int mid_y;
	int isArmed;
}target;

//自定义结构体：目标链表
typedef struct NODE
{
	target t;
	struct NODE* next;
}NODE;

//检查用户信息函数
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
				return 1;																					//账号存在，密码正确，返回1
			}
			else
			{
				fclose(fp);
				return 0;																					//账号存在，密码错误，返回0
			}
		}
	}
	fclose(fp);
	return 2;																								//账号不存在，返回2

}

//加载用户信息函数
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

//注册用户信息函数
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

//存档函数
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

//离地高度判定函数
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
//击杀判定函数
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
//置入png图片函数，来自网络
void drawAlpha( int  picture_x, int picture_y,IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//常量
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
//变量

//页面跳转
int page(int toPage, int isChange) {
	static int p;
	if (isChange) {
		p = toPage;
	}
	else {
		return p;
	}
}

//判定炮弹是否处于飞行状态
int isFlying(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//判定炮弹是否被引爆
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

//记录炮弹数量
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

//记录炮弹种类
int shell_Type(int new_data, int isChange) {
	static int a=0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//炮弹速度
double shell_v(double new_data, int isChange) {
	static double a=5;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//炮弹坐标
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

//炮弹角度
double angle(double new_data, int isChange) {
	static double a=40.0;
	if (isChange) {
		a = new_data;
	}
	else {
		return a;
	}
}

//炮弹落点坐标
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

//炮弹xy方向速度分量
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
