#include "installerpage.h"
#include <stdio.h>
#include <QLabel>
#include <QTextBrowser>
#include <QFont>
#include <QFile>
#include <QDebug>

InstallerPage::InstallerPage(QWidget *parent):
    QWidget(parent){
    QFont cTitleFont;
    cTitleFont.setBold(true);
    cTitleFont.setPointSize(30);
    cTitle = new QLabel(this);
    cTitle->setFont(cTitleFont);
    cTitle->setGeometry(30,45,600,75);
    cContantFont.setBold(false);
    cContantFont.setPointSize(14);
}

InstallerPage::~InstallerPage(){

}

void InstallerPage::PervShow(){

}

void InstallerPage::SLOT_NextButtonClicked(void){

}

void InstallerPage::SLOT_PageChanged(QWidget *){

}

void InstallerPage::resizeEvent(QResizeEvent *){

}

void InstallerPage::SetContantTitle(const QString &str){
    cTitle->setText(str);
}

//----------------------------------//
//--------众神与愚民的分界线-----------//
//--------此刻正是昼夜交替时-----------//
//--------耀日将寝，皓月当空-----------//
//--------鬼哭狼嚎，铁骑千军-----------//
//----------------------------------//


WelcomePage::WelcomePage(InstallerPage *parent):
    InstallerPage(parent){
    Contant = new QLabel(this);
    this->SetContantTitle(tr("欢迎"));
    Contant->setText(tr("欢迎使用本AOSC系统半自动部署器\n您将在本部署器的指导下部署完成整个系统\n祝您使用愉快"));
    Contant->setGeometry(30,115,500,95);
    Contant->setFont(cContantFont);
}

WelcomePage::~WelcomePage(){
    delete Contant;
}

void WelcomePage::PervShow(){
    emit SIGN_SetPervButtonDisabled(true);
}

void WelcomePage::resizeEvent(QResizeEvent *){
}







ReadingPage::ReadingPage(InstallerPage *parent):
    InstallerPage(parent){
    ReadingBrowser  = new QTextBrowser(this);
    isAgreed        = new QCheckBox(this);
    QFile file(":/Argeement/License");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can not open";
    QTextStream in(&file);
    ReadingBrowser->setHtml(in.readAll());
    isAgreed->setText(tr("I Agree"));
    this->connect(isAgreed,SIGNAL(clicked(bool)),this,SLOT(AgreementChanged(bool)));
}

ReadingPage::~ReadingPage(){

}

void ReadingPage::AgreementChanged(bool Status){
    if(Status == true){
        emit SIGN_SetNextButtonDisabled(false);
    }else{
        emit SIGN_SetNextButtonDisabled(true);
    }
}

void ReadingPage::PervShow(){
    emit SIGN_SetNextButtonDisabled(true);
}

void ReadingPage::resizeEvent(QResizeEvent *){
    ReadingBrowser->setGeometry(0,0,this->width(),this->height()-25);
    isAgreed->setGeometry(this->width()-90,this->height()-25,100,20);
}
