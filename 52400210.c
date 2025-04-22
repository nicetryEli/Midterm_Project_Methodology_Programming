#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.1415926535

int laDongC(int dc) {
    if (dc < 8) return 1;
    else return 2;
}

int laDongG(int dg) {
    if (dg < 5) return 1;
    else return 2;
}

double nepBanhChung(double dc){
    return pow(dc,2)*sqrt(dc);
}

double nepBanhGiay(double dg){
    return pow(dg,2)*PI/3;
}

double findX(int dc, int ld){
    int temx;
    int xArr[5][6] = {
        {5,7,10,12,15,20},
        {20,5,7,10,12,15},
        {15,20,5,7,10,12},
        {12,15,20,5,7,10},
        {10,12,15,20,5,7}
    };
    int G = dc % 6;
    int H = ld % 5;
    temx = xArr[G][H];
    double x = (double)temx;
    return x;
}

int isFibonacci(int a, int b) {
    int fib[100];
    fib[0] = 0;
    fib[1] = 1;
    int count = 2;

    while (1) {
        int next = fib[count - 1] + fib[count - 2];
        if (next > 200) break;
        fib[count++] = next;
    }

    int foundA = 0, foundB = 0;
    for (int i = 0; i < count; i++) {
        if (fib[i] == a) foundA = 1;
        if (fib[i] == b) foundB = 1;
    }

    return foundA && foundB;
}
int isFriendNumber(int a, int b) {
    int friendPair[2][2] = {
        {220, 284},
        {1184, 1210}
    };
    
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    for (int i = 0; i < 2; i++) {
        if (a == friendPair[i][0] && b == friendPair[i][1]) {
            return 1;
        }
    }
    return 0;
}

typedef enum{
    FOG,
    SUN,
    WIND,
    RAIN,
    CLOUD
} WeatherType;

typedef struct {
    int bc;
    int bg;
    double nd;
} WeatherResult;
//PROTOTYPE
WeatherResult sun(double n, double dc, double dg, int ld);
WeatherResult wind(double n, double dc, double dg, int ld);
WeatherResult cloud(double n, double dc, double dg, int ld);
WeatherResult rain(double n, double dc, double dg, int ld);
WeatherResult fog(double n, double dc, double dg, int ld);

WeatherResult getWeatherResult(WeatherType type, double n, double dc, double dg, int ld){
    switch (type){
        case FOG:
            return fog(n,dc,dg,ld);
        case SUN:
            return sun(n,dc,dg,ld);
        case WIND:
            return wind(n,dc,dg,ld);
        case RAIN:
            return rain(n,dc,dg,ld);
        case CLOUD:
            return cloud(n,dc,dg,ld);
        default:{
            WeatherResult res = {-1, -1, (int)n};
            return res;
        }
    }
}

WeatherResult wind(double n, double dc, double dg, int ld) {
    WeatherResult result;
    double tem = n;
    int bc = 0, bg = 0;
    
    while (tem >= nepBanhChung(dc) && ld >= laDongC((int)dc)) {
        tem -= nepBanhChung(dc);
        ld -= laDongC((int)dc);
        bc++;
    }
    
    while (tem >= nepBanhGiay(dg) && ld >= laDongG((int)dg)) {
        tem -= nepBanhGiay(dg);
        ld -= laDongG((int)dg);
        bg++;
    }
    
    double nd = tem;
    
    result.bc = bc;
    result.bg = bg;
    result.nd = nd;

    return result;
}

WeatherResult rain(double n, double dc, double dg, int ld) {
    WeatherResult result;
    double nd = 0, tem = n, bctem = 0, bgtem = 0; 
    int bc = 0, bg = 0,laBanhChung, laBanhGiay;
    while (tem >= nepBanhChung(dc) || tem >= nepBanhGiay(dg)) {
        if (tem>=nepBanhChung(dc)){
            tem -= nepBanhChung(dc);
            bctem++;
        } 
        if (tem>=nepBanhGiay(dg)){ 
            tem -= nepBanhGiay(dg);
            bgtem++;
        }
        if (abs(bctem - bgtem) >= 1) break;
    }
    bc = (int)bctem;
    bg = (int)bgtem;

    laBanhChung = bc * laDongC((int)dc);
    laBanhGiay = bg * laDongG((int)dg);
    while (laBanhChung + laBanhGiay > (double)ld){
        if (nepBanhChung(dc) > nepBanhGiay(dg)){
            bg--;
            laBanhGiay = bg * laDongG((int)dg);
        } else {
            bc--;
            laBanhChung = bc * laDongC((int)dc);
        }
    }
    nd = n - (double)bc * nepBanhChung(dc) - (double)bg * nepBanhGiay(dg);

    if (bc == 0 && bg == 0){
        bc = -1;
        bg = -1;
        nd = n;
    } 
    result.bc = bc;
    result.bg = bg;
    result.nd = nd;

    return result;
}

WeatherResult cloud(double n, double dc, double dg, int ld) {
    WeatherResult result;
    double tem = n, bctem = 0, bgtem = 0;

    if (isFriendNumber(ld, (int)n)) {
        result.bc = 0;
        result.bg = 0;
        result.nd = n;
        return result;
    }

    while (tem >= nepBanhGiay(dg) && ld >= laDongG((int)dg)) {
        tem -= nepBanhGiay(dg);
        ld -= laDongG((int)dg);
        bgtem++;
    }

    while (tem >= nepBanhChung(dc) && ld >= laDongC((int)dc)) {
        tem -= nepBanhChung(dc);
        ld -= laDongC((int)dc);
        bctem++;
    }

    result.bc = (int)bctem;
    result.bg = (int)bgtem;
    result.nd = tem;
    return result;
}

WeatherResult sun(double n, double dc, double dg, int ld) {
    WeatherResult result;
    int x = findX(dc, ld);
    n = n * (100 + (double)x) / 100;
    ld = ld - x;

    int weather = (int)(dc + dg) % 3;
    switch (weather) {
        case 0: result = rain(n,dc,dg,ld); break;
        case 1: result = wind(n,dc,dg,ld); break;
        case 2: result = cloud(n,dc,dg,ld); break;
    }
    return result;
}
    
WeatherResult fog(double n, double dc, double dg, int ld){
    WeatherResult result;
    double tem = n;
    int bc = 0, bg = 0;

    if (isFibonacci((int)dc, (int)dg)) {
        dc = dc / 2.0;
        dg = dg / 2.0;
    } else {
        dc = dc * 2.0;
        dg = dg * 2.0;
    }

    double nepC = nepBanhChung(dc);
    double nepG = nepBanhGiay(dg);
    double laC = laDongC((int)dc); 
    double laG = laDongG((int)dg); 

    if (nepC >= nepG) {
        while (tem >= nepC && ld >= laC) {
            tem -= nepC;
            ld -= laC;
            bc++;
        }
        while (tem >= nepG && ld >= laG) {
            tem -= nepG;
            ld -= laG;
            bg++;
        }
    } else {
        while (tem >= nepG && ld >= laG) {
            tem -= nepG;
            ld -= laG;
            bg++;
        }
        while (tem >= nepC && ld >= laC) {
            tem -= nepC;
            ld -= laC;
            bc++;
        }
    }

    result.bc = bc;
    result.bg = bg;
    result.nd = tem;
    return result;
}

int main() {
    FILE *inputfile, *outputfile;
    int n, dc, dg, ld;
    double nAlter, dcAlter, dgAlter;
    char w[6];
    inputfile = fopen("input.inp", "r");

    fscanf(inputfile, "%d %d %d %d %s", &n, &dc, &dg, &ld, &w);
    fclose(inputfile);

    w[strcspn(w, "\r\n")] = 0;  
    
    nAlter = (double)n;
    dcAlter = (double)dc;
    dgAlter = (double)dg;

    if (n > 2000 || n < 0 || ld > 600 || ld < 0) {
        outputfile = fopen("output.out", "w");
        fprintf(outputfile, "-1 -1 %d", n);
        fclose(outputfile);
    } else {
        int code = -1;
        if (strcmp(w, "Fog") == 0) code = FOG;
        else if (strcmp(w, "Sun") == 0) code = SUN;
        else if (strcmp(w, "Wind") == 0) code = WIND;
        else if (strcmp(w, "Rain") == 0) code = RAIN;
        else if (strcmp(w, "Cloud") == 0) code = CLOUD;

        outputfile = fopen("output.out", "w");
        switch (code) {
            case WIND: {
            WeatherResult res = getWeatherResult(WIND, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case RAIN: {
            WeatherResult res = getWeatherResult(RAIN, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case CLOUD: {
            WeatherResult res = getWeatherResult(CLOUD, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case FOG: {
            WeatherResult res = getWeatherResult(FOG, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case SUN: {
            WeatherResult res = getWeatherResult(SUN, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            default: {
            fprintf(outputfile, "-1 -1 %d", n);
            break;
            }
        }
        fclose(outputfile);
        }
    }
