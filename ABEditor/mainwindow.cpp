#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
                                          , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    saved = true;
    newBase = false;
    statusOpenLabel = new QLabel("Файл базы данных не открыт", ui->statusbar);
    statusSaveLabel = new QLabel(ui->statusbar);
    statusProgressBar = new QProgressBar(ui->statusbar);
    ui->statusbar->addWidget(statusOpenLabel);
    ui->statusbar->addWidget(statusSaveLabel);
    ui->statusbar->addPermanentWidget(statusProgressBar);
    connect(ui->addButton, SIGNAL(clicked()), SLOT(showAddDialog()));
    connect(ui->editButton, SIGNAL(clicked()),SLOT(showEditDialog()));
    connect(ui->delButton, SIGNAL(clicked()), SLOT(showDelDialog()));
    connect(ui->createFile, SIGNAL(triggered()), SLOT(newBaseOpen()));
    connect(ui->openFile, SIGNAL(triggered()), SLOT(showOpenDialog()));
    connect(ui->saveFile, SIGNAL(triggered()), SLOT(saveBase()));
    connect(ui->saveFileAs, SIGNAL(triggered()), SLOT(showSaveDialog()));
    connect(ui->closeAll, SIGNAL(triggered()), this, SLOT(exit()));
    connect(&tokenizer, SIGNAL(nextRecord(SignatureRecord*, int, int)),
            SLOT(takeNextRecord(SignatureRecord*, int, int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showAddDialog() {
    qDebug() << "Add";
}

void MainWindow::showEditDialog() {
    qDebug() << "Edit";
}

void MainWindow::showDelDialog() {
    qDebug() << "Del";
}

void MainWindow::newBaseOpen() {
    // Если файл не сохранили, спросить, надо ли сохранить. Если да, но не сохранился, отмена операции
    if (!saved && confirmSave() && !saved)
        return;
    newBase = true;
    saved = true;
    tokenizer.close();
    
}

void MainWindow::showOpenDialog() {
    qDebug() << "Open";
}

void MainWindow::saveBase() {
    qDebug() << "Save";
}

void MainWindow::showSaveDialog() {
    qDebug() << "SaveAs";
}

void MainWindow::exit() {
    if (saved) {
        QApplication::exit(0);
    }
}

bool MainWindow::confirmSave() {

}

void MainWindow::takeNextRecord(SignatureRecord *record, int number, int maxNumber) {

}
