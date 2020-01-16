#ifndef SORTPROXY_H
#define SORTPROXY_H

#include <QSortFilterProxyModel>
#include <iostream>

class SortProxy: public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortProxy(int i){data_type = i;}

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
    {
        QString header_str = sourceModel()->headerData(source_left.column(), Qt::Horizontal).toString();
        QVariant leftData; QVariant rightData;
        if (source_left.column() == 1 || header_str.contains("Clear") || header_str.contains("NHA"))
        {
            int col = source_left.column() - 1;
            leftData = sourceModel()->data(sourceModel()->index(source_left.row(), col));
            rightData = sourceModel()->data(sourceModel()->index(source_right.row(), col));
        }
        else
        {
            leftData = sourceModel()->data(source_left);
            rightData = sourceModel()->data(source_right);
        }
        return leftData < rightData;
    }

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {
        if(data_type == 0)
        {
            bool level_flag = true;
            bool clear_flag = true;
            bool rank_flag = true;
            int level_col = 5;
            int clear_col = 7;
            int rank_col = 11;
            if(filter_level_ > 0) level_flag = sourceModel()->data(sourceModel()->index(source_row, level_col, source_parent)) == filter_level_;
            if(filter_clear_ >= 0) clear_flag = sourceModel()->data(sourceModel()->index(source_row, clear_col, source_parent)) == filter_clear_;
            if(filter_rank_ >= 0) rank_flag = sourceModel()->data(sourceModel()->index(source_row, rank_col, source_parent)) == filter_rank_;
            return level_flag && clear_flag && rank_flag;
        }
        else if(data_type == 1)
        {
            bool level_flag = true;
            bool type_flag = true;
            int level_col = 5;
            int filter_col = 21;

            if(filter_level_ > 0) level_flag = sourceModel()->data(sourceModel()->index(source_row, level_col, source_parent)) == filter_level_;
            if(filter_win < 4) type_flag = sourceModel()->data(sourceModel()->index(source_row, filter_col+filter_type, source_parent)) == filter_win;
            return level_flag && type_flag;
        }
    }

    void setFilterLevel(short lv)    {filter_level_ = lv;}

    // data_type == 0
    void setFilterClear(short cl)    {filter_clear_ = cl;}
    void setFilterRank(short rk)    {filter_rank_ = rk;}

    // data_type == 1
    void setFilterType(int type, int win) // i1 = type, i2 = WLDNA
    {
        filter_type = type;
        filter_win = win;
    }

    void changeType(int i){data_type = i;}

private:
    int data_type;
    int filter_level_ = -1;
    int filter_clear_ = -1;
    int filter_rank_ = -1;

    int filter_type = -1;
    int filter_win = -1;

};

#endif // SORTPROXY_H

