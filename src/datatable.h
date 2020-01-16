#ifndef DATATABLE_H
#define DATATABLE_H

#include <QAbstractTableModel>
#include "common.h"
#include "playerdata.h"
#include "playercompare.h"

class DataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataTable(PlayerData* data_pr, QObject *parent = 0):data_type(0),playerdata_pr(data_pr){}
    DataTable(PlayerCompare* data_pr, QObject *parent = 0):data_type(1),playercompare_pr(data_pr){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        if(data_type == 0) return playerdata_pr->db.size();
        else if(data_type == 1) return playercompare_pr->db.size();
        else return 0;
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        if(data_type == 0) return 13;
        else if(data_type == 1) return 25;
        else return 10;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        int r = index.row();
        int c = index.column();
        if(role == Qt::DisplayRole)
        {
            if(data_type == 0)
            {
                switch(c)
                {
                case 0: return playerdata_pr->db[r].ver;
                case 1: return Label::verLabel(playerdata_pr->db[r].ver);
                case 2: return playerdata_pr->db[r].title;
                case 3: return playerdata_pr->db[r].diff;
                case 4: return Label::diffLabel(playerdata_pr->db[r].diff);
                case 5: return playerdata_pr->db[r].level;
                case 6: return playerdata_pr->db[r].notes;
                case 7: return playerdata_pr->db[r].clear;
                case 8: return Label::clearLabel(playerdata_pr->db[r].clear);
                case 9: return playerdata_pr->db[r].score;
                case 10: if(playerdata_pr->db[r].rate.isValid())
                        return QString("%1").arg(playerdata_pr->db[r].rate.toDouble(), 5, 'f', 2);
                    else return QVariant();
                case 11: return playerdata_pr->db[r].rank;
                case 12: return playerdata_pr->db[r].bp;
                }
            }
            if(data_type == 1)
            {
                switch(c)
                {
                case 0: return playercompare_pr->db[r].ver;
                case 1: return Label::verLabel(playercompare_pr->db[r].ver);
                case 2: return playercompare_pr->db[r].title;
                case 3: return playercompare_pr->db[r].diff;
                case 4: return Label::diffLabel(playercompare_pr->db[r].diff);
                case 5: return playercompare_pr->db[r].level;
                case 6: return playercompare_pr->db[r].notes;
                case 7: return playercompare_pr->db[r].clear;
                case 8: return Label::clearLabel(playercompare_pr->db[r].clear);
                case 9: return playercompare_pr->db[r].score;
                case 10: if(playercompare_pr->db[r].rate.isValid())
                        return QString("%1").arg(playercompare_pr->db[r].rate.toDouble(), 5, 'f', 2);
                    else return QVariant();
                case 11: return playercompare_pr->db[r].rank;
                case 12: return playercompare_pr->db[r].bp;
                case 13: return playercompare_pr->db[r].clear_2;
                case 14: return Label::clearLabel(playercompare_pr->db[r].clear_2);
                case 15: return playercompare_pr->db[r].score_2;
                case 16: if(playercompare_pr->db[r].rate_2.isValid())
                        return QString("%1").arg(playercompare_pr->db[r].rate_2.toDouble(), 5, 'f', 2);
                    else return QVariant();
                case 17: return playercompare_pr->db[r].rank_2;
                case 18: return playercompare_pr->db[r].bp_2;
                case 19:
                {
                    if(!playercompare_pr->db[r].score.isValid() || !playercompare_pr->db[r].score_2.isValid())
                        return QVariant();
                    else return playercompare_pr->db[r].score.toInt() - playercompare_pr->db[r].score_2.toInt();
                }
                case 20:
                {
                    if(!playercompare_pr->db[r].bp.isValid() || !playercompare_pr->db[r].bp_2.isValid())
                        return QVariant();
                    return playercompare_pr->db[r].bp.toInt() - playercompare_pr->db[r].bp_2.toInt();
                }
                case 21: return playercompare_pr->db[r].score_compare;
                case 22: return playercompare_pr->db[r].bp_compare;
                case 23: return playercompare_pr->db[r].clear_compare;
                case 24: return playercompare_pr->db[r].full_compare;
                }
            }
            else return QVariant();
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal)
            {

                if(data_type == 0)
                {
                    switch (section)
                    {
                    case 1: return QString("Ver");
                    case 2: return QString("Title");
                    case 4: return QString("NHA");
                    case 5: return QString("Lv");
                    case 6: return QString("Notes");
                    case 8: return QString("Clear");
                    case 9: return QString("Score");
                    case 10: return QString("Rate");
                    case 12: return QString("Miss");
                    }
                }
                if(data_type == 1)
                {
                    switch (section)
                    {
                    case 1: return QString("Ver");
                    case 2: return QString("Title");
                    case 4: return QString("NHA");
                    case 5: return QString("Lv");
                    case 6: return QString("Notes");
                    case 8: return QString("A Clear");
                    case 9: return QString("Score");
                    case 10: return QString("Rate");
                    case 12: return QString("Miss");
                    case 14: return QString("B Clear");
                    case 15: return QString("Score");
                    case 16: return QString("Rate");
                    case 18: return QString("Miss");
                    case 19: return QString("ScoreD");
                    case 20: return QString("MissD");
                    }
                }
            }
            else
            return QVariant();
        }
        return QVariant();
    }



public:
    short data_type; // 0 = singledata, 1 = vs, 2 = all ver

private:
    PlayerData* playerdata_pr;
    PlayerCompare* playercompare_pr;
};

#endif // DATATABLE_H

