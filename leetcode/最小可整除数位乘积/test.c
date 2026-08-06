int smallestNumber(int n, int t) {
    while (1) {
        int product = 1;
        int tmp = n;

        /* 计算 n 的数位乘积 */
        while (tmp != 0) {
            product *= tmp % 10;
            tmp /= 10;
        }

        if (product % t == 0)
            return n;

        n++;
    }
}