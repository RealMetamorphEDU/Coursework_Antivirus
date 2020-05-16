#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abrecordtokenizer.h"

class RecordViewModel;

QT_BEGIN_NAMESPACE

class QLabel;
class QProgressBar;


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
    explicit MainWindow(QWidget *parent = nullptr);
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
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
