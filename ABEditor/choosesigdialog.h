#pragma once

#include <QDialog>

class QHexEdit;
class QFile;

class ChooseSigDialog: public QDialog {
Q_OBJECT
    QByteArray selected;
    QHexEdit *sigEdit;
public:
    ChooseSigDialog(QFile* file, QWidget *parent = nullptr);
    ~ChooseSigDialog();
    const QByteArray& getSelectedData();
private slots:
    void preAccepted();
};
