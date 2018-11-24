/********************************************************************************
** Form generated from reading UI file 'MiniCAD.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINICAD_H
#define UI_MINICAD_H

#include <MiniCADWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniCADClass
{
public:
    QWidget *centralWidget;
    MiniCADWidget *showWidget;
    QGroupBox *modelBox;
    QRadioButton *radioButton_model2D;
    QRadioButton *radioButton_model3D;
    QGroupBox *sweepBox;
    QDoubleSpinBox *doubleSpinBox_sweep;
    QGroupBox *showBox;
    QCheckBox *checkBox_lineShow;
    QCheckBox *checkBox_volumeShow;
    QListView *solidList;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniCADClass)
    {
        if (MiniCADClass->objectName().isEmpty())
            MiniCADClass->setObjectName(QStringLiteral("MiniCADClass"));
        MiniCADClass->resize(1049, 700);
        centralWidget = new QWidget(MiniCADClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        showWidget = new MiniCADWidget(centralWidget);
        showWidget->setObjectName(QStringLiteral("showWidget"));
        showWidget->setGeometry(QRect(10, 10, 841, 631));
        modelBox = new QGroupBox(centralWidget);
        modelBox->setObjectName(QStringLiteral("modelBox"));
        modelBox->setGeometry(QRect(860, 10, 171, 91));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        modelBox->setFont(font);
        radioButton_model2D = new QRadioButton(modelBox);
        radioButton_model2D->setObjectName(QStringLiteral("radioButton_model2D"));
        radioButton_model2D->setGeometry(QRect(20, 30, 91, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Adobe Arabic"));
        font1.setPointSize(12);
        radioButton_model2D->setFont(font1);
        radioButton_model3D = new QRadioButton(modelBox);
        radioButton_model3D->setObjectName(QStringLiteral("radioButton_model3D"));
        radioButton_model3D->setGeometry(QRect(20, 60, 89, 16));
        radioButton_model3D->setFont(font1);
        sweepBox = new QGroupBox(centralWidget);
        sweepBox->setObjectName(QStringLiteral("sweepBox"));
        sweepBox->setGeometry(QRect(860, 110, 171, 71));
        sweepBox->setFont(font1);
        doubleSpinBox_sweep = new QDoubleSpinBox(sweepBox);
        doubleSpinBox_sweep->setObjectName(QStringLiteral("doubleSpinBox_sweep"));
        doubleSpinBox_sweep->setGeometry(QRect(20, 30, 131, 21));
        QFont font2;
        font2.setPointSize(14);
        doubleSpinBox_sweep->setFont(font2);
        showBox = new QGroupBox(centralWidget);
        showBox->setObjectName(QStringLiteral("showBox"));
        showBox->setGeometry(QRect(860, 190, 171, 91));
        showBox->setFont(font1);
        checkBox_lineShow = new QCheckBox(showBox);
        checkBox_lineShow->setObjectName(QStringLiteral("checkBox_lineShow"));
        checkBox_lineShow->setGeometry(QRect(20, 30, 121, 21));
        QFont font3;
        font3.setPointSize(11);
        checkBox_lineShow->setFont(font3);
        checkBox_volumeShow = new QCheckBox(showBox);
        checkBox_volumeShow->setObjectName(QStringLiteral("checkBox_volumeShow"));
        checkBox_volumeShow->setGeometry(QRect(20, 60, 121, 21));
        checkBox_volumeShow->setFont(font3);
        solidList = new QListView(centralWidget);
        solidList->setObjectName(QStringLiteral("solidList"));
        solidList->setGeometry(QRect(860, 290, 171, 351));
        MiniCADClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiniCADClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1049, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MiniCADClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MiniCADClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MiniCADClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MiniCADClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniCADClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(MiniCADClass);

        QMetaObject::connectSlotsByName(MiniCADClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniCADClass)
    {
        MiniCADClass->setWindowTitle(QApplication::translate("MiniCADClass", "MiniCAD", Q_NULLPTR));
        modelBox->setTitle(QApplication::translate("MiniCADClass", "\346\250\241\345\274\217", Q_NULLPTR));
        radioButton_model2D->setText(QApplication::translate("MiniCADClass", "2D\346\250\241\345\274\217", Q_NULLPTR));
        radioButton_model3D->setText(QApplication::translate("MiniCADClass", "3D\346\250\241\345\274\217", Q_NULLPTR));
        sweepBox->setTitle(QApplication::translate("MiniCADClass", "\346\214\244\345\207\272", Q_NULLPTR));
        showBox->setTitle(QApplication::translate("MiniCADClass", "\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_lineShow->setText(QApplication::translate("MiniCADClass", "\347\272\277\346\241\206\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_volumeShow->setText(QApplication::translate("MiniCADClass", "\345\256\236\344\275\223\346\230\276\347\244\272", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MiniCADClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiniCADClass: public Ui_MiniCADClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINICAD_H
