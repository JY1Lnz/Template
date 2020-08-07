LL K[110][110];
LL det(int n){//求矩阵K的n-1阶顺序主子式
    LL res=1;
    for(int i=1;i<=n-1;i++){//枚举主对角线上第i个元素
        for(int j=i+1;j<=n-1;j++){//枚举剩下的行
            while(K[j][i]){//辗转相除
                int t=K[i][i]/K[j][i];
                for(int k=i;k<=n-1;k++)//转为倒三角
                    K[i][k]=(K[i][k]-t*K[j][k]+MOD)%MOD;
                swap(K[i],K[j]);//交换i、j两行
                res=-res;//取负
            }
        }
        res=(res*K[i][i])%MOD;
    }
    return (res+MOD)%MOD;
}

int main()
{
    int x, y;
    // 边x到y
    K[x][y]--;
    K[y][x]--;
    K[x][x]++; // 度数
    K[y][y]++;
    det(n); // 生成树个数
}