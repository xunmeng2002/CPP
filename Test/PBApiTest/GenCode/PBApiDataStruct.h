#pragma once

#include "stepdef.h"

//基本信息
struct PBStepBaseInfoField
{
	char LOCAL_IP[64];   //客户端本机地址
	char LOCAL_MAC[64];  //客户端MAC地址
	char IP[64];         //终端公网IP
};

struct PBStepRspLockSecurityOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//委托时间
	char WTSJ[64];
};

struct PBStepQryFutureCommissionRateField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//市场类型
	char SCLX[64];
};

struct PBStepRspErrorField
{
	PBStepBaseInfoField BaseInfo;
	//错误代码
	char CODE[64];
	//错误信息
	char MSG[512];
};

struct PBStepFutureCommissionRateField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//投保标志
	char TBBZ[64];
	//开仓金额比例
	char KCJEBL[64];
	//平仓金额比例
	char PCJEBL[64];
	//平今金额比例
	char PJJEBL[64];
	//开仓单位金额
	char KCDWJE[64];
	//平仓单位金额
	char PCDWJE[64];
	//平今单位金额
	char PJDWJE[64];
};

struct PBStepQryHolderAccountField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepReqLockSecurityOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//委托数量
	char WTSL[64];
	//股东号
	char GDH[64];
	//席位号
	char XWH[64];
	//锁定方向
	char SDFX[64];
};

struct PBStepHolderAccountField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//市场名称
	char SCMC[64];
	//股东号
	char GDH[64];
	//主帐号标志
	char ZZHBZ[64];
	//投保标志
	char TBBZ[64];
	//席位号
	char XWH[64];
	//市场信息
	char SCXX[64];
	//外盘标志
	char WPBZ[64];
};

struct PBStepReqCancelOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//股东号
	char GDH[64];
	//席位号
	char XWH[64];
	//市场代码
	char SCDM[64];
	//扩展字段
	char KZZD[64];
	//合约代码
	char HYDM[64];
	//委托日期
	char WTRQ[64];
	//下单席位
	char XDXW[64];
};

struct PBStepInstrumentField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//合约乘数
	char HYCS[64];
	//最小变动价位
	char ZXBDJW[64];
	//合约名称
	char HYDMMC[64];
	//限价单最大下单量
	char WTSX[64];
	//市价单最大下单量
	char ZCSX[64];
	//单位保证金
	char DWBZJ[64];
	//市场类型
	char SCLX[64];
	//到期日
	char DQR[64];
	//单边保证金优惠
	char DBYH[64];
	//品种代码
	char PZDM[64];
	//自动净仓标志
	char ZDJC[64];
	//合约类别
	char HYLB[64];
	//标的代码
	char BDDM[64];
	//标的名称
	char BDMC[64];
	//行权价格
	char XQJG[64];
};

struct PBStepRspInquiryField
{
	PBStepBaseInfoField BaseInfo;
	//询价编号
	char XJBH[64];
};

struct PBStepRspLoginField
{
	PBStepBaseInfoField BaseInfo;
	//资金帐号
	char ZJZH[64];
	//当前交易日
	char TRADE_DATE[64];
	//上一交易日
	char LAST_TRADE_DATE[64];
	//登录标志
	char LOGIN_FLAG[64];
	//修改密码提示信息
	char XGMMTS[64];
	//柜台会话标识
	char GTHHBZ[64];
	//安全密钥
	char AQMY[256];
};

struct PBStepCapitalField
{
	PBStepBaseInfoField BaseInfo;
	//资金帐号
	char ZJZH[64];
	//货币代码
	char HBDM[64];
	//期初余额
	char QCYE[64];
	//可用资金
	char KYZJ[64];
	//总资产(当前权益)
	char ZZC[64];
	//平仓盯市盈亏
	char PCDSYK[64];
	//手续费
	char SXF[64];
	//现金资产
	char XJZC[64];
	//出入金
	char CRJ[64];
};

struct PBStepRspExecOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepTodayExecOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//委托编号
	char WTBH[64];
	//合约代码
	char HYDM[64];
	//委托状态
	char WTZT[64];
	//委托价格
	char WTJG[64];
	//委托数量
	char WTSL[64];
	//委托时间
	char WTSJ[64];
	//申报时间
	char SBSJ[64];
	//席位号
	char XWH[64];
	//下单席位
	char XDXW[64];
	//非交易申请类别
	char FJYSQLB[64];
	//投保标志
	char TBBZ[64];
	//扩展字段
	char KZZD[64];
};

struct PBStepTodayOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//委托编号
	char WTBH[64];
	//合约代码
	char HYDM[64];
	//委托状态
	char WTZT[64];
	//买卖类别
	char MMLB[64];
	//委托数量
	char WTSL[64];
	//委托价格
	char WTJG[64];
	//成交数量
	char CJSL[64];
	//撤单数量
	char CDSL[64];
	//委托时间
	char WTSJ[64];
	//市价委托类别
	char SJWTLB[64];
	//股东号
	char GDH[64];
	//委托日期
	char WTRQ[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//期权备兑标志
	char BDBZ[64];
	//备注信息
	char BZXX[64];
	//价格类型
	char JGLB[64];
	//有效期
	char YXQLX[64];
	//成交量类型
	char CJLLX[64];
	//最小成交量
	char ZXCJL[64];
	//扩展字段
	char KZZD[64];
	//触发条件
	char CFTJ[64];
	//撤单时间
	char CDSJ[64];
	//有效日期
	char YXRQ[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
	//柜台定位串
	char GTDWC[64];
	//委托类型
	char WTLX[64];
};

struct PBStepExecOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//委托编号
	char WTBH[64];
	//合约代码
	char HYDM[64];
	//委托状态
	char WTZT[64];
	//委托数量
	char WTSL[64];
	//委托时间
	char WTSJ[64];
	//席位号
	char XWH[64];
	//备注信息
	char BZXX[64];
	//非交易申请类别
	char FJYSQLB[64];
	//投保标志
	char TBBZ[64];
	//扩展字段
	char KZZD[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepReqInquiryField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//股东号
	char GDH[64];
	//席位号
	char XWH[64];
};

struct PBStepRspInsertOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepRspConfirmSettlementField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepReqCancelExecOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//市场代码
	char SCDM[64];
	//席位号
	char XWH[64];
	//下单席位
	char XDXW[64];
	//股东号
	char GDH[64];
	//扩展字段
	char KZZD[64];
};

struct PBStepQrySystemStatusField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
};

struct PBStepOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//股东号
	char GDH[64];
	//买卖类别
	char MMLB[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//委托状态
	char WTZT[64];
	//强平标志
	char QPBZ[64];
	//委托时间
	char WTSJ[64];
	//撤单时间
	char CDSJ[64];
	//委托编号
	char WTBH[64];
	//委托系统号
	char WTXTH[64];
	//委托数量
	char WTSL[64];
	//成交数量
	char CJSL[64];
	//未成交数量
	char WCJSL[64];
	//委托日期
	char WTRQ[64];
	//交易日期
	char JYRQ[64];
	//委托价格
	char WTJG[64];
	//组合类型
	char WTZHLX[64];
	//价格类型
	char JGLB[64];
	//有效期
	char YXQLX[64];
	//成交量类型
	char CJLLX[64];
	//最小成交量
	char ZXCJL[64];
	//触发条件
	char CFTJ[64];
	//扩展字段
	char KZZD[64];
	//合约类别
	char HYLB[64];
	//期权备兑标志
	char BDBZ[64];
	//撤单数量
	char CDSL[64];
	//备注信息
	char BZXX[64];
	//市价委托类别
	char SJWTLB[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepRspCancelExecOrderField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepQryPositionField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//查询标志
	char CXBZ[64];
};

struct PBStepReqInsertOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//买卖类别
	char MMLB[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//委托数量
	char WTSL[64];
	//委托价格
	char WTJG[64];
	//股东号
	char GDH[64];
	//席位号
	char XWH[64];
	//市价委托类别
	char SJWTLB[64];
	//期权备兑标志
	char BDBZ[64];
	//价格类型
	char JGLB[64];
	//有效期
	char YXQLX[64];
	//成交量类型
	char CJLLX[64];
	//最小成交量
	char ZXCJL[64];
	//触发条件
	char CFTJ[64];
	//组合类型
	char WTZHLX[64];
	//有效日期
	char YXRQ[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepSystemStatusField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//系统状态
	char XTZT[64];
	//交易子状态
	char JYZZT[64];
};

struct PBStepReqLoginField
{
	PBStepBaseInfoField BaseInfo;
	//营业部代码
	char YYBDM[64];
	//券商代码
	char QSDM[64];
	//硬盘编号
	char YPBH[64];
	//客户端本机IP地址
	char LOCAL_IP[64];
	//客户端MAC地址
	char LOCAL_MAC[64];
	//客户端版本号
	char VERSION[64];
	//登录类别
	char DLLB[64];
	//动态密码
	char DTMM[64];
	//动态密码类别
	char DTMMLB[64];
	//帐号类别
	char ZHLB[64];
	//登录帐号
	char DLZH[64];
	//获取短信口令标志
	char HQDXKL[64];
	//核心认证类别
	char HXRZ[64];
	//核心认证密码
	char HXMM[64];
	//CPU
	char CPU[64];
	//主板日期
	char ZBRQ[64];
	//客户端唯一识别码
	char UNIQUE_ID[64];
	//硬盘分区
	char YPFQ[64];
	//计算机名
	char JSJM[64];
	//期货所用的BrokerID
	char BROKER_ID[64];
	//产品
	char CP[64];
	//平台
	char PT[64];
	//手机号码
	char SJHM[64];
	//核心帐号
	char HXZH[64];
	//指纹数据
	char ZWSJ[64];
	//手机的IMSI
	char IMSI[64];
	//穿透式监管终端硬件信息
	char LOCAL_INFO[3000];
	//穿透式监管异常标志
	char YCBS[16];
	//穿透式监管信息完整度
	char XXWZD[2048];
	//穿透式密钥版本
	char CTSMYBB[1024];
	//穿透式密钥版本
	char SQM[64];
	//穿透式版本
	char CTSBB[128];
	//终端APPID
	char APPID[64];
};

struct PBStepQryPositionDetailField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
};

struct PBStepReqSecurityVerityField
{
	PBStepBaseInfoField BaseInfo;
	//客户端密钥
	char MYKL[2048];
};

struct PBStepReqConfirmSettlementField
{
	PBStepBaseInfoField BaseInfo;
	//交易日期
	char JYRQ[64];
};

struct PBStepQryTodayExecOrderField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepQryCapitalField
{
	PBStepBaseInfoField BaseInfo;
	//货币代码
	char HBDM[64];
	//查询可取资金
	char KQBZ[64];
};

struct PBStepFutureMarginRateField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//投保标志
	char TBBZ[64];
	//买卖类别
	char MMLB[64];
	//开仓金额比例
	char KCJEBL[64];
	//开仓单位金额
	char KCDWJE[64];
};

struct PBStepQryIncTradeField
{
	PBStepBaseInfoField BaseInfo;
	//柜台定位串
	char GTDWC[64];
	//请求行数
	char QQHS[64];
	//撤销标志
	char CDBZ[64];
};

struct PBStepQryInstrumentField
{
	PBStepBaseInfoField BaseInfo;
	//市场列表
	char SCLB[64];
};

struct PBStepPositionField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//当前数量
	char DQSL[64];
	//买入均价
	char MRJJ[64];
	//成本价
	char CBJ[64];
	//股东号
	char GDH[64];
	//货币代码
	char HBDM[64];
	//期权备兑标志
	char BDBZ[64];
	//买卖类别
	char MMLB[64];
	//投保标志
	char TBBZ[64];
};

struct PBStepQryTodayTradeField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//成交编号
	char CJBH[64];
	//撤销标志
	char CDBZ[64];
};

struct PBStepTodayTradeField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//合约名称
	char HYDMMC[64];
	//买卖类别
	char MMLB[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//成交时间
	char CJSJ[64];
	//委托编号
	char WTBH[64];
	//成交数量
	char CJSL[64];
	//成交价格
	char CJJG[64];
	//成交编号
	char CJBH[64];
	//期权备兑标志
	char BDBZ[64];
	//成交日期
	char CJRQ[64];
	//合约类别
	char HYLB[64];
	//柜台定位串
	char GTDWC[64];
	//成交类型
	char CJLX[64];
	//原委托号
	char YWTH[64];
};

struct PBStepQryTransferMoneyField
{
	PBStepBaseInfoField BaseInfo;
	//流水序号
	char LSXH[64];
};

struct PBStepQryIncOrderField
{
	PBStepBaseInfoField BaseInfo;
	//柜台定位串
	char GTDWC[64];
	//请求行数
	char QQHS[64];
	//撤销标志
	char CDBZ[64];
};

struct PBStepQryTodayOrderField
{
	PBStepBaseInfoField BaseInfo;
	//委托编号
	char WTBH[64];
	//委托列表
	char WTHLB[64];
	//撤销标志
	char CDBZ[64];
};

struct PBStepTransferMoneyField
{
	PBStepBaseInfoField BaseInfo;
	//流水序号
	char LSXH[64];
	//转账金额
	char ZZJE[64];
	//货币代码
	char HBDM[64];
	//银证业务标识
	char YZYWBZ[64];
	//银证业务状态
	char YZYWZT[64];
	//转帐日期或申请日期
	char SQRQ[64];
	//转帐时间或者申请时间
	char SQSJ[64];
	//结果说明
	char JGSM[64];
};

struct PBStepQryFutureMarginRateField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//投保标志
	char TBBZ[64];
};

struct PBStepRspCancelOrderField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepReqSetUserInfoField
{
	PBStepBaseInfoField BaseInfo;
	//请求标志
	char QQBZ[64];
	//日志路径
	char RZLJ[64];
	//授权文件
	char SQWJ[64];
	//配置文件
	char PZWJ[64];
	//日志ID
	char LOGID[64];
	//RSA公钥
	char RSAKEY[64];
	//穿透式授权码文件
	char RZMWJ[64];
	//交易柜台
	char JYGT[64];
};

struct PBStepQryLockAvailableField
{
	PBStepBaseInfoField BaseInfo;
	//席位号
	char XWH[64];
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//锁定方向
	char SDFX[64];
	//股东号
	char GDH[64];
};

struct PBStepReqExecOrderField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//行权数量
	char XQSL[64];
	//股东号
	char GDH[64];
	//席位号
	char XWH[64];
	//非交易申请类别
	char FJYSQLB[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//期权行权后期货自动自动对冲
	char QHZDC[64];
	//本地报单序号
	char BDBDXH[64];
	//柜台会话标识
	char GTHHBZ[64];
};

struct PBStepTradeField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//合约名称
	char HYDMMC[64];
	//买卖类别
	char MMLB[64];
	//开平仓标志
	char KPBZ[64];
	//投保标志
	char TBBZ[64];
	//成交时间
	char CJSJ[64];
	//委托编号
	char WTBH[64];
	//成交数量
	char CJSL[64];
	//成交价格
	char CJJG[64];
	//成交编号
	char CJBH[64];
	//期权备兑标志
	char BDBZ[64];
	//成交日期
	char CJRQ[64];
	//合约类别
	char HYLB[64];
};

struct PBStepRspSecurityVerityField
{
	PBStepBaseInfoField BaseInfo;
	//安全密钥
	char AQMY[256];
	//时间间隔
	char SJJGS[64];
};

struct PBStepRspSetUserInfoField
{
	PBStepBaseInfoField BaseInfo;
};

struct PBStepUserInfoField
{
	PBStepBaseInfoField BaseInfo;
	//请求标志
	char QQBZ[64];
	//日志路径
	char RZLJ[64];
	//授权文件
	char SQWJ[64];
	//配置文件
	char PZWJ[64];
	//穿透式授权码文件
	char RZMWJ[64];
};

struct PBStepPositionDetailField
{
	PBStepBaseInfoField BaseInfo;
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//当前数量
	char DQSL[64];
	//成本价
	char CBJ[64];
	//买卖类别
	char MMLB[64];
	//投保标志
	char TBBZ[64];
	//保证金
	char BZJ[64];
	//开仓日期
	char KCRQ[64];
	//货币代码
	char HBDM[64];
	//成交编号
	char CJBH[64];
};

struct PBStepSettlementField
{
	PBStepBaseInfoField BaseInfo;
	//结算单
	char JSD[64];
	//结算单确认标志
	char QRBZ[64];
};

struct PBStepQrySettlementField
{
	PBStepBaseInfoField BaseInfo;
	//结算单查询类别（期货）
	char JSDCXLB[64];
	//起始日期
	char QSRQ[64];
	//终止日期
	char ZZRQ[64];
};

struct PBStepLockAvailableField
{
	PBStepBaseInfoField BaseInfo;
	//可委托数量
	char KMSL[64];
	//市场代码
	char SCDM[64];
	//合约代码
	char HYDM[64];
	//锁定方向
	char SDFX[64];
};

