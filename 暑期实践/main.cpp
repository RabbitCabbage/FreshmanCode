#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

vector<string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;
  
  while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
      if(s[i] == seperator[x]){
          ++i;
          flag = 0;
           break;
      }
    }
    
    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
      if(s[j] == seperator[x]){
          flag = 1;
      break;
      }
      if(flag == 0) 
      ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

int main() {
    string keyword;
    while(1){
        cin>>keyword;
        cout<<""<<endl;
        cout<<keyword<<endl;
        if(keyword=="双减了解程度"){
            int wanquan=0,lueyou=0,yiban=0,bububu=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "完全了解")wanquan++;
                else if(learning == "略有耳闻")lueyou++;
                else if(learning=="一般")yiban++;
                else if(learning =="完全不了解")bububu++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"完全了解\t"<<wanquan<<" 占比："<<(double)wanquan/total<<endl;
            cout<<"略有耳闻\t"<<lueyou<<" 占比："<<(double)lueyou/total<<endl;
            cout<<"一般\t"<<yiban<<" 占比："<<(double)yiban/total<<endl;
            cout<<"完全不了解\t"<<bububu<<" 占比："<<(double)bububu/total<<endl;
        }
        if(keyword=="高中工作日每天学习时长"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,twelve_13=0,thirteen_14=0,fourteen_15=0,fifteen_16=0,sixteen=0;
            int total=0;
            string learning;
            double average=0;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "9小时以下")nine++,average+=8;
                else if(learning == "9-10小时")nine_ten++,average+=9.5;
                else if(learning=="10-11小时")++ten_11,average+=10.5;
                else if(learning =="11-12小时")eleven_12++,average+=11.5;
                else if(learning == "12-13小时")twelve_13++,average+=12.5;
                else if(learning=="13-14小时")thirteen_14++,average+=13.5;
                else if(learning =="14-15小时")fourteen_15++,average+=14.5;
                else if(learning == "15-16小时")fifteen_16++,average+=15.5;
                else if(learning=="16小时以上")sixteen++,average+=17;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<""<<endl;
            cout<<"9小时以下\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"9-10小时\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"10-11小时\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"11-12小时\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"12-13小时\t"<<twelve_13<<" 占比："<<(double)twelve_13/total<<endl;
            cout<<"13-14小时\t"<<thirteen_14<<" 占比："<<(double)thirteen_14/total<<endl;
            cout<<"14-15小时\t"<<fourteen_15<<" 占比："<<(double)fourteen_15/total<<endl;
            cout<<"15-16小时\t"<<fifteen_16<<" 占比："<<(double)fifteen_16/total<<endl;
            cout<<"16小时以上\t"<<sixteen<<" 占比："<<(double)sixteen/total<<endl;
        }
        if(keyword=="完成作业的时间"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,after_12=0,wanzixi=0,ziji=0,xiebuwan=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "9点前")nine++;
                else if(learning == "9-10点")nine_ten++;
                else if(learning=="10-11点")++ten_11;
                else if(learning =="11-12点")eleven_12++;
                else if(learning == "12点以后")after_12++;
                else if(learning == "都不是，有时候不能及时完成作业")xiebuwan++;
                else if(learning=="都不是，我上晚自习前就可完成所有学校作业")wanzixi++;
                else if(learning =="都不是，我宁愿先完成自己的作业安排")ziji++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"9点\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"9-10点\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"10-11点\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"11-12点\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"12点以后\t"<<after_12<<" 占比："<<(double)after_12/total<<endl;
            cout<<"都不是，我上晚自习前就可完成所有学校作业\t"<<wanzixi<<" 占比："<<(double)wanzixi/total<<endl;
            cout<<"都不是，有时候不能及时完成作业\t"<<xiebuwan<<" 占比："<<(double)xiebuwan/total<<endl;
            cout<<"都不是，我宁愿先完成自己的作业安排\t"<<ziji<<" 占比："<<(double)ziji/total<<endl;
        }
        if(keyword=="高中睡眠时长"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,twelve_13=0,thirteen_14=0;
            int total=0;
            string learning;
            double average=0;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "四小时以内")nine++,average+=4;
                else if(learning == "4-5小时")nine_ten++,average+=4.5;
                else if(learning=="5-6小时")++ten_11,average+=5.5;
                else if(learning =="6-7小时")eleven_12++,average+=6.5;
                else if(learning == "7-8小时")twelve_13++,average+=7.5;
                else if(learning=="八小时以上")thirteen_14++,average+=8.5;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<""<<endl;
            cout<<"四小时以内\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"4-5小时\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"5-6小时\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"6-7小时\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"7-8小时\t"<<twelve_13<<" 占比："<<(double)twelve_13/total<<endl;
            cout<<"八小时以上\t"<<thirteen_14<<" 占比："<<(double)thirteen_14/total<<endl;
        }
        if(keyword=="睡觉时间"){
            int nine_ten=0,ten_11=0,eleven_12=0,twelve_13=0,thirteen_14=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "10点以前")nine_ten++;
                else if(learning=="10-11点")++ten_11;
                else if(learning =="11-12点")eleven_12++;
                else if(learning == "12-1点")twelve_13++;
                else if(learning=="凌晨1点以后")thirteen_14++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"10点以前\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"10-11点\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"11-12点\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"12-1点\t"<<twelve_13<<" 占比："<<(double)twelve_13/total<<endl;
            cout<<"凌晨1点以后\t"<<thirteen_14<<" 占比："<<(double)thirteen_14/total<<endl;
        }
        if(keyword=="午休情况"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,twelve_13=0,thirteen_14=0,fourteen_15=0,fifteen_16=0,sixteen=0;
            int total=0;
            string learning;
            double average=0;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "我没有午休时间")nine++;
                else if(learning == "十分钟以内")nine_ten++,average+=10;
                else if(learning=="10-30分钟")++ten_11,average+=20;
                else if(learning =="0.5-1小时")eleven_12++,average+=45;
                else if(learning == "1-1.5小时")twelve_13++,average+=75;
                else if(learning=="1.5小时以上")thirteen_14++,average+=90;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            cout<<"我没有午休时间\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"10分钟以内\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"10-30分钟\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"0.5-1小时\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"1-1.5小时\t"<<twelve_13<<" 占比："<<(double)twelve_13/total<<endl;
            cout<<"1.5小时以上\t"<<thirteen_14<<" 占比："<<(double)thirteen_14/total<<endl;
        }
        if(keyword=="学习任务情况"){
            int yes=0,no=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "是，内外环境压迫带来动力")yes++;
                else if(learning == "否，他强任他强，明月照大江")no++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"是，内外环境压迫带来压力\t"<<yes<<" 占比："<<(double)yes/total<<endl;
            cout<<"否，他强任他强，明月照大江\t"<<no<<" 占比："<<(double)no/total<<endl;
        }
        if(keyword=="完成自己任务的时间"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,after_12=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "9点以前")nine++;
                else if(learning == "9-10点")nine_ten++;
                else if(learning=="10-11点")++ten_11;
                else if(learning =="11-12点")eleven_12++;
                else if(learning == "12点以后")after_12++;
                else if(learning == "(跳过)"){
                    total--;
                    continue;
                }
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"9点前\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"9-10点\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"10-11点\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"11-12点\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"12点以后\t"<<after_12<<" 占比："<<(double)after_12/total<<endl;
        }
        if(keyword=="补课科目"){
            int chinese=0,maths=0,english=0,physics=0,chemistry=0,biology=0,geography=0,history=0,politics=0,selfteaching=0;
            int total_extra_learning=0;
            int total_people=0;
            string learning;
            while(1){
                cin>>learning;
                auto res = split(learning,"|\n");
                    total_people++;
                    bool flag=false;
                    for(auto p=res.begin();p!=res.end();++p){
                        total_extra_learning++;
                        if(*p=="语文")chinese++;
                        else if(*p=="数学")maths++;
                        else if(*p=="英语")english++;
                        else if(*p=="物理")physics++;
                        else if(*p=="化学")chemistry++;
                        else if(*p=="生物")biology++;
                        else if(*p=="地理")geography++;
                        else if(*p=="政治")politics++;
                        else if(*p=="历史")history++;
                        else if(*p=="不补课，自学YYDS"){
                            selfteaching++;
                        }
                        else{
                            // cout<<*p<<"afghsdfhadfa"<<endl;
                            total_extra_learning--;
                            total_people--;
                            flag=true;
                            break;
                        }
                    }
                    if(flag)break;
            }
            cout<<"样本总量"<<total_people<<endl;
            cout<<"其中不补习的有"<<selfteaching<<" 占比："<<(double)selfteaching/total_people<<endl;
            cout<<"补习的有"<<total_people-selfteaching<<" 占比："<<(double)(total_people-selfteaching)/total_people<<endl;
            cout<<"在补习的同学中"<<endl;
            cout<<"语文\t"<<chinese<<" 占比："<<(double)chinese/total_extra_learning<<endl;
            cout<<"数学\t"<<maths<<" 占比："<<(double)maths/total_extra_learning<<endl;
            cout<<"英语\t"<<english<<" 占比："<<(double)english/total_extra_learning<<endl;
            cout<<"物理\t"<<physics<<" 占比："<<(double)physics/total_extra_learning<<endl;
            cout<<"化学\t"<<chemistry<<" 占比："<<(double)chemistry/total_extra_learning<<endl;
            cout<<"生物\t"<<biology<<" 占比："<<(double)biology/total_extra_learning<<endl;
            cout<<"地理\t"<<geography<<" 占比："<<(double)geography/total_extra_learning<<endl;
            cout<<"历史\t"<<history<<" 占比："<<(double)history/total_extra_learning<<endl;
            cout<<"政治\t"<<politics<<" 占比："<<(double)politics/total_extra_learning<<endl;
        }
        if(keyword=="高中每周补习时长"){
            int two=0,two_4=0,four_6=0,six_8=0,eight=0,none=0;
            int total=0;
            string learning;
            double average =0;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "两小时以内")two++,average+=1;
                else if(learning == "2-4小时")two_4++,average+=3;
                else if(learning=="4-6小时")++four_6,average+=5;
                else if(learning =="6-8小时")six_8++,average+=7;
                else if(learning == "我不补课")none++,average+=0;
                else if(learning=="8小时以上")eight++,average+=9;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            cout<<"两小时以内\t"<<two<<" 占比："<<(double)two/total<<endl;
            cout<<"2-4小时\t"<<two_4<<" 占比："<<(double)two_4/total<<endl;
            cout<<"4-6小时\t"<<four_6<<" 占比："<<(double)four_6/total<<endl;
            cout<<"6-8小时\t"<<six_8<<" 占比："<< (double)six_8/total<<endl;
            cout<<"8小时\t"<<eight<<" 占比："<<(double)eight/total<<endl;
            cout<<"我不补课\t"<<none<<" 占比："<<(double)none/total<<endl;
        }
        if(keyword=="小学压力"){
            int pressure[5];
            memset(pressure,0,sizeof(pressure)); 
            int total=0;
            string number;
            double average =0;
            while(1){
                cin>>number;
                if(number[0]-'0'>9||number[0]-'0'<0)break;
                average+=number[0]-'0';
                total++;
                pressure[number[0]-'0'-1]++;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            for(int i=0;i<5;++i){
                cout<<i+1<<" "<<pressure[i]<<" 占比："<<(double)pressure[i]/total<<endl;
            }
        }
        if(keyword=="初中压力"){
            int pressure[5];
            memset(pressure,0,sizeof(pressure)); 
            int total=0;
            string number;
            double average=0;
            while(1){
                cin>>number;
                if(number[0]-'0'>9||number[0]-'0'<0)break;
                average+=number[0]-'0';
                total++;
                pressure[number[0]-'0'-1]++;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            for(int i=0;i<5;++i){
                cout<<i+1<<" "<<pressure[i]<<" 占比："<<(double)pressure[i]/total<<endl;
            }
        }
        if(keyword=="高一高二压力"){
            int pressure[5];
            memset(pressure,0,sizeof(pressure)); 
            int total=0;
            double average=0;
            string number;
            while(1){
                cin>>number;
                if(number[0]-'0'>9||number[0]-'0'<0)break;
                total++;
                average+=number[0]-'0';
                pressure[number[0]-'0'-1]++;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            for(int i=0;i<5;++i){
                cout<<i+1<<" "<<pressure[i]<<" 占比："<<(double)pressure[i]/total<<endl;
            }
        }
        if(keyword=="高三压力"){
            int pressure[5];
            memset(pressure,0,sizeof(pressure)); 
            int total=0;
            string number;
            double average=0;
            while(1){
                cin>>number;
                if(number[0]-'0'>9||number[0]-'0'<0)break;
                total++;
                average+=number[0]-'0';
                pressure[number[0]-'0'-1]++;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"平均值"<<average/total<<endl;
            cout<<"中位数"<<endl;
            for(int i=0;i<5;++i){
                cout<<i+1<<" "<<pressure[i]<<" 占比："<<(double)pressure[i]/total<<endl;
            }
        }
        if(keyword=="作业类型"){
            int changgui=0,chengfa=0,tanjiu=0,koutou=0,quwei=0;
            int total_homework=0;
            int total_people=0;
            string learning;
            while(1){
                cin>>learning;
                    auto res = split(learning,"|\n");
                    total_people++;
                    bool flag=false;
                    for(auto p=res.begin();p!=res.end();++p){
                        total_homework++;
                        if(*p=="常规作业")changgui++;
                        else if(*p=="惩罚性作业")chengfa++;
                        else if(*p=="探究性作业")tanjiu++;
                        else if(*p=="口头作业")koutou++;
                        else if(*p=="趣味型作业")quwei++;
                        else{
                            flag=true;
                            total_homework--;
                            total_people--;
                            break;
                        }
                    }
                if(flag)break;
            }
            cout<<"样本总量"<<total_people<<endl;
            cout<<"常规作业\t"<<changgui<<" 占比："<<(double)changgui/total_homework<<endl;
            cout<<"惩罚性作业\t"<<chengfa<<" 占比："<<(double)chengfa/total_homework<<endl;
            cout<<"探究性作业\t"<<tanjiu<<" 占比："<<(double)tanjiu/total_homework<<endl;
            cout<<"口头作业\t"<<koutou<<" 占比："<<(double)koutou/total_homework<<endl;
            cout<<"趣味型作业\t"<<quwei<<" 占比："<<(double)quwei/total_homework<<endl;
        }
        if(keyword=="双减培养兴趣和综合素质赞成程度"){
            int wanquan=0,zantong=0,yiban=0,youdianbu=0,bububu=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "完全赞同")wanquan++;
                else if(learning == "赞同")zantong++;
                else if(learning=="一般")yiban++;
                else if(learning=="有点不赞同")youdianbu++;
                else if(learning =="完全不赞同")bububu++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"完全赞同\t"<<wanquan<<" 占比："<<(double)wanquan/total<<endl;
            cout<<"赞同\t"<<zantong<<" 占比："<<(double)zantong/total<<endl;
            cout<<"一般\t"<<yiban<<" 占比："<<(double)yiban/total<<endl;
            cout<<"有点不赞同"<<youdianbu<<" 占比："<<(double)youdianbu/total<<endl;
            cout<<"完全不赞同\t"<<bububu<<" 占比："<<(double)bububu/total<<endl;
        }
        if(keyword=="双减影响学习生活赞成程度"){
            int wanquan=0,zantong=0,yiban=0,youdianbu=0,bububu=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "完全赞同")wanquan++;
                else if(learning == "赞同")zantong++;
                else if(learning=="一般")yiban++;
                else if(learning=="有点不赞同")youdianbu++;
                else if(learning =="完全不赞同")bububu++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"完全赞同\t"<<wanquan<<" 占比："<<(double)wanquan/total<<endl;
            cout<<"赞同\t"<<zantong<<" 占比："<<(double)zantong/total<<endl;
            cout<<"一般\t"<<yiban<<" 占比："<<(double)yiban/total<<endl;
            cout<<"有点不赞同"<<youdianbu<<" 占比："<<(double)youdianbu/total<<endl;
            cout<<"完全不赞同\t"<<bububu<<" 占比："<<(double)bububu/total<<endl;
        }
        if(keyword=="自主科普情况"){
            int yes=0,no=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "会")yes++;
                else if(learning == "不会")no++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"会\t"<<yes<<" 占比："<<(double)yes/total<<endl;
            cout<<"不会\t"<<no<<" 占比："<<(double)no/total<<endl;
        }
        if(keyword=="自主科普的渠道"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,after_12=0,a=0,b=0,c=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                auto res = split(learning,"|[]\n");
                bool flag =false;
                for(auto p=res.begin();p!=res.end();p++){
                    total ++;
                if(*p == "知乎.开眼等APP")nine++;
                else if(*p == "bilibili")nine_ten++;
                else if(*p=="各种讲座（学校，公共）")++ten_11;
                else if(*p =="书籍")eleven_12++;
                else if(*p == "电视")after_12++;
                else if(*p=="百度百科等搜索引擎")a++;
                else if(*p=="微信公众号")b++;
                else if(*p=="其他"){
                    c++;
                    ++p;
                    //cout<<*p<<endl;
                }
                else if(*p == "(跳过)")continue;
                else {
                    total--;
                    flag = true;
                    break;
                }
                }
                if(flag)break;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"知乎、开眼等APP\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"bilibili\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"各种讲座（学校、公共）\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"书籍\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"电视\t"<<after_12<<" 占比："<<(double)after_12/total<<endl;
            cout<<"百度百科等搜索引擎\t"<<a<<" 占比："<<(double)a/total<<endl;
            cout<<"微信公众号\t"<<b<<" 占比："<<(double)b/total<<endl;
            cout<<"其他\t"<<c<<" 占比："<<(double)c/total<<endl;
        }
        if(keyword=="感兴趣的科普主题"){
            int nine=0,nine_ten=0,ten_11=0,eleven_12=0,after_12=0,a=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                bool flag =false;
                auto res = split(learning,"[]|\n");
                for(auto p=res.begin();p!=res.end();p++){
                total ++;
                if(*p == "自然科学（物理，化学，生物等）")nine++;
                else if(*p == "心理学，认知与行为学等")nine_ten++;
                else if(*p=="生活相关（健身，膳食等）")++ten_11;
                else if(*p =="人文科学（历史，文学，艺术等）")eleven_12++;
                else if(*p == "社会科学（国际博弈论，宗教文化等）")after_12++;
                else if(*p =="其他"){
                    a++;
                    ++p;
                    //cout<<*p<<endl;
                }
                else if(*p == "(跳过)")continue;
                else {
                    total--;
                    flag = true;
                    break;
                }
                }
                if(flag)break;
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"自然科学（物理，化学，生物等）\t"<<nine<<" 占比："<<(double)nine/total<<endl;
            cout<<"心理学，认知与行为学等\t"<<nine_ten<<" 占比："<<(double)nine_ten/total<<endl;
            cout<<"生活相关（健身，膳食等）\t"<<ten_11<<" 占比："<<(double)ten_11/total<<endl;
            cout<<"人文科学（历史，文学，艺术等）\t"<<eleven_12<<" 占比："<<(double)eleven_12/total<<endl;
            cout<<"社会科学（国际博弈论，宗教文化等）\t"<<after_12<<" 占比："<<(double)after_12/total<<endl;
            cout<<"其他\t"<<a<<" 占比："<<(double)a/total<<endl;
        }
        if(keyword=="高中科普讲座频率"){
            int bujuban=0,meizhou=0,shuci=0,qita=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "不举办")bujuban++;
                else if(learning == "每周都有")meizhou++;
                else if(learning=="一学期数次")shuci++;
                else {
                    auto res = split(learning,"[]\n");
                    if(res[0]=="其他"){
                        qita++;
                        //cout<<res[1]<<endl;
                    }
                    else{
                    total--;
                    break;
                    }
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"不举办\t"<<bujuban<<" 占比："<<(double)bujuban/total<<endl;
            cout<<"每周都有\t"<<meizhou<<" 占比："<<(double)meizhou/total<<endl;
            cout<<"一学期数次\t"<<shuci<<" 占比："<<(double)shuci/total<<endl;
            cout<<"其他"<<qita<<" 占比："<<(double)qita/total<<endl;
        }
        if(keyword=="喜爱科普情况"){
            int yes=0,no=0;
            int total=0;
            string learning;
            while(1){
                cin>>learning;
                total ++;
                if(learning == "喜欢，这会拓展我的视野")yes++;
                else if(learning == "不喜欢，会占用我的时间，增加我的负担")no++;
                else {
                    total--;
                    break;
                }
            }
            cout<<"样本总量"<<total<<endl;
            cout<<"喜欢，这会拓展我的视野\t"<<yes<<" 占比："<<(double)yes/total<<endl;
            cout<<"不喜欢，会占用我的时间，增加我的负担\t"<<no<<" 占比："<<(double)no/total<<endl;
        }
        if(keyword=="喜欢的宣传类型"){
            int changgui=0,chengfa=0,tanjiu=0,koutou=0;
            int total_homework=0;
            int total_people=0;
            string learning;
            while(1){
                cin>>learning;
                    auto res = split(learning,"|\n");
                    total_people++;
                    bool flag =false;
                    for(auto p=res.begin();p!=res.end();++p){
                        total_homework++;
                        if(*p=="线上科普")changgui++;
                        else if(*p=="线下讲解")chengfa++;
                        else if(*p=="科普动画")tanjiu++;
                        else if(*p=="模拟实验")koutou++;
                        else{
                            total_homework--;
                            total_people--;
                            flag =true;
                            break;
                        }
                    }
                    if(flag)break;
            }
            cout<<"样本总量"<<total_homework<<endl;
            cout<<"线上科普\t"<<changgui<<" 占比："<<(double)changgui/total_homework<<endl;
            cout<<"线下讲解\t"<<chengfa<<" 占比："<<(double)chengfa/total_homework<<endl;
            cout<<"科普动画\t"<<tanjiu<<" 占比："<<(double)tanjiu/total_homework<<endl;
            cout<<"模拟实验\t"<<koutou<<" 占比："<<(double)koutou/total_homework<<endl;
        }
        if(keyword=="end")break;
    }
    return 0;
}
