#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndexList>
#include <QMessageBox>
#include <QTableView>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QDateTimeEdit>
#include <QSet>
#include <date.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Date selectedDate(bool *ok = nullptr, int *id = nullptr);
    bool isOpenFile() { return fileDirect == nullptr ? 0 : 1; }
    QString FileDirect() { return fileDirect == nullptr ? "" : *fileDirect; }
    void NextDay();
    void PreviousDay();
    void IsLeap();
    void WeekNumber();

    void addDate();
    void changeDate();
    void deleteDate();

    Date inputDateBox(bool *ok = nullptr, QString inputText = "Введите дату: ");

private:
    QString *fileDirect = nullptr;

    void createDock();
    void createMenu();
    void createTable();

    void newDate();
    void loadDate();
    void saveDate();
    void saveAsDate();

    void updateTable();
    void DaysTillYourBithday();
    void Duration();

    QList<Date> dates;

    QStandardItemModel *tableModel;
    QTableView *tableView;

    QDockWidget *dock;
    QWidget *dockContent;
    QPushButton *nextDayButton;
    QPushButton *previousDayButton;
    QPushButton *isLeapButton;
    QPushButton *weekNumberButton;
    QPushButton *yourBithdayButton;
    QPushButton *durationButton;

    QPushButton *addButton;
    QPushButton *changeButton;
    QPushButton *deleteButton;

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
};
#endif // MAINWINDOW_H
