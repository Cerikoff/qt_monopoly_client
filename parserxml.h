#include <QMap>
#include <qxmlstream.h>
#include <QFile>
#include <QtDebug>

#ifndef PARSERXML_H
#define PARSERXML_H

class Parserxml : public QObject
{
private:
    QMap<QString, QString> map_xml;
public:
   Parserxml();
   bool parse(QString path);
   void addElement(QXmlStreamReader&, QMap<QString, QString>&);

};

#endif // PARSERXML_H
