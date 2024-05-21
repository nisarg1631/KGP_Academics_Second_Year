#include <bits/stdc++.h>
using namespace std;

struct point{
    int x,y,ind;
    point(int _x, int _y, int _ind){
        x=_x;
        y=_y;
        ind=_ind;
    }
};

int n;
double mn=1e20l;
vector<point> px;
point ans1(0,0,0), ans2(0,0,0);

double dist(const point &p1, const point &p2){
    return sqrtl(powl(p1.x-p2.x,2)+powl(p1.y-p2.y,2));
}

void get_closest_pair(int l, int r, vector<point> &py){
    if((r-l+1)<=3){
        for(int i=l; i<=r; i++)
            for(int j=i+1; j<=r; j++)
                if(dist(px[i],px[j])<mn){
                    mn=dist(px[i],px[j]);
                    ans1=px[i];
                    ans2=px[j];
                }
        return;
    }
    int mid=(l+r)/2;
    vector<point> y_left, y_right;
    for(int i=0; i<(int)py.size(); i++){
        if(py[i].x<=px[mid].x) y_left.push_back(py[i]);
        else y_right.push_back(py[i]); 
    }
    get_closest_pair(l,mid,y_left);
    get_closest_pair(mid+1,r,y_right);
    vector<point> strip;
    for(int i=0; i<(int)py.size(); i++){
        if(abs(py[i].x-px[mid].x)<=mn) strip.push_back(py[i]);
    }
    for(int i=0; i<strip.size(); i++){
        for(int j=i+1; j<strip.size() && (strip[j].y-strip[i].y)<=mn; j++)
            if(dist(strip[i],strip[j])<mn){
                mn=dist(strip[i],strip[j]);
                ans1=strip[i];
                ans2=strip[j];
            }
    }
}

int main(){
    cin>>n;
    vector<point> py;
    int x,y;
    for(int i=0; i<n; i++){
        cin>>x>>y;
        px.push_back(point(x,y,i));
        py.push_back(point(x,y,i));
    }
    sort(px.begin(), px.end(), [](const point &p1, const point &p2){
        return p1.x<p2.x;
    });
    sort(py.begin(), py.end(), [](const point &p1, const point &p2){
        return p1.y<p2.y;
    });
    get_closest_pair(0,n-1,py);
    cout<<fixed<<setprecision(6);
    cout<<min(ans1.ind,ans2.ind)<<" "<<max(ans1.ind,ans2.ind)<<" "<<mn<<endl;
    return 0;
}