#ifndef CHOOSESIGDIALOG_H
#define CHOOSESIGDIALOG_H

#include <QDialog>

class QHexEdit;
class QFile;

class ChooseSigDialog: public QDialog {
Q_OBJECT
    QByteArray selected;
    QHexEdit *sigEdit;
public:
    explicit ChooseSigDialog(QFile* file, QWidget *parent = nullptr);
    ~ChooseSigDialog();
    const QByteArray& getSelectedData();
private slots:
    void preAccepted();
};

#endif