
/////////////////////////////////////////////////////////////////////////

#ifndef __CMS_PROCESSOR_DEFINES__
#define __CMS_PROCESSOR_DEFINES__

#define MAX_EXCHANGE_ID_LEN 12
#define MAX_EXCHANGE_NAME_LEN 32
#define MAX_PRODUCT_ID_LEN 16
#define MAX_PRODUCT_NAME_LEN 32
#define MAX_CONTRACT_ID_LEN 32
#define MAX_CONTRACT_NAME_LEN 32
#define MAX_BROKER_NAME_LEN 8
#define MAX_ACCOUNT_ID_LEN 16
#define MAX_PASSWORD_LEN 48
#define MAX_ACCOUNT_NAME_LEN 64
#define MAX_ORDER_REF_LEN 16
#define MAX_ORDER_SYSID_LEN 24
#define MAX_ORDER_USERID_LEN 32
#define MAX_TRADE_ID_LEN 24
#define MAX_EXCHANGE_TRADE_ID_LEN 72
#define MAX_TIME_LEN 12
#define MAX_ORDER_SOURCE_LEN 24
#define MAX_CURRENCY_GROUP_LEN 6
#define MAX_CURRENCY_ID_LEN 4
#define MAX_TAG50_LEN 16
#define MAX_CHANNEL_ORDERID_LEN 24

/////////////////////////////////////////////////////////////////////////
///交易状态
/////////////////////////////////////////////////////////////////////////
///未知
#define PTK_ES_Unknown '0'
///集合竞价报单
#define PTK_ES_AuctionOrdering '1'
///连续交易
#define PTK_ES_Trading '2'
///暂停
#define PTK_ES_Pause '3'
///收市
#define PTK_ES_Closed '4'

/////////////////////////////////////////////////////////////////////////
///产品类型
/////////////////////////////////////////////////////////////////////////
///期货
#define PTK_PC_Futures '1'
///期货期权
#define PTK_PC_Options '2'
///组合
#define PTK_PC_Combination '3'
///即期
#define PTK_PC_Spot '4'
///期转现
#define PTK_PC_EFP '5'
///现货期权
#define PTK_PC_SpotOption '6'

/////////////////////////////////////////////////////////////////////////
///持仓类型
/////////////////////////////////////////////////////////////////////////
///净持仓
#define PTK_PT_Net '1'
///综合持仓
#define PTK_PT_Gross '2'

/////////////////////////////////////////////////////////////////////////
///持仓日期类型
/////////////////////////////////////////////////////////////////////////
///使用历史持仓（区分今昨仓）
#define PTK_PDT_UseHistory '1'
///不使用历史持仓（不区分今昨仓）
#define PTK_PDT_NoUseHistory '2'

/////////////////////////////////////////////////////////////////////////
///报单状态
/////////////////////////////////////////////////////////////////////////
///正在申报
#define PTK_OST_Inserting '0'
///已报
#define PTK_OST_Inserted '1'
///部成
#define PTK_OST_PartTraded '2'
///已成
#define PTK_OST_AllTraded '3'
///已撤
#define PTK_OST_Canceled '4'
///部成部撤
#define PTK_OST_PartTradedCanceled '5'
///废单
#define PTK_OST_Error 'e'
///未触发
#define PTK_OST_NotTouched 'p'
///已触发
#define PTK_OST_Touched 't'
///未知
#define PTK_OST_Unknown 'x'

/////////////////////////////////////////////////////////////////////////
///买卖方向
/////////////////////////////////////////////////////////////////////////
///买
#define PTK_D_Buy '0'
///卖
#define PTK_D_Sell '1'

/////////////////////////////////////////////////////////////////////////
///投机套保标志
/////////////////////////////////////////////////////////////////////////
///投机
#define PTK_HF_Speculation '1'
///套利
#define PTK_HF_Arbitrage '2'
///保值
#define PTK_HF_Hedge '3'

/////////////////////////////////////////////////////////////////////////
///报单价格条件
/////////////////////////////////////////////////////////////////////////
///市价
#define PTK_OPT_AnyPrice '1'
///限价
#define PTK_OPT_LimitPrice '2'
///最优价
#define PTK_OPT_BestPrice '3'
///以下仅用于条件单
///最新价
#define PTK_OPT_LastPrice '4'
///最新价浮动上浮1个ticks
#define PTK_OPT_LastPricePlusOneTicks '5'
///最新价浮动上浮2个ticks
#define PTK_OPT_LastPricePlusTwoTicks '6'
///最新价浮动上浮3个ticks
#define PTK_OPT_LastPricePlusThreeTicks '7'
///卖一价
#define PTK_OPT_AskPrice1 '8'
///卖一价浮动上浮1个ticks
#define PTK_OPT_AskPrice1PlusOneTicks '9'
///卖一价浮动上浮2个ticks
#define PTK_OPT_AskPrice1PlusTwoTicks 'A'
///卖一价浮动上浮3个ticks
#define PTK_OPT_AskPrice1PlusThreeTicks 'B'
///买一价
#define PTK_OPT_BidPrice1 'C'
///买一价浮动上浮1个ticks
#define PTK_OPT_BidPrice1PlusOneTicks 'D'
///买一价浮动上浮2个ticks
#define PTK_OPT_BidPrice1PlusTwoTicks 'E'
///买一价浮动上浮3个ticks
#define PTK_OPT_BidPrice1PlusThreeTicks 'F'

/////////////////////////////////////////////////////////////////////////
///开平标志
/////////////////////////////////////////////////////////////////////////
///开仓
#define PTK_OF_Open '0'
///平仓
#define PTK_OF_Close '1'
///平今
#define PTK_OF_CloseToday '2'

/////////////////////////////////////////////////////////////////////////
///今昨仓标志
/////////////////////////////////////////////////////////////////////////
///总仓或昨仓
#define PTK_PSD_Total PTK_OF_Close
///今仓
#define PTK_PSD_Today PTK_OF_CloseToday

/////////////////////////////////////////////////////////////////////////
///撤单改单类型
/////////////////////////////////////////////////////////////////////////
///撤单
#define PTK_AF_Delete '0'
///改单
#define PTK_AF_Modify '3'

/////////////////////////////////////////////////////////////////////////
///触发条件类型
/////////////////////////////////////////////////////////////////////////
///立即
#define PTK_CC_Immediately '1'
///止损
#define PTK_CC_Touch '2'
///止赢
#define PTK_CC_TouchProfit '3'
///预埋单
#define PTK_CC_ParkedOrder '4'
///最新价大于条件价
#define PTK_CC_LastPriceGreaterThanStopPrice '5'
///最新价大于等于条件价
#define PTK_CC_LastPriceGreaterEqualStopPrice '6'
///最新价小于条件价
#define PTK_CC_LastPriceLesserThanStopPrice '7'
///最新价小于等于条件价
#define PTK_CC_LastPriceLesserEqualStopPrice '8'
///卖一价大于条件价
#define PTK_CC_AskPriceGreaterThanStopPrice '9'
///卖一价大于等于条件价
#define PTK_CC_AskPriceGreaterEqualStopPrice 'A'
///卖一价小于条件价
#define PTK_CC_AskPriceLesserThanStopPrice 'B'
///卖一价小于等于条件价
#define PTK_CC_AskPriceLesserEqualStopPrice 'C'
///买一价大于条件价
#define PTK_CC_BidPriceGreaterThanStopPrice 'D'
///买一价大于等于条件价
#define PTK_CC_BidPriceGreaterEqualStopPrice 'E'
///买一价小于条件价
#define PTK_CC_BidPriceLesserThanStopPrice 'F'
///买一价小于等于条件价
#define PTK_CC_BidPriceLesserEqualStopPrice 'H'

/////////////////////////////////////////////////////////////////////////
///有效期类型
/////////////////////////////////////////////////////////////////////////
///立即完成，否则撤销
#define PTK_TC_IOC '1'
///本节有效
#define PTK_TC_GFS '2'
///当日有效
#define PTK_TC_GFD '3'
///指定日期前有效
#define PTK_TC_GTD '4'
///撤销前有效
#define PTK_TC_GTC '5'
///集合竞价有效
#define PTK_TC_GFA '6'

/////////////////////////////////////////////////////////////////////////
///成交量类型
/////////////////////////////////////////////////////////////////////////
///任何数量
#define PTK_VC_AV '1'
///最小数量
#define PTK_VC_MV '2'
///全部数量
#define PTK_VC_CV '3'

/////////////////////////////////////////////////////////////////////////
///强平原因
/////////////////////////////////////////////////////////////////////////
///非强平
#define PTK_FCC_NotForceClose '0'
///资金不足
#define PTK_FCC_LackDeposit '1'
///客户超仓
#define PTK_FCC_ClientOverPositionLimit '2'
///会员超仓
#define PTK_FCC_MemberOverPositionLimit '3'
///持仓非整数倍
#define PTK_FCC_NotMultiple '4'
///违规
#define PTK_FCC_Violation '5'
///其它
#define PTK_FCC_Other '6'
///自然人临近交割
#define PTK_FCC_PersonDeliv '7'

/////////////////////////////////////////////////////////////////////////
///成交类型
/////////////////////////////////////////////////////////////////////////
///普通成交
#define PTK_TRDT_Common '0'
///期权执行
#define PTK_TRDT_OptionsExecution '1'
///OTC成交
#define PTK_TRDT_OTC '2'
///期转现衍生成交
#define PTK_TRDT_EFPDerived '3'
///组合衍生成交
#define PTK_TRDT_CombinationDerived '4'

/////////////////////////////////////////////////////////////////////////
///保证金价格类型
/////////////////////////////////////////////////////////////////////////
///昨结算价
#define PTK_MPT_PreSettlementPrice '1'
///最新价
#define PTK_MPT_SettlementPrice '2'
///成交均价
#define PTK_MPT_AveragePrice '3'
///开仓价
#define PTK_MPT_OpenPrice '4'

/////////////////////////////////////////////////////////////////////////
///浮盈浮亏是否计入可用
/////////////////////////////////////////////////////////////////////////
///浮盈浮亏都计算
#define PTK_AG_All '1'
///浮盈不计，浮亏计
#define PTK_AG_OnlyLost '2'
///浮盈计，浮亏不计
#define PTK_AG_OnlyGain '3'
///浮盈浮亏都不计算
#define PTK_AG_None '4'

/////////////////////////////////////////////////////////////////////////
///平仓盈利类型是否可用
/////////////////////////////////////////////////////////////////////////
///包含平仓盈利
#define PTK_ICP_Include '0'
///不包含平仓盈利
#define PTK_ICP_NotInclude '2'

/////////////////////////////////////////////////////////////////////////
///是否启用上期所大额单边保证金
/////////////////////////////////////////////////////////////////////////
///不使用大额单边保证金算法
#define PTK_MMSA_NO '0'
///使用大额单边保证金算法
#define PTK_MMSA_YES '1'

/////////////////////////////////////////////////////////////////////////
///账户类型
/////////////////////////////////////////////////////////////////////////
///投资者
#define PTK_IAT_Investor '0'
///管理员
#define PTK_IAT_Admin '1'

/////////////////////////////////////////////////////////////////////////
///主账号报单来源
/////////////////////////////////////////////////////////////////////////
///外部
#define PTK_MOS_Others '0'
///本地
#define PTK_MOS_Local '1'

/////////////////////////////////////////////////////////////////////////
///通知类型
/////////////////////////////////////////////////////////////////////////
///普通
#define PTK_NT_Message '0'
///警告
#define PTK_NT_Warning '1'
///已强平
#define PTK_NT_ForceClose '2'
///CTP通知（此消息只推给监控）
#define PTK_NT_CTP '3'

/////////////////////////////////////////////////////////////////////////
///缓存策略
/////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

#define CMS_PROCESSOR_BUFFER_INIT_LARGE 256				// 大缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_LARGE_CONCURRENT 4	// 大缓存块并发数量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL 1024			// 小缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL_CONCURRENT 4	// 小缓存块并发数量
#define CMS_PROCESSOR_INVESTORMAP_INIT 257				// 客户映射表初始大小
#define CMS_PROCESSOR_CONTRACTMAP_INIT 521				// 合约映射表初始大小
#define CMS_PROCESSOR_ORDERMAP_INIT 1031				// 委托映射表初始大小

#define CMS_FRONT_BUFFER_INIT_LARGE 256				// 大缓存块每块容量
#define CMS_FRONT_BUFFER_INIT_LARGE_CONCURRENT 4	// 大缓存块并发数量
#define CMS_FRONT_BUFFER_INIT_SMALL 1024			// 小缓存块每块容量
#define CMS_FRONT_BUFFER_INIT_SMALL_CONCURRENT 4	// 小缓存块并发数量

#define CMS_INSERTOR_BUFFER_INIT_LARGE 32			// 大缓存块每块容量
#define CMS_INSERTOR_BUFFER_INIT_LARGE_CONCURRENT 2	// 大缓存块并发数量
#define CMS_INSERTOR_BUFFER_INIT_SMALL 128			// 小缓存块每块容量
#define CMS_INSERTOR_BUFFER_INIT_SMALL_CONCURRENT 2	// 小缓存块并发数量

#define CMS_DB_BUFFER_INIT_SMALL 128			// 小缓存块每块容量
#define CMS_DB_BUFFER_INIT_SMALL_CONCURRENT 2	// 小缓存块并发数量

#else

#define CMS_PROCESSOR_BUFFER_INIT_LARGE 1024			// 大缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_LARGE_CONCURRENT 16	// 大缓存块并发数量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL 51200			// 小缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL_CONCURRENT 32	// 小缓存块并发数量
#define CMS_PROCESSOR_INVESTORMAP_INIT 99991			// 客户映射表初始大小
#define CMS_PROCESSOR_CONTRACTMAP_INIT 4099				// 合约映射表初始大小
#define CMS_PROCESSOR_ORDERMAP_INIT 130003				// 委托映射表初始大小

#define CMS_FRONT_BUFFER_INIT_LARGE 4096			// 大缓存块每块容量
#define CMS_FRONT_BUFFER_INIT_LARGE_CONCURRENT 16	// 大缓存块并发数量
#define CMS_FRONT_BUFFER_INIT_SMALL 5120			// 小缓存块每块容量
#define CMS_FRONT_BUFFER_INIT_SMALL_CONCURRENT 16	// 小缓存块并发数量

#define CMS_INSERTOR_BUFFER_INIT_LARGE 128				// 大缓存块每块容量
#define CMS_INSERTOR_BUFFER_INIT_LARGE_CONCURRENT 4		// 大缓存块并发数量
#define CMS_INSERTOR_BUFFER_INIT_SMALL 256				// 小缓存块每块容量
#define CMS_INSERTOR_BUFFER_INIT_SMALL_CONCURRENT 16	// 小缓存块并发数量

#define CMS_DB_BUFFER_INIT_SMALL 5120			// 小缓存块每块容量
#define CMS_DB_BUFFER_INIT_SMALL_CONCURRENT 8	// 小缓存块并发数量

/* // 黄金模拟使用
#define CMS_PROCESSOR_BUFFER_INIT_LARGE 2048			// 大缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_LARGE_CONCURRENT 16	// 大缓存块并发数量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL 102400			// 小缓存块每块容量
#define CMS_PROCESSOR_BUFFER_INIT_SMALL_CONCURRENT 16	// 小缓存块并发数量
#define CMS_PROCESSOR_INVESTORMAP_INIT 10093			// 客户映射表初始大小
#define CMS_PROCESSOR_CONTRACTMAP_INIT 17				// 合约映射表初始大小
#define CMS_PROCESSOR_ORDERMAP_INIT 1046527				// 委托映射表初始大小

#define CMS_DB_BUFFER_INIT_LARGE 4096			// 大缓存块每块容量
#define CMS_DB_BUFFER_INIT_LARGE_CONCURRENT 16	// 大缓存块并发数量
#define CMS_DB_BUFFER_STOP 4096				// 缓存用量超过此值时停止交易
*/

#endif

#endif
