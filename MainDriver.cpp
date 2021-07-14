#include<iostream>
#include"Ass2DynamicMem.cpp"
using namespace std;

int main()
{
	int n; //number of test cases
    int ctr =0;
    cin>>n;
    while(n--)
	{
        int sz;
        cin>>sz;
        Ass2DynamicMem *x = new Ass2DynamicMem(sz, 3);
        int t;
        cin>>t;
        while (t--)
		{
            ctr++;
            string s;
            cin>>s;
            int y;
            cin>>y;
            int ans = -5;
            
            if(s == "Allocate")
                ans = x->Allocate(y);
            else if(s == "Free")
                ans = x->Free(y);
            else if(s == "Defragment")
                x->Defragment();    
            if(ans!= -5)
                cout<<ans<<endl;
        }
    }
}
