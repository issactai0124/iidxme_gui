#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QNetworkReply>
#include <QObject>
#include <QSortFilterProxyModel>
#include <QTextCodec>
#include <QUrl>

#include <iostream>
#include <sstream>

#include "playerdata.h"
#include "playercompare.h"
#include "tablea.h"
#include "tableb.h"
#include "datatable.h"
#include "sortproxy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private: // member
    Ui::MainWindow *ui;
    QFile recent;
    QTextCodec *codec;
    PlayerData* data_a;
    TableA* table_a;
    TableB* table_b;
    DataTable* datatable;
    SortProxy* sortproxy;
    PlayerCompare* data_b;
    bool isreset;
    //PlayerData* data_c;

private: // function
    void deleteAll();


    void saveRecent(short i);
    void setInitial();
    void setReady(short num, bool b);
    void loadPlayerData(const QString& id, const QString& ver, const QString& style, short num);
    void loadPlayerData2(const QString& id, const QString& ver, const QString& style, short num, const QString& id_2, const QString& ver_2);
    void loadPlayerData2Next(const QString& id, const QString& ver, const QString& style, short num);
    void activateLoad(short num, bool b);

    bool iscacheexist(const QString& id, const QString& ver, const QString& style)
    {
        QString filename = "./cache/" + id + "_" + ver + "_" + style + ".cache";
        return QFile::exists(filename);
    }

    QString classText(int i)
    {
        switch(i){
        case 1: return QString("-");
        case 2: return codec->toUnicode("\u4E03\u7d1A");
        case 3: return codec->toUnicode("\u516D\u7d1A");
        case 4: return codec->toUnicode("\u4E94\u7D1A");
        case 5: return codec->toUnicode("\u56DB\u7D1A");
        case 6: return codec->toUnicode("\u4E09\u7D1A");
        case 7: return codec->toUnicode("\u4E8C\u7D1A");
        case 8: return codec->toUnicode("\u4E00\u7D1A");
        case 9: return codec->toUnicode("\u521D\u6BB5");
        case 10: return codec->toUnicode("\u4E8C\u6BB5");
        case 11: return codec->toUnicode("\u4E09\u6BB5");
        case 12: return codec->toUnicode("\u56DB\u6BB5");
        case 13: return codec->toUnicode("\u4E94\u6BB5");
        case 14: return codec->toUnicode("\u516D\u6BB5");
        case 15: return codec->toUnicode("\u4E03\u6BB5");
        case 16: return codec->toUnicode("\u516B\u6BB5");
        case 17: return codec->toUnicode("\u4E5D\u6BB5");
        case 18: return codec->toUnicode("\u5341\u6BB5");
        case 19: return codec->toUnicode("\u4E2D\u4F1D");
        case 20: return codec->toUnicode("\u7686\u4F1D");
        default: return QString("N/A");
        }
    }

    void loadFromWeb(const QString& id, const QString& ver, const QString& style, short num);
    void prepareDataA();
    void prepareDataB();

private slots:
    void loadFromWebAFinished(QNetworkReply *reply);
    void loadFromWebB1Finished(QNetworkReply *reply);
    void loadFromWebB2Finished(QNetworkReply *reply);

    void loadFromWebCFinished(QNetworkReply *reply)
    {
        std::cout << "loadBFinished" << std::endl;
    }

private slots:
    void on_apushButton_clicked();
    void on_aradioButton_clicked();
    void on_aradioButton_2_clicked();
    void on_atableView_activated(const QModelIndex &index);
    void on_bpushButton_clicked();
    void on_bcomparecomboBox_currentIndexChanged(int index);
    void on_btableView_activated(const QModelIndex &index);
    void on_a_exportpushButton_clicked();
    void on_b_exportpushButton_clicked();
    void on_alineEdit_returnPressed();
    void on_b1lineEdit_returnPressed();
    void on_b2lineEdit_returnPressed();
};

#endif // MAINWINDOW_H
