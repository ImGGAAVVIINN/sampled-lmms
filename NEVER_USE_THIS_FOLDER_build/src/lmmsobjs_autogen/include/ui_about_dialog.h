/********************************************************************************
** Form generated from reading UI file 'about_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_DIALOG_H
#define UI_ABOUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *iconLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *versionLabel;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *copyrightLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *authorLabel;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QTextEdit *involvedLabel;
    QWidget *Seite;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *translationLabel;
    QWidget *Seite_2;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *licenseLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(504, 286);
        AboutDialog->setMinimumSize(QSize(504, 286));
        verticalLayout_3 = new QVBoxLayout(AboutDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        iconLabel = new QLabel(AboutDialog);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setMinimumSize(QSize(64, 64));

        horizontalLayout->addWidget(iconLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(AboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font:12pt; font-weight:bold;"));

        verticalLayout_2->addWidget(label);

        versionLabel = new QLabel(AboutDialog);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));

        verticalLayout_2->addWidget(versionLabel);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(AboutDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        copyrightLabel = new QLabel(tab);
        copyrightLabel->setObjectName(QString::fromUtf8("copyrightLabel"));
        copyrightLabel->setWordWrap(true);

        verticalLayout->addWidget(copyrightLabel);

        verticalSpacer_4 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        verticalLayout->addWidget(label_4);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        authorLabel = new QTextEdit(tab_2);
        authorLabel->setObjectName(QString::fromUtf8("authorLabel"));
        authorLabel->setReadOnly(true);

        verticalLayout_4->addWidget(authorLabel);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_7 = new QVBoxLayout(tab_3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_7->addWidget(label_5);

        involvedLabel = new QTextEdit(tab_3);
        involvedLabel->setObjectName(QString::fromUtf8("involvedLabel"));
        involvedLabel->setReadOnly(true);

        verticalLayout_7->addWidget(involvedLabel);

        tabWidget->addTab(tab_3, QString());
        Seite = new QWidget();
        Seite->setObjectName(QString::fromUtf8("Seite"));
        verticalLayout_5 = new QVBoxLayout(Seite);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        translationLabel = new QTextEdit(Seite);
        translationLabel->setObjectName(QString::fromUtf8("translationLabel"));
        translationLabel->setReadOnly(true);

        verticalLayout_5->addWidget(translationLabel);

        tabWidget->addTab(Seite, QString());
        Seite_2 = new QWidget();
        Seite_2->setObjectName(QString::fromUtf8("Seite_2"));
        verticalLayout_6 = new QVBoxLayout(Seite_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        licenseLabel = new QTextEdit(Seite_2);
        licenseLabel->setObjectName(QString::fromUtf8("licenseLabel"));
        licenseLabel->setReadOnly(true);

        verticalLayout_6->addWidget(licenseLabel);

        tabWidget->addTab(Seite_2, QString());

        verticalLayout_3->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "About LMMS", nullptr));
        label->setText(QCoreApplication::translate("AboutDialog", "LMMS", nullptr));
        versionLabel->setText(QCoreApplication::translate("AboutDialog", "Version %1 (%2/%3, Qt %4, %5).", nullptr));
        label_2->setText(QCoreApplication::translate("AboutDialog", "LMMS - easy music production for everyone.", nullptr));
        copyrightLabel->setText(QCoreApplication::translate("AboutDialog", "Copyright \302\251 %1.", nullptr));
        label_4->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><a href=\"https://lmms.io\"><span style=\" text-decoration: underline; color:#33cc33;\">https://lmms.io</span></a></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("AboutDialog", "About", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("AboutDialog", "Authors", nullptr));
        label_5->setText(QCoreApplication::translate("AboutDialog", "Contributors ordered by number of commits:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("AboutDialog", "Involved", nullptr));
        translationLabel->setPlainText(QCoreApplication::translate("AboutDialog", "Current language not translated (or native English).\n"
"If you're interested in translating LMMS in another language or want to improve existing translations, you're welcome to help us! Simply contact the maintainer!", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Seite), QCoreApplication::translate("AboutDialog", "Translation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Seite_2), QCoreApplication::translate("AboutDialog", "License", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_DIALOG_H
