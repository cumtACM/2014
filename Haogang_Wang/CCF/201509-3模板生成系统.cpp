#include <iostream>
#include <cstdio> 
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std; 

struct pos{
	int r,c;
	pos(int a,int b):r(a),c(b){}
};
vector<pos> cnt;
vector<int> rec[100];
map<string,vector<int> > tih;
string ans[100];
int main(){
	int n,m;
	char c;
	string var,value;
	while(scanf("%d %d",&m,&n)==2){
		getchar();
		tih.clear();
		cnt.clear();
		for(int i=0;i<m;i++){
			rec[i].clear();
			ans[i]="";
			while(true){
				c=getchar();
				if(c=='\n') break;
				if(c=='{'){
					c=getchar();
					if(c=='{'){
						var="";
						getchar();
						do{
							c=getchar();
							if(c==' '){
								getchar();getchar();
								cnt.push_back(pos(i,ans[i].size()));
								if(!tih.count(var)){
									vector<int> temp;
									temp.push_back(cnt.size()-1);
									tih[var]=temp;
								}
								else tih[var].push_back(cnt.size()-1);
								rec[i].push_back(cnt.size()-1);
								break;
							}
							var.push_back(c);
						}while(true);
					}
					else ans[i].push_back('{'),ans[i].push_back(c);
					continue;
				}
				ans[i].push_back(c);
			}
		}
		while(n--){
			cin>>var;
			value="";
			do{
				c=getchar();
			}while(c!='\"');
			do{
				c=getchar();
				if(c=='\"') break;
				value.push_back(c);
			}while(true);
			getchar();
			vector<int> p=tih[var];
			for(int i=0;i<p.size();i++){
				int row=cnt[p[i]].r,col=cnt[p[i]].c;
				ans[row].insert(col,value);
				for(int j=0;j<rec[row].size();j++){
					int v=rec[row][j];
					if(cnt[v].c>col){
						cnt[v].c+=value.size();
					}
				}
			}
		}
		for(int i=0;i<m;i++)
			cout<<ans[i]<<endl;
	} 
	return 0;
}

#include <iostream>
#include <cstdio> 
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std; 

map<string,string> tih;
string ans[100];
int main(){
	int n,m;
	char c;
	string var,value;
	while(scanf("%d %d",&m,&n)==2){
		getchar();
		tih.clear();
		for(int i=0;i<m;i++)
			getline(cin,ans[i]);
		while(n--){
			cin>>var;
			value="";
			do{
				c=getchar();
			}while(c!='\"');
			do{
				c=getchar();
				if(c=='\"') break;
				value.push_back(c);
	
			}while(true);
			getchar();
			tih.insert(map<string,string>::value_type(var,value));
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<ans[i].size();){
				if(ans[i][j]=='{'&&j+1<ans[i].size()&&ans[i][j+1]=='{'){
					j+=3;
					string temp="";
					while(ans[i][j]!=' '){
						temp+=ans[i][j];
						j++;
					}
					j+=3;
					if(tih.count(temp)) cout<<tih[temp];
				}
				else putchar(ans[i][j++]);
			}
			putchar('\n');
		}
	} 
	return 0;
}