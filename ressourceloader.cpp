//
// Created by Chrystalkey on 30.09.2018.
//
#include "ressourceloader.h"
#include <QtGui/QImage>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QFile>

RessourceLoader::RessourceLoader() {}
RessourceLoader::~RessourceLoader() {
    for(Texture *tex:allTextures){
        delete tex;
    }
}
bool RessourceLoader::parse_block_config(const QString &fileName) {
    QDomDocument xml("block_config");
    QFile xmlFile(fileName);
    xmlFile.open(QFile::ReadOnly);
    /*QString errorString;
    int errLine,errColumn;
    if(!xml.setContent(&xmlFile,true,&errorString,&errLine,&errColumn)){
        QMessageBox::information(nullptr,"Error while parsing block_config.xml",
                                 QString("Parse error at line %1, column %2,: %3\n").arg(errLine).arg(errColumn).arg(errorString));
    }
     */
    if(!xml.setContent(&xmlFile)){
        qDebug() << "Error while Parsing";
    }
    QDomElement root = xml.documentElement();
    if(root.tagName() != "blocks"){
        QMessageBox::information(nullptr,"Error while parsing block_config.xml",
                                 QString("The file is not a valid block_config.xml file"));
        return false;
    }
    QDomElement block = root.firstChildElement();
    while(!block.isNull()){
        parseBlockElement(&block);
        block = block.nextSiblingElement();
    }
}

void RessourceLoader::parseBlockElement(QDomElement *block) {
    QDomElement name = block->firstChildElement("name");
    QDomElement textures = block->firstChildElement("textures");
    QDomElement attributes = block->firstChildElement("attributes");
    prototypes[blockID++] = BlockPrototype();
    prototypes[blockID-1].textures.reserve(textures.childNodes().size());
    int i = 0;
    for(QDomElement element = textures.firstChildElement();!element.isNull();element = element.nextSiblingElement(),i++){
        prototypes[blockID-1].textures[i] = loadTexture(element.nodeValue());
    }
    for(QDomElement element = attributes.firstChildElement();!element.isNull();element = element.nextSiblingElement()){
        prototypes[blockID-1].attributes[element.nodeName()] = element.firstChild().toText().nodeValue();
    }
    qDebug() << prototypes[blockID-1].attributes;
}
Texture *RessourceLoader::loadTexture(const QString &fileName) {
    for(Texture *t:allTextures){
        if(t->fileName==fileName){
            return t;
        }
    }
    Texture *nTex = new Texture();
    nTex->fileName=fileName;
    nTex->id = textureID;
    nTex->texture = QImage(fileName);
    allTextures.push_back(nTex);
    return nTex;
}