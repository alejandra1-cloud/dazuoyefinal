#pragma once

#pragma region 头文件引用

#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <math.h>
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数
#pragma comment(lib, "winmm.lib")
using namespace std;
#pragma endregion

#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			896+16		//游戏窗口宽度
#define WINDOW_HEIGHT			640+32		//游戏窗口高度

#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_2					2
#define STAGE_3				3
#define STAGE_help					10
#define STAGE_pause			11


//尺寸
#define BG_BITMAP_WIDTH			998		//背景图片的位图宽度
#define BG_BITMAP_HEIGHT		713	 //背景图片的位图高度
#define BG_BITMAP_helpmap1_WIDTH 490 //背景图片的位图宽度
#define BG_BITMAP_helpmap1_height 455 //背景图片的位图高度
#define BG_COLUMNS				28		//背景列数
#define BG_ROWS					20		//背景行数
#define HUMAN_SIZE_X			50		//人物在屏幕上的宽度
#define HUMAN_SIZE_Y			60		
#define HUMAN_BITMAP_SIZE_X		19		//人物在位图上的宽度
#define HUMAN_BITMAP_SIZE_Y		26		
#define BLOCK_SIZE_X			32		//背景单格在屏幕上的宽度
#define BLOCK_SIZE_Y			32		//背景单格在屏幕上的高度
#define BLOCK_BITMAP_SIZE_X		16		//地图块在位图上的宽度
#define BLOCK_BITMAP_SIZE_Y		16
#define BLOCK_BITMAP_SIZE_X2    32	//地图块在位图上的宽度
#define BLOCK_BITMAP_SIZE_Y2	32	
#define DIALOG_SIZE_X			896		//对话框背景
#define DIALOG_SIZE_Y			120
#define DIALOG_BITMAP_SIZE_X	250
#define DIALOG_BITMAP_SIZE_Y	44
#define MOSTER_SIZE_X			60		//怪物
#define MOSTER_SIZE_Y			55
#define MOSTER_BITMAP_SIZE_X	20
#define MOSTER_BITMAP_SIZE_Y	17
#define ATTACK_SIZE_X			32
#define ATTACK_SIZE_Y			32
#define ATTACK_BITMAP_SIZE_X	22
#define ATTACK_BITMAP_SIZE_Y	22


//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击

//单位方向定义
#define UNIT_DIRECT_RIGHT		1		//向右
#define UNIT_DIRECT_LEFT		3		//向左
#define UNIT_DIRECT_UP			2		//向上
#define UNIT_DIRECT_DOWN		0		//向下

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		212		//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		76		//开始游戏按钮高度

#define BUTTON_HELP			1002	//开始游戏按钮ID
#define BUTTON_HELP_WIDTH		106		//开始游戏按钮宽度
#define BUTTON_HELP_HEIGHT		38		//开始游戏按钮高度

#define BUTTON_pausebutton			1003	//开始游戏按钮ID
#define BUTTON_pausebutton_WIDTH		36	//开始游戏按钮宽度
#define BUTTON_pausebutton_HEIGHT	36	//开始游戏按钮高度


#define BUTTON_restartb			1005	//开始游戏按钮ID
#define BUTTON_restartb_WIDTH		36	//开始游戏按钮宽度
#define BUTTON_restartb_HEIGHT		36	//开始游戏按钮高度

#define BUTTON_returnb		1004	//开始游戏按钮ID
#define BUTTON_returnb_WIDTH		36	//开始游戏按钮宽度
#define BUTTON_returnb_HEIGHT		36

#define BUTTON_returnb1		1006	//开始游戏按钮ID
#define BUTTON_returnb1_WIDTH		36	//开始游戏按钮宽度
#define BUTTON_returnb1_HEIGHT		36









#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度

#define NPC_MAN1_ID				2001		//每个NPC的ID号
#define NPC_WOMAN1_ID			2002

#define MONSTER_CAT_ID			3001
#define MONSTER_2               3002

///

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// NPC结构体
struct NPC
{
	int npcID;				//NPC编号
	HBITMAP img;			//图片
	bool visible;			//该NPC是否可见
	bool task_complete;		//该npc的任务是否完成。决定了与npc对话时他会说什么，以及其它行为

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧

	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值

	vector<const wchar_t*> conversations_before;	//任务完成前NPC的台词
	vector<const wchar_t*> conversations_after;		//任务完成后NPC的台词
	int next_conversation_id;				//NPC下一次要说第几句台词
};

// 玩家结构体
struct Player
{
	HBITMAP img;	//图片
	int playerID;
	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧

	int state;		//单位状态
	int direction;	//单位方向

	bool visible = true;
	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health=30;		//生命值
	
};
// 攻击特效结构体
struct Attack
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧
	bool visible;			//当前是否可见

	int x;			//坐标x
	int y;			//坐标y
};
// 怪物结构体
struct Monster
{
	int monsterID;			//怪物编号
	HBITMAP img;			//图片
	Attack* attack;			//图片
	int attack_x;
	bool visible;			//是否可见
	bool task_complete;		//任务是否完成

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几帧

	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health=3;		//生命值
	bool alive;		//是否活着
	bool is_attacking = false;
	vector<const wchar_t*> conversations_before;	//任务完成前的台词
	vector<const wchar_t*> conversations_after;		//任务完成后的台词
	int next_conversation_id;						//下一次要说第几句台词
};

//TODO: 添加游戏需要的更多种数据（地物、砖块等）




#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// Existing function declarations...

void MonsterAttackPlayer(Monster* monster, Player* player);
void MonsterAttackNPC(Monster* monster, NPC* npc);

// Existing function declarations...

#pragma endregion
#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加单位函数
Player* CreatePlayer(int x, int y);
NPC* CreateNPC(int x, int y, int npc_id);
Monster* CreateMonster(int x, int y, int monster_id);
Attack* CreateAttack();

// 初始化场景函数
void InitStage(HWND hWnd, int stageID);


//行为和交互函数：update***在定时器事件中以固定频率调用；handle***在发生键盘/鼠标事件时触发
void UpdatePlayer(HWND hWnd);
void UpdateNPCs(HWND hWnd);
void UpdateMonsters(HWND hWnd);
void UpdateMaps(HWND hWnd);
void UpdateAttack(HWND hWnd);
void CheckBoundary(HWND hWnd);

void HandleConversationEvents(HWND hWnd);

//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

#pragma endregion

										