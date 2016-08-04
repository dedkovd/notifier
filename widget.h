#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QFocusEvent>
#include <QMenu>

namespace Ui {
    class Widget;
}

class Menu: public QMenu
{
public:
   explicit Menu(QWidget *parent = 0)
   {
        new QMenu(parent);
   }

   void focusOutEvent(QFocusEvent *event)
   {
       hide();
       QMenu::focusOutEvent(event);
   }
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void onTimer();
    void exit();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void refreshButtonsState();

private:
    Ui::Widget *ui;
    QSystemTrayIcon *i;
    QHash<QString,QDateTime> dt;

    QDateTime getDateTime(const QString &fileName);
    QList<QString> files;

    void readSettings();
    void writeSettings();
};

#endif // WIDGET_H
