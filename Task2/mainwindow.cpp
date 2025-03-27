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

void MainWindow::newFile()
{
    fileDirect = nullptr;
    students.clear();
    updateTable();
}

void MainWindow::loadFile()
{
    fileDirect = new QString(QFileDialog::getOpenFileName(this, "Выберите файл", QDir::homePath()));
    if(FileDirect() == "")
        return;
    QFile file(FileDirect());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    students.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList dataList = line.split(";");
        if(dataList.size() != 14)
            return;
        Student currentStudent = Student(dataList[0].toInt(), dataList[1], dataList[2], dataList[3]);
        for(int i = 0; i < 5; i++)
        {
            currentStudent.setMark(1, static_cast<Student::subjects>(i), dataList[i*2+4].toInt());
            currentStudent.setMark(2, static_cast<Student::subjects>(i), dataList[i*2+5].toInt());
        }
        students.append(currentStudent);
    }
    updateTable();
}

void MainWindow::saveFile()
{
    if(FileDirect() == "" || !isOpenFile())
    {
        saveAsFile();
        return;
    }
    QFile file(FileDirect());
    if (!file.open(QIODevice::WriteOnly))
    {
        saveAsFile();
        return;
    }

    for(int i = 0; i < students.count(); i++)
    {
        file.write((QString::number(students[i].group()) + ';' + students[i].surname() +';' +
                        students[i].name() + ';' + students[i].patronymic() ).toUtf8());
        QString marks;
        for(int j = 0; j < 5; j++)
        {
            marks += ';';
            marks += QString::number(students[i].getMark(1, static_cast<Student::subjects>(j))) + ';';
            marks += QString::number(students[i].getMark(2, static_cast<Student::subjects>(j)));
        }
        file.write((marks + '\n').toUtf8());
    }
}

void MainWindow::saveAsFile()
{
    fileDirect = new QString(QFileDialog::getSaveFileName(this, tr("Save File"),
                                                          (QDir::homePath() + "/date.txt"),
                                                          tr("Files (*.txt)")));
    if(FileDirect() == "")
        return;
    QFile file(FileDirect());
    file.open(QIODevice::WriteOnly);

    for(int i = 0; i < students.count(); i++)
    {
        file.write((QString::number(students[i].group()) + ';' + students[i].surname() +';' +
                    students[i].name() + ';' + students[i].patronymic() ).toUtf8());
        QString marks;
        for(int j = 0; j < 5; j++)
        {
            marks += ';';
            marks += QString::number(students[i].getMark(1, static_cast<Student::subjects>(j))) + ';';
            marks += QString::number(students[i].getMark(2, static_cast<Student::subjects>(j)));
        }
        file.write((marks + '\n').toUtf8());
    }
}

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
    bool ok = 0;
    int row = 0;
    selectedStudent(&ok, &row);
    if(!ok)
        return;

    Student newStudent(students[row]);
    ChangeDialog *dial = new ChangeDialog(newStudent, this);
    if(dial->exec())
        students[row] = newStudent;
    updateTable();
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

void MainWindow::searchStudent(QString text)
{
    for(int i = 0; i < students.size(); i++)
    {
        if(!QString::number(students[i].group()).startsWith(text) && !students[i].surname().startsWith(text) &&
            !students[i].name().startsWith(text) && !students[i].patronymic().startsWith(text))
        {
            tableView->hideRow(i);
        }
        else
        {
            tableView->showRow(i);
        }
    }
}

Student MainWindow::selectedStudent(bool *ok, int *id)
{
    *ok = 1;
    QItemSelectionModel* selectionModel = tableView->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    int row = 0;
    if(selectedIndexes.size() > 0)
    {
        row = selectedIndexes.at(0).row();
    }
    else
    {
        *ok = 0;
        return Student(0, "", "", "");
    }
    for(int i = 0; i < selectedIndexes.size(); i++)
    {
        if(row != selectedIndexes.at(i).row())
        {
            *ok = 0;
            return Student(0, "", "", "");
        }
    }

    Student curStudent(students[row]);
    if(id != nullptr)
        *id = row;

    return curStudent;
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
    connect(detailsButton, &QPushButton::clicked, this, &MainWindow::changeStudent);
    deleteStudentButton = new QPushButton("Удалить", dockContent);
    connect(deleteStudentButton, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    searchEdit = new QLineEdit(dockContent);
    searchEdit->setPlaceholderText("Поиск");
    connect(searchEdit, &QLineEdit::textEdited, this, &MainWindow::searchStudent);


    contentLayout->addWidget(newStudentButton);
    contentLayout->addWidget(detailsButton);
    contentLayout->addWidget(deleteStudentButton);
    contentLayout->addWidget(searchEdit);
    contentLayout->addStretch();
}

void MainWindow::createMenu()
{
    newAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew),
                         tr("&New"), this);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    openAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen),
                          tr("&Open"), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::loadFile);
    saveAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave),
                          tr("&Save"), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);
    saveAsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs),
                            tr("&Save as"), this);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAsFile);

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
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setSortIndicatorShown(true);

    setCentralWidget(tableView);
}
