//
// Created by Chrystalkey on 30.09.2018.
//

#include "ressourceloader.h"
#include <QtGui/QImage>
#include <QtWidgets/QMessageBox>

Q_DECLARE_METATYPE(QDomElement)

RessourceLoader::RessourceLoader() {}
RessourceLoader::~RessourceLoader() {
    for(BlockTexture &t:textures.values()){
        for(int i = 0; i < 6; i++){
            delete t.t[i];
        }
    }
}
bool RessourceLoader::parseBlockPrototypes(const QString &fileName) {
    xmlFile.setFileName(fileName);
    xmlFile.open(QFile::ReadOnly);
    QString errorString;
    int errLine,errColumn;
    if(!xml.setContent(&xmlFile,true,&errorString,&errLine,&errColumn)){
        QMessageBox::information(nullptr,"Error while parsing block_config.xml",
                                 QString("Parse error at line %1, column %2,: %3\n").arg(errLine).arg(errColumn).arg(errorString));
    }
    QDomElement root = xml.documentElement();
    if(root.tagName() != "blocks"){
        QMessageBox::information(nullptr,"Error while parsing block_config.xml",
                                 QString("The file is not a valid block_config.xml file"));
        return false;
    }
    QDomElement block = root.firstChildElement("block");
    while(!block.isNull()){
        parseBlockElement(&block);
    }
}

void RessourceLoader::parseBlockElement(QDomElement *block) {
    QDomElement name = block->firstChildElement("name");
    QDomElement textures = block->firstChildElement("textures");
    QDomElement attributes = block->firstChildElement("attributes");
    int i = 0;
    this->textures[name.nodeValue()] = BlockTexture();
    for(QDomElement txr=textures.firstChildElement("texture_file");!txr.isNull();txr=txr.nextSiblingElement("texture_file")){
        this->textures[name.nodeValue()].t[i++] = new QImage(txr.nodeValue());
    }
    this->blockAttributes[name.nodeValue()] = BlockPrototype();
    for(QDomElement attr=attributes.firstChildElement();!attr.isNull();attr=attr.nextSiblingElement()){
        this->blockAttributes[name.nodeValue()].attributes[attr.nodeName()] = attr.nodeValue();
    }
}