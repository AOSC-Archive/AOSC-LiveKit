/*                                                                              
 * Copyright (C) 2014 AnthonOS Open Source Community                               
 *               2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>                       
 */

#include <QCoreApplication>
#include <QLibraryInfo>
#include <QTextCodec>
#include <QLocale>
#include <QDebug>

#include "i18n.h"

I18N::I18N(const QString & path, const QString & encoding)
{
    m_path = path; m_encoding = encoding;
}

QString I18N::getEncoding() const { return m_encoding; }
void I18N::setEncoding(const QString & encoding) { m_encoding = encoding; }

QString I18N::getPath() const { return m_path; }
void I18N::setPath(const QString & path) { m_path = path; }

void I18N::translate()
{
    m_apTranslator.load(":/" + m_path + "/AOSC_Installer_" + 
        QLocale::system().name() + ".qm");
    
    m_qtTranslator.load("qt_" + QLocale::system().name(), 
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    QCoreApplication::installTranslator(&m_apTranslator);
    QCoreApplication::installTranslator(&m_qtTranslator);
}
