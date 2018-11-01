#ifndef PRAS_DEFINITION_H
#define PRAS_DEFINITION_H

enum IDTimer{
	ID_TIMER_CHILDFRM,
	ID_TIMER_CURRENTTIME
};

enum UserMessage{
	UM_START = WM_USER + 200,	//界面自定义消息起始值
	UM_VIEW_CHANGE,					//view切换消息
	UM_CLOSE					//系统关闭消息
};

enum IDView{
	ID_VIEW_MONITOR,
	ID_VIEW_ROLL,
	ID_VIEW_USER,
	ID_VIEW_OPERATION,
	ID_VIEW_FURNACE
};

#endif