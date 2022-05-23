#include "project_include.h"
#include "myFunction.h"

MOUSEMSG m;																//鼠标信号
NODE* h = nullptr, * s = nullptr,*p=nullptr,*r=nullptr;	//用于处理目标链表																												
clock_t start_t, end_t;														//时间点
info player;																		//用户信息

int login() ;
void homePage();
void shopPage();
void gameend();
void gameexit();

void startup1_1();
void show1_1();
void updateWithoutInput1_1();
void updateWithInput1_1();
void game1_1();

void startup1_2();
void show1_2();
void updateWithoutInput1_2();
void updateWithInput1_2();
void game1_2();

void startup1_3();
void show1_3();
void updateWithoutInput1_3();
void updateWithInput1_3();
void game1_3();

void startup2_1();
void show2_1();
void updateWithoutInput2_1();
void updateWithInput2_1();
void game2_1();

void startup2_2();
void show2_2();
void updateWithoutInput2_2();
void updateWithInput2_2();
void game2_2();

void startup2_3();
void show2_3();
void updateWithoutInput2_3();
void updateWithInput2_3();
void game2_3();

void startup3_1();
void show3_1();
void updateWithoutInput3_1();
void updateWithInput3_1();
void game3_1();

void startup3_2();
void show3_2();
void updateWithoutInput3_2();
void updateWithInput3_2();
void game3_2();

void startup3_3();
void show3_3();
void updateWithoutInput3_3();
void updateWithInput3_3();
void game3_3();

//主函数
int main() {
	mciSendString(_T("open ./music/bf_home.mp3 alias homeBKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/bf_main.mp3 alias mainBKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/bf_3_1.mp3 alias 3_1BKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/bf_3_2.mp3 alias 3_2BKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/bf_3_3.mp3 alias 3_3BKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/bf_end.mp3 alias endBKmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);

	mciSendString(_T("play homeBKmusic repeat"), NULL, 0, NULL);
	if (login()) {													//登录
		page(10, 1);
	}
	while (1) {
		if (page(0, 0) == 10) {
			mciSendString(_T("stop mainBKmusic"), NULL, 0, NULL);
			mciSendString(_T("stop endBKmusic"), NULL, 0, NULL);
			mciSendString(_T("play homeBKmusic repeat"), NULL, 0, NULL);			
			homePage();
		}
		else if (page(0, 0) == 11) {
			mciSendString(_T("play homeBKmusic repeat"), NULL, 0, NULL);
			shopPage();
		}
		else if (page(0, 0) == 1) {
			mciSendString(_T("stop homeBKmusic"), NULL, 0, NULL);
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game1_1();
		}
		else if (page(0, 0) == 2) {
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game1_2();
		}
		else if (page(0, 0) == 3) {
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game1_3();
		}
		else if (page(0, 0) == 4) {
			mciSendString(_T("stop homeBKmusic"), NULL, 0, NULL);
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game2_1();
		}
		else if (page(0, 0) == 5) {
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game2_2();
		}
		else if (page(0, 0) == 6) {
			mciSendString(_T("play mainBKmusic repeat"), NULL, 0, NULL);
			game2_3();
		}
		else if (page(0, 0) == 7) {
			mciSendString(_T("stop homeBKmusic"), NULL, 0, NULL);
			mciSendString(_T("play 3_1BKmusic repeat"), NULL, 0, NULL);
			game3_1();
		}
		else if (page(0, 0) == 8) {
			mciSendString(_T("stop 3_1BKmusic"), NULL, 0, NULL);
			mciSendString(_T("play 3_2BKmusic repeat"), NULL, 0, NULL);
			game3_2();
		}
		else if (page(0, 0) == 9) {
			mciSendString(_T("stop 3_2BKmusic"), NULL, 0, NULL);
			mciSendString(_T("play 3_3BKmusic repeat"), NULL, 0, NULL);
			game3_3();
		}
		else if (page(0, 0) == 12) {
			mciSendString(_T("stop 3_3BKmusic"), NULL, 0, NULL);
			mciSendString(_T("play endBKmusic repeat"), NULL, 0, NULL);
			gameend();
		}
		Sleep(1000);
	}

	return 0;
}

//登录																		
int login() {

	char inputID[50];											//存储输入的数据
	char inputPassword[50];
	char outputPassword[50];
	char temp;
	info input;
	int i = 0, j = 0;												//循环变量

	inputID[0] = '\0';
	inputPassword[0] = '\0';
	outputPassword[0] = '\0';

	initgraph(800, 600);											//加载登录背景图

	setbkcolor(WHITE);
	cleardevice();
	IMAGE img_lgnBk;
	loadimage(&img_lgnBk, _T("./image/background/loginPage.png"), 0, 0, true);
	putimage(0, 0, &img_lgnBk);
	settextstyle(30, 0, _T("simhei"));

	while (1) {																												//登录操作
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				setcolor(BLACK);
				//rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
				if (m.x >= 200 && m.x <= 600 && m.y >= 300 && m.y <= 350) {		//账号
					outtextxy(210, 310, '|');
					while ((temp = _getch()) != '\r') {
						if ((int)temp != 8) {
							inputID[i] = temp;
							inputID[i + 1] = '\0';
							i++;
						}
						else {
							if (i > 0) {
								i--;
								inputID[i] = '\0';
							}
						}
						putimage(0, 0, &img_lgnBk);
						outtextxy(210, 310, CString(inputID));
						outtextxy(210, 360, CString(outputPassword));
						puts(inputID);
					}
					continue;
				}
				if (m.x >= 200 && m.x <= 600 && m.y >= 350 && m.y <= 400) {		//密码
					outtextxy(210, 360, '|');
					while ((temp = _getch()) != '\r') {
						if ((int)temp != 8) {
							inputPassword[j] = temp;
							outputPassword[j] = '*';
							inputPassword[j + 1] = '\0';
							outputPassword[j + 1] = '\0';
							j++;
						}
						else {
							if (j > 0) {
								j--;
								inputPassword[j] = '\0';
								outputPassword[j] = '\0';
							}
						}
						putimage(0, 0, &img_lgnBk);
						outtextxy(210, 310, CString(inputID));
						outtextxy(210, 360, CString(outputPassword));
						puts(inputPassword);
					}
					continue;
				}
				if (m.x >= 200 && m.x <= 400 && m.y >= 400 && m.y <= 450) {		//快捷通道
					strcpy_s(player.id, "administrator");
					strcpy_s(player.passward, "administrator");
					player.score = 999999;
					player.extra_HE = 999;
					player.extra_AP = 999;
					return 1;
					closegraph();
					break;
				}
				if (m.x >= 400 && m.x <= 600 && m.y >= 400 && m.y <= 450) {		//登录
					puts(inputID);
					puts(inputPassword);
					if (strlen(inputID) == 0 || strlen(inputPassword) == 0) {
						inputID[0] = '\0';
						inputPassword[0] = '\0';
						i = 0;
						j = 0;
						continue;
					}
					strcpy_s(input.id, inputID);
					strcpy_s(input.passward, inputPassword);
					switch (checkInfo(input))
					{
					case 1:																								//账号存在，密码正确，关闭登录界面，开始
						player = loadInfo(input);
						return 1;
						closegraph();
						break;
					case 2:																								//账号不存在，添加账户，关闭登录界面，开始
						input.score = 200;
						input.extra_AP = 10;
						input.extra_HE = 10;
						setInfo(input);
						player = input;
						return 1;
						closegraph();
						break;
					case 0:																								//账号存在，密码错误，清除数据，重新输入
						inputID[0] = '\0';
						inputPassword[0] = '\0';
						i = 0;
						j = 0;
						break;
					default:
						break;
					}
					continue;
				}
			}
		}
	}
	closegraph();
}
//主界面
void homePage() {
	initgraph(1000, 750);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img_homeBk;
	loadimage(&img_homeBk, _T("./image/background/homePage.png"), 0, 0, true);

	BeginBatchDraw();
	while (1) {
		putimage(0, 0, &img_homeBk);
		static char score_char[30];
		static char HE_char[30];
		static char AP_char[30];
		sprintf_s(score_char, "%d", player.score);
		sprintf_s(HE_char, "%d", player.extra_HE);
		sprintf_s(AP_char, "%d", player.extra_AP);

		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("simhei"));
		outtextxy(780, 60, CString(player.id));
		outtextxy(840, 110, CString(score_char));
		outtextxy(840, 160, CString(HE_char));
		outtextxy(840, 205, CString(AP_char));

		FlushBatchDraw();
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 680 && m.x <= 1000 && m.y >= 520 && m.y <= 750) {
					page(11, 1);
					setbkcolor(BLACK);
					cleardevice();
					EndBatchDraw();
					return;
				}
				if (m.x >= 427 && m.x <= 596 && m.y >= 238 && m.y <= 273) {
					page(1, 1);
					setbkcolor(BLACK);
					cleardevice();
					EndBatchDraw();
					return;
				}
				if (m.x >= 467 && m.x <= 672 && m.y >= 312 && m.y <= 348) {
					page(4, 1);
					setbkcolor(BLACK);
					cleardevice();
					EndBatchDraw();
					return;
				}
				if (m.x >= 240 && m.x <= 411 && m.y >= 201 && m.y <= 237) {
					page(7, 1);
					setbkcolor(BLACK);
					cleardevice();
					EndBatchDraw();
					return;
				}
				if (m.x >= 780 && m.x <= 968 && m.y >= 296 && m.y <= 330) {
					gameexit();
				}
			}
		}
	}
}
//商店
void shopPage() {
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img_shopBk;
	loadimage(&img_shopBk, _T("./image/background/shopPage.png"), 0, 0, true);
	
	BeginBatchDraw();
	while (1) {
		putimage(0, 0, &img_shopBk);
		static char score_char[30];
		static char HE_char[30];
		static char AP_char[30];
		sprintf_s(score_char, "%d", player.score);
		sprintf_s(HE_char, "%d", player.extra_HE);
		sprintf_s(AP_char, "%d", player.extra_AP);

		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30, 0, _T("simhei"));
		outtextxy(780, 60, CString(player.id));
		outtextxy(840, 110, CString(score_char));
		outtextxy(840, 160, CString(HE_char));
		outtextxy(840, 205, CString(AP_char));

		FlushBatchDraw();
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 10 && m.x <= 170 && m.y >= 460 && m.y <= 610) {
					player.extra_HE++;
					player.score -= 1;
					break;
				}
				if (m.x >= 265 && m.x <= 420 && m.y >= 460 && m.y <= 610) {
					player.extra_AP++;
					player.score -= 2;
					break;
				}
				if (m.x >= 778 && m.x <= 967 && m.y >= 250 && m.y <= 285) {
					saveInfo(player);
					break;
				}
				if (m.x >= 778 && m.x <= 967 && m.y >= 295 && m.y <= 333) {
					page(10, 1);
					setbkcolor(BLACK);
					cleardevice();
					EndBatchDraw();
					return;
				}
			}
		}
	}
}

//结束动画
void gameend() {		
	initgraph(1280, 660);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(200, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("loading"));

	IMAGE video[1331],end;
	loadimage(&end, _T("./image/background/end.jpg"));
	loadimage(&video[0], _T("./image/video/victory (1).jpg"));
	loadimage(&video[1], _T("./image/video/victory (2).jpg"));
	loadimage(&video[2], _T("./image/video/victory (3).jpg"));
	loadimage(&video[3], _T("./image/video/victory (4).jpg"));
	loadimage(&video[4], _T("./image/video/victory (5).jpg"));
	loadimage(&video[5], _T("./image/video/victory (6).jpg"));
	loadimage(&video[6], _T("./image/video/victory (7).jpg"));
	loadimage(&video[7], _T("./image/video/victory (8).jpg"));
	loadimage(&video[8], _T("./image/video/victory (9).jpg"));
	loadimage(&video[9], _T("./image/video/victory (10).jpg"));
	loadimage(&video[10], _T("./image/video/victory (11).jpg"));
	loadimage(&video[11], _T("./image/video/victory (12).jpg"));
	loadimage(&video[12], _T("./image/video/victory (13).jpg"));
	loadimage(&video[13], _T("./image/video/victory (14).jpg"));
	loadimage(&video[14], _T("./image/video/victory (15).jpg"));
	loadimage(&video[15], _T("./image/video/victory (16).jpg"));
	loadimage(&video[16], _T("./image/video/victory (17).jpg"));
	loadimage(&video[17], _T("./image/video/victory (18).jpg"));
	loadimage(&video[18], _T("./image/video/victory (19).jpg"));
	loadimage(&video[19], _T("./image/video/victory (20).jpg"));
	loadimage(&video[20], _T("./image/video/victory (21).jpg"));
	loadimage(&video[21], _T("./image/video/victory (22).jpg"));
	loadimage(&video[22], _T("./image/video/victory (23).jpg"));
	loadimage(&video[23], _T("./image/video/victory (24).jpg"));
	loadimage(&video[24], _T("./image/video/victory (25).jpg"));
	loadimage(&video[25], _T("./image/video/victory (26).jpg"));
	loadimage(&video[26], _T("./image/video/victory (27).jpg"));
	loadimage(&video[27], _T("./image/video/victory (28).jpg"));
	loadimage(&video[28], _T("./image/video/victory (29).jpg"));
	loadimage(&video[29], _T("./image/video/victory (30).jpg"));
	loadimage(&video[30], _T("./image/video/victory (31).jpg"));
	loadimage(&video[31], _T("./image/video/victory (32).jpg"));
	loadimage(&video[32], _T("./image/video/victory (33).jpg"));
	loadimage(&video[33], _T("./image/video/victory (34).jpg"));
	loadimage(&video[34], _T("./image/video/victory (35).jpg"));
	loadimage(&video[35], _T("./image/video/victory (36).jpg"));
	loadimage(&video[36], _T("./image/video/victory (37).jpg"));
	loadimage(&video[37], _T("./image/video/victory (38).jpg"));
	loadimage(&video[38], _T("./image/video/victory (39).jpg"));
	loadimage(&video[39], _T("./image/video/victory (40).jpg"));
	loadimage(&video[40], _T("./image/video/victory (41).jpg"));
	loadimage(&video[41], _T("./image/video/victory (42).jpg"));
	loadimage(&video[42], _T("./image/video/victory (43).jpg"));
	loadimage(&video[43], _T("./image/video/victory (44).jpg"));
	loadimage(&video[44], _T("./image/video/victory (45).jpg"));
	loadimage(&video[45], _T("./image/video/victory (46).jpg"));
	loadimage(&video[46], _T("./image/video/victory (47).jpg"));
	loadimage(&video[47], _T("./image/video/victory (48).jpg"));
	loadimage(&video[48], _T("./image/video/victory (49).jpg"));
	loadimage(&video[49], _T("./image/video/victory (50).jpg"));
	loadimage(&video[50], _T("./image/video/victory (51).jpg"));
	loadimage(&video[51], _T("./image/video/victory (52).jpg"));
	loadimage(&video[52], _T("./image/video/victory (53).jpg"));
	loadimage(&video[53], _T("./image/video/victory (54).jpg"));
	loadimage(&video[54], _T("./image/video/victory (55).jpg"));
	loadimage(&video[55], _T("./image/video/victory (56).jpg"));
	loadimage(&video[56], _T("./image/video/victory (57).jpg"));
	loadimage(&video[57], _T("./image/video/victory (58).jpg"));
	loadimage(&video[58], _T("./image/video/victory (59).jpg"));
	loadimage(&video[59], _T("./image/video/victory (60).jpg"));
	loadimage(&video[60], _T("./image/video/victory (61).jpg"));
	loadimage(&video[61], _T("./image/video/victory (62).jpg"));
	loadimage(&video[62], _T("./image/video/victory (63).jpg"));
	loadimage(&video[63], _T("./image/video/victory (64).jpg"));
	loadimage(&video[64], _T("./image/video/victory (65).jpg"));
	loadimage(&video[65], _T("./image/video/victory (66).jpg"));
	loadimage(&video[66], _T("./image/video/victory (67).jpg"));
	loadimage(&video[67], _T("./image/video/victory (68).jpg"));
	loadimage(&video[68], _T("./image/video/victory (69).jpg"));
	loadimage(&video[69], _T("./image/video/victory (70).jpg"));
	loadimage(&video[70], _T("./image/video/victory (71).jpg"));
	loadimage(&video[71], _T("./image/video/victory (72).jpg"));
	loadimage(&video[72], _T("./image/video/victory (73).jpg"));
	loadimage(&video[73], _T("./image/video/victory (74).jpg"));
	loadimage(&video[74], _T("./image/video/victory (75).jpg"));
	loadimage(&video[75], _T("./image/video/victory (76).jpg"));
	loadimage(&video[76], _T("./image/video/victory (77).jpg"));
	loadimage(&video[77], _T("./image/video/victory (78).jpg"));
	loadimage(&video[78], _T("./image/video/victory (79).jpg"));
	loadimage(&video[79], _T("./image/video/victory (80).jpg"));
	loadimage(&video[80], _T("./image/video/victory (81).jpg"));
	loadimage(&video[81], _T("./image/video/victory (82).jpg"));
	loadimage(&video[82], _T("./image/video/victory (83).jpg"));
	loadimage(&video[83], _T("./image/video/victory (84).jpg"));
	loadimage(&video[84], _T("./image/video/victory (85).jpg"));
	loadimage(&video[85], _T("./image/video/victory (86).jpg"));
	loadimage(&video[86], _T("./image/video/victory (87).jpg"));
	loadimage(&video[87], _T("./image/video/victory (88).jpg"));
	loadimage(&video[88], _T("./image/video/victory (89).jpg"));
	loadimage(&video[89], _T("./image/video/victory (90).jpg"));
	loadimage(&video[90], _T("./image/video/victory (91).jpg"));
	loadimage(&video[91], _T("./image/video/victory (92).jpg"));
	loadimage(&video[92], _T("./image/video/victory (93).jpg"));
	loadimage(&video[93], _T("./image/video/victory (94).jpg"));
	loadimage(&video[94], _T("./image/video/victory (95).jpg"));
	loadimage(&video[95], _T("./image/video/victory (96).jpg"));
	loadimage(&video[96], _T("./image/video/victory (97).jpg"));
	loadimage(&video[97], _T("./image/video/victory (98).jpg"));
	loadimage(&video[98], _T("./image/video/victory (99).jpg"));
	loadimage(&video[99], _T("./image/video/victory (100).jpg"));
	loadimage(&video[100], _T("./image/video/victory (101).jpg"));
	loadimage(&video[101], _T("./image/video/victory (102).jpg"));
	loadimage(&video[102], _T("./image/video/victory (103).jpg"));
	loadimage(&video[103], _T("./image/video/victory (104).jpg"));
	loadimage(&video[104], _T("./image/video/victory (105).jpg"));
	loadimage(&video[105], _T("./image/video/victory (106).jpg"));
	loadimage(&video[106], _T("./image/video/victory (107).jpg"));
	loadimage(&video[107], _T("./image/video/victory (108).jpg"));
	loadimage(&video[108], _T("./image/video/victory (109).jpg"));
	loadimage(&video[109], _T("./image/video/victory (110).jpg"));
	loadimage(&video[110], _T("./image/video/victory (111).jpg"));
	loadimage(&video[111], _T("./image/video/victory (112).jpg"));
	loadimage(&video[112], _T("./image/video/victory (113).jpg"));
	loadimage(&video[113], _T("./image/video/victory (114).jpg"));
	loadimage(&video[114], _T("./image/video/victory (115).jpg"));
	loadimage(&video[115], _T("./image/video/victory (116).jpg"));
	loadimage(&video[116], _T("./image/video/victory (117).jpg"));
	loadimage(&video[117], _T("./image/video/victory (118).jpg"));
	loadimage(&video[118], _T("./image/video/victory (119).jpg"));
	loadimage(&video[119], _T("./image/video/victory (120).jpg"));
	loadimage(&video[120], _T("./image/video/victory (121).jpg"));
	loadimage(&video[121], _T("./image/video/victory (122).jpg"));
	loadimage(&video[122], _T("./image/video/victory (123).jpg"));
	loadimage(&video[123], _T("./image/video/victory (124).jpg"));
	loadimage(&video[124], _T("./image/video/victory (125).jpg"));
	loadimage(&video[125], _T("./image/video/victory (126).jpg"));
	loadimage(&video[126], _T("./image/video/victory (127).jpg"));
	loadimage(&video[127], _T("./image/video/victory (128).jpg"));
	loadimage(&video[128], _T("./image/video/victory (129).jpg"));
	loadimage(&video[129], _T("./image/video/victory (130).jpg"));
	loadimage(&video[130], _T("./image/video/victory (131).jpg"));
	loadimage(&video[131], _T("./image/video/victory (132).jpg"));
	loadimage(&video[132], _T("./image/video/victory (133).jpg"));
	loadimage(&video[133], _T("./image/video/victory (134).jpg"));
	loadimage(&video[134], _T("./image/video/victory (135).jpg"));
	loadimage(&video[135], _T("./image/video/victory (136).jpg"));
	loadimage(&video[136], _T("./image/video/victory (137).jpg"));
	loadimage(&video[137], _T("./image/video/victory (138).jpg"));
	loadimage(&video[138], _T("./image/video/victory (139).jpg"));
	loadimage(&video[139], _T("./image/video/victory (140).jpg"));
	loadimage(&video[140], _T("./image/video/victory (141).jpg"));
	loadimage(&video[141], _T("./image/video/victory (142).jpg"));
	loadimage(&video[142], _T("./image/video/victory (143).jpg"));
	loadimage(&video[143], _T("./image/video/victory (144).jpg"));
	loadimage(&video[144], _T("./image/video/victory (145).jpg"));
	loadimage(&video[145], _T("./image/video/victory (146).jpg"));
	loadimage(&video[146], _T("./image/video/victory (147).jpg"));
	loadimage(&video[147], _T("./image/video/victory (148).jpg"));
	loadimage(&video[148], _T("./image/video/victory (149).jpg"));
	loadimage(&video[149], _T("./image/video/victory (150).jpg"));
	loadimage(&video[150], _T("./image/video/victory (151).jpg"));
	loadimage(&video[151], _T("./image/video/victory (152).jpg"));
	loadimage(&video[152], _T("./image/video/victory (153).jpg"));
	loadimage(&video[153], _T("./image/video/victory (154).jpg"));
	loadimage(&video[154], _T("./image/video/victory (155).jpg"));
	loadimage(&video[155], _T("./image/video/victory (156).jpg"));
	loadimage(&video[156], _T("./image/video/victory (157).jpg"));
	loadimage(&video[157], _T("./image/video/victory (158).jpg"));
	loadimage(&video[158], _T("./image/video/victory (159).jpg"));
	loadimage(&video[159], _T("./image/video/victory (160).jpg"));
	loadimage(&video[160], _T("./image/video/victory (161).jpg"));
	loadimage(&video[161], _T("./image/video/victory (162).jpg"));
	loadimage(&video[162], _T("./image/video/victory (163).jpg"));
	loadimage(&video[163], _T("./image/video/victory (164).jpg"));
	loadimage(&video[164], _T("./image/video/victory (165).jpg"));
	loadimage(&video[165], _T("./image/video/victory (166).jpg"));
	loadimage(&video[166], _T("./image/video/victory (167).jpg"));
	loadimage(&video[167], _T("./image/video/victory (168).jpg"));
	loadimage(&video[168], _T("./image/video/victory (169).jpg"));
	loadimage(&video[169], _T("./image/video/victory (170).jpg"));
	loadimage(&video[170], _T("./image/video/victory (171).jpg"));
	loadimage(&video[171], _T("./image/video/victory (172).jpg"));
	loadimage(&video[172], _T("./image/video/victory (173).jpg"));
	loadimage(&video[173], _T("./image/video/victory (174).jpg"));
	loadimage(&video[174], _T("./image/video/victory (175).jpg"));
	loadimage(&video[175], _T("./image/video/victory (176).jpg"));
	loadimage(&video[176], _T("./image/video/victory (177).jpg"));
	loadimage(&video[177], _T("./image/video/victory (178).jpg"));
	loadimage(&video[178], _T("./image/video/victory (179).jpg"));
	loadimage(&video[179], _T("./image/video/victory (180).jpg"));
	loadimage(&video[180], _T("./image/video/victory (181).jpg"));
	loadimage(&video[181], _T("./image/video/victory (182).jpg"));
	loadimage(&video[182], _T("./image/video/victory (183).jpg"));
	loadimage(&video[183], _T("./image/video/victory (184).jpg"));
	loadimage(&video[184], _T("./image/video/victory (185).jpg"));
	loadimage(&video[185], _T("./image/video/victory (186).jpg"));
	loadimage(&video[186], _T("./image/video/victory (187).jpg"));
	loadimage(&video[187], _T("./image/video/victory (188).jpg"));
	loadimage(&video[188], _T("./image/video/victory (189).jpg"));
	loadimage(&video[189], _T("./image/video/victory (190).jpg"));
	loadimage(&video[190], _T("./image/video/victory (191).jpg"));
	loadimage(&video[191], _T("./image/video/victory (192).jpg"));
	loadimage(&video[192], _T("./image/video/victory (193).jpg"));
	loadimage(&video[193], _T("./image/video/victory (194).jpg"));
	loadimage(&video[194], _T("./image/video/victory (195).jpg"));
	loadimage(&video[195], _T("./image/video/victory (196).jpg"));
	loadimage(&video[196], _T("./image/video/victory (197).jpg"));
	loadimage(&video[197], _T("./image/video/victory (198).jpg"));
	loadimage(&video[198], _T("./image/video/victory (199).jpg"));
	loadimage(&video[199], _T("./image/video/victory (200).jpg"));
	loadimage(&video[200], _T("./image/video/victory (201).jpg"));
	loadimage(&video[201], _T("./image/video/victory (202).jpg"));
	loadimage(&video[202], _T("./image/video/victory (203).jpg"));
	loadimage(&video[203], _T("./image/video/victory (204).jpg"));
	loadimage(&video[204], _T("./image/video/victory (205).jpg"));
	loadimage(&video[205], _T("./image/video/victory (206).jpg"));
	loadimage(&video[206], _T("./image/video/victory (207).jpg"));
	loadimage(&video[207], _T("./image/video/victory (208).jpg"));
	loadimage(&video[208], _T("./image/video/victory (209).jpg"));
	loadimage(&video[209], _T("./image/video/victory (210).jpg"));
	loadimage(&video[210], _T("./image/video/victory (211).jpg"));
	loadimage(&video[211], _T("./image/video/victory (212).jpg"));
	loadimage(&video[212], _T("./image/video/victory (213).jpg"));
	loadimage(&video[213], _T("./image/video/victory (214).jpg"));
	loadimage(&video[214], _T("./image/video/victory (215).jpg"));
	loadimage(&video[215], _T("./image/video/victory (216).jpg"));
	loadimage(&video[216], _T("./image/video/victory (217).jpg"));
	loadimage(&video[217], _T("./image/video/victory (218).jpg"));
	loadimage(&video[218], _T("./image/video/victory (219).jpg"));
	loadimage(&video[219], _T("./image/video/victory (220).jpg"));
	loadimage(&video[220], _T("./image/video/victory (221).jpg"));
	loadimage(&video[221], _T("./image/video/victory (222).jpg"));
	loadimage(&video[222], _T("./image/video/victory (223).jpg"));
	loadimage(&video[223], _T("./image/video/victory (224).jpg"));
	loadimage(&video[224], _T("./image/video/victory (225).jpg"));
	loadimage(&video[225], _T("./image/video/victory (226).jpg"));
	loadimage(&video[226], _T("./image/video/victory (227).jpg"));
	loadimage(&video[227], _T("./image/video/victory (228).jpg"));
	loadimage(&video[228], _T("./image/video/victory (229).jpg"));
	loadimage(&video[229], _T("./image/video/victory (230).jpg"));
	loadimage(&video[230], _T("./image/video/victory (231).jpg"));
	loadimage(&video[231], _T("./image/video/victory (232).jpg"));
	loadimage(&video[232], _T("./image/video/victory (233).jpg"));
	loadimage(&video[233], _T("./image/video/victory (234).jpg"));
	loadimage(&video[234], _T("./image/video/victory (235).jpg"));
	loadimage(&video[235], _T("./image/video/victory (236).jpg"));
	loadimage(&video[236], _T("./image/video/victory (237).jpg"));
	loadimage(&video[237], _T("./image/video/victory (238).jpg"));
	loadimage(&video[238], _T("./image/video/victory (239).jpg"));
	loadimage(&video[239], _T("./image/video/victory (240).jpg"));
	loadimage(&video[240], _T("./image/video/victory (241).jpg"));
	loadimage(&video[241], _T("./image/video/victory (242).jpg"));
	loadimage(&video[242], _T("./image/video/victory (243).jpg"));
	loadimage(&video[243], _T("./image/video/victory (244).jpg"));
	loadimage(&video[244], _T("./image/video/victory (245).jpg"));
	loadimage(&video[245], _T("./image/video/victory (246).jpg"));
	loadimage(&video[246], _T("./image/video/victory (247).jpg"));
	loadimage(&video[247], _T("./image/video/victory (248).jpg"));
	loadimage(&video[248], _T("./image/video/victory (249).jpg"));
	loadimage(&video[249], _T("./image/video/victory (250).jpg"));
	loadimage(&video[250], _T("./image/video/victory (251).jpg"));
	loadimage(&video[251], _T("./image/video/victory (252).jpg"));
	loadimage(&video[252], _T("./image/video/victory (253).jpg"));
	loadimage(&video[253], _T("./image/video/victory (254).jpg"));
	loadimage(&video[254], _T("./image/video/victory (255).jpg"));
	loadimage(&video[255], _T("./image/video/victory (256).jpg"));
	loadimage(&video[256], _T("./image/video/victory (257).jpg"));
	loadimage(&video[257], _T("./image/video/victory (258).jpg"));
	loadimage(&video[258], _T("./image/video/victory (259).jpg"));
	loadimage(&video[259], _T("./image/video/victory (260).jpg"));
	loadimage(&video[260], _T("./image/video/victory (261).jpg"));
	loadimage(&video[261], _T("./image/video/victory (262).jpg"));
	loadimage(&video[262], _T("./image/video/victory (263).jpg"));
	loadimage(&video[263], _T("./image/video/victory (264).jpg"));
	loadimage(&video[264], _T("./image/video/victory (265).jpg"));
	loadimage(&video[265], _T("./image/video/victory (266).jpg"));
	loadimage(&video[266], _T("./image/video/victory (267).jpg"));
	loadimage(&video[267], _T("./image/video/victory (268).jpg"));
	loadimage(&video[268], _T("./image/video/victory (269).jpg"));
	loadimage(&video[269], _T("./image/video/victory (270).jpg"));
	loadimage(&video[270], _T("./image/video/victory (271).jpg"));
	loadimage(&video[271], _T("./image/video/victory (272).jpg"));
	loadimage(&video[272], _T("./image/video/victory (273).jpg"));
	loadimage(&video[273], _T("./image/video/victory (274).jpg"));
	loadimage(&video[274], _T("./image/video/victory (275).jpg"));
	loadimage(&video[275], _T("./image/video/victory (276).jpg"));
	loadimage(&video[276], _T("./image/video/victory (277).jpg"));
	loadimage(&video[277], _T("./image/video/victory (278).jpg"));
	loadimage(&video[278], _T("./image/video/victory (279).jpg"));
	loadimage(&video[279], _T("./image/video/victory (280).jpg"));
	loadimage(&video[280], _T("./image/video/victory (281).jpg"));
	loadimage(&video[281], _T("./image/video/victory (282).jpg"));
	loadimage(&video[282], _T("./image/video/victory (283).jpg"));
	loadimage(&video[283], _T("./image/video/victory (284).jpg"));
	loadimage(&video[284], _T("./image/video/victory (285).jpg"));
	loadimage(&video[285], _T("./image/video/victory (286).jpg"));
	loadimage(&video[286], _T("./image/video/victory (287).jpg"));
	loadimage(&video[287], _T("./image/video/victory (288).jpg"));
	loadimage(&video[288], _T("./image/video/victory (289).jpg"));
	loadimage(&video[289], _T("./image/video/victory (290).jpg"));
	loadimage(&video[290], _T("./image/video/victory (291).jpg"));
	loadimage(&video[291], _T("./image/video/victory (292).jpg"));
	loadimage(&video[292], _T("./image/video/victory (293).jpg"));
	loadimage(&video[293], _T("./image/video/victory (294).jpg"));
	loadimage(&video[294], _T("./image/video/victory (295).jpg"));
	loadimage(&video[295], _T("./image/video/victory (296).jpg"));
	loadimage(&video[296], _T("./image/video/victory (297).jpg"));
	loadimage(&video[297], _T("./image/video/victory (298).jpg"));
	loadimage(&video[298], _T("./image/video/victory (299).jpg"));
	loadimage(&video[299], _T("./image/video/victory (300).jpg"));
	loadimage(&video[300], _T("./image/video/victory (301).jpg"));
	loadimage(&video[301], _T("./image/video/victory (302).jpg"));
	loadimage(&video[302], _T("./image/video/victory (303).jpg"));
	loadimage(&video[303], _T("./image/video/victory (304).jpg"));
	loadimage(&video[304], _T("./image/video/victory (305).jpg"));
	loadimage(&video[305], _T("./image/video/victory (306).jpg"));
	loadimage(&video[306], _T("./image/video/victory (307).jpg"));
	loadimage(&video[307], _T("./image/video/victory (308).jpg"));
	loadimage(&video[308], _T("./image/video/victory (309).jpg"));
	loadimage(&video[309], _T("./image/video/victory (310).jpg"));
	loadimage(&video[310], _T("./image/video/victory (311).jpg"));
	loadimage(&video[311], _T("./image/video/victory (312).jpg"));
	loadimage(&video[312], _T("./image/video/victory (313).jpg"));
	loadimage(&video[313], _T("./image/video/victory (314).jpg"));
	loadimage(&video[314], _T("./image/video/victory (315).jpg"));
	loadimage(&video[315], _T("./image/video/victory (316).jpg"));
	loadimage(&video[316], _T("./image/video/victory (317).jpg"));
	loadimage(&video[317], _T("./image/video/victory (318).jpg"));
	loadimage(&video[318], _T("./image/video/victory (319).jpg"));
	loadimage(&video[319], _T("./image/video/victory (320).jpg"));
	loadimage(&video[320], _T("./image/video/victory (321).jpg"));
	loadimage(&video[321], _T("./image/video/victory (322).jpg"));
	loadimage(&video[322], _T("./image/video/victory (323).jpg"));
	loadimage(&video[323], _T("./image/video/victory (324).jpg"));
	loadimage(&video[324], _T("./image/video/victory (325).jpg"));
	loadimage(&video[325], _T("./image/video/victory (326).jpg"));
	loadimage(&video[326], _T("./image/video/victory (327).jpg"));
	loadimage(&video[327], _T("./image/video/victory (328).jpg"));
	loadimage(&video[328], _T("./image/video/victory (329).jpg"));
	loadimage(&video[329], _T("./image/video/victory (330).jpg"));
	loadimage(&video[330], _T("./image/video/victory (331).jpg"));
	loadimage(&video[331], _T("./image/video/victory (332).jpg"));
	loadimage(&video[332], _T("./image/video/victory (333).jpg"));
	loadimage(&video[333], _T("./image/video/victory (334).jpg"));
	loadimage(&video[334], _T("./image/video/victory (335).jpg"));
	loadimage(&video[335], _T("./image/video/victory (336).jpg"));
	loadimage(&video[336], _T("./image/video/victory (337).jpg"));
	loadimage(&video[337], _T("./image/video/victory (338).jpg"));
	loadimage(&video[338], _T("./image/video/victory (339).jpg"));
	loadimage(&video[339], _T("./image/video/victory (340).jpg"));
	loadimage(&video[340], _T("./image/video/victory (341).jpg"));
	loadimage(&video[341], _T("./image/video/victory (342).jpg"));
	loadimage(&video[342], _T("./image/video/victory (343).jpg"));
	loadimage(&video[343], _T("./image/video/victory (344).jpg"));
	loadimage(&video[344], _T("./image/video/victory (345).jpg"));
	loadimage(&video[345], _T("./image/video/victory (346).jpg"));
	loadimage(&video[346], _T("./image/video/victory (347).jpg"));
	loadimage(&video[347], _T("./image/video/victory (348).jpg"));
	loadimage(&video[348], _T("./image/video/victory (349).jpg"));
	loadimage(&video[349], _T("./image/video/victory (350).jpg"));
	loadimage(&video[350], _T("./image/video/victory (351).jpg"));
	loadimage(&video[351], _T("./image/video/victory (352).jpg"));
	loadimage(&video[352], _T("./image/video/victory (353).jpg"));
	loadimage(&video[353], _T("./image/video/victory (354).jpg"));
	loadimage(&video[354], _T("./image/video/victory (355).jpg"));
	loadimage(&video[355], _T("./image/video/victory (356).jpg"));
	loadimage(&video[356], _T("./image/video/victory (357).jpg"));
	loadimage(&video[357], _T("./image/video/victory (358).jpg"));
	loadimage(&video[358], _T("./image/video/victory (359).jpg"));
	loadimage(&video[359], _T("./image/video/victory (360).jpg"));
	loadimage(&video[360], _T("./image/video/victory (361).jpg"));
	loadimage(&video[361], _T("./image/video/victory (362).jpg"));
	loadimage(&video[362], _T("./image/video/victory (363).jpg"));
	loadimage(&video[363], _T("./image/video/victory (364).jpg"));
	loadimage(&video[364], _T("./image/video/victory (365).jpg"));
	loadimage(&video[365], _T("./image/video/victory (366).jpg"));
	loadimage(&video[366], _T("./image/video/victory (367).jpg"));
	loadimage(&video[367], _T("./image/video/victory (368).jpg"));
	loadimage(&video[368], _T("./image/video/victory (369).jpg"));
	loadimage(&video[369], _T("./image/video/victory (370).jpg"));
	loadimage(&video[370], _T("./image/video/victory (371).jpg"));
	loadimage(&video[371], _T("./image/video/victory (372).jpg"));
	loadimage(&video[372], _T("./image/video/victory (373).jpg"));
	loadimage(&video[373], _T("./image/video/victory (374).jpg"));
	loadimage(&video[374], _T("./image/video/victory (375).jpg"));
	loadimage(&video[375], _T("./image/video/victory (376).jpg"));
	loadimage(&video[376], _T("./image/video/victory (377).jpg"));
	loadimage(&video[377], _T("./image/video/victory (378).jpg"));
	loadimage(&video[378], _T("./image/video/victory (379).jpg"));
	loadimage(&video[379], _T("./image/video/victory (380).jpg"));
	loadimage(&video[380], _T("./image/video/victory (381).jpg"));
	loadimage(&video[381], _T("./image/video/victory (382).jpg"));
	loadimage(&video[382], _T("./image/video/victory (383).jpg"));
	loadimage(&video[383], _T("./image/video/victory (384).jpg"));
	loadimage(&video[384], _T("./image/video/victory (385).jpg"));
	loadimage(&video[385], _T("./image/video/victory (386).jpg"));
	loadimage(&video[386], _T("./image/video/victory (387).jpg"));
	loadimage(&video[387], _T("./image/video/victory (388).jpg"));
	loadimage(&video[388], _T("./image/video/victory (389).jpg"));
	loadimage(&video[389], _T("./image/video/victory (390).jpg"));
	loadimage(&video[390], _T("./image/video/victory (391).jpg"));
	loadimage(&video[391], _T("./image/video/victory (392).jpg"));
	loadimage(&video[392], _T("./image/video/victory (393).jpg"));
	loadimage(&video[393], _T("./image/video/victory (394).jpg"));
	loadimage(&video[394], _T("./image/video/victory (395).jpg"));
	loadimage(&video[395], _T("./image/video/victory (396).jpg"));
	loadimage(&video[396], _T("./image/video/victory (397).jpg"));
	loadimage(&video[397], _T("./image/video/victory (398).jpg"));
	loadimage(&video[398], _T("./image/video/victory (399).jpg"));
	loadimage(&video[399], _T("./image/video/victory (400).jpg"));
	loadimage(&video[400], _T("./image/video/victory (401).jpg"));
	loadimage(&video[401], _T("./image/video/victory (402).jpg"));
	loadimage(&video[402], _T("./image/video/victory (403).jpg"));
	loadimage(&video[403], _T("./image/video/victory (404).jpg"));
	loadimage(&video[404], _T("./image/video/victory (405).jpg"));
	loadimage(&video[405], _T("./image/video/victory (406).jpg"));
	loadimage(&video[406], _T("./image/video/victory (407).jpg"));
	loadimage(&video[407], _T("./image/video/victory (408).jpg"));
	loadimage(&video[408], _T("./image/video/victory (409).jpg"));
	loadimage(&video[409], _T("./image/video/victory (410).jpg"));
	loadimage(&video[410], _T("./image/video/victory (411).jpg"));
	loadimage(&video[411], _T("./image/video/victory (412).jpg"));
	loadimage(&video[412], _T("./image/video/victory (413).jpg"));
	loadimage(&video[413], _T("./image/video/victory (414).jpg"));
	loadimage(&video[414], _T("./image/video/victory (415).jpg"));
	loadimage(&video[415], _T("./image/video/victory (416).jpg"));
	loadimage(&video[416], _T("./image/video/victory (417).jpg"));
	loadimage(&video[417], _T("./image/video/victory (418).jpg"));
	loadimage(&video[418], _T("./image/video/victory (419).jpg"));
	loadimage(&video[419], _T("./image/video/victory (420).jpg"));
	loadimage(&video[420], _T("./image/video/victory (421).jpg"));
	loadimage(&video[421], _T("./image/video/victory (422).jpg"));
	loadimage(&video[422], _T("./image/video/victory (423).jpg"));
	loadimage(&video[423], _T("./image/video/victory (424).jpg"));
	loadimage(&video[424], _T("./image/video/victory (425).jpg"));
	loadimage(&video[425], _T("./image/video/victory (426).jpg"));
	loadimage(&video[426], _T("./image/video/victory (427).jpg"));
	loadimage(&video[427], _T("./image/video/victory (428).jpg"));
	loadimage(&video[428], _T("./image/video/victory (429).jpg"));
	loadimage(&video[429], _T("./image/video/victory (430).jpg"));
	loadimage(&video[430], _T("./image/video/victory (431).jpg"));
	loadimage(&video[431], _T("./image/video/victory (432).jpg"));
	loadimage(&video[432], _T("./image/video/victory (433).jpg"));
	loadimage(&video[433], _T("./image/video/victory (434).jpg"));
	loadimage(&video[434], _T("./image/video/victory (435).jpg"));
	loadimage(&video[435], _T("./image/video/victory (436).jpg"));
	loadimage(&video[436], _T("./image/video/victory (437).jpg"));
	loadimage(&video[437], _T("./image/video/victory (438).jpg"));
	loadimage(&video[438], _T("./image/video/victory (439).jpg"));
	loadimage(&video[439], _T("./image/video/victory (440).jpg"));
	loadimage(&video[440], _T("./image/video/victory (441).jpg"));
	loadimage(&video[441], _T("./image/video/victory (442).jpg"));
	loadimage(&video[442], _T("./image/video/victory (443).jpg"));
	loadimage(&video[443], _T("./image/video/victory (444).jpg"));
	loadimage(&video[444], _T("./image/video/victory (445).jpg"));
	loadimage(&video[445], _T("./image/video/victory (446).jpg"));
	loadimage(&video[446], _T("./image/video/victory (447).jpg"));
	loadimage(&video[447], _T("./image/video/victory (448).jpg"));
	loadimage(&video[448], _T("./image/video/victory (449).jpg"));
	loadimage(&video[449], _T("./image/video/victory (450).jpg"));
	loadimage(&video[450], _T("./image/video/victory (451).jpg"));
	loadimage(&video[451], _T("./image/video/victory (452).jpg"));
	loadimage(&video[452], _T("./image/video/victory (453).jpg"));
	loadimage(&video[453], _T("./image/video/victory (454).jpg"));
	loadimage(&video[454], _T("./image/video/victory (455).jpg"));
	loadimage(&video[455], _T("./image/video/victory (456).jpg"));
	loadimage(&video[456], _T("./image/video/victory (457).jpg"));
	loadimage(&video[457], _T("./image/video/victory (458).jpg"));
	loadimage(&video[458], _T("./image/video/victory (459).jpg"));
	loadimage(&video[459], _T("./image/video/victory (460).jpg"));
	loadimage(&video[460], _T("./image/video/victory (461).jpg"));
	loadimage(&video[461], _T("./image/video/victory (462).jpg"));
	loadimage(&video[462], _T("./image/video/victory (463).jpg"));
	loadimage(&video[463], _T("./image/video/victory (464).jpg"));
	loadimage(&video[464], _T("./image/video/victory (465).jpg"));
	loadimage(&video[465], _T("./image/video/victory (466).jpg"));
	loadimage(&video[466], _T("./image/video/victory (467).jpg"));
	loadimage(&video[467], _T("./image/video/victory (468).jpg"));
	loadimage(&video[468], _T("./image/video/victory (469).jpg"));
	loadimage(&video[469], _T("./image/video/victory (470).jpg"));
	loadimage(&video[470], _T("./image/video/victory (471).jpg"));
	loadimage(&video[471], _T("./image/video/victory (472).jpg"));
	loadimage(&video[472], _T("./image/video/victory (473).jpg"));
	loadimage(&video[473], _T("./image/video/victory (474).jpg"));
	loadimage(&video[474], _T("./image/video/victory (475).jpg"));
	loadimage(&video[475], _T("./image/video/victory (476).jpg"));
	loadimage(&video[476], _T("./image/video/victory (477).jpg"));
	loadimage(&video[477], _T("./image/video/victory (478).jpg"));
	loadimage(&video[478], _T("./image/video/victory (479).jpg"));
	loadimage(&video[479], _T("./image/video/victory (480).jpg"));
	loadimage(&video[480], _T("./image/video/victory (481).jpg"));
	loadimage(&video[481], _T("./image/video/victory (482).jpg"));
	loadimage(&video[482], _T("./image/video/victory (483).jpg"));
	loadimage(&video[483], _T("./image/video/victory (484).jpg"));
	loadimage(&video[484], _T("./image/video/victory (485).jpg"));
	loadimage(&video[485], _T("./image/video/victory (486).jpg"));
	loadimage(&video[486], _T("./image/video/victory (487).jpg"));
	loadimage(&video[487], _T("./image/video/victory (488).jpg"));
	loadimage(&video[488], _T("./image/video/victory (489).jpg"));
	loadimage(&video[489], _T("./image/video/victory (490).jpg"));
	loadimage(&video[490], _T("./image/video/victory (491).jpg"));
	loadimage(&video[491], _T("./image/video/victory (492).jpg"));
	loadimage(&video[492], _T("./image/video/victory (493).jpg"));
	loadimage(&video[493], _T("./image/video/victory (494).jpg"));
	loadimage(&video[494], _T("./image/video/victory (495).jpg"));
	loadimage(&video[495], _T("./image/video/victory (496).jpg"));
	loadimage(&video[496], _T("./image/video/victory (497).jpg"));
	loadimage(&video[497], _T("./image/video/victory (498).jpg"));
	loadimage(&video[498], _T("./image/video/victory (499).jpg"));
	loadimage(&video[499], _T("./image/video/victory (500).jpg"));
	loadimage(&video[500], _T("./image/video/victory (501).jpg"));
	loadimage(&video[501], _T("./image/video/victory (502).jpg"));
	loadimage(&video[502], _T("./image/video/victory (503).jpg"));
	loadimage(&video[503], _T("./image/video/victory (504).jpg"));
	loadimage(&video[504], _T("./image/video/victory (505).jpg"));
	loadimage(&video[505], _T("./image/video/victory (506).jpg"));
	loadimage(&video[506], _T("./image/video/victory (507).jpg"));
	loadimage(&video[507], _T("./image/video/victory (508).jpg"));
	loadimage(&video[508], _T("./image/video/victory (509).jpg"));
	loadimage(&video[509], _T("./image/video/victory (510).jpg"));
	loadimage(&video[510], _T("./image/video/victory (511).jpg"));
	loadimage(&video[511], _T("./image/video/victory (512).jpg"));
	loadimage(&video[512], _T("./image/video/victory (513).jpg"));
	loadimage(&video[513], _T("./image/video/victory (514).jpg"));
	loadimage(&video[514], _T("./image/video/victory (515).jpg"));
	loadimage(&video[515], _T("./image/video/victory (516).jpg"));
	loadimage(&video[516], _T("./image/video/victory (517).jpg"));
	loadimage(&video[517], _T("./image/video/victory (518).jpg"));
	loadimage(&video[518], _T("./image/video/victory (519).jpg"));
	loadimage(&video[519], _T("./image/video/victory (520).jpg"));
	loadimage(&video[520], _T("./image/video/victory (521).jpg"));
	loadimage(&video[521], _T("./image/video/victory (522).jpg"));
	loadimage(&video[522], _T("./image/video/victory (523).jpg"));
	loadimage(&video[523], _T("./image/video/victory (524).jpg"));
	loadimage(&video[524], _T("./image/video/victory (525).jpg"));
	loadimage(&video[525], _T("./image/video/victory (526).jpg"));
	loadimage(&video[526], _T("./image/video/victory (527).jpg"));
	loadimage(&video[527], _T("./image/video/victory (528).jpg"));
	loadimage(&video[528], _T("./image/video/victory (529).jpg"));
	loadimage(&video[529], _T("./image/video/victory (530).jpg"));
	loadimage(&video[530], _T("./image/video/victory (531).jpg"));
	loadimage(&video[531], _T("./image/video/victory (532).jpg"));
	loadimage(&video[532], _T("./image/video/victory (533).jpg"));
	loadimage(&video[533], _T("./image/video/victory (534).jpg"));
	loadimage(&video[534], _T("./image/video/victory (535).jpg"));
	loadimage(&video[535], _T("./image/video/victory (536).jpg"));
	loadimage(&video[536], _T("./image/video/victory (537).jpg"));
	loadimage(&video[537], _T("./image/video/victory (538).jpg"));
	loadimage(&video[538], _T("./image/video/victory (539).jpg"));
	loadimage(&video[539], _T("./image/video/victory (540).jpg"));
	loadimage(&video[540], _T("./image/video/victory (541).jpg"));
	loadimage(&video[541], _T("./image/video/victory (542).jpg"));
	loadimage(&video[542], _T("./image/video/victory (543).jpg"));
	loadimage(&video[543], _T("./image/video/victory (544).jpg"));
	loadimage(&video[544], _T("./image/video/victory (545).jpg"));
	loadimage(&video[545], _T("./image/video/victory (546).jpg"));
	loadimage(&video[546], _T("./image/video/victory (547).jpg"));
	loadimage(&video[547], _T("./image/video/victory (548).jpg"));
	loadimage(&video[548], _T("./image/video/victory (549).jpg"));
	loadimage(&video[549], _T("./image/video/victory (550).jpg"));
	loadimage(&video[550], _T("./image/video/victory (551).jpg"));
	loadimage(&video[551], _T("./image/video/victory (552).jpg"));
	loadimage(&video[552], _T("./image/video/victory (553).jpg"));
	loadimage(&video[553], _T("./image/video/victory (554).jpg"));
	loadimage(&video[554], _T("./image/video/victory (555).jpg"));
	loadimage(&video[555], _T("./image/video/victory (556).jpg"));
	loadimage(&video[556], _T("./image/video/victory (557).jpg"));
	loadimage(&video[557], _T("./image/video/victory (558).jpg"));
	loadimage(&video[558], _T("./image/video/victory (559).jpg"));
	loadimage(&video[559], _T("./image/video/victory (560).jpg"));
	loadimage(&video[560], _T("./image/video/victory (561).jpg"));
	loadimage(&video[561], _T("./image/video/victory (562).jpg"));
	loadimage(&video[562], _T("./image/video/victory (563).jpg"));
	loadimage(&video[563], _T("./image/video/victory (564).jpg"));
	loadimage(&video[564], _T("./image/video/victory (565).jpg"));
	loadimage(&video[565], _T("./image/video/victory (566).jpg"));
	loadimage(&video[566], _T("./image/video/victory (567).jpg"));
	loadimage(&video[567], _T("./image/video/victory (568).jpg"));
	loadimage(&video[568], _T("./image/video/victory (569).jpg"));
	loadimage(&video[569], _T("./image/video/victory (570).jpg"));
	loadimage(&video[570], _T("./image/video/victory (571).jpg"));
	loadimage(&video[571], _T("./image/video/victory (572).jpg"));
	loadimage(&video[572], _T("./image/video/victory (573).jpg"));
	loadimage(&video[573], _T("./image/video/victory (574).jpg"));
	loadimage(&video[574], _T("./image/video/victory (575).jpg"));
	loadimage(&video[575], _T("./image/video/victory (576).jpg"));
	loadimage(&video[576], _T("./image/video/victory (577).jpg"));
	loadimage(&video[577], _T("./image/video/victory (578).jpg"));
	loadimage(&video[578], _T("./image/video/victory (579).jpg"));
	loadimage(&video[579], _T("./image/video/victory (580).jpg"));
	loadimage(&video[580], _T("./image/video/victory (581).jpg"));
	loadimage(&video[581], _T("./image/video/victory (582).jpg"));
	loadimage(&video[582], _T("./image/video/victory (583).jpg"));
	loadimage(&video[583], _T("./image/video/victory (584).jpg"));
	loadimage(&video[584], _T("./image/video/victory (585).jpg"));
	loadimage(&video[585], _T("./image/video/victory (586).jpg"));
	loadimage(&video[586], _T("./image/video/victory (587).jpg"));
	loadimage(&video[587], _T("./image/video/victory (588).jpg"));
	loadimage(&video[588], _T("./image/video/victory (589).jpg"));
	loadimage(&video[589], _T("./image/video/victory (590).jpg"));
	loadimage(&video[590], _T("./image/video/victory (591).jpg"));
	loadimage(&video[591], _T("./image/video/victory (592).jpg"));
	loadimage(&video[592], _T("./image/video/victory (593).jpg"));
	loadimage(&video[593], _T("./image/video/victory (594).jpg"));
	loadimage(&video[594], _T("./image/video/victory (595).jpg"));
	loadimage(&video[595], _T("./image/video/victory (596).jpg"));
	loadimage(&video[596], _T("./image/video/victory (597).jpg"));
	loadimage(&video[597], _T("./image/video/victory (598).jpg"));
	loadimage(&video[598], _T("./image/video/victory (599).jpg"));
	loadimage(&video[599], _T("./image/video/victory (600).jpg"));
	loadimage(&video[600], _T("./image/video/victory (601).jpg"));
	loadimage(&video[601], _T("./image/video/victory (602).jpg"));
	loadimage(&video[602], _T("./image/video/victory (603).jpg"));
	loadimage(&video[603], _T("./image/video/victory (604).jpg"));
	loadimage(&video[604], _T("./image/video/victory (605).jpg"));
	loadimage(&video[605], _T("./image/video/victory (606).jpg"));
	loadimage(&video[606], _T("./image/video/victory (607).jpg"));
	loadimage(&video[607], _T("./image/video/victory (608).jpg"));
	loadimage(&video[608], _T("./image/video/victory (609).jpg"));
	loadimage(&video[609], _T("./image/video/victory (610).jpg"));
	loadimage(&video[610], _T("./image/video/victory (611).jpg"));
	loadimage(&video[611], _T("./image/video/victory (612).jpg"));
	loadimage(&video[612], _T("./image/video/victory (613).jpg"));
	loadimage(&video[613], _T("./image/video/victory (614).jpg"));
	loadimage(&video[614], _T("./image/video/victory (615).jpg"));
	loadimage(&video[615], _T("./image/video/victory (616).jpg"));
	loadimage(&video[616], _T("./image/video/victory (617).jpg"));
	loadimage(&video[617], _T("./image/video/victory (618).jpg"));
	loadimage(&video[618], _T("./image/video/victory (619).jpg"));
	loadimage(&video[619], _T("./image/video/victory (620).jpg"));
	loadimage(&video[620], _T("./image/video/victory (621).jpg"));
	loadimage(&video[621], _T("./image/video/victory (622).jpg"));
	loadimage(&video[622], _T("./image/video/victory (623).jpg"));
	loadimage(&video[623], _T("./image/video/victory (624).jpg"));
	loadimage(&video[624], _T("./image/video/victory (625).jpg"));
	loadimage(&video[625], _T("./image/video/victory (626).jpg"));
	loadimage(&video[626], _T("./image/video/victory (627).jpg"));
	loadimage(&video[627], _T("./image/video/victory (628).jpg"));
	loadimage(&video[628], _T("./image/video/victory (629).jpg"));
	loadimage(&video[629], _T("./image/video/victory (630).jpg"));
	loadimage(&video[630], _T("./image/video/victory (631).jpg"));
	loadimage(&video[631], _T("./image/video/victory (632).jpg"));
	loadimage(&video[632], _T("./image/video/victory (633).jpg"));
	loadimage(&video[633], _T("./image/video/victory (634).jpg"));
	loadimage(&video[634], _T("./image/video/victory (635).jpg"));
	loadimage(&video[635], _T("./image/video/victory (636).jpg"));
	loadimage(&video[636], _T("./image/video/victory (637).jpg"));
	loadimage(&video[637], _T("./image/video/victory (638).jpg"));
	loadimage(&video[638], _T("./image/video/victory (639).jpg"));
	loadimage(&video[639], _T("./image/video/victory (640).jpg"));
	loadimage(&video[640], _T("./image/video/victory (641).jpg"));
	loadimage(&video[641], _T("./image/video/victory (642).jpg"));
	loadimage(&video[642], _T("./image/video/victory (643).jpg"));
	loadimage(&video[643], _T("./image/video/victory (644).jpg"));
	loadimage(&video[644], _T("./image/video/victory (645).jpg"));
	loadimage(&video[645], _T("./image/video/victory (646).jpg"));
	loadimage(&video[646], _T("./image/video/victory (647).jpg"));
	loadimage(&video[647], _T("./image/video/victory (648).jpg"));
	loadimage(&video[648], _T("./image/video/victory (649).jpg"));
	loadimage(&video[649], _T("./image/video/victory (650).jpg"));
	loadimage(&video[650], _T("./image/video/victory (651).jpg"));
	loadimage(&video[651], _T("./image/video/victory (652).jpg"));
	loadimage(&video[652], _T("./image/video/victory (653).jpg"));
	loadimage(&video[653], _T("./image/video/victory (654).jpg"));
	loadimage(&video[654], _T("./image/video/victory (655).jpg"));
	loadimage(&video[655], _T("./image/video/victory (656).jpg"));
	loadimage(&video[656], _T("./image/video/victory (657).jpg"));
	loadimage(&video[657], _T("./image/video/victory (658).jpg"));
	loadimage(&video[658], _T("./image/video/victory (659).jpg"));
	loadimage(&video[659], _T("./image/video/victory (660).jpg"));
	loadimage(&video[660], _T("./image/video/victory (661).jpg"));
	loadimage(&video[661], _T("./image/video/victory (662).jpg"));
	loadimage(&video[662], _T("./image/video/victory (663).jpg"));
	loadimage(&video[663], _T("./image/video/victory (664).jpg"));
	loadimage(&video[664], _T("./image/video/victory (665).jpg"));
	loadimage(&video[665], _T("./image/video/victory (666).jpg"));
	loadimage(&video[666], _T("./image/video/victory (667).jpg"));
	loadimage(&video[667], _T("./image/video/victory (668).jpg"));
	loadimage(&video[668], _T("./image/video/victory (669).jpg"));
	loadimage(&video[669], _T("./image/video/victory (670).jpg"));
	loadimage(&video[670], _T("./image/video/victory (671).jpg"));
	loadimage(&video[671], _T("./image/video/victory (672).jpg"));
	loadimage(&video[672], _T("./image/video/victory (673).jpg"));
	loadimage(&video[673], _T("./image/video/victory (674).jpg"));
	loadimage(&video[674], _T("./image/video/victory (675).jpg"));
	loadimage(&video[675], _T("./image/video/victory (676).jpg"));
	loadimage(&video[676], _T("./image/video/victory (677).jpg"));
	loadimage(&video[677], _T("./image/video/victory (678).jpg"));
	loadimage(&video[678], _T("./image/video/victory (679).jpg"));
	loadimage(&video[679], _T("./image/video/victory (680).jpg"));
	loadimage(&video[680], _T("./image/video/victory (681).jpg"));
	loadimage(&video[681], _T("./image/video/victory (682).jpg"));
	loadimage(&video[682], _T("./image/video/victory (683).jpg"));
	loadimage(&video[683], _T("./image/video/victory (684).jpg"));
	loadimage(&video[684], _T("./image/video/victory (685).jpg"));
	loadimage(&video[685], _T("./image/video/victory (686).jpg"));
	loadimage(&video[686], _T("./image/video/victory (687).jpg"));
	loadimage(&video[687], _T("./image/video/victory (688).jpg"));
	loadimage(&video[688], _T("./image/video/victory (689).jpg"));
	loadimage(&video[689], _T("./image/video/victory (690).jpg"));
	loadimage(&video[690], _T("./image/video/victory (691).jpg"));
	loadimage(&video[691], _T("./image/video/victory (692).jpg"));
	loadimage(&video[692], _T("./image/video/victory (693).jpg"));
	loadimage(&video[693], _T("./image/video/victory (694).jpg"));
	loadimage(&video[694], _T("./image/video/victory (695).jpg"));
	loadimage(&video[695], _T("./image/video/victory (696).jpg"));
	loadimage(&video[696], _T("./image/video/victory (697).jpg"));
	loadimage(&video[697], _T("./image/video/victory (698).jpg"));
	loadimage(&video[698], _T("./image/video/victory (699).jpg"));
	loadimage(&video[699], _T("./image/video/victory (700).jpg"));
	loadimage(&video[700], _T("./image/video/victory (701).jpg"));
	loadimage(&video[701], _T("./image/video/victory (702).jpg"));
	loadimage(&video[702], _T("./image/video/victory (703).jpg"));
	loadimage(&video[703], _T("./image/video/victory (704).jpg"));
	loadimage(&video[704], _T("./image/video/victory (705).jpg"));
	loadimage(&video[705], _T("./image/video/victory (706).jpg"));
	loadimage(&video[706], _T("./image/video/victory (707).jpg"));
	loadimage(&video[707], _T("./image/video/victory (708).jpg"));
	loadimage(&video[708], _T("./image/video/victory (709).jpg"));
	loadimage(&video[709], _T("./image/video/victory (710).jpg"));
	loadimage(&video[710], _T("./image/video/victory (711).jpg"));
	loadimage(&video[711], _T("./image/video/victory (712).jpg"));
	loadimage(&video[712], _T("./image/video/victory (713).jpg"));
	loadimage(&video[713], _T("./image/video/victory (714).jpg"));
	loadimage(&video[714], _T("./image/video/victory (715).jpg"));
	loadimage(&video[715], _T("./image/video/victory (716).jpg"));
	loadimage(&video[716], _T("./image/video/victory (717).jpg"));
	loadimage(&video[717], _T("./image/video/victory (718).jpg"));
	loadimage(&video[718], _T("./image/video/victory (719).jpg"));
	loadimage(&video[719], _T("./image/video/victory (720).jpg"));
	loadimage(&video[720], _T("./image/video/victory (721).jpg"));
	loadimage(&video[721], _T("./image/video/victory (722).jpg"));
	loadimage(&video[722], _T("./image/video/victory (723).jpg"));
	loadimage(&video[723], _T("./image/video/victory (724).jpg"));
	loadimage(&video[724], _T("./image/video/victory (725).jpg"));
	loadimage(&video[725], _T("./image/video/victory (726).jpg"));
	loadimage(&video[726], _T("./image/video/victory (727).jpg"));
	loadimage(&video[727], _T("./image/video/victory (728).jpg"));
	loadimage(&video[728], _T("./image/video/victory (729).jpg"));
	loadimage(&video[729], _T("./image/video/victory (730).jpg"));
	loadimage(&video[730], _T("./image/video/victory (731).jpg"));
	loadimage(&video[731], _T("./image/video/victory (732).jpg"));
	loadimage(&video[732], _T("./image/video/victory (733).jpg"));
	loadimage(&video[733], _T("./image/video/victory (734).jpg"));
	loadimage(&video[734], _T("./image/video/victory (735).jpg"));
	loadimage(&video[735], _T("./image/video/victory (736).jpg"));
	loadimage(&video[736], _T("./image/video/victory (737).jpg"));
	loadimage(&video[737], _T("./image/video/victory (738).jpg"));
	loadimage(&video[738], _T("./image/video/victory (739).jpg"));
	loadimage(&video[739], _T("./image/video/victory (740).jpg"));
	loadimage(&video[740], _T("./image/video/victory (741).jpg"));
	loadimage(&video[741], _T("./image/video/victory (742).jpg"));
	loadimage(&video[742], _T("./image/video/victory (743).jpg"));
	loadimage(&video[743], _T("./image/video/victory (744).jpg"));
	loadimage(&video[744], _T("./image/video/victory (745).jpg"));
	loadimage(&video[745], _T("./image/video/victory (746).jpg"));
	loadimage(&video[746], _T("./image/video/victory (747).jpg"));
	loadimage(&video[747], _T("./image/video/victory (748).jpg"));
	loadimage(&video[748], _T("./image/video/victory (749).jpg"));
	loadimage(&video[749], _T("./image/video/victory (750).jpg"));
	loadimage(&video[750], _T("./image/video/victory (751).jpg"));
	loadimage(&video[751], _T("./image/video/victory (752).jpg"));
	loadimage(&video[752], _T("./image/video/victory (753).jpg"));
	loadimage(&video[753], _T("./image/video/victory (754).jpg"));
	loadimage(&video[754], _T("./image/video/victory (755).jpg"));
	loadimage(&video[755], _T("./image/video/victory (756).jpg"));
	loadimage(&video[756], _T("./image/video/victory (757).jpg"));
	loadimage(&video[757], _T("./image/video/victory (758).jpg"));
	loadimage(&video[758], _T("./image/video/victory (759).jpg"));
	loadimage(&video[759], _T("./image/video/victory (760).jpg"));
	loadimage(&video[760], _T("./image/video/victory (761).jpg"));
	loadimage(&video[761], _T("./image/video/victory (762).jpg"));
	loadimage(&video[762], _T("./image/video/victory (763).jpg"));
	loadimage(&video[763], _T("./image/video/victory (764).jpg"));
	loadimage(&video[764], _T("./image/video/victory (765).jpg"));
	loadimage(&video[765], _T("./image/video/victory (766).jpg"));
	loadimage(&video[766], _T("./image/video/victory (767).jpg"));
	loadimage(&video[767], _T("./image/video/victory (768).jpg"));
	loadimage(&video[768], _T("./image/video/victory (769).jpg"));
	loadimage(&video[769], _T("./image/video/victory (770).jpg"));
	loadimage(&video[770], _T("./image/video/victory (771).jpg"));
	loadimage(&video[771], _T("./image/video/victory (772).jpg"));
	loadimage(&video[772], _T("./image/video/victory (773).jpg"));
	loadimage(&video[773], _T("./image/video/victory (774).jpg"));
	loadimage(&video[774], _T("./image/video/victory (775).jpg"));
	loadimage(&video[775], _T("./image/video/victory (776).jpg"));
	loadimage(&video[776], _T("./image/video/victory (777).jpg"));
	loadimage(&video[777], _T("./image/video/victory (778).jpg"));
	loadimage(&video[778], _T("./image/video/victory (779).jpg"));
	loadimage(&video[779], _T("./image/video/victory (780).jpg"));
	loadimage(&video[780], _T("./image/video/victory (781).jpg"));
	loadimage(&video[781], _T("./image/video/victory (782).jpg"));
	loadimage(&video[782], _T("./image/video/victory (783).jpg"));
	loadimage(&video[783], _T("./image/video/victory (784).jpg"));
	loadimage(&video[784], _T("./image/video/victory (785).jpg"));
	loadimage(&video[785], _T("./image/video/victory (786).jpg"));
	loadimage(&video[786], _T("./image/video/victory (787).jpg"));
	loadimage(&video[787], _T("./image/video/victory (788).jpg"));
	loadimage(&video[788], _T("./image/video/victory (789).jpg"));
	loadimage(&video[789], _T("./image/video/victory (790).jpg"));
	loadimage(&video[790], _T("./image/video/victory (791).jpg"));
	loadimage(&video[791], _T("./image/video/victory (792).jpg"));
	loadimage(&video[792], _T("./image/video/victory (793).jpg"));
	loadimage(&video[793], _T("./image/video/victory (794).jpg"));
	loadimage(&video[794], _T("./image/video/victory (795).jpg"));
	loadimage(&video[795], _T("./image/video/victory (796).jpg"));
	loadimage(&video[796], _T("./image/video/victory (797).jpg"));
	loadimage(&video[797], _T("./image/video/victory (798).jpg"));
	loadimage(&video[798], _T("./image/video/victory (799).jpg"));
	loadimage(&video[799], _T("./image/video/victory (800).jpg"));
	loadimage(&video[800], _T("./image/video/victory (801).jpg"));
	loadimage(&video[801], _T("./image/video/victory (802).jpg"));
	loadimage(&video[802], _T("./image/video/victory (803).jpg"));
	loadimage(&video[803], _T("./image/video/victory (804).jpg"));
	loadimage(&video[804], _T("./image/video/victory (805).jpg"));
	loadimage(&video[805], _T("./image/video/victory (806).jpg"));
	loadimage(&video[806], _T("./image/video/victory (807).jpg"));
	loadimage(&video[807], _T("./image/video/victory (808).jpg"));
	loadimage(&video[808], _T("./image/video/victory (809).jpg"));
	loadimage(&video[809], _T("./image/video/victory (810).jpg"));
	loadimage(&video[810], _T("./image/video/victory (811).jpg"));
	loadimage(&video[811], _T("./image/video/victory (812).jpg"));
	loadimage(&video[812], _T("./image/video/victory (813).jpg"));
	loadimage(&video[813], _T("./image/video/victory (814).jpg"));
	loadimage(&video[814], _T("./image/video/victory (815).jpg"));
	loadimage(&video[815], _T("./image/video/victory (816).jpg"));
	loadimage(&video[816], _T("./image/video/victory (817).jpg"));
	loadimage(&video[817], _T("./image/video/victory (818).jpg"));
	loadimage(&video[818], _T("./image/video/victory (819).jpg"));
	loadimage(&video[819], _T("./image/video/victory (820).jpg"));
	loadimage(&video[820], _T("./image/video/victory (821).jpg"));
	loadimage(&video[821], _T("./image/video/victory (822).jpg"));
	loadimage(&video[822], _T("./image/video/victory (823).jpg"));
	loadimage(&video[823], _T("./image/video/victory (824).jpg"));
	loadimage(&video[824], _T("./image/video/victory (825).jpg"));
	loadimage(&video[825], _T("./image/video/victory (826).jpg"));
	loadimage(&video[826], _T("./image/video/victory (827).jpg"));
	loadimage(&video[827], _T("./image/video/victory (828).jpg"));
	loadimage(&video[828], _T("./image/video/victory (829).jpg"));
	loadimage(&video[829], _T("./image/video/victory (830).jpg"));
	loadimage(&video[830], _T("./image/video/victory (831).jpg"));
	loadimage(&video[831], _T("./image/video/victory (832).jpg"));
	loadimage(&video[832], _T("./image/video/victory (833).jpg"));
	loadimage(&video[833], _T("./image/video/victory (834).jpg"));
	loadimage(&video[834], _T("./image/video/victory (835).jpg"));
	loadimage(&video[835], _T("./image/video/victory (836).jpg"));
	loadimage(&video[836], _T("./image/video/victory (837).jpg"));
	loadimage(&video[837], _T("./image/video/victory (838).jpg"));
	loadimage(&video[838], _T("./image/video/victory (839).jpg"));
	loadimage(&video[839], _T("./image/video/victory (840).jpg"));
	loadimage(&video[840], _T("./image/video/victory (841).jpg"));
	loadimage(&video[841], _T("./image/video/victory (842).jpg"));
	loadimage(&video[842], _T("./image/video/victory (843).jpg"));
	loadimage(&video[843], _T("./image/video/victory (844).jpg"));
	loadimage(&video[844], _T("./image/video/victory (845).jpg"));
	loadimage(&video[845], _T("./image/video/victory (846).jpg"));
	loadimage(&video[846], _T("./image/video/victory (847).jpg"));
	loadimage(&video[847], _T("./image/video/victory (848).jpg"));
	loadimage(&video[848], _T("./image/video/victory (849).jpg"));
	loadimage(&video[849], _T("./image/video/victory (850).jpg"));
	loadimage(&video[850], _T("./image/video/victory (851).jpg"));
	loadimage(&video[851], _T("./image/video/victory (852).jpg"));
	loadimage(&video[852], _T("./image/video/victory (853).jpg"));
	loadimage(&video[853], _T("./image/video/victory (854).jpg"));
	loadimage(&video[854], _T("./image/video/victory (855).jpg"));
	loadimage(&video[855], _T("./image/video/victory (856).jpg"));
	loadimage(&video[856], _T("./image/video/victory (857).jpg"));
	loadimage(&video[857], _T("./image/video/victory (858).jpg"));
	loadimage(&video[858], _T("./image/video/victory (859).jpg"));
	loadimage(&video[859], _T("./image/video/victory (860).jpg"));
	loadimage(&video[860], _T("./image/video/victory (861).jpg"));
	loadimage(&video[861], _T("./image/video/victory (862).jpg"));
	loadimage(&video[862], _T("./image/video/victory (863).jpg"));
	loadimage(&video[863], _T("./image/video/victory (864).jpg"));
	loadimage(&video[864], _T("./image/video/victory (865).jpg"));
	loadimage(&video[865], _T("./image/video/victory (866).jpg"));
	loadimage(&video[866], _T("./image/video/victory (867).jpg"));
	loadimage(&video[867], _T("./image/video/victory (868).jpg"));
	loadimage(&video[868], _T("./image/video/victory (869).jpg"));
	loadimage(&video[869], _T("./image/video/victory (870).jpg"));
	loadimage(&video[870], _T("./image/video/victory (871).jpg"));
	loadimage(&video[871], _T("./image/video/victory (872).jpg"));
	loadimage(&video[872], _T("./image/video/victory (873).jpg"));
	loadimage(&video[873], _T("./image/video/victory (874).jpg"));
	loadimage(&video[874], _T("./image/video/victory (875).jpg"));
	loadimage(&video[875], _T("./image/video/victory (876).jpg"));
	loadimage(&video[876], _T("./image/video/victory (877).jpg"));
	loadimage(&video[877], _T("./image/video/victory (878).jpg"));
	loadimage(&video[878], _T("./image/video/victory (879).jpg"));
	loadimage(&video[879], _T("./image/video/victory (880).jpg"));
	loadimage(&video[880], _T("./image/video/victory (881).jpg"));
	loadimage(&video[881], _T("./image/video/victory (882).jpg"));
	loadimage(&video[882], _T("./image/video/victory (883).jpg"));
	loadimage(&video[883], _T("./image/video/victory (884).jpg"));
	loadimage(&video[884], _T("./image/video/victory (885).jpg"));
	loadimage(&video[885], _T("./image/video/victory (886).jpg"));
	loadimage(&video[886], _T("./image/video/victory (887).jpg"));
	loadimage(&video[887], _T("./image/video/victory (888).jpg"));
	loadimage(&video[888], _T("./image/video/victory (889).jpg"));
	loadimage(&video[889], _T("./image/video/victory (890).jpg"));
	loadimage(&video[890], _T("./image/video/victory (891).jpg"));
	loadimage(&video[891], _T("./image/video/victory (892).jpg"));
	loadimage(&video[892], _T("./image/video/victory (893).jpg"));
	loadimage(&video[893], _T("./image/video/victory (894).jpg"));
	loadimage(&video[894], _T("./image/video/victory (895).jpg"));
	loadimage(&video[895], _T("./image/video/victory (896).jpg"));
	loadimage(&video[896], _T("./image/video/victory (897).jpg"));
	loadimage(&video[897], _T("./image/video/victory (898).jpg"));
	loadimage(&video[898], _T("./image/video/victory (899).jpg"));
	loadimage(&video[899], _T("./image/video/victory (900).jpg"));
	loadimage(&video[900], _T("./image/video/victory (901).jpg"));
	loadimage(&video[901], _T("./image/video/victory (902).jpg"));
	loadimage(&video[902], _T("./image/video/victory (903).jpg"));
	loadimage(&video[903], _T("./image/video/victory (904).jpg"));
	loadimage(&video[904], _T("./image/video/victory (905).jpg"));
	loadimage(&video[905], _T("./image/video/victory (906).jpg"));
	loadimage(&video[906], _T("./image/video/victory (907).jpg"));
	loadimage(&video[907], _T("./image/video/victory (908).jpg"));
	loadimage(&video[908], _T("./image/video/victory (909).jpg"));
	loadimage(&video[909], _T("./image/video/victory (910).jpg"));
	loadimage(&video[910], _T("./image/video/victory (911).jpg"));
	loadimage(&video[911], _T("./image/video/victory (912).jpg"));
	loadimage(&video[912], _T("./image/video/victory (913).jpg"));
	loadimage(&video[913], _T("./image/video/victory (914).jpg"));
	loadimage(&video[914], _T("./image/video/victory (915).jpg"));
	loadimage(&video[915], _T("./image/video/victory (916).jpg"));
	loadimage(&video[916], _T("./image/video/victory (917).jpg"));
	loadimage(&video[917], _T("./image/video/victory (918).jpg"));
	loadimage(&video[918], _T("./image/video/victory (919).jpg"));
	loadimage(&video[919], _T("./image/video/victory (920).jpg"));
	loadimage(&video[920], _T("./image/video/victory (921).jpg"));
	loadimage(&video[921], _T("./image/video/victory (922).jpg"));
	loadimage(&video[922], _T("./image/video/victory (923).jpg"));
	loadimage(&video[923], _T("./image/video/victory (924).jpg"));
	loadimage(&video[924], _T("./image/video/victory (925).jpg"));
	loadimage(&video[925], _T("./image/video/victory (926).jpg"));
	loadimage(&video[926], _T("./image/video/victory (927).jpg"));
	loadimage(&video[927], _T("./image/video/victory (928).jpg"));
	loadimage(&video[928], _T("./image/video/victory (929).jpg"));
	loadimage(&video[929], _T("./image/video/victory (930).jpg"));
	loadimage(&video[930], _T("./image/video/victory (931).jpg"));
	loadimage(&video[931], _T("./image/video/victory (932).jpg"));
	loadimage(&video[932], _T("./image/video/victory (933).jpg"));
	loadimage(&video[933], _T("./image/video/victory (934).jpg"));
	loadimage(&video[934], _T("./image/video/victory (935).jpg"));
	loadimage(&video[935], _T("./image/video/victory (936).jpg"));
	loadimage(&video[936], _T("./image/video/victory (937).jpg"));
	loadimage(&video[937], _T("./image/video/victory (938).jpg"));
	loadimage(&video[938], _T("./image/video/victory (939).jpg"));
	loadimage(&video[939], _T("./image/video/victory (940).jpg"));
	loadimage(&video[940], _T("./image/video/victory (941).jpg"));
	loadimage(&video[941], _T("./image/video/victory (942).jpg"));
	loadimage(&video[942], _T("./image/video/victory (943).jpg"));
	loadimage(&video[943], _T("./image/video/victory (944).jpg"));
	loadimage(&video[944], _T("./image/video/victory (945).jpg"));
	loadimage(&video[945], _T("./image/video/victory (946).jpg"));
	loadimage(&video[946], _T("./image/video/victory (947).jpg"));
	loadimage(&video[947], _T("./image/video/victory (948).jpg"));
	loadimage(&video[948], _T("./image/video/victory (949).jpg"));
	loadimage(&video[949], _T("./image/video/victory (950).jpg"));
	loadimage(&video[950], _T("./image/video/victory (951).jpg"));
	loadimage(&video[951], _T("./image/video/victory (952).jpg"));
	loadimage(&video[952], _T("./image/video/victory (953).jpg"));
	loadimage(&video[953], _T("./image/video/victory (954).jpg"));
	loadimage(&video[954], _T("./image/video/victory (955).jpg"));
	loadimage(&video[955], _T("./image/video/victory (956).jpg"));
	loadimage(&video[956], _T("./image/video/victory (957).jpg"));
	loadimage(&video[957], _T("./image/video/victory (958).jpg"));
	loadimage(&video[958], _T("./image/video/victory (959).jpg"));
	loadimage(&video[959], _T("./image/video/victory (960).jpg"));
	loadimage(&video[960], _T("./image/video/victory (961).jpg"));
	loadimage(&video[961], _T("./image/video/victory (962).jpg"));
	loadimage(&video[962], _T("./image/video/victory (963).jpg"));
	loadimage(&video[963], _T("./image/video/victory (964).jpg"));
	loadimage(&video[964], _T("./image/video/victory (965).jpg"));
	loadimage(&video[965], _T("./image/video/victory (966).jpg"));
	loadimage(&video[966], _T("./image/video/victory (967).jpg"));
	loadimage(&video[967], _T("./image/video/victory (968).jpg"));
	loadimage(&video[968], _T("./image/video/victory (969).jpg"));
	loadimage(&video[969], _T("./image/video/victory (970).jpg"));
	loadimage(&video[970], _T("./image/video/victory (971).jpg"));
	loadimage(&video[971], _T("./image/video/victory (972).jpg"));
	loadimage(&video[972], _T("./image/video/victory (973).jpg"));
	loadimage(&video[973], _T("./image/video/victory (974).jpg"));
	loadimage(&video[974], _T("./image/video/victory (975).jpg"));
	loadimage(&video[975], _T("./image/video/victory (976).jpg"));
	loadimage(&video[976], _T("./image/video/victory (977).jpg"));
	loadimage(&video[977], _T("./image/video/victory (978).jpg"));
	loadimage(&video[978], _T("./image/video/victory (979).jpg"));
	loadimage(&video[979], _T("./image/video/victory (980).jpg"));
	loadimage(&video[980], _T("./image/video/victory (981).jpg"));
	loadimage(&video[981], _T("./image/video/victory (982).jpg"));
	loadimage(&video[982], _T("./image/video/victory (983).jpg"));
	loadimage(&video[983], _T("./image/video/victory (984).jpg"));
	loadimage(&video[984], _T("./image/video/victory (985).jpg"));
	loadimage(&video[985], _T("./image/video/victory (986).jpg"));
	loadimage(&video[986], _T("./image/video/victory (987).jpg"));
	loadimage(&video[987], _T("./image/video/victory (988).jpg"));
	loadimage(&video[988], _T("./image/video/victory (989).jpg"));
	loadimage(&video[989], _T("./image/video/victory (990).jpg"));
	loadimage(&video[990], _T("./image/video/victory (991).jpg"));
	loadimage(&video[991], _T("./image/video/victory (992).jpg"));
	loadimage(&video[992], _T("./image/video/victory (993).jpg"));
	loadimage(&video[993], _T("./image/video/victory (994).jpg"));
	loadimage(&video[994], _T("./image/video/victory (995).jpg"));
	loadimage(&video[995], _T("./image/video/victory (996).jpg"));
	loadimage(&video[996], _T("./image/video/victory (997).jpg"));
	loadimage(&video[997], _T("./image/video/victory (998).jpg"));
	loadimage(&video[998], _T("./image/video/victory (999).jpg"));
	loadimage(&video[999], _T("./image/video/victory (1000).jpg"));
	loadimage(&video[1000], _T("./image/video/victory (1001).jpg"));
	loadimage(&video[1001], _T("./image/video/victory (1002).jpg"));
	loadimage(&video[1002], _T("./image/video/victory (1003).jpg"));
	loadimage(&video[1003], _T("./image/video/victory (1004).jpg"));
	loadimage(&video[1004], _T("./image/video/victory (1005).jpg"));
	loadimage(&video[1005], _T("./image/video/victory (1006).jpg"));
	loadimage(&video[1006], _T("./image/video/victory (1007).jpg"));
	loadimage(&video[1007], _T("./image/video/victory (1008).jpg"));
	loadimage(&video[1008], _T("./image/video/victory (1009).jpg"));
	loadimage(&video[1009], _T("./image/video/victory (1010).jpg"));
	loadimage(&video[1010], _T("./image/video/victory (1011).jpg"));
	loadimage(&video[1011], _T("./image/video/victory (1012).jpg"));
	loadimage(&video[1012], _T("./image/video/victory (1013).jpg"));
	loadimage(&video[1013], _T("./image/video/victory (1014).jpg"));
	loadimage(&video[1014], _T("./image/video/victory (1015).jpg"));
	loadimage(&video[1015], _T("./image/video/victory (1016).jpg"));
	loadimage(&video[1016], _T("./image/video/victory (1017).jpg"));
	loadimage(&video[1017], _T("./image/video/victory (1018).jpg"));
	loadimage(&video[1018], _T("./image/video/victory (1019).jpg"));
	loadimage(&video[1019], _T("./image/video/victory (1020).jpg"));
	loadimage(&video[1020], _T("./image/video/victory (1021).jpg"));
	loadimage(&video[1021], _T("./image/video/victory (1022).jpg"));
	loadimage(&video[1022], _T("./image/video/victory (1023).jpg"));
	loadimage(&video[1023], _T("./image/video/victory (1024).jpg"));
	loadimage(&video[1024], _T("./image/video/victory (1025).jpg"));
	loadimage(&video[1025], _T("./image/video/victory (1026).jpg"));
	loadimage(&video[1026], _T("./image/video/victory (1027).jpg"));
	loadimage(&video[1027], _T("./image/video/victory (1028).jpg"));
	loadimage(&video[1028], _T("./image/video/victory (1029).jpg"));
	loadimage(&video[1029], _T("./image/video/victory (1030).jpg"));
	loadimage(&video[1030], _T("./image/video/victory (1031).jpg"));
	loadimage(&video[1031], _T("./image/video/victory (1032).jpg"));
	loadimage(&video[1032], _T("./image/video/victory (1033).jpg"));
	loadimage(&video[1033], _T("./image/video/victory (1034).jpg"));
	loadimage(&video[1034], _T("./image/video/victory (1035).jpg"));
	loadimage(&video[1035], _T("./image/video/victory (1036).jpg"));
	loadimage(&video[1036], _T("./image/video/victory (1037).jpg"));
	loadimage(&video[1037], _T("./image/video/victory (1038).jpg"));
	loadimage(&video[1038], _T("./image/video/victory (1039).jpg"));
	loadimage(&video[1039], _T("./image/video/victory (1040).jpg"));
	loadimage(&video[1040], _T("./image/video/victory (1041).jpg"));
	loadimage(&video[1041], _T("./image/video/victory (1042).jpg"));
	loadimage(&video[1042], _T("./image/video/victory (1043).jpg"));
	loadimage(&video[1043], _T("./image/video/victory (1044).jpg"));
	loadimage(&video[1044], _T("./image/video/victory (1045).jpg"));
	loadimage(&video[1045], _T("./image/video/victory (1046).jpg"));
	loadimage(&video[1046], _T("./image/video/victory (1047).jpg"));
	loadimage(&video[1047], _T("./image/video/victory (1048).jpg"));
	loadimage(&video[1048], _T("./image/video/victory (1049).jpg"));
	loadimage(&video[1049], _T("./image/video/victory (1050).jpg"));
	loadimage(&video[1050], _T("./image/video/victory (1051).jpg"));
	loadimage(&video[1051], _T("./image/video/victory (1052).jpg"));
	loadimage(&video[1052], _T("./image/video/victory (1053).jpg"));
	loadimage(&video[1053], _T("./image/video/victory (1054).jpg"));
	loadimage(&video[1054], _T("./image/video/victory (1055).jpg"));
	loadimage(&video[1055], _T("./image/video/victory (1056).jpg"));
	loadimage(&video[1056], _T("./image/video/victory (1057).jpg"));
	loadimage(&video[1057], _T("./image/video/victory (1058).jpg"));
	loadimage(&video[1058], _T("./image/video/victory (1059).jpg"));
	loadimage(&video[1059], _T("./image/video/victory (1060).jpg"));
	loadimage(&video[1060], _T("./image/video/victory (1061).jpg"));
	loadimage(&video[1061], _T("./image/video/victory (1062).jpg"));
	loadimage(&video[1062], _T("./image/video/victory (1063).jpg"));
	loadimage(&video[1063], _T("./image/video/victory (1064).jpg"));
	loadimage(&video[1064], _T("./image/video/victory (1065).jpg"));
	loadimage(&video[1065], _T("./image/video/victory (1066).jpg"));
	loadimage(&video[1066], _T("./image/video/victory (1067).jpg"));
	loadimage(&video[1067], _T("./image/video/victory (1068).jpg"));
	loadimage(&video[1068], _T("./image/video/victory (1069).jpg"));
	loadimage(&video[1069], _T("./image/video/victory (1070).jpg"));
	loadimage(&video[1070], _T("./image/video/victory (1071).jpg"));
	loadimage(&video[1071], _T("./image/video/victory (1072).jpg"));
	loadimage(&video[1072], _T("./image/video/victory (1073).jpg"));
	loadimage(&video[1073], _T("./image/video/victory (1074).jpg"));
	loadimage(&video[1074], _T("./image/video/victory (1075).jpg"));
	loadimage(&video[1075], _T("./image/video/victory (1076).jpg"));
	loadimage(&video[1076], _T("./image/video/victory (1077).jpg"));
	loadimage(&video[1077], _T("./image/video/victory (1078).jpg"));
	loadimage(&video[1078], _T("./image/video/victory (1079).jpg"));
	loadimage(&video[1079], _T("./image/video/victory (1080).jpg"));
	loadimage(&video[1080], _T("./image/video/victory (1081).jpg"));
	loadimage(&video[1081], _T("./image/video/victory (1082).jpg"));
	loadimage(&video[1082], _T("./image/video/victory (1083).jpg"));
	loadimage(&video[1083], _T("./image/video/victory (1084).jpg"));
	loadimage(&video[1084], _T("./image/video/victory (1085).jpg"));
	loadimage(&video[1085], _T("./image/video/victory (1086).jpg"));
	loadimage(&video[1086], _T("./image/video/victory (1087).jpg"));
	loadimage(&video[1087], _T("./image/video/victory (1088).jpg"));
	loadimage(&video[1088], _T("./image/video/victory (1089).jpg"));
	loadimage(&video[1089], _T("./image/video/victory (1090).jpg"));
	loadimage(&video[1090], _T("./image/video/victory (1091).jpg"));
	loadimage(&video[1091], _T("./image/video/victory (1092).jpg"));
	loadimage(&video[1092], _T("./image/video/victory (1093).jpg"));
	loadimage(&video[1093], _T("./image/video/victory (1094).jpg"));
	loadimage(&video[1094], _T("./image/video/victory (1095).jpg"));
	loadimage(&video[1095], _T("./image/video/victory (1096).jpg"));
	loadimage(&video[1096], _T("./image/video/victory (1097).jpg"));
	loadimage(&video[1097], _T("./image/video/victory (1098).jpg"));
	loadimage(&video[1098], _T("./image/video/victory (1099).jpg"));
	loadimage(&video[1099], _T("./image/video/victory (1100).jpg"));
	loadimage(&video[1100], _T("./image/video/victory (1101).jpg"));
	loadimage(&video[1101], _T("./image/video/victory (1102).jpg"));
	loadimage(&video[1102], _T("./image/video/victory (1103).jpg"));
	loadimage(&video[1103], _T("./image/video/victory (1104).jpg"));
	loadimage(&video[1104], _T("./image/video/victory (1105).jpg"));
	loadimage(&video[1105], _T("./image/video/victory (1106).jpg"));
	loadimage(&video[1106], _T("./image/video/victory (1107).jpg"));
	loadimage(&video[1107], _T("./image/video/victory (1108).jpg"));
	loadimage(&video[1108], _T("./image/video/victory (1109).jpg"));
	loadimage(&video[1109], _T("./image/video/victory (1110).jpg"));
	loadimage(&video[1110], _T("./image/video/victory (1111).jpg"));
	loadimage(&video[1111], _T("./image/video/victory (1112).jpg"));
	loadimage(&video[1112], _T("./image/video/victory (1113).jpg"));
	loadimage(&video[1113], _T("./image/video/victory (1114).jpg"));
	loadimage(&video[1114], _T("./image/video/victory (1115).jpg"));
	loadimage(&video[1115], _T("./image/video/victory (1116).jpg"));
	loadimage(&video[1116], _T("./image/video/victory (1117).jpg"));
	loadimage(&video[1117], _T("./image/video/victory (1118).jpg"));
	loadimage(&video[1118], _T("./image/video/victory (1119).jpg"));
	loadimage(&video[1119], _T("./image/video/victory (1120).jpg"));
	loadimage(&video[1120], _T("./image/video/victory (1121).jpg"));
	loadimage(&video[1121], _T("./image/video/victory (1122).jpg"));
	loadimage(&video[1122], _T("./image/video/victory (1123).jpg"));
	loadimage(&video[1123], _T("./image/video/victory (1124).jpg"));
	loadimage(&video[1124], _T("./image/video/victory (1125).jpg"));
	loadimage(&video[1125], _T("./image/video/victory (1126).jpg"));
	loadimage(&video[1126], _T("./image/video/victory (1127).jpg"));
	loadimage(&video[1127], _T("./image/video/victory (1128).jpg"));
	loadimage(&video[1128], _T("./image/video/victory (1129).jpg"));
	loadimage(&video[1129], _T("./image/video/victory (1130).jpg"));
	loadimage(&video[1130], _T("./image/video/victory (1131).jpg"));
	loadimage(&video[1131], _T("./image/video/victory (1132).jpg"));
	loadimage(&video[1132], _T("./image/video/victory (1133).jpg"));
	loadimage(&video[1133], _T("./image/video/victory (1134).jpg"));
	loadimage(&video[1134], _T("./image/video/victory (1135).jpg"));
	loadimage(&video[1135], _T("./image/video/victory (1136).jpg"));
	loadimage(&video[1136], _T("./image/video/victory (1137).jpg"));
	loadimage(&video[1137], _T("./image/video/victory (1138).jpg"));
	loadimage(&video[1138], _T("./image/video/victory (1139).jpg"));
	loadimage(&video[1139], _T("./image/video/victory (1140).jpg"));
	loadimage(&video[1140], _T("./image/video/victory (1141).jpg"));
	loadimage(&video[1141], _T("./image/video/victory (1142).jpg"));
	loadimage(&video[1142], _T("./image/video/victory (1143).jpg"));
	loadimage(&video[1143], _T("./image/video/victory (1144).jpg"));
	loadimage(&video[1144], _T("./image/video/victory (1145).jpg"));
	loadimage(&video[1145], _T("./image/video/victory (1146).jpg"));
	loadimage(&video[1146], _T("./image/video/victory (1147).jpg"));
	loadimage(&video[1147], _T("./image/video/victory (1148).jpg"));
	loadimage(&video[1148], _T("./image/video/victory (1149).jpg"));
	loadimage(&video[1149], _T("./image/video/victory (1150).jpg"));
	loadimage(&video[1150], _T("./image/video/victory (1151).jpg"));
	loadimage(&video[1151], _T("./image/video/victory (1152).jpg"));
	loadimage(&video[1152], _T("./image/video/victory (1153).jpg"));
	loadimage(&video[1153], _T("./image/video/victory (1154).jpg"));
	loadimage(&video[1154], _T("./image/video/victory (1155).jpg"));
	loadimage(&video[1155], _T("./image/video/victory (1156).jpg"));
	loadimage(&video[1156], _T("./image/video/victory (1157).jpg"));
	loadimage(&video[1157], _T("./image/video/victory (1158).jpg"));
	loadimage(&video[1158], _T("./image/video/victory (1159).jpg"));
	loadimage(&video[1159], _T("./image/video/victory (1160).jpg"));
	loadimage(&video[1160], _T("./image/video/victory (1161).jpg"));
	loadimage(&video[1161], _T("./image/video/victory (1162).jpg"));
	loadimage(&video[1162], _T("./image/video/victory (1163).jpg"));
	loadimage(&video[1163], _T("./image/video/victory (1164).jpg"));
	loadimage(&video[1164], _T("./image/video/victory (1165).jpg"));
	loadimage(&video[1165], _T("./image/video/victory (1166).jpg"));
	loadimage(&video[1166], _T("./image/video/victory (1167).jpg"));
	loadimage(&video[1167], _T("./image/video/victory (1168).jpg"));
	loadimage(&video[1168], _T("./image/video/victory (1169).jpg"));
	loadimage(&video[1169], _T("./image/video/victory (1170).jpg"));
	loadimage(&video[1170], _T("./image/video/victory (1171).jpg"));
	loadimage(&video[1171], _T("./image/video/victory (1172).jpg"));
	loadimage(&video[1172], _T("./image/video/victory (1173).jpg"));
	loadimage(&video[1173], _T("./image/video/victory (1174).jpg"));
	loadimage(&video[1174], _T("./image/video/victory (1175).jpg"));
	loadimage(&video[1175], _T("./image/video/victory (1176).jpg"));
	loadimage(&video[1176], _T("./image/video/victory (1177).jpg"));
	loadimage(&video[1177], _T("./image/video/victory (1178).jpg"));
	loadimage(&video[1178], _T("./image/video/victory (1179).jpg"));
	loadimage(&video[1179], _T("./image/video/victory (1180).jpg"));
	loadimage(&video[1180], _T("./image/video/victory (1181).jpg"));
	loadimage(&video[1181], _T("./image/video/victory (1182).jpg"));
	loadimage(&video[1182], _T("./image/video/victory (1183).jpg"));
	loadimage(&video[1183], _T("./image/video/victory (1184).jpg"));
	loadimage(&video[1184], _T("./image/video/victory (1185).jpg"));
	loadimage(&video[1185], _T("./image/video/victory (1186).jpg"));
	loadimage(&video[1186], _T("./image/video/victory (1187).jpg"));
	loadimage(&video[1187], _T("./image/video/victory (1188).jpg"));
	loadimage(&video[1188], _T("./image/video/victory (1189).jpg"));
	loadimage(&video[1189], _T("./image/video/victory (1190).jpg"));
	loadimage(&video[1190], _T("./image/video/victory (1191).jpg"));
	loadimage(&video[1191], _T("./image/video/victory (1192).jpg"));
	loadimage(&video[1192], _T("./image/video/victory (1193).jpg"));
	loadimage(&video[1193], _T("./image/video/victory (1194).jpg"));
	loadimage(&video[1194], _T("./image/video/victory (1195).jpg"));
	loadimage(&video[1195], _T("./image/video/victory (1196).jpg"));
	loadimage(&video[1196], _T("./image/video/victory (1197).jpg"));
	loadimage(&video[1197], _T("./image/video/victory (1198).jpg"));
	loadimage(&video[1198], _T("./image/video/victory (1199).jpg"));
	loadimage(&video[1199], _T("./image/video/victory (1200).jpg"));
	loadimage(&video[1200], _T("./image/video/victory (1201).jpg"));
	loadimage(&video[1201], _T("./image/video/victory (1202).jpg"));
	loadimage(&video[1202], _T("./image/video/victory (1203).jpg"));
	loadimage(&video[1203], _T("./image/video/victory (1204).jpg"));
	loadimage(&video[1204], _T("./image/video/victory (1205).jpg"));
	loadimage(&video[1205], _T("./image/video/victory (1206).jpg"));
	loadimage(&video[1206], _T("./image/video/victory (1207).jpg"));
	loadimage(&video[1207], _T("./image/video/victory (1208).jpg"));
	loadimage(&video[1208], _T("./image/video/victory (1209).jpg"));
	loadimage(&video[1209], _T("./image/video/victory (1210).jpg"));
	loadimage(&video[1210], _T("./image/video/victory (1211).jpg"));
	loadimage(&video[1211], _T("./image/video/victory (1212).jpg"));
	loadimage(&video[1212], _T("./image/video/victory (1213).jpg"));
	loadimage(&video[1213], _T("./image/video/victory (1214).jpg"));
	loadimage(&video[1214], _T("./image/video/victory (1215).jpg"));
	loadimage(&video[1215], _T("./image/video/victory (1216).jpg"));
	loadimage(&video[1216], _T("./image/video/victory (1217).jpg"));
	loadimage(&video[1217], _T("./image/video/victory (1218).jpg"));
	loadimage(&video[1218], _T("./image/video/victory (1219).jpg"));
	loadimage(&video[1219], _T("./image/video/victory (1220).jpg"));
	loadimage(&video[1220], _T("./image/video/victory (1221).jpg"));
	loadimage(&video[1221], _T("./image/video/victory (1222).jpg"));
	loadimage(&video[1222], _T("./image/video/victory (1223).jpg"));
	loadimage(&video[1223], _T("./image/video/victory (1224).jpg"));
	loadimage(&video[1224], _T("./image/video/victory (1225).jpg"));
	loadimage(&video[1225], _T("./image/video/victory (1226).jpg"));
	loadimage(&video[1226], _T("./image/video/victory (1227).jpg"));
	loadimage(&video[1227], _T("./image/video/victory (1228).jpg"));
	loadimage(&video[1228], _T("./image/video/victory (1229).jpg"));
	loadimage(&video[1229], _T("./image/video/victory (1230).jpg"));
	loadimage(&video[1230], _T("./image/video/victory (1231).jpg"));
	loadimage(&video[1231], _T("./image/video/victory (1232).jpg"));
	loadimage(&video[1232], _T("./image/video/victory (1233).jpg"));
	loadimage(&video[1233], _T("./image/video/victory (1234).jpg"));
	loadimage(&video[1234], _T("./image/video/victory (1235).jpg"));
	loadimage(&video[1235], _T("./image/video/victory (1236).jpg"));
	loadimage(&video[1236], _T("./image/video/victory (1237).jpg"));
	loadimage(&video[1237], _T("./image/video/victory (1238).jpg"));
	loadimage(&video[1238], _T("./image/video/victory (1239).jpg"));
	loadimage(&video[1239], _T("./image/video/victory (1240).jpg"));
	loadimage(&video[1240], _T("./image/video/victory (1241).jpg"));
	loadimage(&video[1241], _T("./image/video/victory (1242).jpg"));
	loadimage(&video[1242], _T("./image/video/victory (1243).jpg"));
	loadimage(&video[1243], _T("./image/video/victory (1244).jpg"));
	loadimage(&video[1244], _T("./image/video/victory (1245).jpg"));
	loadimage(&video[1245], _T("./image/video/victory (1246).jpg"));
	loadimage(&video[1246], _T("./image/video/victory (1247).jpg"));
	loadimage(&video[1247], _T("./image/video/victory (1248).jpg"));
	loadimage(&video[1248], _T("./image/video/victory (1249).jpg"));
	loadimage(&video[1249], _T("./image/video/victory (1250).jpg"));
	loadimage(&video[1250], _T("./image/video/victory (1251).jpg"));
	loadimage(&video[1251], _T("./image/video/victory (1252).jpg"));
	loadimage(&video[1252], _T("./image/video/victory (1253).jpg"));
	loadimage(&video[1253], _T("./image/video/victory (1254).jpg"));
	loadimage(&video[1254], _T("./image/video/victory (1255).jpg"));
	loadimage(&video[1255], _T("./image/video/victory (1256).jpg"));
	loadimage(&video[1256], _T("./image/video/victory (1257).jpg"));
	loadimage(&video[1257], _T("./image/video/victory (1258).jpg"));
	loadimage(&video[1258], _T("./image/video/victory (1259).jpg"));
	loadimage(&video[1259], _T("./image/video/victory (1260).jpg"));
	loadimage(&video[1260], _T("./image/video/victory (1261).jpg"));
	loadimage(&video[1261], _T("./image/video/victory (1262).jpg"));
	loadimage(&video[1262], _T("./image/video/victory (1263).jpg"));
	loadimage(&video[1263], _T("./image/video/victory (1264).jpg"));
	loadimage(&video[1264], _T("./image/video/victory (1265).jpg"));
	loadimage(&video[1265], _T("./image/video/victory (1266).jpg"));
	loadimage(&video[1266], _T("./image/video/victory (1267).jpg"));
	loadimage(&video[1267], _T("./image/video/victory (1268).jpg"));
	loadimage(&video[1268], _T("./image/video/victory (1269).jpg"));
	loadimage(&video[1269], _T("./image/video/victory (1270).jpg"));
	loadimage(&video[1270], _T("./image/video/victory (1271).jpg"));
	loadimage(&video[1271], _T("./image/video/victory (1272).jpg"));
	loadimage(&video[1272], _T("./image/video/victory (1273).jpg"));
	loadimage(&video[1273], _T("./image/video/victory (1274).jpg"));
	loadimage(&video[1274], _T("./image/video/victory (1275).jpg"));
	loadimage(&video[1275], _T("./image/video/victory (1276).jpg"));
	loadimage(&video[1276], _T("./image/video/victory (1277).jpg"));
	loadimage(&video[1277], _T("./image/video/victory (1278).jpg"));
	loadimage(&video[1278], _T("./image/video/victory (1279).jpg"));
	loadimage(&video[1279], _T("./image/video/victory (1280).jpg"));
	loadimage(&video[1280], _T("./image/video/victory (1281).jpg"));
	loadimage(&video[1281], _T("./image/video/victory (1282).jpg"));
	loadimage(&video[1282], _T("./image/video/victory (1283).jpg"));
	loadimage(&video[1283], _T("./image/video/victory (1284).jpg"));
	loadimage(&video[1284], _T("./image/video/victory (1285).jpg"));
	loadimage(&video[1285], _T("./image/video/victory (1286).jpg"));
	loadimage(&video[1286], _T("./image/video/victory (1287).jpg"));
	loadimage(&video[1287], _T("./image/video/victory (1288).jpg"));
	loadimage(&video[1288], _T("./image/video/victory (1289).jpg"));
	loadimage(&video[1289], _T("./image/video/victory (1290).jpg"));
	loadimage(&video[1290], _T("./image/video/victory (1291).jpg"));
	loadimage(&video[1291], _T("./image/video/victory (1292).jpg"));
	loadimage(&video[1292], _T("./image/video/victory (1293).jpg"));
	loadimage(&video[1293], _T("./image/video/victory (1294).jpg"));
	loadimage(&video[1294], _T("./image/video/victory (1295).jpg"));
	loadimage(&video[1295], _T("./image/video/victory (1296).jpg"));
	loadimage(&video[1296], _T("./image/video/victory (1297).jpg"));
	loadimage(&video[1297], _T("./image/video/victory (1298).jpg"));
	loadimage(&video[1298], _T("./image/video/victory (1299).jpg"));
	loadimage(&video[1299], _T("./image/video/victory (1300).jpg"));
	loadimage(&video[1300], _T("./image/video/victory (1301).jpg"));
	loadimage(&video[1301], _T("./image/video/victory (1302).jpg"));
	loadimage(&video[1302], _T("./image/video/victory (1303).jpg"));
	loadimage(&video[1303], _T("./image/video/victory (1304).jpg"));
	loadimage(&video[1304], _T("./image/video/victory (1305).jpg"));
	loadimage(&video[1305], _T("./image/video/victory (1306).jpg"));
	loadimage(&video[1306], _T("./image/video/victory (1307).jpg"));
	loadimage(&video[1307], _T("./image/video/victory (1308).jpg"));
	loadimage(&video[1308], _T("./image/video/victory (1309).jpg"));
	loadimage(&video[1309], _T("./image/video/victory (1310).jpg"));
	loadimage(&video[1310], _T("./image/video/victory (1311).jpg"));
	loadimage(&video[1311], _T("./image/video/victory (1312).jpg"));
	loadimage(&video[1312], _T("./image/video/victory (1313).jpg"));
	loadimage(&video[1313], _T("./image/video/victory (1314).jpg"));
	loadimage(&video[1314], _T("./image/video/victory (1315).jpg"));
	loadimage(&video[1315], _T("./image/video/victory (1316).jpg"));
	loadimage(&video[1316], _T("./image/video/victory (1317).jpg"));
	loadimage(&video[1317], _T("./image/video/victory (1318).jpg"));
	loadimage(&video[1318], _T("./image/video/victory (1319).jpg"));
	loadimage(&video[1319], _T("./image/video/victory (1320).jpg"));
	loadimage(&video[1320], _T("./image/video/victory (1321).jpg"));
	loadimage(&video[1321], _T("./image/video/victory (1322).jpg"));
	loadimage(&video[1322], _T("./image/video/victory (1323).jpg"));
	loadimage(&video[1323], _T("./image/video/victory (1324).jpg"));
	loadimage(&video[1324], _T("./image/video/victory (1325).jpg"));
	loadimage(&video[1325], _T("./image/video/victory (1326).jpg"));
	loadimage(&video[1326], _T("./image/video/victory (1327).jpg"));
	loadimage(&video[1327], _T("./image/video/victory (1328).jpg"));
	loadimage(&video[1328], _T("./image/video/victory (1329).jpg"));
	loadimage(&video[1329], _T("./image/video/victory (1330).jpg"));
	loadimage(&video[1330], _T("./image/video/victory (1331).jpg"));

	BeginBatchDraw();
	for (int i = 0; i < 1331; i++) {
		putimage(0, 0, &video[i]);
		FlushBatchDraw();
		Sleep(50);
	}
	putimage(0, 0, &end);
	FlushBatchDraw();
	Sleep(8500);
	page(10, 1);
	setbkcolor(BLACK);
	cleardevice();
	EndBatchDraw();
	return;

}

//退出
void gameexit() {
	saveInfo(player);
	EndBatchDraw();
	closegraph();
	exit(0);
}

//1-1
//初始化
void startup1_1() {																										

	initgraph(width(), height(),SHOWCONSOLE);

	setbkcolor(WHITE);
	cleardevice();

	BeginBatchDraw();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY ONE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));
	FlushBatchDraw();

	AP_num(10 + player.extra_AP,1);
	HE_num(10 + player.extra_HE,1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
																														//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 0;
	t1->t.img_x = 774;
	t1->t.img_y = 598;
	t1->t.mid_x = t1->t.img_x+50;
	t1->t.mid_y = t1->t.img_y+20;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_mg1.png");

	t2->t.isArmed = 0;
	t2->t.img_x = 844;
	t2->t.img_y = 530;
	t2->t.mid_x = t2->t.img_x + 20;
	t2->t.mid_y = t2->t.img_y + 20;
	strcpy_s(t2->t.img_Path, "./image/enemy/j_s2.png");

	t3->t.isArmed = 0;
	t3->t.img_x = 966;
	t3->t.img_y = 626;
	t3->t.mid_x = t3->t.img_x + 20;
	t3->t.mid_y = t3->t.img_y + 20;
	strcpy_s(t3->t.img_Path, "./image/enemy/j_s1.png");

	t4->t.isArmed = 0;
	t4->t.img_x = 980;
	t4->t.img_y = 530;
	t4->t.mid_x = t4->t.img_x + 20;
	t4->t.mid_y = t4->t.img_y + 20;
	strcpy_s(t4->t.img_Path, "./image/enemy/j_s1.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 1130;
	t5->t.img_y = 472;
	t5->t.mid_x = t5->t.img_x + 20;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_s1.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1372;
	t6->t.img_y = 562;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/j_s1.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1498;
	t7->t.img_y = 558;
	t7->t.mid_x = t7->t.img_x + 20;
	t7->t.mid_y = t7->t.img_y + 20;
	strcpy_s(t7->t.img_Path, "./image/enemy/j_c1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1038;
	t8->t.img_y = 284;
	t8->t.mid_x = t8->t.img_x + 20;
	t8->t.mid_y = t8->t.img_y + 20;
	strcpy_s(t8->t.img_Path, "./image/enemy/j_s1.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1398;
	t9->t.img_y = 90;
	t9->t.mid_x = t9->t.img_x + 50;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/j_mg1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1124;
	t10->t.img_y = 558;
	t10->t.mid_x = t10->t.img_x + 100;
	t10->t.mid_y = t10->t.img_y + 50;
	strcpy_s(t10->t.img_Path, "./image/enemy/truck.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
				char input = _getch();
				putimage(0, 0, &img_Bk1);
				Sleep(1000);
				return;
		}
	}

}
//显示
void show1_1() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence1, wire_fence2, sandbag,sandbag2;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag, _T("./image/enemy/sandbag.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	drawAlpha(508, 642, &wire_fence1);
	drawAlpha(446, 570, &wire_fence2);
	drawAlpha(565, 445, &sandbag);
	drawAlpha(508, 531, &sandbag);
	drawAlpha(610, 530, &sandbag);
	drawAlpha(648, 626, &sandbag2);
	drawAlpha(676, 656, &sandbag2);

	static IMAGE commander, our_soldier, cannon_1;												//绘制我方单位
	loadimage(&commander, _T("./image/own/c_c.png"));
	loadimage(&our_soldier, _T("./image/own/c_s.png"));
	loadimage(&cannon_1, _T("./image/own/c_g1.png"));
	drawAlpha(50, 570, &commander);
	drawAlpha(200, 570, &our_soldier);
	drawAlpha(100, 570, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0,0,&Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0,0));
	sprintf_s(AP_char, "%d", AP_num(0,0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0,0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) -30 ), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0,0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
		{
			static IMAGE img_buf;
			static char img_Path_buf1[50];
			static int img_x_buf;
			static int img_y_buf;
			img_x_buf = s->t.img_x;
			img_y_buf = s->t.img_y;
			strcpy_s(img_Path_buf1, s->t.img_Path);
			loadimage(&img_buf, CString(img_Path_buf1), 0, 0, true);
			drawAlpha(img_x_buf, img_y_buf, &img_buf);
			img_Path_buf1[0] = '\0';
			s = s->next;
		}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0,0)) {
			putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i],NOTSRCERASE);
			putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
			explosion_i++;	
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0,1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput1_1() {																										

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1,1);
			isHit_show(1,1) ;
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_1(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1,1);
		isHit_show(1,1);
	}

	s = h;

	if (isHit(0,0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0,0)-1,1);
		}
		else {
			HE_num(HE_num(0,0)-1,1);
		}
		isFlying(0,1) ;
		hit_x(shell_x(0, 0),1);
		hit_y(shell_y(0, 0),1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2))<=kill_radius) {
				if (isKilled( h->t.isArmed , shell_Type(0, 0)) ){
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;//p = nullptr;		
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;//s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0,1);

	}

	if (isFlying(0,0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0),1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2,1);
		shell_x(shell_x(0, 0) +shell_vx(0, 0),1);
		shell_y(shell_y(0, 0) +shell_vy(0, 0),1);
	}
	
	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass1_1(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed1_1(1, 1);
	}

}
//有操作更新
void updateWithInput1_1() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while(MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2),1);
				Angle =angle(0,0)* (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10,1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0,0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0,0) > 0)) {
					isFlying(1,1);
					isHit(0,1);
					start_t = clock();
					shell_x(start_x,1);
					shell_y(start_y,1);
					shell_vx(shell_v(0, 0) * cos(Angle),1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle),1);
				}				
			}
		}
	}
}
//关卡1-1
void game1_1() {
	isPass1_1(0, 1);
	isFailed1_1(0, 1);
	startup1_1();
	while (1) {													
		show1_1();
		updateWithoutInput1_1();
		updateWithInput1_1();
		if (isPass1_1(0, 0)) {
			page(2, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed1_1(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//1-2
//初始化
void startup1_2() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	BeginBatchDraw();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY TWO"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));
	FlushBatchDraw();

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 0;
	t1->t.img_x = 774;
	t1->t.img_y = 598;
	t1->t.mid_x = t1->t.img_x + 50;
	t1->t.mid_y = t1->t.img_y + 20;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_mg1.png");

	t2->t.isArmed = 0;
	t2->t.img_x = 844;
	t2->t.img_y = 500;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/truck.png");

	t3->t.isArmed = 0;
	t3->t.img_x = 1172;
	t3->t.img_y = 540;
	t3->t.mid_x = t3->t.img_x + 20;
	t3->t.mid_y = t3->t.img_y + 20;
	strcpy_s(t3->t.img_Path, "./image/enemy/ammo.png");

	t4->t.isArmed = 1;
	t4->t.img_x = 908;
	t4->t.img_y = 602;
	t4->t.mid_x = t4->t.img_x + 100;
	t4->t.mid_y = t4->t.img_y + 50;
	strcpy_s(t4->t.img_Path, "./image/enemy/j_t1.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 1108;
	t5->t.img_y = 586;
	t5->t.mid_x = t5->t.img_x + 100;
	t5->t.mid_y = t5->t.img_y + 50;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_v1.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1368;
	t6->t.img_y = 518;
	t6->t.mid_x = t6->t.img_x + 30;
	t6->t.mid_y = t6->t.img_y + 50;
	strcpy_s(t6->t.img_Path, "./image/enemy/drum.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1330;
	t7->t.img_y = 604;
	t7->t.mid_x = t7->t.img_x + 30;
	t7->t.mid_y = t7->t.img_y + 50;
	strcpy_s(t7->t.img_Path, "./image/enemy/drum.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1404;
	t8->t.img_y = 604;
	t8->t.mid_x = t8->t.img_x + 20;
	t8->t.mid_y = t8->t.img_y + 20;
	strcpy_s(t8->t.img_Path, "./image/enemy/drum.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1492;
	t9->t.img_y = 558;
	t9->t.mid_x = t9->t.img_x + 20;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/j_c1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1478;
	t10->t.img_y = 626;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/j_s1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			return;
		}
	}

}
//显示
void show1_2() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence1, wire_fence2, sandbag, sandbag2;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag, _T("./image/enemy/sandbag.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	drawAlpha(508, 642, &wire_fence1);
	drawAlpha(446, 570, &wire_fence2);
	drawAlpha(565, 445, &sandbag);
	drawAlpha(508, 531, &sandbag);
	drawAlpha(610, 530, &sandbag);
	drawAlpha(648, 626, &sandbag2);
	drawAlpha(676, 656, &sandbag2);

	static IMAGE commander, our_soldier, cannon_1;												//绘制我方单位
	loadimage(&commander, _T("./image/own/c_c.png"));
	loadimage(&our_soldier, _T("./image/own/c_s.png"));
	loadimage(&cannon_1, _T("./image/own/c_g2.png"));
	drawAlpha(10, 570, &commander);
	drawAlpha(200, 570, &our_soldier);
	drawAlpha(50, 570, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf2[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf2, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf2), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf2[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput1_2() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_1(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;//p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;//s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass1_2(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed1_2(1, 1);
	}

}
//有操作更新
void updateWithInput1_2() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡1-2
void game1_2() {
	isPass1_2(0, 1);
	isFailed1_2(0, 1);
	startup1_2();
	while (1) {
		show1_2();
		updateWithoutInput1_2();
		updateWithInput1_2();
		if (isPass1_2(0, 0)) {
			page(3, 1);
			setbkcolor(BLACK);
			cleardevice();
			EndBatchDraw();
			return;
		}
		if (isFailed1_2(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//1-3
//初始化
void startup1_3() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	BeginBatchDraw();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(200, 200, _T("DAY THREE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));
	FlushBatchDraw();

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 1;
	t1->t.img_x = 580;
	t1->t.img_y = 510;
	t1->t.mid_x = t1->t.img_x + 100;
	t1->t.mid_y = t1->t.img_y + 50;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_t2.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 826;
	t2->t.img_y = 504;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/j_t1.png");

	t3->t.isArmed = 1;
	t3->t.img_x = 826;
	t3->t.img_y = 594;
	t3->t.mid_x = t3->t.img_x + 100;
	t3->t.mid_y = t3->t.img_y + 50;
	strcpy_s(t3->t.img_Path, "./image/enemy/j_t2.png");

	t4->t.isArmed = 0;
	t4->t.img_x = 708;
	t4->t.img_y = 540;
	t4->t.mid_x = t4->t.img_x + 20;
	t4->t.mid_y = t4->t.img_y + 20;
	strcpy_s(t4->t.img_Path, "./image/enemy/j_s2.png");
	
	t5->t.isArmed = 0;
	t5->t.img_x = 1108;
	t5->t.img_y = 586;
	t5->t.mid_x = t5->t.img_x + 100;
	t5->t.mid_y = t5->t.img_y + 50;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_v1.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 982;
	t6->t.img_y = 570;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/j_s2.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1016;
	t7->t.img_y = 316;
	t7->t.mid_x = t7->t.img_x + 20;
	t7->t.mid_y = t7->t.img_y + 20;
	strcpy_s(t7->t.img_Path, "./image/enemy/j_s1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1308;
	t8->t.img_y = 564;
	t8->t.mid_x = t8->t.img_x + 80;
	t8->t.mid_y = t8->t.img_y + 50;
	strcpy_s(t8->t.img_Path, "./image/enemy/j_g1.png");
	
	t9->t.isArmed = 0;
	t9->t.img_x = 1492;
	t9->t.img_y = 558;
	t9->t.mid_x = t9->t.img_x + 20;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/j_c1.png");
	
	t10->t.isArmed = 0;
	t10->t.img_x = 1478;
	t10->t.img_y = 626;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/j_s1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			return;
		}
	}

}
//显示
void show1_3() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	static IMAGE wire_fence1, wire_fence2, sandbag2;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	drawAlpha(508, 642, &wire_fence1);
	drawAlpha(446, 570, &wire_fence2);
	drawAlpha(648, 626, &sandbag2);
	drawAlpha(676, 656, &sandbag2);

	static IMAGE commander, our_soldier, cannon_1;												//绘制我方单位
	loadimage(&commander, _T("./image/own/c_c.png"));
	loadimage(&our_soldier, _T("./image/own/c_s.png"));
	loadimage(&cannon_1, _T("./image/own/c_g2.png"));
	drawAlpha(10, 570, &commander);
	drawAlpha(200, 570, &our_soldier);
	drawAlpha(50, 570, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf3[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf3, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf3), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf3[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput1_3() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass1_3(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed1_3(1, 1);
	}

}
//有操作更新
void updateWithInput1_3() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡1-3
void game1_3() {
	isPass1_3(0, 1);
	isFailed1_3(0, 1);
	startup1_3();
	while (1) {
		show1_3();
		updateWithoutInput1_3();
		updateWithInput1_3();
		if (isPass1_3(0, 0)) {
			page(10, 1);
			IMAGE c;
			loadimage(&c, _T("./image/background/completed.png"));
			putimage(0, 0, &c);
			FlushBatchDraw();
			Sleep(3000);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed1_3(0, 0)) {
			page(10, 1);
			IMAGE f;
			loadimage(&f, _T("./image/background/failed.png"));
			putimage(0, 0, &f);
			FlushBatchDraw();
			Sleep(3000);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//2-1
//初始化
void startup2_1() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY ONE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 0;
	t1->t.img_x = 622;
	t1->t.img_y = 314;
	t1->t.mid_x = t1->t.img_x + 50;
	t1->t.mid_y = t1->t.img_y + 20;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_mg1.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 702;
	t2->t.img_y = 300;
	t2->t.mid_x = t2->t.img_x + 120;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/pillbox.png");

	t3->t.isArmed = 0;
	t3->t.img_x = 704;
	t3->t.img_y = 464;
	t3->t.mid_x = t3->t.img_x + 50;
	t3->t.mid_y = t3->t.img_y + 20;
	strcpy_s(t3->t.img_Path, "./image/enemy/j_mg1.png");

	t4->t.isArmed = 1;
	t4->t.img_x = 770;
	t4->t.img_y = 536;
	t4->t.mid_x = t4->t.img_x + 120;
	t4->t.mid_y = t4->t.img_y + 50;
	strcpy_s(t4->t.img_Path, "./image/enemy/pillbox.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 998;
	t5->t.img_y = 332;
	t5->t.mid_x = t5->t.img_x + 20;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_s1.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1086;
	t6->t.img_y = 538;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/j_s2.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1126;
	t7->t.img_y = 420;
	t7->t.mid_x = t7->t.img_x + 80;
	t7->t.mid_y = t7->t.img_y + 50;
	strcpy_s(t7->t.img_Path, "./image/enemy/j_g1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1246;
	t8->t.img_y = 314;
	t8->t.mid_x = t8->t.img_x + 80;
	t8->t.mid_y = t8->t.img_y + 50;
	strcpy_s(t8->t.img_Path, "./image/enemy/j_g1.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1310;
	t9->t.img_y = 518;
	t9->t.mid_x = t9->t.img_x + 50;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/j_mg1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1500;
	t10->t.img_y = 580;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/j_c1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show2_1() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence1, wire_fence2, sandbag,sandbag2,sandbag3;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag, _T("./image/enemy/sandbag.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	loadimage(&sandbag3, _T("./image/enemy/sandbag3.png"));
	drawAlpha(504, 590, &wire_fence1);
	drawAlpha(442, 374, &wire_fence2);
	drawAlpha(472, 480, &wire_fence2);
	drawAlpha(1226, 586, &sandbag);
	drawAlpha(604, 420, &sandbag2);
	drawAlpha(670, 530, &sandbag2);
	drawAlpha(564, 346, &sandbag3);

	static IMAGE cannon_1,ship;	//commander, our_soldier, 											//绘制我方单位
	//loadimage(&commander, _T("./image/own/a_c.png"));
	//loadimage(&our_soldier, _T("./image/own/a_s.png"));
	loadimage(&cannon_1, _T("./image/own/a_t.png"));
	loadimage(&ship, _T("./image/own/a_b.png"));
	//drawAlpha(50, 570, &commander);
	//drawAlpha(200, 570, &our_soldier);
	drawAlpha(40, 520, &cannon_1);
	drawAlpha(0, 408, &ship);
	drawAlpha(0, 300, &ship);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf4[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf4, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf4), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf4[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput2_1() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass2_1(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed2_1(1, 1);
	}

}
//有操作更新
void updateWithInput2_1() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡2-1
void game2_1() {
	isPass2_1(0, 1);
	isFailed2_1(0, 1);
	startup2_1();
	while (1) {
		show2_1();
		updateWithoutInput2_1();
		updateWithInput2_1();
		if (isPass2_1(0, 0)) {
			page(5, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed2_1(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//2-2
//初始化
void startup2_2() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-2.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY TWO"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 0;
	t1->t.img_x = 622;
	t1->t.img_y = 314;
	t1->t.mid_x = t1->t.img_x + 50;
	t1->t.mid_y = t1->t.img_y + 20;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_mg1.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 832;
	t2->t.img_y = 556;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/j_t1.png");

	t3->t.isArmed = 0;
	t3->t.img_x = 704;
	t3->t.img_y = 464;
	t3->t.mid_x = t3->t.img_x + 50;
	t3->t.mid_y = t3->t.img_y + 20;
	strcpy_s(t3->t.img_Path, "./image/enemy/j_mg1.png");

	t4->t.isArmed = 0;
	t4->t.img_x = 832;
	t4->t.img_y = 332;
	t4->t.mid_x = t4->t.img_x + 120;
	t4->t.mid_y = t4->t.img_y + 50;
	strcpy_s(t4->t.img_Path, "./image/enemy/j_p2.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 1082;
	t5->t.img_y = 332;
	t5->t.mid_x = t5->t.img_x + 120;
	t5->t.mid_y = t5->t.img_y + 50;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_p2.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1332;
	t6->t.img_y = 332;
	t6->t.mid_x = t6->t.img_x + 120;
	t6->t.mid_y = t6->t.img_y + 50;
	strcpy_s(t6->t.img_Path, "./image/enemy/j_p2.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1280;
	t7->t.img_y = 452;
	t7->t.mid_x = t7->t.img_x + 100;
	t7->t.mid_y = t7->t.img_y + 50;
	strcpy_s(t7->t.img_Path, "./image/enemy/j_p1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1064;
	t8->t.img_y = 606;
	t8->t.mid_x = t8->t.img_x + 120;
	t8->t.mid_y = t8->t.img_y + 50;
	strcpy_s(t8->t.img_Path, "./image/enemy/truck.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1410;
	t9->t.img_y = 602;
	t9->t.mid_x = t9->t.img_x + 20;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/drum.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1486;
	t10->t.img_y = 650;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/ammo.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show2_2() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence1, wire_fence2, sandbag2, sandbag3;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	loadimage(&sandbag3, _T("./image/enemy/sandbag3.png"));
	drawAlpha(504, 590, &wire_fence1);
	drawAlpha(442, 374, &wire_fence2);
	drawAlpha(472, 480, &wire_fence2);
	drawAlpha(604, 420, &sandbag2);
	drawAlpha(670, 530, &sandbag2);
	drawAlpha(564, 346, &sandbag3);

	static IMAGE cannon_1,our_soldier;	//commander,  											//绘制我方单位
	//loadimage(&commander, _T("./image/own/a_c.png"));
	loadimage(&our_soldier, _T("./image/own/a_s.png"));
	loadimage(&cannon_1, _T("./image/own/a_t.png"));
	//loadimage(&ship, _T("./image/own/a_b.png"));
	//drawAlpha(50, 570, &commander);
	drawAlpha(0,450, &our_soldier);
	drawAlpha(0, 570, &our_soldier);
	drawAlpha(40, 600, &cannon_1);
    //drawAlpha(0, 408, &ship);
	//drawAlpha(0, 300, &ship);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf5[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf5, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf5), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf5[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput2_2() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass2_2(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed2_2(1, 1);
	}

}
//有操作更新
void updateWithInput2_2() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡2-2
void game2_2() {
	isPass2_2(0, 1);
	isFailed2_2(0, 1);
	startup2_2();
	while (1) {
		show2_2();
		updateWithoutInput2_2();
		updateWithInput2_2();
		if (isPass2_2(0, 0)) {
			page(6, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed2_2(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//2-3
//初始化
void startup2_3() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-3.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(200, 200, _T("DAY THREE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 0;
	t1->t.img_x = 408;
	t1->t.img_y = 44;
	t1->t.mid_x = t1->t.img_x + 120;
	t1->t.mid_y = t1->t.img_y + 50;
	strcpy_s(t1->t.img_Path, "./image/enemy/j_p2.png");

	t2->t.isArmed = 0;
	t2->t.img_x = 452;
	t2->t.img_y = 176;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/j_p1.png");

	t3->t.isArmed = 1;
	t3->t.img_x = 596;
	t3->t.img_y = 520;
	t3->t.mid_x = t3->t.img_x + 100;
	t3->t.mid_y = t3->t.img_y + 50;
	strcpy_s(t3->t.img_Path, "./image/enemy/j_t3.png");

	t4->t.isArmed = 1;
	t4->t.img_x = 842;
	t4->t.img_y = 434;
	t4->t.mid_x = t4->t.img_x + 80;
	t4->t.mid_y = t4->t.img_y + 50;
	strcpy_s(t4->t.img_Path, "./image/enemy/j_t2.png");

	t5->t.isArmed = 1;
	t5->t.img_x = 936;
	t5->t.img_y = 595;
	t5->t.mid_x = t5->t.img_x + 80;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/j_t1.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1070;
	t6->t.img_y = 476;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/j_s2.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1256;
	t7->t.img_y = 476;
	t7->t.mid_x = t7->t.img_x + 80;
	t7->t.mid_y = t7->t.img_y + 50;
	strcpy_s(t7->t.img_Path, "./image/enemy/j_s1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1200;
	t8->t.img_y = 590;
	t8->t.mid_x = t8->t.img_x + 20;
	t8->t.mid_y = t8->t.img_y + 20;
	strcpy_s(t8->t.img_Path, "./image/enemy/j_s1.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1390;
	t9->t.img_y = 550;
	t9->t.mid_x = t9->t.img_x + 50;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/j_g1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1536;
	t10->t.img_y = 448;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/j_c1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show2_3() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_2-3.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE cannon_1, our_soldier,commander;												//绘制我方单位
	//loadimage(&commander, _T("./image/own/a_c.png"));
	loadimage(&our_soldier, _T("./image/own/a_s.png"));
	loadimage(&cannon_1, _T("./image/own/a_t.png"));
	loadimage(&commander, _T("./image/own/a_c.png"));
	//drawAlpha(50, 570, &commander);
	drawAlpha(0, 450, &our_soldier);
	drawAlpha(0, 570, &commander);
	drawAlpha(40, 600, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf6[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf6, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf6), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf6[0] = '\0';
		s = s->next;
	}
	s = h;

	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput2_3() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass2_3(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed2_3(1, 1);
	}

}
//有操作更新
void updateWithInput2_3() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡2-3
void game2_3() {
	isPass2_3(0, 1);
	isFailed2_3(0, 1);
	startup2_3();
	while (1) {
		show2_3();
		updateWithoutInput2_3();
		updateWithInput2_3();
		if (isPass2_3(0, 0)) {
			page(10, 1);
			IMAGE c;
			loadimage(&c, _T("./image/background/completed.png"));
			putimage(0, 0, &c);
			FlushBatchDraw();
			Sleep(3000);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed2_3(0, 0)) {
			page(10, 1);
			IMAGE f;
			loadimage(&f, _T("./image/background/failed.png"));
			putimage(0, 0, &f);
			FlushBatchDraw();
			Sleep(3000);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//3-1
//初始化
void startup3_1() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY ONE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr, * t11 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	t11 = (NODE*)malloc(sizeof(NODE));
	h = nullptr;
	s = nullptr;
	p = nullptr;
	r = nullptr;
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}
	if (t11 == NULL) {
		return;
	}

	t1->t.isArmed = 1;
	t1->t.img_x = 644;
	t1->t.img_y = 472;
	t1->t.mid_x = t1->t.img_x + 100;
	t1->t.mid_y = t1->t.img_y + 50;
	strcpy_s(t1->t.img_Path, "./image/enemy/g_t4.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 846;
	t2->t.img_y = 392;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/g_t3.png");

	t3->t.isArmed = 1;
	t3->t.img_x = 776;
	t3->t.img_y = 580;
	t3->t.mid_x = t3->t.img_x + 100;
	t3->t.mid_y = t3->t.img_y + 50;
	strcpy_s(t3->t.img_Path, "./image/enemy/g_t2.png");

	t4->t.isArmed = 0;
	t4->t.img_x = 1056;
	t4->t.img_y = 540;
	t4->t.mid_x = t4->t.img_x + 20;
	t4->t.mid_y = t4->t.img_y + 20;
	strcpy_s(t4->t.img_Path, "./image/enemy/g_s4.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 1196;
	t5->t.img_y = 392;
	t5->t.mid_x = t5->t.img_x + 20;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/g_s3.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1194;
	t6->t.img_y = 482;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/g_s4.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 1218;
	t7->t.img_y = 600;
	t7->t.mid_x = t7->t.img_x + 20;
	t7->t.mid_y = t7->t.img_y + 20;
	strcpy_s(t7->t.img_Path, "./image/enemy/g_s3.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1354;
	t8->t.img_y = 420;
	t8->t.mid_x = t8->t.img_x + 20;
	t8->t.mid_y = t8->t.img_y + 20;
	strcpy_s(t8->t.img_Path, "./image/enemy/g_s3.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1354;
	t9->t.img_y = 610;
	t9->t.mid_x = t9->t.img_x + 20;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/g_s3.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1444;
	t10->t.img_y = 516;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/g_s2.png");

	t11->t.isArmed = 0;
	t11->t.img_x = 1474;
	t11->t.img_y = 390;
	t11->t.mid_x = t11->t.img_x + 100;
	t11->t.mid_y = t11->t.img_y + 50;
	strcpy_s(t11->t.img_Path, "./image/enemy/g_s2.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = t11;
	t11->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show3_1() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-1.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence2, sandbag2, sandbag3;													//绘制敌方固定物品
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	loadimage(&sandbag3, _T("./image/enemy/sandbag3.png"));
	drawAlpha(390, 516, &wire_fence2);
	drawAlpha(390, 636, &wire_fence2);
	drawAlpha(220, 484, &sandbag2);
	drawAlpha(220, 570, &sandbag3);
	drawAlpha(220, 640, &sandbag2);

	static IMAGE commander, cannon_1;												//绘制我方单位
	loadimage(&commander, _T("./image/own/r_c.png"));
	loadimage(&cannon_1, _T("./image/own/r_g1.png"));
	drawAlpha(12, 550, &commander);
	drawAlpha(70, 554, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf7[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf7, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf7), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf7[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput3_1() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass3_1(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed3_1(1, 1);
	}

}
//有操作更新
void updateWithInput3_1() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡3-1
void game3_1() {
	isPass3_1(0, 1);
	isFailed3_1(0, 1);
	startup3_1();
	while (1) {
		show3_1();
		updateWithoutInput3_1();
		updateWithInput3_1();
		if (isPass3_1(0, 0)) {
			page(8, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed3_1(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//3-2
//初始化
void startup3_2() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-2.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, _T("DAY TWO"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr, * t8 = nullptr, * t9 = nullptr, * t10 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}

	t1->t.isArmed = 1;
	t1->t.img_x = 768;
	t1->t.img_y = 600;
	t1->t.mid_x = t1->t.img_x + 100;
	t1->t.mid_y = t1->t.img_y + 30;
	strcpy_s(t1->t.img_Path, "./image/enemy/g_t4.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 1012;
	t2->t.img_y = 600;
	t2->t.mid_x = t2->t.img_x + 100;
	t2->t.mid_y = t2->t.img_y + 30;
	strcpy_s(t2->t.img_Path, "./image/enemy/g_t4.png");

	t3->t.isArmed = 1;
	t3->t.img_x = 1256;
	t3->t.img_y = 600;
	t3->t.mid_x = t3->t.img_x + 100;
	t3->t.mid_y = t3->t.img_y + 30;
	strcpy_s(t3->t.img_Path, "./image/enemy/g_t4.png");

	t4->t.isArmed = 0;
	t4->t.img_x = 808;
	t4->t.img_y = 466;
	t4->t.mid_x = t4->t.img_x + 20;
	t4->t.mid_y = t4->t.img_y + 20;
	strcpy_s(t4->t.img_Path, "./image/enemy/ammo.png");

	t5->t.isArmed = 0;
	t5->t.img_x = 930;
	t5->t.img_y = 424;
	t5->t.mid_x = t5->t.img_x + 20;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/drum.png");

	t6->t.isArmed = 0;
	t6->t.img_x = 1004;
	t6->t.img_y = 424;
	t6->t.mid_x = t6->t.img_x + 20;
	t6->t.mid_y = t6->t.img_y + 20;
	strcpy_s(t6->t.img_Path, "./image/enemy/drum.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 968;
	t7->t.img_y = 330;
	t7->t.mid_x = t7->t.img_x + 20;
	t7->t.mid_y = t7->t.img_y + 20;
	strcpy_s(t7->t.img_Path, "./image/enemy/drum.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 1152;
	t8->t.img_y = 480;
	t8->t.mid_x = t8->t.img_x + 120;
	t8->t.mid_y = t8->t.img_y + 30;
	strcpy_s(t8->t.img_Path, "./image/enemy/truck.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 1468;
	t9->t.img_y = 530;
	t9->t.mid_x = t9->t.img_x + 20;
	t9->t.mid_y = t9->t.img_y + 20;
	strcpy_s(t9->t.img_Path, "./image/enemy/g_s1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1546;
	t10->t.img_y = 530;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/g_c1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show3_2() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-2.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE sandbag, sandbag2;													//绘制敌方固定物品
	loadimage(&sandbag, _T("./image/enemy/sandbag.png"));
	loadimage(&sandbag2, _T("./image/enemy/sandbag2.png"));
	drawAlpha(546, 426, &sandbag);
	drawAlpha(546, 606, &sandbag);
	drawAlpha(644, 546, &sandbag2);

	static IMAGE commander, cannon_1;												//绘制我方单位
	loadimage(&commander, _T("./image/own/r_c.png"));
	loadimage(&cannon_1, _T("./image/own/r_g1.png"));
	drawAlpha(12, 550, &commander);
	drawAlpha(70, 554, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf8[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf8, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf8), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf8[0] = '\0';
		s = s->next;
	}
	s = h;


	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}


	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput3_2() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass3_2(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed3_2(1, 1);
	}

}
//有操作更新
void updateWithInput3_2() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡3-2
void game3_2() {
	isPass3_2(0, 1);
	isFailed3_2(0, 1);
	startup3_2();
	while (1) {
		show3_2();
		updateWithoutInput3_2();
		updateWithInput3_2();
		if (isPass3_2(0, 0)) {
			page(9, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed3_2(0, 0)) {
			page(10, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}

//3-3
//初始化
void startup3_3() {

	initgraph(width(), height());

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-3.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);
	settextstyle(300, 0, _T("STENCIL"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(200, 200, _T("DAY THREE"));
	settextstyle(100, 0, _T("STENCIL"));
	outtextxy(500, 550, _T("按任意键继续"));

	AP_num(10 + player.extra_AP, 1);
	HE_num(10 + player.extra_HE, 1);

	NODE* t1 = nullptr, * t2 = nullptr, * t3 = nullptr, * t4 = nullptr, * t5 = nullptr, * t6 = nullptr, * t7 = nullptr,* t8 = nullptr, * t9 = nullptr, * t10 = nullptr, * t11 = nullptr, * t12 = nullptr, * t13 = nullptr;
	//设置敌方单位
	t1 = (NODE*)malloc(sizeof(NODE));
	t2 = (NODE*)malloc(sizeof(NODE));
	t3 = (NODE*)malloc(sizeof(NODE));
	t4 = (NODE*)malloc(sizeof(NODE));
	t5 = (NODE*)malloc(sizeof(NODE));
	t6 = (NODE*)malloc(sizeof(NODE));
	t7 = (NODE*)malloc(sizeof(NODE));
	t8 = (NODE*)malloc(sizeof(NODE));
	t9 = (NODE*)malloc(sizeof(NODE));
	t10 = (NODE*)malloc(sizeof(NODE));
	t11 = (NODE*)malloc(sizeof(NODE));
	t12 = (NODE*)malloc(sizeof(NODE));
	t13 = (NODE*)malloc(sizeof(NODE));
	h = nullptr;
	s = nullptr;
	p = nullptr;
	r = nullptr;
	h = t1;
	s = h;

	if (t1 == NULL) {
		return;
	}
	if (t2 == NULL) {
		return;
	}
	if (t3 == NULL) {
		return;
	}
	if (t4 == NULL) {
		return;
	}
	if (t5 == NULL) {
		return;
	}
	if (t6 == NULL) {
		return;
	}
	if (t7 == NULL) {
		return;
	}
	if (t8 == NULL) {
		return;
	}
	if (t9 == NULL) {
		return;
	}
	if (t10 == NULL) {
		return;
	}
	if (t11 == NULL) {
		return;
	}
	if (t12 == NULL) {
		return;
	}
	if (t13 == NULL) {
		return;
	}

	t1->t.isArmed = 1;
	t1->t.img_x = 620;
	t1->t.img_y = 444;
	t1->t.mid_x = t1->t.img_x + 120;
	t1->t.mid_y = t1->t.img_y + 50;
	strcpy_s(t1->t.img_Path, "./image/enemy/pillbox.png");

	t2->t.isArmed = 1;
	t2->t.img_x = 840;
	t2->t.img_y = 404;
	t2->t.mid_x = t2->t.img_x + 150;
	t2->t.mid_y = t2->t.img_y + 50;
	strcpy_s(t2->t.img_Path, "./image/enemy/g_t1.png");

	t3->t.isArmed = 1;
	t3->t.img_x = 1060;
	t3->t.img_y = 524;
	t3->t.mid_x = t3->t.img_x + 120;
	t3->t.mid_y = t3->t.img_y + 30;
	strcpy_s(t3->t.img_Path, "./image/enemy/g_t4.png");

	t4->t.isArmed = 1;
	t4->t.img_x = 764;
	t4->t.img_y = 580;
	t4->t.mid_x = t4->t.img_x + 150;
	t4->t.mid_y = t4->t.img_y + 50;
	strcpy_s(t4->t.img_Path, "./image/enemy/g_t1.png");

	t5->t.isArmed = 1;
	t5->t.img_x = 1320;
	t5->t.img_y = 444;
	t5->t.mid_x = t5->t.img_x + 100;
	t5->t.mid_y = t5->t.img_y + 20;
	strcpy_s(t5->t.img_Path, "./image/enemy/g_t3.png");

	t6->t.isArmed = 1;
	t6->t.img_x = 1248;
	t6->t.img_y = 600;
	t6->t.mid_x = t6->t.img_x + 120;
	t6->t.mid_y = t6->t.img_y + 30;
	strcpy_s(t6->t.img_Path, "./image/enemy/g_t4.png");

	t7->t.isArmed = 0;
	t7->t.img_x = 280;
	t7->t.img_y = 20;
	t7->t.mid_x = t7->t.img_x + 100;
	t7->t.mid_y = t7->t.img_y + 50;
	strcpy_s(t7->t.img_Path, "./image/enemy/g_p1.png");

	t8->t.isArmed = 0;
	t8->t.img_x = 460;
	t8->t.img_y = 240;
	t8->t.mid_x = t8->t.img_x + 100;
	t8->t.mid_y = t8->t.img_y + 50;
	strcpy_s(t8->t.img_Path, "./image/enemy/g_p1.png");

	t9->t.isArmed = 0;
	t9->t.img_x = 880;
	t9->t.img_y = 200;
	t9->t.mid_x = t9->t.img_x + 100;
	t9->t.mid_y = t9->t.img_y + 50;
	strcpy_s(t9->t.img_Path, "./image/enemy/g_p1.png");

	t10->t.isArmed = 0;
	t10->t.img_x = 1100;
	t10->t.img_y = 620;
	t10->t.mid_x = t10->t.img_x + 20;
	t10->t.mid_y = t10->t.img_y + 20;
	strcpy_s(t10->t.img_Path, "./image/enemy/g_s3.png");

	t11->t.isArmed = 0;
	t11->t.img_x = 1200;
	t11->t.img_y = 440;
	t11->t.mid_x = t11->t.img_x + 20;
	t11->t.mid_y = t11->t.img_y + 20;
	strcpy_s(t11->t.img_Path, "./image/enemy/g_s2.png");

	t12->t.isArmed = 0;
	t12->t.img_x = 1444;
	t12->t.img_y = 546;
	t12->t.mid_x = t12->t.img_x + 20;
	t12->t.mid_y = t12->t.img_y + 20;
	strcpy_s(t12->t.img_Path, "./image/enemy/g_s4.png");

	t13->t.isArmed = 0;
	t13->t.img_x = 1540;
	t13->t.img_y = 524;
	t13->t.mid_x = t13->t.img_x + 20;
	t13->t.mid_y = t13->t.img_y + 20;
	strcpy_s(t13->t.img_Path, "./image/enemy/g_c1.png");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = t6;
	t6->next = t7;
	t7->next = t8;
	t8->next = t9;
	t9->next = t10;
	t10->next = t11;
	t11->next = t12;
	t12->next = t13;
	t13->next = NULL;

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			putimage(0, 0, &img_Bk1);
			Sleep(1000);
			BeginBatchDraw();
			return;
		}
	}

}
//显示
void show3_3() {

	static IMAGE img_Bk1;																								//加载背景图
	loadimage(&img_Bk1, _T("./image/background/bk_3-3.png"), 0, 0, true);
	putimage(0, 0, &img_Bk1);

	static IMAGE wire_fence1, wire_fence2, sandbag;													//绘制敌方固定物品
	loadimage(&wire_fence1, _T("./image/enemy/wire_fence1.png"));
	loadimage(&wire_fence2, _T("./image/enemy/wire_fence2.png"));
	loadimage(&sandbag, _T("./image/enemy/sandbag.png"));
	drawAlpha(444, 584, &wire_fence1);
	drawAlpha(460, 500, &wire_fence2);
	drawAlpha(540, 422, &sandbag);
	drawAlpha(540, 602, &sandbag);

	static IMAGE our_soldier, cannon_1;												//绘制我方单位
	loadimage(&our_soldier, _T("./image/own/r_s.png"));
	loadimage(&cannon_1, _T("./image/own/r_g2.png"));
	drawAlpha(100, 444, &our_soldier);
	drawAlpha(360, 444, &our_soldier);
	drawAlpha(240, 500, &our_soldier);
	drawAlpha(144, 620, &our_soldier);
	drawAlpha(290, 560, &our_soldier);
	drawAlpha(0, 520, &cannon_1);

	static IMAGE Panel;																								//绘制控制面板
	loadimage(&Panel, _T("./image/background/panel.png"));
	drawAlpha(0, 0, &Panel);

	static char score_char[30];
	static char HE_char[30];
	static char AP_char[30];
	sprintf_s(score_char, "%d", player.score);
	sprintf_s(HE_char, "%d", HE_num(0, 0));
	sprintf_s(AP_char, "%d", AP_num(0, 0));

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, _T("STENCIL"));
	outtextxy(112, 22, CString(player.id));
	outtextxy(112, 52, CString(score_char));
	settextstyle(20, 0, _T("STENCIL"));
	outtextxy(162, 122, CString(HE_char));
	outtextxy(162, 212, CString(AP_char));

	setlinestyle(PS_SOLID, 5);																			  //绘制滑动钮
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(35, -2 * (angle(0, 0) - 150), 5);
	fillcircle(85, -10 * (shell_v(0, 0) - 30), 5);

	setlinecolor(RED);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);
	if (shell_Type(0, 0)) {
		rectangle(110, 210, 160, 260);
	}
	else {
		rectangle(110, 120, 160, 170);
	}

	while (s != NULL)																						//绘制敌方单位
	{
		static IMAGE img_buf;
		static char img_Path_buf9[50];
		static int img_x_buf;
		static int img_y_buf;
		img_x_buf = s->t.img_x;
		img_y_buf = s->t.img_y;
		strcpy_s(img_Path_buf9, s->t.img_Path);
		loadimage(&img_buf, CString(img_Path_buf9), 0, 0, true);
		drawAlpha(img_x_buf, img_y_buf, &img_buf);
		img_Path_buf9[0] = '\0';
		s = s->next;
	}
	s = h;

	if (isFlying(0, 0)) {																								//判断是否有飞行状态的炮弹，如果有，绘制炮弹
		static IMAGE shell_1, shell;
		loadimage(&shell_1, _T("./image/own/shell.png"));
		//rotateimage(&shell, &shell_1, pi / 6);
		//putimage(shell_x, shell_y, &shell);
		if (shell_x(0, 0) >= 30 && shell_x(0, 0) <= width() - 30 && shell_y(0, 0) >= 30 && shell_y(0, 0) <= height() - 30) {
			drawAlpha(shell_x(0, 0) - 15, shell_y(0, 0) - 15, &shell_1);
		}

	}

	/**/
	static int explosion_i = 0;

	static IMAGE explosion_1[6], explosion_2[6];
	loadimage(&explosion_1[0], _T("./image/explosion/1/explosion_1_1.jpg"));
	loadimage(&explosion_1[1], _T("./image/explosion/1/explosion_2_1.jpg"));
	loadimage(&explosion_1[2], _T("./image/explosion/1/explosion_3_1.jpg"));
	loadimage(&explosion_1[3], _T("./image/explosion/1/explosion_4_1.jpg"));
	loadimage(&explosion_1[4], _T("./image/explosion/1/explosion_5_1.jpg"));
	loadimage(&explosion_1[5], _T("./image/explosion/1/explosion_6_1.jpg"));
	loadimage(&explosion_2[0], _T("./image/explosion/1/explosion_1_2.jpg"));
	loadimage(&explosion_2[1], _T("./image/explosion/1/explosion_2_2.jpg"));
	loadimage(&explosion_2[2], _T("./image/explosion/1/explosion_3_2.jpg"));
	loadimage(&explosion_2[3], _T("./image/explosion/1/explosion_4_2.jpg"));
	loadimage(&explosion_2[4], _T("./image/explosion/1/explosion_5_2.jpg"));
	loadimage(&explosion_2[5], _T("./image/explosion/1/explosion_6_2.jpg"));
	if (isHit_show(0, 0)) {
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_1[explosion_i], NOTSRCERASE);
		putimage(hit_x(0, 0) - 100, hit_y(0, 0) - 100, &explosion_2[explosion_i], SRCINVERT);
		explosion_i++;
	}
	if (explosion_i == 6) {
		explosion_i = 0;
		isHit_show(0, 1);
	}

	FlushBatchDraw();
	Sleep(5);

}
//无操作更新
void updateWithoutInput3_3() {

	static double k = 0.00005;														//空气阻力系数
	static double g = 0.05;															    //重力加速度
	static double t = 1.0;																	//炮弹飞行时间

	static double distance_s_t;															//炮弹与目标间距离

	while (s != NULL)																								//检测是否碰撞到敌方单位
	{
		distance_s_t = sqrt(pow((shell_x(0, 0) - s->t.mid_x), 2) + pow((shell_y(0, 0) - s->t.mid_y), 2));
		if (distance_s_t <= 50) {
			isHit(1, 1);
			isHit_show(1, 1);
			break;
		}
		else {
			s = s->next;
		}
	}

	if (toGround_2(shell_x(0, 0), shell_y(0, 0)) <= 0) {																			//检测炮弹是否落地
		isHit(1, 1);
		isHit_show(1, 1);
	}

	s = h;

	if (isHit(0, 0)) {																							//发生碰撞，产生AOE伤害

		mciSendString(_T("close explosion"), NULL, 0, NULL);
		mciSendString(_T("open ./music/explosion.mp3 alias explosion"), NULL, 0, NULL);
		mciSendString(_T("play explosion"), NULL, 0, NULL);

		static int kill_radius;
		if (shell_Type(0, 0)) {
			kill_radius = 100;
		}
		else {
			kill_radius = 250;
		}
		if (shell_Type(0, 0)) {
			AP_num(AP_num(0, 0) - 1, 1);
		}
		else {
			HE_num(HE_num(0, 0) - 1, 1);
		}
		isFlying(0, 1);
		hit_x(shell_x(0, 0), 1);
		hit_y(shell_y(0, 0), 1);
		shell_x(0, 1);
		shell_y(0, 1);

		while (h != NULL) {
			p = h;
			if (sqrt(pow((hit_x(0, 0) - h->t.mid_x), 2) + pow((hit_y(0, 0) - h->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(h->t.isArmed, shell_Type(0, 0))) {
					if (h->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					h = h->next;
					p = nullptr;
					continue;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		p = h;
		r = p;
		s = p;
		while (p != NULL) {
			if (sqrt(pow((hit_x(0, 0) - p->t.mid_x), 2) + pow((hit_y(0, 0) - p->t.mid_y), 2)) <= kill_radius) {
				if (isKilled(p->t.isArmed, shell_Type(0, 0))) {
					if (p->t.isArmed) {
						player.score += 5;
					}
					else {
						player.score += 1;
					}
					p = p->next;
					r->next = p;
					s = nullptr;
					s = p;
					continue;
				}
				else {
					r = p;
					p = p->next;
					s = p;
					continue;
				}
			}
			else {
				r = p;
				p = p->next;
				s = p;
				continue;
			}
		}

		p = h;
		r = p;
		s = p;

		isHit(0, 1);

	}

	if (isFlying(0, 0)) {																				//如果炮弹处于飞行状态，计算下一帧炮弹坐标
		end_t = clock();
		t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		shell_vx(shell_vx(0, 0) - k * shell_v(0, 0) * shell_v(0, 0), 1);
		shell_vy(shell_vy(0, 0) + g * t * t / 2, 1);
		shell_x(shell_x(0, 0) + shell_vx(0, 0), 1);
		shell_y(shell_y(0, 0) + shell_vy(0, 0), 1);
	}

	if (h == NULL) {																		//所有目标被消灭，游戏结束
		isPass3_3(1, 1);
	}

	if (HE_num(0, 0) + AP_num(0, 0) == 0) {
		isFailed3_3(1, 1);
	}

}
//有操作更新
void updateWithInput3_3() {

	static double start_x = 150, start_y = 590;								//发射点
	static double Angle = angle(0, 0) * (PI() / 180.0);
	while (MouseHit()) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 20 && m.x <= 60 && m.y >= 120 && m.y <= 300) {//调整角度
				angle((150 - m.y / 2), 1);
				Angle = angle(0, 0) * (PI() / 180.0);
			}
			if (m.x >= 70 && m.x <= 105 && m.y >= 120 && m.y <= 300) {//调整速度
				shell_v(30 - m.y / 10, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 120 && m.y <= 170) {
				shell_Type(0, 1);
			}
			if (m.x >= 110 && m.x <= 160 && m.y >= 210 && m.y <= 270) {
				shell_Type(1, 1);
			}
			if (m.x >= 30 && m.x <= 100 && m.y >= 330 && m.y <= 400) {//开火
				if ((shell_Type(0, 0) == 0 && HE_num(0, 0) > 0) || (shell_Type(0, 0) == 1 && AP_num(0, 0) > 0)) {
					isFlying(1, 1);
					isHit(0, 1);
					start_t = clock();
					shell_x(start_x, 1);
					shell_y(start_y, 1);
					shell_vx(shell_v(0, 0) * cos(Angle), 1);
					shell_vy(shell_v(0, 0) * sin(2 * PI() - Angle), 1);
				}
			}
		}
	}
}
//关卡3-3
void game3_3() {
	isPass3_3(0, 1);
	isFailed3_3(0, 1);
	startup3_3();
	while (1) {
		show3_3();
		updateWithoutInput3_3();
		updateWithInput3_3();
		if (isPass3_3(0, 0)) {
			page(12, 1);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
		if (isFailed3_3(0, 0)) {
			page(10, 1);
			IMAGE f;
			loadimage(&f, _T("./image/background/failed.png"));
			putimage(0, 0, &f);
			FlushBatchDraw();
			Sleep(3000);
			EndBatchDraw();
			setbkcolor(BLACK);
			cleardevice();
			return;
		}
	}
}
 
