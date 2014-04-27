/*                                                                              
 * Copyright (C) 2014 AnthonOS Open Source Community                               
 *               2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>                       
 */

#ifndef I18N_H
#define I18N_H

#include <QTranslator>

class I18N
{
public:
    I18N(const QString & path, const QString & encoding);

    QString getPath() const;
    void setPath(const QString & path);

    QString getEncoding() const;
    void setEncoding(const QString & encoding);

    void translate();

private:
    QString m_path, m_encoding;
    QTranslator m_apTranslator, m_qtTranslator;
};

#endif // I18N_H
