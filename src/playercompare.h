#ifndef PLAYERCOMPARE_H
#define PLAYERCOMPARE_H
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QTextStream>
#include "common.h"

class Data2
{
public:
    Data2(QString& t, short d, short v, short l, unsigned int n,
          short c, QVariant& s, QVariant& r, short rk, QVariant& b,
          short c2, QVariant& s2, QVariant& r2, short rk2, QVariant& b2,
          int i1, int i2, int i3, int i4)
    {   title = t; diff = d; ver = v; level = l; notes = n;
        clear = c; score = s; rate = r; rank = rk; bp = b;
        clear_2 = c2; score_2 = s2; rate_2 = r2; rank_2 = rk2; bp_2 = b2,
        score_compare = i1; bp_compare = i2; clear_compare = i3; full_compare = i4;}

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

    // play data
    short clear_2; // 0 NO PLAY 1 FAILED 2 ASSIST CLEAR 3 EASY CLEAR 4 CLEAR 5 HARD CLEAR 6 EX-HARD CLEAR 7 FULL COMBO
    QVariant score_2; // unsigned int
    QVariant rate_2; // double
    short rank_2; // 0 F ... 5A 6AA 7 AAA
    QVariant bp_2; // unsigned int

    // compare result
    int score_compare;
    int bp_compare;
    int clear_compare;
    int full_compare;
};

class Subdata
{
public:
    Subdata()
    {
        clear = 0; score = QVariant(); rate = QVariant(); rank = 0; bp = QVariant();
    }
    Subdata(short c, QVariant& s, QVariant& r, short rk, QVariant& b)
    {
        clear = c; score = s; rate = r; rank = rk; bp = b;
    }

    short clear;
    QVariant score;
    QVariant rate;
    short rank;
    QVariant bp;
};

class PlayerCompare
{
public:
    PlayerCompare(const QString& id, const QString& ver, const QString& id_2, const QString& ver_2, const QString& style1)
    {
        id_a = id;
        ver_a = ver;
        id_b = id_2;
        ver_b = ver_2;
        style = style1;
        level_enum_count = 13; // 1 extra for all
        score_count.resize(5 * level_enum_count);
        clear_count.resize(5 * level_enum_count);
        full_count.resize(5 * level_enum_count);
        bp_count.resize(5 * level_enum_count);
    }


    bool loadCache()
    {
        // load DJ B first, form a map and put together with DJ A later
        QFile filename_b("./cache/" + id_b + "_" + ver_b + "_" + style + ".cache");
        if(!filename_b.exists() || !filename_b.open(QIODevice::ReadOnly | QIODevice::Text)) return 0;
        QJsonObject json_b = QJsonDocument::fromJson(filename_b.readAll()).object();
        filename_b.close();
        QJsonObject user_json_b = json_b.take("userdata").toObject();
        name_b = user_json_b["djname"].toString();

        QJsonArray musicdatas_b = json_b.value("musicdata").toArray();
        std::map<QString, Subdata> subdatas;
        for (int i = 0; i < musicdatas_b.size(); ++i)
        {
            QJsonObject musicdata = musicdatas_b.at(i).toObject();
            QJsonObject musicinfo = musicdata.value("data").toObject();

            QString id = musicinfo.value("id").toString() + musicinfo.value("diff").toString();
            short clear = musicdata.value("clear").toInt();
            unsigned int notes = musicinfo.value("notes").toInt();
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
            Subdata subdata(clear, score, rate, rank, bp);
            subdatas[id] = subdata;
        }

        // DJ A
        QFile filename("./cache/" + id_a + "_" + ver_a + "_" + style + ".cache");
        if(!filename.exists() || !filename.open(QIODevice::ReadOnly | QIODevice::Text)) return 0;
        QJsonObject json_a = QJsonDocument::fromJson(filename.readAll()).object();
        filename.close();

        QJsonObject user_json_a = json_a.take("userdata").toObject();
        name_a = user_json_a["djname"].toString();

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

            QString id = musicinfo.value("id").toString() + musicinfo.value("diff").toString();
            // retrieve data of DJ B
            short clear2 = 0;
            QVariant score2 = QVariant();
            QVariant rate2 = QVariant();
            short rank2 = 0;
            QVariant bp2 = QVariant();
            if (subdatas.find(id) != subdatas.end())
            {
                clear2 = subdatas.at(id).clear;
                score2 = subdatas.at(id).score;
                rate2 = subdatas.at(id).rate;
                rank2 = subdatas.at(id).rank;
                bp2 = subdatas.at(id).bp;
            }

            int i1, i2, i3, i4;

            // update count
            if(clear == 0 || clear2 == 0)
            {
                ++clear_count[(level-1)*5 + 3];
                ++full_count[(level-1)*5 + 3];
                ++clear_count[level * 5 - 1];
                ++full_count[level * 5 - 1];
                ++clear_count[level_enum_count * 5 - 1];
                ++full_count[level_enum_count * 5 - 1];
                i3 = 3; i4 = 3;
            }
            else
            {
                if (clear > clear2)
                {
                    ++clear_count[(level-1)*5];
                    ++clear_count[(level_enum_count-1)*5];
                    i3 = 0;
                }
                else if (clear < clear2)
                {
                    ++clear_count[(level-1)*5 + 1];
                    ++clear_count[(level_enum_count-1)*5 + 1];
                    i3 = 1;
                }
                else
                {
                    ++clear_count[(level-1)*5 + 2];
                    ++clear_count[(level_enum_count-1)*5 + 2];
                    i3 = 2;
                }
                ++clear_count[level * 5 - 1];
                ++clear_count[level_enum_count * 5 - 1];

                if (clear == 7 && clear2 < 7) {++full_count[(level-1)*5];++full_count[(level_enum_count-1)*5]; i4 = 0;}
                else if (clear < 7 && clear2 == 7) {++full_count[(level-1)*5 + 1];++full_count[(level_enum_count-1)*5 + 1]; i4 = 1;}
                else {++full_count[(level-1)*5 + 2];++full_count[(level_enum_count-1)*5 + 2]; i4 = 2;}
                ++full_count[level * 5 - 1];
                ++full_count[level_enum_count * 5 - 1];
            }

            if(!score.isValid() || !score2.isValid()) {++score_count[(level-1)*5 + 3]; ++score_count[(level_enum_count-1)*5 + 3]; i1 = 3;}
            else
            {
                int score_int = score.toInt();
                int score2_int = score2.toInt();
                if (score_int > score2_int) {++score_count[(level-1)*5];++score_count[(level_enum_count-1)*5]; i1 = 0;}
                else if (score_int < score2_int) {++score_count[(level-1)*5 + 1];++score_count[(level_enum_count-1)*5 + 1]; i1 = 1;}
                else {++score_count[(level-1)*5 + 2]; ++score_count[(level_enum_count-1)*5 + 2]; i1 = 2;}
            }
            ++score_count[level * 5 - 1];
            ++score_count[level_enum_count * 5 - 1];

            if(!bp.isValid() || !bp2.isValid()) {++bp_count[(level-1)*5 + 3]; ++bp_count[(level_enum_count-1)*5 + 3]; i2 = 3;}
            else
            {
                int bp_int = bp.toInt();
                int bp2_int = bp2.toInt();
                if (bp_int < bp2_int) {++bp_count[(level-1)*5]; ++bp_count[(level_enum_count-1)*5];i2 = 0;}
                else if (bp_int > bp2_int) {++bp_count[(level-1)*5 + 1]; ++bp_count[(level_enum_count-1)*5 + 1];i2 = 1;}
                else {++bp_count[(level-1)*5 + 2]; ++bp_count[(level_enum_count-1)*5 + 2];i2 = 2;}
            }
            ++bp_count[level * 5 - 1];
            ++bp_count[level_enum_count * 5 - 1];

            Data2 data2(title, diff, ver, level, notes, clear, score, rate, rank, bp, clear2, score2, rate2, rank2, bp2, i1, i2, i3, i4);
            db.push_back(data2);
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
            out << "Ver\tTitle\tDiff\tLevel\tNotes\t"
                << "DJ A Clear\tDJ A Score\tDJ A Rate\tDJ A BP\t"
                << "DJ B Clear\tDJ B Score\tDJ B Rate\tDJ B BP\t"
                << "Score Diff\tBP Diff\n";

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
                if (db[r].bp.isValid()) out << db[r].bp.toInt() << '\t';
                else out << " \t";
                out << Label::clearLabel(db[r].clear_2) << '\t';
                if (db[r].score_2.isValid()) out << db[r].score_2.toInt() << '\t';
                else out << " \t";
                if (db[r].rate_2.isValid()) out << QString("%1").arg(db[r].rate_2.toDouble(), 4, 'f', 2) << '\t';
                else out << " \t";
                if (db[r].bp_2.isValid()) out << db[r].bp_2.toInt() << '\t';
                else out << " \t";
                if (db[r].score.isValid() &&  db[r].score_2.isValid()) out << db[r].score.toInt() - db[r].score_2.toInt() << '\t';
                else out << " \t";
                if (db[r].bp.isValid() &&  db[r].bp_2.isValid()) out << db[r].bp.toInt() - db[r].bp_2.toInt() << '\n';
                else out << " \n";
            }
            file.close();
        }
    }

public:
    // Player Info
    QString id_a;
    QString ver_a;
    QString id_b;
    QString ver_b;
    QString style;
    QString name_a;
    QString name_b;

    QVector<short> score_count;
    QVector<short> clear_count;
    QVector<short> full_count;
    QVector<short> bp_count;

    // must be Win / Lose / Draw / NA / All
    short level_enum_count;

    std::vector<Data2> db;
};
#endif // PLAYERCOMPARE_H
