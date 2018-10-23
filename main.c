#include <stdio.h>
#include <stdlib.h>

// ��ʼ�û���IP
static unsigned char IP[8][8] = {
    {58,50,42,34,26,18,10,2},
    {60,52,44,36,28,20,12,4},
    {62,54,46,38,30,22,14,6},
    {64,56,48,40,32,24,16,8},
    {57,49,41,33,25,17,9,1},
    {59,51,43,35,27,19,11,3},
    {61,53,45,37,29,21,13,5},
    {63,55,47,39,31,23,15,7}
};

// ��ʼ�û����û���
static unsigned char revIP[8][8] = {
    {40,8,48,16,56,24,64,32},
    {39,7,47,15,55,23,63,31},
    {38,6,46,14,54,22,62,30},
    {37,5,45,13,53,21,61,29},
    {36,4,44,12,52,20,60,28},
    {35,3,43,11,51,19,59,27},
    {34,2,42,10,50,18,58,26},
    {33,1,41,9,49,17,57,25}
};

// E��չ�����
static unsigned char e_ext_rule[8][6] = {
    {32,1,2,3,4,5},
    {4,5,6,7,8,9},
    {8,9,10,11,12,13},
    {12,13,14,15,16,17},
    {16,17,18,19,20,21},
    {20,21,22,23,24,25},
    {24,25,26,27,28,29},
    {28,29,30,31,32,1}
};

// 8��S��
static unsigned char sbox[8][4][16] = {
    {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    },
    {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    },
    {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
   },
   {
       { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
       {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
       {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
       { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
   },
   {
       { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
       {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
       { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
       {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
   },
   {
       {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
       {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
       { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
       { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
   },
   {
       { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
       {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
       { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
       { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
   },
   {
       {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
       { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
       { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
       { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
   }
};

// P�û���
static unsigned char P_Table[8][4] = {
    {16,7,20,21},
    {29,12,28,17},
    {1,15,23,26},
    {5,18,31,10},
    {2,8,24,14},
    {32,27,3,9},
    {19,13,30,6},
    {22,11,4,25}
};

// ѭ������λ��
static const int timesOfLS[16] = {
   1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

// PC1ѹ���û���
static unsigned char PC_1[8][7] = {
    {57,49,41,33,25,17,9},
    {1,58,50,42,34,26,18},
    {10,2,59,51,43,35,27},
    {19,11,3,60,52,44,36},
    {63,55,47,39,31,23,15},
    {7,62,54,46,38,30,22},
    {14,6,61,53,45,37,29},
    {21,13,5,28,20,12,4}
};

// PC2ѹ���û���
static unsigned char PC_2[8][6] = {
    {14, 17, 11, 24,  1,  5},
    {3, 28, 15,  6, 21, 10},
    {23, 19, 12,  4, 26,  8},
    {16,  7, 27, 20, 13,  2},
    {41, 52, 31, 37, 47, 55},
    {30, 40, 51, 45, 33, 48},
    {44, 49, 39, 56, 34, 53},
    {46, 42, 50, 36, 29, 32}
};

static unsigned char K[16][8][6] = {0};

// ���г�ʼ�û�
void initialProj(unsigned char (*M)[8]){
    unsigned char M0[8][8]={0};
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            int tempI = IP[i][j]/8, tempJ = IP[i][j]%8;
            M0[i][j] = M[tempI][tempJ-1];
        }
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            M[i][j] = M0[i][j];
        }
    }
};

// IP���û�
void reverseIP(unsigned char (*M)[8]) {
    unsigned char M0[8][8]={0};
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            // int tempI = IP[i][j]/8, tempJ = IP[i][j]%8;
            // M0[tempI][tempJ-1] = M[i][j];
            int tempI = revIP[i][j]/8, tempJ = revIP[i][j]%8;
            M0[i][j] = M[tempI][tempJ-1];
        }
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            M[i][j] = M0[i][j];
        }
    }
}

// �����û�
void swapLR(unsigned char (*M)[8]){
    char temp;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 8; ++j){
            temp = M[i][j];
            M[i][j] = M[i+4][j];
            M[i+4][j] = temp;
        }
    }
}

// E��չ
// R0��ʾҪ������չ�Ĵ���extendRes��ʾ��չ���
void EExtend(unsigned char (*R0)[8], unsigned char (*extendRes)[6]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++){
            int tempI = e_ext_rule[i][j]/8, tempJ = e_ext_rule[i][j]%8;
            extendRes[i][j] = R0[tempI][tempJ-1];
        }
    }
}

// ����չ���48λ��������ԿKi�������
void xorWithKi(unsigned char (*extendRes)[6], unsigned char (*Ki)[6]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++){
            if(extendRes[i][j] == Ki[i][j]){
                extendRes[i][j] = 0;
            } else {
                extendRes[i][j] = 1;
            }
        }
    }
}

// s�н���6-4ת����groupΪ8*6�ķ��飬resOfSboxΪ8*4�Ľ��
void sboxTransfor(unsigned char (*group)[6], unsigned char (*resOfSbox)[4]){
    for(int i = 0; i < 8; i++){
        // input: group[i]; output: resOfSbox[i];
        int row = group[i][0] * 2 + group[i][5];
        int col = group[i][1] * 8 + group[i][2] * 4 + group[i][3] * 2 + group[i][4];
        // ��sbox[i][row][col]��ֵת��Ϊ2���Ʊ��浽resOfSbox��
        int res = sbox[i][row][col];
        // ʹ�ó�2ȡ�෨��10����ת��Ϊ2���Ʋ�����
        for(int j = 3; j >= 0; j--){
            resOfSbox[i][j] = res % 2;
            res /= 2;
        }
    }
}

// P�û�����
void PTransform(unsigned char (*resOfSbox)[4], unsigned char (*result)[8]){
    unsigned char temp[8][4]={0};
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 4; ++j){
            int tempI = P_Table[i][j]/4, tempJ = P_Table[i][j]%4;
            temp[i][j] = resOfSbox[tempI][tempJ-1];
        }
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 4; ++j){
            resOfSbox[i][j] = temp[i][j];
        }
    }
    // �����ҽ�8*4���ת��Ϊ4*8�����ں���ļ���
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int row = i * 2;
            result[i][j] = resOfSbox[row][j];
            result[i][j+4] = resOfSbox[row+1][j];
        }
    }
}

// feistel���� ����4*8��32λ��
void feistel(unsigned char (*R0)[8], unsigned char (*Ki)[6], unsigned char (*feisResult)[8]){
    // ��̬���� 4 * 8 �ռ�
//    unsigned char ** result = (unsigned char **)malloc(sizeof(unsigned char *) * 4);
//    for(int i = 0; i < 8; i++){
//        result[i] = (unsigned char *)malloc(sizeof(unsigned char) * 8);
//    }
    // ִ��E��չ
    unsigned char extendRes[8][6] = {0};
    EExtend(R0, extendRes);
    // ���
    xorWithKi(extendRes, Ki);
    // s�н���6-4ת��
    unsigned char resOfSbox[8][4] = {0};
    sboxTransfor(extendRes, resOfSbox);

    // P�û�
    PTransform(resOfSbox, feisResult);
    // return result;
}

// ��L^(i-1) �� feistel(R^(i-1), K[i])�Ľ���������
/**
*@params:
*L0: ��ʾ32λ��L^(i-1)
*feisResult����ʾfeistel(R^(i-1), K[i])�Ľ��
*Rt�������������������ʾR^i
*/
void XOR(unsigned char (*L0)[8], unsigned char (*feisResult)[8], unsigned char (*Rt)[8]){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 8; ++j){
            if(L0[i][j] == feisResult[i][j]) {
                Rt[i][j] = 0;
            } else {
                Rt[i][j] = 1;
            }
        }
    }

    // �ͷŶ�̬����Ŀռ�
//    for(int i = 0; i < 4; i++){
//        free(*(feisResult + i));
//    }
}

// 16��T����
// flag = true��ʾ���ܣ�false ��ʾ����
void iterT(unsigned char (*M)[8], int flag){
    // ��ʼL0 R0
    unsigned char L0[4][8]={0}, R0[4][8]={0};
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 8; ++j){
            L0[i][j] = M[i][j];
            R0[i][j] = M[i+4][j];
        }
    }
    unsigned char Lt[4][8]={0}, Rt[4][8]={0};
    for(int t = 0; t < 16;t++){
        // ����ÿһ��, Lt = R0, Rt = L0 xor feistel(R0, K[i])
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 8; ++j){
                Lt[i][j] = R0[i][j];
            }
        }
        unsigned char feistelRes[4][8]={0};
        if(flag == 1){
            feistel(R0, K[t], feistelRes);
        } else if(flag == 0) {
            feistel(R0, K[15-t], feistelRes);
        }
        XOR(L0, feistelRes, Rt);
        // ����L0, R0 Ϊ���µ�����Ľ��
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 8; ++j){
                L0[i][j] = Lt[i][j];
                R0[i][j] = Rt[i][j];
            }
        }
    }
    // ����M
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 8; ++j){
            M[i][j] = L0[i][j];
            M[i+4][j] = R0[i][j];
        }
    }
}

// ������56λ��C0D0��ǰ28λ����28λ�ֱ�ѭ������1λ
// C0D0: 8*7
void leftShift(unsigned char (*C0D0)[7]){
    unsigned char temp = C0D0[0][0];
    for(int i = 0; i < 27; i++){
        C0D0[i/7][i%7] = C0D0[(i+1)/7][(i+1)%7];
    }
    C0D0[3][6] = temp;
    temp = C0D0[4][0];
    for(int i = 28; i < 55; i++){
        C0D0[i/7][i%7] = C0D0[(i+1)/7][(i+1)%7];
    }
    C0D0[7][6] = temp;
}

// ����16������Կ
void genKey(unsigned char (*Key)[8]){
    // PC_1�û��õ�C0D0
    unsigned char C0D0[8][7] = {0};
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 7; j++){
            int tempI = PC_1[i][j] / 8, tempJ = PC_1[i][j] % 8;
            C0D0[i][j] = Key[tempI][tempJ-1];
        }
    }
    for(int i = 0; i < 16; i++){
        // ѭ������
        for(int j = 0; j < timesOfLS[i]; j++){
            leftShift(C0D0);
        }

        // PC_2�û�,�õ�K[i]
        for(int m = 0; m < 8; m++){
            for(int n = 0; n < 6; n++){
                int tempI = PC_2[m][n] / 7, tempJ = PC_2[m][n] % 7;
                K[i][m][n] = C0D0[tempI][tempJ-1];
            }
        }
    }
}

void encryption(unsigned char (*M)[8]) {
    initialProj(M);
    // 16�ֵ���T
    iterT(M, 1);
    swapLR(M);
    reverseIP(M);
}

void decryption(unsigned char (*M)[8]) {
    initialProj(M);
    // 16�ֵ���T
    iterT(M, 0);
    swapLR(M);
    reverseIP(M);
}

int main()
{
    // ��ʼ64λ����
    unsigned char M[8][8]={
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };

    // 64λ��ԿKey
    unsigned char Key[8][8]={
        {1,0,0,1,1,1,0,1},
        {1,0,1,0,0,0,0,0},
        {1,0,0,1,1,1,1,0},
        {1,0,1,1,0,1,0,0},
        {1,1,1,0,0,1,0,1},
        {1,1,0,0,0,0,1,1},
        {1,0,1,1,0,1,0,1},
        {1,1,0,1,0,1,0,0}
    };

    genKey(Key);

    printf("��ʼ����\n");
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    encryption(M);

    printf("���ܺ������\n");
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    decryption(M);

    printf("���ܺ������\n");
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}
