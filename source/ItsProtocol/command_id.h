
/////////////////////////////////////////////////////////////////////////

#ifndef __CMS_COMMAND_ID_H__
#define __CMS_COMMAND_ID_H__

#define CMS_CID_ACKNOWLEDGEMENT			0		// 接收确认
#define CMS_CID_BROADCAST_QUOTE			5		// 行情广播

#define CMS_CID_BROADCAST_ACCOUNTRISK	32		// 账号的风控策略变化
#define CMS_CID_BROADCAST_ACCOUNTINFO	33		// 账号信息变化
#define CMS_CID_BROADCAST_BASECAPITAL	34		// 期初投入变化 未使用
#define CMS_CID_BROADCAST_SYSPARAM		35		// 系统设置变化
#define CMS_CID_BROADCAST_RISKSN		36		// 某条风控策略变化
#define CMS_CID_BROADCAST_CHANNELINFO	38		// 上手信息变化 未使用
#define CMS_CID_BROADCAST_RISK_DELETED	39		// 某条风控策略被删除
#define CMS_CID_BROADCAST_MARGIN_COMMISSION_CURRENCY	40	// 保证金/手续费/汇率变化
#define CMS_CID_BROADCAST_GROUP			41		// 组属性修改
#define CMS_CID_BROADCAST_DBAGENT		42		// 数据库代理状态
#define CMS_CID_BROADCAST_PROCESSOR		43		// 处理机状态

#define CMS_CID_BROADCAST_MA_ORDER	52			// 主账号委托回报广播 未使用
#define CMS_CID_BROADCAST_MA_TRADE	53			// 主账号成交回报广播 未使用
#define CMS_CID_BROADCAST_MA_CANCEL_FAILED	54	// 主账号撤单失败广播
#define CMS_CID_BROADCAST_EXCHANGE_STATUS	55	// 交易状态广播
#define CMS_CID_BROADCAST_NOTICE		56		// 通知广播
#define CMS_CID_BROADCAST_FORCECLOSE	57		// 强平广播
#define CMS_CID_BROADCAST_TIME			58		// 时间广播
#define CMS_CID_BROADCAST_DEPOSITWITHDRAWAL	59	// 账号资金变化通知
#define CMS_CID_BROADCAST_FORCECANCEL	60		// 强行撤单广播
#define CMS_CID_BROADCAST_ORDER			61		// 账号委托回报广播
#define CMS_CID_BROADCAST_TRADE			62		// 账号成交回报广播
#define CMS_CID_BROADCAST_CANCEL_FAILED	63		// 账号撤单失败广播
#define CMS_CID_BROADCAST_RISKREFUSE	64		// 风控拒绝广播
#define CMS_CID_BROADCAST_REPUSH_DONE	65		// 断线重连后，补推回报完毕
#define CMS_CID_BROADCAST_FORCECANCEL_CME	66	// 强行全部撤单广播 未使用
#define CMS_CID_BROADCAST_TOUCHED		67		// 条件单触发
#define CMS_CID_BROADCAST_FORCECANCEL_APEX	68	// 强行全部撤单广播

#define CMS_CID_CHECK_PASSWORD			101		// 校验用户名密码
#define CMS_CID_LOAD_RISK_BY_ACCOUNT	102		// 取账号的风控设置
#define CMS_CID_CHECK_ADMIN_PASSWORD	103		// 校验管理员用户名密码
#define CMS_CID_LOAD_ADMIN_RIGHTS		104		// 读取管理员权限
#define CMS_CID_CHECK_MD5PASSWORD		105		// 校验用户名MD5密码 未使用
#define CMS_CID_LOAD_RISK_BY_ID			106		// 取风控参数

#define CMS_CID_DEPOSIT					111		// 出入金 未使用
#define CMS_CID_CHECK_ACCOUNT			113		// 删除、修改账号前的检查 未使用
#define CMS_CID_SETTLE					114		// 开始结算 未使用
#define CMS_CID_QUERY_SETTLE_STATUS		115		// 查询结算状态
#define CMS_CID_CLEARSETTLE				116		// 清除结算结果 未使用
#define CMS_CID_RESET_MAXBALANCE		117		// 复位最大权益

#define CMS_CID_CHECK_INSERTOR			121		// 检查报盘机状态
#define CMS_CID_CHECK_PROCESSOR			122		// 检查处理机状态
#define CMS_CID_SYSTEM_STATUS			123		// 取处理机状态
#define CMS_CID_READ_LOG				124		// 读日志 未使用
#define CMS_CID_UPLOAD_HARDWARE_INFO	125		// 上报硬件信息

#define CMS_CID_CHECK_SETTLEPRICE	    150		// 检查结算价是否收到
#define CMS_CID_CHECK_DATABASE		    151		// 检查数据库
#define CMS_CID_UPDATE_DB_CONTRACTS	    152		// 更新数据库的合约表 不使用
#define CMS_CID_LOAD_SUMMARY			153		// 从资金表中读取指定日期的全部记录
#define CMS_CID_LOAD_DEPOSIT_WITHDRAWAL	154		// 从出入金表中读取指定日期的全部出入金记录
#define CMS_CID_LOAD_ORDERS				155		// 从委托表中读取指定日期的委托
#define CMS_CID_LOAD_TRADES				156		// 从成交表中读取指定日期的成交
#define CMS_CID_LOAD_POSITION			157		// 从持仓明细表中读取指定日期的持仓明细
#define CMS_CID_LOAD_INVESTOR_PARAM		158		// 读取投资者特设参数
#define CMS_CID_LOAD_MARGIN_RATE		159		// 读取保证金率
#define CMS_CID_LOAD_COMMISSION_RATE	160		// 读取手续费率
#define CMS_CID_LOAD_SETTLE				161		// 读取结算单

#define CMS_CID_LOAD_ACCOUNT			163		// 读取指定账号的信息
#define CMS_CID_LOAD_MARGIN_PATTERN		164		// 读取保证金率模版
#define CMS_CID_LOAD_COMMISSION_PATTERN	165		// 读取手续费率模版
#define CMS_CID_LOAD_ACCOUNT_MARGIN_COMMISSION	166		// 读取所有账号的手续费率和保证金率

#define CMS_CID_LOAD_SYSTEMPARAM		168		// 读取系统编号
#define CMS_CID_LOAD_CHANNEL_PASSWORD	169		// 读取上手（报盘机）密码
#define CMS_CID_LOAD_SESSIONS			170		// 读取上手（报盘机）会话号
#define CMS_CID_LOAD_MAXBALANCE			171		// 读取最大权益
#define CMS_CID_LOAD_NETVALUE			172		// 读取净值数据
#define CMS_CID_QUERY_MOBILEACCOUNT		173		// 根据手机号查账号
#define CMS_CID_LOAD_CURRENCY			174		// 读取汇率模版
#define CMS_CID_DISABLE_MA				175		// 禁用主账号 未使用
#define CMS_CID_ORDER_CONTRACT_EXPIRED	176		// 未使用

#define CMS_CID_SAVE_NETVALUE			178		// 保存净值数据
#define CMS_CID_SAVE_MAXBALANCE			179		// 保存最大权益
#define CMS_CID_SAVE_SESSIONS			180		// 保存上手（报盘机）会话号
#define CMS_CID_ORDER_RECORD			181		// 向委托表中写入一条记录
#define CMS_CID_TRADE_RECORD			182		// 向成交表中写入一条记录
#define CMS_CID_CLOSE_RECORD			183		// 向平仓表中写入一条记录
#define CMS_CID_POSITION_RECORD			184		// 结算时向持仓明细表中写入一条记录
#define CMS_CID_DEPOSIT_RECORD			185		// 向转账表中写入一条记录 未使用
#define CMS_CID_SUMMARY_RECORD			186		// 结算时向资金表中写入一条记录
#define CMS_CID_LOGIN_RECORD			187		// 向登录记录表中写入一条记录
#define CMS_CID_QUOTE_RECORD			188		// 向行情表中写入一条记录 本系统不使用
#define CMS_CID_TRADE_COMMISSION_RECORD	189		// 更新成交表中的手续费
#define CMS_CID_RISK_RECORD				190		// 记录一条强平日志
#define CMS_CID_INSERTOR_RECORD			191		// 记录报盘机信息 本系统不使用
#define CMS_CID_ORDER_EXTRA_RECORD		192		// 向委托表中写入撤单地址，撤单产品，审核者，审核地址，审核时间
#define CMS_CID_CLEAR_SETTLEMENT		193		// 清除结算结果
#define CMS_CID_MOVE_ORDER_TRADE		194		// 将上一交易日未结算的委托成交移动到当前交易日

#define CMS_CID_LOGIN					201		// 登录
#define CMS_CID_MODIFY_TRADE_PASS		202		// 修改交易密码
#define CMS_CID_MODIFY_FUND_PASSWORD	203		// 修改资金密码
#define CMS_CID_ACCOUNT_STATUS			204		// 查账户资金
#define CMS_CID_ACCOUNT_STATUS_BY_DATE	205		// 查历史账户资金
#define CMS_CID_QUERY_SETTLE			206		// 查结算单
#define CMS_CID_CONFIRM_SETTLE			207		// 确认结算单
#define CMS_CID_QUERY_CONTRACTS			208		// 查合约列表
#define CMS_CID_QUERY_QUOTES			209		// 查行情
#define CMS_CID_QUERY_ORDERS			210		// 查当日委托
#define CMS_CID_QUERY_TRADES			211		// 查当日成交
#define CMS_CID_QUERY_TRADES_BY_DATE	212		// 查历史成交
#define CMS_CID_QUERY_POSITIONS			213		// 查持仓
#define CMS_CID_QUERY_POSITIONS_DETAIL	214		// 查持仓明细
#define CMS_CID_QUERY_MAX_VOLUME		215		// 查可开可平
#define CMS_CID_INSERT_ORDER			216		// 下单
#define CMS_CID_CANCEL_ORDER			217		// 撤单
#define CMS_CID_QUERY_EXCHANGES			218		// 查交易所
#define CMS_CID_QUERY_TRADE_PARAMS		219		// 查交易参数
#define CMS_CID_QUERY_MARGIN_RATE		220		// 查保证金率
#define CMS_CID_QUERY_COMMISSION_RATE	221		// 查手续费率
#define CMS_CID_QUERY_EXCHANGE_MARGIN_RATE		222		// 查交易所保证金率
#define CMS_CID_PATCH_ORDER				223		// 补单
#define CMS_CID_QUERY_COMBINE_POSITIONS_DETAIL	224		// 查组合持仓明细
#define CMS_CID_PATCH_ORDERSTATUS		225		// 补委托状态
#define CMS_CID_PATCH_TRADE				226		// 补成交
#define CMS_CID_APPROVE_ORDER			227		// 报单审核
#define CMS_CID_QUERY_OPTIONS_MARGIN_RATE		228		// 查期权保证金率
#define CMS_CID_QUERY_OPTIONS_COMMISSION_RATE	229		// 查期权手续费率
#define CMS_CID_QUERY_CURRENCY			230		// 查汇率
#define CMS_CID_QUERY_PRODUCTS			231		// 查品种列表

#define CMS_CID_ADMIN_LOGIN				301		// 管理员登录
#define CMS_CID_QUERY_GROUPS			302		// 查组结构
#define CMS_CID_QUERY_GROUPED_INVESTORS	303		// 查组内账号
#define CMS_CID_QUERY_MAIN_ACCOUNTS		304		// 查主账号列表 本系统不使用

#endif
