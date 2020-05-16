/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *createFile;
    QAction *openFile;
    QAction *saveFile;
    QAction *saveFileAs;
    QAction *closeAll;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *delButton;
    QTableView *tableView;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(568, 444);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        MainWindow->setFont(font);
        createFile = new QAction(MainWindow);
        createFile->setObjectName(QString::fromUtf8("createFile"));
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QString::fromUtf8("openFile"));
        saveFile = new QAction(MainWindow);
        saveFile->setObjectName(QString::fromUtf8("saveFile"));
        saveFileAs = new QAction(MainWindow);
        saveFileAs->setObjectName(QString::fromUtf8("saveFileAs"));
        closeAll = new QAction(MainWindow);
        closeAll->setObjectName(QString::fromUtf8("closeAll"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(10);
        addButton->setFont(font1);

        horizontalLayout->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setFont(font1);

        horizontalLayout->addWidget(editButton);

        delButton = new QPushButton(centralwidget);
        delButton->setObjectName(QString::fromUtf8("delButton"));
        delButton->setFont(font1);

        horizontalLayout->addWidget(delButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setMinimumSectionSize(50);
        tableView->horizontalHeader()->setDefaultSectionSize(100);
        tableView->horizontalHeader()->setHighlightSections(false);
        tableView->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy1);
        statusbar->setFont(font);
        statusbar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 568, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font);
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(createFile);
        menuFile->addAction(openFile);
        menuFile->addSeparator();
        menuFile->addAction(saveFile);
        menuFile->addAction(saveFileAs);
        menuFile->addSeparator();
        menuFile->addAction(closeAll);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\261\320\260\320\267 \320\264\320\260\320\275\320\275\321\213\321\205 \320\260\320\275\321\202\320\270\320\262\320\270\321\200\321\203\321\201\320\260", nullptr));
        createFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        createFile->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \320\261\320\260\320\267\321\213</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        createFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        openFile->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        openFile->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\321\216\321\211\321\203\321\216 \320\261\320\260\320\267\321\203</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        openFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        saveFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        saveFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        saveFileAs->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", nullptr));
        closeAll->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
#if QT_CONFIG(shortcut)
        closeAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
