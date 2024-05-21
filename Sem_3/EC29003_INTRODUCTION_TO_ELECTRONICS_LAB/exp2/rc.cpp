#include <bits/stdc++.h>
using namespace std;

const double pi=acos(-1);

int main(){
    double r,c;
    cout<<"Enter R: ";
    cin>>r;
    cout<<"Enter C: ";
    cin>>c;
    double f[8]={50, 150, 450, 1300, 3800, 6500, 11500, 25000};
    //double f[8]={50, 149, 438, 1294, 3818, 11627, 25000, 98150};
    auto calc1=[=](double fr){
        double x=sqrt(1+pow(r*c*2*pi*fr,2));
        return 20*log10(1/x);
    };
    auto calc2=[=](double fr){
        double y=r*c*2*pi*fr;
        double x=sqrt(1+pow(r*c*2*pi*fr,2));
        return 20*log10(y/x);
    };
    cout<<"Low pass:"<<'\n';
    for(auto i:f)
        cout<<calc1(i)<<'\n';
    cout<<"High pass:"<<'\n';
    for(auto i:f)
        cout<<calc2(i)<<'\n';
}