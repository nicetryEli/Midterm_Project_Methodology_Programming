#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI 3.1415926535

int laDongC(int dc){
    if (dc < 8){
        return 1;
    } else if (dc >= 8){
        return 2;
    }
}

int laDongG(int dg){
    if (dg < 5){
        return 1;
    } else if (dg >= 5){
        return 2;
    }
}

float nepBanhChung(float dc){
    return pow(dc,2)*sqrt(dc);
}

float nepBanhGiay(float dg){
    return pow(dg,2)*PI*1/3;
}

float findX(int dc, int ld){
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
    float x = (float)temx;
    return x;
}

int isFibonacci(int a, int b){
    int tem = 0, f1 = 0, f2 = 1;
    if (a>b){
        tem = a;
        a = b;
        b = tem;
    }
    while (f2 == b){
        if (f1 == a && f2 == b){
            return 0;
        }
        tem = f1 + f2;
        f1 = f2;
        f2 = tem;
    }
    return 1;
}

int isFriendNumber(int a, int b){
    int friendPair[2][2] = {
        {220, 284},
        {1184, 1210}
    };
    for (int i = 0; i < 2; i++){
        if (a == friendPair[i][0] && b == friendPair[i][1]){
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
    float nd;
} WeatherResult;
//PROTOTYPE
WeatherResult sun(float n, float dc, float dg, int ld);
WeatherResult wind(float n, float dc, float dg, int ld);
WeatherResult cloud(float n, float dc, float dg, int ld);
WeatherResult rain(float n, float dc, float dg, int ld);
WeatherResult fog(float n, float dc, float dg, int ld);

WeatherResult getWeatherResult(WeatherType type, float n, float dc, float dg, int ld){
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

WeatherResult wind(float n, float dc, float dg, int ld) {
    WeatherResult result;
    float tem = n;
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
    
    float nd = tem;
    
    result.bc = bc;
    result.bg = bg;
    result.nd = nd;

    return result;
}

WeatherResult rain(float n, float dc, float dg, int ld) {
    WeatherResult result;
    float banhChungNep, banhGiayNep, nd = 0, tem = n, bctem = 0, bgtem = 0; 
    int bc = 0, bg = 0,laBanhChung, laBanhGiay;
    while (tem >= nepBanhChung(dc) || tem >= nepBanhGiay(dg)) {
        if (tem>=nepBanhChung(dc)){
            tem -= nepBanhChung(dc);
            bctem++;
        } 
        if (tem>=nepBanhGiay(dc)){
            tem -= nepBanhGiay(dg);
            bgtem++;
        }
        if (abs(bctem - bgtem) >= 1) break;
    }
        bc = (int)bctem;
        bg = (int)bgtem;

        laBanhChung = bc* laDongC((int)dc);
        laBanhGiay = bg* laDongG((int)dg);
    while (laBanhChung + laBanhGiay > (float)ld){
        if (nepBanhChung(dc) > nepBanhGiay(dg)){
            bg--;
            laBanhGiay = bg * laDongG((int)dg);
        } else {
            bc--;
            laBanhChung = bc * laDongC((int)dc);
        }
    }
    nd = n - (float)bc * nepBanhChung(dc) - (float)bg * nepBanhGiay(dg);

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

WeatherResult cloud(float n, float dc, float dg, int ld) {
    WeatherResult result;
    float banhChungNep, banhGiayNep, nd = 0, bctem = 0, bgtem = 0, tem = n;  
    int bc = 0, bg = 0, laBanhChung, laBanhGiay;
    if (isFriendNumber(n,ld)){
        bc = 0;
        bg = 0;
        nd = n;
    } else {
        banhGiayNep = nepBanhGiay(dg);
        banhChungNep = nepBanhChung(dc);
        laBanhChung = laDongC(dc);
        laBanhGiay = laDongG((int)dg);
        while (tem > banhGiayNep && ld > laBanhGiay){
            tem = tem - nepBanhGiay(dg); 
            ld = ld - laDongG((int)dg);               
            bgtem = bgtem + 1;
        }
        while (tem > banhChungNep && ld > laBanhChung){
            tem = tem - nepBanhChung(dc);                
            bctem = bctem + 1;
        }
        bc = (int)bctem;
        bg = (int)bgtem;
        nd = n - (float)bc * nepBanhChung(dc) - (float)bg * nepBanhGiay(dg);
        result.bc = bc;
        result.bg = bg;
        result.nd = nd;

        return result;
    }
    }

WeatherResult sun(float n, float dc, float dg, int ld) {
    WeatherResult result;
    int x = findX(dc, ld);
    n = n * (100 + x) / 100;
    ld = ld - x;

    int weather = (dc + dg) / 3;
    switch (weather) {
        case 0: result = rain(n,dc,dg,ld); break;
        case 1: result = wind(n,dc,dg,ld); break;
        case 2: result = cloud(n,dc,dg,ld); break;
    }
    return result;
        return result;
}
    
WeatherResult fog(float n, float dc, float dg, int ld){
    WeatherResult result;
    float nd = 0, bctem = 0, bgtem = 0, tem = n;
    int bc = 0, bg = 0;
    if (isFibonacci(dc,dg)){
        dc = dc /2;
        dg = dg /2;
    } else {
        dc = dc * 2;
        dg = dg * 2;
    }
    if (nepBanhChung(dc) > nepBanhGiay(dg)){
        return wind(n, dc, dg, ld);
    } else {
        while (tem >= nepBanhGiay(dc) && ld >= laDongG((int)dc)) {
            tem -= nepBanhGiay(dc);
            ld -= laDongG((int)dc);
            bg++;
        }
        
        while (tem >= nepBanhChung(dg) && ld >= laDongC((int)dg)) {
            tem -= nepBanhChung(dg);
            ld -= laDongC((int)dg);
            bc++;
        }
        
        float nd = tem;
            result.bc = bc;
        result.bg = bg;
        result.nd = nd;
        return result;
    }
}

int main() {
    FILE *inputfile, *outputfile;
    int n, dc, dg, ld;
    float nAlter, dcAlter, dgAlter;
    char w[5];
    inputfile = fopen("input.inp", "r");

    fscanf(inputfile, "%d %d %d %d %s", &n, &dc, &dg, &ld, &w);
    fclose(inputfile);
    
    nAlter = (float)n;
    dcAlter = (float)dc;
    dgAlter = (float)dg;

    if (n > 2000 || n < 0 || ld > 600 || ld < 0) {
        outputfile = fopen("output.out", "w");
        fprintf(outputfile, "-1 -1 %d", n);
        fclose(outputfile);
    } else {
        int code = -1;
        if (strcmp(w, "Wind") == 0) code = 0;
        else if (strcmp(w, "Rain") == 0) code = 1;
        else if (strcmp(w, "Cloud") == 0) code = 2;
        else if (strcmp(w, "Fog") == 0) code = 3;
        else if (strcmp(w, "Sun") == 0) code = 4;
        
        outputfile = fopen("output.out", "w");
        switch (code) {
            case 0: {
            WeatherResult res = getWeatherResult(WIND, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case 1: {
            WeatherResult res = getWeatherResult(RAIN, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case 2: {
            WeatherResult res = getWeatherResult(CLOUD, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case 3: {
            WeatherResult res = getWeatherResult(FOG, nAlter, dcAlter, dgAlter, ld);
            fprintf(outputfile, "%d %d %.3f", res.bc, res.bg, res.nd);
            break;
            }
            case 4: {
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
