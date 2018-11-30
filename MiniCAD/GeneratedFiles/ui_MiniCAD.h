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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniCADClass
{
public:
    QWidget *centralWidget;
    MiniCADWidget *showWidget;
    QGroupBox *sweepBox;
    QWidget *gridLayoutWidget;
    QGridLayout *sweepLayout;
    QLineEdit *lineEdit_sweep_y;
    QLineEdit *lineEdit_sweep_z;
    QLabel *Label_1;
    QLineEdit *lineEdit_sweep_l;
    QLabel *label_4;
    QLineEdit *lineEdit_sweep_x;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButton_sweep;
    QGroupBox *showBox;
    QCheckBox *checkBox_lineShow;
    QCheckBox *checkBox_volumeShow;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *SubfaceButton_Reset;
    QPushButton *SubfaceButton_Build;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QPushButton *OutLoopButton_Add;
    QPushButton *InLoopButton_New;
    QPushButton *OutLoopButton_Reset;
    QPushButton *InLoopButton_Add;
    QLabel *label;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLineEdit *OutLoopInput_x_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLineEdit *OutLoopInput_y;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *OutLoopInput_z;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *InLoopInput_x;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QLineEdit *InLoopInput_y;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QLineEdit *InLoopInput_z;
    QLabel *SubfacePointShowLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniCADClass)
    {
        if (MiniCADClass->objectName().isEmpty())
            MiniCADClass->setObjectName(QStringLiteral("MiniCADClass"));
        MiniCADClass->resize(1046, 700);
        centralWidget = new QWidget(MiniCADClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        showWidget = new MiniCADWidget(centralWidget);
        showWidget->setObjectName(QStringLiteral("showWidget"));
        showWidget->setGeometry(QRect(10, 10, 841, 631));
        sweepBox = new QGroupBox(centralWidget);
        sweepBox->setObjectName(QStringLiteral("sweepBox"));
        sweepBox->setGeometry(QRect(860, 95, 171, 171));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(12);
        sweepBox->setFont(font);
        gridLayoutWidget = new QWidget(sweepBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 151, 138));
        sweepLayout = new QGridLayout(gridLayoutWidget);
        sweepLayout->setSpacing(6);
        sweepLayout->setContentsMargins(11, 11, 11, 11);
        sweepLayout->setObjectName(QStringLiteral("sweepLayout"));
        sweepLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_sweep_y = new QLineEdit(gridLayoutWidget);
        lineEdit_sweep_y->setObjectName(QStringLiteral("lineEdit_sweep_y"));

        sweepLayout->addWidget(lineEdit_sweep_y, 1, 1, 1, 1);

        lineEdit_sweep_z = new QLineEdit(gridLayoutWidget);
        lineEdit_sweep_z->setObjectName(QStringLiteral("lineEdit_sweep_z"));

        sweepLayout->addWidget(lineEdit_sweep_z, 2, 1, 1, 1);

        Label_1 = new QLabel(gridLayoutWidget);
        Label_1->setObjectName(QStringLiteral("Label_1"));

        sweepLayout->addWidget(Label_1, 0, 0, 1, 1);

        lineEdit_sweep_l = new QLineEdit(gridLayoutWidget);
        lineEdit_sweep_l->setObjectName(QStringLiteral("lineEdit_sweep_l"));

        sweepLayout->addWidget(lineEdit_sweep_l, 3, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        sweepLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_sweep_x = new QLineEdit(gridLayoutWidget);
        lineEdit_sweep_x->setObjectName(QStringLiteral("lineEdit_sweep_x"));

        sweepLayout->addWidget(lineEdit_sweep_x, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        sweepLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        sweepLayout->addWidget(label_2, 1, 0, 1, 1);

        pushButton_sweep = new QPushButton(gridLayoutWidget);
        pushButton_sweep->setObjectName(QStringLiteral("pushButton_sweep"));
        pushButton_sweep->setMinimumSize(QSize(0, 20));

        sweepLayout->addWidget(pushButton_sweep, 4, 1, 1, 1);

        showBox = new QGroupBox(centralWidget);
        showBox->setObjectName(QStringLiteral("showBox"));
        showBox->setGeometry(QRect(860, 10, 171, 75));
        showBox->setFont(font);
        checkBox_lineShow = new QCheckBox(showBox);
        checkBox_lineShow->setObjectName(QStringLiteral("checkBox_lineShow"));
        checkBox_lineShow->setGeometry(QRect(25, 22, 121, 21));
        QFont font1;
        font1.setPointSize(11);
        checkBox_lineShow->setFont(font1);
        checkBox_volumeShow = new QCheckBox(showBox);
        checkBox_volumeShow->setObjectName(QStringLiteral("checkBox_volumeShow"));
        checkBox_volumeShow->setGeometry(QRect(25, 45, 121, 21));
        checkBox_volumeShow->setFont(font1);
        checkBox_volumeShow->setMouseTracking(true);
        checkBox_volumeShow->setTristate(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(860, 280, 171, 201));
        groupBox->setFont(font);
        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(14, 160, 151, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        SubfaceButton_Reset = new QPushButton(horizontalLayoutWidget);
        SubfaceButton_Reset->setObjectName(QStringLiteral("SubfaceButton_Reset"));

        horizontalLayout->addWidget(SubfaceButton_Reset);

        SubfaceButton_Build = new QPushButton(horizontalLayoutWidget);
        SubfaceButton_Build->setObjectName(QStringLiteral("SubfaceButton_Build"));

        horizontalLayout->addWidget(SubfaceButton_Build);

        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(13, 30, 151, 120));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        OutLoopButton_Add = new QPushButton(gridLayoutWidget_2);
        OutLoopButton_Add->setObjectName(QStringLiteral("OutLoopButton_Add"));

        gridLayout->addWidget(OutLoopButton_Add, 1, 2, 1, 1);

        InLoopButton_New = new QPushButton(gridLayoutWidget_2);
        InLoopButton_New->setObjectName(QStringLiteral("InLoopButton_New"));

        gridLayout->addWidget(InLoopButton_New, 3, 1, 1, 1);

        OutLoopButton_Reset = new QPushButton(gridLayoutWidget_2);
        OutLoopButton_Reset->setObjectName(QStringLiteral("OutLoopButton_Reset"));

        gridLayout->addWidget(OutLoopButton_Reset, 1, 1, 1, 1);

        InLoopButton_Add = new QPushButton(gridLayoutWidget_2);
        InLoopButton_Add->setObjectName(QStringLiteral("InLoopButton_Add"));

        gridLayout->addWidget(InLoopButton_Add, 3, 2, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        OutLoopInput_x_2 = new QLineEdit(gridLayoutWidget_2);
        OutLoopInput_x_2->setObjectName(QStringLiteral("OutLoopInput_x_2"));

        horizontalLayout_2->addWidget(OutLoopInput_x_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_3->addWidget(label_8);

        OutLoopInput_y = new QLineEdit(gridLayoutWidget_2);
        OutLoopInput_y->setObjectName(QStringLiteral("OutLoopInput_y"));

        horizontalLayout_3->addWidget(OutLoopInput_y);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_9 = new QLabel(gridLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_4->addWidget(label_9);

        OutLoopInput_z = new QLineEdit(gridLayoutWidget_2);
        OutLoopInput_z->setObjectName(QStringLiteral("OutLoopInput_z"));

        horizontalLayout_4->addWidget(OutLoopInput_z);


        gridLayout->addLayout(horizontalLayout_4, 0, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 10, -1, -1);
        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_5->addWidget(label_10);

        InLoopInput_x = new QLineEdit(gridLayoutWidget_2);
        InLoopInput_x->setObjectName(QStringLiteral("InLoopInput_x"));

        horizontalLayout_5->addWidget(InLoopInput_x);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 10, -1, -1);
        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_6->addWidget(label_11);

        InLoopInput_y = new QLineEdit(gridLayoutWidget_2);
        InLoopInput_y->setObjectName(QStringLiteral("InLoopInput_y"));

        horizontalLayout_6->addWidget(InLoopInput_y);


        gridLayout->addLayout(horizontalLayout_6, 2, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 10, -1, -1);
        label_12 = new QLabel(gridLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_7->addWidget(label_12);

        InLoopInput_z = new QLineEdit(gridLayoutWidget_2);
        InLoopInput_z->setObjectName(QStringLiteral("InLoopInput_z"));

        horizontalLayout_7->addWidget(InLoopInput_z);


        gridLayout->addLayout(horizontalLayout_7, 2, 2, 1, 1);

        SubfacePointShowLabel = new QLabel(centralWidget);
        SubfacePointShowLabel->setObjectName(QStringLiteral("SubfacePointShowLabel"));
        SubfacePointShowLabel->setGeometry(QRect(700, 20, 131, 521));
        SubfacePointShowLabel->setContextMenuPolicy(Qt::DefaultContextMenu);
        SubfacePointShowLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        MiniCADClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiniCADClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1046, 23));
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
        sweepBox->setTitle(QApplication::translate("MiniCADClass", "\346\214\244\345\207\272", Q_NULLPTR));
        Label_1->setText(QApplication::translate("MiniCADClass", " X\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("MiniCADClass", "L\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MiniCADClass", " Z\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("MiniCADClass", " Y\357\274\232", Q_NULLPTR));
        pushButton_sweep->setText(QApplication::translate("MiniCADClass", "Sweep", Q_NULLPTR));
        showBox->setTitle(QApplication::translate("MiniCADClass", "\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_lineShow->setText(QApplication::translate("MiniCADClass", "\347\272\277\346\241\206\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_volumeShow->setText(QApplication::translate("MiniCADClass", "\345\256\236\344\275\223\346\230\276\347\244\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MiniCADClass", "\345\272\225\351\235\242", Q_NULLPTR));
        SubfaceButton_Reset->setText(QApplication::translate("MiniCADClass", "Reset", Q_NULLPTR));
        SubfaceButton_Build->setText(QApplication::translate("MiniCADClass", "Build", Q_NULLPTR));
        OutLoopButton_Add->setText(QApplication::translate("MiniCADClass", "Add", Q_NULLPTR));
        InLoopButton_New->setText(QApplication::translate("MiniCADClass", "New", Q_NULLPTR));
        OutLoopButton_Reset->setText(QApplication::translate("MiniCADClass", "Reset", Q_NULLPTR));
        InLoopButton_Add->setText(QApplication::translate("MiniCADClass", "Add", Q_NULLPTR));
        label->setText(QApplication::translate("MiniCADClass", "OutLoop:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MiniCADClass", "InLoop:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MiniCADClass", "X", Q_NULLPTR));
        label_8->setText(QApplication::translate("MiniCADClass", "Y", Q_NULLPTR));
        label_9->setText(QApplication::translate("MiniCADClass", "Z", Q_NULLPTR));
        label_10->setText(QApplication::translate("MiniCADClass", "X", Q_NULLPTR));
        label_11->setText(QApplication::translate("MiniCADClass", "Y", Q_NULLPTR));
        label_12->setText(QApplication::translate("MiniCADClass", "Z", Q_NULLPTR));
        SubfacePointShowLabel->setText(QApplication::translate("MiniCADClass", "Subface Point : ", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MiniCADClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiniCADClass: public Ui_MiniCADClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINICAD_H
