#ifndef PLAYERDATA_H
#define PLAYERDATA_H
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QTextStream>
#include "common.h"

class Data
{
public:
    Data(QString& t, short d, short v, short l, unsigned int n, short c, QVariant& s, QVariant& r, short rk, QVariant& b)
    {title = t; diff = d; ver = v; level = l; notes = n; clear = c; score = s; rate = r; rank = rk; bp = b;}

    // song info
    QString title;
    short diff; // 0 NORMAL, 1 HYPER, 2 ANOTHER
    short ver;
    short level;
    unsigned int notes;

    // play data
    short clear; // 0 NO PLAY 1 FAILED 2 ASSIST CLEAR 3 EASY CLEAR 4 CLEAR 5 HARD CLEAR 6 EX-HARD CLEAR 7 FULL COMBO
    QVariant score; // unsigned int
    QVariant rate; // double
    short rank; // 0 F ... 5A 6AA 7 AAA
    QVariant bp; // unsigned int
};

class PlayerData
{
public:
    PlayerData(const QString& id, const QString& ver, const QString& style1)
    {
        id_a = id;
        ver_a = ver;
        style = style1;
        clear_enum_count = 9;
        rank_enum_count = 9;
        level_enum_count = 13;
        clear_count.resize(clear_enum_count * level_enum_count);
        rank_count.resize(rank_enum_count * level_enum_count);
    }

    void loadUserData(const QJsonObject& user_json)
    {   
        name_a = user_json["djname"].toString();
        if(style == "SP") {class_a = user_json["spclass"].toInt(); djp_a = user_json["sppoint"].toDouble();}
        else {class_a = user_json["dpclass"].toInt(); djp_a = user_json["dppoint"].toDouble();}
    }

    bool loadCache()
    {
        QFile filename("./cache/" + id_a + "_" + ver_a + "_" + style + ".cache");
        if(!filename.exists() || !filename.open(QIODevice::ReadOnly | QIODevice::Text)) return 0;
        QJsonObject json_a = QJsonDocument::fromJson(filename.readAll()).object();
        filename.close();

        QJsonObject user_json_a = json_a.take("userdata").toObject();
        loadUserData(user_json_a);

        QJsonArray musicdatas = json_a.value("musicdata").toArray();

        for (int i = 0; i < musicdatas.size(); ++i)
        {
            QJsonObject musicdata = musicdatas.at(i).toObject();
            QJsonObject musicinfo = musicdata.value("data").toObject();

            QString title = musicinfo.value("title").toString();
            QString diffori = musicinfo.value("diff").toString();
            short diff;
            if(diffori.contains("n")) diff = 0;
            else if(diffori.contains("h")) diff = 1;
            else diff = 2;

            short ver = musicinfo.value("version").toString().toShort() * 10;
            if (ver == 0) ver = 15; // substream
            short level = musicinfo.value("level").toInt();
            unsigned int notes = musicinfo.value("notes").toInt();


            short clear = musicdata.value("clear").toInt();
            QVariant score = musicdata.value("score").toVariant();
            QVariant rate = QVariant::Invalid;
            short rank = 0;
            if(score.isValid())
            {
                rate = score.toDouble() / notes / 2 * 100;
                int rank_raw = int(rate.toDouble() * 9 / 100 + 1e-10);
                if (rank_raw <= 1) rank = 0;
                else if(rank_raw <= 8) rank = rank_raw - 1;
                else rank = 7;
            }
            QVariant bp = musicdata.value("miss").toVariant();
            Data data(title, diff, ver, level, notes, clear, score, rate, rank, bp);
            db.push_back(data);

            // update count
            ++clear_count[(level-1)*clear_enum_count + clear];
            ++clear_count[level * clear_enum_count - 1];
            ++rank_count[(level-1)*rank_enum_count + rank];
            ++rank_count[level * rank_enum_count - 1];
            ++clear_count[(level_enum_count-1)*clear_enum_count + clear];
            ++clear_count[level_enum_count * clear_enum_count - 1];
            ++rank_count[(level_enum_count-1)*rank_enum_count + rank];
            ++rank_count[level_enum_count * rank_enum_count - 1];
        }
        return 1;
    }

    void export_to_csv(QString& filename)
    {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");;
            out << "Ver\tTitle\tDiff\tLevel\tNotes\tClear\tScore\tRate\tBP\n";

            for (int r = 0; r < db.size(); ++r)
            {
                out << Label::verLabel(db[r].ver) << '\t'
                    << db[r].title << '\t'
                    << Label::diffLabel(db[r].diff) << '\t'
                    << db[r].level << '\t'
                    << db[r].notes << '\t'
                    << Label::clearLabel(db[r].clear) << '\t';
                if (db[r].score.isValid()) out << db[r].score.toInt() << '\t';
                else out << " \t";
                if (db[r].rate.isValid()) out << QString("%1").arg(db[r].rate.toDouble(), 4, 'f', 2) << '\t';
                else out << " \t";
                if (db[r].bp.isValid()) out << db[r].bp.toInt() << '\n';
                else out << " \n";
            }
            file.close();
        }
    }

public:
    // Player Info
    QString id_a;
    QString ver_a;
    QString style;

    QString name_a;
    int class_a;
    double djp_a;

    QVector<short> clear_count;
    QVector<short> rank_count;

    short clear_enum_count;
    short rank_enum_count;
    short level_enum_count;

    std::vector<Data> db;
};

#endif // PLAYERDATA_H
