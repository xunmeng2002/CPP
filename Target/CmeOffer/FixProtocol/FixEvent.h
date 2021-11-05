#pragma once

#include "Event.h"



constexpr int FixEventOnMessage = 10000;		//收到消息
constexpr int FixEventOnSequenceGap = 10001;		//序号间隙信息
constexpr int FixEventReqLogon = 10002;		//请求登录
constexpr int FixEventRspLogon = 10003;		//登录回报
constexpr int FixEventReqLogout = 10004;		//请求登出
constexpr int FixEventRspLogout = 10005;		//登出回报
constexpr int FixEventReqHeartBeat = 10006;		//请求心跳
constexpr int FixEventRspHeartBeat = 10007;		//心跳回报
constexpr int FixEventReqTestRequest = 10008;		//请求测试请求
constexpr int FixEventRspTestRequest = 10009;		//测试请求回报
constexpr int FixEventReqResendRequest = 10010;		//请求重发请求
constexpr int FixEventRspResendRequest = 10011;		//重发请求回报
constexpr int FixEventReqSequenceReset = 10012;		//请求序号重置
constexpr int FixEventRspSequenceReset = 10013;		//序号重置回报
constexpr int FixEventReqNewOrder = 10014;		//请求报单
constexpr int FixEventReqOrderCancel = 10015;		//请求撤单
constexpr int FixEventReqOrderCancelReplace = 10016;		//请求改单
constexpr int FixEventRspExecutionReport = 10017;		//执行回报
constexpr int FixEventRspOrderCancelReject = 10018;		//撤单拒绝回报
constexpr int FixEventRspSessionLevelReject = 10019;		//会话级别拒绝回报
constexpr int FixEventDoResendLastResendRequest = 10020;		//重发上次重发的请求报文


