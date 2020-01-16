#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),codec(QTextCodec::codecForName("UTF-8")),
    recent("./cache/recent.cache"),
    data_a(NULL),data_b(NULL),//data_c(NULL),
    table_a(NULL),table_b(NULL),
    datatable(NULL),
    sortproxy(new SortProxy(-1)),
    isreset(true),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    /*
    QFile filename = "./cache/test.cache";
    if(!filename.exists() || !filename.open(QIODevice::ReadOnly | QIODevice::Text)) std::cout << "error";
    QJsonObject json_a = QJsonDocument::fromJson(filename.readAll()).object();
    filename.close();
    */
    setInitial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteAll()
{
    QItemSelectionModel *m1 = ui->atableView->selectionModel();
    QItemSelectionModel *m2 = ui->btableView->selectionModel();
    ui->datatableView->setDisabled(true);
    isreset = true;
    //delete sortproxy;
    //delete table_a;
    //delete table_b;
    //delete datatable;
    //delete data_a;
    //delete data_b;
    //delete m1;
    //delete m2;
}

void MainWindow::saveRecent(short i)
{
    QString id = ui->alineEdit->text();
    QString id_1 = ui->b1lineEdit->text();
    QString id_2 = ui->b2lineEdit->text();

    if (recent.open(QIODevice::WriteOnly))
    {
        QTextStream out(&recent);
        out << i << "\t";
        if(!id.isEmpty()) {out << id.toUtf8() << "\t";}
        if(!id_1.isEmpty()) {out << id_1.toUtf8() << "\t";}
        if(!id_2.isEmpty()) {out << id_2.toUtf8() << "\t";}
        recent.close();
    }
}

void MainWindow::setInitial()
{
    ui->koishi_textEdit->setText(codec->toUnicode("\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000,..:\'\'::\"\u00B4::\uFFE3:::\uFFE3\uFF40::\u30FD.\uFF0F\uFFE3\uFF1E\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \uFF0F;:\u4E8C \u4E8C _\uFFE3\uFFE3\uFFE3\uFF40}\uFF1E\u304F\u00B4\uFFE3,}\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 ,. :\'\'\"\u00B4:::::::::::::::::::\uFFE3::::\uFFE3::\u4E8C::\u2010::\uFF40\uFF1C\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \uFF0F:::::::::::::;r \uFF70-\uFF64\uFF0F \uFFE3\uFF40\'\'\uFF70\'\u00B4\u3000\uFF40\u30FD\u3001::::::\uFF40\u30FD.\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000l:::::::::::::/\u00B4\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \uFF84\uFF64::::::::::::\',\u3000\u3000\u3000 ,.-\uFF64 \uFF0F \uFF09\u2510\n\u3000r\u2010 \uFF64\u3000\u3000\u3000\u3000\u30FD\uFF64\uFF0F\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000,\uFF8A\uFF3F\uFF8A\u3000\u30FD.\u3000\uFF89\u3001:::::::\uFF89\u3000\u3000\u3000/\u3000\uFF89\u3000\uFF0F /\n\u3000\'\uFF64\u3000 \uFF40\u30FD\u3001\u3000\uFF64_\u30CE\u3000\u3000\u3000\u3000__\u3000\uFF72\u3000\u3000\uFF0F_,\uFF63_/\uFF40i\u3000\u3000|\u3000\u3000 \u3009\uFF0F\u3000,r\uFF677\u00B4\u3000/ \u00B4\uFF64 \u30CE\uFF67\n\u3000 ,\u309D \uFF0F:\uFFE3_\uFF3C\u3009\u3000 \u3000 \'\u00B4__,/ |\u3000 / \uFF71,-\uFF64 \u30FD,\uFF84\uFF64\u3000\u3009\u3000 \uFF72\u2312\uFF0F l::::|\u3000\u3000\uFF09\u3000\u3000\u30BD\n\u3000\u30FD/:::::\uFF0F\u00B4 \u2220\u3000 \u3000 ,\uFF72\u00B4r\uFF67` |\uFF0F\u3000\u3000!_\u308A\u3000\uFF89|\u3000\uFF09\' \uFF8A \u3008\uFF0F\u3000\u3000l:::::!\u3000\u3000\u3000\u3000\u30CE\n\u3000\u3000!::::/\u3000\u3000 \u3000 \uFF89\u30A4\u3000\uFF8A!. l_\uFF98\u3000 , \u3000 \u3000 \u3000 \"\'\'\uFF89\u3000\u3000/,.\u30A4\u3000\u3000 \u3000 !::::i\u3000\uFF1E\u30A4\n\u3000\u3000\u30FDl \u3000 \u3000 \u3000 \u3000 \uFF9A\'\u30007\'\"\u3000\u3000r\uFF67\'\u00B4\uFFE3\u30FD\u3000\u2220,\u3000 \uFF0F/ \u3000 \u3000 \u3000 \',::::V\u00B4::::i\n\u3000\u3000\u3000 \uFF3C.\u3000\u3000 \u3000 \u3008\u3000,\u516B\u3000\u3000\u3000\u30FD\u3000\u3000 \u30CE\u3000\u3000\uFF89\u3000 !\u3000|\u3000\u3000\u3000\u3000\u3000\u3000\uFF3C:\uFF3C/\n\u3000\u3000 \u3000 \u3000 \uFF3C\u3000\u3000,\uFF89\u30A4\u3000 \uFF40\uFF1E \uFF64.,__\u3000\u3000 ,.\u30A4\u3008\u3000 \uFF89\u3000 |\u3000 \u3000 \u3000 ,. \u30A4\u00B4\uFFE3\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000 >\uFF64,\u3000 l\uFF0F\u3000\u3000 /\u00B4:;\uFF72_\u30A2\u00B4::::/}\uFF9A\'\u3000 \u3000|\u3000 \u3000 \uFF0F\u3000 i\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000 !\u3000 ` \uFF64\u3000\u3000\u3000\u039B/\u3008_\u3009\u30FD;:\u30CE\uFF63\u3000\u3000 \u3000 /\u3000 \uFF0F\u3000\u3000\u3000!\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \'\uFF64\u3000\u3000\u3000\uFF3C\u3000.!\u3000 \uFF40\u30FD\uFF64\u3000\u3000 \uFF3F\u3000 \uFF0F\u3000/\u3000\u3000\u3000\u3000 /\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \uFF3C\u3000 \u3000 \u30FD| \u3000 \u3008_\u3009 \uFF40Y;___\u30CEV \'\uFF64 /\u3000\u3000\u3000\u3000 /\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \u3000 \uFF40\"\'\'\u30FC-i\u3000\u3000 \u3000 \u3000 \'\uFF64;___;\uFF89\u3000 \uFF72\u3000\u3000\u3000 \uFF0F\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\',\u3000\u3000\u3008_\u3009\u3000\u3000\u3000\u3000\u3000\u3000 \u3009_,,.. \'\'\u00B4\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\uFF0F`\uFF70-\uFF67r - ..,,\uFF3F ,,..\u30CE \uFF3C\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000 r\u304F\u3000\u3000 \uFF0F::::\'\uFF64\u3000\u3000\u3000\u3000\u3000\u3000\u3000 \uFF89\uFF40\"\'\'\u30FC-\u2010\uFF67\n\u3000\u3000\u3000\u3000\u3000 \u3000 r.-\u2010.\'\'\"\u00B4:;::::`\uFF70\':::::::::::::::\uFF3C\uFF3F\u3000\u3000 \uFF0F::::::::::\uFF3C::::\u3008\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3009::\uFF3F::\uFF0F:::::/::::::::::::\uFF0F::::::::::::::\uFFE3:::::::::::::::::::::::\uFF3C:}\n\u3000 \u3000 \u3000 \u3000 \u3008\uFFE3::::::::::::::::/:::::::::::/\u00B4\uFFE3 \uFF40\u30FD;:::/:::::::;:::::::::::::::::::::::\uFF71\n\u3000\u3000\u3000\u3000\u3000\uFF0F\uFF40\u30FD;:::::::::\uFF0F:::::::::::::|\u3000\u3000\u3000 \u3000 |/:::::::::::\';:::::::::::::::::::\uFF89\n\u3000\u3000\u3000\u3000/\u3000\u3000 \u3000 \u30FDl\u00B4;\uFF40\u30FD\u3001::::::::|\u3000\u3000\u3000\u3000|/::::::::::::::::\';::::,.::-\uFF1C\n\u3000\u3000\u3000\u3000\'\uFF64\u3000\u3000\u3000\u3000\u3000V\u3000\u3000 \uFF3C;\u30CE|\u3000\u3000 \u3000 |::::::::::::::::::::l\u00B4\u3000\u3000\u3000\u3000\uFF40\u30FD.\n\u3000\u3000\u3000\u3000\u3000\uFF3C\u3000\u3000\u3000/\u3000\u3000\u3000\u3000/\u3000.!`\uFF70-\u2010\'\u00B4i`\'\u30FC--\u2010\'\u00B4\u3000\u3000\u3000\u3000\u3000\u3000\u3000\',\n\u3000\u3000 \u3000 \u3000 \u3000 \uFF40\"\'\'7\u3000\u3000\u3000\u3000/.,___|\u3000\u3000\u3000\u3000|\u2010 \u3001\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\uFF89\n\u3000\u3000 \u3000 \u3000 \u3000 \u3000 /\u3000\u3000\u3000\u3000/\u3000\u3000 !`\'\uFF70-\u2010\'\'\u00B4!\u30CE\u3000\u3000\u3000\u3000\u3000_,,.. -\u2010\'\'\"\u00B4\n\u3000\u3000\u3000\u3000\u3000\u3000\u3000_\u039B\u3000\u3000\u3000 /\u3000\u3000 /(`\u2312):\'\u00B4::| \u2010\'\' \" \u00B4\uFFE3\n\u3000\u3000\u3000\u3000\u3000\uFF67\'\u00B4/\u3000 \uFF40\'\uFF70\'\'\uFF17 \uFF70\u2010\'\' |::::\uFF40\'\u00B4:::::::::|\n\u3000\u3000\u3000\u3000\u3000\'\uFF64\u039B,\u3000\u3000\u3000 /\u3000\u3000 \u3000 \'\uFF64::::::::::::::/\n\u3000\u3000\u3000\u3000 \uFF0F\'-\uFF64`\uFF70-\u20107\u3000\u3000 \u3000 \u3000 \u30FD;__\uFF0F\n\u3000\u3000\u3000 / \'\uFF64_,\u30CE:::::::::::\uFF89\n\u3000\u3000\u3000 !::::::::::::::::::\uFF89\u00B4\n\u3000\u3000\u3000 `\u30FC -\u2010\'\u00B4\n"));
    ui->koishi_label->setText(codec->toUnicode("\u9589\u3058\u305f\u604b\u306e\u77b3\u3000\u53e4\u660e\u5730\u3053\u3044\u3057<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\uff5e \u6771\u65b9\u5730\u970a\u6bbf\u3088\u308a\u3000<br><br>&nbsp;&nbsp;&nbsp;\u3053\u3044\u3057\u3061\u3083\u3093\u304b\u308f\u3044\u3044"));
    ui->about_intro_label->setOpenExternalLinks(true);
    ui->about_intro_label->setText("<b>iidxdotmeViewer Ver 1.00 (Updated on 2016-02-05)</b><br>a small tool developed by <a href=http://iidx.me/rapiko>RAPIKO</a> for loading players data<br>on <a href=http://iidx.me>iidx.me</a> (powered by Kurosmitz / designed by Durumi).");
    ui->about_update_label->setText("<b>Update History</b><br>Ver 1.00 - First release.");
    ui->about_contact_label->setOpenExternalLinks(true);
    ui->about_contact_label->setText("<b>Contact</b><br>Any bug reports or suggestions are welcome.<br>Chinese: <a href=http://www.plurk.com/p/lgrkmo>Plurk</a><br>English / Japanese: (E-mail) rapianyo@gmail.com<br>I am sorry that I cannot speak Korean.");

    if(recent.exists())
    {
        if (recent.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray line = recent.readLine();
            QList<QByteArray> entries = line.split('\t');
            if(entries.size() > 0)
            { ui->tabWidget->setCurrentIndex(entries[0].toInt());}
            if(entries.size() > 1){ ui->alineEdit->setText(entries[1]);}
            if(entries.size() > 2){ ui->b1lineEdit->setText(entries[2]);}
            if(entries.size() > 3){ ui->b2lineEdit->setText(entries[3]);}
            recent.close();
        }
    }
    else ui->tabWidget->setCurrentIndex(0);
    ui->aloadlabel->setText("No data");
    ui->bloadlabel->setText("No data");
    setReady(0, false);
    setReady(1, false);

    ui->atableView->setAlternatingRowColors(true);

    ui->datatableView->setAlternatingRowColors(true);
    ui->datatableView->setSortingEnabled(true);
}

void MainWindow::setReady(short num, bool b)
{
    switch(num){
    case 0:
    {
        ui->a_exportpushButton->setEnabled(b);
        ui->aradioButton->setEnabled(b);
        ui->aradioButton_2->setEnabled(b);
        break;
    }
    case 1:
    {
        ui->b_exportpushButton->setEnabled(b);
        ui->bcomparecomboBox->setEnabled(b);
        break;
    }
    case 2:
    {
        break;
    }
    }
}

void MainWindow::loadPlayerData(const QString& id, const QString& ver, const QString& style, short num)
{
    if(id.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please input Player ID.");
        msgBox.exec();
        activateLoad(num, true);
    }
    else
    {
        deleteAll();
        data_a = new PlayerData(id, ver, style);
        ui->aloadlabel->setText("Loading..."); setReady(0, false);

        if(iscacheexist(id, ver, style))
        {
            if(ver == "copula")
            {
                // confirm if reload when ver is copula
                QMessageBox msgBox;
                msgBox.setText("Cache file found.\nReload from iidx.me?");
                msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                int reply = msgBox.exec();
                if (reply == QMessageBox::Yes) loadFromWeb(id, ver, style, num);
                else {activateLoad(num, true); prepareDataA();}
            }
            else {activateLoad(num, true); prepareDataA();}
        }
        else
        {
            loadFromWeb(id, ver, style, num);
        }
    }
}

void MainWindow::activateLoad(short num, bool b)
{
    switch(num){
    case 0: {ui->alineEdit->setEnabled(b); ui->acomboBox->setEnabled(b); ui->acomboBox_2->setEnabled(b); ui->apushButton->setEnabled(b); break;}
    case 1: {ui->b1lineEdit->setEnabled(b); ui->b2lineEdit->setEnabled(b);
        ui->b1comboBox->setEnabled(b); ui->b2comboBox->setEnabled(b); ui->bcomboBox->setEnabled(b);
        ui->bpushButton->setEnabled(b); break;}
    case 2: break;
    }
}

void MainWindow::loadFromWeb(const QString& id, const QString& ver, const QString& style, short num)
{
    QString verstr;
    if(ver == "copula") verstr = ""; // http://json.iidx.me/RAPIKO/sp/search/?l=..
    else if(ver == "PENDUAL") verstr = "dispv=pendual&"; // http://json.iidx.me/RAPIKO/sp/search/?dispv=pendual&l=..
    else if(ver == "SPADA") verstr = "dispv=spada&"; // http://json.iidx.me/RAPIKO/sp/search/?dispv=spada&l=..
    else verstr = "dispv=tricoro&"; // http://json.iidx.me/RAPIKO/sp/search/?dispv=tricoro&l=..
    QUrl url = "http://json.iidx.me/" + id + "/" + style.toLower() + "/search/?" + verstr + "l=..";
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    std::cout << "Downloading player data from " << url.toString().toStdString() << std::endl;
    switch(num)
    {
    case 0: connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadFromWebAFinished(QNetworkReply*))); break;
    case 1: connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadFromWebB1Finished(QNetworkReply*))); break;
    case 11: connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadFromWebB2Finished(QNetworkReply*))); break;
    case 3: connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadFromWebCFinished(QNetworkReply*))); break;
    }
    manager->get(request);
}

void MainWindow::prepareDataA()
{
    ui->aloadlabel->setText("OK!");
    setReady(0, true);

    // load cache file and prepare player data...
    bool success = data_a->loadCache();
    if( !success ) ui->aloadlabel->setText("Load cache failed.");
    else
    {
        // success!
        ui->anamelabel->setText("DJ " + data_a->name_a);
        ui->aclasslabel->setText(data_a->style + classText(data_a->class_a));
        ui->adjplabel->setText("DJ Point: " + QString::number(data_a->djp_a));

        table_a = new TableA(data_a);
        ui->atableView->setModel(table_a);
        ui->aradioButton->click();

        //data
        ui->datalabel->setText("Select a cell to show song details.");
    }
}

void MainWindow::prepareDataB()
{
    ui->bloadlabel->setText("OK!");
    setReady(1, true);

    // load cache file and prepare player data...
    bool success = data_b->loadCache();
    if( !success ) ui->bloadlabel->setText("Load cache failed.");
    else
    {
        // success!
        ui->bnamelabel->setText("DJ " + data_b->name_a +
                                " (" + data_b->ver_a + ") vs DJ "
                                 + data_b->name_b + " (" + data_b->ver_b + ") ("
                                 + data_b->style + ")");

        table_b = new TableB(data_b);
        ui->btableView->setModel(table_b);
        ui->bcomparecomboBox->setCurrentIndex(1);
        ui->bcomparecomboBox->setCurrentIndex(0);

        //data
        ui->datalabel->setText("Select a cell to show song details.");
    }
}

void MainWindow::loadFromWebAFinished(QNetworkReply *reply)
{
    if (reply->size() < 102400)
    {
        activateLoad(0, true);
        ui->aloadlabel->setText("ID not found");
    }
    else
    {
        QString filename = "./cache/" + data_a->id_a + "_" + data_a->ver_a + "_" + data_a->style + ".cache";
        QDir dir("./cache");
        if (!dir.exists()) dir.mkpath(".");
        std::cout << "Download finished. Write to cache file: " << filename.toStdString() << std::endl;
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "Could not open cache file %s for writing: %s\n",
                    qPrintable("test"),
                    qPrintable(file.errorString()));
        }
        file.write(reply->readAll());
        file.close();
        activateLoad(0, true);
        prepareDataA();
    }
}

void MainWindow::loadFromWebB1Finished(QNetworkReply *reply)
{
    if (reply->size() < 102400)
    {
        activateLoad(1, true);
        ui->bloadlabel->setText("DJ A ID not found");
    }
    else
    {
        QString filename = "./cache/" + data_b->id_a + "_" + data_b->ver_a + "_" + data_b->style + ".cache";
        QDir dir("./cache");
        if (!dir.exists()) dir.mkpath(".");
        std::cout << "Download finished. Write to cache file: " << filename.toStdString() << std::endl;
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "Could not open cache file %s for writing: %s\n",
                    qPrintable("test"),
                    qPrintable(file.errorString()));
        }
        file.write(reply->readAll());
        file.close();

        QString id_2 = ui->b2lineEdit->text();
        QString ver_2 = ui->b2comboBox->currentText();
        QString style = ui->bcomboBox->currentText();

        loadPlayerData2Next(id_2, ver_2, style, 1);
    }
}

void MainWindow::loadFromWebB2Finished(QNetworkReply *reply)
{
    if (reply->size() < 102400)
    {
        activateLoad(1, true);
        ui->bloadlabel->setText("DJ B ID not found");
    }
    else
    {
        QString filename = "./cache/" + data_b->id_b + "_" + data_b->ver_b + "_" + data_b->style + ".cache";
        QDir dir("./cache");
        if (!dir.exists()) dir.mkpath(".");
        std::cout << "Download finished. Write to cache file: " << filename.toStdString() << std::endl;
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "Could not open cache file %s for writing: %s\n",
                    qPrintable("test"),
                    qPrintable(file.errorString()));
        }
        file.write(reply->readAll());
        file.close();

        QString id_2 = ui->b2lineEdit->text();
        QString ver_2 = ui->b2comboBox->currentText();
        QString style = ui->bcomboBox->currentText();

        activateLoad(1, true);
        prepareDataB();
    }
}

void MainWindow::on_apushButton_clicked()
{
    activateLoad(0, false);

    QString id = ui->alineEdit->text();
    QString ver = ui->acomboBox->currentText();
    QString style = ui->acomboBox_2->currentText();
    saveRecent(0);
    loadPlayerData(id, ver, style, 0);
}

void MainWindow::on_aradioButton_clicked()
{
    table_a->setDisplayType(0);
    table_a->dataChanged(table_a->index(0,0), table_a->index(table_a->rowCount()-1, table_a->columnCount()-1));
    table_a->headerDataChanged(Qt::Horizontal, 0, table_a->columnCount());
    ui->atableView->resizeRowsToContents();
    for (int i = 0; i < table_a->columnCount(); ++i)
    {
        ui->atableView->setColumnWidth(i, 31);
    }
}

void MainWindow::on_aradioButton_2_clicked()
{
    table_a->setDisplayType(1);
    table_a->dataChanged(table_a->index(0,0), table_a->index(table_a->rowCount()-1, table_a->columnCount()-1));
    table_a->headerDataChanged(Qt::Horizontal, 0, table_a->columnCount());
    ui->atableView->resizeRowsToContents();
    for (int i = 0; i < table_a->columnCount(); ++i)
    {
        ui->atableView->setColumnWidth(i, 31);
    }
}

void MainWindow::on_atableView_activated(const QModelIndex &index)
{
    int r = index.row();
    int c = index.column();

    QVariant level_v = table_a->headerData(r, Qt::Vertical, Qt::DisplayRole);
    QVariant type_v = table_a->headerData(c, Qt::Horizontal, Qt::DisplayRole);
    QString qs = data_a->name_a + " (" +
            data_a->ver_a + ") (" +
            data_a->style + "): Level " + level_v.toString();
    if (type_v.toString() != "All") qs += " with " + type_v.toString();

    ui->datalabel->setText(qs);
    ui->datatableView->setEnabled(true);

    if(isreset || datatable->data_type != 0)
    {
        sortproxy->changeType(0);
        datatable = new DataTable(data_a);
        isreset = false;
    }
    sortproxy->setFilterLevel(level_v.toInt());
    if(table_a->display_type == 0)    {sortproxy->setFilterClear(c == table_a->columnCount() - 1 ? -1 : c);sortproxy->setFilterRank(-1);}
    else {sortproxy->setFilterClear(-1);sortproxy->setFilterRank(c == table_a->columnCount() - 1 ? -1 : c);}
    sortproxy->setSourceModel(datatable);
    ui->datatableView->setModel(sortproxy);
    ui->datatableView->resizeRowsToContents();
    ui->datatableView->setColumnWidth(1, 41); // Ver
    ui->datatableView->setColumnWidth(2, 365); // Title
    ui->datatableView->setColumnWidth(4, 33); // NHA
    ui->datatableView->setColumnWidth(5, 30); // Lv
    ui->datatableView->setColumnWidth(6, 41); // Notes
    ui->datatableView->setColumnWidth(8, 101); // Clear
    ui->datatableView->setColumnWidth(9, 41); // Score
    ui->datatableView->setColumnWidth(10, 38); // Rate
    ui->datatableView->setColumnWidth(12, 36); // Miss
    ui->datatableView->hideColumn(0);
    ui->datatableView->hideColumn(3);
    ui->datatableView->hideColumn(7);
    ui->datatableView->hideColumn(11);
}


// PlayerCompare
void MainWindow::on_bpushButton_clicked()
{
    activateLoad(1, false);
    QString id_1 = ui->b1lineEdit->text();
    QString ver_1 = ui->b1comboBox->currentText();
    QString id_2 = ui->b2lineEdit->text();
    QString ver_2 = ui->b2comboBox->currentText();
    QString style = ui->bcomboBox->currentText();
    saveRecent(1);
    loadPlayerData2(id_1, ver_1, style, 1, id_2, ver_2);
}

void MainWindow::loadPlayerData2(const QString& id, const QString& ver, const QString& style, short num, const QString& id_2, const QString& ver_2)
{
    if(id.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please input Player ID for DJ A.");
        msgBox.exec();
        activateLoad(num, true);
    }
    else if(id_2.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please input Player ID for DJ B.");
        msgBox.exec();
        activateLoad(num, true);
    }
    else
    {
        deleteAll();
        /*
        delete table_b; //delete sortproxy;
        if(datatable && datatable->data_type == 1) delete datatable;
        delete data_b;*/
        data_b = new PlayerCompare(id, ver, id_2, ver_2, style);
        ui->bloadlabel->setText("Loading..."); setReady(1, false);

        if(iscacheexist(id, ver, style))
        {
            if(ver == "copula")
            {
                // confirm if reload when ver is copula
                QMessageBox msgBox;
                msgBox.setText("Cache file found for DJ A.\nReload from iidx.me?");
                msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                int reply = msgBox.exec();
                if (reply == QMessageBox::Yes) loadFromWeb(id, ver, style, num);
                else {loadPlayerData2Next(id_2, ver_2, style, 1);}
            }
            else {loadPlayerData2Next(id_2, ver_2, style, 1);}
        }
        else
        {
            loadFromWeb(id, ver, style, num);
        }
    }
}

void MainWindow::loadPlayerData2Next(const QString& id, const QString& ver, const QString& style, short num)
{
    if(iscacheexist(id, ver, style))
    {
        if(ver == "copula")
        {
            // confirm if reload when ver is copula
            QMessageBox msgBox;
            msgBox.setText("Cache file found for DJ B.\nReload from iidx.me?");
            msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            int reply = msgBox.exec();
            if (reply == QMessageBox::Yes) loadFromWeb(id, ver, style, num+10);
            else {activateLoad(num, true); prepareDataB();}
        }
        else {activateLoad(num, true); prepareDataB();}
    }
    else
    {
        loadFromWeb(id, ver, style, num+10);
    }
}

void MainWindow::on_bcomparecomboBox_currentIndexChanged(int index)
{
    table_b->setDisplayType(index);
    table_b->dataChanged(table_b->index(0,0), table_b->index(table_b->rowCount()-1, table_b->columnCount()-1));
    // table_a->headerDataChanged(Qt::Horizontal, 0, table_a->columnCount());
    ui->btableView->resizeRowsToContents();
    for (int i = 0; i < table_b->columnCount(); ++i)
    {
        ui->btableView->setColumnWidth(i, 52);
    }

}

void MainWindow::on_btableView_activated(const QModelIndex &index)
{
    int r = index.row();
    int c = index.column();

    QVariant level_v = table_b->headerData(r, Qt::Vertical, Qt::DisplayRole);
    QVariant type_v = table_b->headerData(c, Qt::Horizontal, Qt::DisplayRole);
    QString qs = ui->bnamelabel->text() + ": Level " + level_v.toString();
    if (type_v.toString() != "All") qs += " with " + type_v.toString();
    ui->datalabel->setText(qs);
    ui->datatableView->setEnabled(true);
    if(isreset || datatable->data_type == 0) // NULL or different: reassign the pointer
    {
        sortproxy->changeType(1);
        datatable = new DataTable(data_b);
        isreset = false;
    }
    sortproxy->setFilterLevel(level_v.toInt());
    sortproxy->setFilterType(ui->bcomparecomboBox->currentIndex(), c);
    sortproxy->setSourceModel(datatable);
    ui->datatableView->setModel(sortproxy);
    ui->datatableView->resizeRowsToContents();
    ui->datatableView->setColumnWidth(1, 41); // Ver
    ui->datatableView->setColumnWidth(2, 265); // Title
    ui->datatableView->setColumnWidth(4, 33); // Title
    ui->datatableView->setColumnWidth(5, 30); // Lv
    ui->datatableView->setColumnWidth(6, 41); // Notes
    ui->datatableView->setColumnWidth(8, 101); // Clear
    ui->datatableView->setColumnWidth(9, 41); // Score
    ui->datatableView->setColumnWidth(10, 38); // Rate
    ui->datatableView->setColumnWidth(12, 36); // Miss
    ui->datatableView->setColumnWidth(14, 101); // Clear
    ui->datatableView->setColumnWidth(15, 41); // Score
    ui->datatableView->setColumnWidth(16, 38); // Rate
    ui->datatableView->setColumnWidth(18, 36); // Miss
    ui->datatableView->setColumnWidth(19, 48); // Score diff
    ui->datatableView->setColumnWidth(20, 45); // Miss diff
    ui->datatableView->hideColumn(0);
    ui->datatableView->hideColumn(3);
    ui->datatableView->hideColumn(7);
    ui->datatableView->hideColumn(11);
    ui->datatableView->hideColumn(13);
    ui->datatableView->hideColumn(17);
    ui->datatableView->hideColumn(21);
    ui->datatableView->hideColumn(22);
    ui->datatableView->hideColumn(23);
    ui->datatableView->hideColumn(24);
}

void MainWindow::on_a_exportpushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Export to csv"),
                                                    data_a->id_a + "_" + data_a->ver_a + "_" + data_a->style,
                                                    tr("Comma-separated values (*.csv)"));
    std::cout << filename.toStdString() << std::endl;
    data_a->export_to_csv(filename);
}

void MainWindow::on_b_exportpushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Export to csv"),
                                                    data_b->id_a + "_" + data_b->ver_a + "_" + data_b->id_b + "_" + data_b->ver_b + "_" + data_b->style,
                                                    tr("Comma-separated values (*.csv)"));
    std::cout << filename.toStdString() << std::endl;
    data_b->export_to_csv(filename);

}

void MainWindow::on_alineEdit_returnPressed()
{
    on_apushButton_clicked();
}

void MainWindow::on_b1lineEdit_returnPressed()
{
    on_bpushButton_clicked();
}

void MainWindow::on_b2lineEdit_returnPressed()
{
    on_bpushButton_clicked();
}
