#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main(){	
	int n,cnt;
	vector<string> cur,deal;
	scanf("%d",&n);getchar();
	string temp="";
	char in;
	getchar();
	in=getchar();
	while(in!='\n'){
		temp+=in;
		in=getchar();
		if(in=='/'){
			cur.push_back(temp);
			temp="";
			in=getchar();
		}
	}
	cur.push_back(temp);
	temp="";
	while(n--){
		in=getchar();
		if(in=='/'){
			while(in=='/') in=getchar();
			while(in!='\n'){
				if(in=='.'&&temp.size()==0){
					cnt=1;
					in=getchar();
					while(in=='.'){
						cnt++;
						in=getchar();
					}
					if(cnt>2&&(in=='/'||in=='\n')){
						for(int i=0;i<cnt;i++) temp+='.';
						deal.push_back(temp);
						temp="";
					}
					else if(in!='/'&&in!='\n'){
						for(int i=0;i<cnt;i++) temp+='.';
					}
					else if(in=='/'||in=='\n'){
						if(cnt==2&&deal.size()) deal.pop_back();
					}
					if(in=='/'){
						in=getchar();
						continue;
					} 
					if(in=='\n'){
						if(temp.size()) deal.push_back(temp);
						temp="";
						break;
					} 
				}
				temp+=in;
				in=getchar();
				if(in=='/'){
					deal.push_back(temp);
					temp="";
					if(in=='\n'){
						deal.push_back(temp);
						break;
						temp="";
					} 
					while(in=='/') in=getchar();
				}
				else if(in=='\n'){
					deal.push_back(temp);
					temp="";
				} 
			}
		}
		else if(in=='.'){
			deal=cur;
			cnt=0;
			while(in!='\n'){
				if(in=='.'&&temp.size()==0){
					cnt=1;
					in=getchar();
					while(in=='.'){
						cnt++;
						in=getchar();
					}
					if(cnt>2&&(in=='/'||in=='\n')){
						for(int i=0;i<cnt;i++) temp+='.';
						deal.push_back(temp);
						temp="";
					}
					else if(in!='/'&&in!='\n'){
						for(int i=0;i<cnt;i++) temp+='.';
					}
					else if(in=='/'||in=='\n'){
						if(cnt==2&&deal.size()) deal.pop_back();
					}
					if(in=='/'){
						in=getchar();
						continue;
					} 
					if(in=='\n'){
						if(temp.size()) deal.push_back(temp);
						temp="";
						break;
					} 
				}
				temp+=in;
				in=getchar();
				if(in=='/'){
					deal.push_back(temp);
					temp="";
					while(in=='/') in=getchar();
					if(in=='\n'){
						deal.push_back(temp);
						temp="";
					} 
				}
				else if(in=='\n'){
					deal.push_back(temp);
					temp="";
				} 
			}
		}
		else if(in=='\n') deal=cur;
		if(!deal.size()){
			printf("/\n");
			continue;
		}
		for(int i=0;i<deal.size();i++){
			printf("/%s",deal[i].c_str());
		}
		putchar('\n');
		deal.clear();
	}
	return 0;
}

#include <set>
#include <ctime>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

//#pragma comment(linker, "/STACK:1024000000,1024000000")

#define FIN             freopen("input.txt","r",stdin)
#define FOUT            freopen("output.txt","w",stdout)
#define fst             first
#define snd             second

//typedef __int64 LL;
typedef long long LL;
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;
const int MAXN = 1000 + 15;
int N;
string cur, str;
stack<string> stk1, stk2;
/**
 * 转化为绝对路径
 */
void toABSPath (string& s) {
    string buf;
    if (s[0] != '/') {
        buf = cur;
        buf += '/';
        buf += s;
        s = buf;
    }
}
/**
 * 将字符串正则化
 */
void reg (string& s) {
    string sx = "";
    int len = s.length();
    for (int i = 0; i <= len; i++) {
        if (s[i] == '/' || i == len) {
            if (sx != "" && sx != ".") {
                if (sx == "..") {
                    if (!stk1.empty() )
                        stk1.pop();
                } else {
                    stk1.push (sx);
                }
            }
            sx = "";
        } else {
            sx += s[i];
        }
    }
    while (!stk1.empty() ) {
        sx = stk1.top();
        stk1.pop();
        stk2.push (sx);
    }
    bool fst = true;
    s = "/";
    while (!stk2.empty() ) {
        sx = stk2.top();
        stk2.pop();
        if (fst) {
            fst = false;
        } else {
            s += "/";
        }
        s += sx;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    FIN;
#endif // ONLINE_JUDGE
    int len;
    ios::sync_with_stdio (false);
    while (cin >> N) {
        cin >> cur;
        cin.ignore();
        for (int i = 0; i < N; i ++) {
            getline (cin, str);
            len = str.length();
            if (len == 0) {
                cout << cur << endl;
                continue;
            }
            toABSPath (str);
            reg (str);
            cout << str << endl;
        }
    }
    return 0;
}