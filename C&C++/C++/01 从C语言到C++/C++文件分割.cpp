#include<iostream>
#include<string>
using namespace std;

string str("632242946----chendaxue592256 \
	462084800----13923917670 \
	315984797----yu19880726. \
	492942626----190186 \
	495585175----ut36940258 \
	492527893----13092446031 \
	409966941----mo19841006 \
	648483611----woan.kang \
	497786869----wodeziyou \
	847254279----198602240224 \
	298856022----xyy1435 \
	734717024----820562490 \
	1806105----19780326skyxpf \
	891387663----taolei7765 \
	398209105----panhaili0125 \
	21440800----woshiLIANLIAN \
	460914687----13481335384mei \
	284504153----715616 \
	190258896----000000li \
	450646999----93008412190 \
	116511603----13459889985520 \
	284272413----hebo841014 \
	461238892----wushan461238892 \
	20398924----QQ7972657 \
	591405090----wlx138333 \
	779765066----ldmwan060217 \
	337681311----4448107q \
	389383642----gaomi810514 \
	283318096----ljl5211314");
struct Info
{
	long long QQ;
	string passwd;
};
struct Infos
{
	struct Info* base;
	int size;
}infos;
int getDataNum(string str);
void initInfos();
void splitStr(string str);
void showInfos();
int main333()
{
	initInfos();
	splitStr(str);
	showInfos();

	return 0;
}
//获取以"----"分隔的字符串数量
int getDataNum(string str)
{
	int cnt = -1;
	for(int i = 0; i != str.npos ;i = str.find("----",i+1))
	{
		cnt++;
	}
	return cnt;
}

void initInfos()
{
	infos.size = getDataNum(str);
	infos.base = new Info[infos.size];
}
void showInfos()
{
	cout << "QQ\t\t密码" << endl;;
	for (int i = 0; i < infos.size; i++)
	{
		cout << infos.base[i].QQ << "\t\t" << infos.base[i].passwd << endl;
	}
}

void splitStr(string str)
{
	//把所有空格都替换成'\0'
	for (int i = 0; i != str.npos; i = str.find(' ', i+1))
	{
		str[i] = '\0';
	}
	
	int index = 0;
	for (size_t pos = 0; pos != str.npos; pos = str.find('\0',pos+1),index++)
	{
		string subStr(str.data() + pos + 1);	//取出子串
		size_t nsub = subStr.find("----");      //分解子串
		//存入结构体数组
		sscanf(subStr.data(), "%lld", &infos.base[index].QQ);
		infos.base[index].passwd = subStr.data() + nsub + 4;

		//strcpy(infos.base[index].passwd, subStr.data()+nsub+4);
	}
}
