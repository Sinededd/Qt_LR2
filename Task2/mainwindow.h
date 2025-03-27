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
#include <QFileDialog>
#include <QHeaderView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void newFile();
    void loadFile();
    void saveFile();
    void saveAsFile();
    void updateTable();

    void addStudent();
    void changeStudent();
    void deleteStudent();
    void searchStudent(QString text);

    Student selectedStudent(bool *ok = nullptr, int *id = nullptr);
    QString FileDirect() { return fileDirect == nullptr ? "" : *fileDirect; }
     bool isOpenFile() { return fileDirect == nullptr ? 0 : 1; }

private:
    QString *fileDirect = nullptr;

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
    QLineEdit *searchEdit;

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
};
#endif // MAINWINDOW_H
