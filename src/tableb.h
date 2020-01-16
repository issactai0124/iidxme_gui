#ifndef TABLEB_H
#define TABLEB_H

#include <QAbstractTableModel>
#include <iostream>
#include "playercompare.h"

class TableB : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableB(PlayerCompare* data_pr, QObject *parent = 0):playercompare_pr(data_pr),
        level_enum_count(data_pr->level_enum_count){}
    //TableA(QObject *parent = 0){}
    int rowCount(const QModelIndex &parent = QModelIndex()) const{return level_enum_count;}
    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 5;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        int r = index.row();
        int c = index.column();
        if(role == Qt::DisplayRole)
        {
            switch (display_type)
            {
            case 0: return playercompare_pr->score_count[r*5+c];
            case 1: return playercompare_pr->bp_count[r*5+c];
            case 2: return playercompare_pr->clear_count[r*5+c];
            case 3: return playercompare_pr->full_count[r*5+c];
            }
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
                switch (section)
                {
                case 0: return QString("Win");
                case 1: return QString("Lose");
                case 2: return QString("Draw");
                case 3: return QString("N/A");
                case 4: return QString("All");
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
     short level_enum_count;
     short display_type; // 0 = score 1 = misscount 2 = clearlamp 3 fullcombo

private:
    PlayerCompare* playercompare_pr;


};
#endif // TABLEB_H

