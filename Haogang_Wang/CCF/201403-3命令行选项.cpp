#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int can[26];
bool mo[26];
string shu[26];
int main(void){
	string a;
	while(cin>>a){
		memset(can,0,sizeof(can));
		for(int i=0;i<a.size();i++){
			if(isalpha(a[i])){
				if(i+1<a.size()&&a[i+1]==':') 
					can[a[i]-'a']=2;
				else can[a[i]-'a']=1;
			}
		}
		int n;
		scanf("%d",&n);getchar();
		for(int k=1;k<=n;k++){
			memset(mo,false,sizeof(mo));
			getline(cin,a);
			printf("Case %d:",k);
			int i=0;
			while(i<a.size()&&a[i]!=' ') i++;
			i++;
			for(;i<a.size();){
				if(a[i]=='-'&&i+1<a.size()&&a[i+1]>='a'
					&&a[i+1]<='z'&&(i+2==a.size()||a[i+2]==' ')){
						i++;
						if(can[a[i]-'a']==1){
							mo[a[i]-'a']=true;
							i+=2;
						}
						else if(can[a[i]-'a']==2){
							int t=a[i]-'a';
							mo[t]=true;
							shu[t]="";
							i+=2;
							while(i<a.size()&&a[i]!=' ')
								shu[t]+=a[i++];
							if(shu[t]=="") {
								break;
							}
							i++; 
						}
						else break;
				}
				else break;
			}
			for(int i=0;i<26;i++){
				if(mo[i]){
					printf(" -%c",'a'+i);
					if(can[i]==2) cout<<" "<<shu[i];
				}
			}
			putchar('\n');
		}
	}
    return 0;
}

#include<iostream>
#include<string>
#include<map> //map���Զ�����
using namespace std;
int main(){
 int N,i,first,second,index,flag;
 string letters,cmds,tmp,parameter;
 map<string,string> m;
 cin>>letters>>N;
 getline(cin,cmds);
 for(i = 0; i < N; i++){
  getline(cin,cmds);
  first = cmds.find(" ");
  while(first > 0){
  flag=0; //�мǳ�ʼ�����˴���δ��ʼ����20�֣�
   cmds = cmds.substr(first+1,cmds.length()-first-1);
   second = cmds.find(" ");
   if(second < 0)
   {
    flag=1;
    second = cmds.length();
   }// break;
   
   tmp = cmds.substr(0,second);
   if(tmp.length() == 2 && tmp[0] == '-'){
    index = letters.find(tmp[1]);
    if(index >= 0){    
     if(index+1 < letters.length() &&letters[index+1] == ':'){ //������
     	if(flag==1) break;//��������������ls -w,�򱨴�,���޲Σ�����ls -a������ȷ����
     	else
     	{
      		cmds = cmds.substr(second+1,cmds.length()-second-1);
      		second = cmds.find(" ");
      		if(second < 0) second = cmds.length();
      		parameter = cmds.substr(0,second);
      		if(m.count(tmp))//ʹ��count���map������ĳ���Ƿ����
       			m.erase(tmp); //���ڣ���ɾ��  //�����ظ����
      		m.insert(pair<string,string>(tmp,parameter)); 
     	}
     }
     else
     {
       if(m.count(tmp))//ʹ��count���map������ĳ���Ƿ����
       m.erase(tmp); //���ڣ���ɾ��
        m.insert(pair<string,string>(tmp,"")); //�����ظ����
     }
     
     first = cmds.find(" "); 
        
    }
    else break; //���������
   }
   else break;  //��������  
  }
  cout<<"Case "<<i+1<<":";
  map<string,string>::iterator it = m.begin();  //mapĬ�����ź����
  while(it != m.end()){
   cout<<" "<<it->first;
   if(it->second !="")
    cout<<" "<<it->second;
   ++it;
  }
  cout<<endl;
  m.clear();  
 }
 return 0;
}