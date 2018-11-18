#include<bits/stdc++.h>
using namespace std;
const int MAXM = 1e5;
const int HIDECOUNT = 20;
const int SHOWCOUNT = 30;
const int WRONGCNT = 50;
#define keyC1 10
#define keyC2 90
#define keyC3 0.85
#define gen_people() (rand()%MAXM + 1)
#define rep(i,n) for(int i=1;i<=n;i++)
const int N = 100010;
struct customer{
    float credit;
    vector<int> son,pa;
    customer(){
        son.clear();
        pa.clear();
    }
}c[N];
vector<int> badShow,badHide;

void dfsdecrease(int x,float c_2_trans,float c3){
    c[x].credit -= c_2_trans * c3;
    if(c_2_trans<5) return;
    for(int sx : c[x].son)
        dfsdecrease(sx,c_2_trans*c3,c3);
}

void decrease(float c_1,float c_2,float c_3){
    for(int i : badShow){
        for(int j : c[i].pa){
            c[j].credit -= c_1;
            for(int k : c[j].son)
                c[k].credit -= c_1;
        }
        for(int j : c[i].son)
           dfsdecrease(j,c_2,c_3);
    }
}

int main(){
    srand(19260817);
    rep(i,MAXM){
        c[i].credit = 450 + rand()%SHOWCOUNT;
        int inv = rand()%3;
        for(int j=0;j<inv;j++){
            int invi = gen_people();
            if(invi==i){j--;continue;}
            c[i].son.push_back(invi);
            c[invi].pa.push_back(i);
        }
    }
    rep(i,SHOWCOUNT) {
        int p = gen_people();
        badShow.push_back(p);
        c[p].credit = 250 + rand()%SHOWCOUNT;
    }
    rep(i,HIDECOUNT){
        int p = gen_people();
        vector<int>::iterator iter = find(badShow.begin(),badShow.end(),p);
        if(iter==badShow.end())  {
            badHide.push_back(p);
            c[p].credit = 350 + rand()%HIDECOUNT;
        }
        else i--;
    }
    rep(i,HIDECOUNT+4){
        int p1 = rand()%SHOWCOUNT  , p2 = rand()%HIDECOUNT ;
        c[badShow[p1]].son.push_back(badHide[p2]);
        c[badHide[p2]].pa.push_back(badShow[p1]);
    }
    cout<<"The data has been generated!"<<endl;
    decrease(keyC1,keyC2,keyC3);
    int cnt = 0 , cnt2 = 0;
    rep(i,MAXM){
        if(c[i].credit<300){
            cnt2++;
            vector<int>::iterator iter = find(badHide.begin(),badHide.end(),i);
            cnt += (iter!=badHide.end());
        }
    }
    cout<<"The algorithm accurates : "<<1-1.0*abs(cnt2-WRONGCNT)/WRONGCNT<<endl;
    cout<<"The TP is : "<<1.0*cnt2/(cnt2+abs(cnt2-WRONGCNT))<<endl;
    cout<<"The R is : "<<1.0*cnt2/(cnt2+HIDECOUNT-cnt)<<endl;
    return 0;
}