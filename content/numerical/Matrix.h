/**
 * Author: HuyAT
 * Description: Matrix multiplication and exponentiation, remember to set M before using
 * Status: Tested by CSES
 */


struct Matrix{
    std::vector<std::vector<long long>> mat;
    Matrix(int n,int m) : mat(n,std::vector<long long>(m,0)){
 
    }
    unsigned int size() const{
        return mat.size();
    }
    const std::vector<long long>& operator [](int i) const{
        return mat[i];
    }
    std::vector<long long>& operator [](int i){
        return mat[i];
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b){
//        std::cerr << a.size() << " " << a[0].size() << " " << b.size() << " " << b[0].size() << newl;
        assert(a.size() && b.size());
        assert(a[0].size() == b.size());
        Matrix res(a.size(),b[0].size());
        for(int i = 0;i < (int)a.size();++i){
            for(int j = 0;j < (int)b[0].size();++j){
                for(int k = 0;k < (int)a[0].size();++k){
                    res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % M;
                }
            }
        }
        return res;
    }
    friend void operator *= (Matrix &a,const Matrix &b){
        a = a * b;
    }
    static Matrix identity(int n){
        Matrix res(n,n);
        for(int i = 0;i < n;++i){
            res[i][i] = 1;
        }
        return res;
    }
    friend Matrix operator ^ (const Matrix &a,long long n){
        assert(a.size());
        assert(a.size() == a[0].size());
        Matrix res = Matrix::identity(a.size()),t = a;
        for(int i = 0;i <= B;++i,t *= t){
            if((n >> i) & 1){
                res *= t;
            }
        }
        return res;
    }
};