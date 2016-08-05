#include <stdio.h>  
#include <string.h>  


const int MAXQ = 500000+10;  
const int MAXN = 1000000+10;  
const int MAXK = 26; //自动机里字符集的大小  
struct TrieNode  
{  
    TrieNode* fail;  
    TrieNode* next[MAXK];  
    bool danger;   //该节点是否为某模式串的终结点  
    int cnt;    //以该节点为终结点的模式串个数  
    TrieNode()  
    {  
        fail = NULL;  
        memset(next, NULL, sizeof(next));  
        danger = false;  
        cnt = 0;  
    }  
}*que[MAXQ], *root;  
//文本字符串  
char msg[MAXN];  
int   N;  
void TrieInsert(char *s)  
{  
    int i = 0;  
    TrieNode *ptr = root;  
    while(s[i])  
    {  
        int idx = s[i]-'a';  
        if(ptr->next[idx] == NULL)  
            ptr->next[idx] = new TrieNode();  
        ptr = ptr->next[idx];  
        i++;  
    }  
    ptr->danger = true;  
    ptr->cnt++;  
}  

void Init()  
{  
    int i;  
    char s[100];  
    root = new TrieNode();  
    scanf("%d", &N);  
    for(i = 0; i < N; i++)  
    {  
        scanf("%s", s);  
        TrieInsert(s);  
    }  
}  

void Build_AC_Automation()  
{  
    int rear = 1, front = 0, i;  
    que[0] = root;  
    root->fail = NULL;  
    while(rear != front)  
    {  
        TrieNode *cur = que[front++];  
        for(i = 0; i < 26; i++)  
            if(cur->next[i] != NULL)  
            {  
                if(cur == root)  
                    cur->next[i]->fail = root;  
                else  
                {  
                    TrieNode *ptr = cur->fail;  
                    while(ptr != NULL)  
                    {  
                        if(ptr->next[i] != NULL)  
                        {  
                            cur->next[i]->fail = ptr->next[i];  
                            if(ptr->next[i]->danger == true)  
                                cur->next[i]->danger = true;  
                            break;  
                        }  
                        ptr = ptr->fail;  
                    }  
                    if(ptr == NULL) cur->next[i]->fail = root;  
                }  
                que[rear++] = cur->next[i];  
            }  
    }  
}  
int AC_Search()  
{  
    int i = 0, ans = 0;  
    TrieNode *ptr = root;  
    while(msg[i])  
    {  
        int idx = msg[i]-'a';  
        while(ptr->next[idx] == NULL && ptr != root) ptr = ptr->fail;  
        ptr = ptr->next[idx];  
        if(ptr == NULL) ptr = root;  
        TrieNode *tmp = ptr;  
        while(tmp != NULL && tmp->cnt != -1)  
        {  
            ans += tmp->cnt;  
            tmp->cnt = -1;  
            tmp = tmp->fail;  
        }  
        i++;  
    }  
    return ans;  
}  
int main()  
{  
    int T;  
    scanf("%d", &T);  
    while(T--)  
    {  
        Init();  
        Build_AC_Automation();  
        //文本  
        scanf("%s", msg);  
        printf("%d\n", AC_Search());  
    }  
    return 0;  
} 
