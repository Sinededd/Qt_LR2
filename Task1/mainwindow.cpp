#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 400);

    createTable();
    createDock();
    createMenu();

}

MainWindow::~MainWindow() {}

Date MainWindow::selectedDate(bool *ok, int *id)
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
        return Date("");
    }
    for(int i = 0; i < selectedIndexes.size(); i++)
    {
        if(row != selectedIndexes.at(i).row())
        {
            *ok = 0;
            return Date("");
        }
    }

    Date curDate(tableModel->data(tableModel->index(row, 0)).toInt(),
                 tableModel->data(tableModel->index(row, 1)).toInt(),
                 tableModel->data(tableModel->index(row, 2)).toInt());
    if(id != nullptr)
        *id = row;

    return curDate;
}

void MainWindow::NextDay()
{
    bool ok = 0;
    Date curDate(selectedDate(&ok));
    if(!ok)
        return;

    QMessageBox messageBox;
    messageBox.setText("Следующий день: " + curDate.NextDay().getString());
    messageBox.setWindowTitle("");
    messageBox.exec();
}

void MainWindow::PreviousDay()
{
    bool ok = 0;
    Date curDate(selectedDate(&ok));
    if(!ok)
        return;

    QMessageBox messageBox;
    messageBox.setText("Предыдущий день: " + curDate.PreviousDay().getString());
    messageBox.setWindowTitle("");
    messageBox.exec();
}

void MainWindow::IsLeap()
{
    bool ok = 0;
    Date curDate(selectedDate(&ok));
    if(!ok)
        return;

    QMessageBox messageBox;
    if(curDate.IsLeap())
        messageBox.setText("Этот год высокосный");
    else
        messageBox.setText("Этот год не высокосный");
    messageBox.setWindowTitle("");
    messageBox.exec();
}

void MainWindow::WeekNumber()
{
    bool ok = 0;
    Date curDate(selectedDate(&ok));
    if(!ok)
        return;

    QMessageBox messageBox;
    QString nameOfWeek[7] = {"Понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"};
    messageBox.setText(nameOfWeek[curDate.WeekNumber() - 1]);
    messageBox.setWindowTitle("");
    messageBox.exec();
}

void MainWindow::addDate()
{
    bool ok = 0;
    Date curDate(inputDateBox(&ok));
    if(!ok)
        return;

    dates.append(curDate);
    updateTable();
}

void MainWindow::changeDate()
{
    bool ok = 0;
    int row = 0;
    selectedDate(&ok, &row);
    if(!ok)
        return;

    ok = 0;
    Date curDate(inputDateBox(&ok));
    if(!ok)
        return;

    dates[row] = curDate;
    updateTable();
}

void MainWindow::deleteDate()
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
        dates.remove(listRows.at(i));
        updateTable();
    }
}

Date MainWindow::inputDateBox(bool *ok, QString inputText)
{
    *ok =  1;
    QDialog *messageBox = new QDialog(this);

    QVBoxLayout *boxLayout = new QVBoxLayout(messageBox);
    QLabel *text = new QLabel(inputText);
    QDateEdit *timeEdit = new QDateEdit(messageBox);
    boxLayout->addWidget(text);
    boxLayout->addWidget(timeEdit);

    QHBoxLayout *buttonLay = new QHBoxLayout();
    QPushButton *buttonOk = new QPushButton(tr("&OK"), this);
    QPushButton *buttonCancel = new QPushButton(tr("&Cancel"), this);
    buttonLay->addWidget(buttonCancel);
    buttonLay->addWidget(buttonOk);
    boxLayout->addLayout(buttonLay);
    connect(buttonOk, &QPushButton::clicked, messageBox, &QDialog::accept);
    connect(buttonCancel, &QPushButton::clicked, messageBox, &QDialog::reject);

    messageBox->setLayout(boxLayout);

    if(messageBox->exec())
    {
        return Date(timeEdit->date().day(), timeEdit->date().month(), timeEdit->date().year());
    }
    else
    {
        *ok = 0;
        return Date("");
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
    nextDayButton = new QPushButton("Next day", dockContent);
    connect(nextDayButton, &QPushButton::clicked, this, &MainWindow::NextDay);
    previousDayButton = new QPushButton("Previous day", dockContent);
    connect(previousDayButton, &QPushButton::clicked, this, &MainWindow::PreviousDay);
    isLeapButton = new QPushButton("Is leap", dockContent);
    connect(isLeapButton, &QPushButton::clicked, this, &MainWindow::IsLeap);
    weekNumberButton = new QPushButton("Day of week", dockContent);
    connect(weekNumberButton, &QPushButton::clicked, this, &MainWindow::WeekNumber);
    durationButton = new QPushButton("Duration", dockContent);
    connect(durationButton, &QPushButton::clicked, this, &MainWindow::Duration);
    yourBithdayButton = new QPushButton("Your bithday", dockContent);
    connect(yourBithdayButton, &QPushButton::clicked, this, &MainWindow::DaysTillYourBithday);
    addButton = new QPushButton("Add", dockContent);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addDate);
    changeButton = new QPushButton("Change", dockContent);
    connect(changeButton, &QPushButton::clicked, this, &MainWindow::changeDate);
    deleteButton = new QPushButton("Delete", dockContent);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteDate);
    contentLayout->addWidget(nextDayButton);
    contentLayout->addWidget(previousDayButton);
    contentLayout->addWidget(isLeapButton);
    contentLayout->addWidget(weekNumberButton);
    contentLayout->addWidget(durationButton);
    contentLayout->addWidget(yourBithdayButton);
    contentLayout->addSpacing(30);
    contentLayout->addWidget(addButton);
    contentLayout->addWidget(changeButton);
    contentLayout->addWidget(deleteButton);

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
    tableModel = new QStandardItemModel(0, 3);
    tableModel->setHeaderData(0, Qt::Horizontal, "День");
    tableModel->setHeaderData(1, Qt::Horizontal, "Месяц");
    tableModel->setHeaderData(2, Qt::Horizontal, "Год");

    tableView = new QTableView(this);
    tableView->setModel(tableModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setCentralWidget(tableView);
}

void MainWindow::newDate()
{
    fileDirect = nullptr;
    dates.clear();
    updateTable();
}

void MainWindow::loadDate()
{
    fileDirect = new QString(QFileDialog::getOpenFileName(this, "Выберите файл", QDir::homePath()));
    if(FileDirect() == "")
        return;
    QFile file(FileDirect());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    dates.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        Date currentDate = Date(line);
        if(currentDate.IsCorrect())
        {
            dates.append(currentDate);
        }
    }
    updateTable();
}

void MainWindow::saveDate()
{
    if(FileDirect() == "" || !isOpenFile())
    {
        saveAsDate();
        return;
    }
    QFile file(FileDirect());
    if (!file.open(QIODevice::WriteOnly))
    {
        saveAsDate();
        return;
    }

    for(int i = 0; i < dates.count(); i++)
    {
        file.write((dates[i].getString() + '\n').toUtf8());
    }
}

void MainWindow::saveAsDate()
{
    fileDirect = new QString(QFileDialog::getSaveFileName(this, tr("Save File"),
                                                          (QDir::homePath() + "/date.txt"),
                                                          tr("Files (*.txt)")));
    if(FileDirect() == "")
        return;
    QFile file(FileDirect());
    file.open(QIODevice::WriteOnly);

    for(int i = 0; i < dates.count(); i++)
    {
        file.write((dates[i].getString() + '\n').toUtf8());
    }
}

void MainWindow::updateTable()
{
    tableModel->removeRows(0, tableModel->rowCount());
    for(int i = 0; i < dates.size(); i++)
    {
        QStandardItem *dayItem = new QStandardItem(QString::number(dates[i].Day()));
        QStandardItem *monthItem = new QStandardItem(QString::number(dates[i].Month()));
        QStandardItem *yearItem = new QStandardItem(QString::number(dates[i].Year()));
        QList<QStandardItem *> dateItem;
        dateItem << dayItem << monthItem << yearItem;
        tableModel->appendRow(dateItem);
    }

}

void MainWindow::DaysTillYourBithday()
{
    bool ok = 0;
    Date birthdayDate(inputDateBox(&ok, "Введите дату дня рождения: "));
    if(!ok)
        return;

    QMessageBox messageBox;
    messageBox.setText("До вашего дня рождения: " + QString::number(Date::DaysTillYourBithday(birthdayDate)) + " дней");
    messageBox.exec();
}

void MainWindow::Duration()
{
    bool ok = 0;
    Date curDate(selectedDate(&ok));
    if(!ok)
        return;

    QMessageBox messageBox;
    messageBox.setText("C данной даты: " + QString::number(curDate.Duration(Date::Now())) + " дней");
    messageBox.exec();
}
