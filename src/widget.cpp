#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QFileInfo>
#include <QSettings>
#include <QFileDialog>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    readSettings();

    foreach(const QString &s, files) {
        ui->listWidget->addItem(s);
        dt[s] = getDateTime(s);
    }

    Menu *m = new Menu(this);
    QAction *show = m->addAction(tr("Show"));
    QAction *exit = m->addAction(tr("Exit"));

    i = new QSystemTrayIcon(QIcon(":/updates"),this);
    i->geometry().setWidth(100);
    i->show();
    i->setContextMenu(m);

    refreshButtonsState();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    connect(exit,SIGNAL(triggered()),this,SLOT(exit()));
    connect(show,SIGNAL(triggered()),this,SLOT(show()));
    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(refreshButtonsState()));
    timer->start(6000);
}

void Widget::closeEvent(QCloseEvent *event){
    if (i->isVisible()) {
        hide();
        event->ignore();
    }
}

void Widget::exit()
{
    i->setVisible(false);
    close();
}

void Widget::onTimer()
{
    QStringList changedFiles;

    foreach (QString s, files)
    {
        if (dt[s] != getDateTime(s)) {
            changedFiles.append(s);
            dt[s] = getDateTime(s);
        }
    }

    if (changedFiles.size() > 0) {
        i->showMessage(tr("Updates"),tr("Updates aviable!\nUpdated files:\n%1").arg(changedFiles.join("\n")));
    }
}

QDateTime Widget::getDateTime(const QString &fileName)
{
    QFileInfo *f = new QFileInfo(fileName);
    if (f->exists())
    {
        return f->lastModified();
    }

    return QDateTime();
}

void Widget::refreshButtonsState()
{
    ui->removeButton->setEnabled(ui->listWidget->selectedItems().size() > 0);
}

Widget::~Widget()
{
    i->hide();
    delete ui;
}

void Widget::readSettings() {
    QSettings s("Home Inc", "Notifier", this);
    int size = s.beginReadArray("Files");
    for (int i=0; i<size; i++)
    {
        s.setArrayIndex(i);
        files.append(s.value("File").toString());
    }
    s.endArray();
}

void Widget::writeSettings() {
    QSettings s("Home Inc", "Notifier", this);
    s.beginWriteArray("Files",files.size());
    for (int i=0; i<files.size(); i++)
    {
        s.setArrayIndex(i);
        s.setValue("File",files.at(i));
    }
    s.endArray();
}

void Widget::on_addButton_clicked()
{
    QString fname = QFileDialog::getOpenFileName(this,tr("Select file"),QDir::homePath(),tr("All files (*.*)"));
    if (fname.length() > 0)
    {
        if (files.contains(fname))
        {
            ui->listWidget->findItems(fname, Qt::MatchFixedString).at(0)->setSelected(true);

        } else
        {
            dt[fname] = getDateTime(fname);
            files.append(fname);
            ui->listWidget->addItem(fname);
            ui->listWidget->findItems(fname, Qt::MatchFixedString).at(0)->setSelected(true);
            writeSettings();
        }
    }
}

void Widget::on_removeButton_clicked()
{
    foreach(QListWidgetItem *item, ui->listWidget->selectedItems())
    {
        files.removeAll(item->text());
    }

    ui->listWidget->clear();
    foreach(const QString &s, files) {
        ui->listWidget->addItem(s);
    }

    writeSettings();
}
