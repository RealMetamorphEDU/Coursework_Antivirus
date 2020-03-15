#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include "abrecordtokenizer.h"
#include "recordviewmodel.h"
#include "editrecorddialog.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow: public QMainWindow {
Q_OBJECT
    bool saved;
    bool newBase;
    bool operating;

    ABRecordTokenizer tokenizer;

    RecordViewModel *recordView;

    QLabel *statusOpenLabel;
    QLabel *statusSaveLabel;
    QProgressBar *statusProgressBar;

    void disableButtons(bool yes);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showAddDialog();
    void showEditDialog();
    void showDelDialog();
    void newBaseOpen();
    void showOpenDialog();
    void saveBase();
    void showSaveDialog();
    void exit();
    bool confirmSave();
    void takeNextRecord(SignatureRecord *record, int number);
    void readFinished();
    void writeFinished();
signals:
    void writeRecord(SignatureRecord* record);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
