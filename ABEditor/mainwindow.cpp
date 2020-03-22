#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"

void MainWindow::disableButtons(bool yes) {
    ui->addButton->setDisabled(yes);
    ui->editButton->setDisabled(yes);
    ui->delButton->setDisabled(yes);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    saved = true;
    newBase = false;
    operating = false;
    recordView = new RecordViewModel(ui->centralwidget);
    statusOpenLabel = new QLabel("Файл базы данных не открыт", ui->statusbar);
    statusSaveLabel = new QLabel(ui->statusbar);
    statusProgressBar = new QProgressBar(ui->statusbar);
    ui->statusbar->addWidget(statusOpenLabel);
    ui->statusbar->addWidget(statusSaveLabel);
    ui->statusbar->addPermanentWidget(statusProgressBar);
    ui->tableView->setModel(recordView);
    ui->tableView->resizeColumnsToContents();
    disableButtons(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->addButton, SIGNAL(clicked()), SLOT(showAddDialog()));
    connect(ui->editButton, SIGNAL(clicked()),SLOT(showEditDialog()));
    connect(ui->delButton, SIGNAL(clicked()), SLOT(showDelDialog()));
    connect(ui->createFile, SIGNAL(triggered()), SLOT(newBaseOpen()));
    connect(ui->openFile, SIGNAL(triggered()), SLOT(showOpenDialog()));
    connect(ui->saveFile, SIGNAL(triggered()), SLOT(saveBase()));
    connect(ui->saveFileAs, SIGNAL(triggered()), SLOT(showSaveDialog()));
    connect(ui->closeAll, SIGNAL(triggered()), this, SLOT(exit()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showAddDialog() {
    EditRecordDialog dialog;
    if (dialog.exec()) {
        SignatureRecord *record = dialog.getRecord();
        recordView->addRecord(record);
        ui->tableView->resizeColumnsToContents();
        saved = false;
        statusSaveLabel->setText("");
    }
}

void MainWindow::showEditDialog() {
    QModelIndexList list = ui->tableView->selectionModel()->selectedRows();
    if (list.empty())
        return;
    int row = list.at(0).row();
    SignatureRecord *record = recordView->getRecords().at(row);
    EditRecordDialog dialog(record);
    if (dialog.exec()) {
        recordView->updateRow(row);
        ui->tableView->resizeColumnsToContents();
        saved = false;
        statusSaveLabel->setText("");
    }
}

void MainWindow::showDelDialog() {
    QModelIndexList list = ui->tableView->selectionModel()->selectedRows();
    if (list.empty())
        return;
    int row = list.at(0).row();
    recordView->removeRow(row);
    saved = false;
    statusSaveLabel->setText("");
}

void MainWindow::newBaseOpen() {
    // Если файл не сохранили, спросить, надо ли сохранить. Если да, но не сохранился, отмена операции
    if (operating)
        return;
    if (!saved && confirmSave() && !saved)
        return;
    newBase = true;
    saved = true;
    recordView->clear();
    tokenizer.close();
    disableButtons(false);
    statusOpenLabel->setText("Новый файл");
    statusProgressBar->setValue(0);
}

void MainWindow::showOpenDialog() {
    if (operating)
        return;
    if (!saved && confirmSave() && !saved)
        return;
    QFileDialog fileDialog;
    fileDialog.setWindowTitle("Открыть файл");
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setOption(QFileDialog::DontConfirmOverwrite, true);
    fileDialog.setFilter(QDir::Readable | QDir::Executable);
    fileDialog.setNameFilter("ADB file (*.adb)");
    if (fileDialog.exec()) {
        QStringList list = fileDialog.selectedFiles();
        if (list.size() == 0)
            return;
        recordView->clear();
        tokenizer.close();
        tokenizer.setBaseFile(list.at(0));
        newBase = false;
        saved = true;
        ui->addButton->setDisabled(false);
        ui->editButton->setDisabled(false);
        ui->delButton->setDisabled(false);
        statusOpenLabel->setText(list.at(0));
        statusProgressBar->setValue(0);
        int status = -1;//tokenizer.prepareForRead();
        if (status == -1) {
            statusSaveLabel->setText("Файл повреждён");
            operating = true;
            disableButtons(true);
        } else
            statusProgressBar->setRange(0, status);
    }
}

void MainWindow::saveBase() {
    if (operating)
        return;
    if (newBase)
        showSaveDialog();
    else {
        operating = true;
        disableButtons(true);
        tokenizer.prepareForWrite(recordView->getRecords().size());
        statusProgressBar->setRange(0, recordView->getRecords().size());
        for (int i = 0; i < recordView->getRecords().size(); ++i) {
            statusProgressBar->setValue(i + 1);
            emit writeRecord(recordView->getRecords().at(i));
        }
        saved = true;
        statusSaveLabel->setText("Сохранено");
    }
}

void MainWindow::showSaveDialog() {
    if (operating)
        return;
    QFileDialog fileDialog;
    fileDialog.setWindowTitle("Сохранить файл");
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setOption(QFileDialog::DontConfirmOverwrite, false);
    fileDialog.setFilter(QDir::Readable | QDir::Executable);
    fileDialog.setNameFilter("ADB file (*.adb)");
    if (fileDialog.exec()) {
        QStringList list = fileDialog.selectedFiles();
        if (list.empty())
            return;
        tokenizer.close();
        tokenizer.setBaseFile(list.at(0));
        newBase = false;
        saved = true;
        statusOpenLabel->setText(list.at(0));
        statusProgressBar->setValue(0);
        newBase = false;
        saveBase();
    }
}

void MainWindow::exit() {
    if (operating)
        return;
    if (!saved && confirmSave() && !saved)
        return;
    QApplication::exit(0);
}

bool MainWindow::confirmSave() {
    //TODO
    return false;
}

void MainWindow::takeNextRecord(SignatureRecord *record, int number) {
    statusProgressBar->setValue(number);
    record->moveToThread(QThread::currentThread());
    recordView->addRecord(record);
}

void MainWindow::readFinished() {
    operating = false;
    ui->tableView->resizeColumnsToContents();
    disableButtons(false);
}

void MainWindow::writeFinished() {
    operating = false;
    disableButtons(false);
}
