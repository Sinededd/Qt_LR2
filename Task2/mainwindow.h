#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student.h"
#include <changedialog.h>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QStandardItemModel>
#include <QTableView>
#include <QDockWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void newDate(){};
    void loadDate(){};
    void saveDate(){};
    void saveAsDate(){};
    void updateTable();

    void addStudent();
    void changeStudent();
    void deleteStudent();

private:
    void createDock();
    void createMenu();
    void createTable();

    QList<Student> students;

    QStandardItemModel *tableModel;
    QTableView *tableView;

    QDockWidget *dock;
    QWidget *dockContent;
    QPushButton *newStudentButton;
    QPushButton *detailsButton;
    QPushButton *deleteStudentButton;

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
};
#endif // MAINWINDOW_H
