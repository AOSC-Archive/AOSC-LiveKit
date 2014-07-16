#include "ConfigureUserTab.h"
#include "ui_ConfigureUserTab.h"

ConfigureUserTab::ConfigureUserTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigureUserTab)
{
    ui->setupUi(this);
    ui->RootPassEdit_1->setEchoMode(QLineEdit::Password);
    ui->RootPassEdit_2->setEchoMode(QLineEdit::Password);
    ui->UserPassEdit_1->setEchoMode(QLineEdit::Password);
    ui->UserPassEdit_2->setEchoMode(QLineEdit::Password);
}

ConfigureUserTab::~ConfigureUserTab()
{
    delete ui;
}

int ConfigureUserTab::CheckInput(){
    if(ui->RootPassEdit_1->text().isEmpty()|| ui->RootPassEdit_2->text().isEmpty())     return NO_ROOT_PASS;
    else if(ui->UserPassEdit_1->text().isEmpty()||ui->UserPassEdit_2->text().isEmpty()) return NO_USER_PASS;
    else if(ui->UserNameEdit->text().isEmpty())                                         return NO_USER_NAME;
    else if(ui->RootPassEdit_1->text()!=ui->RootPassEdit_2->text())                     return ROOT_PASS_NOT_MATCH;
    else if(ui->UserPassEdit_1->text()!=ui->UserPassEdit_2->text())                     return USER_PASS_NOT_MATCH;
    else {
        ui->UserNameEdit->setText(ui->UserNameEdit->text().toLower());      //  转化成小写
        int i;
        for(i=0;i<ui->UserNameEdit->text().size();i++){
            if(ui->UserNameEdit->text().at(i) == ' '){
                return  USER_NAME_HAS_SPACE;
            }
        }
        return 0;
    }
}

QString ConfigureUserTab::GetUserName(){
    return ui->UserNameEdit->text();
}

QString ConfigureUserTab::GetUserPass(){
    return ui->UserPassEdit_1->text();
}

QString ConfigureUserTab::GetRootPass(){
    return ui->RootPassEdit_1->text();
}
