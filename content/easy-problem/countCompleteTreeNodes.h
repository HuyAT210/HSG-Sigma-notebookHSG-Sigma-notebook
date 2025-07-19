/**
 * Author: Cellul4r
 * Description: None 
 */
int addDigits(int num) {
    if(num <= 9) {
        return num;
    }
    // 10 19 28
    int n = (num - 10) / 9 + 1;
    int k = 10 + (n - 1) * 9;        
    return 1 + (num - k);
}
