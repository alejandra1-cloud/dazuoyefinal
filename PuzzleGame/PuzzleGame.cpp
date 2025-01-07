// PuzzleGame.cpp : 定义应用程序的入口点。
//

#include "PuzzleGame.h"
using namespace std;
#include <string.h>
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_HelpButton;	    //help按钮图像资源
HBITMAP bmp_pausebutton;   //pause按钮图像资源
HBITMAP bmp_restartb;   //pause1按钮图像资源
HBITMAP bmp_returnb;
HBITMAP bmp_returnb1;
HBITMAP bmp_pausemap;   //pausemap按钮图像资源
HBITMAP bmp_Player;			//玩家图像
HBITMAP bmp_NPC_MAN1;		//各位NPC图像
HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_map;			//地图砖块图像
HBITMAP bmp_heart;			//地图砖块图像


HBITMAP bmp_dialog;			//对话框背景图像
HBITMAP bmp_monster1;		//怪物1图像
HBITMAP bmp_monster2;		//怪物1图像
HBITMAP bmp_attack;			//攻击特效图像
HBITMAP bmp_helpmap1;
HBITMAP bmp_stage3;




Stage* currentStage = NULL; //当前场景状态
vector<NPC*> npcs;			//NPC列表
vector<Monster*> monsters;	//怪物列表
Player* player = NULL;		//玩家
vector<Button*> buttons;	//按钮	
Attack* attack = NULL;		//攻击特效

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyAttackDown = false;
bool in_conversation = false;	//当前游戏处在对话状态
const wchar_t* converstaion_content = nullptr;	//当前对话的内容

//TODO 更多的全局变量


//帧
int PLAYER_FRAMES_HOLD[] = { 0 };
int PLAYER_FRAMES_HOLD_COUNT = sizeof(PLAYER_FRAMES_HOLD) / sizeof(int);
int NPC_FRAMES_HOLD[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int NPC_FRAMES_HOLD_COUNT = sizeof(NPC_FRAMES_HOLD) / sizeof(int);
int FRAMES_WALK[] = { 0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3, };
int FRAMES_WALK_COUNT = sizeof(FRAMES_WALK) / sizeof(int);
int ATTACK_FRAMES[] = { 0,0,0,0,1,1,1,1,2,2,2,2 };
int ATTACK_FRAMES_COUNT = sizeof(ATTACK_FRAMES) / sizeof(int);

//地图
//0空地 1草 2红花 3+7树 4/5/6/8/9/10/12/13/14土地 11蓝花 15路牌
int map_stage1[20][28] = {
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,},
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 5, 5, 6, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12,13,13,13,14, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,},
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,},
};
//第二个关卡地图
int map_stage2[20][28] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
int map_STAGE_help[20][28] = {
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,},
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 5, 5, 6, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 9, 9,10, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12,13,13,13,14, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 2, 2, 2, 2,11,11,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,},
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,},
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,},
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,},
};
int map_stage3[20][28] = {

	{91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118},
{155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182},
{219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246},
{283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310},
{347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374},
{411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438},
{475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502},
{539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566},
{603, 604, 605, 606, 607, 608, 609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630},
{667, 668, 669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 1275, 1275,1275, 1275, 1275, 1275, 1275, 1275, 1275, 1275,1275},
{731, 732, 733, 734, 735, 736, 737, 738, 739, 740, 741, 742, 743, 744, 745, 746, 681, 681, 681, 750, 751, 752, 753, 754, 755, 756, 757, 758},
{795, 796, 797, 798, 799, 800, 801, 802, 803, 804, 805, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822},
{859, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871, 872, 873, 874, 875, 876, 877, 878, 879, 880, 881, 882, 883, 884, 885, 886},
{923, 924, 925, 926, 927, 928, 929, 930, 931, 932, 933, 934, 935, 935, 935, 935, 939, 940, 941, 942, 943, 944, 945, 946, 947, 948, 949, 950},
{861, 603, 861, 990, 991, 992, 993, 994, 995, 996, 997, 998, 999, 999,999, 999, 999, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014},
{861, 861, 861, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1063, 1063, 1063, 1063, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078},
{861, 861, 861, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125, 1126, 1126, 1126, 1126, 1126, 1127, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, 1140, 1141, 1142},
{861, 861, 861, 861, 861, 861, 861, 1186, 1187, 1188, 1189, 1190, 1126, 1126, 1126, 1126, 1126, 1127, 1197, 1198, 1199, 1200, 1201, 1202, 1203, 1204, 1205, 1206},
{861, 861, 861, 861, 861, 861, 861, 1250, 1251, 1252, 1253, 1254, 1254, 1254, 1254, 1254, 1254, 1191, 1261, 1262, 1263, 1264, 1265, 1266, 1267, 1268, 1269, 1270},
{1307, 1308, 1309, 1310, 1311, 1312, 1313, 1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 1322, 1323, 1254, 1325, 1326, 1327, 1328, 1329, 1330, 1331, 1332, 1333, 1334},


};
int map[20][28] = { 0 };	//存储当前关卡的地图


// TODO: 在此添加其它全局变量

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PUZZLEGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PUZZLEGAME));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PUZZLEGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PUZZLEGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);
	SetMenu(hWnd, NULL);     //隐藏菜单栏
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_Background = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BACKGROUND));
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_STARTBUTTON));
	bmp_pausebutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_pausebutton));
	bmp_HelpButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HELP_BUTTON));
	bmp_Player = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_PLAYER));
	bmp_NPC_MAN1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_NPC_MAN1));
	bmp_map = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MAP));
	bmp_stage3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_map2));
	bmp_dialog = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_DIALOG));
	bmp_monster1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_MONSTER1));
	bmp_monster2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_monster2));
	bmp_attack = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ATTACK));
	bmp_helpmap1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_helpmap1));
	bmp_restartb = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_restartb));
	bmp_returnb = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_returnb));
	bmp_heart = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_heart));
	//bmp_returnb1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_returnb1));




	//添加按钮
	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2);

	//
	Button* helpButton = CreateButton(BUTTON_HELP, bmp_HelpButton, BUTTON_HELP_WIDTH, BUTTON_HELP_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2 + 50, ((WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2) + 80);

	Button* pausebutton = CreateButton(BUTTON_pausebutton, bmp_pausebutton, BUTTON_pausebutton_WIDTH, BUTTON_pausebutton_HEIGHT,
		(WINDOW_WIDTH - BUTTON_pausebutton_WIDTH) / 2 + 400, 0);
	Button* restartb = CreateButton(BUTTON_restartb, bmp_restartb, BUTTON_restartb_WIDTH, BUTTON_restartb_HEIGHT,
		(WINDOW_WIDTH - BUTTON_restartb_WIDTH) / 2 - 100, 200);
	Button* returnb = CreateButton(BUTTON_returnb, bmp_returnb, BUTTON_returnb_WIDTH, BUTTON_returnb_HEIGHT,
		(WINDOW_WIDTH - BUTTON_returnb_WIDTH) / 2 + 100, 200);
	Button* returnb1 = CreateButton(BUTTON_returnb1, bmp_returnb, BUTTON_returnb1_WIDTH, BUTTON_returnb1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_returnb1_WIDTH) / 2 - 350, 550);

	buttons.push_back(startButton);
	buttons.push_back(helpButton);
	buttons.push_back(pausebutton);
	buttons.push_back(restartb);
	buttons.push_back(returnb);
	buttons.push_back(returnb1);

	attack = CreateAttack();




	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_SPACE:
		break;
	case 'J':
		keyAttackDown = true;
		attack->visible = true;
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_SPACE:
		HandleConversationEvents(hWnd);
		break;
	case 'J':
		keyAttackDown = false;
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

int stage_last;
// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID) {
				case BUTTON_STARTGAME:

				{
					//TODO：判断进入哪个关卡
					InitStage(hWnd, STAGE_1);
				}
				break;
				case BUTTON_HELP:

				{
					//TODO：判断进入哪个关卡
					InitStage(hWnd, STAGE_help);
					break;
				}
				case BUTTON_pausebutton:
				{
					stage_last = currentStage->stageID;
					currentStage->timerOn = false;
					for (int i = 0; i < buttons.size(); i++)
					{
						Button* button = buttons[i];
						if (button->buttonID == BUTTON_restartb || button->buttonID == BUTTON_returnb)//开始游戏按钮ID
							button->visible = true;
						//else button->visible = false;

					}

					InvalidateRect(hWnd, NULL, FALSE);
					break;
				}
				case BUTTON_restartb:
				{
					InitStage(hWnd, stage_last);
					break;
				}

				case BUTTON_returnb:
				{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				case BUTTON_returnb1:
				{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}

				}
			}

		}
	}

}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	UpdatePlayer(hWnd);
	UpdateNPCs(hWnd);
	UpdateMonsters(hWnd);
	UpdateMaps(hWnd);
	UpdateAttack(hWnd);
	CheckBoundary(hWnd);
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}
//更新玩家状态
void UpdatePlayer(HWND hWnd) {
	if (player->health < 0) {
		InitStage(hWnd, STAGE_STARTMENU);
		player->health = 40;
	}
	//如果键盘按下，设置状态为WALK
	if (keyLeftDown || keyUpDown || keyRightDown || keyDownDown) {
		player->state = UNIT_STATE_WALK;
		player->frame_sequence = FRAMES_WALK;
		player->frame_count = FRAMES_WALK_COUNT;
		if (keyLeftDown) {
			player->direction = UNIT_DIRECT_LEFT;
		}
		else if (keyUpDown) {
			player->direction = UNIT_DIRECT_UP;
		}
		else if (keyRightDown) {
			player->direction = UNIT_DIRECT_RIGHT;
		}
		else if (keyDownDown) {
			player->direction = UNIT_DIRECT_DOWN;
		}
		player->frame_row = player->direction;
	}
	else {
		player->state = UNIT_STATE_HOLD;
		player->frame_sequence = PLAYER_FRAMES_HOLD;
		player->frame_count = PLAYER_FRAMES_HOLD_COUNT;
	}
	//更新位置
	if (player->state == UNIT_STATE_WALK) {
		switch (player->direction) {
		case UNIT_DIRECT_LEFT:
			player->x -= player->vx;
			break;
		case UNIT_DIRECT_UP:
			player->y -= player->vy;
			break;
		case UNIT_DIRECT_RIGHT:
			player->x += player->vx;
			break;
		case UNIT_DIRECT_DOWN:
			player->y += player->vy;
			break;
		default:
			break;
		};
	}

	//动画运行到下一帧
	player->frame_id++;
	player->frame_id = player->frame_id % player->frame_count;
	player->frame_column = player->frame_sequence[player->frame_id];
}
//更新NPC状态
void UpdateNPCs(HWND hWnd) {

	//顺次更新每个npc
	for (int i = 0; i < npcs.size(); i++) {
		//动画运行到下一帧
		npcs[i]->frame_id++;
		npcs[i]->frame_id = npcs[i]->frame_id % npcs[i]->frame_count;
		npcs[i]->frame_column = npcs[i]->frame_sequence[npcs[i]->frame_id];

	}
}
void UpdateMonsters(HWND hWnd)
{
	//顺次更新每个怪物
	for (int i = 0; i < monsters.size(); i++) {
		Monster* monster = monsters[i];
		if (rand() % 20 == 0) {
			if (rand() % 3 == 0) {	//转身
				monster->frame_column = rand() % 4;
				monster->direction = monster->frame_column;
			}
			else {					//移动
				switch (monster->frame_column)
				{
				case 0:		//down
					monster->y += MOSTER_SIZE_Y;
					monster->direction = UNIT_DIRECT_DOWN;
					break;
				case 1:		//right
					monster->x += MOSTER_SIZE_X;
					monster->direction = UNIT_DIRECT_RIGHT;
					break;
				case 2:		//left
					monster->x -= MOSTER_SIZE_X;
					monster->direction = UNIT_DIRECT_LEFT;
					break;
				case 3:		//up
					monster->y -= MOSTER_SIZE_Y;
					monster->direction = UNIT_DIRECT_UP;
					break;
				default:
					break;
				}
			}
		}
		if (monster->visible) {

			monster->is_attacking = false;
			// Check for collisions with player and NPCs
			MonsterAttackPlayer(monster, player);
			for (NPC* npc : npcs) {
				MonsterAttackNPC(monster, npc);
			}

			// Additional monster update logic (e.g., animation)
		}
	}
}
// 地图切换逻辑
void UpdateMaps(HWND hWnd)
{
	//走到地图边界，切换到map2
	if (currentStage->stageID == STAGE_1 && player->y <= 0 && map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_Y] == 0)
	{
		InitStage(hWnd, STAGE_2);
		player->y = WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y;
	}
	if (currentStage->stageID == STAGE_2 && player->y <= 0 && map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_Y] == 0)
	{
		InitStage(hWnd, STAGE_3);
		player->y = WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y;
	}
	if (currentStage->stageID == STAGE_2 && player->y >= WINDOW_HEIGHT - 40 && map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_Y] == 0)
	{
		InitStage(hWnd, STAGE_1);
		player->y = 0.5 * HUMAN_SIZE_Y;
	}
	if (currentStage->stageID == STAGE_3 && player->y >= WINDOW_HEIGHT - 40 && map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_Y] == 0)
	{
		InitStage(hWnd, STAGE_2);
		player->y = 0.5 * HUMAN_SIZE_Y;
	}
}
void CheckBoundary(HWND hWnd)
{
	if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2)
		if (player->x - 0.5 * HUMAN_SIZE_X < 0) {
			player->x = 0.5 * HUMAN_SIZE_X;
			player->direction = UNIT_DIRECT_RIGHT;
		}
		else if (player->x > WINDOW_WIDTH - 20 - 0.5 * HUMAN_SIZE_X) {
			player->x = WINDOW_WIDTH - 20 - 0.5 * HUMAN_SIZE_X;
			player->direction = UNIT_DIRECT_LEFT;
		}

		else if (player->y > WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y && currentStage->stageID == STAGE_1) {
			player->y = WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y;
			player->direction = UNIT_DIRECT_DOWN;
		}
	/*else if (player->y < 0.5 * HUMAN_SIZE_Y) {
		player->y = 0.5 * HUMAN_SIZE_Y;
		player->direction = UNIT_DIRECT_UP;
	}*/

		else if (map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_X] == 3 || map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_X] == 7) {
			if (player->direction == UNIT_DIRECT_DOWN) {
				player->y -= player->vy;
				player->direction = UNIT_DIRECT_UP;
			}
			else if (player->direction == UNIT_DIRECT_UP) {
				player->y += player->vy;
				player->direction = UNIT_DIRECT_DOWN;
			}
			else if (player->direction == UNIT_DIRECT_LEFT) {
				player->x += player->vx;
				player->direction = UNIT_DIRECT_RIGHT;
			}
			else if (player->direction == UNIT_DIRECT_RIGHT) {
				player->x -= player->vx;
				player->direction = UNIT_DIRECT_LEFT;
			}
		}

	if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2)
		for (auto monster : monsters) {
			if (monster->x - 0.5 * MOSTER_SIZE_X < 0) {
				monster->x = 0.5 * MOSTER_SIZE_X;
				monster->direction = UNIT_DIRECT_RIGHT;
			}
			else if (monster->x > WINDOW_WIDTH - 20 - 0.5 * MOSTER_SIZE_X) {
				monster->x = WINDOW_WIDTH - 20 - 0.5 * MOSTER_SIZE_X;
				monster->direction = UNIT_DIRECT_LEFT;
			}

			else if (monster->y > WINDOW_HEIGHT - 40 - 0.5 * MOSTER_SIZE_Y) {
				monster->y = WINDOW_HEIGHT - 40 - 0.5 * MOSTER_SIZE_Y;
				monster->direction = UNIT_DIRECT_DOWN;
			}

			else if (monster->y - 0.5 * MOSTER_SIZE_Y < 0) {
				monster->y = 0.5 * MOSTER_SIZE_Y;
				monster->direction = UNIT_DIRECT_UP;
			}
			else if (map[monster->y / BLOCK_SIZE_Y][monster->x / BLOCK_SIZE_X] == 3 || map[monster->y / BLOCK_SIZE_Y][monster->x / BLOCK_SIZE_X] == 7) {
				if (monster->direction == UNIT_DIRECT_DOWN) {
					monster->y -= monster->vy;
					monster->direction = UNIT_DIRECT_UP;
				}
				else if (monster->direction == UNIT_DIRECT_UP) {
					monster->y += monster->vy;
					monster->direction = UNIT_DIRECT_DOWN;
				}
				else if (monster->direction == UNIT_DIRECT_LEFT) {
					monster->x += monster->vx;
					monster->direction = UNIT_DIRECT_RIGHT;
				}
				else if (monster->direction == UNIT_DIRECT_RIGHT) {
					monster->x -= monster->vx;
					monster->direction = UNIT_DIRECT_LEFT;
				}
			}

		}
	if (currentStage->stageID == STAGE_3)
	{
		int id = map[player->y / BLOCK_SIZE_Y][player->x / BLOCK_SIZE_X];
		int y = id / 64;
		int x = id % 64;

		if (player->x - 0.5 * HUMAN_SIZE_X < 0) {
			player->x = 0.5 * HUMAN_SIZE_X;
			player->direction = UNIT_DIRECT_RIGHT;
		}
		else if (player->x > WINDOW_WIDTH - 20 - 0.5 * HUMAN_SIZE_X) {
			player->x = WINDOW_WIDTH - 20 - 0.5 * HUMAN_SIZE_X;
			player->direction = UNIT_DIRECT_LEFT;
		}

		/*else if (player->y > WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y) {
			player->y = WINDOW_HEIGHT - 40 - 0.5 * HUMAN_SIZE_Y;
			player->direction = UNIT_DIRECT_DOWN;
		}*/
		else if (player->y < 0.5 * HUMAN_SIZE_Y) {
			player->y = 0.5 * HUMAN_SIZE_Y;
			player->direction = UNIT_DIRECT_UP;
		}
		else if (y >= 0 && y < 8 && x >= 32 && x <= 40) {
			if (player->direction == UNIT_DIRECT_DOWN) {
				player->y -= player->vy;
				player->direction = UNIT_DIRECT_UP;
			}
			else if (player->direction == UNIT_DIRECT_UP) {
				player->y += player->vy;
				player->direction = UNIT_DIRECT_DOWN;
			}
			else if (player->direction == UNIT_DIRECT_LEFT) {
				player->x += player->vx;
				player->direction = UNIT_DIRECT_RIGHT;
			}
			else if (player->direction == UNIT_DIRECT_RIGHT) {
				player->x -= player->vx;
				player->direction = UNIT_DIRECT_LEFT;
			}
		}
	}
}



void UpdateAttack(HWND hWnd) {
	if (attack->visible) {
		// Animation to the next frame
		attack->frame_id++;
		attack->frame_id = attack->frame_id % attack->frame_count;
		attack->frame_column = attack->frame_sequence[attack->frame_id];
		if (!keyAttackDown && attack->frame_id == 0)
			attack->visible = false;
	}
	for (int i = 0; i < monsters.size();++i) {
		Monster* monster = monsters[i];
		monster->attack->frame_id++;
		monster->attack->frame_id = monster->attack->frame_id % monster->attack->frame_count;
		monster->attack->frame_column = monster->attack->frame_sequence[monster->attack->frame_id];
		if (!monster->is_attacking && monster->attack->frame_id == 0)
			monster->attack->visible = false;

	}
	if (player != NULL) {
		switch (player->direction) {
		case UNIT_DIRECT_RIGHT:
			attack->x = player->x + HUMAN_SIZE_X / 2 + ATTACK_SIZE_X / 2;
			attack->y = player->y;
			break;
		case UNIT_DIRECT_LEFT:
			attack->x = player->x - HUMAN_SIZE_X / 2 - ATTACK_SIZE_X / 2;
			attack->y = player->y;
			break;
		case UNIT_DIRECT_UP:
			attack->x = player->x;
			attack->y = player->y - HUMAN_SIZE_Y / 2 - ATTACK_BITMAP_SIZE_Y / 2;
			break;
		case UNIT_DIRECT_DOWN:
			attack->x = player->x;
			attack->y = player->y + HUMAN_SIZE_Y / 2 + ATTACK_SIZE_Y / 2;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < monsters.size(); i++) {
		Monster* monster = monsters[i];
		switch (monster->direction) {
		case UNIT_DIRECT_RIGHT:
			monster->attack->x = monster->x + MOSTER_SIZE_X / 2 + ATTACK_SIZE_X / 2;
			monster->attack->y = monster->y;
			break;
		case UNIT_DIRECT_LEFT:
			monster->attack->x = monster->x - MOSTER_SIZE_X / 2 - ATTACK_SIZE_X / 2;
			monster->attack->y = monster->y;
			break;
		case UNIT_DIRECT_UP:
			monster->attack->x = monster->x;
			monster->attack->y = monster->y - MOSTER_SIZE_Y / 2 - ATTACK_BITMAP_SIZE_Y / 2;
			break;
		case UNIT_DIRECT_DOWN:
			monster->attack->x = monster->x;
			monster->attack->y = monster->y + MOSTER_SIZE_Y / 2 + ATTACK_SIZE_Y / 2;
			break;
		default:
			break;
		}
	}

	// Collision detection
	if (attack->visible && attack->frame_id == 1) {
		for (Monster* monster : monsters) {
			if (monster->visible &&
				((attack->x <= monster->x && monster->x <= attack->x + ATTACK_SIZE_X) || (monster->x <= attack->x && attack->x <= monster->x + ATTACK_SIZE_X)) &&
				((attack->y <= monster->y && monster->y <= attack->y + ATTACK_SIZE_Y) || (monster->y <= attack->y && attack->y <= monster->y + ATTACK_SIZE_Y))) {
				monster->health -= 3;
				if (monster->health <= 0) {
					monster->alive = false;
					attack ->visible = false;
					monster->visible = false;
					switch (monster->monsterID) {
					case MONSTER_CAT_ID:
						PlaySound(L"killm.wav", NULL, SND_SYNC);
						for (NPC* npc : npcs) {
							if (npc->npcID == NPC_MAN1_ID) {
								npc->task_complete = true;
							}
						}
						break;
					case MONSTER_2:
						PlaySound(L"killm.wav", NULL, SND_SYNC);
						for (NPC* npc : npcs) {
							if (npc->npcID == NPC_MAN1_ID) {
								npc->task_complete = true;
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
}




void MonsterAttackPlayer(Monster* monster, Player* player) {
	if (!monster->visible 
		|| abs(monster->x - player->x) >= ATTACK_SIZE_X || abs(monster->y - player->y) >= ATTACK_SIZE_Y) {

		return;
	}		player->health -= 1;
			monster->is_attacking = true;// Reduce player's health
			
	
	
}

void MonsterAttackNPC(Monster* monster, NPC* npc) {
	if (!monster->visible
		|| abs(monster->x - npc->x) >= ATTACK_SIZE_X || abs(monster->y - npc->y) >= ATTACK_SIZE_Y) {


		return;
	}
	npc->health -= 1;
	monster->is_attacking = true;// Reduce player's health
	
}



//抬起空格时触发，开启对话
void HandleConversationEvents(HWND hWnd)
{
	//当前已经开启对话，再按一次空格关闭
	if (in_conversation) {
		in_conversation = false;
		return;
	}
	//player与npc做碰撞检测，判断与哪个npc对话
	for (int i = 0; i < npcs.size(); i++) {
		NPC* npc = npcs[i];
		if (((player->x <= npc->x && npc->x <= player->x + HUMAN_SIZE_X) || (npc->x <= player->x && player->x <= npc->x + HUMAN_SIZE_X)) &&
			((player->y <= npc->y && npc->y <= player->y + HUMAN_SIZE_Y) || (npc->y <= player->y && player->y <= npc->y + HUMAN_SIZE_X))) {
			in_conversation = true;
			if (!npc->task_complete) {
				converstaion_content = npc->conversations_before[npc->next_conversation_id];
				if (npc->next_conversation_id < npc->conversations_before.size() - 1)
					npc->next_conversation_id++;	//npc的这句话已经说完，下次该说下一句话了；如果已经说到最后一句话了，则一直重复
			}
			else {
				converstaion_content = npc->conversations_after[npc->next_conversation_id];
				if (npc->next_conversation_id < npc->conversations_after.size() - 1)
					npc->next_conversation_id++;	//npc的这句话已经说完，下次该说下一句话了；如果已经说到最后一句话了，则一直重复
			}

		}
	}
	if (currentStage->stageID == STAGE_3)
	{
		if (((player->x <= 13 * BLOCK_SIZE_X && 13 * BLOCK_SIZE_X <= player->x + HUMAN_SIZE_X) || (13 * BLOCK_SIZE_X <= player->x && player->x <= 13 * BLOCK_SIZE_X + HUMAN_SIZE_X)) &&
			((player->y <= 10 * BLOCK_SIZE_Y && player->y <= 10 * BLOCK_SIZE_Y <= player->y + HUMAN_SIZE_Y) || (player->y <= 10 * BLOCK_SIZE_Y <= player->y && player->y <= player->y <= 10 * BLOCK_SIZE_Y + HUMAN_SIZE_X)))
		{
			in_conversation = true;
			converstaion_content = L"This is a conversation.";
		}
	}
}


//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = false;
	return button;
}

// 添加主角函数
Player* CreatePlayer(int x, int y)
{
	Player* player = new Player();
	player->img = bmp_Player;
	player->x = x;
	player->y = y;
	player->direction = UNIT_DIRECT_RIGHT;
	player->vx = 5;
	player->vy = 5;

	player->state = UNIT_STATE_HOLD;
	player->frame_row = player->direction;
	player->frame_column = 0;
	player->frame_sequence = PLAYER_FRAMES_HOLD;
	player->frame_count = PLAYER_FRAMES_HOLD_COUNT;
	player->frame_id = 0;

	return player;
}
// 添加NPC函数
NPC* CreateNPC(int x, int y, int npc_id)
{
	NPC* npc = new NPC();
	npc->npcID = npc_id;
	npc->visible = true;
	npc->task_complete = false;
	npc->x = x;
	npc->y = y;
	npc->direction = UNIT_DIRECT_DOWN;
	npc->vx = 0;
	npc->vy = 0;
	npc->state = UNIT_STATE_HOLD;
	npc->frame_row = npc->direction;
	npc->frame_column = 0;
	npc->frame_sequence = NPC_FRAMES_HOLD;
	npc->frame_count = NPC_FRAMES_HOLD_COUNT;
	npc->frame_id = 0;
	npc->next_conversation_id = 0;
	//根据不同NPC初始化不同的图像和对话
	switch (npc_id)
	{
	case NPC_MAN1_ID: {
		npc->img = bmp_NPC_MAN1;
		npc->conversations_before.push_back(L"你好！我是花花镇的居民，很高兴认识你。");
		npc->conversations_before.push_back(L"最近花花镇有些不太平，幽暗森林里时不时会传来一些声响，镇子里的人们每天都惴惴不安，可以请你帮忙调查一下吗？");
		npc->conversations_before.push_back(L"你说幽暗森林怎么走？往城镇上方直走就是啦。");
		npc->conversations_after.push_back(L"这样啊，原来是有一只猫妖跑到森林里了，谢谢你把它赶走，这下镇子里又可以太平了。");
		break;
	}
	default:
		break;
	}

	return npc;
}

Monster* CreateMonster(int x, int y, int monster_id)
{
	Monster* monster = new Monster();
	monster->monsterID = monster_id;
	monster->visible = true;
	monster->task_complete = false;
	monster->x = x;
	monster->y = y;
	monster->direction = UNIT_DIRECT_DOWN;
	monster->attack=CreateAttack();
	monster->attack->img = bmp_attack;
	monster->vx = 0;
	monster->vy = 0;
	monster->state = UNIT_STATE_HOLD;
	monster->frame_row = monster->direction;
	monster->frame_column = 0;
	monster->frame_sequence = NPC_FRAMES_HOLD;
	monster->frame_count = NPC_FRAMES_HOLD_COUNT;
	monster->frame_id = 0;
	monster->next_conversation_id = 0;
	monster->health = 2;
	monster->alive = true;
	//根据不同ID初始化不同的图像和对话
	switch (monster_id)
	{
	case MONSTER_CAT_ID:
	{
		monster->img = bmp_monster1;
		monster->conversations_before.push_back(L"喵喵喵。");
		break;
	}
	case MONSTER_2:
	{
		monster->img = bmp_monster2;
		monster->conversations_before.push_back(L"喵喵喵。");
		break;
	}
	default:
		break;
	}

	return monster;
}

Attack* CreateAttack()
{
	Attack* attack = new Attack();
	attack->img = bmp_attack;
	attack->visible = false;

	attack->frame_row = 0;
	attack->frame_column = 0;
	attack->frame_sequence = ATTACK_FRAMES;
	attack->frame_count = ATTACK_FRAMES_COUNT;
	attack->frame_id = 0;

	return attack;
}


// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例

	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;

	if (stageID == STAGE_STARTMENU) {
		currentStage->bg = bmp_Background;// add backgroud
		currentStage->timerOn = false;
		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)//add button
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_HELP)
				button->visible = true;
			else
				button->visible = false;
		}
	}

	else if (stageID == STAGE_help) {
		currentStage->bg = bmp_helpmap1;// add backgroud
		currentStage->timerOn = false;
		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)//add button
		{
			Button* button = buttons[i];
			//button->visible = false;
			if (button->buttonID == BUTTON_returnb1)
				button->visible = true;
			else
				button->visible = false;
		}
	}

	else if (stageID == STAGE_pause) {
		currentStage->bg = bmp_pausebutton;// add backgroud
		currentStage->timerOn = false;
		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)//add button
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_HELP)
				button->visible = true;
			else
				button->visible = false;
		}
	}



	//TODO：添加多个游戏场景
	else if (stageID == STAGE_1)
	{
		currentStage->bg = bmp_Background;
		currentStage->timerOn = true;
		memcpy(map, map_stage1, sizeof(map));	//初始化地图
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_pausebutton)
				buttons[i]->visible = true;
			else
				buttons[i]->visible = false;
		}
		if (player == NULL)
			player = CreatePlayer(200, 200);					//第一次调用：初始化player
		if (npcs.size() == 0) {
			npcs.push_back(CreateNPC(625, 200, NPC_MAN1_ID));	//第一次调用：初始化NPC
		}
		monsters.clear();
		//NPC的可见性
		for (int i = 0; i < npcs.size(); i++)
		{
			NPC* npc = npcs[i];
			if (true) //TODO：加载游戏界面需要的按钮
				npc->visible = true;
			else
				npc->visible = false;
		}
		//Monster的可见性
		for (int i = 0; i < monsters.size(); i++)
		{
			Monster* monster = monsters[i];
			if (false) //TODO：加载游戏界面需要的按钮
				monster->visible = true;
			else
				monster->visible = false;
		}
	}
	else if (stageID == STAGE_2)
	{
		currentStage->bg = bmp_Background;
		currentStage->timerOn = true;
		memcpy(map, map_stage2, sizeof(map));
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_pausebutton)
				button->visible = true;
			else
				button->visible = false;
		}
		if (player == NULL)
			player = CreatePlayer(200, 200);
		monsters.clear();
		if (monsters.size() == 0) {
			monsters.push_back(CreateMonster(495, 205, MONSTER_CAT_ID));//初始化Monster
			monsters.push_back(CreateMonster(495, 205, MONSTER_2));
		}
		//NPC的可见性
		for (int i = 0; i < npcs.size(); i++)
		{
			NPC* npc = npcs[i];
			if (false) //TODO：加载游戏界面需要的按钮
				npc->visible = true;
			else
				npc->visible = false;
		}
		//Monster的可见性
		for (int i = 0; i < monsters.size(); i++)
		{
			Monster* monster = monsters[i];
			if (true) //TODO：加载游戏界面需要的按钮
				monster->visible = true;
			else
				monster->visible = false;
		}
	}
	else if (stageID == STAGE_3)
	{
		currentStage->bg = bmp_stage3;
		currentStage->timerOn = true;
		memcpy(map, map_stage3, sizeof(map));
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_pausebutton)
				button->visible = true;
			else
				button->visible = false;
		}
		if (player == NULL)
			player = CreatePlayer(200, 200);
		monsters.clear();
		//NPC的可见性
		for (int i = 0; i < npcs.size(); i++)
		{
			NPC* npc = npcs[i];
			if (false) //TODO：加载游戏界面需要的按钮
				npc->visible = true;
			else
				npc->visible = false;
		}
		//Monster的可见性
		for (int i = 0; i < monsters.size(); i++)
		{
			Monster* monster = monsters[i];
			if (true) //TODO：加载游戏界面需要的按钮
				monster->visible = true;
			else
				monster->visible = false;
		}
	}



	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}





// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);


	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) {
		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		TransparentBlt(
			hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, BG_BITMAP_WIDTH, BG_BITMAP_HEIGHT,
			RGB(255, 255, 255));

	}
	else
		if (currentStage->stageID == STAGE_help) {
			// 绘制背景到缓存
			SelectObject(hdc_loadBmp, currentStage->bg);
			TransparentBlt(
				hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
				hdc_loadBmp, 0, 0, BG_BITMAP_helpmap1_WIDTH, BG_BITMAP_helpmap1_height,
				RGB(255, 255, 255));

		}

		else
		{
			if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_2) //TODO：添加多个游戏场景
			{
				//绘制地图
				SelectObject(hdc_loadBmp, bmp_map);
				for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
					for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
						TransparentBlt(
							hdc_memBuffer,
							j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
							BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
							hdc_loadBmp,
							(map[i][j] % 4) * BLOCK_BITMAP_SIZE_X,						// 位图上起始绘制点
							(map[i][j] / 4) * BLOCK_BITMAP_SIZE_Y,
							BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,					// 位图上绘制宽度高度
							RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
					}
				}


			}
			else if (currentStage->stageID == STAGE_3) //TODO：添加多个游戏场景
			{
				//绘制地图
				SelectObject(hdc_loadBmp, bmp_map);
				for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
					for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
						if (i == 10 && j == 13)
						{
							TransparentBlt(
								hdc_memBuffer,
								j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
								BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
								hdc_loadBmp,
								3 * BLOCK_BITMAP_SIZE_X,						// 位图上起始绘制点
								3 * BLOCK_BITMAP_SIZE_Y,
								BLOCK_BITMAP_SIZE_X, BLOCK_BITMAP_SIZE_Y,					// 位图上绘制宽度高度
								RGB(255, 255, 255));
						}
					}
				}
				SelectObject(hdc_loadBmp, bmp_stage3);
				for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
					for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
						if (i == 10 && j == 13)
						{
							continue;
						}
						TransparentBlt(
							hdc_memBuffer,
							j * BLOCK_SIZE_X, i * BLOCK_SIZE_Y,							// 界面上起始绘制点
							BLOCK_SIZE_X, BLOCK_SIZE_Y,									// 界面上绘制宽度高度
							hdc_loadBmp,
							(map[i][j] % 64) * BLOCK_BITMAP_SIZE_X2,						// 位图上起始绘制点
							(map[i][j] / 64) * BLOCK_BITMAP_SIZE_Y2,
							BLOCK_BITMAP_SIZE_X2, BLOCK_BITMAP_SIZE_Y2,					// 位图上绘制宽度高度
							RGB(255, 255, 255));										// 位图上的哪个颜色会被视为背景
					}
				}
			}
			// 绘制玩家
			if (player->visible) {
SelectObject(hdc_loadBmp, player->img);
			TransparentBlt(
				hdc_memBuffer,
				player->x - 0.5 * HUMAN_SIZE_X, player->y - 0.5 * HUMAN_SIZE_Y,			// 界面上起始绘制点
				HUMAN_SIZE_X, HUMAN_SIZE_Y,											// 界面上绘制宽度高度
				hdc_loadBmp,
				HUMAN_BITMAP_SIZE_X * player->frame_column, HUMAN_BITMAP_SIZE_Y * player->frame_row,	// 位图上起始绘制点
				HUMAN_BITMAP_SIZE_X, HUMAN_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
				RGB(255, 255, 255)
			);
			if (attack->visible) {
				SelectObject(hdc_loadBmp, attack->img);
				TransparentBlt(
					hdc_memBuffer,
					attack->x - 0.5 * ATTACK_SIZE_X, attack->y - 0.5 * ATTACK_SIZE_Y,		// 界面上起始绘制点
					ATTACK_SIZE_X, ATTACK_SIZE_Y,											// 界面上绘制宽度高度
					hdc_loadBmp,
					ATTACK_BITMAP_SIZE_X * attack->frame_column, ATTACK_BITMAP_SIZE_Y * attack->frame_row,	// 位图上起始绘制点
					ATTACK_BITMAP_SIZE_X, ATTACK_BITMAP_SIZE_Y,												// 位图上绘制宽度高度
					RGB(255, 255, 255)
				);
			}
			}
			
			//绘制npc
			for (int i = 0; i < npcs.size(); i++) {
				if (npcs[i]->visible) {
					SelectObject(hdc_loadBmp, npcs[i]->img);
					TransparentBlt(
						hdc_memBuffer,
						npcs[i]->x - 0.5 * HUMAN_SIZE_X, npcs[i]->y - 0.5 * HUMAN_SIZE_Y,			// 界面上起始绘制点
						HUMAN_SIZE_X, HUMAN_SIZE_Y,											// 界面上绘制宽度高度
						hdc_loadBmp,
						HUMAN_BITMAP_SIZE_X * npcs[i]->frame_column, HUMAN_BITMAP_SIZE_Y * npcs[i]->frame_row,	// 位图上起始绘制点
						HUMAN_BITMAP_SIZE_X, HUMAN_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);
				}
			}
			//绘制怪物
			for (int i = 0; i < monsters.size(); i++) {
				if (monsters[i]->visible) {
					SelectObject(hdc_loadBmp, monsters[i]->img);
					TransparentBlt(
						hdc_memBuffer,
						monsters[i]->x - 0.5 * MOSTER_SIZE_X, monsters[i]->y - 0.5 * MOSTER_SIZE_Y,		// 界面上起始绘制点
						MOSTER_SIZE_X, MOSTER_SIZE_Y,											// 界面上绘制宽度高度
						hdc_loadBmp,
						MOSTER_BITMAP_SIZE_X * monsters[i]->frame_column, MOSTER_BITMAP_SIZE_Y * monsters[i]->frame_row,	// 位图上起始绘制点
						MOSTER_BITMAP_SIZE_X, MOSTER_BITMAP_SIZE_Y,											// 位图上绘制宽度高度
						RGB(255, 255, 255)
					);

					if (monsters[i]->is_attacking) {
SelectObject(hdc_loadBmp, monsters[i]->attack->img);
				TransparentBlt(
					hdc_memBuffer,
					monsters[i]->attack->x - 0.5 * MOSTER_SIZE_X, monsters[i]->attack->y - 0.5 * MOSTER_SIZE_Y,		// 界面上起始绘制点
					ATTACK_SIZE_X, ATTACK_SIZE_Y,											// 界面上绘制宽度高度
					hdc_loadBmp,
					ATTACK_BITMAP_SIZE_X * monsters[i]->attack->frame_column, ATTACK_BITMAP_SIZE_Y * monsters[i]->attack->frame_row,	// 位图上起始绘制点
					ATTACK_BITMAP_SIZE_X, ATTACK_BITMAP_SIZE_Y,												// 位图上绘制宽度高度
					RGB(255, 255, 255)
				);
					}
						
				}
				
				
			}
			


			//如果正处在对话状态：绘制对话框
			if (in_conversation) {
				SelectObject(hdc_loadBmp, bmp_dialog);
				TransparentBlt(
					hdc_memBuffer,
					0, WINDOW_HEIGHT - DIALOG_SIZE_Y - 38, WINDOW_WIDTH - 16, DIALOG_SIZE_Y,					// 界面上绘制位置
					hdc_loadBmp,
					0, 0, DIALOG_BITMAP_SIZE_X, DIALOG_BITMAP_SIZE_Y,	// 位图上绘制位置
					RGB(255, 255, 255)
				);
				//绘制文字
				HFONT hFont = CreateFontW(
					20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
					L"SimSun");		//创建字体
				SelectObject(hdc_memBuffer, hFont);
				SetTextColor(hdc_memBuffer, RGB(0, 0, 0));	// 设置颜色:黑色字体白色背景
				SetBkColor(hdc_memBuffer, RGB(255, 255, 255));
				RECT rect;
				rect.left = 50;
				rect.top = WINDOW_HEIGHT - DIALOG_SIZE_Y - 18;
				rect.right = WINDOW_WIDTH - 110;
				rect.bottom = WINDOW_HEIGHT - 50;
				DrawTextW(hdc_memBuffer, converstaion_content, -1, &rect, DT_WORDBREAK);
			}
		}

	// 绘制按钮到缓存
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);



	// 结束绘制
	EndPaint(hWnd, &ps);

}
