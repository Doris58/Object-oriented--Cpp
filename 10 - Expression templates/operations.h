    #include <cstddef>
    #include <cassert>
    #include <array>

    // Dio implementacije operacija -- nadopuniti

    // Deklaracija
     class Scalar;

    // Klasa obilježja koja nam omogućava da vektor tretiramo kroz
    // reference, a skalare po vrijednosti.
    template <typename T>
    struct Traits{
     typedef T const& ExprRef;
    };
    // Specijalizacija na skalare
    // Na skalare ne uzimamo referencu jer im vijek trajanja može biti kraći od
    // vijeka trajanja izraza koji se izračunava.
    template <>
    struct Traits<Scalar>{
     typedef Scalar ExprRef;
    };



    // Klasa koja reprezentira zbrajanje.
    template <typename OP1, typename OP2>
    class Add{
     private:
     typename Traits<OP1>::ExprRef op1;
     typename Traits<OP2>::ExprRef op2;
     public:
     Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}

     double operator[](int i) const { return op1[i]+op2[i]; };
    };
    //klasa koja reprezentira množenje
    template<typename OP1, typename OP2>
    class Mult{
     private:
     typename Traits<OP1>::ExprRef op1;
     typename Traits<OP2>::ExprRef op2;
     public:
     Mult(OP1 const&a,OP2 const &b):op1(a),op2(b) {}

     double operator[](int i) const {return op1[i]*op2[i];};
    };


    template<typename OP1,typename OP2>
    class Sub{
     private:
     typename Traits<OP1>::ExprRef op1;
     typename Traits<OP2>::ExprRef op2;
     public:
     Sub(OP1 const&a,OP2 const &b):op1(a),op2(b) {}

     double operator[](int i) const {return op1[i]-op2[i];};
    };




    // Operator indeksiranja vraća vrijednost skalara.
    class Scalar{
     private:
     double val;
     public:
     Scalar(double const& v) : val(v) {}
     double operator[](size_t) const { return val; }
    };

    template <size_t N, typename Rep = std::array<double,N> >
    class Vector{
     private:
     Rep expr_rep; // vektor ili reprezentacija operacije nad vektorima
     public:
     // Polje iz skalarne vrijednosti
     explicit Vector(double val = 0.0) {expr_rep.fill(val);}
     // Polje iz reprezentacije
     Vector(Rep const& r) : expr_rep(r) {}
     // pridruživanje polja različitog tipa
     template <typename Rep2>
     Vector& operator=(Vector<N,Rep2> const& rhs){
     for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
     return *this;
     }
     size_t size() const { return N; }

     double operator[](size_t i) const { return expr_rep[i]; }
     double& operator[](size_t i) { return expr_rep[i]; }

     Rep const& rep() const { return expr_rep; }
     Rep& rep() { return expr_rep; }
    };
    template <typename T, size_t N, size_t M>
    class Array2D{
     private:
     T m_data[N][M];
     public:
     Array2D(T const& t=0)
     {
     for(size_t i=0;i<rows();++i)
     for(size_t j=0;j<cols();++j)
     m_data[i][j]=t;
     }
     const T& operator()(size_t i, size_t j) const {return m_data[i][j];}
     T& operator()(size_t i, size_t j) {return m_data[i][j];}

     // Izbrisana kontrola kopiranja
     Array2D(Array2D const &) = delete;
     Array2D(Array2D &&) = delete;
     Array2D & operator=(Array2D const &) = delete;
     Array2D & operator=(Array2D &&) = delete;

     size_t rows() const { return N; }
     size_t cols() const { return M; }
    };

    template <size_t N, size_t M, typename Rep = Array2D<double,N,M> >
     class Matrix{
     private:
     Rep expr_rep; // implementacija matrice
     public:
     // Matrica iz reprezentacije
     Matrix() {}
     Matrix(Rep const& r) : expr_rep(r) {}

     Matrix & operator=(double val){ expr_rep=val; return *this; }
     double operator()(size_t i, size_t j)const { return expr_rep(i,j); }
     double& operator()(size_t i, size_t j){ return expr_rep(i,j); }

     size_t rows() const {return expr_rep.rows(); }
     size_t cols() const {return expr_rep.cols(); }

     Rep const& rep() const { return expr_rep; }
     Rep& rep() { return expr_rep; }
     };

     template <size_t N, typename OP2>
     class Mult<Array2D<double, N,N>, OP2 >
     {
     private:
     typedef Array2D<double, N,N> OP1;
     OP1 const & op1;

     typename Traits<OP2>::ExprRef op2;
     public:
     Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
     double operator[](int i) const {
     double tmp = 0.0;
     for(size_t j=0; j<N; ++j) tmp += op1(i,j)*op2[j];
     return tmp;}
     };

    //operator matrica*vektor
     template <size_t N, size_t M , typename R2>
     Vector<N, Mult<Array2D<double, N,N>,R2> > operator*(Matrix<N,M,Array2D<double,N,M> > const& a, Vector<M,R2> const& b){
     return Vector<N, Mult<Array2D<double,N,N>,R2> >( Mult<Array2D<double,N,N>,R2>( a.rep(),b.rep() ) );
     }

    // Operator zbrajanje vektora
    template <size_t N, typename R1, typename R2>
    Vector<N, Add<R1,R2> >
    operator+(Vector<N,R1> const& a, Vector<N,R2> const& b){
     return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
    }

    // Operator množenje skalar * vektor
    template <size_t N, typename R2>
    Vector<N, Mult<Scalar,R2> >
    operator*(double const& a, Vector<N,R2> const& b)
    {
     return Vector<N,Mult<Scalar,R2> >( Mult<Scalar,R2>( Scalar(a), b.rep() ) );
    }

    //Operator množenje vektor*skalar
    template <size_t N, typename R1 >
    Vector<N, Mult<R1,Scalar > >
    operator*(Vector<N,R1> const& a, double const& b)
    {
     return Vector<N,Mult<R1,Scalar> >( Mult<R1,Scalar >( a.rep(), Scalar(b) ) );
    }

    // Operator oduzimanje vektora
    template <size_t N, typename R1, typename R2>
    Vector<N, Sub<R1,R2> >
    operator-(Vector<N,R1> const& a, Vector<N,R2> const& b){
     return Vector<N, Sub<R1,R2> >(Sub<R1,R2>( a.rep(),b.rep() ) );
    }




    // Zbrajanje vektor + skalar
    template <size_t N, typename R1>
    Vector<N, Add<R1,Scalar > >
    operator+(Vector<N,R1> const& a, double const& b){
     return Vector<N, Add<R1, Scalar > >( Add<R1,Scalar>( a.rep(), Scalar(b) ) );
    }

    // Zbrajanje skalar +vektor
    template <size_t N, typename R2>
    Vector<N, Add<Scalar,R2> >
    operator+(double const& a, Vector<N,R2> const& b){
     return Vector<N, Add<Scalar,R2> >( Add<Scalar,R2>( Scalar(a), b.rep() ) );
    }

    template <size_t N, size_t M>
    void makeTridiagonalMatrix(Matrix<N,M,Array2D<double,N,M> >& A, double const& a, double const& b)
    {
     for(size_t i=0;i<A.rows();++i)
     for(size_t j=0;j<A.cols();++j)
     {
     if(j==i) A(i,j)=a;
     else if(j==i+1 || j==i-1) A(i,j)=b;
     else A(i,j)=0;
     }
    }
