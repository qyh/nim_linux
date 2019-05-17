#include <nim_client.h>
#include <nim_res_code_def.h>
#include <nim_sysmsg.h>
#include <stdio.h>

const char* appKey = "2eb9987eb954b4f56e57c94e54055aca";
const char* account = "8af7c7c5d0600a272b265be028a11c7f";
const char* token = "ff5dbb52da81cf1bae74abf62a063340";

//全局会话列表变更通知函数
void CallbackSessionChange(int rescode, const char *result, int total_unread_counts, const char *json_extension, const void *user_data)
{
    if (rescode == kNIMResSuccess)
    {
        //处理会话变更
		printf("session change\n");
    }
    else
    {
        //错误处理
		printf("session error\n");
    }
}

void regist_call_back()
{
    //注册全局会话列表变更通知函数
    nim_session_reg_change_cb(NULL, &CallbackSessionChange, NULL);  // 会话列表变更通知(nim_session)
}
void CallbackLogin(const char* res, const void *user_data)
{
    //解析JSON数据处理登录状态
	printf("login_callback:\n");
	printf("res:%s\n", res);
	printf("user_data:%s\n", user_data);
}

void login()
{
    //app key: 应用标识，不同应用之间的数据（用户，消息，群组等）是完全隔离的。开发自己的应用时，需要替换成自己申请来的app key
    //注意：替换成客户自己的app key之后，请不要对登录密码进行md5加密。
    nim_client_login(appKey, account, token, NULL, &CallbackLogin, NULL);
}
void my_nim_talk_receive_cb_func(const char *result, const char *json_extension, const void *user_data)
{
	printf("recv msg:\n");
	printf("result:%s\n", result);
	printf("json_extension:%s\n", json_extension);
	printf("user_data:%s\n", (const char*)user_data);
	printf("recv msg end\n");
}
void my_nim_sysmsg_receive_cb_func(const char *result, const char *json_extension, const void *user_data)
{
	printf("recv sysmsg:\n");
	printf("result:%s\n", result);
	printf("json_extension:%s\n", json_extension);
	printf("user_data:%s\n", (const char*)user_data);
	printf("recv sysmsg end\n");
}

int main()
{
	const char* config = "{\
                \"global_config\": {\
                \"db_encrypt_key\": \"\",\
                \"preload_attach\": true,\
                \"sdk_log_level\": 6,\
                }}";

    //初始化SDK
    nim_client_init("nim_data", "nim_install", config);
	regist_call_back();
	login();
	//监听事件
	nim_talk_reg_receive_cb(0,my_nim_talk_receive_cb_func,0);
	nim_sysmsg_reg_sysmsg_cb(0,my_nim_sysmsg_receive_cb_func,0); 
	while(true){
		sleep(1);
	}
	return 0;
}

