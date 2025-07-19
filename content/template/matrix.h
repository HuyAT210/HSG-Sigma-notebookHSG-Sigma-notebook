/**
 * Author: Cellul4r
 * Description: None
 */
struct Matrix {
    vector<vector<long long>> a;
    int rows, cols;
 
    Matrix(int r, int c, int val) : rows(r), cols(c), a(r, vector<long long>(c, val)) {}
 
    // Matrix multiplication operator
    Matrix operator *(const Matrix& other) {
        // The resulting matrix will have dimensions (rows x other.cols)
        Matrix product(rows, other.cols, 0);
 
        // Matrix multiplication: A (rows x cols) * B (other.rows x other.cols)
        // Ensure cols == other.rows for valid multiplication
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    product.a[i][j] += a[i][k] * other.a[k][j] % INF;
                    product.a[i][j] %= INF;
                }
            }
        }
        return product;
    }
};
 
Matrix expo_power(Matrix a, long long n, int size){
    Matrix product(size,size,0);
    for(int i=0;i<size;++i)product.a[i][i]=1;
    while(n>0){
        if(n&1){
            product = product * a;
        }
        a = a * a;
        n>>=1;
    }
    return product;
}
