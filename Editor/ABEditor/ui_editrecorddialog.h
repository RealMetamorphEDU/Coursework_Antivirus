/********************************************************************************
** Form generated from reading UI file 'editrecorddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRECORDDIALOG_H
#define UI_EDITRECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditRecordDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *fieldLable_1;
    QLabel *fieldLable_2;
    QLabel *fieldLable_3;
    QLabel *fieldLable_4;
    QLabel *fieldLable_5;
    QLabel *fieldLable_6;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *lenBox;
    QLabel *label;
    QPushButton *chooseSigButton;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *prefixEdit;
    QSpinBox *prefLenBox;
    QLineEdit *hashEdit;
    QSpinBox *beginOffsetBox;
    QSpinBox *endOffsetBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *EditRecordDialog)
    {
        if (EditRecordDialog->objectName().isEmpty())
            EditRecordDialog->setObjectName(QString::fromUtf8("EditRecordDialog"));
        EditRecordDialog->resize(570, 230);
        EditRecordDialog->setModal(false);
        formLayoutWidget = new QWidget(EditRecordDialog);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 551, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        fieldLable_1 = new QLabel(formLayoutWidget);
        fieldLable_1->setObjectName(QString::fromUtf8("fieldLable_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, fieldLable_1);

        fieldLable_2 = new QLabel(formLayoutWidget);
        fieldLable_2->setObjectName(QString::fromUtf8("fieldLable_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, fieldLable_2);

        fieldLable_3 = new QLabel(formLayoutWidget);
        fieldLable_3->setObjectName(QString::fromUtf8("fieldLable_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, fieldLable_3);

        fieldLable_4 = new QLabel(formLayoutWidget);
        fieldLable_4->setObjectName(QString::fromUtf8("fieldLable_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, fieldLable_4);

        fieldLable_5 = new QLabel(formLayoutWidget);
        fieldLable_5->setObjectName(QString::fromUtf8("fieldLable_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, fieldLable_5);

        fieldLable_6 = new QLabel(formLayoutWidget);
        fieldLable_6->setObjectName(QString::fromUtf8("fieldLable_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, fieldLable_6);

        nameEdit = new QLineEdit(formLayoutWidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        lenBox = new QSpinBox(formLayoutWidget);
        lenBox->setObjectName(QString::fromUtf8("lenBox"));
        lenBox->setReadOnly(true);
        lenBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lenBox->setMaximum(1000100146);
        lenBox->setValue(0);

        horizontalLayout_2->addWidget(lenBox);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        chooseSigButton = new QPushButton(formLayoutWidget);
        chooseSigButton->setObjectName(QString::fromUtf8("chooseSigButton"));

        horizontalLayout_2->addWidget(chooseSigButton);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        prefixEdit = new QLineEdit(formLayoutWidget);
        prefixEdit->setObjectName(QString::fromUtf8("prefixEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prefixEdit->sizePolicy().hasHeightForWidth());
        prefixEdit->setSizePolicy(sizePolicy1);
        prefixEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(prefixEdit);

        prefLenBox = new QSpinBox(formLayoutWidget);
        prefLenBox->setObjectName(QString::fromUtf8("prefLenBox"));
        prefLenBox->setReadOnly(false);
        prefLenBox->setMinimum(5);
        prefLenBox->setMaximum(12);

        horizontalLayout_3->addWidget(prefLenBox);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_3);

        hashEdit = new QLineEdit(formLayoutWidget);
        hashEdit->setObjectName(QString::fromUtf8("hashEdit"));
        hashEdit->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, hashEdit);

        beginOffsetBox = new QSpinBox(formLayoutWidget);
        beginOffsetBox->setObjectName(QString::fromUtf8("beginOffsetBox"));
        beginOffsetBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        beginOffsetBox->setMaximum(1000);

        formLayout->setWidget(4, QFormLayout::FieldRole, beginOffsetBox);

        endOffsetBox = new QSpinBox(formLayoutWidget);
        endOffsetBox->setObjectName(QString::fromUtf8("endOffsetBox"));
        endOffsetBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        endOffsetBox->setMaximum(1000);

        formLayout->setWidget(5, QFormLayout::FieldRole, endOffsetBox);

        horizontalLayoutWidget = new QWidget(EditRecordDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 190, 551, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        saveButton = new QPushButton(horizontalLayoutWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout->addWidget(saveButton);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        QWidget::setTabOrder(nameEdit, chooseSigButton);
        QWidget::setTabOrder(chooseSigButton, beginOffsetBox);
        QWidget::setTabOrder(beginOffsetBox, endOffsetBox);
        QWidget::setTabOrder(endOffsetBox, saveButton);
        QWidget::setTabOrder(saveButton, lenBox);
        QWidget::setTabOrder(lenBox, hashEdit);
        QWidget::setTabOrder(hashEdit, cancelButton);

        retranslateUi(EditRecordDialog);

        QMetaObject::connectSlotsByName(EditRecordDialog);
    } // setupUi

    void retranslateUi(QDialog *EditRecordDialog)
    {
        EditRecordDialog->setWindowTitle(QCoreApplication::translate("EditRecordDialog", "empty", nullptr));
        fieldLable_1->setText(QCoreApplication::translate("EditRecordDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        fieldLable_2->setText(QCoreApplication::translate("EditRecordDialog", "\320\224\320\273\320\270\320\275\320\260 \321\201\320\270\320\263\320\275\320\260\321\202\321\203\321\200\321\213", nullptr));
        fieldLable_3->setText(QCoreApplication::translate("EditRecordDialog", "\320\237\321\200\320\265\321\204\320\270\320\272\321\201", nullptr));
        fieldLable_4->setText(QCoreApplication::translate("EditRecordDialog", "\320\245\321\215\321\210", nullptr));
        fieldLable_5->setText(QCoreApplication::translate("EditRecordDialog", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \321\201\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        fieldLable_6->setText(QCoreApplication::translate("EditRecordDialog", "\320\232\320\276\320\275\320\265\321\207\320\275\320\276\320\265 \321\201\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        lenBox->setSpecialValueText(QString());
        label->setText(QCoreApplication::translate("EditRecordDialog", "\320\261\320\260\320\271\321\202", nullptr));
        chooseSigButton->setText(QCoreApplication::translate("EditRecordDialog", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\270\320\263\320\275\320\260\321\202\321\203\321\200\321\203", nullptr));
        saveButton->setText(QCoreApplication::translate("EditRecordDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("EditRecordDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditRecordDialog: public Ui_EditRecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRECORDDIALOG_H
