#pragma once

#include <QDialog>
#include <QFileDialog>
#include "signaturerecord.h"

namespace Ui {
    class EditRecordDialog;
};


class EditRecordDialog: public QDialog {
Q_OBJECT
    SignatureRecord *record;
    bool sigSet;
    QByteArray selectedData;
    bool checkFields();
public:
    EditRecordDialog(QWidget *parent = Q_NULLPTR);
    EditRecordDialog(SignatureRecord *record, QWidget *parent = Q_NULLPTR);
    ~EditRecordDialog();
    SignatureRecord* getRecord();
private slots:
    void checkAccept();
    void chooseSig();
    void choosedSig();
    void changedPrefixLen(int value);
private:
    Ui::EditRecordDialog *ui;
};
