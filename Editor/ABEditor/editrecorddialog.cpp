#include "editrecorddialog.h"

#include <qcryptographichash.h>


#include "choosesigdialog.h"
#include "ui_editrecorddialog.h"
#include "QMessageBox"

bool EditRecordDialog::checkFields() const {
    return !ui->nameEdit->text().isEmpty() && sigSet;
}

EditRecordDialog::EditRecordDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EditRecordDialog) {
    ui->setupUi(this);
    setWindowTitle("Добавить запись");
    setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    record = nullptr;
    sigSet = false;
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(checkAccept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->chooseSigButton, SIGNAL(clicked()), this, SLOT(chooseSig()));
    connect(ui->prefLenBox, SIGNAL(valueChanged(int)), this, SLOT(changedPrefixLen(int)));
}

EditRecordDialog::EditRecordDialog(SignatureRecord *record, QWidget *parent) : EditRecordDialog(parent) {
    this->record = record;
    sigSet = true;
    if (record != nullptr) {
        setWindowTitle("Изменить запись");
        ui->nameEdit->setText(record->getName());
        ui->lenBox->setValue(record->getSigLength());
        ui->prefixEdit->setText(record->getSigPrefix().toHex(' '));
        ui->hashEdit->setText(record->getSigHash().toHex(' '));
        ui->beginOffsetBox->setValue(record->getBeginOffset());
        ui->endOffsetBox->setValue(record->getEndOffset());
        ui->prefLenBox->setValue(record->getSigPrefix().size());
        ui->prefLenBox->setReadOnly(true);
    }
}

EditRecordDialog::~EditRecordDialog() {
    delete ui;
}

SignatureRecord* EditRecordDialog::getRecord() const {
    return record;
}

void EditRecordDialog::checkAccept() {
    if (!checkFields())
        return;
    if (record == nullptr)
        record = new SignatureRecord(this);
    record->setName(ui->nameEdit->text());
    record->setSigLength(ui->lenBox->value());
    record->setSigPrefix(selectedData.left(ui->prefLenBox->value()));
    record->setSigHash(QCryptographicHash::hash(selectedData, QCryptographicHash::Sha256));
    record->setBeginOffset(ui->beginOffsetBox->value());
    record->setEndOffset(ui->endOffsetBox->value());
    accept();
}

void EditRecordDialog::chooseSig() {
    QFileDialog fileDialog;
    fileDialog.setWindowTitle("Выберите файл");
    fileDialog.setOption(QFileDialog::DontConfirmOverwrite, true);
    fileDialog.setFilter(QDir::Readable | QDir::Executable);
    if (fileDialog.exec()) {
        auto *sigFile = new QFile(fileDialog.selectedFiles().at(0), this);
        if (sigFile->exists()) {
            ChooseSigDialog chooseSigDialog(sigFile);
            if (chooseSigDialog.exec()) {
                selectedData = chooseSigDialog.getSelectedData();
                chosenSig();
            }
        } else
            QMessageBox::warning(this, "Ошибка", "Файл не существует или его невозможно прочитать!", "Ок");
        sigFile->deleteLater();
    }
}

void EditRecordDialog::chosenSig() {
    if (selectedData.size() > 5) {
        int prefSize = ui->prefLenBox->value();
        ui->prefixEdit->setText(selectedData.left(prefSize).toHex(' '));
        ui->lenBox->setValue(selectedData.size());
        ui->hashEdit->setText(QCryptographicHash::hash(selectedData, QCryptographicHash::Sha1).toHex(' '));
        sigSet = true;
    } else {
        QMessageBox::warning(this, "Маленькая сигнатура", "Минимальный размер сигнатуры - 5 байт!", "Ок");
    }
}

void EditRecordDialog::changedPrefixLen(int value) const {
    ui->prefixEdit->setText(selectedData.left(value).toHex(' '));
}
