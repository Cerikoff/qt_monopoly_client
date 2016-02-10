#include "parserxml.h"

Parserxml::Parserxml()
{

}

bool Parserxml::parse(QString path)
{
    QFile* file = new QFile(path);
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Can not open XML-config" << endl;
        return false;
    }
    QXmlStreamReader xml(file);

    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;
        if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name()=="root")
                    continue;
            else
                    addElement(xml, map_xml);
        }
    }

    return true;
}

void Parserxml::addElement(QXmlStreamReader &xml, QMap<QString, QString> &map)
{
    if(xml.tokenType()!=QXmlStreamReader::StartElement)
        return;
    QString elementName = xml.name().toString();
    xml.readNext();
    map.insert(elementName,xml.text().toString());
}


