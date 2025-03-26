#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(700, 500);

    createTable();
    createDock();
    createMenu();
}

MainWindow::~MainWindow() {}

void MainWindow::updateTable()
{
    tableModel->removeRows(0, tableModel->rowCount());
    for(int i = 0; i < students.size(); i++)
    {
        QStandardItem *groupItem = new QStandardItem(QString::number(students[i].group()));
        QStandardItem *surnameItem = new QStandardItem(students[i].surname());
        QStandardItem *nameItem = new QStandardItem(students[i].name());
        QStandardItem *patronymicItem = new QStandardItem(students[i].patronymic());
        int status = 0;
        for(int j = 0; j < 5; j++)
        {
            if(students[i].getMark(1, static_cast<Student::subjects>(j)) < 4)
            {
                status = 1;
                break;
            }
        }
        int badMarks = 0;
        for(int j = 0; j < 5; j++)
        {
            if(students[i].getMark(2, static_cast<Student::subjects>(j)) < 4)
            {
                badMarks++;
            }
            if(badMarks > 1 && status == 1)
            {
                status = 2;
                break;
            }
        }
        if(status == 0 && badMarks > 0)
            status = 1;
        QStandardItem *statusItem  = new QStandardItem("Нормис");
        statusItem->setForeground(Qt::green);
        switch (status) {
        case 1:
            statusItem->setText("Должник");
            statusItem->setForeground(Qt::yellow);
            break;
        case 2:
            statusItem->setText("Отчислен");
            statusItem->setForeground(Qt::red);
            break;
        }
        QList<QStandardItem *> studentItem;
        studentItem << groupItem << surnameItem << nameItem << patronymicItem << statusItem;
        tableModel->appendRow(studentItem);
    }
}

void MainWindow::addStudent()
{
    Student newStudent(0, "", "", "");
    ChangeDialog *dial = new ChangeDialog(newStudent, this);
    if(dial->exec())
        students.append(newStudent);
    updateTable();
}

void MainWindow::changeStudent()
{

}

void MainWindow::deleteStudent()
{
    QItemSelectionModel* selectionModel = tableView->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    QSet<int> selRows;
    for(int i = 0; i < selectedIndexes.size(); i++)
    {
        selRows.insert(selectedIndexes.at(i).row());
    }
    QList<int> listRows = selRows.values();
    std::sort(listRows.begin(), listRows.end());
    for(int i = listRows.count() - 1; i >= 0; i--)
    {
        students.remove(listRows.at(i));
        updateTable();
    }
}

void MainWindow::createDock()
{
    dock = new QDockWidget(this);
    dock->setFeatures(QDockWidget::DockWidgetFeatures({QDockWidget::DockWidgetClosable, QDockWidget::DockWidgetMovable}));
    dock->setAllowedAreas(Qt::DockWidgetAreas({Qt::LeftDockWidgetArea, Qt::RightDockWidgetArea}));
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dock);
    dockContent = new QWidget(dock);
    dock->setWidget(dockContent);

    QVBoxLayout *contentLayout = new QVBoxLayout(dockContent);
    newStudentButton = new QPushButton("Добавить", dockContent);
    connect(newStudentButton, &QPushButton::clicked, this, &MainWindow::addStudent);
    detailsButton = new QPushButton("Подробнее", dockContent);
    // connect(detailsButton, &QPushButton::clicked, this, &MainWindow::);
    deleteStudentButton = new QPushButton("Удалить", dockContent);
    connect(deleteStudentButton, &QPushButton::clicked, this, &MainWindow::deleteStudent);

    contentLayout->addWidget(newStudentButton);
    contentLayout->addWidget(detailsButton);
    contentLayout->addWidget(deleteStudentButton);
    contentLayout->addStretch();
}

void MainWindow::createMenu()
{
    newAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                         tr("&New"), this);
    connect(newAct, &QAction::triggered, this, &MainWindow::newDate);
    openAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                          tr("&Open"), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::loadDate);
    saveAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave),
                          tr("&Save"), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveDate);
    saveAsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs),
                            tr("&Save as"), this);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAsDate);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
}

void MainWindow::createTable()
{
    tableModel = new QStandardItemModel(0, 5);
    tableModel->setHeaderData(0, Qt::Horizontal, "Группа №");
    tableModel->setHeaderData(1, Qt::Horizontal, "Фамилия");
    tableModel->setHeaderData(2, Qt::Horizontal, "Имя");
    tableModel->setHeaderData(3, Qt::Horizontal, "Отчество");
    tableModel->setHeaderData(4, Qt::Horizontal, "Статус");

    tableView = new QTableView(this);
    tableView->setModel(tableModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setCentralWidget(tableView);
}
