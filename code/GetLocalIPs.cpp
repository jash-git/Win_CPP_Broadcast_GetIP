//结构体记录ip信息
typedef struct tagIPInfo  
{  
    char ip[30];  
}IPInfo;  

//获取多个ip地址信息列表
bool GetLocalIPs(IPInfo* ips,int maxCnt,int* cnt)  
{  
    //1.初始化wsa  
    WSADATA wsaData;  
    int ret=WSAStartup(MAKEWORD(2,2),&wsaData);  
    if (ret!=0)  
    {  
        return false;  
    }  
    //2.获取主机名  
    char hostname[256];  
    ret=gethostname(hostname,sizeof(hostname));  
    if (ret==SOCKET_ERROR)  
    {  
        return false;  
    }  
    //3.获取主机ip  
    HOSTENT* host=gethostbyname(hostname);  
    if (host==NULL)  
    {  
        return false;  
    }  
    //4.逐个转化为char*并拷贝返回  
    *cnt=host->h_length<maxCnt?host->h_length:maxCnt;  
    for (int i=0;i<*cnt;i++)  
    {  
        in_addr* addr=(in_addr*)*host->h_addr_list;  
        strcpy(ips[i].ip,inet_ntoa(addr[i]));  
    }  
    return true;  
} 