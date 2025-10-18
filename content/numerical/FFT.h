/**
 * Author: Zero_OP
 * Description: just FFT
 * Status: I don't know
 */

using cd=complex<double>;
const double PI=acos(-1);

void fft(vector<cd>& a, bool is_inverse){
    int n=a.size();
    int lg=0; while((1<<lg)<n) ++lg;

    for(int i=1, j=0; i<n; ++i){
        int bit=n>>1;
        for(; j&bit; bit>>=1) j^=bit;
        j^=bit;
        if(i<j) swap(a[i], a[j]);
    }

    for(int len=2; len<=n; len<<=1){
        double ang=2.0*PI/len*(is_inverse?-1:1);
        cd wlen(cos(ang), sin(ang));
        for(int i=0; i<n; i+=len){
            cd w(1);
            for(int j=0; j*2<len; ++j){
                cd u=a[i+j], v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(is_inverse){
        for(cd &x:a) x/=n;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<cd> fa(all(a)), fb(all(b));
    int n=1; while(a.size()+b.size()>n) n<<=1;

    fa.resize(n), fb.resize(n);
    fft(fa, 0), fft(fb, 0);
    for(int i=0; i<n; ++i) fa[i]*=fb[i];
    fft(fa, 1);

    vector<int> result(n);
    for(int i=0; i<n; ++i) result[i]=round(fa[i].real());
    return result;
}
