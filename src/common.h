#ifndef COMMON_H
#define COMMON_H
#include <QString>

class Label
{
public:

    static QString verLabel(short ver)
    {
        switch(ver)
        {
        case 10: return QString("1st");
        case 15: return QString("sub");
        case 20: return QString("2nd");
        case 30: return QString("3rd");
        case 40: return QString("4th");
        case 50: return QString("5th");
        case 60: return QString("6th");
        case 70: return QString("7th");
        case 80: return QString("8th");
        case 90: return QString("9th");
        case 100: return QString("10th");
        case 110: return QString("RED");
        case 120: return QString("SKY");
        case 130: return QString("DD");
        case 140: return QString("GOLD");
        case 150: return QString("DJT");
        case 160: return QString("EMP");
        case 170: return QString("SIR");
        case 180: return QString("RA");
        case 190: return QString("LC");
        case 200: return QString("tri");
        case 210: return QString("SPA");
        case 220: return QString("PEN");
        case 230: return QString("cop");
        }
    }

    static QString diffLabel(short diff)
    {
        switch(diff)
        {
        case 0: return QString("N");
        case 1: return QString("H");
        case 2: return QString("A");
        }
    }

    static QString clearLabel(short clear)
    {
        switch(clear)
        {
        case 0: return QString("NO PLAY");
        case 1: return QString("FAILED");
        case 2: return QString("ASSIST CLEAR");
        case 3: return QString("EASY CLEAR");
        case 4: return QString("CLEAR");
        case 5: return QString("HARD CLEAR");
        case 6: return QString("EX-HARD CLEAR");
        case 7: return QString("FULL COMBO");
        }
    }
};

#endif // COMMON_H

