/********************************************************************************
** Form generated from reading UI file 'ctkEventTranslatorPlayerWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTKEVENTTRANSLATORPLAYERWIDGET_H
#define UI_CTKEVENTTRANSLATORPLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ctkEventTranslatorPlayerWidget
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *TestCaseLabel;
    QComboBox *TestCaseComboBox;
    QSpacerItem *verticalSpacer;
    QPushButton *TranslatorButton;
    QPushButton *PlayerButton;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ctkEventTranslatorPlayerWidget)
    {
        if (ctkEventTranslatorPlayerWidget->objectName().isEmpty())
            ctkEventTranslatorPlayerWidget->setObjectName(QString::fromUtf8("ctkEventTranslatorPlayerWidget"));
        ctkEventTranslatorPlayerWidget->resize(494, 331);
        centralwidget = new QWidget(ctkEventTranslatorPlayerWidget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        TestCaseLabel = new QLabel(centralwidget);
        TestCaseLabel->setObjectName(QString::fromUtf8("TestCaseLabel"));
        TestCaseLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(TestCaseLabel);

        TestCaseComboBox = new QComboBox(centralwidget);
        TestCaseComboBox->setObjectName(QString::fromUtf8("TestCaseComboBox"));

        verticalLayout->addWidget(TestCaseComboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        TranslatorButton = new QPushButton(centralwidget);
        TranslatorButton->setObjectName(QString::fromUtf8("TranslatorButton"));

        verticalLayout->addWidget(TranslatorButton);

        PlayerButton = new QPushButton(centralwidget);
        PlayerButton->setObjectName(QString::fromUtf8("PlayerButton"));

        verticalLayout->addWidget(PlayerButton);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(stackedWidget);

        ctkEventTranslatorPlayerWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ctkEventTranslatorPlayerWidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 494, 23));
        ctkEventTranslatorPlayerWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(ctkEventTranslatorPlayerWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ctkEventTranslatorPlayerWidget->setStatusBar(statusbar);

        retranslateUi(ctkEventTranslatorPlayerWidget);

        QMetaObject::connectSlotsByName(ctkEventTranslatorPlayerWidget);
    } // setupUi

    void retranslateUi(QMainWindow *ctkEventTranslatorPlayerWidget)
    {
        ctkEventTranslatorPlayerWidget->setWindowTitle(QApplication::translate("ctkEventTranslatorPlayerWidget", "MainWindow", 0, QApplication::UnicodeUTF8));
        TestCaseLabel->setText(QApplication::translate("ctkEventTranslatorPlayerWidget", "TestCase :", 0, QApplication::UnicodeUTF8));
        TranslatorButton->setText(QApplication::translate("ctkEventTranslatorPlayerWidget", "Record", 0, QApplication::UnicodeUTF8));
        PlayerButton->setText(QApplication::translate("ctkEventTranslatorPlayerWidget", "Playback", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ctkEventTranslatorPlayerWidget: public Ui_ctkEventTranslatorPlayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTKEVENTTRANSLATORPLAYERWIDGET_H
