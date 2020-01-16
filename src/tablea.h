#ifndef TABLEA_H
#define TABLEA_H

#include <QAbstractTableModel>
#include <iostream>
#include "playerdata.h"

class TableA : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableA(PlayerData* data_pr, QObject *parent = 0):playerdata_pr(data_pr),
        clear_enum_count(data_pr->clear_enum_count),
        rank_enum_count(data_pr->rank_enum_count),
        level_enum_count(data_pr->level_enum_count){}
    //TableA(QObject *parent = 0){}
    int rowCount(const QModelIndex &parent = QModelIndex()) const{return level_enum_count;}
    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        if (display_type == 0) return clear_enum_count;
        else return rank_enum_count;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        int r = index.row();
        int c = index.column();
        if(role == Qt::DisplayRole)
        {
            if (display_type == 0) return playerdata_pr->clear_count[r*clear_enum_count+c];
            else return playerdata_pr->rank_count[r*rank_enum_count+c];
        }
        if(role == Qt::TextAlignmentRole) return Qt::AlignCenter;
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal)
            {

                if(display_type == 1)
                {
                    switch (section)
                    {
                    case 0: return QString("F");
                    case 1: return QString("E");
                    case 2: return QString("D");
                    case 3: return QString("C");
                    case 4: return QString("B");
                    case 5: return QString("A");
                    case 6: return QString("AA");
                    case 7: return QString("AAA");
                    case 8: return QString("All");
                    }
                }
                else
                {
                    switch (section)
                    { // 0 NO PLAY 1 FAILED 2 ASSIST CLEAR 3 EASY CLEAR 4 CLEAR 5 HARD CLEAR 6 EX-HARD CLEAR 7 FULL COMBO
                    case 0: return QString("NP");
                    case 1: return QString("F");
                    case 2: return QString("AC");
                    case 3: return QString("EC");
                    case 4: return QString("C");
                    case 5: return QString("HC");
                    case 6: return QString("EH");
                    case 7: return QString("FC");
                    case 8: return QString("All");
                    }
                }
            }
            else
            if (orientation == Qt::Vertical)
            {
                if (section <= 11) return section+1;
                else return QString("All");
            }
        }
        return QVariant();
    }

    void setDisplayType(short s){display_type = s;}

public:
     short clear_enum_count;
     short rank_enum_count;
     short level_enum_count;
     short display_type; // 0 = clear, 1 = rank

private:
    PlayerData* playerdata_pr;


};

#endif // TABLEA_H

