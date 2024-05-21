#include <iostream>
#include <cmath>
using namespace std;

/* utitlity functions */

int gcd(int a, int b){
    a=abs(a);
    b=abs(b);
    while(b){
        a=a%b;
        swap(a,b);
    }
    return a;
}

bool isPerfectSquare(int a){
    if(a<0)
        return false;
    double root=sqrt(a);
    if(abs(root-round(root))<1e-6)
        return true;
    else
        return false;
}

/* ------------------ */

/* special numbers */

class splnum{

    private:
        int a, b, c, d;

    public:
        //default initialization
        splnum() : a(0), b(0), c(1), d(0) {}
        //initialisation from values
        splnum(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {
            normalise();
        }

        //ensures a, b, c, and d follow the standard convention as asked in the assignment
        // 1. makes c positive if not already so
        // 2. absorbs the contribution of d to a if d is a perfect square
        // 3. ensures gcd(a,b,c)=1
        void normalise(){
            if(isPerfectSquare(d)){
                b*=(int)round(sqrt(d));
                a+=b;
                b=d=0;
            }
            if(c<0){
                c=-c;
                a=-a;
                b=-b;
            }
            if(b==0){
                d=0;
            }
            int common=gcd(a,gcd(b,c));
            a/=common;
            b/=common;
            c/=common;
        }

        bool isZero() const{
            return (a==0 && b==0);
        }

        splnum inverse() const{
            //returns 0 if inverse doesn't exist
            if(isZero())
                return splnum();
            else
                return splnum(a*c, -b*c, (a*a)-(b*b*d), d);
        }

        void print(){
            if(isZero()){
                cout<<0;
                return;
            }
            cout<<((a && b && (c!=1)) ? "(" : "");
            if(a){
                cout<<a;
                cout<<(b ? " " : "");
            }
            if(b){
                cout<<((b>0 && a) ? "+ " : "");
                cout<<(b<0 ? "- " : "");
                abs(b)!=1 ? cout<<abs(b)<<" " : cout<<"";
                cout<<"sqrt("<<d<<")";
            }
            cout<<((a && b && (c!=1)) ? ")" : "");
            if(c!=1){
                cout<<" / "<<c;
            }
        }

        //addition
        splnum operator+(const splnum& n){
            int a1=n.a;
            int b1=n.b;
            int c1=n.c;
            int d1=(d ? d : n.d);
            return splnum((a*c1)+(a1*c), (b*c1)+(b1*c), c*c1, d1);
        }
        //negation
        splnum operator-() const{
            return splnum(-a,-b,c,d);
        }
        //subtraction
        splnum operator-(const splnum& n){
            return (*this)+(-n); 
        }
        //multiplication
        splnum operator*(const splnum& n){
            int a1=n.a;
            int b1=n.b;
            int c1=n.c;
            int d1=(d ? d : n.d);
            return splnum((a*a1)+(b*b1*d), (a*b1)+(a1*b), c*c1, d1);
        }
        //division
        splnum operator/(const splnum& n){
            //returns 0 on division by 0
            return (*this)*(n.inverse());
        }
        //equality check
        bool operator==(const splnum& n){
            return ((a==n.a) && (b==n.b) && (c==n.c) && (d==n.d));
        }

};

/* --------------- */

void findroots(int r, int s, splnum roots[2]){
    int c=2;
    int d=(r*r)+(4*s);
    if((r%2) == 0){
        r/=2;
        c/=2;
        d/=4;
    }
    roots[0]=splnum(r,1,c,d);
    roots[1]=splnum(r,-1,c,d);
}

void solvehomogeneous(int r, int s, int a0, int a1){
    cout<<"\n+++ Solving the homogeneous recurrence"<<endl;
    cout<<"\tCharacteristic equation: x^2 + ("<<-r<<")x + ("<<-s<<") = 0"<<endl;

    splnum roots[2];
    findroots(r,s,roots);
    cout<<"\tRoot 1 = "; roots[0].print(); cout<<endl;
    cout<<"\tRoot 2 = "; roots[1].print(); cout<<endl;

    //convert a0 and a1 to splnum format
    splnum s0(a0,0,1,0);
    splnum s1(a1,0,1,0);

    cout<<"\tHomogeneous solution :\n";
    splnum u,v;
    if(roots[0]==roots[1]){
        v=s0;
        u=(s1/roots[0])-v;
        cout<<"\t[("; u.print(); cout<<")n + ("; v.print(); cout<<")] ["; roots[1].print(); cout<<"]^n"<<endl;
    }
    else{
        u=((s0*roots[1])-s1)/(roots[1]-roots[0]);
        v=s0-u;
        cout<<"\t["; u.print(); cout<<"] ["; roots[0].print(); cout<<"]^n + ["; v.print(); cout<<"] ["; roots[1].print(); cout<<"]^n"<<endl;
    }
}

void solvenonhomogeneous(int r, int s, int t, int a0, int a1){
    cout<<"\n+++ Solving the nonhomogeneous recurrence"<<endl;
    cout<<"\tCharacteristic equation: x^2 + ("<<-r<<")x + ("<<-s<<") = 0"<<endl;

    splnum roots[2];
    findroots(r,s,roots);
    cout<<"\tRoot 1 = "; roots[0].print(); cout<<endl;
    cout<<"\tRoot 2 = "; roots[1].print(); cout<<endl;

    //convert a0 and a1 to splnum format
    splnum s0(a0,0,1,0);
    splnum s1(a1,0,1,0);
    //storing 1 in splnum format to check for multiplicity of 1 as root
    splnum one(1,0,1,0);

    cout<<"\tParticular solution : ";
    splnum p,u,v;
    if(roots[0]==one || roots[1]==one){
        //1 is root of multiplicity 2
        if(roots[0]==roots[1]){
            p=splnum(t,0,2,0);
            cout<<"["; p.print(); cout<<"] n^2\n";
            cout<<"\tHomogeneous solution :\n";
            v=s0;
            u=((s1-p)/roots[0])-v;
            cout<<"\t[("; u.print(); cout<<")n + ("; v.print(); cout<<")] ["; roots[1].print(); cout<<"]^n"<<endl;
        }
        //1 is root of multiplicity 1
        else{
            p=splnum(t,0,1+s,0);
            cout<<"["; p.print(); cout<<"] n\n";
            cout<<"\tHomogeneous solution :\n";
            u=((s0*roots[1])-(s1-p))/(roots[1]-roots[0]);
            v=s0-u;
            cout<<"\t["; u.print(); cout<<"] ["; roots[0].print(); cout<<"]^n + ["; v.print(); cout<<"] ["; roots[1].print(); cout<<"]^n"<<endl;
        }
    }
    //1 is not a root
    else{
        p=splnum(t,0,1-r-s,0);
        p.print();
        cout<<"\n\tHomogeneous solution :\n";
        if(roots[0]==roots[1]){
            v=s0-p;
            u=((s1-p)/roots[0])-v;
            cout<<"\t[("; u.print(); cout<<")n + ("; v.print(); cout<<")] ["; roots[1].print(); cout<<"]^n"<<endl;
        }
        else{
            u=(((s0-p)*roots[1])-(s1-p))/(roots[1]-roots[0]);
            v=(s0-p)-u;
            cout<<"\t["; u.print(); cout<<"] ["; roots[0].print(); cout<<"]^n + ["; v.print(); cout<<"] ["; roots[1].print(); cout<<"]^n"<<endl;
        }
    }
}

int main(){
    freopen("TestCases.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int r,s,t,a0,a1;
    for(int i=0; i<20; i++){
        cout<<"Test Case "<<i+1<<endl;
        cout<<"r = ";   cin>>r; cout<<r<<endl;
        cout<<"s = ";   cin>>s; cout<<s<<endl;
        cout<<"t = ";   cin>>t; cout<<t<<endl;
        cout<<"a0 = ";  cin>>a0; cout<<a0<<endl;
        cout<<"a1 = ";  cin>>a1; cout<<a1<<endl;
        solvehomogeneous(r,s,a0,a1);
        solvenonhomogeneous(r,s,t,a0,a1);
        cout<<endl;
    }
    return 0;
}