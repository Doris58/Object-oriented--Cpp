#include <iostream>
    #include <ctime>
    #include <chrono>

    #include "operations.h"
    using namespace std;

    int main()
    {
        const size_t max = 3;

        Vector<max>  x, y(2.0), z,w,m;
        x[0]=1.0; x[1]= 1.5; x[2]=1;

        z = x + y;
        for(int i=0;i<3;i++)
        {
            cout<<z[i]<<" ";

        }
        cout<<endl;
        int a=2;

        w=2*z; m=z*2;
        for(int i=0;i<3;i++)
        {
            cout<<w[i]<<endl;
            cout<<m[i]<<endl;

        }
        z=w-m;

        for(int i=0;i<3;i++)
        {
            cout<<z[i]<<" ";

        }
        cout<<endl;
      Vector<5000> vekt(8), vekt2(10),vekt3(45);
        auto start = std::chrono::system_clock::now();
            for(int c=0; c<1000; ++c){
                double coef = 1.0;
                for(unsigned int i=0; i < 5000; ++i) vekt[i] = 2.0*vekt2[i] + coef*(vekt2[i]-vekt3[i]);
                coef += 0.01;
            }
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                                            (std::chrono::system_clock::now() - start);

            cout<< "C time for " << "5000" << " additions = "<<  duration.count() <<" ms.\n";
            cout << vekt[566] << endl; // Da spriječi potpunu eliminaciju koda s opcijom -O2

            start = std::chrono::system_clock::now();
            for(int c=0; c<1000; ++c){
                double coef = 1.0;
                vekt = 2.0*vekt2 + coef*(vekt2-vekt3);
                coef += 0.01;
            }
            end = std::chrono::system_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>
                                            (std::chrono::system_clock::now() - start);

            cout<< "C++ time for " << "5000"<< " additions = "<<  duration.count() <<" ms.\n";
            cout << vekt[566] << endl;// Da spriječi potpunu eliminaciju koda s opcijom -O2

            Vector<4> vektor(2),V;
            Matrix<4,4> M;
            M(0,0)=M(1,1)=M(2,2)=1;
            M(3,3)=3;
            M(1,0)=M(2,1)=M(3,2)=0;
            M(3,0)=2;
            M(0,1)=0;
            M(0,2)=M(0,3)=1;
            M(1,2)=2;
            M(1,3)=0;
            M(2,3)=3;
            M(2,0) = 1;
            M(3,1)=0;
            V=M*vektor;
            cout<<V[0];




        return 0;
    }
